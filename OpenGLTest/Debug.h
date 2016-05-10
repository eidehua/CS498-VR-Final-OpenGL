#pragma once

#include <stdio.h>
#include <fstream>

class Debug
{
public:
	/**
	* Initialize Static Debug attributes, open file, set verbose level
	* @param int (check .h for int descriptions)
	**/
	void init(int verbose)
	{
		this->output_level = verbose;
		this->debug_file.open("debug.txt", std::ios::trunc);
	}

	/**
	* Print to debug file, overloads the bitwise operator
	* @param anything that can be stringafied?
	**/
	template<typename T>
	void write(T string)
	{
		if (this->output_level == this->VERBOSE)
		{
			this->debug_file << string << std::endl;
		}
	}

	//Static Consts for verbosity level
	const static int VERBOSE = 1;
	const static int NOOUTPUT = 0;

	//Determines whether to print or not when called
	int output_level;

	//File to print too
	std::ofstream debug_file;
};

extern Debug debug;