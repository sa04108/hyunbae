using System.ComponentModel.DataAnnotations;

public class Heap<T> where T : IComparable<T> // Min Heap
{
    T[] heapArray;
    public int count = 0;

    public Heap(int capacity)
    {
        heapArray = new T[capacity];
    }

    public void Insert(T data)
    {
        if (count >= heapArray.Length)
        {
            Console.WriteLine("Heap is full");
            return;
        }

        heapArray[++count] = data;

        int child = count;
        int parent = count / 2;
        while (parent > 0)
        {
            if (heapArray[parent].CompareTo(heapArray[child]) <= 0)
                break;

            heapArray.Swap(parent, child);

            child = parent;
            parent = parent / 2;
        }
    }

    public T Delete()
    {
        if (count == 0)
        {
            Console.WriteLine("Heap is empty");
            return default;
        }

        var data = heapArray[1];
        heapArray[1] = heapArray[count--];

        int lchild = 2;
        int parent = 1;
        while (lchild <= count)
        {
            int minChild = lchild < count ? heapArray.MinIndex(lchild, lchild + 1) : lchild;
            if (heapArray[parent].CompareTo(heapArray[minChild]) <= 0)
                break;

            heapArray.Swap(parent, minChild);

            parent = minChild;
            lchild = parent * 2;
        }

        return data;
    }

    public void Print()
    {
        for (int i = 1; i < count; i++)
        {
            Console.Write($"{heapArray[i]}, ");
        }
        Console.WriteLine($"{heapArray[count]}");
    }
}