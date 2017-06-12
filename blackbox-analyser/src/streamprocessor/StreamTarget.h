/*
 * Target.h
 *
 *  Created on: 11Jun.,2017
 *      Author: NGrondi
 */

#ifndef SRC_STREAMPROCESSOR_TARGET_H_
#define SRC_STREAMPROCESSOR_TARGET_H_

#include <iostream>
#include "Target.h"

using namespace std;

class StreamTarget : public Target
{
public:
	StreamTarget(unsigned int c);
	virtual ~StreamTarget();
	bool Drain();

protected:
	void ProcessInputs();
};

#endif /* SRC_STREAMPROCESSOR_TARGET_H_ */
