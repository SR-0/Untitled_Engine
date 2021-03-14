#pragma once

#include <cstdlib>
#include <time.h>

class RandomNumberGenerator
{
public:

	RandomNumberGenerator(unsigned int seed = time(0))
	{
		srand(seed);
	}

public:

	void seed(unsigned int seed)
	{
		srand(seed);
	}

	unsigned int range(unsigned int start, unsigned int end)
	{
		return rand() % (unsigned int)(end + 1 - start) + start;
	}

};

#pragma once
