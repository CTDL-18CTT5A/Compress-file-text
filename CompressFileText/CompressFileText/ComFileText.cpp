#pragma once
#include"ComFileText.h"
#include<iostream>
#include<vector>
#include<sstream>
#include<bitset>
using namespace std;


NODE* newNode(char data, int freq)
{
	NODE* temp = new NODE;
	temp->pLeft = NULL;
	temp->pRight = NULL;
	temp->_text = data;
	temp->_freq = freq;
	return temp;

}




bool IsExist(char s, vector<char> str)
{
	for (vector<char>::iterator iter_name = str.begin(); iter_name != str.end(); iter_name++)
	{
		if (s == *iter_name)
			return true;
	}
	return false;

}

//Đếm số lương kí tự khác nhau trong file
int NumberOfCharFile(FILE* p)
{
	if (p == NULL)
		return 0;
	int count = 0;
	vector<char> s(100);
	char ch = getc(p);
	while (ch != EOF)
	{
		if (IsExist(ch, s) == false)
		{
			s.push_back(ch);
			count++;
		}
		ch = getc(p);
	}
	return count;
}

HuffData ReadFileText(FILE* p)
{
	if (p == NULL)
	{
		cout << "Khong the doc file";
		exit(0);
	}
	HuffData haf;
	int n = NumberOfCharFile(p);
	rewind(p);
	haf.s = new char[n];
	haf.wei = new int[n];
	char ch = getc(p);
	vector<char> s;
	int row = 0;
	while (ch != EOF)
	{
		if (IsExist(ch, s) == false)
		{
			s.push_back(ch);
			haf.wei[row] = 1;
			haf.s[row++] = ch;

		}
		else
		{
			int rowtemp = 0;
			for (vector<char>::iterator iter_name = s.begin(); iter_name != s.end(); iter_name++)
			{
				if (ch == *iter_name)
				{
					break;
				}
				rowtemp++;
			}
			haf.wei[rowtemp] += 1;
		}
		ch = getc(p);
	}
	haf.s[row] = NULL;
	return haf;

}


HuffmanTree* InitHuffTree(int size)
{
	HuffmanTree* hufftree = new HuffmanTree;

	hufftree->size = 0;

	hufftree->Array = (NODE**)malloc(size * sizeof(NODE*));

	return hufftree;

}

void SwapNode(NODE*& a, NODE*& b)
{
	NODE* temp = a;
	a = b;
	b = temp;
}

void MinHeapify(HuffmanTree* hufftree, int index)
{
	int min = index;
	int left = 2 * index + 1;
	int right = 2 * index + 2;

	if (left < hufftree->size && hufftree->Array[left]->_freq < hufftree->Array[min]->_freq)
	{
		min = left;
	}
	if (right < hufftree->size && hufftree->Array[right]->_freq < hufftree->Array[min]->_freq)
	{
		min = right;
	}
	if (min != index)
	{
		SwapNode(hufftree->Array[min], hufftree->Array[index]);
		MinHeapify(hufftree, min);
	}
}

NODE* getNodeMin(HuffmanTree* hufftree)
{
	NODE* node = hufftree->Array[0];
	//Lấy ra thì phải đưa cuối lên đầu và trừ bớt size(giống heap sort)
	hufftree->Array[0] = hufftree->Array[hufftree->size - 1];

	--hufftree->size;
	MinHeapify(hufftree, 0);

	return node;
}

void insertHuffTree(HuffmanTree* hufftree, NODE* newnode)
{
	++hufftree->size;
	//Vị trí cuối cùng để thêm vào phần tử mới
	int posInsert = hufftree->size - 1;

	//Nếu node insert nhỏ hơn root thì phải chuyển lên đầu để tiếp tục tạo root rồi chèn vào
	 //Nó sẽ so với root mà chưa cây con đó(tại vì khi thêm vào chỉ cần check tại nhanh đó thôi)
	//Đẩu thằng root nhỏ nhất luôn lên vị trí pos = 0;
	while (posInsert && newnode->_freq < hufftree->Array[(posInsert - 1) / 2]->_freq)
	{
		hufftree->Array[posInsert] = hufftree->Array[(posInsert - 1) / 2];
		posInsert = (posInsert - 1) / 2;
	}

	hufftree->Array[posInsert] = newnode;

}



void BuildMinHeap(HuffmanTree* hufftree)
{
	int n = hufftree->size - 1;
	for (int i = (n - 1) / 2; i >= 0; i--)
	{
		MinHeapify(hufftree, i);
	}
}

bool isMinSize(HuffmanTree* hufftree)
{
	return (hufftree->size == 1);
}


HuffmanTree* CreateHeapHuffman(HuffData map , int size)
{
	HuffmanTree* hufftree = InitHuffTree(size);
	hufftree->size = size;

	for (int i = 0; i < size; i++)
	{
		hufftree->Array[i] = newNode(map.s[i], map.wei[i]);
	}

	BuildMinHeap(hufftree);

	return hufftree;
}


NODE* builfHuffmanTree(HuffData map ,  int size)
{

	NODE* left, * right, * root;

	HuffmanTree* hufftree = CreateHeapHuffman(map , size);

	while (!isMinSize(hufftree))
	{
		left = getNodeMin(hufftree);
		right = getNodeMin(hufftree);


		root = newNode(' ', left->_freq + right->_freq);

		root->pLeft = left;
		root->pRight = right;
		
		insertHuffTree(hufftree, root);
	}

	//Sau khi đã liên kết lại hết với nhau thì chỉ cần lấy ra root

	return getNodeMin(hufftree);

}

bool isLeaf(NODE* root)
{
	return !(root->pLeft) && !(root->pRight);

}

void ArrayOutput(HuffMap &map , int index , int a[], int n)
{
	int i = 0;
	for (i; i < n; ++i)
	{
		map.BitArray[index][i] = a[i];
	}
	map.BitArray[index][i] = 2;

}

//Duyệt cây lưu dữ liệu vào map
void CompressFile(HuffMap &map , NODE* root, int arr[], int top)
{
	static int index = 0;
	// Assign 0 to left edge and recur 
	if (root->pLeft) 
	{

		arr[top] = 0;
		CompressFile(map ,root->pLeft, arr, top + 1);
	}

	// Assign 1 to right edge and recur 
	if (root->pRight) 
	{

		arr[top] = 1;
		CompressFile(map,  root->pRight, arr, top + 1);
	}

	
	//Index là biến đếm những node lá ứng với các kí tự
	if (isLeaf(root)) 
	{ 
		map.charater[index] = root->_text;
		map.BitArray[index] = new int[top];
		ArrayOutput(map, index , arr, top);
		index++;
	}
}


int convertBinaryToDecimal(long long n)
{
	int decimalNumber = 0, i = 0, remainder;
	while (n != 0)
	{
		remainder = n % 10;
		n /= 10;
		decimalNumber += remainder * pow(2, i);
		++i;
	}
	return decimalNumber;
}


//Lưu đống dữ liệu vào map
void HuffmanCompress(FILE *fileInput , FILE *fileOut , HuffMap &map , HuffData  data, int size)
{


	// Construct Huffman Tree 
	NODE* root = builfHuffmanTree(data, size);
	// Print Huffman codes using 
	// the Huffman tree built above 
	int arr[500];
	long long top = 0;
	map.BitArray = new int* [size];

	map.charater = new char[size];

	CompressFile(map , root, arr, top);

	WriteHeaderFile(fileOut, data);
	
	rewind(fileInput);

	//Lưu vào file
	char ch = getc(fileInput);
	//Dem so luong cac bit da ma hoa
	long long countBit8 = 0;
	//Tong cac bit da ghi ra
	long long countSumBit = 0;


	long long countBit = 0;
	long long sumBitOut = 0;
	char bit8[8];
	while (ch != EOF)
	{
		int j = 0;
		for (int i = 0; i < size; i++)
		{
			if (ch == map.charater[i])
			{
				while (map.BitArray[i][j] != 2)
				{
					countSumBit++;

					bit8[countBit++] = char(map.BitArray[i][j] + 48);
					//cout << map.BitArray[i][j];
					if (countBit == 8)
					{
						//cout << endl;
						stringstream sstream(bit8);
						std::bitset<8> bits;
						sstream >> bits;
						char textOutput = char(bits.to_ulong());
						fprintf(fileOut, "%c", textOutput);
						countBit = 0;
						countBit8 += 8;
					}

					j++;
				}

				break;
			}
			
		}
		ch = getc(fileInput);
	}

	int soBitLe = 0;
	for (int z = 0; z < countBit; z++)
	{
		fprintf(fileOut, "%c", bit8[z]);
		soBitLe++;
	}


	fprintf(fileOut, "%d", soBitLe);


	
}



void WriteHeaderFile(FILE* Output, HuffData data)
{
	int size = strlen(data.s);
	fprintf(Output, "%d", size);
	fprintf(Output, "$");


	for (int i = 0; i < size; i++)
	{
		fprintf(Output, "%c", data.s[i]);
		fprintf(Output, "%d", data.wei[i]);
		if (i != size - 1)
			fprintf(Output, "$");
		else
			fprintf(Output, "#");
	}

}


void ReadHeaderFile(FILE* fileIN, HuffData& data)
{
	char ch = getc(fileIN);
	//Get size
	int size = 0;
	while (ch != '$')
	{
		int t = int(ch - 48);
		size = size * 10 + t;
		ch = getc(fileIN);
	}
	data.s = new char[size];
	data.wei = new int[size];

	ch = getc(fileIN);
	//Save vào data
	int i = 0;
	while (ch != '#')
	{
		/*if (ch == '\n')
			ch = getc(fileIN);*/
		data.s[i] = ch;


		//Save wei
		int wei = 0;
		ch = getc(fileIN);
		while (ch != '$')
		{
			int t = int(ch - 48);
			wei = wei * 10 + t;
			ch = getc(fileIN);
			if (ch == '#')
				break;

		}
		data.wei[i] = wei;
		i++;
		if (ch == '#')
			break;
		ch = getc(fileIN);
	}
	data.s[i] = '\0';
}




long long getNumberOfFileAtIndex(FILE* in, int index)
{
	fseek(in, index, SEEK_SET);
	int thisPoint = ftell(in);
	fseek(in, 0, SEEK_END);
	long long maxsize = ftell(in);
	return maxsize - thisPoint;

}


//Hàm trả về vị trí cuối bit lưu số bit lẻ trả vệ  vị trí con trỏ ở bit lẻ
long long VitriLe(FILE* fileIN)
{

	fseek(fileIN, 0, SEEK_END);
	return ftell(fileIN) - 1;

}

void ConvertToBinArray(FILE* in, int indexStart, int* a , long long &k , long long viTriLe)
{
	long long EndFile = VitriLe(in);
	fseek(in, indexStart, SEEK_SET);
	int count = ftell(in);

	char c = getc(in);
	
	while (count != viTriLe)
	{
		for (int i = 7; i >= 0; --i)
		{
			char s = ((c & (1 << i)) ? '1' : '0');
			s -= 48;
			a[k] = s;
			k++;
			

		}
		c = getc(in);
		count++;
	}
	while (count!=EndFile)
	{
		a[k] = int(c - 48);
		k++;
		c = getc(in);
		count++;
	}
}


void Decode(FILE* in, FILE* out)
{
	//Lay Bit Le
	
	//______________Gán vtLe để lấy ra số bit lẻ_______________
	long long vtLe = VitriLe(in);
	fseek(in, vtLe, SEEK_SET);
	char ch = getc(in);
	int SoLuongBitLe = int(ch - 48);
	//Sau khi lưu số lượng bit lẻ vì vtLe đang nằm ở cuối file , ta trừ đi số bit lẻ => ra đc vị trí số lẻ đầu tiên.
	for(int z = 0; z < SoLuongBitLe; z++)
		vtLe -= 1;


	rewind(in);

	HuffData data;
	ReadHeaderFile(in, data);
	


	//____________Define max size of bit array_____________
	int StartIndex = ftell(in);
	long long sizeOfBit = getNumberOfFileAtIndex(in, StartIndex)*8;
	int* bit = new int[sizeOfBit];
	long long n = 0;
	rewind(in);
	fseek(in, StartIndex, SEEK_SET);

	//__________Chuyển kí tự về bit và lưu hết vào trong mảng bit____________
	ConvertToBinArray(in, StartIndex, bit , n , vtLe);
	//Tiếp tục lưu các bia thừa.

	int size = strlen(data.s);

	//_________Tạo ra map dữ liệu____________
	NODE* root = builfHuffmanTree(data, size);	
	HuffMap map;
	map.BitArray = new int* [size]; //SS
	map.charater = new char [size]; //SS
	int arr[500];
	long long top = 0;
	CompressFile(map, root, arr, top);

	//Nếu cây huffman không tồn tại(Tức chỉ có 1 phần tử trong file)
	cout << data.wei[0] << endl;
	if (size == 1)
	{
		int temp = 0;
		while (temp < data.wei[0])
		{
			fprintf(out, "%c",data.s[0]);
			temp++;
		}
		return;
	}

	//________Chuyển từ dãy bit sang string để dễ so sánh_________
	string* BitArray = new string[size];
	for (int i = 0; i < size; i++)
	{
		int j = 0;
		while (map.BitArray[i][j]!=2)
		{
			char test = char(map.BitArray[i][j]+48);
			cout << test;
			BitArray[i] += test;

			j++;
		}
		//cout << BitArray[i] << endl;
	}

	//Bắt đầu so sánh và ghi ra file
	string compare;
	for (int i = 0; i < n; i++)
	{
		compare += char(bit[i]+48);
		for (int k = 0; k < size; k++)
		{
			if (compare == BitArray[k])
			{
				//cout << map.BitArray[k][j];
				cout << map.charater[k];
				fprintf(out, "%c", map.charater[k]);

				compare.clear();
			}
		}
	}
	


}