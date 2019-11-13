#include<iostream>
#include<vector>
#include"ComFileText.h"
using namespace std;


int main()
{
	FILE* file = fopen("Input.txt", "r");
	HaffMap temp = ReadFileText(file);
	OutputHaffMap(temp);
}