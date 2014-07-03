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
#include "BarcodeOnecode.h"
#include "BarcodeDataMatrix.h"
#include "BarcodeQrcode.h"


namespace glbarcode
{

	Factory::BarcodeTypeMap Factory::mBarcodeTypeMap;
	std::vector<std::string> Factory::mSupportedTypes;


	Factory* Factory::instance( void )
	{
		static Factory* singletonInstance = NULL;
		
		if ( singletonInstance == NULL )
		{
			singletonInstance = new Factory();
			singletonInstance->init();
		}

		return singletonInstance;
	}


	void Factory::registerType( std::string typeId, Factory::BarcodeCreateFct fct )
	{
		mBarcodeTypeMap[ typeId ] = fct;
		mSupportedTypes.push_back( typeId );
	}


	bool Factory::isTypeSupported( std::string typeId )
	{
		BarcodeTypeMap::iterator i = mBarcodeTypeMap.find( typeId );

		return ( i != mBarcodeTypeMap.end() );
	}


	const std::vector<std::string> Factory::getSupportedTypes( void )
	{
		return mSupportedTypes;
	}


	Barcode* Factory::createBarcode( std::string typeId )
	{
		BarcodeTypeMap::iterator i = mBarcodeTypeMap.find( typeId );

		if( i != mBarcodeTypeMap.end() )
		{
			return i->second();
		}

		return NULL;
	}


	void Factory::init( void )
	{
		registerType( "code39",      &BarcodeCode39::create );
		registerType( "code39ext",   &BarcodeCode39Ext::create );
		registerType( "upc-a",       &BarcodeUpcA::create );
		registerType( "ean-13",      &BarcodeEan13::create );
		registerType( "postnet",     &BarcodePostnet::create );
		registerType( "postnet-5",   &BarcodePostnet5::create );
		registerType( "postnet-9",   &BarcodePostnet9::create );
		registerType( "postnet-11",  &BarcodePostnet11::create );
		registerType( "cepnet",      &BarcodeCepnet::create );
		registerType( "onecode",     &BarcodeOnecode::create );
		registerType( "datamatrix",  &BarcodeDataMatrix::create );
#if HAVE_QRENCODE
		registerType( "qrcode",      &BarcodeQrcode::create );
#endif
	}


}
