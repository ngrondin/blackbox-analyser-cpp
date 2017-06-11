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
	names.clear();
	values.clear();
	for(unsigned int i = 0; i < n.size(); i++)
		AddValue(n[i], 0);
}

void BBData::AddValue(string name, long int value)
{
	names.push_back(name);
	values.push_back(value);
}

void BBData::ZeroValues()
{
	for(unsigned int i = 0; i < values.size(); i++)
		values[i] = 0;
}

long int BBData::GetValue(string name)
{
	for(unsigned int i = 0; i < names.size(); i++)
		if(names[i].compare(name) == 0)
			return values[i];
	return 0;
}

long int BBData::GetValue(int id)
{
	return values[id];
}



