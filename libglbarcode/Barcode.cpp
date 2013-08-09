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

		for ( primitive = m_primitives.begin(); primitive != m_primitives.end(); primitive++ )
		{
			delete *primitive;
		}
	}


	bool Barcode::is_empty( void )
	{
		return m_empty_flag;
	}


	bool Barcode::is_data_valid( void )
	{
		return m_data_valid_flag;
	}


	double Barcode::get_w( void )
	{
		return m_w;
	}


	double Barcode::get_h( void )
	{
		return m_h;
	}


	void Barcode::init( std::string raw_data,
			    double      w,
			    double      h,
			    bool        text_flag,
			    bool        checksum_flag )
	{
		m_text_flag     = text_flag;
		m_checksum_flag = checksum_flag;
		m_w             = w;
		m_h             = h;
		m_raw_data      = raw_data;

		if ( m_raw_data.empty() )
		{
			m_empty_flag = true;
			m_data_valid_flag = false;
		}
		else
		{
			m_empty_flag = false;

			if ( validate( m_raw_data ) )
			{
				m_data_valid_flag = true;

				m_cooked_data  = preprocess( m_raw_data );
				m_coded_data   = encode( m_cooked_data );

				m_display_text = prepare_text( m_raw_data );

				vectorize( m_coded_data, m_display_text );
			}
			else
			{
				m_data_valid_flag = false;
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


	void Barcode::add_line( double x, double y, double length, double width )
	{
		m_primitives.push_back( new PrimitiveLine( x, y, length, width ) );
	}


	void Barcode::add_box( double x, double y, double w, double h )
	{
		m_primitives.push_back( new PrimitiveBox( x, y, w, h ) );
	}


	void Barcode::add_text( double x, double y, double fsize, std::string s )
	{
		m_primitives.push_back( new PrimitiveText( x, y, fsize, s ) );
	}


	void Barcode::add_ring( double x, double y, double r, double line_width )
	{
		m_primitives.push_back( new PrimitiveRing( x, y, r, line_width ) );
	}


	void Barcode::add_hexagon( double x, double y, double h )
	{
		m_primitives.push_back( new PrimitiveHexagon( x, y, h ) );
	}


	void Barcode::render( Renderer &renderer )
	{
		renderer.render( m_w, m_h, m_primitives );
	}

}
