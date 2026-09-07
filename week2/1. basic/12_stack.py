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
        아이디어
            1) stack은 후입선출 개념의 자료구조. 예를 들면, 뷔페식으로 나오는 음식들. 가장 최근에 요리한 음식들을 손님께 내놓는다.
            2) 올바른 괄호의 경우 - 여는 괄호와 닫는 괄호가 짝을 이룬다면 True
            3) 잘못된 괄호의 경우 - 짝을 이루지 못하면 False
            4) 괄호들을 넣을 임시 배열 생성
            5) 입력받은 문자열 순회
            6) 만약 (을 만난다면 append / )을 만난다면 pop을 진행
            7) 문자열 순회가 끝난 후 스택이 비어 있어야 True
    """
    tmp_is = []
    for chr in s:
        if chr == "(":
            tmp_is.append(chr)
        elif chr == ")":
            if not tmp_is: return False
            tmp_is.pop()
    if not tmp_is: return True 
    else: return False
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


