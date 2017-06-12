/*
 * ExampleSource.cpp
 *
 *  Created on: Jun 12, 2017
 *      Author: USER
 */

#include "ExampleSource.h"

ExampleSource::ExampleSource()
{
	count = 0;
	SetOutputChannelCount(2);
}

ExampleSource::~ExampleSource()
{
}

bool ExampleSource::NextStep()
{
	if(count < 10)
	{
		SetOutput(0, 3);
		SetOutput(1, count);
		count++;
		return true;
	}
	else
	{
		return false;
	}
}
