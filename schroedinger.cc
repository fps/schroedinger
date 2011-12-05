#include <iostream>

#include "schroedinger.h"


Schroedinger::Schroedinger (const std::vector<unsigned int> &sizes, const std::vector<field_data_t> &spacing, field_data_t t, field_data_t d) :
	delta_t (t),
	damping (d),
	field_sizes (sizes),
	field_spacing (spacing),
	wave_field (Field (sizes, 2)),
	wave_derivative_field (Field (sizes, 2)),
	wave_laplace_field (Field (sizes, 2)),
	potential_field (Field (sizes, 1))
{
}

void Schroedinger::iterate () 
{
	// std::cout << std::endl;
	/*
		ok, let the fun start. we start by calculating the laplace field,
		cause that's what determines the time derivative of each value,
		which in turn then causes an updated wave function value
	*/
	
	/* we iterate over both dimensions except for the border cells */
	std::vector<unsigned int> pos (2);

	// std::cout << "laplace" << std::endl;

	for (pos[0] = 1; pos[0] < field_sizes[0] - 1; ++pos[0])
	{
		for (pos[1] = 1; pos[1] < field_sizes[1] - 1; ++pos[1])
		{
			/* then we calculate both second derivatives */
			wave_laplace_field.set_data (pos, 0, 0.5 * (1.0 / field_spacing [0])
			* (wave_field.get_data_2D (pos[0], pos[1] + 1, 0) + wave_field.get_data_2D (pos[0], pos[1] - 1, 0) - 2.0f * wave_field.get_data_2D (pos[0], pos[1], 0) 
			+ wave_field.get_data_2D (pos[0] + 1, pos[1], 0) + wave_field.get_data_2D (pos[0] - 1, pos[1], 0) - 2.0f * wave_field.get_data_2D (pos[0], pos[1], 0)));

			wave_laplace_field.set_data (pos, 1, 0.5 * (1.0 / field_spacing[1]) 
			* (wave_field.get_data_2D (pos[0], pos[1] + 1, 1) + wave_field.get_data_2D (pos[0], pos[1] - 1, 1) - 2.0f * wave_field.get_data_2D (pos[0], pos[1], 1) 
			+ wave_field.get_data_2D (pos[0] + 1, pos[1], 1) + wave_field.get_data_2D (pos[0] - 1, pos[1], 1) - 2.0f * wave_field.get_data_2D (pos[0], pos[1], 1)));

			// std::cout << "[" << wave_laplace_field.get_data (pos, 0) << "\t" << wave_laplace_field.get_data (pos, 1) << "]\t";
		}
		// std::cout << std::endl;
	}

	/* 
		ok, we got our laplace field done, now to updating the wave function.
		the laplacian of the wavefunction plus the potential times the wavefunction
		is equal to i*hbar times the time derivative.

		so by calculating the time derivative we know how to update our wavefunction
		for the next timestep
	*/

	// std::cout << "update wave" << std::endl;

	for (pos[0] = 1; pos[0] < field_sizes[0] - 1; ++pos[0])
	{
		for (pos[1] = 1; pos[1] < field_sizes[1] - 1; ++pos[1])
		{
			// std::cout << wave_field.get_data (pos, 0) << "\t";

			std::vector<field_data_t> tmp (2);
			
			// the potential field is real valued, saving us the hassle
			// of complex multiplication
			tmp[0] = potential_field.get_data (pos, 0) * wave_field.get_data (pos, 0);

			tmp[1] = potential_field.get_data (pos, 0) * wave_field.get_data (pos, 1);


			// then we add -h_bar^2/2m * laplace
			tmp[0] += (-1.0 * hbar * hbar  / (2.0 * elec_m)) * wave_laplace_field.get_data (pos, 0);

			tmp[1] += (-1.0 * hbar * hbar  / (2.0 * elec_m)) * wave_laplace_field.get_data (pos, 1);


			wave_field.set_data (pos, 0, wave_field.get_data (pos, 0) + delta_t * (tmp[1] / hbar));

			wave_field.set_data (pos, 1, wave_field.get_data (pos, 1) + delta_t * (-1.0 * tmp[0] / hbar));

		}
		// std::cout << std::endl;
	}
}
