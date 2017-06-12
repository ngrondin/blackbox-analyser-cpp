/*
 * RollingAverage.cpp
 *
 *  Created on: 12Jun.,2017
 *      Author: NGrondi
 */

#include "RollingAverage.h"

RollingAverage::RollingAverage()
{
	SetInputChannelCount(1);
	SetOutputChannelCount(1);
	WindowSize = 1;
	sum = 0;
	lag = 0;
}


RollingAverage::RollingAverage(unsigned int ws)
{
	SetInputChannelCount(1);
	SetOutputChannelCount(1);
	WindowSize = ws;
	sum = 0;
	lag = 0;
}

RollingAverage::~RollingAverage()
{
}

void RollingAverage::SetProperty(string p, string v)
{
	if(p.compare("windowsize") == 0)
	{
		WindowSize = atoi(v.c_str());
	}
}

void RollingAverage::ProcessStep()
{
	long int val = InputValues[0];
	sum += val;
	buffer.push(val);
	if(buffer.size() > WindowSize)
	{
		long int dropval = buffer.front();
		sum -= dropval;
		buffer.pop();
	}
	long int avg = sum / buffer.size();
	if(lag < (WindowSize / 2))
		lag++;
	else
		SetOutput(0, avg);
}

bool RollingAverage::ProcessDrain()
{
	if(lag > 0)
	{
		long int dropval = buffer.front();
		sum -= dropval;
		buffer.pop();
		long int avg = sum / buffer.size();
		SetOutput(0, avg);
		lag--;
		return false;
	}
	else
	{
		return true;
	}
}
