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

#include "Primitives.h"


namespace glbarcode
{

	/*
	 * Barcode private data
	 */
	struct Barcode::PrivateData {

		double                 m_w;               /**< Width of barcode (points) */
		double                 m_h;               /**< Height of barcode (points) */

		BarcodeOptions         m_options;         /**< Barcode options */

		bool                   m_empty_flag;      /**< Empty data flag */
		bool                   m_data_valid_flag; /**< Valid data flag */

		std::list<Primitive *> m_primitives;      /**< List of drawing primitives */

		/*
		 * Data to be made available to derived classes:
		 */
		std::string            m_raw_data;        /**< Raw data */
		std::string            m_cooked_data;     /**< Preprocessed data */
		std::string            m_display_text;    /**< Text data to be displayed */
		std::string            m_coded_data;      /**< Encoded data */
	};


	Barcode::Barcode()
	{
		d = new Barcode::PrivateData;
	}


	Barcode::~Barcode()
	{
		std::list<Primitive*>::iterator primitive;

		for ( primitive = d->m_primitives.begin(); primitive != d->m_primitives.end(); primitive++ )
		{
			delete *primitive;
		}

		delete d;
	}


	void Barcode::render( Renderer &renderer )
	{
		renderer.render( d->m_w, d->m_h, d->m_primitives );
	}


	bool Barcode::is_empty( void )
	{
		return d->m_empty_flag;
	}


	bool Barcode::is_data_valid( void )
	{
		return d->m_data_valid_flag;
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


	void Barcode::init( std::string           raw_data,
			    double                w,
			    double                h,
			    BarcodeOptions const& options )
	{
		d->m_raw_data      = raw_data;
		d->m_w             = w;
		d->m_h             = h;
		d->m_options       = options;

		if ( d->m_raw_data.empty() )
		{
			d->m_empty_flag = true;
			d->m_data_valid_flag = false;
		}
		else
		{
			d->m_empty_flag = false;

			if ( validate( d->m_raw_data ) )
			{
				d->m_data_valid_flag = true;

				d->m_cooked_data  = preprocess( d->m_raw_data );
				d->m_coded_data   = encode( d->m_cooked_data );

				d->m_display_text = prepare_text( d->m_raw_data );

				vectorize( d->m_coded_data, d->m_display_text );
			}
			else
			{
				d->m_data_valid_flag = false;
			}
		}
	}


	/*
	 * Default preprocess method
	 */
	std::string Barcode::preprocess( std::string raw_data )
	{
		return raw_data;
	}


	/*
	 * Default prepare_text method
	 */
	std::string Barcode::prepare_text( std::string raw_data )
	{
		return raw_data;
	}


	void Barcode::add_line( double x, double y, double w, double h )
	{
		d->m_primitives.push_back( new PrimitiveLine( x, y, w, h ) );
	}


	void Barcode::add_box( double x, double y, double w, double h )
	{
		d->m_primitives.push_back( new PrimitiveBox( x, y, w, h ) );
	}


	void Barcode::add_text( double x, double y, double fsize, std::string s )
	{
		d->m_primitives.push_back( new PrimitiveText( x, y, fsize, s ) );
	}


	void Barcode::add_ring( double x, double y, double r, double lwidth )
	{
		d->m_primitives.push_back( new PrimitiveRing( x, y, r, lwidth ) );
	}


	void Barcode::add_hexagon( double x, double y, double h )
	{
		d->m_primitives.push_back( new PrimitiveHexagon( x, y, h ) );
	}


	const std::string& Barcode::raw_data( void )
	{
		return d->m_raw_data;
	}


	const std::string& Barcode::cooked_data( void )
	{
		return d->m_cooked_data;
	}


	const std::string& Barcode::display_text( void )
	{
		return d->m_display_text;
	}


	const std::string& Barcode::coded_data( void )
	{
		return d->m_coded_data;
	}


	const BarcodeOptions& Barcode::options( void )
	{
		return d->m_options;
	}


}
