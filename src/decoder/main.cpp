#include <algorithm>
#include <fstream>
#include <iostream>

#include "Decoder.h"

using namespace std;

int main(int argc, char** argv)
{
    if (argc != 3)
	{
		cout << "Error: should be 2 arguments\n";
	}
	else
	{
		Decoder decoder;
		decoder.decode(argv[1], argv[2]);
	}
	return 0;
}
