# Greedy 미팅 — 문제점 기록

- 풀이 코드: [`09_greedy_meeting.py`](../../week3/1.%20basic/09_greedy_meeting.py)
- 진행 상태: 구현 및 디버깅 중
- 설계 기록: [Greedy 미팅 — 설계 기록](../설계모음집/09_greedy_meeting.md)

## 순회와 튜플

- `(0, len(meetings))`를 범위로 생각했다.
- 튜플 자체를 순회하는 것과 `range()`가 만든 정수 범위를 순회하는 것의 차이가 불분명했다.
- `(start, end)` 구조에서 `meetings[i][0]`, `meetings[i][1]`이 각각 무엇을 뜻하는지 확인할 필요가 있었다.
- 인덱스로 접근하는 방식과 tuple unpacking을 비교할 필요가 있었다.

관련 개념: [튜플과 순회](../개념모음집/python_튜플과_순회.md)

## 리스트 상태와 조작

- 빈 `selected`에서 `selected[0]` 또는 `selected[-1]`에 접근해 `IndexError`가 발생할 수 있었다.
- 빈 리스트에는 `append()`를 사용할 수 없다고 잘못 추측했다.
- `append()`와 index assignment의 차이가 불분명했다.
- `pop()`의 대상을 잘못 정하면 이미 선택한 회의를 제거할 수 있었다.
- `if not selected`, `selected[-1]`, `continue`를 언제 사용할지 정리할 필요가 있었다.

관련 개념: [리스트 조작](../개념모음집/python_리스트_조작.md)

## 정렬 기준

- `(start, end)` 튜플에 대한 `sort()`의 기본 비교 순서를 확인할 필요가 있었다.
- `sort(key=...)`의 `key`에 숫자가 아닌 함수를 전달한다는 점이 낯설었다.
- `get_end`와 `get_end()`를 혼동했다.
- 일반 함수와 `lambda`로 같은 정렬 기준을 표현하는 법을 비교할 필요가 있었다.

관련 개념: [정렬과 key](../개념모음집/python_정렬과_key.md)

## 발견된 오류 기록

| 오류 또는 현상 | 당시 추측 | 현재 상태 |
|---|---|---|
| `IndexError: list index out of range` | 빈 리스트에는 `append()`가 안 될 수 있다고 생각함 | 추측이 틀렸음을 확인; 정확한 접근 순서를 점검 중 |
| `AttributeError: 'tuple' object has no attribute 'pop'` | 선택을 취소하기 위해 `pop()`을 사용하려 함 | 어떤 객체에 `pop()`을 호출했는지 점검 필요 |
| 선택 결과가 의도와 달라질 가능성 | 먼저 추가하고 조건이 맞지 않으면 제거함 | 조건을 먼저 검사하는 설계로 수정 중 |

## 다음에 다시 풀 때 확인할 핵심

작성 예정. 현재 구현과 디버깅이 끝난 뒤, 스스로 설명할 수 있는 문장으로 정리한다.
