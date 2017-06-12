/*
 * PipeTarget.cpp
 *
 *  Created on: 12Jun.,2017
 *      Author: NGrondi
 */

#include "PipeTarget.h"

PipeTarget::PipeTarget()
{
	InputCount = 0;
	InputSetMask = 0;

}

PipeTarget::~PipeTarget()
{
}

void PipeTarget::AddInputPoint()
{
	InputCount++;
}

bool PipeTarget::IsReadyForNewInput(int id)
{
	if((InputSetMask & (1 << id)) == 0)
		return true;
	else
		return false;
}
