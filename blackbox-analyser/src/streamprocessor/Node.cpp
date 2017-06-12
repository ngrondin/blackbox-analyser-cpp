/*
 * Node.cpp
 *
 *  Created on: 11Jun.,2017
 *      Author: NGrondi
 */

#include "Node.h"

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
	Process();
}

bool Node::Drain()
{
	return true;
}

void Node::Process()
{
	for(unsigned int i = 0; i < InputValues.size(); i++)
		SetOutput(i, InputValues[i]);
}

void Node::SetProperty(string p, string v)
{
}

Node::Node() {
}
