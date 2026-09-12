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
        설계)
            1) mid - 배열의 중간 idx 초기화
                -> 이 값을 구하려면 시작/끝 idx 필요
                    -> start = 0, end = 0
            2) 반복문을 사용. 그 전에 분기를 나누어 mid구간을 순회할지 end구간을 순회할지
                ! 이유: 정렬되어 있는 배열이기 때문에 중간값과 비교하여 시간복잡도를 줄일 수 있다. O(n) + O(n) -> O(n)
                2-1) start ~ mid 구간 순회
                    target과 일치한다면 target의 idx에 idx 할당 후 순회 종료
                2-2) mid ~ end 구간 순회
                    target과 일치한다면 target의 idx에 idx 할당 후 순회 종료
            3) target이 없다면 결과 idx에 -1 반환
    """
    # res_idx = 0
    # start = 0
    # end = len(arr)-1
    # mid = (start+end)//2

    # if target == arr[mid]:
    #     return mid
    # if target < arr[mid]:
    #     for i in range(start, mid):
    #         if target == arr[i]:
    #             return i
    # elif target > arr[mid]:
    #     for i in range(mid, end+1):
    #         if target == arr[i]:
    #             return i
    # return -1
    """
    Trouble Shooting)
        이분 탐색의 핵심을 제대로 이해하지 못했다. 결국 한 번만 반으로 나누면 시간복잡도는 줄어들지 않는다.
        O(n) -> O(log n)으로 줄이기 위해서는 가능한 쪼갤 수 있는 범위까지 문제를 쪼갠다면 비교하면 된다.
        결론: 재귀함수로 구현.
    """
    """
    재귀함수)
        - 재귀를 구현할 내용: target과 비교할 한 개의 원소가 남을 때까지 반으로 나누기
        - 종료지점: 원소의 배열 길이 == 1
        - 어떻게 담고 반환할 것인가? 
            target과 일치한다면 arr[i] 에서 i를 반환
            !binary_search(쪼개진 배열, target)
    """
    """
    TroubleShooting2)
        - 문제에서 binary_search() 인자는 정해져있기 때문에 새로운 보조 함수를 재귀함수로 사용!
        - start > end라면 타겟을 찾지 못하고 배열이 비어있기 때문에 종료
    """
    start = 0
    end = len(arr)-1

    def search(start, end):
        mid = (start+end)//2
        if start > end:
            return -1
        if target == arr[mid]:
            return mid
        if target < arr[mid]:
            return search(start, mid-1)
        if target > arr[mid]:
            return search(mid+1, end)
    idx = search(start, end)

    return idx
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
