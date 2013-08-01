/*  Barcode.cpp
 *
 *  Copyright (C) 2013  Jim Evins <evins@snaught.com>
 *
 *  This file is part of glbarcode++.
 *
 *  glbarcode++ is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  glbarcode++ is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with glbarcode++.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Barcode.h"


namespace glbarcode
{

	Barcode::~Barcode()
	{
		std::list<Primitive*>::iterator primitive;

		for ( primitive = primitives.begin(); primitive != primitives.end(); primitive++ )
		{
			delete *primitive;
		}
	}


	bool Barcode::is_empty( void )
	{
		return empty_flag;
	}


	bool Barcode::is_data_valid( void )
	{
		return data_valid_flag;
	}


	double Barcode::get_w( void )
	{
		return w;
	}


	double Barcode::get_h( void )
	{
		return h;
	}


	void Barcode::init( std::string raw_data,
			    double      w,
			    double      h,
			    bool        text_flag,
			    bool        checksum_flag )
	{
		this->text_flag     = text_flag;
		this->checksum_flag = checksum_flag;
		this->w             = w;
		this->h             = h;
		this->raw_data      = raw_data;

		if ( raw_data.empty() )
		{
			empty_flag = true;
			data_valid_flag = false;
		}
		else
		{
			empty_flag = false;

			if ( validate( raw_data ) )
			{
				data_valid_flag = true;

				std::string cooked_data  = preprocess( raw_data );
				std::string coded_data   = encode( cooked_data );

				std::string display_text = prepare_text( raw_data );

				vectorize( coded_data, cooked_data, display_text );
			}
			else
			{
				data_valid_flag = false;
			}
		}
	}


	std::string Barcode::preprocess( std::string raw_data )
	{
		return raw_data;
	}


	std::string Barcode::prepare_text( std::string raw_data )
	{
		return raw_data;
	}


	void Barcode::add_box( double x, double y, double w, double h )
	{
		primitives.push_back( new PrimitiveBox( x, y, w, h ) );
	}


	void Barcode::add_string( double x, double y, double fsize, std::string s )
	{
		primitives.push_back( new PrimitiveText( x, y, fsize, s ) );
	}


	void Barcode::add_ring( double x, double y, double r, double line_width )
	{
		primitives.push_back( new PrimitiveRing( x, y, r, line_width ) );
	}


	void Barcode::add_hexagon( double x, double y, double h )
	{
		primitives.push_back( new PrimitiveHexagon( x, y, h ) );
	}


	void Barcode::render( Renderer &renderer )
	{
		renderer.render( w, h, primitives );
	}

}
