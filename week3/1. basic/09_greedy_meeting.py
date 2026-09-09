"""
[그리디 - 회의실 배정]

문제 설명:
- 하나의 회의실에 여러 회의를 배정합니다.
- 각 회의는 시작 시간과 종료 시간이 있습니다.
- 최대한 많은 회의를 배정하려고 합니다.

입력:
- meetings: [(시작, 종료), ...] 회의 리스트

출력:
- 배정된 회의 개수

예제:
입력: [(1, 4), (3, 5), (0, 6), (5, 7), (3, 8), (5, 9), (6, 10), (8, 11), (8, 12), (2, 13), (12, 14)]
출력: 4개
선택: [(1, 4), (5, 7), (8, 11), (12, 14)]
"""

def select_meetings(meetings):
    """
    회의실 배정 (그리디)
    
    Args:
        meetings: [(시작, 종료)] 리스트
    
    Returns:
        (배정된 회의 개수, 선택된 회의 리스트)
    """
    """
    설계)
        - 오름차순 정렬을 종료시간 기준으로?
        - 최대한 많은 회의를 배정하려면
            1) 회의시간이 짧으면 되는데 -> 코드로 어떻게?
        - 회의 시간을 오름차순을 정렬
        - 튜플 리스트 순회하면서 앞 원소: (시작시간, 종료시간) 뒤 원소: (시작시간, 종료시간) -> i의 종료시간 < j의 시작시간 라면 결과에 반환
            -> 회의시간이 겹치지 않기 때문에
    """
    # result - 결과값을 담을 배열 생성
    result = []

    # 종료시간(튜플의 2번째 원소) 기준으로 오름차순 정렬
    for i in range(0, len(meetings)):
        for j in range(i+1, len(meetings)):
            if meetings[i][1] > meetings[j][1]:
                meetings[i], meetings[j] = meetings[j], meetings[i]

    # 튜플 리스트 순회 -> 앞 원소의 종료시간 > 뒤 원소의 시작시간: 결과값에 반환
    for i in range(0, len(meetings)):
        if not result:
            result.append(meetings[i])
        if result[-1][1] <= meetings[i][0]:
            result.append(meetings[i])    
    return len(result), result
# 테스트 케이스
if __name__ == "__main__":
    # 테스트 케이스 1
    meetings1 = [(1, 4), (3, 5), (0, 6), (5, 7), (3, 8), (5, 9)]
    count1, selected1 = select_meetings(meetings1)
    print("=== 테스트 케이스 1 ===")
    print(f"전체 회의: {meetings1}")
    print(f"배정된 회의 개수: {count1}개")
    print(f"선택된 회의: {selected1}")
    print()
    
    # 테스트 케이스 2
    meetings2 = [(1, 4), (3, 5), (0, 6), (5, 7), (3, 8), (5, 9), (6, 10), (8, 11), (8, 12), (2, 13), (12, 14)]
    count2, selected2 = select_meetings(meetings2)
    print("=== 테스트 케이스 2 ===")
    print(f"전체 회의: {len(meetings2)}개")
    print(f"배정된 회의 개수: {count2}개")
    print(f"선택된 회의: {selected2}")


