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
        1) Recursion
    """
    # # 시작 지점 방문기록
    # if not visited:
    #     visited = []
    # visited.append(start)

    # for g in graph[start]:
    #     if g not in visited:
    #         dfs(graph, g, visited) 

    # return visited
    """
        2) Stack
    """
    # 스택으로 담을 자료구조 배열 생성
    stack = []
    # 스택에 start(시작 정점)을 넣고 시작
    stack.append(start)
    visited = {}
    visited = set()
    visited.add(start)

    # 기준 정점의 이웃한 정점을 스택에 쌓고 가장 직전에 방문한 이웃부터 차례로 방문 여부 판단
    while stack:
        last = stack.pop() # 가장 직전에 방문한 노드
        for neigh in graph[last]:
            if neigh not in visited:
                visited.add(neigh)
                stack.append(neigh)

    return list(visited)


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


