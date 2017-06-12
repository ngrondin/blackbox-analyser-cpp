/*
 * PipeTarget.h
 *
 *  Created on: 12Jun.,2017
 *      Author: NGrondi
 */

#ifndef SRC_STREAMPROCESSOR_PIPETARGET_H_
#define SRC_STREAMPROCESSOR_PIPETARGET_H_

#include <vector>

using namespace std;

class Target {
public:
	Target();
	virtual ~Target();

	bool IsReadyForNewInput(int channel);
	void SetInput(unsigned int channel, long int val);
	virtual bool Drain() = 0;

protected:
	vector<long int> InputValues;
	long int InputSetMask;

	void SetInputChannelCount(unsigned int c);
	virtual void ProcessInputs() = 0;
};

#endif /* SRC_STREAMPROCESSOR_PIPETARGET_H_ */
