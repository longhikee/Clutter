class TreeNode:
  def __init__(self, x):
    self.val = x
    self.left = None
    self.right = None
    
class Solution:
  def preorderTraversal(self, root):
    """
    :type root: TreeNode
    :rtype: List[int]
    """
    orderlist = []
    rlist = []
    node = root
    while True:
      while node is not None:
        orderlist.append(node.val)
        if node.right is not None:
          rlist.append(node.right)
        node = node.left
        
      if len(rlist)  == 0:
        break
      node = rlist.pop()
      
    return orderlist

  def inorderTraversal(self, root):
    orderlist = []
    ilist = []
    node = root
    while True:
      while node is not None:
        ilist.append(node)
        node = node.left
       
      if len(ilist) == 0:
          break
 
      node = ilist.pop()
      orderlist.append(node.val)
      node = node.right

    return orderlist

  def postorderTraversal(self, root):
    orderlist = []
    plist = []
    plist.append(root)
    while len(plist) != 0:
      node = plist.pop(0);
      if node is None:
        continue
      orderlist.append(node.val)
      
      if node.right is not None:
        plist.append(node.right)
      if node.left is not None:
        plist.append(node.left)

    orderlist.reverse()
    return orderlist


  def levelorderTraversal(self, root):
    orderlist = []
    llist = []
    node = root

    while True:
      orderlist.append(node.val)
      if node.right is not None:
        llist.append(node.right)
      if node.left is not None:
        llist.append(node.left)

      if len(llist) == 0:
        break
      node = llist.pop()
      
    return orderlist

                
tr1 = TreeNode(1)
tr2 = TreeNode(2)
tr3 = TreeNode(3)

#tr0 = TreeNode(0)
#tr1.left = tr0

tr1.right = tr2
tr2.left = tr3
 
#input [1, null, 2, 3]
#preorder: [1, 2, 3]
#Inorder: [1 3, 2]
#postorder: [3,  2, 1]

#input [3, 9, 20, null, null, 15, 7]
tree1 = TreeNode(3)
tree2 = TreeNode(9)
tree3 = TreeNode(20)
tree4 = TreeNode(15)
tree5 = TreeNode(7)

tree1.left = tree2
tree1.right = tree3
tree3.left = tree4
tree3.right = tree5

def main():
  s = Solution()
  orderlist = s.preorderTraversal(tr1)
  print("preoder:", end=' ')
  for i in orderlist:
    print(i, end=' ')
  print('\n')

  orderlist = s.inorderTraversal(tr1)
  print("inorder:", end=' ')
  for i in orderlist:
    print(i, end=' ')
  print('\n')

  orderlist = s.postorderTraversal(tr1)
  print("postorder:", end=' ')
  for i in orderlist:
    print(i, end=' ')
  print('\n')
  orderlist = s.levelorderTraversal(tr1)
  print("levelorder:", end=' ')
  for i in orderlist:
    print(i, end=' ')
  print('\n')
  print("#######################")
##############################################
  orderlist = s.preorderTraversal(tree1)
  print("preoder:", end=' ')
  for i in orderlist:
    print(i, end=' ')
  print('\n')

  orderlist = s.inorderTraversal(tree1)
  print("inorder:", end=' ')
  for i in orderlist:
    print(i, end=' ')
  print('\n')

  orderlist = s.postorderTraversal(tree1)
  print("postorder:", end=' ')
  for i in orderlist:
    print(i, end=' ')
  print('\n')

  orderlist = s.levelorderTraversal(tree1)
  print("levelorder:", end=' ')
  for i in orderlist:
    print(i, end=' ')
  print('\n')

main()
