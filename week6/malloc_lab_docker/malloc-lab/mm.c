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
 * mm_init - initialize the malloc package.
 */
int mm_init(void)
{
    char *heap_listp; // char 포인터 자료형 -> payload 시작 주소를 가리키는
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