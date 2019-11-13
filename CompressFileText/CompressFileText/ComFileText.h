#pragma once
#include<iostream>
using namespace std;
struct NODE
{
	int _wei;
	char _text;
	NODE* pLeft;
	NODE* pRight;
};

struct HaffMap
{
	char *s;
	int *wei;
};

void init(NODE*& tree);

NODE* CreateNewRootHaffman();

bool IsExist(char s, char str[]);

HaffMap ReadFileText(FILE* p);

void OutputHaffMap(HaffMap haff);

void CreateTreeHaffman(NODE*& treeHaffman, FILE* p);