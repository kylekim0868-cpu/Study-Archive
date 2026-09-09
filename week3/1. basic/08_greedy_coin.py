"""
[그리디 알고리즘 - 거스름돈]

문제 설명:
- 그리디(Greedy) 알고리즘으로 거스름돈을 계산합니다.
- 가장 큰 단위의 동전부터 사용하여 최소 개수로 거슬러줍니다.
- 매 순간 최선의 선택(가장 큰 동전)을 합니다.

입력:
- change: 거슬러줄 금액
- coins: 사용 가능한 동전 종류 (예: [500, 100, 50, 10])

출력:
- 필요한 동전의 개수
- 각 동전의 사용 개수

예제:
입력: change = 1260, coins = [500, 100, 50, 10]
출력:
500원: 2개
100원: 2개
50원: 1개
10원: 1개
총 6개
"""

def make_change_greedy(change, coins):
    """
    그리디 알고리즘으로 거스름돈 계산
    
    Args:
        change: 거슬러줄 금액
        coins: 동전 종류 리스트 (큰 순서)
    
    Returns:
        (총 개수, {동전: 개수} 딕셔너리)
    """
    # 딕셔너리 생성 - 거스를 경우의 수를 담은 동전의 종류와 갯수
    result = {}
    # 동전 개수 count
    count = 0
    # 총 사용된 동전 개수 count
    total = 0

    # 동전 종류 순회 (500원일 때, 100원일 때, 50원일 때, 10원일 때..)
    for coin in coins:
        # 거스름돈을 나눈 몫 = 동전 사용 수
        count = change//coin

        # 동전 사용 수와 동전 종류를 result에 담기
        if count != 0:
            result[coin] = count

        change -= (coin*count)

        total += count

        # 거슬러줄 금액//동전 종류 중 하나 == 0 -> (전부 거슬러줬다는 이야기 = 더 이상의 동전을 사용X)
        if (change%coin) == 0:
            count = change//coin
            total += count
            break

    return total, result

# 테스트 케이스
if __name__ == "__main__":
    # 테스트 케이스 1
    change1 = 1260
    coins1 = [500, 100, 50, 10]
    total, details = make_change_greedy(change1, coins1)
    
    print("=== 거스름돈 계산 ===")
    print(f"거슬러줄 금액: {change1}원")
    for coin, count in details.items():
        print(f"{coin}원: {count}개")
    print(f"총 {total}개")
    print()
    
    # 테스트 케이스 2
    change2 = 4570
    coins2 = [500, 100, 50, 10]
    total, details = make_change_greedy(change2, coins2)
    
    print("=== 거스름돈 계산 ===")
    print(f"거슬러줄 금액: {change2}원")
    for coin, count in details.items():
        print(f"{coin}원: {count}개")
    print(f"총 {total}개")
    print()
    
    # 테스트 케이스 3
    change3 = 1000
    coins3 = [500, 100, 50, 10]
    total, details = make_change_greedy(change3, coins3)
    
    print("=== 거스름돈 계산 ===")
    print(f"거슬러줄 금액: {change3}원")
    for coin, count in details.items():
        print(f"{coin}원: {count}개")
    print(f"총 {total}개")


