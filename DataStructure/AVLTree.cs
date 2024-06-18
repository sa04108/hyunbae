public partial class BSTNode
{
    private int GetHeight(BSTNode node)
    {
        int leftH;
        int rightH;

        if (node == null)
            return 0;
        
        leftH = GetHeight(node.left);
        rightH = GetHeight(node.right);

        if (leftH > rightH)
            return leftH + 1;
        else
            return rightH + 1;
    }

    private int GetHeightDiff(BSTNode node)
    {
        if (node == null)
            return 0;
        
        int lsh = GetHeight(node.left); // left sub tree height
        int rsh = GetHeight(node.right); // right sub tree height
        return lsh - rsh;
    }

    private BSTNode RotateLL(BSTNode node)
    {
        var pNode = node;
        var cNode = node.left;

        pNode.left = cNode.right;
        cNode.right = pNode;

        return cNode;
    }

    private BSTNode RotateRR(BSTNode node)
    {
        var pNode = node;
        var cNode = node.right;

        pNode.right = cNode.left;
        cNode.left = pNode;

        return cNode;
    }

    // RR -> LL
    private BSTNode RotateLR(BSTNode node)
    {
        var pNode = node;
        var cNode = node.left;

        pNode.left = RotateRR(cNode);
        return RotateLL(pNode);
    }

    // LL -> RR
    private BSTNode RotateRL(BSTNode node)
    {
        var pNode = node;
        var cNode = node.right;

        pNode.right = RotateLL(cNode);
        return RotateRR(pNode);
    }

    public BSTNode Rebalance()
    {
        int hDiff = GetHeightDiff(this);

        // 균형 인수가 2 이상이면 LL 또는 LR 상태이다.
        if (hDiff > 1)
        {
            if (GetHeightDiff(left) > 0)
                return RotateLL(this);
            else
                return RotateLR(this);
        }
        // 균형 인수가 -2 이하이면 RR 또는 RL 상태이다.
        if (hDiff < -1)
        {
            if (GetHeightDiff(right) < 0)
                return RotateRR(this);
            else
                return RotateRL(this);
        }

        return this;
    }
}