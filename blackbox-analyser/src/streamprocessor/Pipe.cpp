/*
 * Pipe.cpp
 *
 *  Created on: 11Jun.,2017
 *      Author: NGrondi
 */

#include "Pipe.h"

Pipe::Pipe()
{
	Target = 0;
	TargetInputId = 0;
}

Pipe::~Pipe()
{
}

void Pipe::ConnectOutputNode(PipeTarget* t, int id)
{
	Target = t;
	TargetInputId = id;
}

void Pipe::SetInput(long int in)
{
	buffer.push(in);
	DrainBuffer();
}

bool Pipe::DrainBuffer()
{
	if(buffer.size() > 0)
	{
		if(Target != 0)
		{
			if(Target->IsReadyForNewInput(TargetInputId))
			{
				long int val = buffer.front();
				buffer.pop();
				Target->SetInput(TargetInputId, val);
				return true;
			}
		}
	}
	return false;
}

