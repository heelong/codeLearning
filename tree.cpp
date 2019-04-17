#include "stdafx.h"
#include "tree.h"
#include <map>
#include <stack>
tree::tree()
{
}


tree::~tree()
{
}
//找到数左（右）边最近的数，并保存下来
void stackToMap(std::stack<node*>&stack_, std::map<node*, node*>&bigMap)
{
	node* tmp = stack_.top();
	stack_.pop();
	if (stack_.empty())
		bigMap[tmp] = nullptr;
	else
		bigMap[tmp] = stack_.top();

}
void tree::getMaxTree(const int* arr, const int &num)
{
	node**narr = new node*[num];
	for (int i = 0; i < num;++i)
	{
		narr[i] = new node(arr[i]);
	}
	std::stack<node*>m_stack;
	std::map<node*, node*> lBigMap;
	std::map<node*, node*> rBigMap;
	//遍历数组的每一个数，找到每个数最左边第一个比该数大的数
	for (int i = 0; i < num;++i)
	{
		node *cur= narr[i];
		while ((!m_stack.empty())&&(m_stack.top()->value<cur->value))
		{
			stackToMap(m_stack, lBigMap);
		}
		m_stack.push(cur);
	}
	while (!m_stack.empty())
	{
		stackToMap(m_stack, lBigMap);
	}
	
	for (int i = num-1; i >=0; --i)
	{
		node *cur = narr[i];
		while ((!m_stack.empty()) && (m_stack.top()->value < cur->value))
		{
			stackToMap(m_stack, rBigMap);
		}
		m_stack.push(cur);
	}
	while (!m_stack.empty())
	{
		stackToMap(m_stack, rBigMap);
	}

	node*head=nullptr;
	for (int i = 0; i < num;++i)
	{
		node*cur = narr[i];
		node*left = lBigMap[cur];
		node*right = rBigMap[cur];
		if (left==nullptr&&right==nullptr)
		{
			head = cur;
		}else if (left==nullptr)
		{
			if (right->left==nullptr)
			{
				right->left = cur;
			}
			else
			{
				right->right = cur;
			}
		}else if (right==nullptr)
		{
			if (left->left==nullptr)
			{
				left->left = cur;
			}
			else
			{
				left->right = cur;
			}
		}
		else
		{
			node*parent = left->value < right->value ? left : right;
			if (parent->left=nullptr)
			{
				parent->left = cur;
			}
			else
			{
				parent->right=cur;
			}
		}
	}

	for (int i = 0; i < num; ++i)
	{
		delete narr[i];
	}
	delete[]narr;
}
