/*  BarcodeUpcBase.h
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

#ifndef glbarcode_BarcodeUpcBase_h
#define glbarcode_BarcodeUpcBase_h


#include "Barcode1dBase.h"


namespace glbarcode
{

	/**
	 * @class BarcodeUpcBase BarcodeUpcBase.h glbarcode/BarcodeUpcBase.h
	 *
	 * UpcBase barcode, base class for UPC-A and EAN-13 barcode types, implements Barcode1dBase
	 */
	class BarcodeUpcBase : public Barcode1dBase
	{
	protected:
		virtual bool validate_digits( int n_digits ) = 0;

		virtual void vectorize_text( std::string display_text,
					     double size1, double size2,
					     double x1_left, double x1_right, double y1,
					     double x2_left, double x2_right, double y2 ) = 0;

	private:
		bool validate( std::string raw_data );

		std::string encode( std::string cooked_data );

		std::string prepare_text( std::string raw_data );

		void vectorize( std::string coded_data,
				std::string display_text,
				std::string cooked_data,
				double      &w,
				double      &h );


	protected:
		int m_end_bars_modules;
		int m_first_digit_val;


	private:
		int m_check_digit_val;

	};

}


#endif // glbarcode_BarcodeUpcBase_h
