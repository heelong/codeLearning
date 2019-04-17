#pragma once
//编写栈与队列类试题
#include <stack>
#include <queue>
#include <iostream>
class stack_queue
{
public:
	stack_queue();
	~stack_queue();
	//1、压栈函数，正常压入数据保存栈；
	//2、当value值小于或等于最小值栈栈顶元素时，压入最小值栈
	void push(const int& value);
	//1、退栈函数，正常退出数据保存栈栈顶元素
	//2、当退栈元素等于最小栈栈顶元素时，退出最小栈栈顶元素
	int pop();
	//返回当前栈的最小元素，由于最小栈栈顶元素即为最小值，直接返回
	int getmin();
private:
	std::stack<int>stackData;//用于保存数据
	std::stack<int>stackMin;//用于保存当前栈的最小值
};

class two_stack_queue
{
private:
	std::stack<int>stackPushData;//用于压入数据
	std::stack<int>stackPopData;//用于弹出数据
public:
	//压入数据，只往stackPushData中压入数据
	void push(const int& value);
	//弹出数据，从stackPopData中弹出，当stackPopData中没有数据时，将stackPushData中的所有数据压入stackPopData中
	int pop();

	//仅用递归函数以及栈操作逆序一个栈
	//返回并删除栈的最后一个元素
	int getAndRemoveLastElement(std::stack<int>&stack_in);
	//逆序一个栈,仅使用递归操作，逆序一个栈，不申请多余的存储空间
	//可用于逆序一个数据，不申请多余空间
	void reverse(std::stack<int>&stack_in);
	//用一个栈给另一个栈进行排序，不使用其他的数据结构
	void sortStackByStack(std::stack<int>&stack_in);
};

// 猫狗队列
class pet
{
private:
	std::string type;
public:
	pet();
	pet(std::string type_)
	{
		type = type_;
	}
	std::string getPetType()
	{
		return type;
	}
};

class dog:public pet
{
public:
	dog()
	{
		std::cout << "dog" << std::endl;
	}
	~dog();
private:
};
class cat :public pet
{
public:
	cat()
	{
		std::cout << "dog" << std::endl;
	}
	~cat();
private:
};
class petEnterQueue
{
private:
	pet m_pet;
	long count;//时间戳，用于计数
public:
	petEnterQueue(const pet&pet_, const int& count_)
	{
		m_pet = pet_;
		count = count_;
	}
	pet getPet()
	{
		return m_pet;
	}
	long getCount()
	{
		return count;
	}
	std::string getEnterType()
	{
		return m_pet.getPetType();
	}
};

class DogCatQueue
{
private:
	std::queue<petEnterQueue>dogQ;
	std::queue<petEnterQueue>catQ;
	long count;
public:
	DogCatQueue()
	{
		count = 0;
	}
	void add(pet&pet_)
	{
		if (pet_.getPetType()=="dog")
		{
			dogQ.push(petEnterQueue(pet_,count++));
		}
		else if (pet_.getPetType() == "cat")
		{
			catQ.push(petEnterQueue(pet_, count++));
		}
		else
		{
			std::cout << "输入类型有误" << std::endl;
		}
	}
	//返回宠物队列中的宠物，按照时间戳进行
	pet pullAll()
	{
		if (!dogQ.empty()&&!catQ.empty())//都不为空，根据时间戳进行判断
		{
			if (dogQ.front().getCount()<catQ.front().getCount())
			{
				return dogQ.front().getPet();
			}
			else
			{
				return catQ.front().getPet();
			}
		} 
		else if (!dogQ.empty())
		{
			return  dogQ.front().getPet();
		}
		else if (!catQ.empty())
		{
			return catQ.front().getPet();
		}
		else
			std::cout << "队列为空" << std::endl;
	}
	pet pollDog()
	{
		if (!dogQ.empty())
		{
			return dogQ.front().getPet();
		} 
		else
		{
			std::cout << "队列为空" << std::endl;
		}
	}
	pet pollCat()
	{
		if (!catQ.empty())
		{
			return catQ.front().getPet();
		}
		else
		{
			std::cout << "队列为空" << std::endl;
		}
	}
	bool isEmpty()
	{
		return dogQ.empty() && catQ.empty();
	}
	bool isDogEmpty()
	{
		return dogQ.empty();
	}
	bool isCatEmpty()
	{
		return catQ.empty();
	}
};
