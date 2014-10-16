#include <iostream>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include "lava.h"

int main(int argv, char *argc[]) {
	if (argv < 2) {
		std::cout << "need file name" << std::endl;
		return 1;
	}

	lava::Lava *lava = new lava::Lava(open(argc[1], O_RDONLY));
	lava->Eval();
	delete lava;
}
