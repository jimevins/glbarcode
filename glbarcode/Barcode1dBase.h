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
		 * @param[in] data Data to encode in barcode
		 * @param[in] w    Requested width of barcode (0 = auto size)
		 * @param[in] h    Requested height of barcode (0 = auto size)
		 *
		 * @returns A reference to this Barcode object for chaining methods
		 */
		Barcode& build( const std::string&    data,
		                double                w = 0,
		                double                h = 0 );


	protected:
		/**
		 * Validate barcode data.
		 *
		 * Required virtual method to test if data is valid for encoding with
		 * barcode type.
		 *
		 * @param[in] rawData Data to validate
		 *
		 * @return True if data is valid data for barcode type
		 * @return False if data is not valid data for barcode type
		 */
		virtual bool validate( const std::string& rawData ) = 0;


		/**
		 * Preprocess barcode data.
		 *
		 * Optional virtual method to perform any transformation of the data needed
		 * before encoding.  (E.g. encoding an extended alphabet into a simpler one).
		 *
		 * @param[in] rawData Data to preprocess
		 *
		 * @return Preprocessed data
		 */
		virtual std::string preprocess( const std::string& rawData );


		/**
		 * Encode barcode data
		 *
		 * Required virtual method to encode data such that it can be later vectorized.
		 * The encoded data is usually a list of characters that represent an atomic
		 * barcode element (e.g. 'w' = a wide line & 'n' = a narrow line).
		 *
		 * @param[in] cookedData Data to encode
		 *
		 * @return Encoded data
		 */
		virtual std::string encode( const std::string& cookedData ) = 0;


		/**
		 * Prepare text
		 *
		 * Optional virtual method to prepare text to be displayed as part of barcode.
		 *
		 * @param[in] rawData Data to prepare
		 *
		 * @return text in display form
		 */
		virtual std::string prepareText( const std::string& rawData );


		/**
		 * Vectorize encoded data
		 *
		 * Required virtual method to convert encoded data into a list of drawing
		 * primitives which can later be rendered.
		 *
		 * @param[in]     encodedData Data to vectorize
		 * @param[in]     displayText Text to display
		 * @param[in]     cookedData  Original data prior to encoding (may be needed for sizing)
		 * @param[in,out] w           Requested width of barcode (0 = auto size), vectorize will overwrite with actual width
		 * @param[in,out] h           Requested height of barcode (0 = auto size), vectorize will overwrite with actual width
		 */
		virtual void vectorize( const std::string& encodedData,
		                        const std::string& displayText,
		                        const std::string& cookedData,
		                        double&            w,
		                        double&            h ) = 0;


	private:
		/**
		 * Barcode1dBase Private data
		 */
		struct PrivateData;
		PrivateData *d;

	};

}


#endif // glbarcode_Barcode1dBase_h
