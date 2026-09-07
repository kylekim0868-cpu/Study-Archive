"""
[머지 정렬 구현]

문제 설명:
- 머지 정렬(Merge Sort) 알고리즘을 구현합니다.
- 분할 정복(Divide and Conquer) 방식을 사용합니다.
- 배열을 절반으로 나누고, 각각을 정렬한 후 병합합니다.

입력:
- arr: 정렬되지 않은 정수 배열

출력:
- 오름차순으로 정렬된 배열

예제:
입력: [38, 27, 43, 3, 9, 82, 10]
출력: [3, 9, 10, 27, 38, 43, 82]

힌트:
- 배열을 절반으로 분할 (재귀)
- 각 부분을 재귀적으로 정렬
- 정렬된 두 부분을 병합
"""

def merge(arr, left, mid, right):
    """
    두 개의 정렬된 부분 배열을 병합하는 함수
    
    Args:
        arr: 원본 배열
        left: 왼쪽 부분의 시작 인덱스
        mid: 왼쪽 부분의 끝 인덱스
        right: 오른쪽 부분의 끝 인덱스
    """
    """
        아이디어)
            1) 배열을 반으로 나누기 위해 중간값을 구하기
            2) 시작 인덱스부터 중간 인덱스까지 - 왼쪽 배열 / 중간 인덱스부터 끝 인덱스까지 - 오른쪽 배열 => 재귀로 구현
            ❌ 3) ~~배열[시작 인덱스] > 배열[중간 인덱스] : 스왑 배열[시작 인덱스], 배열[중간 인덱스] = 배열[중간 인덱스], 배열[시작 인덱스]~~
            ✅ 3) 머지 정렬에서는 배열안에서 비교하거나 값을 교환하지 않음
            4) 종료 조건 - 배열[시작 인덱스] == 배열[끝(중간) 인덱스] : return 
                ❗️이유: 1개의 배열은 이미 정렬이 됐다고 간주
            5) 왼쪽 배열 정렬 / 오른쪽 배열 정렬 
            6) 두 배열 머지
    """
    # TODO: 왼쪽과 오른쪽 부분 배열을 임시 배열로 복사
    left_arr = []
    for i in range(left, mid+1):
        left_arr.append(arr[i])
    right_arr = []
    for i in range(mid+1, right+1):
        right_arr.append(arr[i])
    pass
    
    # TODO: 두 배열을 병합
    pass
    merge_arr = []

    # 1) for문
    # TODO: left_arr와 right_arr를 비교하며 작은 값을 arr에 복사
    pass
    # 1) for문
    # 왼쪽 / 오른쪽 배열의 개수가 다르기 때문에 2개의 서로 다른 포인터를 할당
    i = 0
    j = 0
    for k in range(len(left_arr)+len(right_arr)): # 왼쪽과 오른쪽의 배열의 개수가 같을 경우가 있기 때문에 2개의 길이를 합친 수만큼 순회
        # case1) 오른쪽 배열을 다 썼거나
        if j >= len(right_arr):
            merge_arr.append(left_arr[i])
            i += 1
        # case2) 왼쪽 원소가 더 작은 경우
        elif (i < len(left_arr) and left_arr[i] <= right_arr[j]):
            merge_arr.append(left_arr[i])
            i += 1
        # case3) 왼쪽 배열을 다 썼거나 오른쪽 원소가 더 작은 경우
        else: 
            merge_arr.append(right_arr[j])
            j += 1

    # 어려운 코드 구현
    for k in range(len(merge_arr)):
        arr[left+k] = merge_arr[k]
    pass

def merge_sort_helper(arr, left, right):
    """
    머지 정렬 재귀 함수
    
    Args:
        arr: 배열
        left: 시작 인덱스
        right: 끝 인덱스
    """
    # TODO: base case - left가 right보다 작을 때만 정렬
    if left >= right:
        return 
    mid = (left+right)//2
    merge_sort_helper(arr, left, mid)
    merge_sort_helper(arr, mid+1, right)
    merge(arr, left, mid, right)                
    ## 중간 지점 계산
    ## 왼쪽 절반 재귀 정렬
    ## 오른쪽 절반 재귀 정렬
    ## 정렬된 두 절반을 병합
    pass

def merge_sort(arr):
    """
    머지 정렬 메인 함수
    
    Args:
        arr: 정렬할 배열
    
    Returns:
        정렬된 배열
    """
    if len(arr) > 1:
        merge_sort_helper(arr, 0, len(arr) - 1)
    return arr

# 테스트 케이스
if __name__ == "__main__":
    # 테스트 케이스 1
    arr1 = [38, 27, 43, 3, 9, 82, 10]
    print("=== 테스트 케이스 1 ===")
    print(f"정렬 전: {arr1}")
    result1 = merge_sort(arr1.copy())
    print(f"정렬 후: {result1}")
    print()
    
    # 테스트 케이스 2
    arr2 = [12, 11, 13, 5, 6, 7]
    print("=== 테스트 케이스 2 ===")
    print(f"정렬 전: {arr2}")
    result2 = merge_sort(arr2.copy())
    print(f"정렬 후: {result2}")
    print()
    
    # 테스트 케이스 3: 역순
    arr3 = [9, 8, 7, 6, 5, 4, 3, 2, 1]
    print("=== 테스트 케이스 3: 역순 ===")
    print(f"정렬 전: {arr3}")
    result3 = merge_sort(arr3.copy())
    print(f"정렬 후: {result3}")
    print()
    
    # 테스트 케이스 4: 중복 원소
    arr4 = [5, 2, 8, 2, 9, 1, 5, 5]
    print("=== 테스트 케이스 4: 중복 원소 ===")
    print(f"정렬 전: {arr4}")
    result4 = merge_sort(arr4.copy())
    print(f"정렬 후: {result4}")


