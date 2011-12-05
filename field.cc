#include "field.h"

Field1D::Field1D (const std::vector<unsigned int>& sizes) :
	field_sizes (sizes)
{
	unsigned int dim = 1;

	for (unsigned int i = 0; i < sizes.size (); ++i)
	{
		dim *= sizes[i];
	}

	field_data.resize (dim);

	/* zero the stuff */
	for (unsigned int i = 0; i < dim; ++i)
	{
		field_data[i] = 0;
	}
}


Field::Field (const std::vector<unsigned int>& sizes, unsigned int vectorspace_dim) :
	vectorspace_dimension (vectorspace_dim),
	field_sizes (sizes)
{
	for (unsigned int i = 0; i < vectorspace_dim; ++i)
	{
		field_data.push_back (Field1D (sizes));
	}
}



