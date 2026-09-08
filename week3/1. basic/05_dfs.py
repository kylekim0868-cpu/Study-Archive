"""
[DFS - 깊이 우선 탐색 (Depth-First Search)]

문제 설명:
- DFS로 그래프를 탐색합니다.
- 깊이 방향으로 끝까지 탐색합니다.
- 재귀 또는 스택을 사용합니다.

입력:
- graph: 그래프 (인접 리스트)
- start: 시작 정점

출력:
- 방문 순서

예제:
그래프:
  0 ─── 1
  │     │
  └─ 2 ─┘
      │
      3

시작: 0
DFS: [0, 1, 2, 3] (순서는 구현에 따라 다를 수 있음)
"""

def dfs(graph, start, visited=None):
    """
    깊이 우선 탐색 (재귀)
    
    Args:
        graph: 그래프 딕셔너리
        start: 현재 정점
        visited: 방문 리스트
    
    Returns:
        방문 순서 리스트
    """
    """
        설계)
            - 시작정점 방문 처리
            - 현재 노드와 연결된 이웃 확인
            - 방문하지 않았다면 재귀함수 호출
            - 연결된 이웃이 없다면 재귀함수 종료
            - 호출 스택을 통해 직전 노드로 돌아가 다른 이웃 탐색
            - 모든 재귀 호출이 종료되어 호출 스택이 비면 탐색 종료
    """
    """""""""""""""""""""""""""구현1) 재귀"""""""""""""""""""""""""""
    """
    if not visited: # None이면 return False
        visited = []

    # 시작정점 방문 처리
    visited.append(start)

    # # 현재 노드와 연결된 이웃 확인
    # for neigh in graph:
    #     if neigh not in visited: # graph 인접한 노드가 방문기록에 없다면 방문 처리
    #         dfs(graph, neigh, visited) # graph와 방문스택의 최상단 정점와 visited 인자로 넘겨주어 재귀함수 호출

    for i in range(len(graph[start])):
        if graph[start][i] not in visited:
            dfs(graph, graph[start][i], visited)
    """
    """""""""""""""""""""""""""구현2) 스택"""""""""""""""""""""""""""
    """
        설계)
            - 시작정점을 스택에 넣고
            - 스택의 맨 위 정점을 꺼내고
            - 아직 방문하지 않았다면 방문 처리
            - 그 정점의 이웃을 스택에 넣고
            - 스택이 빌 때까지 반복
    """
    # stack 초기화
    stack = []
    # visited 초기화
    visited = []
    # 시작정점 스택에 추가
    stack.append(start)

    while stack:
        current = stack.pop()
        # 꺼낸 스택 방문 기록
        if current not in visited:
            visited.append(current)
        # 스택의 맨 위 정점 꺼낸다
        for neigh in reversed(graph[current]):
            if neigh not in visited:
                stack.append(neigh)


    
    return visited

# 테스트 케이스
if __name__ == "__main__":
    # 그래프 생성
    graph = {
        0: [1, 2],
        1: [0, 2],
        2: [0, 1, 3],
        3: [2]
    }
    
    print("=== DFS (깊이 우선 탐색) ===")
    result = dfs(graph, 0)
    print(f"시작 정점: 0")
    print(f"방문 순서: {result}")


