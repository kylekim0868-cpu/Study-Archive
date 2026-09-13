"""
    원형큐 구현
    - 문제: 고정 크기 배열(예: 크기 10)만 사용하여, 요소를 이동시키지 않고 O(1)로 삽입/삭제가 가능한 큐를 설계한다면 어떻게 해야할까? 설계 방식을 설명하고 간단하게 파이썬 혹은 수도 코드로 enque, deque 함수를 만들어 보시오. 
"""
"""
    설계)
    - size = 10, queue = [], def enque(n), def deque(n)
    - front = 0, rear = 0, front는 제거할 위치(index), rear는 삽입할 위치(index)
    - count_size = 0, 사이즈 카운터
    - size만큼 빈 배열 queue 생성
    - def enque
        - 배열이 full이라면 종료
        - q[rear] = n
        - rear +1
        - count_size +1
    - def deque
        - 배열이 비어있다면 종료
        - q[front] = None
        - front위치 맨 앞으로 초기화
        - count_size -1
"""

size = 10
front = 0
rear = 0
count_size = 0
queue = [None]*size

def enque(n):
    global front, rear, count_size
    # case1) 배열이 full이라면 종료
    if (count_size == size):
        return

    # case2) 배열이 가득차지 않았다면 바로 삽입
    queue[rear] = n
    # rear+1 다음 차례에 넣을 데이터를 위해 빈 위치로 이동
    rear = (rear+1)%size
    count_size += 1

def deque():
    global front, rear, count_size
    #case1) 데이터가 비어 있다면 종료
    if (count_size == 0):
        return
    #case2) 제거
    temp_value = queue[front] # 제거할 값 저장
    queue[front] = None # -> deque클래스를 사용하여 popleft로도 구현 가능

    #front를 다음게 꺼낼 위치로 이동
    front = (front+1)%size # 모듈러 연산 방법
    count_size -= 1

    return temp_value
 