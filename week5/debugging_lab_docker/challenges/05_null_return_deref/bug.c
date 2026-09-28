/*
 * Challenge 05 — NULL 반환 미확인 역참조 (심화: 설정 템플릿 확장기)
 *
 * [시나리오]
 *   key=value 설정 저장소(Config)와, "${key}" 자리표시자를 실제 값으로 치환하는
 *   템플릿 확장기 expand() 를 만든다. 예: "http://${host}:${port}/${path}".
 *
 * [기대 동작]
 *   템플릿의 모든 ${key} 를 설정값으로 치환한 최종 문자열을 출력.
 *
 * [증상]
 *   cfg_get() 은 키가 없으면 NULL 을 돌려준다. expand() 는 이 반환값을 검사하지 않고
 *   곧장 strlen()/memcpy() 에 넘긴다. 템플릿에 설정에 없는 키(${path})가 섞여 있으면
 *   그 순간 v==NULL 이 되어 strlen(NULL) 에서 SIGSEGV.
 *   크래시는 strlen(libc) 안에서 나지만, 원인은 "검사 없이 흘려보낸 NULL 반환값"이다.
 *
 * [gdb 로 잡기]
 *   make gdb NAME=05_null_return_deref
 *   (gdb) run                     → 크래시(SIGSEGV)
 *   (gdb) bt                      → strlen ← expand ← main
 *   (gdb) frame 1 ; print key      → 어떤 키를 찾다가 죽었는지(예: "path")
 *   (gdb) print v                  → v == 0x0 (cfg_get 이 NULL 을 돌려줬음)
 *   (gdb) break expand             → 각 ${key} 마다 cfg_get 결과를 살펴 NULL 을 잡기
 *
 * [printf(로그)로 잡기]
 *   치환 직전 키와 조회 결과 포인터를 함께 찍는다:
 *     fprintf(stderr, "expand key=%s v=%p\n", key, (void*)v);
 *   → v 가 (nil) 로 찍힌 키가 원인.
 *   (stdout 은 버퍼링되니 stderr 로 찍어야 크래시 직전 로그가 남는다)
 *
 * TODO: cfg_get() 의 NULL 반환을 반드시 검사하라. 없는 키는 기본값("")으로 대체하거나
 *       명시적 오류로 처리한다("사용 전에 검사" 원칙).
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KV 16
typedef struct {
    const char *keys[MAX_KV];
    const char *vals[MAX_KV];
    int n;
} Config;

static void cfg_set(Config *c, const char *k, const char *v) {
    if (c->n < MAX_KV) { c->keys[c->n] = k; c->vals[c->n] = v; c->n++; }
}

static const char *cfg_get(const Config *c, const char *k) {
    for (int i = 0; i < c->n; i++)
        // strcmp(c->key[i], k)함수란 c->key[i]와 k의 문자열을 비교하는 함수 같다면 0, 첫 번째가 앞선다 음수, 두 번째가 앞선다 양수 
        // 만약 두 문자열이 일치한다면 value값 반환, 일치하지 않는다면 NULL반환
        if (strcmp(c->keys[i], k) == 0) return c->vals[i]; 
    return NULL;                       /* 없는 키 → NULL */
}

static int expand(const Config *c, const char *tmpl, char *out, size_t outcap) {
    size_t o = 0;
    for (const char *p = tmpl; *p; ) { // tmpl의 주소를 포인터 지역변수 p에 담고, p의 값(문자열) 길이만큼 순회
        if (p[0] == '$' && p[1] == '{') { // p의 첫 번째 문자열이 '$' 이고 '{'이면 
            const char *end = strchr(p, '}'); // strchr(a, '@'): 첫 번째 인자 a 문자열에서  @가 들어있는 주소 반환하는 함수
            if (!end) return 0; // '}'가 p 문자열에 없다면 0을 반환하고 종료. 짝이 맞지 않는다면 잘못된 문자열이기 때문에 {}
            char key[32]; // 32바이트의 key 문자열 배열 변수 선언 ? 왜 32바이트를 할당했지?
            size_t kl = (size_t)(end - (p + 2)); // '}'가 담겨있는 주소(end)에서 p의 시작 주소 2바이트 떨어진 거리가 얼마나 되는지 계산 end가 (p+4)라면 (p+2)에서 2바이트 떨어진 거리에 있다는 뜻. 다시 말해, kl은 '$', '{'. '}'의 특수문자를 제외한 텍스트만 담겨 있는 문자열의 사이즈를 의미.
            if (kl >= sizeof key) kl = sizeof key - 1; // kl사이즈가 32바이트보다 크다면 kl사이즈를 32바이트에서 -1한 31바이트 할당 ? 내가 궁금한 점: 문자열에는 뒤에 '\0' 존재하기 때문인가?
            memcpy(key, p + 2, kl); // memcpy(key, p+2, kl)은 p+2만큼 kl만큼 떨어진 문자열을 key에 복사 -> ex) ${host} => key = {'h', 'o', 's', 't'};로 담긴다는 의미
            key[kl] = '\0'; // 문자열 마지막에 '\0' 할당

            // 원인2) *v에 NULL값을 반환하게 된다. 이유는 Config 구조체는 n = 2, keys의 길이는 2개(host, port), vals의 길이는 2개(example.com, 8080)의 값만 저장되어 있기 때문이다.
            const char *v = cfg_get(c, key); // Config 구조체와, key 문자열 배열를 인자로 넘겨준다
            // 해결2) *v의 값을 NULL여부를 판단하는 분기를 생성
            //       if(strlen(v) == 0) return;
            // 해결3) *v가 NULL인데 strlen()은 NULL 포인터에 사용되면 정의되지 않은 오류로 판별해 비정상 종료. 그렇다면 다음 해결책은 뭐가 좋을까?
            //       - NULL값을 판별하는 메소드가 있을까?
            //       - if(!(v)) if(!(*v)) 이거는 오류가 날 것이다. v라는 포인터 변수는 생성만 되어있지 주소값과 객체가 없기 때문에 거기에 접근하는 순간 프로그램은 종료시킨다.
            //       - return을 하게 되면 ${path} 다음 문자열을 비교하지 않는다. 그렇다면 continue를 한다면? 왜 printf()가 무한으로 찍히지? -> 알았다. 주소값을 이동시키지 않고 똑같은 '${path}'의 '$'을 반복하기 때문이다.
            // 해결4) if(!(v))분기에 p++ 코드를 continue전에 넣어준다.
            if(!(v)) {
                return 0;
            }
            size_t vl = strlen(v); // 반환받은 value의 문자열 길이를 vl에 담는다
            if (o + vl < outcap) { memcpy(out + o, v, vl); o += vl; } // 만약 최대문자열을 넘지 않는다면 out 문자열에 v를 v의 사이즈만큼 저장한다.
            p = end + 1; // p의 시작주소를 end(})의 주소 뒤로 초기화. 
        } else { // '$', '{' 문자가 아닌 경우 그대로 해당되는 문자열을 out 배열에 저장
            if (o + 1 < outcap) out[o++] = *p; // out[o]에 저장을 하고 o++
            p++; // p 주소값 이동(1바이트씩)
        }
    }
    out[o] = '\0';
    return 1; // 모든 문자열에 이상이 없을 시 성공 1을 반환
}

int main(void) {
    /* [Thinking Point]
     * "{ .n = 0 }" 은 멤버 이름을 콕 집어 초기화하는 '지정 초기화자(designated initializer)'다.
     *   tip 1. 초기화자에 하나라도 값을 주면, 명시하지 않은 나머지 멤버는 전부 0 으로
     *          채워진다. 즉 keys[], vals[] 배열도 모두 NULL 로 초기화된다.
     *   tip 2. 만약 그냥 "Config cfg;" 로만 뒀다면 지역 변수라 n·keys·vals 가 쓰레기 값이다.
     *   생각해보기: n 이 쓰레기 값이면 cfg_set/cfg_get 에서 무슨 일이 벌어질까?
     *               */
    Config cfg = { .n = 0 };
    int result;
    cfg_set(&cfg, "host", "example.com");
    cfg_set(&cfg, "port", "8080");
    // 원인 1) cfg_set(&cfg, "path", "~~"); Config에 설정하는 [key=path, val=tbd] 초기화하는 코드가 빠져있다
    // 해결 1) 임의의 값을 설정
    cfg_set(&cfg, "path", "test");

    /* [Thinking Point]
     * "${host}" 처럼 ${...} 로 감싼 부분은 expand 함수가 설정값으로 치환하는 'placeholder' 다.
     *   tip 1. 이 문자열 자체는 그냥 상수 텍스트일 뿐, 컴파일러가 ${...} 를 해석하지 않는다.
     *          실제 치환은 런타임에 expand 함수 안에서 키를 찾아 값을 끼워넣는 방식으로 일어난다.
     *   tip 2. cfg_get("path") 는 등록되지 않은 키라 NULL 을 돌려준다.
     *   생각해보기: 설정에 없는 키(${path})를 만나면 expand() 는 어떤 값을 받게 되고,
     *               그 값을 검사 없이 strlen/복사에 쓰면 무슨 일이 벌어질까? -> 값이 없기 때문에 segmentation fault. 메모리 역참조 오류가 발생하고 정의되지 않는 동작이기 때문에 프로그램은 종료한다.
     *               (힌트: "값이 없다"는 NULL 이지 빈 문자열 ""이 아니다) */
    const char *tmpl = "http://${host}:${port}/${path}/index.html";
    char out[256];

    result = expand(&cfg, tmpl, out, sizeof out);   /* ${path} 치환 시 NULL 역참조 → 크래시 */

    if(result){
        printf("url = %s\n", out);
    }else{
        printf("참조하는 key값이 없거나 {}의 짝이 맞지 않으므로 실패!");
    }
    return 0;
}

/*
    해결5) expand의 결과값을 성공, 실패로 명시적으로 나누어 main에서 expand()의 결과값을 토대로 출력하는 결과를 다르게 한다.
        1) void expand() -> int expand() 수정
        2) expand()안에 실패하는 경우 0, 성공하는 경우 1 코드 추가
        3) main 함수에 int result; 선언
        4) expand()안에 성공 시 return 1반환
        5) int result = expand(~);
        6) if(result) else 분기 처리로 성공/실패 시 출력 문자를 다르게 설정
*/ 
