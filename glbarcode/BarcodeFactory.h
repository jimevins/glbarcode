/*  BarcodeFactory.h
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

#ifndef glbarcode_BarcodeFactory_h
#define glbarcode_BarcodeFactory_h

#include "Barcode.h"

#include <string>
#include <map>


/**
 * Barcode factory base for CAPI
 */
extern "C" struct glbBarcodeFactory {};


namespace glbarcode
{
	/**
	 * @class BarcodeFactory BarcodeFactory.h glbarcode/BarcodeFactory.h
	 *
	 * Singleton Barcode factory class.
	 */
	class BarcodeFactory : public glbBarcodeFactory
	{

	public:
		/**
		 * Barcode creation function signature.
		 */
		typedef Barcode* (*BarcodeCreateFct)( void );


	private:
		/**
		 * Map barcode type strings to creation functions.
		 */
		typedef std::map<std::string,BarcodeCreateFct> BarcodeTypeMap;


	public:
		/**
		 * Get singleton instance of BarcodeFactory, create if uninitialized.
		 */
		static BarcodeFactory* instance( void );


		/**
		 * Create barcode based on type ID string.
		 *
		 * @param type_id Barcode type ID string
		 */
		static Barcode* create_barcode( std::string type_id );


		/**
		 * Register barcode type ID.
		 *
		 * @param type_id Barcode type ID string
		 * @param fct Function to create barcode object of concrete Barcode class
		 */
		static void register_type( std::string type_id, BarcodeCreateFct fct );


		/**
		 * Is barcode type supported?
		 */
		static bool is_type_supported( std::string type_id );


		/**
		 * Get list of supported types.
		 */
		static const std::list<std::string> get_supported_types( void );


	private:
		/**
		 * Initialize factory by registering all built-in Barcode types.
		 */
		static void init( void );


		/**
		 * Map barcode type strings to creation functions.
		 */
		static BarcodeTypeMap m_barcode_type_map;


		/**
		 * Supported barcode types.
		 */
		static std::list<std::string> m_supported_types;

	};

}


#endif // glbarcode_BarcodeFactory_h
