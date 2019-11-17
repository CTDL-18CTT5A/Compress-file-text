
#pragma once
#include<iostream>
#include<string>
using namespace std;
struct NODE
{
	int _freq;
	char _text;
	NODE* pLeft;
	NODE* pRight;
};
//Lưu dữ liệu trong file
struct HuffData
{
	char* s;
	int* wei;
};


struct HuffMap
{
	int** BitArray;
	char* charater;
};

struct HuffmanTree
{
	int size;
	//Tạo ra một mảng con trỏ node , mỗi phần tử chứa một cây root
	NODE** Array;

};

NODE* newNode(char data, int freq);

HuffmanTree* InitHuffTree(int size);

void SwapNode(NODE*& a, NODE*& b);

void MinHeapify(HuffmanTree* hufftree, int index);

NODE* getNodeMin(HuffmanTree* hufftree);

void insertHuffTree(HuffmanTree* hufftree, NODE* newnode);



void BuildMinHeap(HuffmanTree* hufftree);

bool isMinSize(HuffmanTree* hufftree);


HuffmanTree* CreateHeapHuffman(HuffData map, int size);


NODE* builfHuffmanTree(HuffData map, int size);

bool isLeaf(NODE* root);

void ArrayOutput(HuffMap& map, int index, int a[], int n);


void CompressFile(HuffMap& map, NODE* root, int arr[], int top);


void HuffmanCompress(FILE* fileInput, FILE* fileOut, HuffMap& map, HuffData  data, int size);


HuffData ReadFileText(FILE* p);

























////#pragma once
////#include<iostream>
////using namespace std;
////struct NODE
////{
////	int _freq;
////	char _text;
////	NODE* pLeft;
////	NODE* pRight;
////};
////
////struct HuffmanTree
////{
////	int size;
////	//Tạo ra một mảng con trỏ node , mỗi phần tử chứa một cây root
////	NODE** Array;
////
////};
////
////NODE* newNode(char data , int freq)
////{
////	NODE* temp = new NODE;
////	temp->pLeft = NULL;
////	temp->pRight = NULL;
////	temp->_text = data;
////	temp->_freq = freq;
////	return temp;
////
////}
////
////HuffmanTree* createHuffmanTree(int size)
////{
////	HuffmanTree* hufftree = new HuffmanTree;
////
////	hufftree->size = 0;
////
////	hufftree->Array = (NODE**)malloc(size * sizeof(NODE*));
////
////	return hufftree;
////
////}
////
////void SwapNode(NODE* a, NODE* b)
////{
////	NODE* temp = a;
////	a = b;
////	b = temp;
////}
////                                                                                                                                                                                                                                                             
////void MinHeapify(HuffmanTree* hufftree, int index)
////{
////	int min = index;
////	int left = 2 * index + 1;
////	int right = 2 * index + 2;
////
////	if (left < hufftree->size && hufftree->Array[left]->_freq < hufftree->Array[min]->_freq)
////	{
////		min = left;
////	}
////	if (right < hufftree->size && hufftree->Array[right]->_freq < hufftree->Array[min]->_freq)
////	{
////		min = right;
////	}
////	if (min != index)
////	{
////		SwapNode(hufftree->Array[min], hufftree->Array[index]);
////		MinHeapify(hufftree, min);
////	}
////}
////
////NODE* getNodeMin(HuffmanTree* hufftree)
////{
////	NODE* node = hufftree->Array[0];
////	//Lấy ra thì phải đưa cuối lên đầu và trừ bớt size(giống heap sort)
////	hufftree->Array[0] = hufftree->Array[hufftree->size - 1];
////
////	--hufftree->size;
////	MinHeapify(hufftree, 0);
////
////	return node;
////}
////
////void insertHuffTree(HuffmanTree* hufftree, NODE* newnode)
////{
////	++hufftree->size;
////	//Vị trí cuối cùng để thêm vào phần tử mới
////	int posInsert = hufftree->size - 1;
////
////	//Nếu node insert nhỏ hơn root thì phải chuyển lên đầu để tiếp tục tạo root rồi chèn vào
////	 //Nó sẽ so với root mà chưa cây con đó(tại vì khi thêm vào chỉ cần check tại nhanh đó thôi)
////	//Đẩu thằng root nhỏ nhất luôn lên vị trí pos = 0;
////	while (posInsert && newnode->_freq < hufftree->Array[(posInsert - 1) / 2]->_freq)
////	{
////		hufftree->Array[posInsert] = hufftree->Array[(posInsert - 1) / 2];
////		posInsert = (posInsert - 1) / 2;
////	}
////
////	hufftree->Array[posInsert] = newnode;
////
////}
////
////
////
////void BuildMinHeap(HuffmanTree* hufftree)
////{
////	int n = hufftree->size - 1;
////	for (int i = (n - 1) / 2; i >= 0; i--)
////	{
////		MinHeapify(hufftree, i);
////	}
////}
////
////bool isMinSize(HuffmanTree* hufftree)
////{
////	return (hufftree->size == 1);
////}
////
////
////HuffmanTree* CreateHeapHuffman(char* data, int* freq, int size)
////{
////	HuffmanTree* hufftree = createHuffmanTree(size);
////	hufftree->size = size;
////	
////	for (int i = 0; i < size; i++)
////	{
////		hufftree->Array[i] = newNode(data[i], freq[i]);
////	}
////
////	BuildMinHeap(hufftree);
////}
////
////
////NODE* builfHuffmanTree(char* data, int* freq, int size)
////{
////	NODE* left, * right, * root;
////
////	HuffmanTree* hufftree = CreateHeapHuffman(data, freq, size);
////
////	while (isMinSize(hufftree) != 1)
////	{
////		left = getNodeMin(hufftree);
////		right = getNodeMin(hufftree);
////
////
////		root = newNode(' ', left->_freq + right->_freq);
////
////		root->pLeft = left;
////		root->pRight = right;
////
////		insertHuffTree(hufftree, root);
////	}
////
////	//Sau khi đã liên kết lại hết với nhau thì chỉ cần lấy ra root
////
////	return getNodeMin(hufftree);
////
////}
////
////bool isLeaf(NODE* root)
////{
////	return !(root->pLeft) && !(root->pRight);
////
////}
////
////void ArrayOutput(int a[], int n)
////{
////	for (int i = 0; i < n; ++i)
////		printf("%d", a[i]);
////
////	printf("\n");
////}
////
////
////void CompressFile(NODE* root, int a[], int index)
////{
////	//Duyệt LRN để tìm cây lá
////	if (root->pLeft)
////	{
////		a[index] = 0;
////		CompressFile(root, a, index + 1);
////	}
////	if (root->pRight)
////	{
////		a[index] = 1;
////		CompressFile(root, a, index + 1);
////
////	}
////
////	if (isLeaf)
////	{
////		printf("%c : ", root->_text);
////		ArrayOutput(a, index);
////	}
////}
////
////
////void HuffmanCodes(char data[], int freq[], int size)
////
////{
////	// Construct Huffman Tree 
////	NODE* root = builfHuffmanTree(data, freq, size);
////	// Print Huffman codes using 
////	// the Huffman tree built above 
////	int arr[100], top = 0;
////
////	CompressFile(root, arr, top);
////}
////
////
////int main()
////{
////
////	char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
////	int freq[] = { 1, 2, 12, 13, 16, 45 };
////
////	//char arr[] = { '0', '1', 'C', 'L', 'N' , 'T' };
////	//int freq[] = { 12, 6, 11, 5, 8, 12 };
////
////	int size = sizeof(arr) / sizeof(arr[0]);
////
////	HuffmanCodes(arr, freq, size);
////
////	return 0;
////}
////
//// This constant can be avoided by explicitly 
//// calculating height of Huffman Tree 
//#define MAX_TREE_HT 100 
//#include<iostream>
//using namespace std;
//// A Huffman tree node 
//struct MinHeapNode {
//
//	// One of the input characters 
//	char data;
//
//	// Frequency of the character 
//	unsigned freq;
//
//	// Left and right child of this node 
//	 MinHeapNode* left, * right;
//};
//
//// A Min Heap:  Collection of 
//// min-heap (or Huffman tree) nodes 
//struct HuffManTree {
//
//	// Current size of min heap 
//	unsigned size;
//
//	// capacity of min heap 
//	unsigned capacity;
//
//	// Array of minheap node pointers 
//	 MinHeapNode** array;
//};
//
//// A utility function allocate a new 
//// min heap node with given character 
//// and frequency of the character 
// MinHeapNode* newNode(char data, unsigned freq)
//{
//	MinHeapNode* temp = new MinHeapNode;
//
//	temp->left = temp->right = NULL;
//	temp->data = data;
//	temp->freq = freq;
//
//	return temp;
//}
//
////Tạo ra vùng nhớ mặc đinh cho cây huffman
//HuffManTree* createHuffmanTree(unsigned capacity)
//
//{
//
//	HuffManTree* hufftree = new HuffManTree;
//
//	// current size is 0 
//	hufftree->size = 0;
//
//	hufftree->capacity = capacity;
//
//	hufftree->array= (MinHeapNode**)malloc(hufftree->capacity * sizeof(MinHeapNode*));
//	return hufftree;
//}
//
////Swap 2 node con trong cây huff
//void swapMinHeapNode(MinHeapNode*& a,MinHeapNode*& b)
//{
//
//	MinHeapNode* t = a;
//	a = b;
//	b = t;
//}
//
////Cấu hình lại cây huffman
//void minHeapify(HuffManTree* hufftree, int idx)
//{
//
//	int smallest = idx;
//	int left = 2 * idx + 1;
//	int right = 2 * idx + 2;
//
//	if (left < hufftree->size && hufftree->array[left]->freq < hufftree->array[smallest]->freq)
//		smallest = left;
//
//	if (right < hufftree->size && hufftree->array[right]->freq < hufftree->array[smallest]->freq)
//		smallest = right;
//
//	if (smallest != idx) 
//	{
//		swapMinHeapNode(hufftree->array[smallest],hufftree->array[idx]);
//		minHeapify(hufftree, smallest);
//	}
//}
//
//// A utility function to check 
//// if size of heap is 1 or not 
//int isSizeOne(HuffManTree* hufftree)
//{
//
//	return (hufftree->size == 1);
//}
//
//// A standard function to extract 
//// minimum value node from heap 
// MinHeapNode* extractMin(HuffManTree* hufftree)
//{
//
//	MinHeapNode* temp = hufftree->array[0];
//	hufftree->array[0] = hufftree->array[hufftree->size - 1];
//
//	--hufftree->size;
//	minHeapify(hufftree, 0);
//	return temp;
//}
//
//// A utility function to insert 
//// a new node to Min Heap 
//void insertHuffTree(HuffManTree* hufftree, MinHeapNode* minHeapNode)
//
//{
//
//	++hufftree->size;
//	int i = hufftree->size - 1;
//
//	//Nếu node insert nhỏ hơn root thì phải chuyển lên đầu để tiếp tục tạo root rồi chèn vào
//	//Nó sẽ so với root mà chưa cây con đó(tại vì khi thêm vào chỉ cần check tại nhanh đó thôi)
//	//Đẩu thằng root nhỏ nhất luôn lên vị trí pos = 0;
//	while (i && minHeapNode->freq < hufftree->array[(i - 1) / 2]->freq) 
//	{
//		hufftree->array[i] = hufftree->array[(i - 1) / 2];
//		i = (i - 1) / 2;
//
//	}
//	hufftree->array[i] = minHeapNode;
//	//cout << hufftree->array[i]->freq << endl;
//}
//
//// A standard function to build min heap 
//void buildMinHeap(HuffManTree* hufftree)
//
//{
//
//	int n = hufftree->size - 1;
//	int i;
//
//	for (i = (n - 1) / 2; i >= 0; --i)
//		minHeapify(hufftree, i);
//}
//
//// A utility function to print an array of size n 
//void printArr(int arr[], int n)
//{
//	int i;
//	for (i = 0; i < n; ++i)
//		printf("%d", arr[i]);
//
//	printf("\n");
//}
//
//// Utility function to check if this node is leaf 
//int isLeaf(MinHeapNode* root)
//
//{
//
//	return !(root->left) && !(root->right);
//}
//
//// Creates a min heap of capacity 
//// equal to size and inserts all character of 
//// data[] in min heap. Initially size of 
//// min heap is equal to capacity 
//HuffManTree* createAndBuildHuffTree(char data[], int freq[], int size)
//
//{
//
//	HuffManTree* hufftree = createHuffmanTree(size);
//
//	for (int i = 0; i < size; ++i)
//		hufftree->array[i] = newNode(data[i], freq[i]);
//
//	hufftree->size = size;
//	buildMinHeap(hufftree);
//
//	return hufftree;
//}
//
//// The main function that builds Huffman tree 
//MinHeapNode* buildHuffmanTree(char data[], int freq[], int size)
//{
//	 MinHeapNode* left, * right, * top;
//
//	// Step 1: Create a min heap of capacity 
//	// equal to size.  Initially, there are 
//	// modes equal to size. 
//	 HuffManTree* hufftree = createAndBuildHuffTree(data, freq, size);
//
//	// Iterate while size of heap doesn't become 1 
//	while (!isSizeOne(hufftree)) {
//
//		// Step 2: Extract the two minimum 
//		// freq items from min heap 
//		left = extractMin(hufftree);
//		right = extractMin(hufftree);
//
//		// Step 3:  Create a new internal 
//		// node with frequency equal to the 
//		// sum of the two nodes frequencies. 
//		// Make the two extracted node as 
//		// left and right children of this new node. 
//		// Add this node to the min heap 
//		// '$' is a special value for internal nodes, not used 
//		top = newNode('$', left->freq + right->freq);
//
//		top->left = left;
//		top->right = right;
//
//		insertHuffTree(hufftree, top);
//	}
//
//	// Step 4: The remaining node is the 
//	// root node and the tree is complete. 
//	return extractMin(hufftree);
//}
//
//// Prints huffman codes from the root of Huffman Tree. 
//// It uses arr[] to store codes 
//void printCodes(MinHeapNode* root, int arr[], int top)
//
//{
//
//	// Assign 0 to left edge and recur 
//	if (root->left) {
//
//		arr[top] = 0;
//		printCodes(root->left, arr, top + 1);
//	}
//
//	// Assign 1 to right edge and recur 
//	if (root->right) {
//
//		arr[top] = 1;
//		printCodes(root->right, arr, top + 1);
//	}
//
//	// If this is a leaf node, then 
//	// it contains one of the input 
//	// characters, print the character 
//	// and its code from arr[] 
//	if (isLeaf(root)) {
//
//		printf("%c: ", root->data);
//		printArr(arr, top);
//	}
//}
//
//// The main function that builds a 
//// Huffman Tree and print codes by traversing 
//// the built Huffman Tree 
//void HuffmanCodes(char data[], int freq[], int size)
//
//{
//	// Construct Huffman Tree 
//	MinHeapNode* root= buildHuffmanTree(data, freq, size);
// 	// Print Huffman codes using 
//	// the Huffman tree built above 
//	int arr[MAX_TREE_HT], top = 0;
//
//	printCodes(root, arr, top);
//}
//
//
//// Driver program to test above functions 
//int main()
//{
//	
//	char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
//	int freq[] = { 1, 2, 12, 13, 16, 45 };
//
//	//char arr[] = { '0', '1', 'C', 'L', 'N' , 'T' };
//	//int freq[] = { 12, 6, 11, 5, 8, 12 };
//
//	int size = sizeof(arr) / sizeof(arr[0]);
//
//	HuffmanCodes(arr, freq, size);
//
//	return 0;
//}
//
//
//
//
//
//
//
