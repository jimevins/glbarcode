/*  BarcodeUpcA.h
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

#ifndef glbarcode_BarcodeUpcA_h
#define glbarcode_BarcodeUpcA_h


#include "BarcodeUpcBase.h"


namespace glbarcode
{

	/**
	 * @class BarcodeUpcA BarcodeUpcA.h glbarcode/BarcodeUpcA.h
	 *
	 * UPC-A barcode, implements BarcodeUpcBase
	 */
	class BarcodeUpcA : public BarcodeUpcBase
	{
	public:
		/**
		 * Static UPC-A barcode creation method
		 *
		 * Used by glbarcode::Factory
		 */
		static Barcode* create( std::string           data,
					double                w,
					double                h,
					BarcodeOptions const& options );

		/**
		 * UPC-A barcode constructor
		 */
		BarcodeUpcA( std::string           data,
			     double                w,
			     double                h,
			     BarcodeOptions const& options );

	private:
		bool validate_digits( int n_digits );

		std::string preprocess( std::string           raw_data,
					BarcodeOptions const& options );

		void vectorize_text( std::string display_text,
				     double size1, double size2,
				     double x1_left, double x1_right, double y1,
				     double x2_left, double x2_right, double y2 );

	};

}


#endif // glbarcode_BarcodeUpcA_h
