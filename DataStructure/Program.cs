public class Program
{
    public static void Main(string[] args)
    {
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

        int[] nums = Enumerable.Range(1, 100).ToArray();

        int i = 0;
        UndoRedoHistory<int> history = new UndoRedoHistory<int>(3);
        while (true)
        {
            var key = Console.ReadKey(intercept: true); // 입력받은 키를 화면에 표시하지 않음
            char keyChar = key.KeyChar;

            if (keyChar == 'a')
            {
                Console.WriteLine($"{history.Undo()}");
            }
            else if (keyChar == 's')
            {
                if (i < nums.Length)
                {
                    history.AddState(nums[i]);
                    Console.WriteLine($"{nums[i++]}");
                }
            }
            else if (keyChar == 'd')
            {
                Console.WriteLine($"{history.Redo()}");
            }
        }
    }
}
