#include <stdlib.h>
#include "list.h"

void list_init(struct list_head *list)
{
	list->next = list;
	list->prev = list;
}

// 在两个非空结点中插入一个结点，new, prev, next均不能为空
static void __list_add(struct list_head *new, struct list_head *prev, struct list_head *next)
{
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}


void list_add(struct list_head *new, struct list_head *pnode)
{
	__list_add(new, pnode, pnode->next);
}


//删除prev和next之间的结点
static void __list_del(struct list_head *prev, struct list_head *next)
{
	next->prev = prev;
	prev->next = next;
}


// 删除节点entry，如果entry节点的data是malloc分配，需要list_del前（后）自行free
void list_del(struct list_head *pnode)
{
	__list_del(pnode->prev, pnode->next);
	pnode->prev = NULL;
	pnode->next = NULL;
}

void list_move(struct list_head *pnode, struct list_head *pos)
{
	__list_del(pnode->prev, pnode->next);
	list_add(pnode, pos);
}

// 判断list是否为空
int list_empty(const struct list_head *head)
{
	return (head->next == head) && (head->prev == head);
}

static void __list_splice(struct list_head *list1, struct list_head *list2)
{
	struct list_head *first = list1->next; //第一个数据从list1->next开始，因为list1的head节点data成员无效
	struct list_head *last = list1->prev;
	struct list_head *at = list2->next; // 将list1插入到list2当前节点之后，list2->next之前

	first->prev = list2;
	list2->next = first;

	last->next = at;
	at->prev = last;
}

void list_splice(struct list_head *list1, struct list_head *list2)
{
	if (!list_empty(list1))
	{
		__list_splice(list1, list2);
	}
}


