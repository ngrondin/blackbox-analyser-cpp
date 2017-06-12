/*
 * ExampleSource.h
 *
 *  Created on: Jun 12, 2017
 *      Author: USER
 */

#ifndef BLACKBOX_ANALYSER_SRC_STREAMPROCESSOR_EXAMPLESOURCE_H_
#define BLACKBOX_ANALYSER_SRC_STREAMPROCESSOR_EXAMPLESOURCE_H_

#include "StreamSource.h"
class ExampleSource : public StreamSource
{
public:
	ExampleSource();
	virtual ~ExampleSource();
	bool NextStep();
private:
	int count;
};

#endif /* BLACKBOX_ANALYSER_SRC_STREAMPROCESSOR_EXAMPLESOURCE_H_ */
