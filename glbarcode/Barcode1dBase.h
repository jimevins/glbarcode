/*  Barcode1dBase.h
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

#ifndef glbarcode_Barcode1dBase_h
#define glbarcode_Barcode1dBase_h


#include <string>

#include "Barcode.h"
#include "Renderer.h"


namespace glbarcode
{

	/**
	 * @class Barcode1dBase Barcode1dBase.h glbarcode/Barcode1dBase.h
	 *
	 * Base class for all barcode types.
	 */
	class Barcode1dBase : public Barcode
	{

	protected:
		/**
		 * Default constructor.
		 */
		Barcode1dBase();


	public:
		/**
		 * Destructor.
		 */
		virtual ~Barcode1dBase();


		/**
		 * Build barcode from data.
		 *
		 * @param data Data to encode in barcode
		 * @param w Requested width of barcode (0 = auto size)
		 * @param h Requested height of barcode (0 = auto size)
		 */
		void build( std::string           data,
			    double                w = 0,
			    double                h = 0 );


	protected:
		/**
		 * Validate barcode data.
		 *
		 * Required virtual method to test if data is valid for encoding with
		 * barcode type.
		 *
		 * @param raw_data Data to validate
		 * @return True if data is valid data for barcode type
		 * @return False if data is not valid data for barcode type
		 */
		virtual bool validate( std::string raw_data ) = 0;


		/**
		 * Preprocess barcode data.
		 *
		 * Optional virtual method to perform any transformation of the data needed
		 * before encoding.  (E.g. encoding an extended alphabet into a simpler one).
		 *
		 * @param raw_data Data to preprocess
		 * @return Preprocessed data
		 */
		virtual std::string preprocess( std::string raw_data );


		/**
		 * Encode barcode data
		 *
		 * Required virtual method to encode data such that it can be later vectorized.
		 * The encoded data is usually a list of characters that represent an atomic
		 * barcode element (e.g. 'w' = a wide line & 'n' = a narrow line).
		 *
		 * @param cooked_data Data to encode
		 * @return Encoded data
		 */
		virtual std::string encode( std::string cooked_data ) = 0;


		/**
		 * Prepare text
		 *
		 * Optional virtual method to prepare text to be displayed as part of barcode.
		 *
		 * @param raw_data Data to prepare
		 * @return text in display form
		 */
		virtual std::string prepare_text( std::string raw_data );


		/**
		 * Vectorize encoded data
		 *
		 * Required virtual method to convert encoded data into a list of drawing
		 * primitives which can later be rendered.
		 *
		 * @param encoded_data Data to vectorize
		 * @param display_text Text to display
		 * @param cooked_data Original data prior to encoding (may be needed for sizing)
		 * @param w Requested width of barcode (0 = auto size), vectorize will overwrite with actual width
		 * @param h Requested height of barcode (0 = auto size), vectorize will overwrite with actual width
		 */
		virtual void vectorize( std::string encoded_data,
					std::string display_text,
					std::string cooked_data,
					double      &w,
					double      &h ) = 0;


	private:
		/**
		 * Barcode1dBase Private data
		 */
		struct PrivateData;
		PrivateData *d;

	};

}


#endif // glbarcode_Barcode1dBase_h