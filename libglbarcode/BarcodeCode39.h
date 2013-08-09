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


#include "Barcode.h"


namespace glbarcode
{

	/**
	 * Code39 barcode, implements Barcode
	 */
	class BarcodeCode39 : public Barcode
	{
	public:
		static Barcode* create( std::string data,
					double      w,
					double      h,
					bool        text_flag,
					bool        checksum_flag );

	private:
		bool validate( std::string data );

		std::string encode( std::string canon_data );

		void vectorize( std::string coded_data,
				std::string display_text );
	};

}


#endif // glbarcode_BarcodeCode39_h
