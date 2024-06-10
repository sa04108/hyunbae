public static class Sort
{
    public static void BubbleSort<T>(this T[] src) where T : IComparable<T>
    {
        for (int i = 0; i < src.Length - 1; i++)
        {
            for (int j = 0; j < src.Length - i - 1; j++)
            {
                if (src[j].CompareTo(src[j + 1]) > 0) // src[j] > src[j + 1]
                {
                    src.Swap(j, j + 1);
                }
            }
        }
    }

    public static void SelectionSort<T>(this T[] src) where T : IComparable<T>
    {
        for (int i = 0; i < src.Length; i++)
        { 
            int min = i;
            for (int j = i; j < src.Length; j++)
            {
                if (src[min].CompareTo(src[j]) > 0)
                {
                    min = j;
                }
            }
            src.Swap(i, min);
        }
    }

    public static void InsertionSort<T>(this T[] src) where T : IComparable<T>
    {
        for (int i = 1; i < src.Length; i++)
        {
            for (int j = i; j > 0; j--)
            {
                if (src[j].CompareTo(src[j - 1]) < 0)
                {
                    src.Swap(j, j - 1);
                }
                else
                {
                    break;
                }
            }
        }
    }

    public static void HeapSort<T>(this T[] src) where T : IComparable<T>
    {
        var heap = new Heap<T>(src.Length + 1);
        for (int i = 0; i < src.Length; i++)
        {
            heap.Insert(src[i]);
        }
        for (int i = 0; i < src.Length; i++)
        {
            src[i] = heap.Delete();
        }
    }

    public static void MergeSort<T>(this T[] src) where T : IComparable<T>
    {
        T[] tmpArr = new T[src.Length];
        DivideAndMerge(0, src.Length - 1);

        void DivideAndMerge(int left, int right)
        {
            if (left < right)
            {
                int mid = (left + right) / 2;

                DivideAndMerge(left, mid);
                DivideAndMerge(mid + 1, right);

                Merge(left, mid, right);
            }
        }

        void Merge(int left, int mid, int right)
        {
            int fIdx = left;
            int rIdx = mid + 1;

            int sIdx = left;

            while (fIdx <= mid && rIdx <= right)
            {
                if (src[fIdx].CompareTo(src[rIdx]) <= 0)
                    tmpArr[sIdx] = src[fIdx++];
                else
                    tmpArr[sIdx] = src[rIdx++];

                sIdx++;
            }

            // 한 쪽 데이터셋이 전부 정렬된 이후 나머지 데이터셋의 남은 데이터들을 순차적으로 입력
            if (fIdx > mid)
            {
                for (int i = rIdx; i <= right; i++, sIdx++)
                    tmpArr[sIdx] = src[i];
            }
            else
                for (int i = fIdx; i <= mid; i++, sIdx++)
                    tmpArr[sIdx] = src[i];

            for (int i = left; i <= right; i++)
                src[i] = tmpArr[i];
        }
    }

    public static void QuickSort<T>(this T[] src) where T : IComparable<T>
    {
        Divide(0, src.Length - 1);

        void Divide(int left, int right)
        {
            if (left <= right)
            {
                int pivot = Partition(left, right);
                Divide(left, pivot - 1);
                Divide(pivot + 1, right);
            }
        }

        int Partition(int left, int right)
        {
            T pivot = src[left];
            int low = left + 1;
            int high = right;

            while (low <= high)
            {
                while (low < src.Length && pivot.CompareTo(src[low]) >= 0 && low <= right)
                    low++;
                while (high > 0 && pivot.CompareTo(src[high]) <= 0 && high >= left + 1)
                    high--;
                
                if (low <= high)
                    src.Swap(low, high);
            }

            src.Swap(left, high);
            return high;
        }
    }

    public static void RadixSort(this int[] src)
    {
        ListQueue<int>[] buckets = new ListQueue<int>[10];
        for (int i = 0; i < buckets.Length; i++)
            buckets[i] = new ListQueue<int>();
            
        int maxLen = MaxLen();
        int divfac = 1;

        for (int i = 0; i < maxLen; i++)
        {
            foreach (int val in src)
            {
                int radix = (val / divfac) % 10;
                buckets[radix].Enqueue(val);
            }

            int di = 0;
            for (int j = 0; j < 10; j++)
            {
                while (!buckets[j].IsQueueEmpty())
                    src[di++] = buckets[j].Dequeue();
            }

            divfac *= 10;
        }

        int MaxLen() => src.Max().ToString().Length;
    }

    public static void Swap<T>(this T[] src, int a, int b)
    {
        if (a == b)
            return;

        var tmp = src[a];
        src[a] = src[b];
        src[b] = tmp;
    }

    public static int MinIndex<T>(this T[] src, int a, int b) where T : IComparable<T>
    {
        if (src[a].CompareTo(src[b]) < 0)
            return a;
        else
            return b;
    }

    public static int MaxIndex<T>(this T[] src, int a, int b) where T : IComparable<T>
    {
        if (src[a].CompareTo(src[b]) > 0)
            return a;
        else
            return b;
    }

    public static void Print<T>(this T[] src, int count = 0)
    {
        int lim = count > 0 ? count : src.Length;
        for (int i = 0; i < lim - 1; i++)
        {
            Console.Write($"{src[i]}, ");
        }
        Console.WriteLine($"{src[lim - 1]}");
    }
}