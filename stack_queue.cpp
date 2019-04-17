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
	else if (getmin()>=value)//��һ�ַ�������Ԫ�ش��ڵ�����Сջջ��Ԫ��ʱ���ظ�ѹ����Сջջ��Ԫ��
	{
		stackMin.push(value);
	}
	stackData.push(value);
}
int stack_queue::pop()
{
	if (stackData.empty())
	{
		std::cout << "�����ѿ�"<<std::endl;
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
		std::cout << "�����ѿ�" << std::endl;
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
		std::cout << "����Ϊ�գ�û������" << std::endl;
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
		int last = getAndRemoveLastElement(stack_in);//�ݹ���ã�����ջ��Ԫ�ز�ɾ��
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
	std::stack<int>help;//��������
	while (!stack_in.empty())
	{
		int value = stack_in.top();//��ȡջ��Ԫ��
		stack_in.pop();
		if (help.empty())
		{
			help.push(value);
		}else if (value<=help.top())//ջ��Ԫ��С�ڻ���ڸ���ջջ��Ԫ�أ�ֱ�ӽ�ֵѹ�븨��ջ��
		{
			help.push(value);
		}
		else
		{
			while (value>help.top())//���value����ջ��Ԫ�أ���help��Ԫ����һ������ѹ��stack_in�У�ֱ������ջջ��Ԫ�ش��ڻ��ߵ���value���ٽ�valueѹ��help
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