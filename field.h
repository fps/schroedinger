#ifndef SCHR_FIELD_HH
#define SCHR_FIELD_HH

#include <vector>

#include "global.h"

/*
	an n dimensional scalar field
*/
struct Field1D
{
	std::vector<field_data_t> field_data;

	/*
		the dimension of the scalar field is determined
		implicitly by the size of the field_sizes vector
	*/
	std::vector<unsigned int> field_sizes;

	Field1D (const std::vector<unsigned int> &sizes);

	inline void set_data (const std::vector<unsigned int> &pos, field_data_t value)
	{
		long long unsigned int flat_pos = 0;
		
		long unsigned int factor = 1;
	
		for (unsigned int i = 0; i < field_sizes.size (); ++i)
		{
			flat_pos += factor * pos[i];
			factor *= field_sizes[i];
		}
		field_data [flat_pos] = value;
	}

	inline field_data_t get_data (const std::vector<unsigned int> &pos)
	{
		long long unsigned int flat_pos = 0;
		
		long unsigned int factor = 1;
	
		for (unsigned int i = 0; i < field_sizes.size (); ++i)
		{
			flat_pos += factor * pos[i];
			factor *= field_sizes[i];
		}
		return field_data [flat_pos];
	}

	inline void set_data_2D (unsigned int pos_1, unsigned int pos_2, field_data_t value)
	{
		std::vector<unsigned int> pos (2);
		pos[0] = pos_1;
		pos[1] = pos_2;

		set_data (pos, value);
	}

	inline field_data_t get_data_2D (unsigned int pos_1, unsigned int pos_2)
	{
		std::vector<unsigned int> pos (2);
		pos[0] = pos_1;
		pos[1] = pos_2;

		return get_data (pos);
	}
};

/* an n-dimensional vectorfield with vectors from m-dimensional vectorspace */
struct Field
{
	unsigned int vectorspace_dimension;
	
	/* 
		n numbers denoting the size [elements] of the 
		field in each dimension. i.e. a three-dimensional field of
		six-dimensional vectors will have three numbers
	*/
	std::vector<unsigned int> field_sizes;

	/*
		each component of the vector data gets its own Field1D
	*/
	std::vector<Field1D> field_data;

	/* the dimension of the field is given implicitly by the sizes-vector */ 
	Field (const std::vector<unsigned int> &sizes, unsigned int vectorspace_dim = 2);

	inline field_data_t get_data (const std::vector<unsigned int> &pos, unsigned int component)
	{
		return field_data [component].get_data (pos);
	}

	inline void set_data (const std::vector<unsigned int> &pos, unsigned int component, field_data_t value)
	{
		field_data [component].set_data (pos, value);
	}

	inline field_data_t get_data_2D (unsigned int pos_1, unsigned int pos_2, unsigned int component)
	{
		return field_data [component].get_data_2D (pos_1, pos_2);
	}

	inline void set_data_2D (unsigned int pos_1, unsigned int pos_2, unsigned int component, field_data_t value)
	{
		field_data [component].set_data_2D (pos_1, pos_2, value);
	}

};

#endif
