#include <algorithm>
#include <fstream>
#include <iostream>

#include "Encoder.h"

using namespace std;

int main(int argc, char** argv)
{
    if (argc != 3)
	{
		cout << "Error: should be 2 arguments\n";
	}
	else
	{
		Encoder encoder;
		encoder.encode(argv[1], argv[2]);
	}
	return 0;
}
