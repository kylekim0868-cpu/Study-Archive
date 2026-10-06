/*
 * mm-naive.c - The fastest, least memory-efficient malloc package.
 *
 * In this naive approach, a block is allocated by simply incrementing
 * the brk pointer.  A block is pure payload. There are no headers or
 * footers.  Blocks are never coalesced or reused. Realloc is
 * implemented directly using mm_malloc and mm_free.
 *
 * NOTE TO STUDENTS: Replace this header comment with your own header
 * comment that gives a high level description of your solution.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/
team_t team = {
    /* Team name */
    "ateam",
    /* First member's full name */
    "Harry Bovik",
    /* First member's email address */
    "bovik@cs.cmu.edu",
    /* Second member's full name (leave blank if none) */
    "",
    /* Second member's email address (leave blank if none) */
    ""};

/* single word (4) or double word (8) alignment */
#define ALIGNMENT 8

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT - 1)) & ~0x7)

#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))

/* Basic constants and macros */
#define WSIZE 4 /* Word and header/footer size (bytes) */
#define DSIZE 8 /* Double word size (bytes) */
#define CHUNKSIZE (1<<12) /* Extend heap by this amounb (bytes) */ // 1을 왼쪽 쉬프트 연산 12번을 하면 2의 12승 = 4143

#define MAX(x, y) ((x) > (y)? (x): (y))

/* Pack a szie and allocated bit into a ward */
#define PACK(size, alloc) ((size) | (alloc))

/* Read and write a word at address p */
#define GET(p) (*(unsigned int *)(p))
#define PUT(p, val) (*(unsigned int* )(p) = (val))

/* Read the size and allocated fields from address p */
#define GET_SIZE(p) (GET(p) & ~0x7)
#define GET_ALLOC(p) (GET(p) & 0x1)

/* Given block ptr bp, compute address of its header and footer */
#define HDRP(bp) ((char *)(bp) - WSIZE) // header pointer
#define FTRP(bp) ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE) // footer pointer

/* Given block ptr bp, compute address of next and previous blocks */
#define NEXT_BLKP(bp) ((char *)(bp) + GET_SIZE(((char *)(bp) - WSIZE))) // next payload pointer
#define PREV_BLKP(bp) ((char *)(bp) - GET_SIZE(((char *)(bp) - DSIZE))) // previous payload pointer

static char *heap_listp;

/* 4가지 free 케이스! */
static void *coalesce(void *bp)
{
    size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
    size_t size = GET_SIZE(HDRP(bp));

    // Case1) 이전 블록 할당 여부 = 1 이고 다음 블록 할당 여부 = 1
    if(prev_alloc && next_alloc){ 
        return bp;
    }

    // Case2) 이전 블록 할당 여부 = 1 이고 다음 블록 할당 여부 = 0
    else if(prev_alloc && !next_alloc){ 
        size += GET_SIZE(HDRP(NEXT_BLKP(bp))); // size = 4096*2 → 이유: NEXT_BLKP는 다음 payload의 시작 주소를 반환
        PUT(HDRP(bp), PACK(size, 0)); 
        PUT(FTRP(bp), PACK(size, 0));
    }

    // Case3) 이전 블록 할당 여부 = 0 이고 다음 블록 할당 여부 = 1
    else if(!prev_alloc && next_alloc){
        size += GET_SIZE(HDRP(PREV_BLKP(bp))); // 이전 블록의 헤더 사이즈를 더해준다 값을 size에 저장
        PUT(FTRP(bp), PACK(size, 0)); // 현재 블록의 푸터 자리에 새 크기
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0)); // 이전 블록의 헤더 자리에 새 크기
        bp = PREV_BLKP(bp); // bp를 이전 블록으로 갱신
    }

    else{
        size += GET_SIZE(HDRP(PREV_BLKP(bp))) + GET_SIZE(FTRP(NEXT_BLKP(bp))); // 이전+다음 블록 사이즈 더하기. GET_SIZE(FTRP(NEXT_BLKP(bp)) 를 GET_SIZE(ㅗㅇRP(NEXT_BLKP(bp)) 로 바꿔줘도 이상없다.
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0)); // 이전 블록 크기 갱신
        PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0)); // 다음 블록 크기 갱신
        bp = PREV_BLKP(bp); // bp를 이전 블록으로 갱신
    }

    return bp;
}


/* 힙 확장 */
static void *extend_heap(size_t words)
{
    char *bp;
    size_t size;
    
    /* Allocate an even number of words to maintain alignment */
    size = (words % 2) ? (words+1) * WSIZE : words * WSIZE; // heap의 크기를 늘릴 사이즈 홀수/짝수 여부 판단: 홀수 -> (사이즈+1)*4 / 짝수 -> (사이즈)*4 => 8바이트 정렬을 위해
    if((long)(bp = mem_sbrk(size)) == -1) return NULL; // heap 크기 조절 실패 시 -1 반환

    /* Initialize free block header/footer and the epilogu header */
    PUT(HDRP(bp), PACK(size, 0)); /* Free block header */
    PUT(FTRP(bp), PACK(size, 0)); /* Free block footer */
    PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1)); /* New epilogue header */

    /* Coalesce if the previous block was free */
    return coalesce(bp);
}

/*
* find_fit - 처음 블록부터 순회를 돌면서 크기가 맞는 블록을 찾는다.
*/
static void *find_fit(size_t asize)
{
    /*
        설계)
            - 필요한 변수
                → 각 블록을 이동할 포인터 char *bp; 블록 사이즈 asize;
            - bp 선언 char *bp;
            - ✔︎ bp를 초기화를 어떻게 하지? → 첫 블록의 payload의 값을 가져오면 문제 없을텐데?
                -> 초기화가 필요 없이 heap_listp를 사용해서 사이즈를 안다는 전제 하에 블록을 순회할 수 있다.
            - 순회해야 하는데 순회 범위는? → 헤더블록의 크기가 0보다 클 때까지 순회
            - 순회 종료 조건은 GET_ALLOC() = 0 && GET_SIZE(bp-WSIZE) >= asize 이면 return bp; 하고 종료
    */
    char *bp;
    bp = heap_listp;

    while(GET_SIZE(bp - WSIZE) > 0){
        if(GET_ALLOC(bp - WSIZE) == 0 && GET_SIZE(bp - WSIZE) >= asize){
            return bp;
        }    
        bp = NEXT_BLKP(bp);    
    }
    return NULL;
}

/*
* place() - 가용 블록을 할당하고 남은 블록을 분할하는 함수
*/
static void place(void *bp, size_t asize)
{
    /*
        설계)
            - 인자 *bp = 가용 가능한 블록의 payload 시작 주소
            - 인자 asize = 할당할 size
            - 필요한 변수 
                → size_t csize: 분할하기 전 전체 사이즈
            - csize에 GET_SIZE(HDRP(bp)) 대입
            - 분할 조건: 가용 가능한 전체 사이즈 - 할당할 사이즈 >= DSIZE*2 보다 크다면 분할
                - 조건O: 현재 할당할 블록의 헤더 크기 및 할당 여부 갱신
                    → PUT(HDRP(bp), PACK(asize, 1)); // 헤더에 할당할 크기로 갱신
                    → PUT(FTRP(bp), PACK(asize, 1); // 푸터에 할당할 크기로 갱신
                    → bp = NEXT_BLKP(bp); // bp를 분할할 다음 블록의 payload 주소로 갱신
                    → PUT(HDRP(bp), PACK(csize-asize, 0)); // 헤더에 csize-asize 크기, 할당 여부 = 0 으로 갱신
                    → PUT(FTRP(bp), PACK(csize-asize, 0)); // 푸터에 csize-asize 크기, 할당 여부 = 0 으로 갱신
                - 조건X: 분할 X
                    → 갱신 필요가 없다. asize 대신 csize 그대로 사용. 대신 할당 여부만 1로 갱신
                    → PUT(HDRP(bp), PACK(csize, 1));
                    → PUT(FTRP(bp), PACK(csize, 1));
    */

    size_t csize = GET_SIZE(HDRP(bp));

    if((csize - asize) >= DSIZE*2){ // ★ 왜 16바이트가 분할할 수 있는 최소 바이트일까?
        PUT(HDRP(bp), PACK(asize, 1));
        PUT(FTRP(bp), PACK(asize, 1));
        bp = NEXT_BLKP(bp);
        PUT(HDRP(bp), PACK(csize-asize, 0));
        PUT(FTRP(bp), PACK(csize-asize, 0));
    }else{
        PUT(HDRP(bp), PACK(csize, 1));
        PUT(FTRP(bp), PACK(csize, 1));
    }
}

/*
 * mm_init - initialize the malloc package.
 */
int mm_init(void)
{
    /* Create the initial empty heap */
    if((heap_listp = mem_sbrk(4*WSIZE)) == (void *)-1){
        return -1;
    }
    PUT(heap_listp, 0); // bp 초기화
    PUT(heap_listp + (1*WSIZE), PACK(DSIZE, 1)); // Prologue header bp의 시작 주소를 payload시작 주소로 이동하고 값(9)을 저장 
    PUT(heap_listp + (2*WSIZE), PACK(DSIZE, 1)); // Prologue footer
    PUT(heap_listp + (3*WSIZE), PACK(0, 1)); // Epilogue header 
    heap_listp += (2*WSIZE);

    /* Extend the empty headp with a free block of CHUNKSIZE bytes */
    if (extend_heap(CHUNKSIZE/WSIZE) == NULL) return -1;
    return 0;
}

/*
 * mm_malloc - Allocate a block by incrementing the brk pointer.
 *     Always allocate a block whose size is a multiple of the alignment.
 */
void *mm_malloc(size_t size)
{
    int newsize = ALIGN(size + SIZE_T_SIZE);
    void *p = mem_sbrk(newsize);
    if (p == (void *)-1)
        return NULL;
    else
    {
        *(size_t *)p = size;
        return (void *)((char *)p + SIZE_T_SIZE);
    }
}

/*
 * mm_free - Freeing a block does nothing.
 */
void mm_free(void *ptr)
{
    size_t size = GET_SIZE(HDRP(ptr));

    PUT(HDRP(ptr), PACK(size, 0));
    PUT(FTRP(ptr), PACK(size, 0));
    coalesce(ptr);
}

/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 */
void *mm_realloc(void *ptr, size_t size)
{
    void *oldptr = ptr;
    void *newptr;
    size_t copySize;

    newptr = mm_malloc(size);
    if (newptr == NULL)
        return NULL;
    copySize = *(size_t *)((char *)oldptr - SIZE_T_SIZE);
    if (size < copySize)
        copySize = size;
    memcpy(newptr, oldptr, copySize);
    mm_free(oldptr);
    return newptr;
}