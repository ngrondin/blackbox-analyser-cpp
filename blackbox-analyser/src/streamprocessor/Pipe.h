/*
 * Pipe.h
 *
 *  Created on: 11Jun.,2017
 *      Author: NGrondi
 */

#ifndef SRC_STREAMPROCESSOR_PIPE_H_
#define SRC_STREAMPROCESSOR_PIPE_H_

#include <queue>
#include "PipeTarget.h"

using namespace std;


class Pipe {
public:
	Pipe();
	virtual ~Pipe();

	void ConnectOutputNode(PipeTarget* n, int id);
	void SetInput(long int in);
	bool DrainBuffer();

protected:
	PipeTarget* Target;
	int TargetInputId;
	queue<long int> buffer;


};

#endif /* SRC_STREAMPROCESSOR_PIPE_H_ */
