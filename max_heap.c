
typedef struct _heap_struct
{
    element_type *m_elements; // 存储堆元素的数组
    int m_size; // 堆的当前元素个数
    int m_capaticy; // 堆的最大容量
} heap_struct, *ptr_max_heap;

ptr_max_heap create(int max_size)
{
    ptr_max_heap h = (ptr_max_heap)malloc(sizeof(heap_struct));
    h->m_elements = (element_type *)malloc((max_size+1) * sizeof(element_type));
    h->m_size = 0;
    h->m_capaticy = max_size;
    h->m_elements[0] = MAX_DATA; // 定义哨兵为大于堆中所有可能元素的值，便于以后更快操作

    return h;
}

// 时间复杂度O(logN)
void insert(ptr_max_heap h, element_type item)
{
    // 将元素item插入最大堆h，其中h->m_elements[0]已经被定义为哨兵
    int i;
    if (is_full(h))
    {
        printf("最大堆已满");
        return;
    }

    i = ++h->m_size; // i指向插入后堆中的最后一个元素的位置
    for (; h->m_elements[i/2] < item; i /= 2) // i/2指向i结点的父节点
    {
        h->m_elements[i] = h->m_elements[i/2]; // 向下过滤结点
    }
    h->m_elements[i] = item; // 插入item
}

// 取出根结点（最大值）元素，同时删除堆的一个结点
// 时间复杂度O(logN)
element_type delete_max(ptr_max_heap h)
{
    // 从最大堆h中取出键值最大的元素，并删除一个结点
    int parent, child;
    element_type max_item, temp;

    if (is_empty(h))
    {
        printf("最大堆已经为空");
        return;
    }

    max_item = h->m_elements[1]; // 取出根结点，最大值

    temp = h->m_elements[h->m_size--]; // 用最大堆中最后一个元素从根结点开始向上过滤下层结点

    // parent*2 <= h->m_size, 说明parent结点有lchild
    for (parent = 1; parent*2 <= h->m_size; parent = child)
    {
        child = parent * 2;
        if (child != h->m_size && h->m_elements[child] < h->m_elements[child+1])
        {
            child++; // child指向左右子结点中的较大者
        }
        if (temp >= h->m_elements[child])
        {
            break;
        }
        else
        {
            // 移动temp元素到下一层
            h->m_elements[parent] = h->m_elements[child];
        }
    }
    h->m_elements[parent] temp;

    return max_item;
}

