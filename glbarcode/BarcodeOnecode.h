/*  BarcodeOnecode.h
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

#ifndef glbarcode_BarcodeOnecode_h
#define glbarcode_BarcodeOnecode_h


#include "Barcode.h"

#include <stdint.h>


namespace glbarcode
{

	/**
	 * @class BarcodeOnecode BarcodeOnecode.h glbarcode/BarcodeOnecode.h
	 *
	 * Onecode barcode, implements Barcode
	 */
	class BarcodeOnecode : public Barcode
	{
	public:
		/**
		 * Static Onecode barcode creation method
		 *
		 * Used by glbarcode::Factory
		 */
		static Barcode* create( std::string           data,
					double                w,
					double                h,
					BarcodeOptions const& options );

		/**
		 * Onecode barcode constructor
		 */
		BarcodeOnecode( std::string           data,
				double                w,
				double                h,
				BarcodeOptions const& options );


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

	private:
		uint32_t USPS_MSB_Math_CRC11GenerateFrameCheckSequence( uint8_t* ByteArrayPtr );

		class Int104
		{
		public:
			Int104( void );

			void mult_uint( uint32_t y );
			void add_uint64( uint64_t y );
			uint32_t div_uint( uint32_t y );

			uint8_t byte[13];
		};


	};

}


#endif // glbarcode_BarcodeOnecode_h
