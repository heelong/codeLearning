#pragma once

class node
{
public: 
	int value;
	node* left;
	node*right;
	node()
	{
		value = 0;
		left = nullptr;
		right = nullptr;
	}
	node(const int& data)
	{
		value = data;
		left = nullptr;
		right = nullptr;
	}
	node& operator=(const node& tmp)
	{
		if (this!=&tmp)
		{
			value = tmp.value;
			left = tmp.left;
			right = tmp.right;
		}
		return *this;
	}
};
class tree
{
public:
	tree();
	~tree();
	void getMaxTree(const int* arr, const int &num);
};

