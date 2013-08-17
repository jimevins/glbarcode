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
#include "BarcodeCode39Ext.h"
#include "BarcodeUpcA.h"
#include "BarcodeEan13.h"
#include "BarcodePostnet.h"
#include "BarcodePostnet5.h"
#include "BarcodePostnet9.h"
#include "BarcodePostnet11.h"
#include "BarcodeCepnet.h"


namespace glbarcode
{

	Factory::BarcodeTypeMap Factory::m_barcode_type_map;
	std::list<std::string> Factory::m_supported_types;


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
		m_barcode_type_map[ type ] = fct;
		m_supported_types.push_back( type );
	}


	bool Factory::is_type_supported( std::string type )
	{
		BarcodeTypeMap::iterator i = m_barcode_type_map.find( type );

		return ( i != m_barcode_type_map.end() );
	}


	const std::list<std::string> Factory::get_supported_types( void )
	{
		return m_supported_types;
	}


	Barcode* Factory::create_barcode( std::string type,
					  std::string data,
					  double      w,
					  double      h,
					  bool        text_flag,
					  bool        checksum_flag )
	{
		BarcodeTypeMap::iterator i = m_barcode_type_map.find( type );

		if( i != m_barcode_type_map.end() )
		{
			return i->second( data, w, h, text_flag, checksum_flag );
		}

		return NULL;
	}


	void Factory::init( void )
	{
		register_type( "code39",      &BarcodeCode39::create );
		register_type( "code39ext",   &BarcodeCode39Ext::create );
		register_type( "upc-a",       &BarcodeUpcA::create );
		register_type( "ean-13",      &BarcodeEan13::create );
		register_type( "postnet",     &BarcodePostnet::create );
		register_type( "postnet-5",   &BarcodePostnet5::create );
		register_type( "postnet-9",   &BarcodePostnet9::create );
		register_type( "postnet-11",  &BarcodePostnet11::create );
		register_type( "cepnet",      &BarcodeCepnet::create );
	}


}
