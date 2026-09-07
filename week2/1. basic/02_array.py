"""
[배열 - 2차원 배열 회전]

문제 설명:
- N x N 크기의 2차원 배열을 시계방향으로 90도 회전시킵니다.
- 배열의 인덱스 변환 규칙을 이해하는 문제입니다.

입력:
- matrix: N x N 크기의 2차원 리스트

출력:
- 시계방향으로 90도 회전된 2차원 리스트

예제:
입력:
[
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9]
]

출력:
[
    [7, 4, 1],
    [8, 5, 2],
    [9, 6, 3]
]
"""

def rotate_matrix_90(matrix):
    """
    2차원 배열을 시계방향으로 90도 회전
    
    Args:
        matrix: N x N 2차원 리스트
    
    Returns:
        회전된 2차원 리스트
    """
    """
        아이디어
            1) 90도 회전은 행열로 생각했을 때 첫 번째 행이 마지막 열로 치환되는 형태
                1-1) 내부 배열의 원소 하나씩 변환된 idx의 규칙을 찾기
                    3x3 배열 가정!
                        첫 번째 배열 [1,2,3]
                            1 - (0,0) 2 - (0,1) 3 - (0,2)
                                    ↓(90도 회전)
                            1 - (0,2) 2 - (1,2) 3 - (2,2)
                        두 번째 배열 [4,5,6]
                            4 - (1,0) 5 - (1,1) 6 - (1,2)
                                    ↓(90도 회전)
                            4 - (0,1) 5 - (1,1) 6 - (2,1)
                        ...
                        n 번째 배열 [3,5,6,..]
                            3 - (i,j) 5 - (i+1,j+1) 6 - (i+2,j+2) ...
                                    ↓(90도 회전)
                            3 - (i,n-1-i) 5 - (i+1,n-1-i) 6- (i+2,n-1-i)
                
            2) 이중 순회를 통해 90도 회전한 이차원 배열을 임시 배열에 반환
                -> 할당을 어떻게 할 것인가? append()?
                -> 임시 배열로 2차원 배열을 어떻게 생성할 것인가? tmp_matrix = [] ?
    """
    n = len(matrix)
    # 결과로 반환할 임시 2차원 배열 생성
    tmp_matrix = []
    for i in range(0, n): # []와 같은 빈 배열(행)을 n개만큼 생성
        tmp_matrix.append([])
        for j in range(0, n):
            tmp_matrix[i].append(0) # 현재 행에 0을 n개 추가

    # 2차원 배열이기 때문에 이중 for문을 사용
    for i in range(0, n):
        for j in range(0, n):
            tmp_matrix[j][n-1-i] = matrix[i][j] # 원본 (i,j)의 값을 회전 후 좌표에 저장
    return tmp_matrix
def print_matrix(matrix):
    """배열을 보기 좋게 출력하는 헬퍼 함수"""
    for row in matrix:
        print(row)

# 테스트 케이스
if __name__ == "__main__":
    # 테스트 케이스 1: 3x3 배열
    matrix1 = [
        [1, 2, 3],
        [4, 5, 6],
        [7, 8, 9]
    ]
    
    print("원본 배열:")
    print_matrix(matrix1)
    print("\n회전 후:")
    rotated1 = rotate_matrix_90(matrix1)
    print_matrix(rotated1)
    print()
    
    # 테스트 케이스 2: 4x4 배열
    matrix2 = [
        [1, 2, 3, 4],
        [5, 6, 7, 8],
        [9, 10, 11, 12],
        [13, 14, 15, 16]
    ]
    
    print("원본 배열:")
    print_matrix(matrix2)
    print("\n회전 후:")
    rotated2 = rotate_matrix_90(matrix2)
    print_matrix(rotated2)


