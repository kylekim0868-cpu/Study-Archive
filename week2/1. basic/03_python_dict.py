"""
[파이썬 기본 문법 - 리스트와 딕셔너리 활용]

문제 설명:
- 학생들의 이름과 점수를 입력받아 평균 점수 이상인 학생들을 찾아 출력합니다.
- 파이썬의 기본 자료구조인 리스트와 딕셔너리를 활용하는 문제입니다.

입력:
- students: 학생 정보를 담은 딕셔너리 리스트
  예: [{"name": "Alice", "score": 85}, {"name": "Bob", "score": 92}]

출력:
- 평균 점수
- 평균 이상인 학생들의 이름 리스트

예제:
입력:
[
    {"name": "Alice", "score": 85},
    {"name": "Bob", "score": 92},
    {"name": "Charlie", "score": 78},
    {"name": "David", "score": 95}
]

출력:
평균 점수: 87.5
평균 이상 학생: ['Bob', 'David']


"""

def find_above_average_students(students):
    """
    평균 점수 이상인 학생들을 찾는 함수
    
    Args:
        students: 학생 정보 딕셔너리 리스트
    
    Returns:
        tuple: (평균 점수, 평균 이상 학생 이름 리스트)
    """
    """
        아이디어)
            1) 딕셔너리 자료구조에 대해 얼마나 이해하고 있는지 -> key, value의 쌍으로 이루어진 자료구조
            2) key와 value을 적절하게 활용을 잘했는가에 대한 이해도 테스트
            3) 평균점수 = students 순회하며 점수를 추출 후 합산한 결과 / students의 길이
            4) students 순회하며 조건(평균 점수 >= students.get("score"))에 부합하는 students.get("name")을 리스트에 할당
            5) 리스트를 다시 배열에 담는다?
    """
    n = len(students)
    score_avg = (sum(students[i].get("score") for i in range(n)))/n
    score_avg_students = list(students[i].get("name") for i in range(n) if students[i].get("score") >= score_avg)

    return [score_avg, score_avg_students]

# 테스트 케이스
if __name__ == "__main__":
    # 테스트 케이스 1
    students1 = [
        {"name": "Alice", "score": 85},
        {"name": "Bob", "score": 92},
        {"name": "Charlie", "score": 78},
        {"name": "David", "score": 95}
    ]
    
    avg, students = find_above_average_students(students1)
    print(f"평균 점수: {avg}")
    print(f"평균 이상 학생: {students}")
    print()
    
    # 테스트 케이스 2
    students2 = [
        {"name": "Emma", "score": 70},
        {"name": "Frank", "score": 85},
        {"name": "Grace", "score": 90}
    ]
    
    avg, students = find_above_average_students(students2)
    print(f"평균 점수: {avg}")
    print(f"평균 이상 학생: {students}")


