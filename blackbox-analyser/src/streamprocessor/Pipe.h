/*
 * Pipe.h
 *
 *  Created on: 11Jun.,2017
 *      Author: NGrondi
 */

#ifndef SRC_STREAMPROCESSOR_PIPE_H_
#define SRC_STREAMPROCESSOR_PIPE_H_

#include <queue>
#include "Target.h"
#include "Source.h"

using namespace std;

class Source;
class Target;

class Pipe {
public:
	Pipe(Source* src, int SourceOutputChannel, Target* trg, int TargetInputChannel);
	virtual ~Pipe();

	void ConnectOutputNode(Target* target, int channel);
	void SetInput(long int in);
	bool Drain();

protected:
	Target* PipeTarget;
	int PipeTargetInputChannel;
	queue<long int> buffer;
};

#endif /* SRC_STREAMPROCESSOR_PIPE_H_ */
