# Python — 딕셔너리와 메모이제이션

## 학습 계기

`06_dp_fibonacci.py`에서 재귀 호출 사이에 계산 결과를 보관하고 재사용하는 과정에서 작성했다.

## key와 value

```python
memo[n] = result
```

- `n`: 계산한 부분 문제를 식별하는 key
- `result`: 그 부분 문제의 계산 결과인 value
- `memo[n]`: key `n`에 저장된 value 조회

`return n`은 인덱스를 반환하고, `return memo[n]`은 저장된 계산 결과를 반환한다.

## 저장과 조회

```python
if n in memo:
    return memo[n]

memo[n] = calculate(n)
return memo[n]
```

메모이제이션에서는 저장만으로 충분하지 않다. 계산 전에 key의 존재 여부를 확인하고 기존 결과를 반환해야 중복 계산을 피할 수 있다.

## 최초 호출에서만 초기화

```python
def solve(n, memo=None):
    if memo is None:
        memo = {}
```

재귀 호출마다 `{}`를 새로 만들면 이전 결과가 사라진다. `None`일 때만 만들면 이후 재귀 호출은 전달받은 같은 딕셔너리를 사용한다.

## 대입문의 평가 순서

```python
memo[n] = left() + right()
```

`left()`와 `right()`를 호출하고 덧셈까지 마친 후 결과를 `memo[n]`에 저장한다. 함수 호출식 자체가 딕셔너리에 먼저 저장되는 것은 아니다.

## 관련 문제

- [DP 피보나치 문제점 기록](../문제모음집/06_dp_fibonacci.md)
- [DP 피보나치 설계 기록](../설계모음집/06_dp_fibonacci.md)
