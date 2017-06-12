/*
 * Target.cpp
 *
 *  Created on: 11Jun.,2017
 *      Author: NGrondi
 */

#include "StreamTarget.h"

StreamTarget::StreamTarget(unsigned int c)
{
	SetInputChannelCount(c);
}

StreamTarget::~StreamTarget()
{
}

void StreamTarget::ProcessInputs()
{
	for(unsigned int i = 0; i < InputValues.size(); i++)
	{
		if(i > 0)
			cout << ",";
		cout << InputValues[i];
	}
	cout << "\n";
}



bool StreamTarget::Drain()
{
	return true;
}
