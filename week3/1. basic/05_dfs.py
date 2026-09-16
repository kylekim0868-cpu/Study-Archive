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
            1) Recursion
            2) Stack
                -> 2가지 방법으로 구현 가능
            1) Recursion
                - 필요한 변수는? graph, start, visited
                - visited, result 변수 초기화
                - 종료 지점은? 마지막 노드에 도착해 더 이상 탐색할 노드가 없을 때
                - 재귀 내용은? 현재 노드에서 다음 인접 노드 탐색 방문마다 visited에 저장
                - result에 배열 반환
        TroubleShooting)
            1) visited, result가 재귀함수를 호출할 때마다 초기화가 된다
                -> visited가 None일 때만 visited = []로 초기화
            2) 무한 루프에 빠진다 종료를 못하네?
                -> 기존에는 방문한 노드에도 재귀를 호출하도록 구현. 하지만 방문하지 않은 노드!!만 재귀를 돌도록
                -> 종료 지점 설계가 부족 -> 현재 노드에 탐색할 미방문 이웃이 없으면 이전 호출로 돌아간다
    """
    if visited == None:
        visited = []

    visited.append(start) 

    for neigh in graph[start]:
        if neigh not in visited:
            dfs(graph, neigh, visited)
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


