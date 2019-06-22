#include "fstream.h"
#include "string.h"

#define MaxNameLen 15

struct DataStruct
{
	char Name[MaxNameLen];
	int Score;
}

DataStrucrt* readDataFromFile(const char* FileName)
{
	DataStruct Data[5];
	ifstream fl;
	if(!fl.open(FileName))
		return false;
	for(int i=0;i<5;i++)
	{
		fl>>Data[i].Name;
		fl>>Data[i].Score;
	}
	fl.close();
	return Data[5];
}

void writeData2File(const char* FileName,const char* playerName,int score)
{
	DataStruct TempStruct;
	strcpy(TempStruct,)
}