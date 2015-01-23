

typedef struct _tree_node
{
    element_type m_data;
    struct _tree_node *m_left;
    struct _tree_node *m_right;
} tree_node;


// 递归实现先序遍历, root, m_left, m_right
void preorder_traversal(tree_node *bt)
{
    if (bt)
    {
        printf("%d", bt->data);
        preorder_traversal(bt->m_left);
        preorder_traversal(bt->m_right);
    }
}

// 递归实现中序遍历, m_left, root, m_right
void inorder_traversal(tree_node *bt)
{
    if (bt)
    {
        inorder_traversal(bt->m_left);
        printf("%d", bt->data);
        inorder_traversal(bt->m_right);
    }
}

// 递归实现后序遍历, m_left, m_right, root
void postorder_traversal(tree_node *bt)
{
    if (bt)
    {
        postorder_traversal(bt->m_left);
        postorder_traversal(bt->m_right);
        printf("%d", bt->data);
    }
}


// 非递归实现中序遍历，使用堆栈
// 1. 遇到一个结点，就把它压栈，并去遍历它的左子树；
// 2. 当左子树遍历结束后，从栈顶弹出这个结点，并访问它
// 3. 然后按其右子树指针(当作root结点)再去中序遍历该节点的右子树
void inorder_traversal_norecurse(tree_node *bt)
{
    tree_node *t = bt;
    stack s = create_stack(MAXSIZE); // 创建并初始化堆栈
    while (t || !is_empty(s))
    {
        while (t) // 一直向左，并将沿途结点压栈
        {
            push(s, t); // 第一次碰到该结点
            t = t->m_left;
        }

        if (!is_empty(s))
        {
            t = pop(s); // 结点出栈，第二次碰到该几点
            printf("%d", t->data); // 访问出栈结点
            t = t->m_right; // 转向右子树
        }
    }
}

void preorder_traversal_norecurse(tree_node *bt)
{
    tree_node *t = bt;
    stack s = create_stack(MAXSIZE); // 创建并初始化堆栈
    while (t || !is_empty(s))
    {
        while (t) // 一直向左，并将沿途结点压栈
        {
            push(s, t); // 第一次碰到该结点
            printf("%d", t->data); // 访问出栈结点
            t = t->m_left;
        }

        if (!is_empty(s))
        {
            t = pop(s); // 结点出栈，第二次碰到该几点
            t = t->m_right; // 转向右子树
        }
    }
}

// 层序遍历
// 1. 先根结点入队
// 2. 从队列中取出一个结点，访问
// 3. 若该结点的左右子树非空，将左右子树指针顺序入队
void levelorder_traversal(tree_node *bt)
{
    queue q;
    tree_node *t = NULL;
    if (!bt) // 若是空树，直接返回
    {
        return;
    }

    q = create_queue(MAXSIZE); // 创建并初始化队列q
    add_q(q, bt);
    while (!is_empty(q))
    {
        t = delete_q(q);
        printf("%d", t->data); // 访问取出队列的结点
        if (t->m_left)
        {
            add_q(q, t->m_left);
        }
        if (t->m_right)
        {
            add_q(q, t->m_right);
        }
    }
}

// 二叉搜索树(二叉查找树, 二叉排序树)
// m_left < root < m_right

position find(element_type x, tree_node *bst)
{
    if (!bst)
    {
        return NULL;
    }

    if (x > bst->data)
    {
        return find(x, bst->m_right);
    }
    else if (x < bst->data)
    {
        return find(x, bst->m_left);
    }
    else
    {
        return bst;
    }
}

// 非递归实现
position iter_find(element_type x, tree_node *bst)
{
    if (!bst)
    {
        return NULL;
    }

    while (bst)
    {
        if (x > bst->data)
        {
            bst = bst->m_right;
        }
        else if (x < bst->data)
        {
            bst = bst->m_left;
        }
        else
        {
            return bst;
        }
    }

    return NULL;
}

// find_min用递归实现
position find_min(tree_node *bst)
{
    if (!bst)
    {
        return NULL;
    }

    if (bst->m_left)
    {
        return find_min(bst->m_left);
    }

    return bst;
}

// find_max用loop实现
position find_max(tree_node *bst)
{
    if (!bst)
    {
        return NULL;
    }

    while (bst->m_right)
    {
        bst = bst->m_right;
    }

    return bst;
}

tree_node *insert(element_type x, tree_node *bst)
{
    if (!bst)
    {
        bst = malloc(sizeof(struct tree_node));
        bst->data = x;
        bst->m_left = bst->m_right = NULL;
    }
    else
    {
        if (x < bst->data)
        {
            bst->m_left = insert(x, bst->m_left);
        }
        else if (x > bst->data)
        {
            bst->m_right = insert(x, bst->m_right);
        }
        // else X已经存在，什么都不做
    }

    return bst;
}

tree_node *delete(element_type x, tree_node *bst)
{
    position tmp;
    if (!bst)
    {
        printf("要删除的元素未找到");
    }
    else if (x < bst->data)
    {
        bst->m_left = delete(x, bst->m_left);
    }
    else if (x > bst->data)
    {
        bst->m_right = delete(x, bst->m_right);
    }
    else // 找到要删除的结点
    {
        if (bst->m_left && bst->m_right)
        {
            tmp = find_min(bst->m_right); // 找到右子树的最小结点（该结点肯定只有0或1个子结点）
            bst->data = tmp->data;
            bst->m_right = delete(bst->data, bst->m_right); // 删除右子树的最小结点
        }
        else // 被删除结点只有0或1个子结点
        {
            tmp = bst;
            if (!bst->m_left)
            {
                bst = bst->m_right;
            }
            else if (!bst->m_right)
            {
                bst = bst->m_left;
            }

            free(tmp);
        }
    }

    return bst;
}


