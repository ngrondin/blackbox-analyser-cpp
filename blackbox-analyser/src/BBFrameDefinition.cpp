/*
 * BBFrameDefinition.cpp
 *
 *  Created on: May 21, 2017
 *      Author: USER
 */

#include "BBFrameDefinition.h"

BBFrameDefinition::BBFrameDefinition()
{
}

BBFrameDefinition::~BBFrameDefinition()
{

}

void BBFrameDefinition::SetNames(vector<string> names)
{
	FieldNames.clear();
	for(unsigned int i = 0; i < names.size(); i++)
		FieldNames.push_back(names[i]);
}

void BBFrameDefinition::SetEncodings(vector<int> encodings)
{
	FieldEncodings.clear();
	for(unsigned int i = 0; i < encodings.size(); i++)
		FieldEncodings.push_back((fieldencodingetype_enum)encodings[i]);
}

int BBFrameDefinition::GetFieldId(string fieldname)
{

	for(unsigned int i = 0; i < FieldNames.size(); i++)
		if(FieldNames[i].compare(fieldname) == 0)
			return i;
	return -1;
}
