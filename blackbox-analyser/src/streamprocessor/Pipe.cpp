/*
 * Pipe.cpp
 *
 *  Created on: 11Jun.,2017
 *      Author: NGrondi
 */

#include "Pipe.h"

Pipe::Pipe(Source* src, int SourceOutputChannel, Target* trg, int TargetInputChannel)
{
	PipeTarget = trg;
	PipeTargetInputChannel = TargetInputChannel;
	src->ConnectOutputPipe(this, SourceOutputChannel);
}

Pipe::~Pipe()
{
}


void Pipe::ConnectOutputNode(Target* target, int channel)
{
	PipeTarget = target;
	PipeTargetInputChannel = channel;
}


void Pipe::SetInput(long int in)
{
	if(PipeTarget != 0)
	{
		if(PipeTarget->IsReadyForNewInput(PipeTargetInputChannel))
		{
			long int val = in;
			if(buffer.size() > 0)
			{
				buffer.push(in);
				val = buffer.front();
				buffer.pop();
			}
			PipeTarget->SetInput(PipeTargetInputChannel, val);
		}
		else
		{
			buffer.push(in);
		}
	}
}

bool Pipe::Drain()
{
	int buffersize = buffer.size();
	bool FullyDrained = true;
	if(PipeTarget != 0)
	{
		if(buffersize > 0)
		{
			if(PipeTarget->IsReadyForNewInput(PipeTargetInputChannel))
			{
				long int val = buffer.front();
				buffer.pop();
				PipeTarget->SetInput(PipeTargetInputChannel, val);
				if(buffersize > 1)
					FullyDrained = false;
			}
		}
		else
		{
			FullyDrained = PipeTarget->Drain();
		}

	}
	return FullyDrained;
}

