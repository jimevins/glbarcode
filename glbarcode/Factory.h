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
	 * Barcode factory class
	 */
	class Factory
	{

	public:
		/**
		 * Barcode creation function signature
		 */
		typedef Barcode* (*BarcodeCreateFct)(std::string           data,
						     double                w,
						     double                h,
						     BarcodeOptions const& options );

	private:
		/**
		 * Map barcode type strings to creation functions
		 */
		typedef std::map<std::string,BarcodeCreateFct> BarcodeTypeMap;


	public:
		/**
		 * Get singleton instance of Factory, create if uninitialized.
		 */
		static Factory* instance( void );

		/**
		 * Create barcode based on type string.
		 *
		 * @param type Barcode type string
		 * @param data Data to encode in barcode
		 * @param w Requested width of barcode (0 = auto size)
		 * @param h Requested height of barcode (0 = auto size)
		 * @param options Barcode options
		 */
		static Barcode* create_barcode( std::string           type,
						std::string           data,
						double                w,
						double                h,
						BarcodeOptions const& options );

		/**
		 * Register barcode type
		 *
		 * @param type Barcode type string
		 * @param fct Function to create barcode object of concrete Barcode class
		 */
		static void register_type( std::string type, BarcodeCreateFct fct );

		/**
		 * Is barcode type supported?
		 */
		static bool is_type_supported( std::string type );


		/**
		 * Get list of supported types
		 */
		const std::list<std::string> get_supported_types( void );


	private:
		/**
		 * Initialize factory by registering all built-in Barcode types
		 */
		static void init( void );

		/**
		 * Map barcode type strings to creation functions
		 */
		static BarcodeTypeMap m_barcode_type_map;

		/**
		 * Supported barcode types
		 */
		static std::list<std::string> m_supported_types;

	};

}


#endif // glbarcode_Factory_h
