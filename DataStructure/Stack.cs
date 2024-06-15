public class Stack<T>
{
    public int count { get; protected set; }
    protected Node<T> peek;

    public T Peek()
    {
        if (count == 0)
        {
            Console.WriteLine("Stack is empty");
            return default;
        }

        return peek.data;
    }

    public virtual void Push(T data)
    {
        Node<T> node = new Node<T>(data);
        if (peek != null)
        {
            peek.next = node;
            node.prev = peek;
        }
        peek = node;
        count++;
    }

    public virtual T Pop()
    {
        if (peek != null)
        {
            var tmp = peek;
            peek = peek.prev;
            count--;
            return tmp.data;
        }
        return default;
    }

    public void Clear()
    {
        peek = null;
        count = 0;
    }
}

public class LimitedStack<T> : Stack<T>
{
    int limitCount;
    Node<T> bottom;

    public LimitedStack(int limitCount)
    {
        this.limitCount = limitCount;
    }

    public override void Push(T data)
    {
        if (count >= limitCount)
        {
            bottom = bottom.next;
            bottom.prev = null;
            count--;
        }

        base.Push(data);

        if (bottom == null)
            bottom = peek;
    }

    public override T Pop()
    {
        var data = base.Pop();
        
        if (count == 0)
            bottom = null;

        return data;
    }
}

public class UndoRedoHistory<T>
{
    const int DefaultUndoCount = 10;
    Stack<T> undoStack;
    Stack<T> redoStack;

    public UndoRedoHistory() : this(DefaultUndoCount) { }

    public UndoRedoHistory(int defaultUndoCount)
    {
        undoStack = new LimitedStack<T>(defaultUndoCount);
        redoStack = new LimitedStack<T>(defaultUndoCount);
    }

    // Ctrl + Z
    public T Undo()
    {
        if (undoStack.count <= 1)
        {
            Console.WriteLine("Undo Stack is empty");

            if (undoStack.count > 0)
                return undoStack.Peek();
            else
                return default;
        }

        T state = undoStack.Pop();
        redoStack.Push(state);
        return undoStack.Peek();
    }

    // Ctrl + Y
    public T Redo()
    {
        if (redoStack.count == 0)
        {
            Console.WriteLine("Redo Stack is empty");

            if (undoStack.count > 0)
                return undoStack.Peek();
            else
                return default;
        }

        T state = redoStack.Pop();
        undoStack.Push(state);
        return state;
    }

    // Remember: peek of undo stack is always current state
    public void AddState(T state)
    {
        undoStack.Push(state);
        redoStack.Clear();
    }

    public void ClearState()
    {
        undoStack.Clear();
        redoStack.Clear();
    }

    public void Run(T[] arr)
    {
        int i = 0;
        while (true)
        {
            var keyInfo = Console.ReadKey(intercept: true); // 입력받은 키를 화면에 표시하지 않음
            char keyChar = keyInfo.KeyChar;

            if (keyChar == 'a')
            {
                Console.WriteLine($"{Undo()}");
            }
            else if (keyChar == 's')
            {
                if (i < arr.Length)
                {
                    AddState(arr[i]);
                    Console.WriteLine($"{arr[i++]}");
                }
            }
            else if (keyChar == 'd')
            {
                Console.WriteLine($"{Redo()}");
            }
            else if (keyInfo.Key == ConsoleKey.Escape)
            {
                break;
            }
        }
    }
}