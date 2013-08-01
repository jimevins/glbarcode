/*  Factory.h
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

#ifndef glbarcode_Factory_h
#define glbarcode_Factory_h

#include "Barcode.h"

#include <string>
#include <map>


namespace glbarcode
{
	/**
	 * Barcode Create Function Signature
	 */
	typedef Barcode* (*BarcodeCreateFct)(std::string data,
					     double      w,
					     double      h,
					     bool        text_flag,
					     bool        checksum_flag );

	/**
	 * Barcode Factory Class
	 */
	class Factory
	{
	public:
		static Factory* instance( void );

		static void register_type( std::string type, BarcodeCreateFct fct );

		static Barcode* create_barcode( std::string type,
						std::string data,
						double      w,
						double      h,
						bool        text_flag,
						bool        checksum_flag );

	private:
		static void init( void );

		typedef std::map<std::string,BarcodeCreateFct> BarcodeTypeMap;
		static BarcodeTypeMap barcode_type_map;

	};

}


#endif // glbarcode_Factory_h
