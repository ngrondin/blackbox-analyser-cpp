/*
 * BBLogStream.cpp
 *
 *  Created on: May 20, 2017
 *      Author: USER
 */


#include "BBLogStream.h"


BBLogStream::BBLogStream(string filename)
{
	logfile.open(filename.c_str(), ios_base::in | ios_base::binary);
	peekedchar = 0;
	haspeeked = false;
	timedelta = 0;
	frameinterval = 1;
	streamcounter = 0;
	minthrottle = 1000;
	logfinished = true;
}

BBLogStream::~BBLogStream()
{
	logfile.close();
}

bool BBLogStream::StartNextLog()
{
	if (logfile.is_open())
	{
		if(ReadHeader())
		{
			logfinished = false;
			return true;
		}
	}
	return false;
}

bool BBLogStream::NextStep()
{
	frametype_enum frametype = FRAME_TYPE_BAD;
	while(frametype != FRAME_TYPE_P  &&  frametype != FRAME_TYPE_I  && !logfinished)
	{
		frametype = ReadNextFrame();
	}
	return !logfinished;
}

int BBLogStream::GetFieldID(string name)
{
	return FrameDefinitions[0].GetFieldId(name);
}


long int BBLogStream::GetValue(int field)
{
	return CurrentData.values[field];
}



bool BBLogStream::ReadHeader()
{
	char c;
	string headerline;
	bool quit = false;
	bool headerok = false;

	while(!quit)
	{
		c = PeekNextChar();
		if(c == 'H')
		{
			headerok = true;
			ReadNextChar();
			headerline = ReadNextLine('\n');
			vector<string> parts = SplitString(headerline, ':');

			if(parts[0].compare(" Field I name") == 0)
				FrameDefinitions[FRAME_TYPE_I].SetNames(SplitString(parts[1], ','));
			if(parts[0].compare(" Field P name") == 0)
				FrameDefinitions[FRAME_TYPE_P].SetNames(SplitString(parts[1], ','));
			if(parts[0].compare(" Field S name") == 0)
				FrameDefinitions[FRAME_TYPE_S].SetNames(SplitString(parts[1], ','));

			if(parts[0].compare(" Field I encoding") == 0)
				FrameDefinitions[FRAME_TYPE_I].SetEncodings(SplitStringToInteger(parts[1], ','));
			if(parts[0].compare(" Field P encoding") == 0)
				FrameDefinitions[FRAME_TYPE_P].SetEncodings(SplitStringToInteger(parts[1], ','));
			if(parts[0].compare(" Field S encoding") == 0)
				FrameDefinitions[FRAME_TYPE_S].SetEncodings(SplitStringToInteger(parts[1], ','));

			if(parts[0].compare(" P interval") == 0)
			{
				if(parts[1].compare("1/2") == 0)
					frameinterval = 2;
			}

			if(parts[0].compare(" minthrottle") == 0)
			{
				minthrottle = atoi(parts[1].c_str());
			};
		}
		else
		{
			if(headerok)
			{
				CurrentData.Initialize(FrameDefinitions[FRAME_TYPE_I].FieldNames);
			}
			quit = true;
		}
	}
	return headerok;
}


frametype_enum BBLogStream::ReadNextFrame()
{
	unsigned char c;
	frametype_enum frametype;

	c = ReadNextChar();
	while(c != 'I'  &&  c != 'P'  &&  c != 'E')
		c = ReadNextChar();

	if(c == 'I' || c == 'P')
	{
		if(c == 'I')
		{
			frametype = FRAME_TYPE_I;
			CurrentData.ZeroValues();
			timedelta = 0;
		}
		else
		{
			frametype = FRAME_TYPE_P;
		}

		for(unsigned int i = 0; i < FrameDefinitions[frametype].FieldEncodings.size(); i++)
		{
			fieldencodingetype_enum encoding = FrameDefinitions[frametype].FieldEncodings[i];

			long int values[4];
			int valuecount = 0;
			if(encoding == FIELD_ENCODING_SIGNED_VB)
			{
				values[0] = ReadNextSignedVB();
				valuecount = 1;
			}
			else if(encoding == FIELD_ENCODING_UNSIGNED_VB)
			{
				values[0] = ReadNextUnsignedVB();
				valuecount = 1;
			}
			else if(encoding == FIELD_ENCODING_TAG2_3S32)
			{
				ReadNextTag2_3S32(values);
				valuecount = 3;
			}
			else if(encoding == FIELD_ENCODING_TAG8_4S16)
			{
				ReadNextTag8_4S16(values);
				valuecount = 4;
			}
			else if(encoding == FIELD_ENCODING_NULL)
			{
				values[0] = 0;
				valuecount = 1;
			}

			for(int j = 0; j < valuecount; j++)
				CurrentData.values[i + j] += ApplyFieldSpecificRule(frametype, i + j, values[j]);

			i += (valuecount - 1);
		}
		unsigned char nextc = PeekNextChar();
		if(nextc != 'I' && nextc != 'S' && nextc != 'P' && nextc != 'E')
			frametype = FRAME_TYPE_BAD;
	}
	else if(c == 'E')
	{
		frametype = FRAME_TYPE_E;
		c = ReadNextChar();
		if(c == 255)
		{
			string line = ReadNextLine(0);
			if(line.compare("End of log") == 0)
				logfinished = true;
		}
	}
	return frametype;
}

long int BBLogStream::ApplyFieldSpecificRule(frametype_enum frametype, int field, long int value)
{
	long int newvalue = value;

	if(frametype == FRAME_TYPE_P)
	{
		if(field == 0)
		{
			newvalue = frameinterval;
		}

		if(field == 1)
		{
			timedelta += value;
			newvalue = timedelta;
		}
	}

	if(frametype == FRAME_TYPE_I)
	{
		if(FrameDefinitions[FRAME_TYPE_I].FieldNames[field].compare("rcCommand[3]") == 0)
		{
			newvalue = value + minthrottle;
		}
	}
	return newvalue;
}

char BBLogStream::ReadNextChar()
{
	char c;
	if(haspeeked)
	{
		c = peekedchar;
		haspeeked = false;
	}
	else
	{
		c = logfile.get();
		streamcounter++;
	}
	return c;
}

char BBLogStream::PeekNextChar()
{
	char c;
	if(haspeeked)
	{
		c = peekedchar;
	}
	else
	{
		c = ReadNextChar();
		peekedchar = c;
		haspeeked = true;
	}
	return c;
}


string BBLogStream::ReadNextLine(char eol)
{
	string line;
	char c;
	line.erase();
	do
	{
		c = ReadNextChar();
		if(c != eol)
			line.push_back(c);
	}
	while(c != eol);
	return line;
}

long int BBLogStream::ReadNextSignedVB()
{
	long int uval = ReadNextUnsignedVB();
	long int val = ((uval >> 1) ^ (-(uval  & 1)));
	return val;
}

long int BBLogStream::ReadNextUnsignedVB()
{
	unsigned long int uval = 0;
	long int val = 0;
	unsigned int bytecount = 0;
	bool hasmorebytes = true;
	while(hasmorebytes)
	{
		char c = ReadNextChar();
		if((c & 0x80) == 0)
			hasmorebytes = false;
		uval |= ((unsigned long int)(c & 0x7F)) << (7 * bytecount);
		bytecount++;
	}
	val = (signed long int)uval;
	return val;
}

void BBLogStream::ReadNextTag8_4S16(long int* vals)
{
	int selectors = 0;
	char c = ReadNextChar();
	int readbit = -1;
	int bitstoread = 0;
	selectors = c;
	for(int i = 0; i < 4; i++)
	{
		vals[i] = 0;
		switch(((selectors >> (2 * i)) & 0x03))
		{
			case 0: bitstoread = 0; break;
			case 1: bitstoread = 4; break;
			case 2: bitstoread = 8; break;
			case 3: bitstoread = 16; break;
		}
		for(int writebit = bitstoread - 1; writebit >= 0; writebit--)
		{
			if(readbit == -1)
			{
				c = ReadNextChar();
				readbit = 7;
			}
			vals[i] |= ((c >> readbit) & 0x01) << writebit;
			readbit--;
		}
		if(vals[i] & (1 << (bitstoread - 1)))
			vals[i] -= (1 << bitstoread);
	}
}

void BBLogStream::ReadNextTag2_3S32(long int* vals)
{
	int selector = 0;
	int selector2 = 0;
	char c = ReadNextChar();
	selector = (c >> 6) & 0x03;
	if(selector == 0)
	{
		vals[0] = (c >> 4) & 0x03;
		vals[1] = (c >> 2) & 0x03;
		vals[2] = (c >> 0) & 0x03;
	}
	else if(selector == 1)
	{
		vals[0] = c & 0x0F;
		c = ReadNextChar();
		vals[1] = (c >> 4) & 0x0F;
		vals[2] = c & 0x0F;
	}
	else if(selector == 2)
	{
		vals[0] = c & 0x3F;
		c = ReadNextChar();
		vals[1] = c & 0x3F;
		c = ReadNextChar();
		vals[2] = c & 0x3F;

	}
	else if(selector == 3)
	{
		selector2 = c & 0x03;
		for(int i = 0; i < 3; i++)
		{
			vals[i] = 0;
			for(int j = 0; j <= selector2; j++)
			{
				c = ReadNextChar();
				vals[i] |= (c << (j * 8));
			}
		}
	}
}


vector<string> BBLogStream::SplitString(string str, char delimiter)
{
	vector<string> internal;
	stringstream ss(str); // Turn the string into a stream.
	string tok;

	while(getline(ss, tok, delimiter))
		internal.push_back(tok);

	return internal;
}

vector<int> BBLogStream::SplitStringToInteger(string str, char delimiter)
{
	vector<int> internal;
	stringstream ss(str); // Turn the string into a stream.
	string tok;

	while(getline(ss, tok, delimiter))
	{
		internal.push_back(atoi(tok.c_str()));
	}

	return internal;
}
