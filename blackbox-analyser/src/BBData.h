/*
 * BBData.h
 *
 *  Created on: Jun 10, 2017
 *      Author: USER
 */

#ifndef BBDATA_H_
#define BBDATA_H_

#include "BBFrameDefinition.h"

using namespace std;

class BBData {
public:
	vector<long int> values;
	vector<string> names;

	BBData();
	virtual ~BBData();

	void Initialize(vector<string> n);
	void AddValue(string name, long int value);
	void ZeroValues();
	long int GetValue(string name);
	long int GetValue(int id);
};



#endif /* BBDATA_H_ */
