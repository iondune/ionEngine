/*
***************************************************************************
*                                                                         *
*                         Platform Independent                            *
*                   Bitmap Image Reader Writer Library                    *
*                                                                         *
* Author: Arash Partow - 2002                                             *
* URL: http://www.partow.net                                              *
*                                                                         *
* Note: This library only supports 24-bits per pixel bitmap format files. *
*                                                                         *
* Copyright notice:                                                       *
* Free use of the Platform Independent Bitmap Image Reader Writer Library *
* is permitted under the guidelines and in accordance with the most       *
* current version of the Common Public License.                           *
* http://www.opensource.org/licenses/cpl1.0.php                           *
*                                                                         *
***************************************************************************
*/

#pragma once

#include <ionCore.h>

#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <limits>
#include <cmath>
#include <cstdlib>


struct bitmap_file_header
{
	u16 type;
	u32 size;
	u16 reserved1;
	u16 reserved2;
	u32 off_bits;

	unsigned int struct_size()
	{
		return 
			sizeof(type)      +
			sizeof(size)      +
			sizeof(reserved1) +
			sizeof(reserved2) +
			sizeof(off_bits);
	}
};

struct bitmap_information_header
{
	u32 size;
	u32 width;
	u32 height;
	u16 planes;
	u16 bit_count;
	u32 compression;
	u32 size_image;
	u32 x_pels_per_meter;
	u32 y_pels_per_meter;
	u32 clr_used;
	u32 clr_important;

	unsigned int struct_size()
	{
		return
			sizeof(size)             +
			sizeof(width)            +
			sizeof(height)           +
			sizeof(planes)           +
			sizeof(bit_count)        +
			sizeof(compression)      +
			sizeof(size_image)       +
			sizeof(x_pels_per_meter) +
			sizeof(y_pels_per_meter) +
			sizeof(clr_used)         +
			sizeof(clr_important);
	}
};

inline void write_bih(std::ofstream & stream, bitmap_information_header const & bih);
inline void write_bfh(std::ofstream & stream, bitmap_file_header const & bfh);

class bitmap_image
{
public:

	bitmap_image(const unsigned int width, const unsigned int height)
		: file_name_(""), data_(0), bytes_per_pixel_(3), length_(0),
		width_(width), height_(height), row_increment_(0), channel_mode_(1)
	{
		create_bitmap();
	}

	~bitmap_image()
	{
		delete [] data_;
	}

	inline void set_pixel(const unsigned int x, const unsigned int y,
		const unsigned char red,
		const unsigned char green,
		const unsigned char blue)
	{
		data_[(y * row_increment_) + (x * bytes_per_pixel_ + 0)] = blue;
		data_[(y * row_increment_) + (x * bytes_per_pixel_ + 1)] = green;
		data_[(y * row_increment_) + (x * bytes_per_pixel_ + 2)] = red;
	}

	void save_image(const std::string& file_name)
	{
		std::ofstream stream(file_name.c_str(),std::ios::binary);

		if (!stream)
		{
			std::cout << "bitmap_image::save_image(): Error - Could not open file "  << file_name << " for writing!" << std::endl;
			return;
		}

		bitmap_file_header bfh;
		bitmap_information_header bih;

		bih.width            = width_;
		bih.height           = height_;
		bih.bit_count        = static_cast<unsigned short>(bytes_per_pixel_ << 3);
		bih.clr_important    =  0;
		bih.clr_used         =  0;
		bih.compression      =  0;
		bih.planes           =  1;
		bih.size             = 40;
		bih.x_pels_per_meter =  0;
		bih.y_pels_per_meter =  0;
		bih.size_image       = (((bih.width * bytes_per_pixel_) + 3) & 0xFFFC) * bih.height;

		bfh.type      = 19778;
		bfh.size      = 55 + bih.size_image;
		bfh.reserved1 = 0;
		bfh.reserved2 = 0;
		bfh.off_bits  = bih.struct_size() + bfh.struct_size();

		write_bfh(stream,bfh);
		write_bih(stream,bih);

		unsigned int padding = (4 - ((3 * width_) % 4)) % 4;
		char padding_data[4] = {0x0,0x0,0x0,0x0};
		for (unsigned int i = 0; i < height_; ++i)
		{
			unsigned char* data_ptr = data_ + (row_increment_ * (height_ - i - 1));
			stream.write(reinterpret_cast<char*>(data_ptr),sizeof(unsigned char) * bytes_per_pixel_ * width_);
			stream.write(padding_data,padding);
		}
		stream.close();
	}

private:

	void create_bitmap()
	{
		length_ = width_ * height_ * bytes_per_pixel_;
		row_increment_ = width_ * bytes_per_pixel_;
		if (0 != data_)
		{
			delete[] data_;
		}
		data_ = new unsigned char[length_];
	}

	std::string    file_name_;
	unsigned char* data_;
	unsigned int   bytes_per_pixel_;
	unsigned int   length_;
	unsigned int   width_;
	unsigned int   height_;
	unsigned int   row_increment_;
	u32   channel_mode_;
};

inline bool big_endian()
{
	unsigned int v = 0x01;
	return (1 != reinterpret_cast<char*>(&v)[0]);
}

inline unsigned short flip(u16 const & v)
{
	return ((v >> 8) | (v << 8));
}

inline unsigned int flip(u32 const & v)
{
	return
		((v & 0xFF000000) >> 0x18) |
		((v & 0x000000FF) << 0x18) |
		((v & 0x00FF0000) >> 0x08) |
		((v & 0x0000FF00) << 0x08);
}

template<typename T>
inline void write_to_stream(std::ofstream& stream,const T& t)
{
	stream.write(reinterpret_cast<const char*>(&t),sizeof(T));
}

inline void write_bfh(std::ofstream& stream, const bitmap_file_header& bfh)
{
	if (big_endian())
	{
		flip(bfh.type);
		flip(bfh.size);
		flip(bfh.reserved1);
		flip(bfh.reserved2);
		flip(bfh.off_bits);
	}

	write_to_stream(stream,bfh.type);
	write_to_stream(stream,bfh.size);
	write_to_stream(stream,bfh.reserved1);
	write_to_stream(stream,bfh.reserved2);
	write_to_stream(stream,bfh.off_bits);
}

inline void write_bih(std::ofstream& stream, const bitmap_information_header& bih)
{
	if (big_endian())
	{
		flip(bih.size);
		flip(bih.width);
		flip(bih.height);
		flip(bih.planes);
		flip(bih.bit_count);
		flip(bih.compression);
		flip(bih.size_image);
		flip(bih.x_pels_per_meter);
		flip(bih.y_pels_per_meter);
		flip(bih.clr_used);
		flip(bih.clr_important);
	}
	write_to_stream(stream,bih.size);
	write_to_stream(stream,bih.width);
	write_to_stream(stream,bih.height);
	write_to_stream(stream,bih.planes);
	write_to_stream(stream,bih.bit_count);
	write_to_stream(stream,bih.compression);
	write_to_stream(stream,bih.size_image);
	write_to_stream(stream,bih.x_pels_per_meter);
	write_to_stream(stream,bih.y_pels_per_meter);
	write_to_stream(stream,bih.clr_used);
	write_to_stream(stream,bih.clr_important);
}
