/*
 * BBLogStream.h
 *
 *  Created on: May 20, 2017
 *      Author: USER
 */

#ifndef BBLOGSTREAM_H_
#define BBLOGSTREAM_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stdlib.h>

#include "BBFrameDefinition.h"
#include "BBData.h"

using namespace std;


class BBLogStream {
public:
	BBLogStream(string filename);
	virtual ~BBLogStream();
	bool 	StartNextLog();
	bool	NextStep();
	int 	GetFieldID(string name);
	long int GetValue(int field);

private:
	BBFrameDefinition FrameDefinitions[3];
	BBData CurrentStepData;
	BBData CurrentSlowData;
	BBData HeaderData;
	int timedelta;
	int frameinterval;
	int minthrottle;
	//int pids[3][3];
	ifstream logfile;
	char peekedchar;
	bool haspeeked;
	long int streamcounter;
	bool logfinished;

	char 	ReadNextChar();
	char 	PeekNextChar();
	string 	ReadNextLine(char eol);
	bool 	ReadHeader();
	frametype_enum ReadNextFrame();
	long int ReadNextSignedVB();
	long int ReadNextUnsignedVB();
	void	 ReadNextTag8_4S16(long int* vals);
	void	 ReadNextTag2_3S32(long int* vals);
	vector<string> 	SplitString(string str, char delimiter);
	vector<int> 	SplitStringToInteger(string str, char delimiter);
	long int ApplyFieldSpecificRule(frametype_enum frametype, int field, long int value);
};

#endif /* BBLOGSTREAM_H_ */
