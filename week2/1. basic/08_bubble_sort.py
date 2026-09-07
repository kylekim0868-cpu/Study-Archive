"""
[버블 정렬 구현]

문제 설명:
- 버블 정렬(Bubble Sort) 알고리즘을 구현합니다.
- 인접한 두 원소를 비교하여 정렬하는 방식입니다.
- 가장 큰 원소가 배열의 끝으로 "버블"처럼 이동합니다.

입력:
- arr: 정렬되지 않은 정수 배열

출력:
- 오름차순으로 정렬된 배열

예제:
입력: [64, 34, 25, 12, 22, 11, 90]
출력: [11, 12, 22, 25, 34, 64, 90]
"""

def bubble_sort(arr):
    """
    버블 정렬 구현
     
    Args:
        arr: 정렬할 배열
    
    Returns:
        정렬된 배열
    """
    """
        아이디어
            1) n만큼 순회하면서 arr[i] n-1만큼 순회하면서 arr[j] 비교
            2) arr[j] > arr[j+1] : 스왑 -> 버블 정렬은 인접한 두 원소를 비교한다는 개념
    """
    n = len(arr)
    for i in range(0, n):
        for j in range(0, n-1):
            if arr[j] > arr[j+1]:
                arr[j], arr[j+1] = arr[j+1], arr[j]
    return arr

def bubble_sort_optimized(arr):
    """
    최적화된 버블 정렬 (조기 종료 포함)
    
    Args:
        arr: 정렬할 배열
    
    Returns:
        정렬된 배열
    """
    n = len(arr)
    

    return arr

# 테스트 케이스
if __name__ == "__main__":
    # 테스트 케이스 1
    arr1 = [64, 34, 25, 12, 22, 11, 90]
    print("=== 테스트 케이스 1 ===")
    print(f"정렬 전: {arr1}")
    result1 = bubble_sort(arr1.copy())
    print(f"정렬 후: {result1}")
    print()
    
    # 테스트 케이스 2: 이미 정렬된 배열
    arr2 = [1, 2, 3, 4, 5]
    print("=== 테스트 케이스 2: 이미 정렬됨 ===")
    print(f"정렬 전: {arr2}")
    result2 = bubble_sort_optimized(arr2.copy())
    print(f"정렬 후: {result2}")
    print("최적화 버전은 1번의 패스만 수행")
    print()
    
    # 테스트 케이스 3: 역순 배열
    arr3 = [5, 4, 3, 2, 1]
    print("=== 테스트 케이스 3: 역순 ===")
    print(f"정렬 전: {arr3}")
    result3 = bubble_sort(arr3.copy())
    print(f"정렬 후: {result3}")


