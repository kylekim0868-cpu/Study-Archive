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
1. 현재 상태는 무엇인가?
    시작정점 = 0
2. 다음 상태로 어떻게 이동하는가?
    인접한 정점을 찾는다. 
3. 언제 탐색을 종료하는가?
    target에 도달하거나 target에 최소로 도달했을 경우
4. 어떤 값을 결과로 반환하는가?
    최소 간선 수 혹은 -1

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
    # TODO 1: 시작 상태를 담은 큐를 만든다.
    # 큐의 원소 하나에는 어떤 정보가 들어가야 하는가?
    distance = 0
    queue = deque([(start, distance)])
    # TODO 2: 시작 정점을 방문 기록에 남긴다.
    visited = []
    visited.append(start)
    # TODO 3: 큐에 탐색할 정점이 남아 있는 동안 반복한다.
    while queue:
        # TODO 4: 큐의 맨 앞 상태를 꺼내 현재 정점과 거리로 나눈다. -> 튜플 언패킹
        current, distance = queue.popleft()
        # TODO 5: 현재 정점이 target이라면 무엇을 반환해야 하는가? 이동 거리
        if current == target:
            return distance
        # TODO 6: 현재 정점의 이웃을 하나씩 확인한다.
        for neigh in graph[current]:
            # TODO 7: 아직 방문하지 않은 이웃만 방문 처리한다.
            if neigh not in visited:
            # TODO 8: 다음 정점의 거리는 현재 거리에서 어떻게 변하는가?
            # 다음 상태를 큐에 추가한다.
                visited.append(neigh)
                queue.append((neigh, distance+1))
    # TODO 9: 큐가 빌 때까지 target을 찾지 못했다면 무엇을 반환해야 하는가?
    pass
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
