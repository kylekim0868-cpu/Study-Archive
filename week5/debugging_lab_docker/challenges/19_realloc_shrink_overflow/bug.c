/*
 * Challenge 19 — realloc 로 줄인 뒤 옛 길이로 접근 (심화: 신호 버퍼 트림)
 *
 * [시나리오]
 *   센서 신호를 담는 Signal 버퍼. 앞부분의 유효 구간만 남기고 나머지를 잘라내
 *   메모리를 절약하는 signal_trim() 을 호출한 뒤, 에너지(제곱합)를 계산한다.
 *
 * [예시 상황]
 *   마이크 / 음성
 *   음성 구간 검출(VAD)이 이 패턴을 사용한다.
 *   44,100Hz로 녹음하면 1초에 samples가 44,100개다.
 *   무음인 앞부분만 남기고 뒤를 자르는 게 signal_trim이고, 소리가 얼마나 큰지(에너지)를 보려면 제곱합을 쓴다.
 *
 * [기대 동작]
 *   트림 후에는 남은 표본 개수(len)만큼만 접근/계산.
 *
 * [증상]
 *   signal_trim() 이 realloc 으로 버퍼를 "축소"하고 용량(cap)은 갱신하지만, 길이
 *   필드(len)를 갱신하지 않는다. 이후 signal_energy() 는 여전히 옛 len(수백만)으로
 *   순회하므로, 축소된(해제되어 unmap 된) 영역까지 읽어 SIGSEGV.
 *   크래시는 energy 루프의 samples[i] 에서 나지만, 원인은 "트림 시 len 미갱신".
 *
 * [gdb 로 잡기]
 *   make gdb NAME=19_realloc_shrink_overflow
 *   (gdb) run                        → 크래시(SIGSEGV)
 *   (gdb) bt                         → signal_energy 의 s->samples[i] 지점
 *   (gdb) print i ; print s->len ; print s->cap
 *        → len 이 cap 보다 훨씬 큼(트림으로 cap 만 줄었고 len 은 옛값)
 *   (gdb) break signal_trim          → 트림 후 len/cap 이 어긋나는지 확인
 *
 * [printf(로그)로 잡기]
 *   순회 인덱스와 len/cap 을 비교 출력:
 *     fprintf(stderr, "i=%zu len=%zu cap=%zu\n", i, s->len, s->cap);
 *   → i 가 cap 을 넘어서는(=축소된 버퍼 밖) 순간이 위험 지점.
 *   (stdout 은 버퍼링되니 stderr 로 찍어야 크래시 직전 로그가 남는다)
 *
 * TODO: 버퍼를 축소하면 길이(len)도 함께 새 크기로 갱신하고, 이후 접근은 갱신된
 *       len 으로만 하세요. (cap 과 len 을 항상 정합적으로 유지)
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double *samples;
    size_t  len;      
    size_t  cap;      
} Signal;

// Signal 구조체의 각 멤버 변수 초기화 작업
// *samples 200000*8바이트 공간의 동적 메모리를 할당하고 힙 시작 주소를 가지고 있는 변수
// len = cap = 2000000
static void signal_init(Signal *s, size_t n) {
    s->samples = malloc(n * sizeof(double)); // 8*2000000의 공간을 할당해주고 그 공간의 시작 주소를 반환
    if (!s->samples) { perror("malloc"); exit(1); }
    s->len = s->cap = n;
    for (size_t i = 0; i < n; i++) s->samples[i] = (double)(i % 7) - 3.0;
}

static void signal_trim(Signal *s, size_t keep) {
    if (keep > s->cap) return;
    double *p = realloc(s->samples, keep * sizeof(double)); // keep개의 double이 들어갈 크기로 변경을 요청하는 코드
    if (p) {
        s->samples = p; 
        s->len = keep; // 해결1) 재할당된 메모리의 길이를 갱신
        s->cap = keep; // cap 갱신도 재할당 성공 조건 안에 해야 정합성이 유지된다
    } // p가 realloc에 실패했다면 원본 주소에 p포인터 값 저장
}

// signal_energy(): s->samples[i]의 제곱값의 총합을 e에 할당하고 반환해주는 함수
static double signal_energy(const Signal *s) {
    double e = 0.0;
    for (size_t i = 0; i < s->len; i++) {   // 원인1) s->samples의 배열은 크기가 줄었는데 s->len을 기준으로 반복되기 때문에 i가 유효 범위를 넘어서게 되어 
        e += s->samples[i] * s->samples[i]; 
    }
    return e;
}


int main(void) {
    Signal s;
    signal_init(&s, 2000000);       

    signal_trim(&s, 8);             

    double e = signal_energy(&s);   
    
    printf("energy = %.1f (len=%zu cap=%zu)\n", e, s.len, s.cap);
    free(s.samples);
    return 0;
}
        /*
            가설) 
                - i = 510일 때 왜 SIGSEGV 오류가 발생했을까?
                - s->samples[i]의 길이가 총 509까지였을까? 틀린 가설: signal_init()을 파헤쳐 보면 s->samples에 할당된 공간은 엄청나게 크다. (16000000B)
                - 위의 Signal 구조체의 samples 배열의 길이와 원소가 어떻게 채워져 있는지 확인이 필요해 보인다.
                - main > signal_init()함수를 파헤쳐보자. 여기서 Signal 구조체의 멤버 객체를 초기화하는 것처럼 보인다.
                - signal_trim()에 단서가 있을까? 
                - signal_trim()이 무슨 작동을 하는지 분석해보자.
                - p의 시작 주소값이 samples의 시작 주소와 같을까, realloc()으로 원본 주소인 samples의 시작 주소의 끝 공간에 붙여서 할당해줄까? (✘) rp의 시작주소는 samples와 같다
                - p가 바라보는 힙 메모리를 B, s->samples가 바라보는 힙 메모리를 A라고 생각했을 때,
                    B는 1600000+16B / A는 1600000 인건가?
                - s->samples에 p의 주소값을 할당한다면 s->samples가 바라본 힙 메모리는 어떻게 되는거지?
                - 위의 궁금증들을 전부 gdb로 확인해보자(검증)
            검증)
                - *p의 시작 주소값이 samples의 시작 주소와 같을까, realloc()으로 원본 주소인 samples의 시작 주소의 끝 공간에 붙여서 할당해줄까? 시작주소가 같다
                - p가 바라보는 힙 메모리를 B, s->samples가 바라보는 힙 메모리를 A라고 생각했을 때,
                    s->samples가 배열의 메모리가 줄어들었다. 그러면 A가 B보다 메모리가 컸을 때 뒤에 있는 메모리는 해제가 되는건가? 아니면 접근을 하지 못하는건가?
                - s->samples에 p의 주소값을 할당한다면 s->samples가 바라본 힙 메모리는 어떻게 되는거지?
        */ 