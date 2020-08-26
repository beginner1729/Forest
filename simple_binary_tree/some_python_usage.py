import BinaryTree as bt

o = bt.IntBinaryClass(0)
head = None

head = o.enter_graph(head,12)
head = o.enter_graph(head,3)
head = o.enter_graph(head,21)
head = o.enter_graph(head,15)
head = o.enter_graph(head,8)
head = o.enter_graph(head,9)
head = o.enter_graph(head,4)
head = o.enter_graph(head,11)

head.traverse_graph()
if head.is_present(15):
    print("Found 15")
if head.delete_key(4):
    print("Deleted key 4")
print("After deletion")
head.traverse_graph()
head.clear_tree()
head.traverse_graph()
del(head)
del(o)
