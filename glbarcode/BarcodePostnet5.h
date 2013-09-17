/*  BarcodePostnet5.h
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

#ifndef glbarcode_BarcodePostnet5_h
#define glbarcode_BarcodePostnet5_h


#include "BarcodePostnet.h"


namespace glbarcode
{

	/**
	 * @class BarcodePostnet5 BarcodePostnet5.h glbarcode/BarcodePostnet5.h
	 *
	 * Postnet-5 barcode (ZIP only), extends BarcodePostnet
	 *
	 * @image html sample-postnet-5.svg "Sample 5 digit USPS Postnet Barcode"
	 *
	 */
	class BarcodePostnet5 : public BarcodePostnet
	{
	public:
		/**
		 * Static Postnet-5 barcode creation method
		 *
		 * Used by glbarcode::BarcodeFactory
		 */
		static Barcode* create( void );


	private:
		bool validate_digits( int n_digits );

	};

}


#endif // glbarcode_BarcodePostnet5_h
