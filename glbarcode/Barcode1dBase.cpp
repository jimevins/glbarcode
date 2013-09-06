/*  Barcode1dBase.cpp
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

#include "Barcode1dBase.h"

#include <list>

#include "DrawingPrimitives.h"


namespace glbarcode
{

	/*
	 * Barcode1dBase private data
	 */
	struct Barcode1dBase::PrivateData {
		int dummy;
	};


	Barcode1dBase::Barcode1dBase()
	{
		d = new Barcode1dBase::PrivateData;
	}


	Barcode1dBase::~Barcode1dBase()
	{
		delete d;
	}


	void Barcode1dBase::build( std::string raw_data,
				   double      w,
				   double      h )
	{
		std::string cooked_data;     /* Preprocessed data */
		std::string display_text;    /* Text data to be displayed */
		std::string coded_data;      /* Encoded data */

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
				coded_data   = encode( cooked_data );
				display_text = prepare_text( raw_data );

				vectorize( coded_data, display_text, cooked_data, w, h );

				set_width( w );
				set_height( h );
			}
		}
	}


	/*
	 * Default preprocess method
	 */
	std::string Barcode1dBase::preprocess( std::string raw_data )
	{
		return raw_data;
	}


	/*
	 * Default prepare_text method
	 */
	std::string Barcode1dBase::prepare_text( std::string raw_data )
	{
		return raw_data;
	}


}
