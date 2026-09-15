"""
[스택 - 괄호 짝 맞추기]

문제 설명:
- 스택(Stack)을 사용하여 괄호가 올바르게 짝지어져 있는지 확인합니다.
- LIFO (Last In First Out) 구조를 활용합니다.

입력:
- s: 괄호 문자열 (예: "(())", "(()")

출력:
- True: 올바른 괄호
- False: 잘못된 괄호

예제:
입력: "(())"
출력: True

입력: "(()"
출력: False
"""

def is_valid_parentheses(s):
    """
    괄호 짝이 맞는지 확인
    
    Args:
        s: 괄호 문자열
    
    Returns:
        올바른 괄호면 True, 아니면 False
    """
    """
    설계)
        - stack = []; s의 문자를 담을 stack 변수
        - s만큼 순회
            - stack이 비어 있다면 s의 문자 push
            - s의 문자가 "("일 경우 push
            - s의 문자가 ")"일 경우 + stack에 "("있다면 "("을 pop()해서 꺼낸다
        - 순회가 끝나고도 문자가 남아있다면 False / 아니라면 True 
    """
    """
    TroubleShooting)
        - 예외 처리의 부재
            - 만약 ")"를 먼저 만난다면 스택은 비어 있다. 이 상태에서 pop()을 호출하면 정의되지 않은 동작이 발생할 수 있기 때문에, pop()을 호출하기 전에 스택이 비어 있는지 확인해야 한다. (IndexError)
    """
    stack = []

    for chr in s:
        if (chr == "("):
            stack.append(chr)
        elif(chr == ")"):
            # ) 차례에 stack이 비어 있다면 False로 반환하고 종료
            if not stack:
                return False
            stack.pop()
    return not stack
# 테스트 케이스
if __name__ == "__main__":
    # 테스트 케이스 1
    test1 = "(())"
    result1 = is_valid_parentheses(test1)
    print(f"입력: {test1}")
    print(f"결과: {result1}")
    print()
    
    # 테스트 케이스 2
    test2 = "(()"
    result2 = is_valid_parentheses(test2)
    print(f"입력: {test2}")
    print(f"결과: {result2}")
    print()
    
    # 테스트 케이스 3
    test3 = "()(())"
    result3 = is_valid_parentheses(test3)
    print(f"입력: {test3}")
    print(f"결과: {result3}")
    print()
    
    # 테스트 케이스 4
    test4 = "())("
    result4 = is_valid_parentheses(test4)
    print(f"입력: {test4}")
    print(f"결과: {result4}")


