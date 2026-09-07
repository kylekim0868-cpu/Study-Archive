"""
[문자열 - 회문(Palindrome) 판별]

문제 설명:
- 주어진 문자열이 회문(앞에서 읽으나 뒤에서 읽으나 같은 문자열)인지 판별합니다.
- 대소문자를 구분하지 않고, 공백과 특수문자는 무시합니다.

입력:
- s: 판별할 문자열

출력:
- True: 회문인 경우
- False: 회문이 아닌 경우

예제:
입력: "A man, a plan, a canal: Panama"
출력: True

입력: "race a car"
출력: False
"""

def is_palindrome(s):
    """
    문자열이 회문인지 판별하는 함수
    
    Args:
        s: 판별할 문자열

    Returns:
        bool: 회문이면 True, 아니면 False
    """
    """
        아이디어
            0) 문자열 인자(Args)를 먼저 통일시킨다. ex) abCbA -> abcba # 이유는 파이썬에서 대문자와 소문자를 다르다고 판별
            1) 문자열의 문자 개수만큼 순회
            2) 순회하면서 공백과 특수문자만 빼고 추출 -> isalnum()메서드 사용
            3) 문자와 숫자만 담은 문자열 뒤집기
            4) 뒤집은 문자열 = 기존 문자열 -> 일치하면 결과값에 True반환 / 일치하지 않으면 결과값에 False반환
        시간복잡도
            0(n)
                - 근거: 입력 문자열의 길이가 n이라고 가정한다면 n만큼만 순회하기 때문. n이 커지면 시간복잡도 n만큼 증가!
    """
    # lower()
    s = s.lower()
    # 숫자와 문자만 담아줄 임시 문자열 생성
    new_chr = ""

    # 문자열 순회하면서 isalnum()을 사용해 숫자와 문자만 new_chr에 할당
    for chr in s:
        if chr.isalnum():
            new_chr += chr
    # 문자열을 뒤집어 일치 여부 판단 후 반환
    if new_chr[::-1] == new_chr:
        return True
    else:
        return False
    
#테스트 케이스
if __name__ == "__main__":
    # 테스트 케이스 1
    test1 = "A man, a plan, a canal: Panama"
    result1 = is_palindrome(test1)
    print(f"입력: \"{test1}\"")
    print(f"회문 여부: {result1}")
    print()
    
    # # 테스트 케이스 2
    test2 = "race a car"
    result2 = is_palindrome(test2)
    print(f"입력: \"{test2}\"")
    print(f"회문 여부: {result2}")
    print()
    
    # # 테스트 케이스 3
    test3 = "Was it a car or a cat I saw?"
    result3 = is_palindrome(test3)
    print(f"입력: \"{test3}\"")
    print(f"회문 여부: {result3}")
    print()
    
    # # 테스트 케이스 4
    test4 = "Madam"
    result4 = is_palindrome(test4)
    print(f"입력: \"{test4}\"")
    print(f"회문 여부: {result4}")


