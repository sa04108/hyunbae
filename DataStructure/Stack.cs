public class Stack<T>
{
    public int count = 0;
    public Node<T> peek = null;

    public void Push(T data)
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
}