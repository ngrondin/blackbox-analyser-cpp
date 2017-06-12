/*
 * StreamSource.cpp
 *
 *  Created on: 11Jun.,2017
 *      Author: NGrondi
 */

#include "StreamSource.h"

StreamSource::StreamSource()
{

}

StreamSource::~StreamSource()
{
}

bool StreamSource::Drain()
{
	return DrainOutputs();
}
