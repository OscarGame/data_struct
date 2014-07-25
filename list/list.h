#ifndef LIST_H_
#define LIST_H_

struct list_head
{
	struct list_head *next;
	struct list_head *prev;
};

#define LIST_HEAD(pList) ((pList)->next)
#define LIST_END(pList)  (pList)
#define NEXT_NODE(pNode) ((pNode)->next)

//这个宏已经在stddef.h中定义了
//#define offsetof(type, member)		((size_t)&((type *)0)->member)

//获取指向宿主结构体的指针
//ptr 为宿主结构体中member的指针
//type 为宿主结构体的类型
//member 宿主结构体中成员，必须跟ptr指向的成员是同一个
#define list_entry(ptr, type, member) \
		((type *)((char *)(ptr) - (unsigned long)(&((type *)0)->member)))

//pos为struct list_head类型的指针
//遍历从head->next开始，head节点无data，head->prev指向最后一个节点，最后一个节点last->next == head
#define list_for_each(pos, head) \
	for (pos = (head)->next; pos != (head); pos = pos->next)

#define list_for_each_reverse(pos, head) \
	for (pos = (head)->prev; pos != (head); pos = pos->prev)

//pos为指向宿主类型的指针，head是头结点，即data_list，member是宿主成员struct list_head list
#define list_for_each_entry(pos, head, member)    \
    for (pos = list_entry((head)->next, typeof(*pos), member);      \
            &pos->member != (head);       \
            pos = list_entry(pos->member.next, typeof(*pos), member))

#define list_for_each_entry_reverse(pos, head, member)     \
    for (pos = list_entry((head)->prev, typeof(*pos), member);      \
            &pos->member != (head);            \
            pos = list_entry(pos->mmeber.prev, typeof(*pos), member))

//链表初始化
void list_init(struct list_head *list);

//在pnode之后插入新结点
void list_add(struct list_head *new, struct list_head *pnode);

//删除结点pnode
void list_del(struct list_head *pnode);

//将pnode结点移动到pos之后
void list_move(struct list_head *pnode, struct list_head *pos);

//判断链表是否为空
int list_empty(const struct list_head *head);

//将list1插入到list2中,list2和list2->next之间，list1的链表头被抛弃了
void list_splice(struct list_head *list1, struct list_head *list2);

#endif /* LIST_H_ */
