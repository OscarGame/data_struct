
// 伪码实现, 时间复杂度O(N)
// n个结点的判定树的深度为logn + 1，每个结点的查找次数不会超过判定树的深度

int binary_search(static_table *tbl, element_type k)
{
    int left, right, mid, not_found = -1;

    left = 1;
    right = tbl->length;

    while (left <= right)
    {
        mid = (left + right) / 2;
        if (k < tbl->element[mid])
        {
            right = mid - 1;
        }
        else if (k > tbl->element[mid])
        {
            left = mid + 1;
        }
        else
        {
            return mid;
        }
    }

    return not_found;
}
