#include"ComFileText.h"





int main()
{

	
	FILE* file = fopen("Input.txt", "r");
	FILE* fileCompresss = fopen("InputCompress.txt", "w");
	HuffData data = ReadFileText(file);
	HuffMap map;
	//int size = sizeof(arr) / sizeof(arr[0]);
	int size = strlen(data.s);
	HuffmanCompress(file  , fileCompresss,  map , data, size);
	
	


	return 0;
}
