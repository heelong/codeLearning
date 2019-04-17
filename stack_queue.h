#pragma once
//��дջ�����������
#include <stack>
#include <queue>
#include <iostream>
class stack_queue
{
public:
	stack_queue();
	~stack_queue();
	//1��ѹջ����������ѹ�����ݱ���ջ��
	//2����valueֵС�ڻ������Сֵջջ��Ԫ��ʱ��ѹ����Сֵջ
	void push(const int& value);
	//1����ջ�����������˳����ݱ���ջջ��Ԫ��
	//2������ջԪ�ص�����Сջջ��Ԫ��ʱ���˳���Сջջ��Ԫ��
	int pop();
	//���ص�ǰջ����СԪ�أ�������Сջջ��Ԫ�ؼ�Ϊ��Сֵ��ֱ�ӷ���
	int getmin();
private:
	std::stack<int>stackData;//���ڱ�������
	std::stack<int>stackMin;//���ڱ��浱ǰջ����Сֵ
};

class two_stack_queue
{
private:
	std::stack<int>stackPushData;//����ѹ������
	std::stack<int>stackPopData;//���ڵ�������
public:
	//ѹ�����ݣ�ֻ��stackPushData��ѹ������
	void push(const int& value);
	//�������ݣ���stackPopData�е�������stackPopData��û������ʱ����stackPushData�е���������ѹ��stackPopData��
	int pop();

	//���õݹ麯���Լ�ջ��������һ��ջ
	//���ز�ɾ��ջ�����һ��Ԫ��
	int getAndRemoveLastElement(std::stack<int>&stack_in);
	//����һ��ջ,��ʹ�õݹ����������һ��ջ�����������Ĵ洢�ռ�
	//����������һ�����ݣ����������ռ�
	void reverse(std::stack<int>&stack_in);
	//��һ��ջ����һ��ջ�������򣬲�ʹ�����������ݽṹ
	void sortStackByStack(std::stack<int>&stack_in);
};

// è������
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
	long count;//ʱ��������ڼ���
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
			std::cout << "������������" << std::endl;
		}
	}
	//���س�������еĳ������ʱ�������
	pet pullAll()
	{
		if (!dogQ.empty()&&!catQ.empty())//����Ϊ�գ�����ʱ��������ж�
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
			std::cout << "����Ϊ��" << std::endl;
	}
	pet pollDog()
	{
		if (!dogQ.empty())
		{
			return dogQ.front().getPet();
		} 
		else
		{
			std::cout << "����Ϊ��" << std::endl;
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
			std::cout << "����Ϊ��" << std::endl;
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
