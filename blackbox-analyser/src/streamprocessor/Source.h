/*
 * PipeSource.h
 *
 *  Created on: Jun 12, 2017
 *      Author: USER
 */

#ifndef SRC_STREAMPROCESSOR_PIPESOURCE_H_
#define SRC_STREAMPROCESSOR_PIPESOURCE_H_

#include <vector>

#include "Pipe.h"

using namespace std;

class Pipe;

class Source {
public:
	Source();
	virtual ~Source();

	void ConnectOutputPipe(Pipe* pipe, unsigned int outputchannel);

protected:
	vector<vector<Pipe*> > OutputToPipeMap;

	void SetOutputChannelCount(unsigned int c);
	void SetOutput(unsigned int channel, long int val);
	bool DrainOutputs();
};

#endif /* SRC_STREAMPROCESSOR_PIPESOURCE_H_ */
