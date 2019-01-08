#include "gameManager.h"
#include "utility.h"

int customRand() {

	int deg;
	int brench = rand() % 2 + 1;
	if (brench == 1) {
		deg = rand() % 90 + 45;
	}
	else {
		deg = rand() % 90 + 225;
	}

	return deg;
}
