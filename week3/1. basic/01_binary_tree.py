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
        - 기준 노드를 기준으로 왼쪽/오른쪽 방향 설정
        - node = None: 종료하고 이전 노드로 이동
        - 그러면 result에 언제 append()?
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
    node = root

    # 종료 지점
    if node == None:
        return []
    
    left_pre = preorder(node.left) # 왼쪽 노드 재귀
    right_pre = preorder(node.right) # 오른쪽 노드 재귀
 
    result = [node.value]+ left_pre + right_pre

    return result

def inorder(root):
    """중위 순회: 왼쪽 → 루트 → 오른쪽"""
    result = []
    node = root
    
    # 종료 지점
    if node == None:
        return []
        
    left_pre = inorder(node.left) # 왼쪽 노드 재귀
    right_pre = inorder(node.right) # 오른쪽 노드 재귀
    
    result = left_pre + [node.value] + right_pre
    
    return result

def postorder(root):
    """후위 순회: 왼쪽 → 오른쪽 → 루트"""
    result = []
    node = root
    
    # 종료 지점
    if node == None:
        return []
        
    left_pre = postorder(node.left) # 왼쪽 노드 재귀
    right_pre = postorder(node.right) # 오른쪽 노드 재귀

    result = left_pre + right_pre + [node.value]
       
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

