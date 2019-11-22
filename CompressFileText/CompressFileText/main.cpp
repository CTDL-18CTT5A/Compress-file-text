#include"ComFileText.h"

#include<bitset>




int main()
{
	
	//
	//FILE* file = fopen("Input2.txt", "r");
	//FILE* fileCompresss = fopen("InputCompress.txt", "w");
	//HuffData data = ReadFileText(file);
	//HuffMap map;
	////int size = sizeof(arr) / sizeof(arr[0]);
	//int size = strlen(data.s);
	//HuffmanCompress(file  , fileCompresss,  map , data, size);
	//

	FILE* header = fopen("InputCompress.txt", "r");
	FILE* out = fopen("ec.txt", "w");
	Decode(header, out);




	return 0;
}
