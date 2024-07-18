
#pragma once

#include "include_base.hpp"

// 链环结构
template <class Tem>
struct node
{
	node<Tem> *node_next = nullptr;
	node<Tem> *node_last = nullptr;

	Tem *node_data = nullptr;
};

template <class Tem>
class Ring
{
public:
	Ring(Tem *p = nullptr, uint = 0);
	~Ring(); // 会直接尝试删除所有节点包括所有data

	Tem *Node_next();  // nownode前进一个，返回data
	Tem *Node_last();  // nownode后退一个，返回data
	Tem *Node_now();   // 返回data
	uint Node_count(); // 返回节点数量

	// 在nownode之前添加若干个新节点，n为数量
	void Node_add(Tem *d, uint n = 1);

	// 删除nownode这个节点，nodenow回退一个
	// 返回删除节点的data，如果是head则返回nullptr
	Tem *Node_delete();

private:
	node<Tem> node_head; // 头节点
	uint node_count;	 // 节点数量
	node<Tem> *node_now; // 目前正在操作的节点
};

// 以下是headnode类的实现

template <class Tem>
Ring<Tem>::Ring(Tem *t, uint n) : node_head({&node_head, &node_head, nullptr}), node_count(0), node_now(&node_head) { Node_add(t, n); }

template <class Tem>
Ring<Tem>::~Ring()
{
	node_now = node_head.node_last;

	Tem *d = nullptr;
	while (d = Node_delete())
	{
		delete d;
	}
}

template <class Tem>
Tem *Ring<Tem>::Node_next()
{
	node_now = node_now->node_next;
	return node_now->node_data;
}

template <class Tem>
Tem *Ring<Tem>::Node_last()
{
	node_now = node_now->node_last;
	return node_now->node_data;
}

template <class Tem>
Tem *Ring<Tem>::Node_now()
{
	return node_now->node_data;
}

template <class Tem>
uint Ring<Tem>::Node_count()
{
	return node_count;
}

template <class Tem>
void Ring<Tem>::Node_add(Tem *d, uint n)
{
	for (int i = 0; i < n; i++)
	{
		node<Tem> *r = new node<Tem>;
		r->node_next = node_now;
		r->node_last = node_now->node_last;
		r->node_data = d;

		node_now->node_last->node_next = r;
		node_now->node_last = r;

		node_count++;
	}
}

template <class Tem>
Tem *Ring<Tem>::Node_delete()
{
	// 如果不是head
	if (node_now != &node_head)
	{
		node<Tem> *p = node_now;
		node_now = node_now->node_last;

		p->node_next->node_last = p->node_last;
		p->node_last->node_next = p->node_next;
		Tem *d = p->node_data;
		delete p;

		node_count--;

		return d;
	}
	else
	{
		return nullptr;
	}
}
