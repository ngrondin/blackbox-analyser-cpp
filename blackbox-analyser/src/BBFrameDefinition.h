/*
 * BBFrameDefinition.h
 *
 *  Created on: May 21, 2017
 *      Author: USER
 */

#ifndef BBFRAMEDEFINITION_H_
#define BBFRAMEDEFINITION_H_

#include <string>
#include <vector>

using namespace std;

typedef enum frametype_enum {
	FRAME_TYPE_BAD	= 0,
	FRAME_TYPE_I	= 1,
	FRAME_TYPE_P	= 2,
	FRAME_TYPE_S	= 3,
	FRAME_TYPE_E	= 4
} frametype_enum;

typedef enum fieldencodingetype_enum {
    FIELD_ENCODING_SIGNED_VB       = 0, // Signed variable-byte
    FIELD_ENCODING_UNSIGNED_VB     = 1, // Unsigned variable-byte
    FIELD_ENCODING_TAG2_3S32       = 7,
    FIELD_ENCODING_TAG8_4S16       = 8,
    FIELD_ENCODING_NULL            = 9 // Nothing is written to the file, take value to be zero
} fieldencodingetype_enum;

class BBFrameDefinition {
public:
	vector<string> FieldNames;
	vector<fieldencodingetype_enum> FieldEncodings;

	BBFrameDefinition();
	virtual ~BBFrameDefinition();
	void SetNames(vector<string> names);
	void SetEncodings(vector<int> encodings);
	int GetFieldId(string fieldname);

};

#endif /* BBFRAMEDEFINITION_H_ */
