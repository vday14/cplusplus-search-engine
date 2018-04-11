#pragma once

class SeekEntry
	{
public:
    SeekEntry ( )
		{
		offset = 0;
		realLocation = 0;
		}

    SeekEntry (size_t offset_in, size_t realLocation_in) : offset(offset_in),
																		realLocation(realLocation_in)
		{}

	size_t offset;
	size_t realLocation;
	};