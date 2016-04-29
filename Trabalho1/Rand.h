#pragma once

#include <stdlib.h>

class Rand {
public:
	Rand(){}

	int get0toX(int X) {
		return (rand()) % (X + 1);
	}
};
