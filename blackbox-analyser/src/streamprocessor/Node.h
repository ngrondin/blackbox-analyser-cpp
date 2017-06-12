/*
 * Node.h
 *
 *  Created on: 11Jun.,2017
 *      Author: NGrondi
 */

#ifndef SRC_STREAMPROCESSOR_NODE_H_
#define SRC_STREAMPROCESSOR_NODE_H_

#include <vector>
#include "Pipe.h"
#include "PipeTarget.h"

using namespace std;

class Pipe;

class Node : PipeTarget
{
public:
	Node();
	virtual ~Node();

	void ConnectOutputPipe(Pipe* p);
	void SetInput(int id, long int val);

protected:
	long int OutputValue;
	bool HasNewOutput;
	bool HasOutput;
	vector<Pipe*> OutputPipes;

	bool Process();
};

#endif /* SRC_STREAMPROCESSOR_NODE_H_ */
