#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "list.h"

typedef struct _data
{
	int version;
	char str[20];
	struct list_head list;
}data;



int NODE_NUM =	5;

int main(void)
{
	data *pdata = NULL, *pdata2 = NULL;
	data *tmp_data = NULL;
	struct list_head data_list, data_list2;
	struct list_head *pos = NULL, *n = NULL;
	int i = 0;

	list_init(&data_list);
	list_init(&data_list2);

	pdata = (data *)malloc(sizeof(data) * 5);
	if (pdata == NULL)
	{
		printf("malloc for pdata error\n");
		return -1;
	}

	pdata2 = (data *)malloc(sizeof(data) * 5);
	if (pdata2 == NULL)
	{
		printf("malloc for pdata2 error\n");
		return -1;
	}

	memset(pdata, 0, sizeof(data));
	memset(pdata2, 0, sizeof(data));
	for (i = 0; i < NODE_NUM; i++)
	{
		sprintf(pdata[i].str, "version%d", i+1);
		sprintf(pdata2[i].str, "version%d", i+4);
		pdata[i].version = i+1;
		pdata2[i].version = i+4;
		list_add(&(pdata[i].list), &data_list);
		list_add(&(pdata2[i].list), &data_list2);
	}

	printf("data_list 链表\n");
	list_for_each_entry(tmp_data, &data_list, list)
	{
		printf("version: %d, \tversion str: %s\n", tmp_data->version, tmp_data->str);
	}

	printf("data_list2 链表\n");
	for(pos = LIST_HEAD(&data_list2); pos != LIST_END(&data_list2); pos = NEXT_NODE(pos))
	{
		tmp_data = list_entry(pos, data, list);
		printf("version: %d, \tversion str: %s\n", tmp_data->version, tmp_data->str);
	}

	list_splice(&data_list, &data_list2);

	printf("data_list, data_list2合并以后\n");
    printf("data_list2 链表\n");
	for(pos = LIST_HEAD(&data_list2); pos != LIST_END(&data_list2); pos = NEXT_NODE(pos))
	{
		tmp_data = list_entry(pos, data, list);
		printf("version: %d, \tversion str: %s\n", tmp_data->version, tmp_data->str);
	}

    // 此时data_list链表的head已经被丢弃，遍历会出问题
//	printf("data_list 链表\n");
//	for(pos = data_list.next; pos != &data_list; pos = pos->next)
//	{
//		tmp_data = list_entry(pos, data, list);
//		printf("version: %d, \tversion str: %s\n", tmp_data->version, tmp_data->str);
//	}

	list_move(&pdata[3].list, &data_list2);
	printf("将pdata[3]移至head和head->next两个结点之间\n");
    printf("data_list2 链表\n");
	//循环读出list中每个结点的数据部分
	for(pos = LIST_HEAD(&data_list2); pos != LIST_END(&data_list2); pos = NEXT_NODE(pos))
	{
		tmp_data = list_entry(pos, data, list);
		printf("version: %d, \tversion str: %s\n", tmp_data->version, tmp_data->str);
	}

	if (list_empty(&data_list2))
	{
		printf("链表为空\n");
	}
	else
	{
		printf("链表非空\n");
	}

    i = 0;
    for (pos = LIST_HEAD(&data_list2); pos != LIST_END(&data_list2); pos = n)
    {
        n = NEXT_NODE(pos);
        list_del(pos);
        printf("%d\n", i++);
    }

    printf("删除data_list2各节点后重新检测\n");
	if (list_empty(&data_list2))
	{
		printf("链表为空\n");
	}
	else
	{
		printf("链表非空\n");
	}

	free(pdata);

	return 0;

}
