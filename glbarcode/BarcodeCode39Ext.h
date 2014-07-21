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
	 * @class BarcodeCode39Ext BarcodeCode39Ext.h glbarcode/BarcodeCode39Ext.h
	 *
	 * Extended Code39 barcode, extends BarcodeCode39
	 *
	 * @image html sample-code39ext.svg "Sample Extended Code 39 Barcode"
	 *
	 */
	class BarcodeCode39Ext : public BarcodeCode39
	{
	public:
		/**
		 * Static Extended Code39 barcode creation method
		 *
		 * Used by glbarcode::BarcodeFactory
		 */
		static Barcode* create( void );


	private:
		bool validate( std::string rawData );

		std::string preprocess( std::string rawData );

		std::string prepareText( std::string rawData );

	};

}


#endif // glbarcode_BarcodeCode39Ext_h
