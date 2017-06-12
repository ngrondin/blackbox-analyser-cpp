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

class PipeTarget {
public:
	PipeTarget();
	virtual ~PipeTarget();

	void AddInputPoint();
	bool IsReadyForNewInput(int id);
	virtual void SetInput(int id, long int val);

protected:
	int InputCount;
	vector<long int> InputValues;
	long int InputSetMask;

};

#endif /* SRC_STREAMPROCESSOR_PIPETARGET_H_ */
