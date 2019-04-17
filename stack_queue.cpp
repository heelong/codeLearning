#include "stdafx.h"
#include "stack_queue.h"
#include <iostream>

stack_queue::stack_queue()
{
}


stack_queue::~stack_queue()
{
}
void stack_queue::push(const int& value)
{
	if (stackMin.empty())
	{
		stackMin.push(value);
	}
	else if (getmin()>=value)//另一种方法，当元素大于等于最小栈栈顶元素时，重复压入最小栈栈顶元素
	{
		stackMin.push(value);
	}
	stackData.push(value);
}
int stack_queue::pop()
{
	if (stackData.empty())
	{
		std::cout << "队列已空"<<std::endl;
	}
	int value = stackData.top(); 
	stackData.pop();
	if (value==getmin())
	{
		stackMin.pop();
	}
	return value;
}
int stack_queue::getmin()
{
	if (stackMin.empty())
	{
		std::cout << "队列已空" << std::endl;
	}
	return stackMin.top();
}

void two_stack_queue::push(const int &value)
{
	stackPushData.push(value);
}

int two_stack_queue::pop()
{
	if (stackPopData.empty()&&stackPushData.empty())
	{
		std::cout << "队列为空，没有数据" << std::endl;
	}
	else if (stackPopData.empty())
	{
		while (!stackPushData.empty())
		{
			stackPopData.push(stackPushData.top());
			stackPushData.pop();
		}
	}
	int value= stackPopData.top();
	stackPopData.pop();
	return value;
}
int two_stack_queue::getAndRemoveLastElement(std::stack<int>&stack_in)
{
	int result = stack_in.top();
	stack_in.pop();
	if (stack_in.empty())
	{
		return result;
	}
	else
	{
		int last = getAndRemoveLastElement(stack_in);//递归调用，返回栈底元素并删除
		stack_in.push(result);
		return last;
	}
}
void two_stack_queue::reverse(std::stack<int>&stack_in)
{
	if (stack_in.empty())
	{
		return;
	}
	int value = getAndRemoveLastElement(stack_in);
	reverse(stack_in);
	stack_in.push(value);
}

void two_stack_queue::sortStackByStack(std::stack<int>&stack_in)
{
	std::stack<int>help;//辅助数组
	while (!stack_in.empty())
	{
		int value = stack_in.top();//获取栈顶元素
		stack_in.pop();
		if (help.empty())
		{
			help.push(value);
		}else if (value<=help.top())//栈顶元素小于或等于辅助栈栈顶元素，直接将值压入辅助栈顶
		{
			help.push(value);
		}
		else
		{
			while (value>help.top())//如果value大于栈顶元素，则将help的元素逐一弹出并压入stack_in中，直到辅助栈栈顶元素大于或者等于value，再将value压入help
			{
				stack_in.push(help.top());
				help.pop();
			}
			help.push(value);
		}
	}
	while (!help.empty())
	{
		stack_in.push(help.top());
		help.pop();
	}
}