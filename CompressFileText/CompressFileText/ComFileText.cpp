#include"ComFileText.h"
#include<iostream>
#include<vector>
using namespace std;

void init(NODE*& tree)
{
	tree = NULL;
}

//NODE* CreateNewRootHaffman()
//{
//
//}

bool IsExist(char s, vector<char> str)
{
	for (vector<char>::iterator iter_name = str.begin(); iter_name != str.end(); iter_name++)
	{
		if (s == *iter_name)
			return true;
	}
	return false;

}

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

HaffMap ReadFileText(FILE* p)
{
	if (p == NULL)
	{
		cout << "Khong the doc file";
		exit(0);
	}
	HaffMap haf;
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
			haf.wei[rowtemp]+=1;
		}
		ch = getc(p);
	}
	haf.s[row] = NULL;
	return haf;

}


void OutputHaffMap(HaffMap haff)
{
	for (int i = 0; i < strlen(haff.s); i++)
	{
		cout << haff.s[i] << "\t" << haff.wei[i] << endl;
	}
}

void CreateTreeHaffman(NODE*& treeHaffman , FILE *p)
{
	if (p == NULL)
	{
		cout << "File is not exits" << endl;
		return;
	}


}