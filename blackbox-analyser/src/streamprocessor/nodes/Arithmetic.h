/*
 * Arithmetic.h
 *
 *  Created on: Jun 12, 2017
 *      Author: USER
 */

#ifndef SRC_STREAMPROCESSOR_NODES_ARITHMETIC_H_
#define SRC_STREAMPROCESSOR_NODES_ARITHMETIC_H_

#include "../Node.h"

typedef enum operator_enum
{
	ADDITION,
	SUBSTRACTION,
	MULTIPLICATION,
	DIVISION
} operator_enum;

class Arithmetic : public Node
{
public:
	Arithmetic();
	Arithmetic(operator_enum o);
	virtual ~Arithmetic();
	void SetProperty(string p, string v);

protected:
	operator_enum op;

	void ProcessStep();
};

#endif /* SRC_STREAMPROCESSOR_NODES_ARITHMETIC_H_ */
