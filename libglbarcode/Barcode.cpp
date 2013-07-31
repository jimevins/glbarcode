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


bool glbarcode::Barcode::is_empty( void )
{
	return empty_flag;
}

bool glbarcode::Barcode::is_data_valid( void )
{
	return data_valid_flag;
}


double glbarcode::Barcode::get_w( void )
{
	return w;
}

double glbarcode::Barcode::get_h( void )
{
	return h;
}


void glbarcode::Barcode::build( bool        text_flag,
				bool        checksum_flag,
				double      w,
				double      h,
				std::string data )
{
	this->text_flag     = text_flag;
	this->checksum_flag = checksum_flag;
	this->w             = w;
	this->h             = h;
	this->data          = data;

	if ( data.empty() )
	{
		empty_flag = true;
		data_valid_flag = false;
	}
	else
	{
		empty_flag = false;

		if ( validate( data ) )
		{
			data_valid_flag = true;

			std::string cooked_data  = preprocess( data );
			std::string coded_data   = encode( cooked_data );

			std::string display_text = prepare_text( data );

			vectorize( coded_data, cooked_data, display_text );
		}
		else
		{
			data_valid_flag = false;
		}
	}
}


std::string glbarcode::Barcode::preprocess( std::string data )
{
	return data;
}


std::string glbarcode::Barcode::prepare_text( std::string data )
{
	return data;
}


void glbarcode::Barcode::add_box( double x, double y, double w, double h )
{
	primitives.push_back( new PrimitiveBox( x, y, w, h ) );
}

void glbarcode::Barcode::add_string( double x, double y, double fsize, std::string s )
{
	primitives.push_back( new PrimitiveText( x, y, fsize, s ) );
}

void glbarcode::Barcode::add_ring( double x, double y, double r, double line_width )
{
	primitives.push_back( new PrimitiveRing( x, y, r, line_width ) );
}

void glbarcode::Barcode::add_hexagon( double x, double y, double h )
{
	primitives.push_back( new PrimitiveHexagon( x, y, h ) );
}


void glbarcode::Barcode::render( Renderer &renderer )
{
	renderer.render( w, h, primitives );
}

