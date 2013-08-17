/*  BarcodePostnet9.h
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

#ifndef glbarcode_BarcodePostnet9_h
#define glbarcode_BarcodePostnet9_h


#include "BarcodePostnet.h"


namespace glbarcode
{

	/**
	 * Postnet-9 barcode (ZIP+4 only), extends BarcodePostnet
	 */
	class BarcodePostnet9 : public BarcodePostnet
	{
	public:
		/**
		 * Static Postnet-9 barcode creation method
		 *
		 * Used by glbarcode::Factory
		 */
		static Barcode* create( std::string data,
					double      w,
					double      h,
					bool        text_flag,
					bool        checksum_flag );

		/**
		 * Postnet-9 barcode constructor
		 */
		BarcodePostnet9( std::string data,
				 double      w,
				 double      h,
				 bool        text_flag,
				 bool        checksum_flag );

	private:
		bool validate_digits( int n_digits );

	};

}


#endif // glbarcode_BarcodePostnet9_h
