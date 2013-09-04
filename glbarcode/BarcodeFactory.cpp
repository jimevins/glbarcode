/*  BarcodeFactory.cpp
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

#include "BarcodeFactory.h"

#include "BarcodeCode39.h"
#include "BarcodeCode39Ext.h"
#include "BarcodeUpcA.h"
#include "BarcodeEan13.h"
#include "BarcodePostnet.h"
#include "BarcodePostnet5.h"
#include "BarcodePostnet9.h"
#include "BarcodePostnet11.h"
#include "BarcodeCepnet.h"
#include "BarcodeOnecode.h"


namespace glbarcode
{

	BarcodeFactory::BarcodeTypeMap BarcodeFactory::m_barcode_type_map;
	std::list<std::string> BarcodeFactory::m_supported_types;


	BarcodeFactory* BarcodeFactory::instance( void )
	{
		static BarcodeFactory* singleton_instance = NULL;
		
		if ( singleton_instance == NULL )
		{
			singleton_instance = new BarcodeFactory();
			singleton_instance->init();
		}

		return singleton_instance;
	}


	void BarcodeFactory::register_type( std::string type_id, BarcodeFactory::BarcodeCreateFct fct )
	{
		m_barcode_type_map[ type_id ] = fct;
		m_supported_types.push_back( type_id );
	}


	bool BarcodeFactory::is_type_supported( std::string type_id )
	{
		BarcodeTypeMap::iterator i = m_barcode_type_map.find( type_id );

		return ( i != m_barcode_type_map.end() );
	}


	const std::list<std::string> BarcodeFactory::get_supported_types( void )
	{
		return m_supported_types;
	}


	Barcode* BarcodeFactory::create_barcode( std::string type_id )
	{
		BarcodeTypeMap::iterator i = m_barcode_type_map.find( type_id );

		if( i != m_barcode_type_map.end() )
		{
			return i->second();
		}

		return NULL;
	}


	void BarcodeFactory::init( void )
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
		register_type( "onecode",     &BarcodeOnecode::create );
	}


}
