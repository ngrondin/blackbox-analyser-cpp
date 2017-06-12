/*
 * PipeSource.cpp
 *
 *  Created on: Jun 12, 2017
 *      Author: USER
 */

#include "Source.h"

Source::Source()
{

}

Source::~Source()
{

}

void Source::ConnectOutputPipe(Pipe* pipe, unsigned int outputchannel)
{
	if(outputchannel < OutputToPipeMap.size())
		OutputToPipeMap[outputchannel].push_back(pipe);
}

void Source::SetOutput(unsigned int channel, long int val)
{
	if(channel < OutputToPipeMap.size())
	{
		for(unsigned int i = 0; i < OutputToPipeMap[channel].size(); i++)
			OutputToPipeMap[channel][i]->SetInput(val);
	}
}

void Source::SetOutputChannelCount(unsigned int c)
{
	for(unsigned int i = 0; i < c; i++)
	{
		vector<Pipe*> newvector = *(new vector<Pipe*>());
		OutputToPipeMap.push_back(newvector);
	}

}

bool Source::DrainOutputs()
{
	bool FullyDrained = true;
	for(unsigned int i = 0; i < OutputToPipeMap.size(); i++)
	{
		for(unsigned int j = 0; j < OutputToPipeMap[i].size(); j++)
		{
			if(!OutputToPipeMap[i][j]->Drain())
				FullyDrained = false;
		}
	}
	return FullyDrained;

}
