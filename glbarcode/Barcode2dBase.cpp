/*  Barcode2dBase.cpp
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

#include "Barcode2dBase.h"

#include "Constants.h"
#include "DrawingPrimitives.h"

#include <list>


using namespace glbarcode::Constants;


namespace
{

	const double MIN_CELL_SIZE  = ( 0.01 * PTS_PER_INCH );

}


namespace glbarcode
{

	/*
	 * Barcode2dBase private data
	 */
	struct Barcode2dBase::PrivateData {
		int dummy;
	};


	Barcode2dBase::Barcode2dBase()
	{
		d = new Barcode2dBase::PrivateData;
	}


	Barcode2dBase::~Barcode2dBase()
	{
		delete d;
	}


	void Barcode2dBase::build( std::string raw_data,
				   double      w,
				   double      h )
	{
		std::string          cooked_data;   /* Preprocessed data */
		Simple2dMatrix<bool> encoded_data;  /* Encoded data matrix */

		clear();

		if ( raw_data.empty() )
		{
			set_empty_flag( true );
			set_data_valid_flag( false );

			set_width( 0 );
			set_height( 0 );
		}
		else
		{
			set_empty_flag( false );

			if ( !validate( raw_data ) )
			{
				set_data_valid_flag( false );

				set_width( 0 );
				set_height( 0 );
			}
			else
			{
				set_data_valid_flag( true );

				cooked_data  = preprocess( raw_data );
				encode( cooked_data, encoded_data );

				vectorize( encoded_data, w, h );

				set_width( w );
				set_height( h );
			}
		}
	}


	/*
	 * Default preprocess method
	 */
	std::string Barcode2dBase::preprocess( std::string raw_data )
	{
		return raw_data;
	}


	/*
	 * Default 2D vectorization method
	 */
	void Barcode2dBase::vectorize( const Simple2dMatrix<bool> & encoded_data,
				       double                     & w,
				       double                     & h )
	{

		/* determine size and establish scale */
		double scale;
		double min_w = MIN_CELL_SIZE*encoded_data.nx() + 2*MIN_CELL_SIZE;
		double min_h = MIN_CELL_SIZE*encoded_data.ny() + 2*MIN_CELL_SIZE;

		if ( (w <= min_w) && (h <= min_h) )
		{
			scale = MIN_CELL_SIZE;
			w     = min_w;
			h     = min_h;
		}
		else if ( w <= min_w )
		{
			scale = ( h / min_h ) * MIN_CELL_SIZE;
			w     = scale * min_w;
		}
		else if ( h <= min_h )
		{
			scale = ( w / min_w ) * MIN_CELL_SIZE;
			h     = scale * min_h;
		}
		else
		{
			scale = std::min( w / min_w, h / min_h ) * MIN_CELL_SIZE;
			w     = scale * min_w;
			h     = scale * min_h;
		}
		double cell_size  = scale;
		double quiet_size = scale;
		
		
		for ( int iy = 0; iy < encoded_data.ny(); iy++ )
		{
			for ( int ix = 0; ix < encoded_data.nx(); ix++ )
			{
				if ( encoded_data[iy][ix] )
				{
					add_box( quiet_size + ix*cell_size,
						 quiet_size + iy*cell_size,
						 cell_size,
						 cell_size );
				}
			}
		}

	}


}
