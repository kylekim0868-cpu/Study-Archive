"""
[큐 - 프린터 대기열]

문제 설명:
- 큐(Queue)를 사용하여 프린터 작업을 순서대로 처리합니다.
- FIFO (First In First Out) 구조를 활용합니다.

입력:
- jobs: 인쇄 작업 리스트 (예: ["문서A", "문서B", "문서C"])

출력:
- 작업이 처리되는 순서

예제:
입력: ["문서A", "문서B", "문서C"]
출력:
처리: 문서A 
처리: 문서B
처리: 문서C
"""

from collections import deque

def process_print_queue(jobs):
    """
    프린터 작업을 순서대로 처리
    
    Args:
        jobs: 작업 리스트
    
    Returns:
        처리된 작업 리스트
    """
    """
        설계 단계)
            - 일단 인자로 받은 배열을 deque에 담아준다.
            - 인쇄 작업 리스트의 순서대로 배열의 가장 처음 인덱스에 담겨져있기 때문에 배열의 개수(len(jobs))만큼 순회
            - 순회
                print(jobs)
                배열의 인덱스 순서대로 임시 배열(printed)에 append()
                deque.popleft() 진행   
    """
    q = deque(jobs)
    printed = []
    for i in range(len(jobs)):
        print(f"처리: {jobs[i]}")
        printed.append(jobs[i])
        q.popleft()
    return printed

# 테스트 케이스
if __name__ == "__main__":
    # 테스트 케이스 1
    jobs1 = ["문서A", "문서B", "문서C"]
    print("=== 프린터 작업 처리 ===")
    result1 = process_print_queue(jobs1)
    print(f"처리 완료: {result1}")
    print()
    
    # 테스트 케이스 2
    jobs2 = ["이메일", "보고서", "사진", "계약서"]
    print("=== 프린터 작업 처리 ===")
    result2 = process_print_queue(jobs2)
    print(f"처리 완료: {result2}")


