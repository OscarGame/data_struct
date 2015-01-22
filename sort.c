/*
 插入排序属于稳定的排序，时间复杂度为：O(N2)， 空间复杂度：O(1) 
 选择排序属于不稳定的排序，时间复杂度为：O(N2)， 空间复杂度：O(1)
 冒泡排序属于稳定的排序，时间复杂度为：O(N2)， 空间复杂度：O(1)
 希尔排序属于不稳定的排序，时间复杂度为：O(N2)， 空间复杂度：O(1)
 快速排序属于不稳定排序，时间复杂度为：O(N2)， 空间复杂度：O(1)
 */

#include <stdio.h>

#define SIZE 8

void print(int *array, int array_size);

void straight_insert_sort(int *array, int array_size);

void select_sort(int *array, int array_size);

void bubble_sort(int *array, int array_size);

void shells_sort(int *array, int array_size);

void quick_sort(int *array, int start_index, int end_index);

int main(int argc, char **argv)
{
    int array[SIZE] = {3, 5, 1, 8, 4, 6, 7, 2};
    print(array, SIZE);
    //straight_insert_sort(array, SIZE);
    select_sort(array, SIZE);
    //bubble_sort(array, SIZE);
    //shells_sort(array, SIZE);
    //quick_sort(array, 0, SIZE-1);
    print(array, SIZE);
}

void print(int *array, int array_size)
{
    int i;
    for (i=0; i<array_size; i++)
    {
        printf("%d\t", array[i]);
    }
    printf("\n");
}

void straight_insert_sort(int *array, int array_size)
{
    int *tmp = array;
    int i, j, num_to_insert;
    for (i=1; i<array_size; i++)
    {
        num_to_insert = *(tmp+i);
        j = i-1;
        while (j>=0 && num_to_insert<*(tmp+j))
        {
            *(tmp+j+1) = *(tmp+j);
            j--;
        }
        *(tmp+j+1) = num_to_insert;
    }
    return;
}

// 找出array中index在[begin, end]范围内最小元素的index
int scan_for_min(int *array, int begin, int end)
{
    int i;
    int min_index = begin;

    for (i=begin; i<=end; ++i)
    {
        if (array[min_index] > array[i])
        {
            min_index = i;
        }
    }

    return min_index;
}

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void select_sort(int *array, int array_size)
{
    int min_index = 0;
    int i = 0;

    for (i=0; i<array_size; ++i)
    {
        // 找到array[i]~array[array_size-1]中的最小元
        // 记录位置到min_index
        min_index = scan_for_min(array, i, array_size-1);

        // 将上面找到的最小元与已排序部分的最后位置元素互换
        swap(&array[i], &array[min_index]);
    }
}

#define TRUE    1
#define FALSE   0
void bubble_sort(int *array, int array_size)
{
    // 对比相邻的两个元素，如果array[i] > array[i+1]，那么交换位置
    // 然后继续检测下两个相邻元素
    // 如果一次循环中，只有检测，没有交换，那么说明排序已完成
    int tmp;
    int i, j;
    int do_sort = FALSE; //设置标志位，判断是否还需要进行排序
    
    for (i=0; i<array_size-1; i++)
    {
        do_sort = FALSE;
        for (j=0; j<array_size-1-i; j++)
        {
            if (array[j+1] < array[j])
            {
                tmp = array[j];
                array[j] = array[j+1];
                array[j+1] = tmp;
                do_sort = TRUE;
            }
        }
        if (FALSE == do_sort)
        {
            break;
        }
    }
}

void shells_sort(int *array, int array_size)
{
    int tmp, i;
    int gap = array_size/2 + array_size%2;

    while (gap >= 1)
    {
        for (i=0; i+gap < array_size; i++)
        {
            if (array[i] > array[i+gap])
            {
                tmp = array[i];
                array[i] = array[i+gap];
                array[i+gap] = tmp;
            }
        }
        if (1 == gap)
        {
            break;
        }
        gap = gap/2 + gap%2;
    }
}

//array: 要排序的数组
//start_index: 排序起始位置
//end_index: 排序结束位置
void quick_sort(int *array, int start_index, int end_index)
{
    // 序列长度大于1才需要进行排序
    if (start_index < end_index)
    {
        int i = start_index;
        int j = end_index;

        //执行i++操作，直到array[i] >= array[start_index]或者到达序列尾部
        while (array[start_index] >= array[i] && i != end_index)
            i++;

        //执行j--操作，直到array[j] < array[start_index]或者到达序列首部
        while (array[start_index] < array[j] && j != start_index)
            j--;
        if (i < j)
        {
            int tmp = array[i];
            array[i] = array[j];
            array[j] = tmp;
            quick_sort(array, start_index, end_index);
        }
        else
        {
            // 交换后完成一次划分
            int tmp = array[start_index];
            array[start_index] = array[j];
            array[j] = tmp;

            // 对划分左半部分进行排序
            quick_sort(array, start_index, j-1);

            // 对划分右半部分进行排序
            quick_sort(array, j+1, end_index);
        }
    }
}
