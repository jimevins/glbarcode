/*  Factory.cpp
 *
 *  Copyright (C) 2013-2014  Jim Evins <evins@snaught.com>
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
#include "BarcodeOnecode.h"
#include "BarcodeDataMatrix.h"
#include "BarcodeQrcode.h"


namespace glbarcode
{

	Factory::BarcodeTypeMap Factory::mBarcodeTypeMap;
	TypeIdList              Factory::mSupportedTypes;


	Factory::Factory()
	{
		/*
		 * Register built-in types.
		 */
		internalRegisterType( "code39",      &BarcodeCode39::create );
		internalRegisterType( "code39ext",   &BarcodeCode39Ext::create );
		internalRegisterType( "upc-a",       &BarcodeUpcA::create );
		internalRegisterType( "ean-13",      &BarcodeEan13::create );
		internalRegisterType( "postnet",     &BarcodePostnet::create );
		internalRegisterType( "postnet-5",   &BarcodePostnet5::create );
		internalRegisterType( "postnet-9",   &BarcodePostnet9::create );
		internalRegisterType( "postnet-11",  &BarcodePostnet11::create );
		internalRegisterType( "cepnet",      &BarcodeCepnet::create );
		internalRegisterType( "onecode",     &BarcodeOnecode::create );
		internalRegisterType( "datamatrix",  &BarcodeDataMatrix::create );
#if HAVE_QRENCODE
		internalRegisterType( "qrcode",      &BarcodeQrcode::create );
#endif
	}


	void Factory::init( void )
	{
		static Factory* singletonInstance = NULL;
		
		if ( singletonInstance == NULL )
		{
			singletonInstance = new Factory();
		}
	}


	void Factory::registerType( const std::string& typeId, Factory::BarcodeCreateFct fct )
	{
		init();

		internalRegisterType( typeId, fct );
	}


	bool Factory::isTypeSupported( const std::string& typeId )
	{
		init();

		BarcodeTypeMap::iterator i = mBarcodeTypeMap.find( typeId );

		return ( i != mBarcodeTypeMap.end() );
	}


	TypeIdList Factory::getSupportedTypes( void )
	{
		init();

		return mSupportedTypes;
	}


	Barcode* Factory::createBarcode( const std::string& typeId )
	{
		init();

		BarcodeTypeMap::iterator i = mBarcodeTypeMap.find( typeId );

		if( i != mBarcodeTypeMap.end() )
		{
			return i->second();
		}

		return NULL;
	}


	void Factory::internalRegisterType( const std::string& typeId, Factory::BarcodeCreateFct fct )
	{
		mBarcodeTypeMap[ typeId ] = fct;
		mSupportedTypes.push_back( typeId );
	}


}
