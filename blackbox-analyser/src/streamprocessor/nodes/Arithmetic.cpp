/*
 * Arithmetic.cpp
 *
 *  Created on: Jun 12, 2017
 *      Author: USER
 */

#include "Arithmetic.h"

Arithmetic::Arithmetic(operator_enum o)
{
	SetInputChannelCount(2);
	SetOutputChannelCount(1);
	op = o;
}

Arithmetic::Arithmetic()
{
	SetInputChannelCount(2);
	SetOutputChannelCount(1);
	op = ADDITION;
}

Arithmetic::~Arithmetic()
{

}

void Arithmetic::SetProperty(string p, string v)
{
	if(p.compare("operator") == 0)
	{
		if(v.compare("+") == 0)
			op = ADDITION;
		else if(v.compare("-") == 0)
			op = SUBSTRACTION;
		else if(v.compare("*") == 0)
			op = MULTIPLICATION;
		else if(v.compare("/") == 0)
			op = DIVISION;
	}
}

void Arithmetic::ProcessStep()
{
	long int val = 0;
	if(op == ADDITION)
		val = InputValues[0] + InputValues[1];
	else if(op == SUBSTRACTION)
		val = InputValues[0] - InputValues[1];
	else if(op == MULTIPLICATION)
		val = InputValues[0] * InputValues[1];
	else if(op == DIVISION)
		val = InputValues[0] / InputValues[1];

	SetOutput(0, val);
}
