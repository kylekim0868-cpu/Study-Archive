"""
[BFS 기초 복습 - 그래프에서 최소 이동 횟수 찾기]

이 문제를 먼저 푸는 이유:
- 게임 맵 최단거리는 큐, 2차원 좌표, 범위 검사, 방문 처리, 거리 계산을
  한 번에 생각해야 해서 현재 나에게는 여러 개념이 섞여 보였다.
- 이번 문제에서는 2차원 좌표와 범위 검사를 제외하고
  큐, 방문 기록, 거리 계산에만 집중한다.

문제 설명:
- 여러 정점의 연결 관계가 graph에 주어진다.
- start에서 target까지 이동할 때 필요한 최소 간선 수를 반환한다.
- 한 번의 이동으로 현재 정점과 직접 연결된 이웃 정점으로 갈 수 있다.
- target에 도달할 수 없다면 -1을 반환한다.

입력 예시:
    0 ─ 1 ─ 3 ─ 5
    │           │
    └─ 2 ─ 4 ──┘

    start = 0
    target = 5

가능한 경로:
- 0 → 1 → 3 → 5: 3번 이동
- 0 → 2 → 4 → 5: 3번 이동

출력:
- 최소 이동 횟수 3

구현하기 전에 먼저 적어볼 것:
1. 현재 상태는 무엇인가? 시작 정점
2. 다음 상태로 어떻게 이동하는가? 인접한 이웃 노드를 탐색해 방문하지 않은 노드를 탐색한다
3. 언제 탐색을 종료하는가? 종료 지점을 만나거나 모든 노드를 탐색했을 때 종료 지점을 만나지 못한 경우 -1 반환하며 종료
4. 어떤 값을 결과로 반환하는가? 종료 지점까지의 최소 간선 수

힌트:
- 큐에는 현재 정점과 start부터의 이동 횟수를 함께 저장할 수 있다.
- 시작 정점에서 시작 정점까지의 이동 횟수는 0이다.
- 먼저 발견한 정점을 먼저 확인해야 가까운 거리부터 탐색할 수 있다.
- 같은 정점을 다시 큐에 넣지 않도록 방문 기록이 필요하다.
"""

from collections import deque


def shortest_steps(graph, start, target):
    """
    Args:
        graph: 정점별 이웃 목록을 가진 딕셔너리
        start: 탐색을 시작할 정점
        target: 도착해야 할 정점

    Returns:
        start에서 target까지의 최소 이동 횟수
        도달할 수 없다면 -1
    """
    """
    설계)
        - 필요한 변수는? edge; 이동 거리를 나타내는 간선, edge와 start를 넣을 deque 생성, 방문기록을 담을 visited(배열) 변수
        - 초기화는? deque 초기화, visited 배열 초기화
        - 예외 처리는? X
        - 시작 정점과 시작 이동 횟수(간선) 초기화 -> start = 0, edge = 0
        - deque에 push
        - visited = [] visited 초기화
        - visited.append(start)
        - while문을 사용해 queue가 빌 때까지 -> 즉 이웃한 노드가 없을 때까지 탐색
            - 만약 target을 만난다면 종료
            - 방문한 적이 없다면 인접 노드 방문 처리 후 edge += 1
            - 
    설계 수정)
        - 이동 횟수는 0으로 시작, 시작 정점은 0이 아니라 인자로 받은 정점으로 시작 따라서 "start = 0" 설계는 잘못되었음
        - "queue가 빌 때까지는" 발견해 둔 정점 중 처리할 정점이 없다는 뜻
        - 거리는 탐색 전체의 누적 횟수가 아니다. 이웃까지의 거리가 현재 정점까지의 거리 + 1
    """
    """
    TroubleShooting)
        1) q.append(start, edge)
            이렇게 되면 방문처리한 시작 정점도 다시 큐에 넣으면서 중복값이 발생. 또한 이웃 정점으로 이동하면 edge+1 
            -> 이웃이라면 neigh을 넣어야 한다
            -> q.append(neigh, edge+1)
        2) if( edge == target)
            이동 거리 횟수와 종료 지점은 같다는 종료 지점에 도달했는데 한 번에 도달하게 되면 어긋나므로 수정 필요
            -> start == target (시작 정점 == 종료 정점)
        3) deque([start, edge])
            -> 리스트의 형태로 원소가 2개가 생성이 된다. 즉, 쌍으로 묶여 하나의 원소로 deque에 객체가 생성된다.
            -> deque([(start, edge)]) 튜플 리스트 형태로 한 쌍으로 묶어 전달해야함
    """
    edge = 0
    q = deque([(start, edge)])
    visited = []
    visited.append(start)

    while(q):
        start, edge = q.popleft()
        if(start == target):
            return edge
        for neigh in graph[start]:
            if neigh not in visited:
                visited.append(neigh)
                q.append((neigh, edge+1))

    return -1

if __name__ == "__main__":
    connected_graph = {
        0: [1, 2],
        1: [0, 3],
        2: [0, 4],
        3: [1, 5],
        4: [2, 5],
        5: [3, 4],
    }

    disconnected_graph = {
        0: [1],
        1: [0],
        2: [3],
        3: [2],
    }

    print("=== BFS 최소 이동 횟수 복습 ===")
    print("테스트 1 예상: 3")
    print("테스트 1 결과:", shortest_steps(connected_graph, 0, 5))
    print()
    print("테스트 2 예상: 0")
    print("테스트 2 결과:", shortest_steps(connected_graph, 2, 2))
    print()
    print("테스트 3 예상: -1")
    print("테스트 3 결과:", shortest_steps(disconnected_graph, 0, 3))
