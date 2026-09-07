"""
[이진 트리 - Binary Tree 기본]

문제 설명:
- 이진 트리의 기본 구조를 구현합니다.
- 각 노드는 최대 2개의 자식(왼쪽, 오른쪽)을 가집니다.
- 전위, 중위, 후위 순회를 구현합니다.
- 각 노드가 최대 2개의 자식 노드(왼쪽, 오른쪽)를 가질 수 있는 트리 구조.

입력:
- 트리 노드들

출력:
- 전위 순회: 루트 → 왼쪽 → 오른쪽
- 중위 순회: 왼쪽 → 루트 → 오른쪽
- 후위 순회: 왼쪽 → 오른쪽 → 루트

예제:
트리 구조:
      1
     / \
    2   3
   / \
  4   5

전위: [1, 2, 4, 5, 3]
중위: [4, 2, 5, 1, 3]
후위: [4, 5, 2, 3, 1]

힌트:
- 재귀로 간단히 구현 가능
- 순회 순서만 다름                                                                                                                                                                                                                
"""
"""
    설계)
        1) 재귀적 생각 - 왼쪽으로 반복해서 내려가다가 자식 노드가 없다면 다시 올라가서 부모 노드를 만나면 오른쪽 탐색
        2) 종료 지점 - node 자체가 없다면 종료
"""
class TreeNode:
    """이진 트리 노드"""
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None

def preorder(root):
    """전위 순회: 루트 → 왼쪽 → 오른쪽"""
    result = []
    # node 객체 할당 코드 구현 방법을 모르겠네
    node = root
    # base line: node가 비어 있다면 return
    if node == None:
        return [] # "return" 은 None을 반환
    # 현재 node를 result에 담기
    result.append(node.value)
    # 현재 node에서 왼쪽으로 이동
    left_result = preorder(node.left) # 왼쪽으로 이동한 node의 result배열 반환
    # 현재 node에서 오른쪽으로 이동
    right_result = preorder(node.right) # 왼쪽으로 이동한 node의 result배열 반환
    # 
    result = result + left_result + right_result

    return result

def inorder(root):
    """중위 순회: 왼쪽 → 루트 → 오른쪽"""
    result = []
    # node 객체 할당 코드 구현 방법을 모르겠네
    node = root
    # base line: node가 비어 있다면 return
    if node == None:
        return [] # "return" 은 None을 반환
    
    # 현재 node에서 왼쪽으로 이동
    left_result = inorder(node.left) # 왼쪽으로 이동한 node의 result배열 반환
    # 현재 node를 result에 담기
    result.append(node.value)
    # 현재 node에서 오른쪽으로 이동
    right_result = inorder(node.right) # 왼쪽으로 이동한 node의 result배열 반환
    # 
    result = left_result + result + right_result 

    
    return result

def postorder(root):
    """후위 순회: 왼쪽 → 오른쪽 → 루트"""
    result = []
# node 객체 할당 코드 구현 방법을 모르겠네
    node = root
    # base line: node가 비어 있다면 return
    if node == None:
        return [] # "return" 은 None을 반환
    
    # 현재 node에서 왼쪽으로 이동
    left_result = postorder(node.left) # 왼쪽으로 이동한 node의 result배열 반환
    # 현재 node에서 오른쪽으로 이동
    right_result = postorder(node.right) # 왼쪽으로 이동한 node의 result배열 반환
    # 현재 node를 result에 담기
    result.append(node.value)
    # 
    result = left_result + right_result + result   
   
    return result

# 테스트 케이스
if __name__ == "__main__":
    # 트리 생성:
    #       1
    #      / \
    #     2   3
    #    / \
    #   4   5
    root = TreeNode(1)
    root.left = TreeNode(2)
    root.right = TreeNode(3)
    root.left.left = TreeNode(4)
    root.left.right = TreeNode(5)
    
    print("=== 이진 트리 순회 ===")
    print(f"전위 순회: {preorder(root)}")
    print(f"중위 순회: {inorder(root)}")
    print(f"후위 순회: {postorder(root)}")

