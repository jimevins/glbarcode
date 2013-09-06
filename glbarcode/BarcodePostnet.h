/*  BarcodePostnet.h
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

#ifndef glbarcode_BarcodePostnet_h
#define glbarcode_BarcodePostnet_h


#include "Barcode1dBase.h"


namespace glbarcode
{

	/**
	 * @class BarcodePostnet BarcodePostnet.h glbarcode/BarcodePostnet.h
	 *
	 * Postnet barcode (All USPS sizes: ZIP, ZIP+4, ZIP+4+DC), implements Barcode1dBase
	 */
	class BarcodePostnet : public Barcode1dBase
	{
	public:
		/**
		 * Static Postnet barcode creation method
		 *
		 * Used by glbarcode::BarcodeFactory
		 */
		static Barcode* create( void );


	protected:
		/**
		 * Validate number of digits
		 */
		virtual bool validate_digits( int n_digits );


	private:
		bool validate( std::string raw_data );

		std::string encode( std::string cooked_data );

		void vectorize( std::string coded_data,
				std::string display_text,
				std::string cooked_data,
				double      &w,
				double      &h );

	};

}


#endif // glbarcode_BarcodePostnet_h
