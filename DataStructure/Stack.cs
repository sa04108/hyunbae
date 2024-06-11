public class Stack<T>
{
    public int count = 0;
    public Node<T> peek;

    public virtual void Push(T data)
    {
        Node<T> node = new Node<T>(data);
        if (peek != null)
        {
            node.prev = peek;
        }
        peek = node;
        count++;
    }

    public T Pop()
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
    public int limitCount;

    public LimitedStack(int limitCount)
    {
        this.limitCount = limitCount;
    }

    public override void Push(T data)
    {
        if (count >= limitCount)
        {
            Console.WriteLine("Stack is full");
            return;
        }

        base.Push(data);
    }
}