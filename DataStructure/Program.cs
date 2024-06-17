public class Program
{
    public static void Main(string[] args)
    {
        #region Sort
        // var queue = new ListQueue<int>();
        // queue.Enqueue(1);
        // Console.WriteLine("Dequeue: {0}", queue.Dequeue());
        // Console.WriteLine("Dequeue: {0}", queue.Dequeue());
        // queue.Enqueue(2);
        // queue.Enqueue(3);
        // queue.Enqueue(4);
        // queue.Dequeue();
        // queue.Dequeue();
        // queue.Enqueue(5);
        // queue.Enqueue(6);
        // queue.Print();
        // Console.WriteLine("Peek: {0}", queue.Peek());
        
        // int[] nums = { 8, 15, 3, 1, 4, 7, 12, 9, 13 };
        // int[] nums = { 1, 1, 1, 1, 1, 1, 1, 1, 1 };
        // int[] nums = { 13, 212, 14, 7141, 10987, 6, 15};
        // nums.RadixSort();
        // nums.Print();

        // int[] nums = Enumerable.Range(1, 100).ToArray();
        // var history = new UndoRedoHistory<int>();
        // history.Run(nums);
        #endregion

        #region BTree
        // var node1 = new BTreeNode<int>(1);
        // var node2 = new BTreeNode<int>(2);
        // var node3 = new BTreeNode<int>(3);
        // var node4 = new BTreeNode<int>(4);
        // var node5 = new BTreeNode<int>(5);
        // var node6 = new BTreeNode<int>(6);

        // node1.MakeLeft(node2);
        // node1.MakeRight(node3);
        // node2.MakeLeft(node4);
        // node2.MakeRight(node5);
        // node3.MakeLeft(node6);
        
        // node1.PostorderTraverse((data) => {
        //     Console.Write($"{data}, ");
        // });

        // var calculator = new Calculator();
        // var expRoot = calculator.MakeExpTree("12+7*");
        // Console.WriteLine(calculator.EvalExpTree(expRoot));
        #endregion

        var root = new BSTNode(10);
        root.BSTInsert(1);
        root.BSTInsert(5);
        root.BSTInsert(4);
        root.BSTInsert(13);
        root.BSTInsert(17);
        root.BSTInsert(12);

        root.BSTRemove(10);
        root.PreorderTraverse((data) =>
        {
            Console.Write($"{data}, ");
        });
    }
}
