"""
[정수론 - 최대공약수(GCD)와 최소공배수(LCM)]

문제 설명:
- 두 정수의 최대공약수(GCD)와 최소공배수(LCM)를 구합니다.
- 유클리드 호제법을 사용하여 GCD를 효율적으로 계산합니다.
- GCD를 이용하여 LCM을 계산합니다.

입력:
- a, b: 두 개의 양의 정수

출력:
- GCD: 최대공약수
- LCM: 최소공배수

예제:
입력: a = 48, b = 18
출력: 
  GCD = 6
  LCM = 144

힌트:
- 유클리드 호제법: gcd(a, b) = gcd(b, a % b)
- LCM 공식: lcm(a, b) = (a × b) / gcd(a, b)
"""

def gcd(a, b):
    """
    유클리드 호제법을 사용한 최대공약수 계산
    
    Args:
        a, b: 두 양의 정수
    
    Returns:
        최대공약수
    """
    # TODO: 유클리드 호제법 구현
    # base case: b가 0이면 a 반환
    # recursive를 이용 
    # 유클리드 호제법: 두 수 중에 큰 수를 작은 수로 나누어 나온 몫고 나머지를 계속해서 반복하다가 나머지가 0일떄의 몫을 구하는 개념
    if b == 0:
        return a
    rem = a%b
    if rem == 0:
        return b

    return gcd(b, a%b)
    pass

def gcd_iterative(a, b):
    """
    반복문을 사용한 최대공약수 계산
    
    Args:
        a, b: 두 양의 정수
    
    Returns:
        최대공약수
    """
    # TODO: 반복문으로 구현
    # b가 0이 될 때까지 반복
    while b > 0:
        tmp = b
        rem = a%b
        b = rem
        a = tmp
    return a 
    pass

def lcm(a, b):
    """
    최소공배수 계산
    
    Args:
        a, b: 두 양의 정수
    
    Returns:
        최소공배수
    """
    # 최소공배수 계산 - 두 수의 곱을 두 수의 최대공약수로 나눈 결과값
    # TODO: LCM 계산
    result = a*b//gcd(a,b)
    return result
    pass

def extended_gcd(a, b):
    """
    확장 유클리드 호제법
    ax + by = gcd(a, b)를 만족하는 x, y를 찾음
    
    Args:
        a, b: 두 양의 정수
    
    Returns:
        (gcd, x, y) 튜플
    """
    # TODO: 확장 유클리드 호제법 구현
    # base case: b가 0이면 (a, 1, 0) 반환   
    # recursive case
    # 역추적하며 x, y 계산
    return False

def is_prime(n):
    """
    소수 판별
    
    Args:
        n: 판별할 양의 정수
    
    Returns:
        소수이면 True, 아니면 False
    """
    # TODO: 소수 판별 구현
    # n이 2보다 작으면 False
    # 2부터 sqrt(n)까지 나누어 떨어지는지 확인    
    # 3부터 sqrt(n)까지 홀수만 확인
    """
        아이디어
        1) 소수 개념을 이해
            소수란 1과 자기 자신을 제외한 수로 나누어 떨어지지 않는 수. (단, 1과 2는 제외)
            -> 보통 짝수는 소수에 포함이 되지 않음. (이유: 4는 1,2,4로 나누어떨어지기 때문)
        2) 말로 이해한 내용을 sudo code 형식로 한 단계씩 작성
            2-1)
                n이 1일 때 False 반환 
            2-2)
                n이 2일 때 True 반환 
            2-3)
                n이 3부터는 1과 자기 자신을 제외한 수들로 나누었을 때 나누어떨어진다면 소수X / 나누어떨어지지 않는다면 소수O
    """
    """
        ************************구현1************************
    """
    # def sqrt(n):
    #     return n**n
    # if n < 2:
    #     return False
    # elif n == 2:
    #     return True
    # elif n > 2:
    #     if sqrt(n)%2 != 0:
    #         return True
    """
        ************************구현1************************
    """
    """
        구현1 - 실패 이유
            1) 거듭제곱근을 표현할 수 있는 파이썬 기본 문법 오류
            2) n이 3부터 홀수를 계산한다면 와 6,9와 같은 숫자들은 소수가 아닌데도 소수라고 반환.
        구현1 - 해결책
            1) AI의 도움을 받아 거듭제곱근을 표현할 수 있는 파이썬 문법에 대한 개념 이해
            2) 홀수가 아닌 모든 수를 나누어보는 경우의 수를 코드에 녹여내야함. -> 3 ~ sqrt(n)까지 반복하는데 나누어떨어지는 즉시 false.
    """
    """
        ************************구현2************************
    """
    def sqrt(n):
        return n**0.5
    if n < 2:
        return False
    elif n == 2:
        return True
    elif n > 2:
        for i in range(2,int(sqrt(n))+1): #❗️범위 설정을 정확하게 하는 것이 중요!
            if n%i == 0:
                return False
        return True
    """
        ************************구현2************************
    """
    
    pass 

# 테스트 케이스
if __name__ == "__main__":
    # 테스트 케이스 1: GCD와 LCM
    print("=== 테스트 케이스 1: GCD와 LCM ===")
    a, b = 48, 18
    print(f"a = {a}, b = {b}")
    print(f"GCD (재귀): {gcd(a, b)}")
    print(f"GCD (반복): {gcd_iterative(a, b)}")
    print(f"LCM: {lcm(a, b)}")
    print()
    
    # 테스트 케이스 2
    print("=== 테스트 케이스 2 ===")
    a, b = 100, 75
    print(f"a = {a}, b = {b}")
    print(f"GCD: {gcd(a, b)}")
    print(f"LCM: {lcm(a, b)}")
    print()
    
    # 테스트 케이스 3: 서로소
    print("=== 테스트 케이스 3: 서로소 ===")
    a, b = 17, 19
    print(f"a = {a}, b = {b}")
    print(f"GCD: {gcd(a, b)}")
    print(f"LCM: {lcm(a, b)}")
    print("서로소(coprime): GCD가 1")
    print()
    
    # 테스트 케이스 4: 확장 유클리드
    print("=== 테스트 케이스 4: 확장 유클리드 ===")
    a, b = 35, 15
    g, x, y = extended_gcd(a, b)
    print(f"a = {a}, b = {b}")
    print(f"GCD = {g}")
    print(f"{a} × {x} + {b} × {y} = {g}")
    print(f"검증: {a * x + b * y} = {g}")
    print()
    
    # 테스트 케이스 5: 소수 판별
    print("=== 테스트 케이스 5: 소수 판별 ===")
    test_numbers = [2, 3, 4, 17, 20, 29, 100]
    for num in test_numbers:
        result = "소수" if is_prime(num) else "합성수"
        print(f"{num}: {result}")


