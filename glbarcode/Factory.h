/*  Factory.h
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

#ifndef glbarcode_Factory_h
#define glbarcode_Factory_h

#include "Barcode.h"

#include <string>
#include <vector>
#include <map>


/**
 * Barcode factory base for CAPI
 */
extern "C" struct gbcFactory {};


namespace glbarcode
{
	/**
	 * @class Factory Factory.h glbarcode/Factory.h
	 *
	 * Singleton Barcode factory class.
	 */
	class Factory : public gbcFactory
	{

	public:
		/**
		 * Barcode creation function signature.
		 */
		typedef Barcode* (*BarcodeCreateFct)( void );


	private:
		/**
		 * Barcode factory constructor
		 */
		Factory();


	public:
		/**
		 * Initialize barcode factory.
		 *
		 * Initializes the barcode factory and registers all built-in Barcode types.  It
		 * is optional for an application to call init(), because libglabels++ will automatically
		 * initialize the factory on demand.
		 */
		static void init( void );

		
		/**
		 * Create barcode based on type ID string.
		 *
		 * @param[in] typeId Barcode type ID string
		 */
		static Barcode* createBarcode( const std::string& typeId );


		/**
		 * Register barcode type ID.
		 *
		 * @param[in] typeId Barcode type ID string
		 * @param[in] fct Function to create barcode object of concrete Barcode class
		 */
		static void registerType( const std::string& typeId, BarcodeCreateFct fct );


		/**
		 * Is barcode type supported?
		 */
		static bool isTypeSupported( const std::string& typeId );


		/**
		 * Get list of supported types.
		 */
		static const std::vector<std::string> getSupportedTypes( void );


	private:
		/**
		 * Internal register barcode type ID.
		 *
		 * @param[in] typeId Barcode type ID string
		 * @param[in] fct Function to create barcode object of concrete Barcode class
		 */
		static void internalRegisterType( const std::string& typeId, BarcodeCreateFct fct );


		/**
		 * Map barcode type strings to creation functions.
		 */
		typedef std::map<std::string,BarcodeCreateFct> BarcodeTypeMap;
		static BarcodeTypeMap mBarcodeTypeMap;


		/**
		 * Supported barcode types.
		 */
		static std::vector<std::string> mSupportedTypes;

	};

}


#endif // glbarcode_Factory_h
