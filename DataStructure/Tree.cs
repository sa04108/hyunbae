public class BTreeNode<T>
{
    public T data;
    public BTreeNode<T> left;
    public BTreeNode<T> right;
    public delegate void OnTraverse(T data);
    public BTreeNode(T data)
    {
        this.data = data;
    }

    public void MakeLeft(BTreeNode<T> node)
    {
        left = node;
    }

    public void MakeRight(BTreeNode<T> node)
    {
        right = node;
    }

    public void PreorderTraverse(OnTraverse action)
    {
        action(data);

        if (left != null)
            left.PreorderTraverse(action);

        if (right != null)
            right.PreorderTraverse(action);
    }

    public void InorderTraverse(OnTraverse action)
    {
        if (left != null)
            left.InorderTraverse(action);

        action(data);

        if (right != null)
            right.InorderTraverse(action);
    }

    public void PostorderTraverse(OnTraverse action)
    {
        if (left != null)
            left.PostorderTraverse(action);

        if (right != null)
            right.PostorderTraverse(action);

        action(data);
    }
}