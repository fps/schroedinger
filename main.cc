#include <stdlib.h>
#include <iostream>

#include "schroedinger.h"

int main(int argc, char *argv[])
{
	std::vector<unsigned int> sizes;

	sizes.push_back(20);
	sizes.push_back(20);


	std::vector<field_data_t> spacing;

	spacing.push_back(hbar*hbar);
	spacing.push_back(hbar*hbar);


	std::cout << "init" << std::endl;

	Schroedinger schroedinger (sizes, spacing, hbar*hbar, 1.0);

	schroedinger.wave_field.set_data_2D (10,10,0,1);
	schroedinger.wave_field.set_data_2D (10,10,1,0);


	std::cout << "iterating" << std::endl;

	unsigned long long int count = 0;
	unsigned int total = 0;
	while (1) 
	{
		if (count == 0)
			std::cout << schroedinger.wave_field.get_data_2D (10, 10, 0) << std::endl; 
		schroedinger.iterate ();
		// std::cout << count++ << " ";
		count++;
		if (count >= 10) count = 0;
		if (total++ > 1000) break;
	}
}
