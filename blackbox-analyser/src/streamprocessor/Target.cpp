/*
 * PipeTarget.cpp
 *
 *  Created on: 12Jun.,2017
 *      Author: NGrondi
 */

#include "Target.h"

Target::Target()
{
	InputSetMask = 0;

}

Target::~Target()
{
}


bool Target::IsReadyForNewInput(int channel)
{
	if((InputSetMask & (1 << channel)) == 0)
		return true;
	else
		return false;
}

void Target::SetInput(unsigned int channel, long int val)
{
	if(channel < InputValues.size())
	{
		InputValues[channel] = val;
		InputSetMask |= (1 << channel);
		if(InputSetMask == ((1 << InputValues.size()) - 1))
		{
			ProcessInputs();
			InputSetMask = 0;
		}
	}
}

void Target::SetInputChannelCount(unsigned int c)
{
	for(unsigned int i = 0; i < c; i++)
		InputValues.push_back(0);
}
