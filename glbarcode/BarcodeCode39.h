/*  BarcodeCode39.h
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

#ifndef glbarcode_BarcodeCode39_h
#define glbarcode_BarcodeCode39_h


#include "Barcode1dBase.h"


namespace glbarcode
{

	/**
	 * @class BarcodeCode39 BarcodeCode39.h glbarcode/BarcodeCode39.h
	 *
	 * Code39 barcode, implements Barcode1dBase
	 */
	class BarcodeCode39 : public Barcode1dBase
	{
	public:
		/**
		 * Static Code39 barcode creation method
		 *
		 * Used by glbarcode::BarcodeFactory
		 */
		static Barcode* create( void );


	private:
		bool validate( std::string raw_data );

		std::string encode( std::string cooked_data );

		std::string prepare_text( std::string raw_data );

		void vectorize( std::string coded_data,
				std::string display_text,
				std::string cooked_data,
				double      &w,
				double      &h );
	};

}


#endif // glbarcode_BarcodeCode39_h