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

public partial class BSTNode
{
    public int data;
    public BSTNode left;
    public BSTNode right;
    public delegate void OnTraverse(int data);
    public BSTNode(int data)
    {
        this.data = data;
    }

    public void BSTInsert(int data, ref BSTNode newRoot)
    {
        var pNode = this;
        var cNode = this;

        while (cNode != null)
        {
            if (data == cNode.data)
                return;

            pNode = cNode;

            if (data < cNode.data)
                cNode = cNode.left;
            else
                cNode = cNode.right;
        }

        var newNode = new BSTNode(data);
        if (pNode != null)
        {
            if (data < pNode.data)
                pNode.left = newNode;
            else
                pNode.right = newNode;
        }

        newRoot = Rebalance();
    }

    public int BSTRemove(int data, ref BSTNode newRoot)
    {
        // 삭제 대상 노드가 루트 노드인 경우를 감안하여 아래 탐색을 일반화할 수단으로 루트의 부모 노드 생성
        var pNode = new BSTNode(0);
        pNode.right = this;
        var cNode = this;

        while (cNode != null)
        {
            if (data == cNode.data)
                break;

            pNode = cNode;

            if (data < cNode.data)
                cNode = cNode.left;
            else
                cNode = cNode.right;
        }

        if (cNode == null)
            return -1;

        int rData = cNode.data;

        // 삭제 대상 노드가 단말 노드인 경우
        if (cNode.left == null && cNode.right == null)
        {
            // 부모 노드와 연결 해제
            if (pNode.left == cNode)
                pNode.left = null;
            else
                pNode.right = null;
        }
        // 삭제 대상 노드가 자식이 하나인 노드인 경우
        else if (cNode.left == null || cNode.right == null)
        {
            // 자식 노드를 찾아서 삭제할 노드의 부모와 연결
            BSTNode dcNode;

            if (cNode.left != null)
                dcNode = cNode.left;
            else
                dcNode = cNode.right;

            if (pNode.left == cNode)
                pNode.left = dcNode;
            else
                pNode.right = dcNode;
        }
        // 삭제 대상 노드가 두 자식을 모두 가지고 있는 경우 => 실제로는 삭제 대상 노드는 값만 바뀌고 대체 노드가 트리에서 제거된다.
        else
        {
            // 삭제할 노드의 오른쪽 서브 트리에서 가장 작은 노드 탐색 후, 그 노드 주변의 새로운 연결을 형성하고 그 값을 삭제할 노드 위치에 대입
            // (혹은 왼쪽 서브트리에서 가장 큰 노드를 탐색해도 된다.)
            var mPNode = cNode;
            var mNode = cNode.right;

            // 오른쪽 서브 트리에서 가장 작은 노드 탐색
            while (mNode.left != null)
            {
                mPNode = mNode;
                mNode = mNode.left;
            }

            // 그 노드에 저장된 값을 삭제할 노드 위치에 대입
            cNode.data = mNode.data;

            // 찾은 노드의 부모를 찾은 노드의 오른쪽 자식노드와 연결
            // 오른쪽 서브 트리에서 가장 작은 노드를 탐색하면서 왼쪽으로만 탐색했으므로 마지막으로 탐색한 노드가 자식이 있다면 오른쪽 자식일 수 밖에 없다.
            if (mPNode.left == mNode)
                mPNode.left = mNode.right;
            else
                mPNode.right = mNode.right;
        }

        newRoot = Rebalance();
        return rData;
    }

    public BSTNode BSTSearch(int data)
    {
        var cNode = this;

        while (cNode != null)
        {
            if (data == cNode.data)
                return cNode;
            else if (data < cNode.data)
                cNode = cNode.left;
            else
                cNode = cNode.right;
        }

        return null;
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