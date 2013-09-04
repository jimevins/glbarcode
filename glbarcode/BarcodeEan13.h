/*  BarcodeEan13.h
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

#ifndef glbarcode_BarcodeEan13_h
#define glbarcode_BarcodeEan13_h


#include "BarcodeUpcBase.h"


namespace glbarcode
{

	/**
	 * @class BarcodeEan13 BarcodeEan13.h glbarcode/BarcodeEan13.h
	 *
	 * EAN-13 barcode, implements BarcodeUpcBase
	 */
	class BarcodeEan13 : public BarcodeUpcBase
	{
	public:
		/**
		 * Static EAN-13 barcode creation method
		 *
		 * Used by glbarcode::BarcodeFactory
		 */
		static Barcode* create( void );


		/**
		 * Default constructor
		 */
		BarcodeEan13();


	private:
		bool validate_digits( int n_digits );

		std::string preprocess( std::string raw_data );

		void vectorize_text( std::string display_text,
				     double size1, double size2,
				     double x1_left, double x1_right, double y1,
				     double x2_left, double x2_right, double y2 );

	};

}


#endif // glbarcode_BarcodeEan13_h
