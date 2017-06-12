/*
 * Node.cpp
 *
 *  Created on: 11Jun.,2017
 *      Author: NGrondi
 */

#include "Node.h"

Node::Node()
{
}

Node::~Node()
{
}

Node::Node(unsigned int InputChannelCount, unsigned int OutputChannelCount)
{
	SetInputChannelCount(InputChannelCount);
	SetOutputChannelCount(OutputChannelCount);
}

void Node::ProcessInputs()
{
	ProcessStep();
}

bool Node::Drain()
{
	bool FullyDrained = true;
	if(ProcessDrain())
	{
		if(!DrainOutputs())
			FullyDrained = false;
	}
	return FullyDrained;
}

void Node::ProcessStep()
{
	for(unsigned int i = 0; i < InputValues.size(); i++)
		SetOutput(i, InputValues[i]);
}

bool Node::ProcessDrain()
{
	return true;
}

void Node::SetProperty(string p, string v)
{
}

