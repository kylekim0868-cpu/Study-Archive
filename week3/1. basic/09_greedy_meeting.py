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
        selected = [(시작시간, 종료시간), (시작시간, 종료시간), ..] -> 보통 시작시간 == 종료시간 이렇게 들어오진 않기 때문에 예외 생각안해도 됨
        설계)
            - selected 배열 초기화
            - meetings 배열 순회
                - selected 배열 안의 종료시간 >= meetings 배열 안의 종료시간 : 다음 순회
                - selecetd배열에 meetings 배열의 원소값 push
        ! 위의 설계대로 진행한다면 일단 오류가 난다. 왜? 배열이 오름차순이 아니라 뒤죽박죽 엉켜 입력된다면? 모두 패스한다.
            -> 그렇다면 이중 순회문을 사용하여 배열 안에서 기준 인접 원소를 비교하여 selected에 push하는 방향으로
        !! !설계대로 해도 일단 된다 하더라도 시간복잡도 측면에서 굉장히 비효율적인거 같다. 다시 수정
            - selecetd 배열 초기화
            - meetings 튜플 순회
                - for start, end in meetings: 
                - selected.append((start,end)) # selected 배열에 push
                - selected
        !!! 이것도 아니야 첫 번째 배열로 간단하게 끝낼 수 있을 거 같아
        !!!! 종료 시간 기준 오름차순 후 비교하면 훨씬 빠른 작업이 되겠네? 
            -> 튜플의 정렬 원리를 이해해야할듯?
                1) lambda
                2) 함수 생성해서 반환
                3) key
                위의 3개의 방법을 사용해서 차순 정렬 가능!
    """
    # selected = []
    # n = len(meetings)
    # meetings.sort(key=1)
    # for i in range(0, n):
    #     if [] in selected:
    #         selected.append(meetings[i])
    #     if selected[i][1] < meetings[i][0]:
    #         selected[i].append(meetings[i])
    #     else: 
    #         selected.pop()
    
    # return len(selected), selected
    selected = []
    n = len(meetings)
    def get_end(meetings):
        return meetings[1]
    meetings.sort(key=get_end)
    for i in range(n):
        if not selected:
            selected.append(meetings[i])
        if selected[-1][1] < meetings[i][0]:
            selected.append(meetings[i])
    """
        blocked
            1) selected에 빈값이 있기 때문에 51번 라인에서 에러가 난다. IndexError: list index out of range
            Solving -> 첫 번째 순회에는 selected배열에 push
            2) 1번의 작업으로 코드를 수정해도 같은 에러. IndexError: list index out of range
            Solving -> append는 빈 배열에 적용되느 ㄴ메서드가 아니라 할당해주는 작업으로 수정해야한다.
            3) 2번 해결방식은 내가 개념을 이해 못한 방식이라 틀렸다. append()는 빈 배열에 추가가 가능하다.
            4) AttributeError: 'tuple' object has no attribute 'pop'
    """
    return len(selected), selected
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


