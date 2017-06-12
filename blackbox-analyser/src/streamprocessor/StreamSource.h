/*
 * StreamSource.h
 *
 *  Created on: 11Jun.,2017
 *      Author: NGrondi
 */

#ifndef SRC_STREAMPROCESSOR_STREAMSOURCE_H_
#define SRC_STREAMPROCESSOR_STREAMSOURCE_H_

#include <vector>
#include "Source.h"

using namespace std;

class StreamSource : public Source
{
public:
	StreamSource();
	virtual ~StreamSource();
	virtual bool NextStep() = 0;;
	bool Drain();
};

#endif /* SRC_STREAMPROCESSOR_STREAMSOURCE_H_ */
