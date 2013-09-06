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

#include <list>

#include "DrawingPrimitives.h"


namespace glbarcode
{

	/*
	 * Barcode private data
	 */
	struct Barcode::PrivateData {

		bool                   m_show_text_flag;  /**< Display text flag */
		bool                   m_checksum_flag;   /**< Add checksum flag */

		double                 m_w;               /**< Width of barcode (points) */
		double                 m_h;               /**< Height of barcode (points) */

		bool                   m_empty_flag;      /**< Empty data flag */
		bool                   m_data_valid_flag; /**< Valid data flag */

		std::list<DrawingPrimitive *> m_primitives;      /**< List of drawing primitives */

	};


	Barcode::Barcode()
	{
		d = new Barcode::PrivateData;

		d->m_show_text_flag  = false;
		d->m_checksum_flag   = false;

		d->m_w               = 0;
		d->m_h               = 0;

		d->m_empty_flag      = true;
		d->m_data_valid_flag = false;
	}


	Barcode::~Barcode()
	{
		clear(); /* Clear drawing primitives. */
		delete d;
	}


	Barcode& Barcode::show_text( bool value )
	{
		d->m_show_text_flag = value;
		return *this;
	}


	bool Barcode::show_text( void ) const
	{
		return d->m_show_text_flag;
	}


	Barcode& Barcode::checksum( bool value )
	{
		d->m_checksum_flag = value;
		return *this;
	}


	bool Barcode::checksum( void ) const
	{
		return d->m_checksum_flag;
	}


	void Barcode::render( Renderer &renderer )
	{
		renderer.render( d->m_w, d->m_h, d->m_primitives );
	}


	bool Barcode::is_empty( void )
	{
		return d->m_empty_flag;
	}


	void Barcode::set_empty_flag( bool value )
	{
		d->m_empty_flag = value;
	}


	bool Barcode::is_data_valid( void )
	{
		return d->m_data_valid_flag;
	}


	void Barcode::set_data_valid_flag( bool value )
	{
		d->m_data_valid_flag = value;
	}


	double Barcode::width( void )
	{
		return d->m_w;
	}


	double Barcode::height( void )
	{
		return d->m_h;
	}


	void Barcode::set_width( double w )
	{
		d->m_w = w;
	}


	void Barcode::set_height( double h )
	{
		d->m_h = h;
	}


	void Barcode::clear( void )
	{
		std::list<DrawingPrimitive*>::iterator primitive;

		for ( primitive = d->m_primitives.begin(); primitive != d->m_primitives.end(); primitive++ )
		{
			delete *primitive;
		}

		d->m_primitives.clear();
	}


	void Barcode::add_line( double x, double y, double w, double h )
	{
		d->m_primitives.push_back( new DrawingPrimitiveLine( x, y, w, h ) );
	}


	void Barcode::add_box( double x, double y, double w, double h )
	{
		d->m_primitives.push_back( new DrawingPrimitiveBox( x, y, w, h ) );
	}


	void Barcode::add_text( double x, double y, double fsize, std::string s )
	{
		d->m_primitives.push_back( new DrawingPrimitiveText( x, y, fsize, s ) );
	}


	void Barcode::add_ring( double x, double y, double r, double lwidth )
	{
		d->m_primitives.push_back( new DrawingPrimitiveRing( x, y, r, lwidth ) );
	}


	void Barcode::add_hexagon( double x, double y, double h )
	{
		d->m_primitives.push_back( new DrawingPrimitiveHexagon( x, y, h ) );
	}


}
