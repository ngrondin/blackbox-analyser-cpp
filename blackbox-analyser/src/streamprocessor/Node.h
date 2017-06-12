/*
 * Node.h
 *
 *  Created on: 11Jun.,2017
 *      Author: NGrondi
 */

#ifndef SRC_STREAMPROCESSOR_NODE_H_
#define SRC_STREAMPROCESSOR_NODE_H_

#include <vector>
#include <string>
#include "Pipe.h"
#include "Target.h"
#include "Source.h"

using namespace std;

class Pipe;

class Node : public Target, public Source
{
public:
	Node();
	Node(unsigned int InputChannelCount, unsigned int OutputChannelCount);
	virtual ~Node();
	bool Drain();
	virtual void SetProperty(string p, string v);

protected:

	void ProcessInputs();
	virtual void ProcessStep();
	virtual bool ProcessDrain();
};

#endif /* SRC_STREAMPROCESSOR_NODE_H_ */
