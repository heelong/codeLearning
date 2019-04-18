// codeLearning.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <deque>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include "algorithm.h"
using namespace std;
/*
	按照顺时针顺序打印矩阵
*/
void printEdge1(int*matrix,int row,int col,int topRow,int topCol,int downRow,int downCol)
{
	if (topRow == downRow)//只有一行
	{
		for (int i = topCol; i <= downCol;i++)
		{
			std::cout << matrix[topRow*col + i] << " ";
		}
	}
	else if (topCol==downCol)//只有一列时
	{
		for (int i = topRow; i < +downRow;i++)
		{
			std::cout << matrix[i*col + topCol] << " ";
		}
	}
	else
	{
		int currentRow = topRow;
		int currentCol = topCol;
		while (currentCol!=downCol)//从左向右输出
		{
			std::cout << matrix[topRow*col + currentCol] <<" ";
			currentCol++;
		}
		while (currentRow != downRow)//从上向下输出
		{
			std::cout << matrix[currentRow*col + downCol] << " ";
			currentRow++;
		}
		while (currentCol!=topCol)//从右向左输出
		{
			std::cout << matrix[downRow*col + currentCol] << " ";
			currentCol--;
		}
		while (currentRow!=topRow)
		{
			std::cout << matrix[currentRow*col + topCol] << " ";
			currentRow--;
		}
	}
}
void TurnAroundPrintMatrix()
{
	int matrix[16] = { 1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16 };
	int topRow = 0;
	int topCol = 0;
	int downRow = 3;
	int downCol = 3;
	while (topRow <= downRow&&topCol <= downCol)
		printEdge1(matrix, 4,4,topRow++, topCol++, downRow--, downCol--);
}
void printEdge2(int*matrix, int row, int col, int topRow, int topCol, int downRow, int downCol)
{
	int startRow = topRow;
	int startCol = topCol;
	int deta = downCol - topCol;
	int tmp=0;//用于交换
	for (int i = 0; i != deta;i++)
	{
		tmp = matrix[topRow*col+topCol+i];
		matrix[topRow*col + topCol + i] = matrix[(downRow-i)*col + topCol];
		matrix[(downRow - i)*col + topCol] = matrix[downRow*col + downCol-i];
		matrix[downRow*col + downCol - i] = matrix[(topRow+i)*col + downCol];
		matrix[(topRow + i)*col + downCol] = tmp;

	}
}
void rotateMatrix()
{
	int matrix[16] = { 1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16 };
	int topRow = 0;
	int topCol = 0;
	int downRow = 3;
	int downCol = 3;
	while (topRow <= downRow&&topCol <= downCol)
		printEdge2(matrix, 4, 4, topRow++, topCol++, downRow--, downCol--);
	for (int i = 0; i <4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			std::cout<<matrix[i*4 + j]<<" ";
		}
		std::cout << std::endl;
	}
}
void printEdge3(int*matrix, int row, int col, int topRow, int topCol, int downRow, int downCol,bool order)
{
	if (order)
	{
		while (topRow!=downRow+1)
		{
			std::cout << matrix[topRow*col + topCol] << " ";
			topRow++;
			topCol--;
		}
	}
	else
	{
		while (downRow!=topRow-1)
		{
			std::cout << matrix[downRow*col + downCol] << " ";
			downRow--;
			downCol++;
		}
	}
}
//之字形打印矩阵
void ZigMatrix()
{
	int matrix[16] = { 1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16 };
	int row = 4, col = 4;
	int endRow = 3, endCol = 3;
	int topRow = 0;
	int topCol = 0;
	int downRow = 0;
	int downCol = 0;
	bool order = false;
	while (topRow!=row)
	{
		printEdge3(matrix, row, col, topRow, topCol, downRow, downCol, order);
		topRow = topCol == endCol ? topRow + 1 : topRow;
		topCol = topCol == endCol ? topCol : topCol+1;
		downCol = downRow == endRow ? downCol + 1 : downCol;
		downRow = downRow == endRow ? downRow : downRow + 1;
		order = !order;
	}

}

//判断一个点是否在矩形形中(平行于坐标轴的情况)
bool isInside(double x1,double y1,double x4,double y4,double x,double y)
{
	if (x <= x1)
		return false;
	if (x>=x4)
	{
		return false;
	}
	if (y<=y1)
	{
		return false;
	}
	if (y>=y4)
	{
		return false;
	}
	return true;
}
bool isInside(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x, double y)
{
	if (y1 == y2)
		return isInside(x1, y1, x4, y4, x, y);
	
	double l = x4 - x3;
	double s = y4 - y3;
	double len = std::sqrt(l*l+s*s);
	double sin_ = s / len;
	double cos_ = l / len;
	double x1R = cos_*x1 + sin_*y1;
	double y1R = -sin_*x1 + cos_*y1;
	double x4R = cos_*x4 + sin_*y4;
	double y4R = -sin_*x4 + cos_*y4;
	double xR = cos_*x + sin_*y;
	double yR = -sin_*x + cos_*y;
	return isInside(x1R, y1R, x4R, y4R, xR, yR);
}

//返回两向量的叉乘
double crossProduct(const double x1,const double y1,const double x2,const double y2)
{
	return x1*y2 - x2*y1;
}
//点是否在三角形中
bool isInside2(double x1,  double y1,  double x2,  double y2,
	 double x3,  double y3, const double x, const double y)
{
	//判断三角形三个点的输入顺序是否为逆时针
	if (crossProduct(x3-x1,y3-y1,x2-x1,y2-y1)>=0)
	{
		double tmpx = x2;
		double tmpy = y2;
		x2 = x3; y2 = y3;
		x3 = tmpx; y3 = tmpy;
	}
	if (crossProduct(x3 - x1, y3 - y1, x - x1, y - y1)<0)
	{
		return false;
	}
	if (crossProduct(x1-x2,y1-y2,x-x2,y-y2)<0)
	{
		return false;
	}
	if (crossProduct(x2-x3,y2-y3,x-x3,y-y3)<0)
	{
		return false;
	}
}

/*汉诺塔问题
有三根杆子A，B，C。A杆上有N个(N>1)穿孔圆环，盘的尺寸由下到上依次变小。要求按下列规则将所有圆盘移至C杆：
1、每次只能移动一个圆盘；
2、大盘不能叠在小盘上面。

基本步骤如下：
假设已经知道改怎么移动n-1个移动盘了
1、把n-1个圆盘从起点盘移动到没有任何圆盘的过渡盘；
2、将最后一个原盘从起点盘移动到目标盘；
3、将n-1个盘从过度盘移动到目标盘，完成汉诺塔问题；
*/
void hannoiProblem(int n, char A,char B, char C)
{
	if (n==1)
	{
		std::cout << "move" << n << "from" << A << " to " << C << std::endl;
	}
	else
	{
		hannoiProblem(n - 1, A, C, B);
		std::cout << "move" << n << "from" << A << " to " << C << std::endl;
		hannoiProblem(n - 1, B, A, C);
	}
}

void getMaxWindows(const int*arr_in,const int&num_in,int*arr_out,const int&num_out,const int&windows_size)
{
	if (arr_in==nullptr||arr_out==nullptr||windows_size<1)
	{
		return;
	}
	int index = 0;
	std::deque<int>qmax;//标记子窗口最大值的位置
	for (int i = 0; i < num_in;++i)
	{
		while (!qmax.empty()&&arr_in[qmax.back()]<=arr_in[i])
		{
			qmax.pop_back();
		}
		qmax.push_back(i);
		if (qmax.front()==(i-windows_size))
		{
			qmax.pop_front();
		}
		if (i >= (windows_size - 1))
		{
			arr_out[index++] = arr_in[qmax.front()];
		}
	}
	return;
}

void replaceSpace(char *str, int length) {
	if (str == nullptr || length < 0)
		return;
	int numOfSpace = 0;
	int i = 0;
	int oldLength = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
			numOfSpace++;
		i++;
		oldLength++;
	}
	int newLength = oldLength + numOfSpace * 2;
	if (newLength > length)
		return;
	while (oldLength >= 0 && oldLength < newLength)
	{
		if (str[oldLength] == ' ')
		{
			str[newLength--] = '0';
			str[newLength--] = '2';
			str[newLength--] = '%';
		}
		else
		{
			str[newLength--] = str[oldLength];
		}
		oldLength--;
	}
}

int StrToInt(std::string str) {
	int len = str.length();
	int i = 0;
	int flag = 1; bool hasFlag = false;
	int num = 0;
	int size_i = 1;
	int size = std::pow(10, len - size_i);
	while (i<len){
		if (str[i] == '-' || str[i] == '+'){
			size = std::pow(10, len - size_i - 1);
			if (((i + 1 < len) && (str[i + 1] <= '0' || str[i + 1] > '9')) ||
				(i + 1 >= len))
				return 0;
			flag = (str[i] == '-') ? -1 : 1;
			num += ((str[i + 1] - '0')*size);
			i += 2; size /= 10;
			break;
		}
		else if (str[i]>'0' || str[i] <= '9'){
			num += (str[i] - '0')*size;
			++i; size /= 10;
			break;
		}
		size_i++;
		size = std::pow(10, len - size_i);;
		++i;
	}
	while (i<len){
		if (str[i]>'0'&&str[i] <= '9'){
			num += (str[i] - '0')*size;
			++i; size /= 10;
		}
		else
			return 0;
	}
	return num*flag;
}

string ReverseSentence(string str) {
	string res = str;
	int len = str.length();
	int end_count = len - 1;
	for (int i = 0; i < len; ++i){
		int i_end = i;
		if (str[i_end] == ' '){
			res[end_count--] = ' ';
			continue;
		}
		while (i_end < len&&str[i_end] != ' '){
			i_end++;
		}
		for (int j = i_end - 1; j >= i; --j){
			res[end_count--] = str[j];
		}
		i = i_end - 1;
	}
	return res;
}

static bool comp(const int&a, const int&b){
	return a < b;
}
bool IsContinuous(vector<int> numbers) {
	sort(numbers.begin(), numbers.end(), comp);
	int numberOfZero = 0;
	int len = numbers.size();
	for (int i = 0; i < len; ++i){
		if (numbers[i] == 0)
			numberOfZero += 1;
		else
			break;
	}
	int count = 0;
	for (int i = numberOfZero; i < (len - 1); ++i){
		int gap = numbers[i + 1] - numbers[i]-1;
		if (gap < 0)
			return false;
		count += gap;
	}
	if (count <= (numberOfZero))return true;
	return false;
}

int abs_by_move(int n){
	return n*((n >> 31 << 1) + 1);
}



double abs_by_move(double number){

		//printf("&#37;f ", number);
		unsigned long long* x = (unsigned long long*)&number;
		*x &= 0x7fffffffffffffff;

		number = *(double *)x;
		//printf("%f \n", number);
		return number;
}

struct Node{
	int val;
	struct Node*next;
	Node(int value_) : val(value_), next(nullptr) {
	}
};

int LastRemaining_Solution(int n, int m)
{
	if (n < 1)return 0;
	Node*head = new Node(0);
	Node*curNode = head;
	for (int i = 1; i < n; ++i){
		curNode->next = new Node(i);
		curNode = curNode->next;
	}
	curNode->next = head;//组成环
	Node*pre = curNode;//记录前一节点
	Node*cur;
	curNode = head;//从头节点开始
	int count = -1;
	while (curNode->next != curNode){
		count++;
		if (count == (m - 1)){
			cur = curNode;//记录当前节点
			curNode = curNode->next;//跳到下一节点
			pre->next = curNode;
			delete cur; cur = nullptr;
			count = -1;
		}
		pre = pre->next;
		curNode = curNode->next;//跳到下一节点
	}
	int lucky = curNode->val;
	delete curNode; curNode = nullptr;
	return lucky;
}
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
		val(x), next(NULL) {
	}
};
ListNode* EntryNodeOfLoop(ListNode* pHead)
{
	if (pHead == nullptr || pHead->next == nullptr || pHead->next->next == nullptr)
		return nullptr;
	ListNode* fast = pHead->next->next;
	ListNode* slow = pHead;
	while (fast != slow){
		if (fast != nullptr&&fast->next != nullptr){
			slow = slow->next;
			fast = fast->next->next;
		}
		else
			return nullptr;
	}
	fast = fast->next;
	int count = 1;//统计环的大小
	while (fast != slow){
		count += 1;
		fast = fast->next;
	}
	fast = pHead;
	for (int i = 0; i < count; ++i){
		fast = fast->next;
	}
	slow = pHead;
	while (fast != slow){
		fast = fast->next;
		slow = slow->next;
	}
	return slow;
}


struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
		val(x), left(NULL), right(NULL) {
	}
};

void Serialize(TreeNode *root, string&out) {
	if (root == nullptr){
		out += '#';
		return;
	}
	out.append(to_string(root->val));
	out += ',';
	Serialize(root->left, out);
	Serialize(root->right, out);
}
char* Serialize(TreeNode *root) {
	if (root == nullptr)return nullptr;
	string out;
	Serialize(root, out);
	char*out_char = new char[out.length() + 1]();
	int size = out.length();
	int i = 0;
	for (; i < size; ++i){
		out_char[i] = out[i];
	}
	out_char[i] = '\0';
	return out_char;
}

TreeNode* Deserialize(char **str) {
	if (**str == '#'){
		++(*str);
		return nullptr;
	}
	int num = 0;
	while (**str != '/0'&&**str != ','){
		num = num * 10 + ((**str) - '0');
		++(*str);
	}
	TreeNode*root = new TreeNode(num);
	if (**str == '/0')
		return root;
	else
		++(*str);
	root->left = Deserialize(str);
	root->right = Deserialize(str);
	return root;
}
TreeNode* Deserialize1(char *str) {
	if (str == nullptr)return nullptr;
	TreeNode*head = Deserialize(&str);
	return head;
}

class MedianHeap {
public:
	void Insert(int num)
	{
		//如果值比大根堆堆顶的值小，插入大根堆
		if (m_max_heap.size() != 0 && num<m_max_heap.front())
				HeapInsert_Max(m_max_heap, num);
		else
			HeapInsert_Min(m_min_heap, num);
		if (abs(m_max_heap.size() - m_min_heap.size()>1))//两个堆的差大于1时
		{
			if (m_max_heap.size() > m_min_heap.size())
			{
				HeapInsert_Min(m_min_heap, HeapDelete_Max(m_max_heap));
			}
			else
				HeapInsert_Max(m_max_heap, HeapDelete_Min(m_min_heap));
		}
	}
	double GetMedian()
	{
		int size = m_max_heap.size() + m_min_heap.size();
		if (size%2==0)
		{
			return static_cast<double>(m_max_heap.front() + m_min_heap.front()) / 2.0;
		}
		else{
			if (m_max_heap.size() > m_min_heap.size())
				return m_max_heap.front();
			else
				return m_min_heap.front();
		}
	}

	void deleteTop(){
		HeapDelete_Max(m_max_heap);
	}
private:
	void swap(std::vector<int>&heap_,const int&i, const int&j){
		heap_[i] = heap_[i] ^ heap_[j];
		heap_[j] = heap_[i] ^ heap_[j];
		heap_[i] = heap_[i] ^ heap_[j];
	}

	void HeapInsert_Max(std::vector<int>&heap_, const int&value){
		heap_.push_back(value);//将value值插入到堆中
		int size = heap_.size();//获取当前整个数组的大小
		int child = size - 1;//获取最后一个叶子结点
		int parent = (child - 1) / 2;//获取父节点的值
		for (int i = parent; i >= 0; --i)
		{
			adjustHeap_max(heap_,i);
		}
	}
	//由上向下进行交换,把最大值交换上来
	void adjustHeap_max(std::vector<int>&heap_,const int&parent_in){
		int parent = parent_in;
		int child = 2 * parent + 1;//获取左子节点
		int tmp_value = 0;
		int size = heap_.size();
		while (child < size)
		{
			if (child + 1 < size&&heap_[child + 1] > heap_[child]){
				child += 1;//右节点更大，切换到右节点
			}
			tmp_value = heap_[parent];
			if (tmp_value >= heap_[child])
				break;

			swap(heap_, parent, child);
			parent = child;
			child = 2 * parent + 1;
		}
	}

	void HeapInsert_Min(std::vector<int>&heap_, const int&value){
		heap_.push_back(value);//将value值插入到堆中
		int size = heap_.size();//获取当前整个数组的大小
		int child = size - 1;//获取最后一个叶子结点
		int parent = (child - 1) / 2;//获取父节点的值
		for (int i = parent; i >= 0; --i)
		{
			adjustHeap_Min(heap_, i);
		}
	}
	//由上向下进行交换,把最大值交换上来
	void adjustHeap_Min(std::vector<int>&heap_, const int&parent_in){
		int parent = parent_in;
		int child = 2 * parent + 1;//获取左子节点
		int tmp_value = 0;
		int size = heap_.size();
		while (child < size)
		{
			if (child + 1 < size&&heap_[child + 1] < heap_[child]){
				child += 1;//右节点更小，切换到右节点
			}
			tmp_value = heap_[parent];
			if (tmp_value <= heap_[child])
				break;

			swap(heap_, parent, child);
			parent = child;
			child = 2 * parent + 1;
		}
	}

	//删除大根堆的最大值，并返回
	int HeapDelete_Max(std::vector<int>&heap_){
		int value = heap_.front();//获取大根堆最大值
		int size = heap_.size();
		swap(heap_, 0, size - 1);//交换大根堆堆顶与最后一个元素
		heap_.erase(heap_.begin() + (size - 1));//删除最后一个节点

		int child = heap_.size() - 1;//获取最后个叶子结点
		int parent = (child - 1) / 2;//获取父节点的值
		for (int i = parent; i >= 0; --i)
		{
			adjustHeap_max(heap_, i);
		}
		return value;
	}

	//删除小根堆的最小值，并返回
	int HeapDelete_Min(std::vector<int>&heap_){
		int value = heap_.front();//获取大根堆最大值
		int size = heap_.size();
		swap(heap_, 0, size - 1);//交换大根堆堆顶与最后一个元素
		heap_.erase(heap_.begin() + (size - 1));//删除最后一个节点

		int child = heap_.size() - 1;//获取最后个叶子结点
		int parent = (child - 1) / 2;//获取父节点的值
		for (int i = parent; i >= 0; --i)
		{
			adjustHeap_Min(heap_, i);
		}
		return value;
	}

private:
	std::vector<int>m_max_heap;
	std::vector<int>m_min_heap;
};


void trimLeftTrailingSpaces(string &input) {
	input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) {
		return !isspace(ch);
	}));
}

void trimRightTrailingSpaces(string &input) {
	input.erase(find_if(input.rbegin(), input.rend(), [](int ch) {
		return !isspace(ch);
	}).base(), input.end());
}

vector<int> stringToIntegerVector(string input) {
	vector<int> output;
	trimLeftTrailingSpaces(input);
	trimRightTrailingSpaces(input);
	input = input.substr(1, input.length() - 2);
	stringstream ss;
	ss.str(input);
	string item;
	char delim = ',';
	while (getline(ss, item, delim)) {
		output.push_back(stoi(item));
	}
	return output;
}

/////////////////////////////////虚函数的学习//////////////////////////////////
class Base {
public:
	virtual void f() { cout << "base::f" << endl; }
	virtual void g() { cout << "base::g" << endl; }
	virtual void h() { cout << "base::h" << endl; }
};

class Derive : public Base{
public:
	void g() { cout << "derive::g" << endl; }
};

class SolutionMedianSorted {
public:

	double findMedianSortedArrays(vector<int>& A, vector<int>& B) {
		int m = A.size();
		int n = B.size();
		if (m > n) { // to ensure m<=n
			return findMedianSortedArrays(B,A);
		}
		int iMin = 0, iMax = m, halfLen = (m + n + 1) / 2;
		while (iMin <= iMax) {
			int i = (iMin + iMax) / 2;
			int j = halfLen - i;
			if (i < iMax && B[j - 1] > A[i]){
				iMin = i + 1; // i is too small
			}
			else if (i > iMin && A[i - 1] > B[j]) {
				iMax = i - 1; // i is too big
			}
			else { // i is perfect
				int maxLeft = 0;
				if (i == 0)
				{
					maxLeft = B[j - 1];
				}
				else if (j == 0)
				{
					maxLeft = A[i - 1];
				}
				else
				{
					maxLeft = max(A[i - 1], B[j - 1]);
				}
				if ((m + n) % 2 == 1)
				{
					return maxLeft;
				}

				int minRight = 0;
				if (i == m)
				{
					minRight = B[j];
				}
				else if (j == n)
				{
					minRight = A[i];
				}
				else
				{
					minRight = min(B[j], A[i]);
				}

				return (maxLeft + minRight) / 2.0;
			}
		}
		return 0.0;
	}
};




int _tmain(int argc, _TCHAR* argv[])
{
	string line;
	//while (getline(cin, line)) {
	//	vector<int> nums1 = stringToIntegerVector(line);
	//	getline(cin, line);
	//	vector<int> nums2 = stringToIntegerVector(line);

	//	double ret = SolutionMedianSorted().findMedianSortedArrays(nums1, nums2);

	//	string out = to_string(ret);
	//	cout << out << endl;
	//}

	//ListNode*head = new ListNode(0);
	//ListNode*curNode = head;
	//ListNode*enter = nullptr;
	//for (int i = 1; i < 8; ++i){
	//	curNode->next = new ListNode(i);
	//	curNode = curNode->next;
	//	if (i == 4)
	//		enter = curNode;
	//}
	//curNode->next = enter;
	//ListNode*enter_tmp=EntryNodeOfLoop(head);
	//
	//char str[] = { '1', ',', '2', ',', '#', '#', '3', ',', '#',  '#', '\0' };
	//Deserialize1(str);
	//
	//MedianHeap heap_tmp;
	//for (int i = 0; i <20;++i)
	//{
	//	heap_tmp.Insert(i);
	//}
	//heap_tmp.deleteTop();

	GeometricAlgorithm::GeometricAlgorithmTest();
	return 0;
}

