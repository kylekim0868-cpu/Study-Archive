/*
 * Challenge 09 — strcpy 힙 오버플로 (심화: join 크기계산 off-by-one)
 *
 * [시나리오]
 *   여러 조각(parts)을 구분자 없이 이어 붙여 하나의 문자열을 만드는 join().
 *   필요한 크기를 먼저 계산(joined_size)해 malloc 한 뒤, 각 조각을 순서대로 복사한다.
 *
 * [기대 동작]
 *   모든 조각을 이어 붙인 결과 길이를 출력하고 정상 종료.
 *
 * [증상]
 *   크기 계산 함수 joined_size() 의 루프가 `i < n - 1` 이라, "마지막 조각"의 길이를
 *   더하지 않는다. 그런데 실제 복사 루프는 `i < n` 으로 마지막 조각까지 복사한다.
 *   마지막 조각이 크면(여기서는 큰 본문), 할당량보다 훨씬 많이 써서 힙을 크게 넘어간다.
 *   → 힙 메타데이터 손상(이후 free 에서 abort) 또는 매핑 밖 접근으로 SIGSEGV.
 *   크래시는 strcpy/free 에서 나지만, 원인은 "크기 계산의 off-by-one"이다.
 *
 * [gdb 로 잡기]
 *   make gdb NAME=09_strcpy_overflow
 *   (gdb) run                       → 크래시(SIGSEGV 또는 abort)
 *   (gdb) bt                        → join 의 strcpy 또는 free 근처
 *   (gdb) break joined_size ; run    → 반환값(need)과 실제 필요한 총합을 비교
 *   (gdb) print need                → 마지막 조각 길이가 빠져 need 가 부족함을 확인
 *
 * [printf(로그)로 잡기]
 *   계산한 크기와 실제로 복사한 바이트를 비교 출력:
 *     fprintf(stderr, "alloc=%zu copied=%zu\n", need, off);
 *   → copied 가 alloc 을 넘어서면 그 초과분이 힙을 침범한 것.
 *   (stdout 은 버퍼링되니 stderr 로 찍어야 크래시 직전 로그가 남는다)
 *
 * TODO: 크기 계산 루프를 `i < n` 으로 고쳐 모든 조각 길이와 종료 문자('\0') 자리를
 *       빠짐없이 더한다. "계산 루프와 복사 루프의 범위를 반드시 일치"시킨다.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 필요한 총 바이트 수 = 모든 조각 길이 합 + 종료 문자 1 */
static size_t joined_size(const char *const *parts, int n) {
    size_t total = 1;                        /* '\0' 자리 */
    for (int i = 0; i < n; i++) {        
        total += strlen(parts[i]);
    }
    return total;
}

static char *join(const char *const *parts, int n) {
    size_t need = joined_size(parts, n); 
    char *out = malloc(need);                /* 마지막 조각 길이만큼 부족하게 할당됨 */
    if (!out) { perror("malloc"); exit(1); }

    size_t off = 0;
    for (int i = 0; i < n; i++) {            /* 복사는 마지막 조각까지 전부 → 오버플로 */
        strcpy(out + off, parts[i]);
        off += strlen(parts[i]);
    }
    out[off] = '\0';
    return out;
}         

int main(void) {
    
    static char body[200000];
    memset(body, 'x', sizeof body - 1);
    body[sizeof body - 1] = '\0';

    const char *parts[] = { "GET ", "/index.html", " HTTP/1.1\r\n\r\n", body };
    int n = (int)(sizeof(parts) / sizeof(parts[0]));

    char *msg = join(parts, n);              /* 복사 중 힙 오버플로 → 크래시 */

    printf("joined length = %zu\n", strlen(msg));
    free(msg);
    return 0;
}

/*
    가설)
        - strcpy(out + off, parts[i]); 코드에서 크래시가 났다.
        - bt로 추적해본 결과, parts=0xfffffffff468 / n=4일 때 크래시가 발생했고
        - parts가 어떤 것을 담고 있는지 추적해봐야겠다. parts = {"GET ", "/indexpr.html", " HTTP/1.1\r\n\r\n", body} -> body는 첫 원소의 시작 주소값을 가지고 있음
        - 왜 need=29일까? parts[0~2]까지의 길이를 모두 더하면 34가 나오는데 그러면 need=31? \r은 문자열로 취급 안하나? -> ✔︎ 해결했음, "index" 대신 "indexpr"이 들어가있음
        - joined_size에서 n-1만큼만 malloc을 했는데 *join함수에서는 n만큼 부족한 공간을 사용하려고 하니 오류가 발생할 것이라고 생각된다.
        - parts에는 원소가 n개가 있기 때문이다.
        - need가 이 문제의 원인이고 해결 포인트이다. 인자로 받은 원소의 개수만큼 size를 동적할당해줘야 한다.
    검증)
        - joined_size -> n-1만큼 순회하면 need = 29
                      -> n만큼 순회하면 need = 200028
        - i=3에서 에러가 발생한다. 정확하게 strcpy()에서 에러가 발생한다.
        - 만약 out[off] = '\0'; 끝 문자를 뜻하는 널을 갱신하지 않았다면 오류가 발생하지 않는다
            → 마지막 널 문자 대입을 제거했을 때 크래시가 나지 않았다. 하지만 기존 할당량이 29바이트였다면 strcpy()에서 이미 범위 밖 쓰기가 발생하므로, 이것만으로 해결됐다고 볼 수 없다.
*/