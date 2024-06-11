public class Stack<T>
{
    public int count { get; private set; }
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
        }

        base.Push(data);

        if (bottom == null)
            bottom = peek;

        Console.Write($"push count: {count} / ");
    }

    public override T Pop()
    {
        var data = base.Pop();
        
        if (count == 0)
            bottom = null;

        Console.Write($"pop count: {count} / ");

        return data;
    }
}