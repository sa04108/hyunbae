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
}