/*  BarcodePostnet9.cpp
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

#include "BarcodePostnet9.h"


namespace glbarcode
{

	/*
	 * Static Postnet-9 barcode creation method
	 */
	Barcode* BarcodePostnet9::create( std::string           data,
					  double                w,
					  double                h,
					  BarcodeOptions const& options )
	{
		return new BarcodePostnet9( data, w, h, options );
	}


	/*
	 * Postnet-9 barcode constructor
	 */
	BarcodePostnet9::BarcodePostnet9( std::string           data,
					  double                w,
					  double                h,
					  BarcodeOptions const& options )
	{
		build( data, w, h, options );
	}


	/*
	 * Postnet-9 validation of number of digits, overrides BarcodePostnet::validate_digits()
	 */
	bool BarcodePostnet9::validate_digits( int n_digits )
	{
		return n_digits == 9; /* Zip + 4 */
	}

}
