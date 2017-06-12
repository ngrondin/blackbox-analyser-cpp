/*
 * RollingAverage.h
 *
 *  Created on: 12Jun.,2017
 *      Author: NGrondi
 */

#ifndef SRC_STREAMPROCESSOR_NODES_ROLLINGAVERAGE_H_
#define SRC_STREAMPROCESSOR_NODES_ROLLINGAVERAGE_H_

#include <queue>
#include <stdlib.h>
#include "../Node.h"

using namespace std;

class RollingAverage: public Node
{
public:
	RollingAverage();
	RollingAverage(unsigned int ws);
	virtual ~RollingAverage();
	void SetProperty(string p, string v);

protected:
	unsigned int WindowSize;
	queue<long int> buffer;
	long int sum;
	unsigned int lag;

	void ProcessStep();
	bool ProcessDrain();
};

#endif /* SRC_STREAMPROCESSOR_NODES_ROLLINGAVERAGE_H_ */
