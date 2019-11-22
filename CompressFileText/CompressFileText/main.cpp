#include"ComFileText.h"

#include<bitset>




int main()
{
	
	
	//FILE* file = fopen("Input.txt", "r");
	//FILE* fileCompresss = fopen("InputCompress.txt", "w");
	//HuffData data = ReadFileText(file);
	//HuffMap map;
	////int size = sizeof(arr) / sizeof(arr[0]);
	//int size = strlen(data.s);
	//HuffmanCompress(file  , fileCompresss,  map , data, size);
	

	FILE* header = fopen("TextHeader.txt", "r");
	FILE* out = fopen("ec", "w");
	//cout << VitriLe(header);
	


	/*HuffData dadada;
	ReadHeaderFile(header, dadada);
	int* a = new int[1000];*/
	Decode(header,out);



	return 0;
}
