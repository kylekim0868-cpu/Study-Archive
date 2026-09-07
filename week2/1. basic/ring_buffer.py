"""
    원형큐 구현
    - 문제: 고정 크기 배열(예: 크기 10)만 사용하여, 요소를 이동시키지 않고 O(1)로 삽입/삭제가 가능한 큐를 설계한다면 어떻게 해야할까? 설계 방식을 설명하고 간단하게 파이썬 혹은 수도 코드로 enque, deque 함수를 만들어 보시오. 
"""
"""
    설계)
        1. 크기가 SIZE로 고정된 배열을 생성한다.
        2. front는 다음에 제거할 요소의 위치를 나타낸다.
        3. rear는 다음에 삽입할 위치를 나타낸다.
        4. enqueue
           - rear 위치에 데이터를 저장한다.
           - rear를 다음 위치로 이동한다.
           - 배열의 끝에서는 % SIZE를 사용하여 처음으로 순환한다.
        5. dequeue
           - front 위치의 데이터를 반환한다.
           - front를 다음 위치로 이동한다.
           - 배열의 끝에서는 % SIZE를 사용하여 처음으로 순환한다.
        6. 배열의 요소를 직접 이동시키지 않으므로
           enqueue/dequeue는 O(1)을 유지한다.
"""
size =10
front = 0
rear = 0
count_size = 0 # q에 몇개 쌓았는지 count ? 근데 이미 쌓여있는 데이터는 몇개 인지 어디서 불러오지? 함수를 만들어야하나?
q = [None]*size # size만큼의 배열 생성

def enqueue(value):
    global rear, count_size
    # q가 가득찼다면 return
    if count_size == size:
        return "Queue 가득참"
    # q[rear]에 value를 담는다.
    q[rear] = value
    # rear+1 이유는? 다음 차례에 넣을 데이터를 빈 위치에 위치시켜야하기 때문에
    rear += 1 
    count_size += 1

def dequeue(value):
    global front, count_size
    #데이터가 없다면 return
    #count_size 대신 len(q) ==0은 어떤가? => q의 배열 사이즈 고정이기 때문에
    if count_size == 0: 
        return "Queue에 데이터가 없음"
    # q[front] 제거한다.
    q[front] = None
    # front+1 이유는? 다음에 꺼내질 원소의 인덱스로 한칸 옮겨야하기 때문에
    front += (front+1)%size
    count_size -= 1