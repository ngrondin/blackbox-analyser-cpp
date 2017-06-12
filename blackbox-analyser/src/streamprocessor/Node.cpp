/*
 * Node.cpp
 *
 *  Created on: 11Jun.,2017
 *      Author: NGrondi
 */

#include "Node.h"

Node::Node()
{
	OutputValue = 0;
	HasOutput = false;
	HasNewOutput = false;
}

Node::~Node()
{
	// TODO Auto-generated destructor stub
}

void Node::SetInput(int id, long int val)
{
	if(id < InputCount)
	{
		InputValues[id] = val;
		InputSetMask |= (1 << id);
		if(InputSetMask == ((1 << InputCount) - 1))
		{
			Process();
			if(HasNewOutput)
			{
				for(unsigned int i = 0; i < OutputPipes.size(); i++)
					OutputPipes[i]->SetInput(OutputValue);
			}
			InputSetMask = 0;
		}
	}
}

void Node::ConnectOutputPipe(Pipe* p)
{
	OutputPipes.push_back(p);
}

