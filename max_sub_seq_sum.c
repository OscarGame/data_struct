/*
 给定N个整数的序列{a1, a2, ..., an}, 求最大子列和
 */
#include <stdio.h>

// 在线处理算法
// 每输入一个数据就进行即时处理，在任何一个地方中止输入，算法都能正确给出当前的解
int max_sub_seq_sum(int *array, int array_size)
{
    int cursum = 0;
    int maxsum = 0;
    int i = 0;

    for (i=0; i<array_size; ++i)
    {
        cursum += array[i]; // 向右累加
        if (cursum > maxsum)
        {
            maxsum = cursum; // 发现更大和，则更新maxsum
        }
        else if (cursum < 0) // 当前子列和为负
        {
            cursum = 0; // 不可能使后面的部分和增大，抛弃之
        }
    }

    return maxsum;
}

int main(int argc, char **argv)
{
    int a[] = {-1, 3, -2, 4, -6, 1, 6, -1};

    int maxsum = max_sub_seq_sum(a, sizeof(a)/sizeof(int));
    printf("maxsum=%d\n", maxsum);

    return 0;
}
