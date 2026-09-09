# 딕셔너리 — 빈 것과 None 구분하기

[복습 목록](../README.md)

## 먼저 답해볼 질문

- memo가 {}일 때 not memo와 memo is None은 각각 무엇일까?
- memo = {}와 memo[n] = 값은 무엇이 다를까?
- graph, graph.values(), graph[start]를 순회하면 각각 무엇이 나올까?

<details>
<summary>막혔을 때 확인할 핵심</summary>

- not x는 참·거짓 판정을 뒤집는다. None, False, 숫자 0, 빈 자료구조는 거짓으로 판단된다.
- x is None은 정확히 None 객체인지 확인한다. 빈 딕셔너리는 존재하는 객체다.
- memo = {}는 새 딕셔너리를 가리키게 한다. memo[n] = 값은 기존 딕셔너리의 내용을 바꾼다.
- 같은 객체를 전달받은 함수끼리는 내용 변경을 공유한다. 한쪽에서 새 객체를 대입해도 다른 쪽 변수까지 바뀌지 않는다.
- key로 값을 조회한다. 없는 키를 읽으면 KeyError가 나지만, 새 키에 대입해서 추가할 수 있다.

| x | not x | x is None |
|---|---|---|
| None | True | True |
| {} 또는 [] | True | False |
| 0 또는 False | True | False |
| [0] | False | False |

</details>

## 내가 헷갈린 부분

‘없다’라고 뭉뚱그려 생각했다. 0점은 미채점이 아니고, 빈 딕셔너리는 딕셔너리가 없는 상태가 아니다. 정확히 None만 처리할지 먼저 정하자.

| 순회 대상 | 나오는 것 |
|---|---|
| graph | 키 하나씩 |
| graph.values() | 값 하나씩 — 인접 리스트라면 리스트 하나씩 |
| graph.items() | (키, 값) 쌍 하나씩 |
| graph[start] | 해당 정점의 이웃 하나씩 |

[DP 복습](algorithm_top_down_dp.md) · [당시 오류](../문제모음집/06_dp_fibonacci.md) · [Python 공식 정의](https://docs.python.org/3/library/stdtypes.html#truth-value-testing)
