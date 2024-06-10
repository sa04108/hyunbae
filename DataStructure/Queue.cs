// 배열 기반 원형 큐
public class CircularQueue<T>
{
    public int front = 0;
    public int rear = 0;
    T[] queueArray;
    public int count = 0;

    public CircularQueue(int capacity)
    {
        queueArray = new T[capacity];
    }

    public bool IsQueueEmpty()
    {
        return front == rear;
    }

    public bool IsQueueFull()
    {
        return (rear + 1) % queueArray.Length == front;
    }

    public T Peek()
    {
        if (IsQueueEmpty())
        {
            Console.WriteLine("Queue is Empty");
            return default;
        }

        return queueArray[(front + 1) % queueArray.Length];
    }

    public void Enqueue(T data)
    {
        if (IsQueueFull())
        {
            Console.WriteLine("Queue is Full");
            return;
        }

        rear = (rear + 1) % queueArray.Length;
        queueArray[rear] = data;
        count++;
    }

    public T Dequeue()
    {
        if (IsQueueEmpty())
        {
            Console.WriteLine("Queue is Empty");
            return default;
        }

        front = (front + 1) % queueArray.Length;
        count--;
        return queueArray[front];
    }

    public void Print()
    {
        int cur = (front + 1) % queueArray.Length;
        while (cur != rear)
        {
            Console.Write("{0}, ", queueArray[cur]);
            cur = (cur + 1) % queueArray.Length;
        }
        Console.WriteLine("{0}", queueArray[rear]);
    }
}

// 연결리스트 기반 큐
public class ListQueue<T>
{
    public Node<T> front = null;
    public Node<T> rear = null;
    public int count = 0;

    public bool IsQueueEmpty()
    {
        return front == null;
    }

    public T Peek()
    {
        if (IsQueueEmpty())
        {
            Console.WriteLine("Queue is Empty");
            return default;
        }

        return front.data;
    }

    public void Enqueue(T data)
    {
        var node= new Node<T>(data);
        if (IsQueueEmpty())
            front = node;
        else
            rear.next = node;
            
        rear = node;
        count++;
    }

    public T Dequeue()
    {
        if (IsQueueEmpty())
        {
            Console.WriteLine("Queue is Empty");
            return default;
        }

        var data = front.data;
        front = front.next;

        if (front == null)
            rear = null;
        
        return data;
    }

    public void Print()
    {
        var cur = front;
        while (cur != null)
        {
            Console.Write("{0}, ", cur.data);
            cur = cur.next;
        }
    }
}