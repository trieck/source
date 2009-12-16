//////////////////////////////////////////////////////////////////////////////
//
// RANDOM.H : Random number generators
//
// Quick-and-dirty linear congruential generator 
// Based on Numerical Recipes, 2d ed., p. 284.
//
// Adapted from Allen Akin.
//
// BEGIN_COPYRIGHT
//
// Copyright (C) 1999  Allen Akin   All Rights Reserved.
//
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use,
// copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following
// conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the
// Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY
// KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL ALLEN AKIN BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
// AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
// OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//
// END_COPYRIGHT
//

#ifndef __RANDOM_H__
#define __RANDOM_H__

///////////////////////////////////////////////////////////////////////////////
class Random32 
{
public:
// Construction / Destruction
	Random32(uint32_t seed): i(seed) {}
	Random32(): i(1) {}
	virtual ~Random32(){}
	
// Interface		
	inline uint32_t next() {
		i = 1664525 * i + 1013904223;
		return i;
	}
	
// Implementation	
private:
	uint32_t i;
};

///////////////////////////////////////////////////////////////////////////////
// RandomDouble:  Returns a random floating-point value in the closed
// interval [0.0, 1.0].
class RandomDouble : public Random32 
{
public:
// Construction / Destruction
	RandomDouble(uint32_t seed):  Random32(seed) {}
	RandomDouble(): Random32() {}
	~RandomDouble() {}
		
// Interface
	inline double next() {
		return static_cast<double>(Random32::next()) / 4294967295.0;
	}
	
// Implementation
}; 

#endif // __RANDOM_H__