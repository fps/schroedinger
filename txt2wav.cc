#include <sndfile.h>
#include <iostream>
#include <fstream>
#include <cstdlib>

// argc[1] is the inputfilename
int main (int argc, char *argv[])
{
	if (argc < 3)
	{
		std::cout << "please specify input text file name and output wav filename" << std::endl;
		exit (EXIT_FAILURE);
	}
	std::ifstream stream (argv[1]);

	float tmp;

	SNDFILE* sndfile;
	SF_INFO sf_info;
	sf_info.samplerate = 48000;
	sf_info.channels = 1;
	sf_info.format = SF_FORMAT_WAV | SF_FORMAT_PCM_24;

	sndfile = sf_open (argv[2], SFM_WRITE, &sf_info); 

	while (true) 
	{
		stream >> tmp;
		if (!stream) break;

		std::cout << tmp << std::endl;
		sf_write_float (sndfile, &tmp, 1);
	} 
	sf_close (sndfile);

}
