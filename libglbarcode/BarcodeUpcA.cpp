/*  BarcodeUpcA.cpp
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

#include "BarcodeUpcA.h"

#include <cctype>
#include <string>


namespace glbarcode
{

	/*
	 * Static UPC-A barcode creation method
	 */
	Barcode* BarcodeUpcA::create( std::string           data,
				      double                w,
				      double                h,
				      BarcodeOptions const& options )
	{
		return new BarcodeUpcA( data, w, h, options );
	}


	/*
	 * UPC-A barcode constructor
	 */
	BarcodeUpcA::BarcodeUpcA( std::string           data,
				  double                w,
				  double                h,
				  BarcodeOptions const& options )
	{
		m_end_bars_thresh  = 7;
		m_end_bars_modules = 7;

		build( data, w, h, options );
	}


	/*
	 * UPC-A validate number of digits, implements BarcodeUpcBase::validate_digits()
	 */
	bool BarcodeUpcA::validate_digits( int n_digits )
	{
		return (n_digits == 11);
	}


	/*
	 * UPC-A Pre-process data before encoding, implements Barcode::preprocess()
	 */
	std::string BarcodeUpcA::preprocess( std::string raw_data )
	{
		std::string cooked_data;

		for ( int i = 0; i < raw_data.size(); i++ )
		{
			if ( isdigit( raw_data[i] ) )
			{
				cooked_data += raw_data[i];
			}
		}

		m_first_digit_val = 0;
		return cooked_data;
	}


	/*
	 * UPC-A vectorize text, implements BarcodeUpcBase::vectorize_text()
	 */
	void BarcodeUpcA::vectorize_text( std::string display_text,
					  double size1, double size2,
					  double x1_left, double x1_right, double y1,
					  double x2_left, double x2_right, double y2 )
	{
		add_text( x2_left,  y2, size2, display_text.substr( 0, 1 ) );
		add_text( x1_left,  y1, size1, display_text.substr( 1, 5 ) );
		add_text( x1_right, y1, size1, display_text.substr( 6, 5 ) );
		add_text( x2_right, y2, size2, display_text.substr( 11, 1 ) );
	}

}
