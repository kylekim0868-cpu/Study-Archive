# BFS — 문제점 기록

- 풀이 코드: [`04_bfs.py`](../../week3/1.%20basic/04_bfs.py)
- 진행 상태: 제공된 테스트 통과
- 설계 기록: [BFS — 설계 기록](../설계모음집/04_bfs.md)

## 큐와 방문 기록의 역할을 섞음

처음에는 `queue`와 `visited`에 시작점 `0`이 함께 들어가는 이유가 낯설었다.

```text
queue   = [0]  → 앞으로 이웃을 조사할 정점
visited = [0]  → 이미 발견했으므로 다시 큐에 넣지 않을 정점
```

`visited`에 있다고 해서 해당 정점의 이웃 조사까지 끝난 것은 아니다. 큐에 남아 있다면 아직 조사할 차례를 기다리는 상태다.

## `deque(start)`에 정수를 전달함

### 당시 코드

```python
queue = deque(start)
```

### 원인

`start`는 정수 `0`인데, `deque()`는 여러 원소를 담은 반복 가능한 묶음을 받는다.

### 수정

```python
queue = deque([start])
```

리스트 `[start]`는 시작 정점 하나가 들어 있는 최초 큐다.

## 메서드와 메서드 호출을 혼동함

### 당시 코드

```python
queue.popleft
```

괄호가 없으면 큐에서 값을 꺼내는 기능 자체를 가리킬 뿐 실행하지 않는다.

### 수정

```python
current = queue.popleft()
```

`popleft()`는 큐 맨 앞의 정점을 제거하고, 그 값을 `current`에 저장한다.

## 방문 조건의 방향을 반대로 작성함

### 당시 코드

```python
if neigh in visited:
    visited.append(neigh)
```

### 문제점

이미 방문한 정점을 다시 기록한다. 새 이웃은 추가되지 않으므로 탐색이 진행되지 않는다.

### 수정

```python
if neigh not in visited:
```

## `visited`에는 기록하지만 `queue`에는 넣지 않음

0번의 이웃 `1`, `2`를 발견해도 큐에 넣지 않으면 큐는 빈 상태가 되어 첫 반복 뒤 종료한다. 따라서 2번의 이웃인 3번까지 도달하지 못한다.

```python
visited.append(neigh)  # 발견 기록
queue.append(neigh)    # 나중에 이웃을 조사하도록 예약
```

## 다시 확인할 질문

- `queue`에 있지만 아직 `visited`에 없는 상태가 가능한가?
- `visited`에는 있지만 `queue`에도 남아 있는 상태는 무슨 뜻인가?
- `queue.append(neigh)`만 하고 방문 기록을 하지 않으면 무방향 그래프에서 어떤 일이 생기는가?
