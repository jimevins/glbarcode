/*  BarcodeCode39Ext.h
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

#ifndef glbarcode_BarcodeCode39Ext_h
#define glbarcode_BarcodeCode39Ext_h


#include "BarcodeCode39.h"


namespace glbarcode
{

	/**
	 * Code39Ext barcode, extends BarcodeCode39
	 */
	class BarcodeCode39Ext : public BarcodeCode39
	{
	public:
		static Barcode* create( std::string data,
					double      w,
					double      h,
					bool        text_flag,
					bool        checksum_flag );

	private:
		bool validate( std::string raw_data );

		std::string prepare_text( std::string raw_data );

		std::string preprocess( std::string raw_data );
	};

}


#endif // glbarcode_BarcodeCode39Ext_h
