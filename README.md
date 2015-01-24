data_struct
===

由于不是计算机科班出身，自从变成一名coder，数据结构和算法一直是自己的弱项，知道了自己的弱项，当然剩下的就是勤加学习和练习。
在网上会经常发现一些数据结构的很神奇的实现，自己学习工作过程中为了练手也会在此留下痕迹，

```
├── binary_search.c
├── bin_tree.c
├── list
│   ├── list.c
│   ├── list.h
│   ├── makefile
│   └── ut_list.c
├── max_heap.c
├── max_sub_seq_sum.c
├── README.md
└── sort.c
```

1. [linux循环链表学习](http://blog.csdn.net/wzzfeitian/article/details/7816614)，这是之前在csdn写的博客，记录了该实现的一些想法 ./list/
2. redis里面各种数据结构的实现
3. 最大子列和问题，./max_sub_seq_sum.c中使用在线处理算法，时间复杂度为O(N)
4. 二叉树伪代码实现 ./bin_tree.c，简单描述了二叉树的常用操作
5. 二叉搜索树的简单操作伪代码实现 ./bin_tree.c
6. 二分查找伪代码实现 ./binary_search.c
7. 最大堆伪代码实现 ./max_heap.c


#####排序算法

稳定性：任意两个相等的数据，排序前后的相对位置不发生改变

|排序算法|是否稳定|时间复杂度|空间复杂度|
|:-------|:-------|:---------|:---------|
|插入排序|稳定    |O(N2)     |O(1)      |
|选择排序|不稳定  |O(N2)     |O(1)      |
|冒泡排序|稳定    |O(N2)     |O(1)      |
|希尔排序|不稳定  |O(N2)     |O(1)      |
|快速排序|不稳定  |O(N2)     |O(1)      |
|归并排序|稳定    |O(NlogN)  |O(N)      |

