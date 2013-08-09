/*  Factory.cpp
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

#include "Factory.h"

#include "BarcodeCode39.h"


namespace glbarcode
{

	Factory::BarcodeTypeMap Factory::barcode_type_map;


	/**
	 * Get singleton instance of Factory, create if uninitialized.
	 */
	Factory* Factory::instance( void )
	{
		static Factory* singleton_instance = NULL;
		
		if ( singleton_instance == NULL )
		{
			singleton_instance = new Factory();
			singleton_instance->init();
		}

		return singleton_instance;
	}


	void Factory::register_type( std::string type, Factory::BarcodeCreateFct fct )
	{
		barcode_type_map[ type ] = fct;
	}


	Barcode* Factory::create_barcode( std::string type,
					  std::string data,
					  double      w,
					  double      h,
					  bool        text_flag,
					  bool        checksum_flag )
	{
		BarcodeTypeMap::iterator i = barcode_type_map.find( type );

		if( i != barcode_type_map.end() )
		{
			return i->second( data, w, h, text_flag, checksum_flag );
		}

		return NULL;
	}


	void Factory::init( void )
	{
		register_type( "code39", &BarcodeCode39::create );
	}


}
