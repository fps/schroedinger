#ifndef SCHROED_HH
#define SCHROED_HH

#include <cmath>

#include "field.h"

/*
	some values :)
*/
#define planck_h (6.626e-34)

#define light_c (2.998e8)

static const double
	hbar = planck_h/(2*M_PI),
	elec_m = 9.109e-31,
	elec_q = 1.602e-19,
	coul_const = 8.988e9;

/*
	this class[struct] implements the time dependent schroedinger
	wave equation in 2 dimensions.
*/
struct Schroedinger
{
	field_data_t delta_t;

	field_data_t damping;

	std::vector <unsigned int> field_sizes;

	std::vector <field_data_t> field_spacing;

	/*  we need a field for the wave function values. complex */
	Field wave_field;

	/* and one for the time derivative of the wave_function. complex */
	Field wave_derivative_field;

	/* and one for the second space derivative [laplace] of the wave_function. complex */
	Field wave_laplace_field;

	/* and one for the potential.same dimension as above. real */
	Field potential_field;

	/* 
		sizes is the number of discrete cells per dimension	
		spacing is the distance along each dimension
	*/
	Schroedinger (const std::vector<unsigned int> &sizes, const std::vector<field_data_t> &spacing, field_data_t delta_t = 0.0000001, field_data_t damping = 9.9999999);

	/*
		do that thang
	*/
	void iterate ();
};

#endif
