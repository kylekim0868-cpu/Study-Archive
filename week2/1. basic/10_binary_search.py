"""
[이분 탐색 - Binary Search]

문제 설명:
- 정렬된 배열에서 특정 값을 찾는 이분 탐색 알고리즘을 구현합니다.
- 배열을 반으로 나누어 탐색 범위를 절반씩 줄여갑니다.

입력:
- arr: 정렬된 정수 배열
- target: 찾고자 하는 값

출력:
- target이 있는 인덱스 (없으면 -1)

예제:
입력: arr = [1, 3, 5, 7, 9, 11, 13], target = 7
출력: 3

힌트:
- left, right 포인터 사용
- mid = (left + right) // 2
- arr[mid]와 target 비교하여 범위 조정
"""

def binary_search(arr, target):
    """
    이분 탐색 구현
    
    Args:
        arr: 정렬된 배열
        target: 찾을 값
    
    Returns:
        target의 인덱스 (없으면 -1)
    """
    """
        아이디어
            1) 배열의 길이만큼 반복문을 돌린다
            2) 반복문 안에 target과 배열의 값의 일치 여부 조건을 넣는다.
            3) 일치하면 원본 배열의 index 반환
            4) 일치하지 않으면 -1 반환
            -> 선형 탐색(단순 기본 문법 로직)
    """
    """
        ************************구현1************************
    """
    # n = len(arr)
    # for i in range(0, n):
    #     if target == arr[i]:
    #         return i
    # return -1
    pass
    """
        ************************구현1************************
    """
    """
            이분 탐색 아이디어(조건: 무조건 정렬된 배열에 경우 가능)
                1) 배열의 양 끝쪽 index를 left와 right에 할당
                2) 양쪽의 중간인 mid = left+right // 2 할당
                3) mid를 기준으로 반을 나누어 target과 비교
    """
    """
        ************************구현2************************
    """
    n = len(arr)
    left = 0 # 배열의 가장 첫 번째 idx
    right = n-1 # 배열의 가장 마지막 idx
    mid = int((left+right)/2) #배열의 가운데 idx (배열이 홀수 개일 경우 float이기 때문에 int를 사용해 소숫점 뒤는 버림)

    if target < arr[mid]: #target이 배열의 가운데 idx에 해당하는 숫자보다 작을 경우 -> range: 0~mid까지 반복하며 target과 일치하는지 찾기
        for i in range(left, mid):
            if target == arr[i]: return i
    elif target > arr[mid]: #target이 배열의 가운데 idx에 해당하는 숫자보다 클 경우 -> range: mid~right까지 반복하며 target과 일치하는지 찾기
        for i in range(mid, right):
            if target == arr[i]: return i
    else: return mid # target 배열의 mid 인덱스에 해당하는 값과 같을 경우 mid 반환

    return -1
    pass
    """
        ************************구현2************************
    """
# 테스트 케이스
if __name__ == "__main__":
    # 테스트 케이스 1
    arr1 = [1, 3, 5, 7, 9, 11, 13]
    target1 = 7
    result1 = binary_search(arr1, target1)
    print(f"배열: {arr1}")
    print(f"찾는 값: {target1}")
    print(f"결과: 인덱스 {result1}")
    print()
    
    # 테스트 케이스 2
    arr2 = [2, 4, 6, 8, 10, 12, 14, 16, 18, 20]
    target2 = 14
    result2 = binary_search(arr2, target2)
    print(f"배열: {arr2}")
    print(f"찾는 값: {target2}")
    print(f"결과: 인덱스 {result2}")
    print()
    
    # 테스트 케이스 3: 없는 값
    arr3 = [1, 3, 5, 7, 9]
    target3 = 6
    result3 = binary_search(arr3, target3)
    print(f"배열: {arr3}")
    print(f"찾는 값: {target3}")
    print(f"결과: 인덱스 {result3}")
