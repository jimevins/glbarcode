/*  BarcodePostnet.h
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

#ifndef glbarcode_BarcodePostnet_h
#define glbarcode_BarcodePostnet_h


#include "Barcode.h"


namespace glbarcode
{

	/**
	 * Postnet barcode (All USPS sizes: ZIP, ZIP+4, ZIP+4+DC), implements Barcode
	 */
	class BarcodePostnet : public Barcode
	{
	public:
		/**
		 * Static Postnet barcode creation method
		 *
		 * Used by glbarcode::Factory
		 */
		static Barcode* create( std::string           data,
					double                w,
					double                h,
					BarcodeOptions const& options );

		/**
		 * Postnet barcode constructor
		 */
		BarcodePostnet( std::string           data,
				double                w,
				double                h,
				BarcodeOptions const& options );

	protected:
		/**
		 * Dummy Postnet barcode constructor for derived types
		 */
		BarcodePostnet() { };

		/**
		 * Validate number of digits
		 */
		virtual bool validate_digits( int n_digits );


	private:
		bool validate( std::string           raw_data,
			       BarcodeOptions const& options );

		std::string encode( std::string           cooked_data,
				    BarcodeOptions const& options );

		void vectorize( std::string           coded_data,
				std::string           display_text,
				std::string           cooked_data,
				double                w,
				double                h,
				BarcodeOptions const& options );
	};

}


#endif // glbarcode_BarcodePostnet_h
