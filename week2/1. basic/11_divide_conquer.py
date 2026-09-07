"""
[분할 정복 - 배열의 최댓값 찾기]

문제 설명:
- 분할 정복(Divide and Conquer) 방식으로 배열의 최댓값을 찾습니다.
- 배열을 반으로 나누고, 각 부분의 최댓값을 구한 후 비교합니다.

입력:
- arr: 정수 배열
- left: 시작 인덱스
- right: 끝 인덱스

출력:
- 배열의 최댓값

예제:
입력: [3, 5, 1, 8, 2, 9, 4]
출력: 9

힌트:
- Base case: left == right일 때 arr[left] 반환
- 배열을 반으로 나누어 재귀 호출
- 왼쪽과 오른쪽의 최댓값 중 큰 값 반환
"""

def find_max_divide_conquer(arr, left, right):
    """
    분할 정복으로 최댓값 찾기
    
    Args:
        arr: 배열
        left: 시작 인덱스
        right: 끝 인덱스
    
    Returns:
        최댓값
    """
    """
            아이디어
                1) 배열을 반으로 나눈다
                2) 또 반으로 나눈다         ------
                ...                          ㅣ     반으로 나눈다 => 구현할 재귀함수의 핵심 내용 
                N) 반으로 나눈다            ------
                3) 만약, 반으로 나눈 배열의 길이가 1이면 다시 반으로 합친 후
                4) 또 반으로 합친다         ------
                ...                           ㅣ    반으로 합친다 => 구현할 재귀함수의 핵심 내용
                N) 반으로 합친다            ------
                5) 반으로 합친 배열의 길이가 1이면 그 값(최대값)을 반환
                ❓그러면 재귀함수 2개를 써야하는것인가? 라는 생각이 든다.
                                
    """
    """
        ************************구현1************************
    """
        # mid = (left+right)/2

        # if(left == right):  #배열의 길이가 1이기 때문에 하나 존재하는 값을 반환
        #     return arr[left]
        # if(arr[left] > arr[right]):
        #     return arr[left]
        # elif(arr[left] < arr[right]):
        #     return arr[right]    
        # else: 
        #     return find_max_divide_conquer(arr, left, right)
        # pass
    """
        ************************구현1************************
    """
    """
        ************************구현2************************
    """
    # mid = (left+right)//2 # 배열의 중간 포인터
    
    # if(left == right):  # 배열의 길이가 1이기 때문에 하나 존재하는 값을 반환
    #     return arr[left]
    # if (left >= mid):
    #     return find_max_divide_conquer(arr, left, mid)
    # if(left < mid):
    #     return find_max_divide_conquer(arr, mid+1, right)
    """
        ************************구현2************************
    """
    """
        ************************구현3************************
    """
    # mid = (left+right)//2 # 배열의 중간 포인터
    
    # if(left == right):  # 배열의 길이가 1이기 때문에 하나 존재하는 값을 반환
    #     return arr[left]
    # if(left >= mid):
    #     return find_max_divide_conquer(arr, left, mid)
    # if(left < mid):
    #     return find_max_divide_conquer(arr, mid+1, right)
    """
        ************************구현3************************
    """
    """
        아이디어4
            1) mid를 기준으로 왼쪽 영역 / 오른쪽 영역으로 나눈다
            2) left의 최댓값 추출
            3) right의 최댓값 추출
            4) left최댓값 right최댓값 비교 후 더 큰 수를 반환
                단, 배열의 길이가 1일 때는 그 값을 반환
                                        
    """
    """
        ************************구현4************************
    """
    mid = (left+right)//2

    # base line: 양, 끝 idx가 같다는 건 배열의 길이가 1
    if(left == right): 
        return arr[left]
    left_max = find_max_divide_conquer(arr, left, mid)
    right_max = find_max_divide_conquer(arr, mid+1, right)

    if(left_max > right_max):
        return left_max
    elif(left_max < right_max):
        return right_max
    else: # ❗️배열은 중복이 허용되지 않는 자료구조인 줄 알고 이 부분을 구현 못했음. 중복이 허용되지 않는 배열은 set!
        return left_max
    """
        ************************구현4************************
    """    
# 테스트 케이스
if __name__ == "__main__":
    # 테스트 케이스 1
    arr1 = [3, 5, 1, 8, 2, 9, 4]
    result1 = find_max_divide_conquer(arr1, 0, len(arr1) - 1)
    print(f"배열: {arr1}")
    print(f"최댓값: {result1}")
    print()
    
    # 테스트 케이스 2
    arr2 = [10, 20, 30, 40, 50]
    result2 = find_max_divide_conquer(arr2, 0, len(arr2) - 1)
    print(f"배열: {arr2}")
    print(f"최댓값: {result2}")
    print()
    
    # 테스트 케이스 3
    arr3 = [100]
    result3 = find_max_divide_conquer(arr3, 0, len(arr3) - 1)
    print(f"배열: {arr3}")
    print(f"최댓값: {result3}")


