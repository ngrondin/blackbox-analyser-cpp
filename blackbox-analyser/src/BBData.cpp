#include "BBData.h"


BBData::BBData()
{
//	names = *(new vector<string>(50));
//	values = *(new vector<long int>(50));
}

BBData::~BBData()
{
	//names.clear();
}


void BBData::Initialize(vector<string> n)
{
	//names.push_back("pouet");
	names.clear();
	values.clear();
	for(unsigned int i = 0; i < n.size(); i++)
	{
		names.push_back(n[i]);
		values.push_back(0);
	}
}

void BBData::ZeroValues()
{
	for(unsigned int i = 0; i < values.size(); i++)
		values[i] = 0;
}




