/*  Barcode2dBase.h
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

#ifndef glbarcode_Barcode2dBase_h
#define glbarcode_Barcode2dBase_h


#include <string>
#include <vector>

#include "Barcode.h"
#include "Renderer.h"
#include "Matrix.h"


namespace glbarcode
{

	/**
	 * @class Barcode2dBase Barcode2dBase.h glbarcode/Barcode2dBase.h
	 *
	 * Base class for all barcode types.
	 */
	class Barcode2dBase : public Barcode
	{

	protected:
		/**
		 * Default constructor.
		 */
		Barcode2dBase();


	public:
		/**
		 * Destructor.
		 */
		virtual ~Barcode2dBase();


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
		 * @param rawData Data to validate
		 * @return True if data is valid data for barcode type
		 * @return False if data is not valid data for barcode type
		 */
		virtual bool validate( std::string rawData ) = 0;


		/**
		 * Preprocess barcode data.
		 *
		 * Optional virtual method to perform any transformation of the data needed
		 * before encoding.  (E.g. encoding an extended alphabet into a simpler one).
		 *
		 * @param rawData Data to preprocess
		 * @return Preprocessed data
		 */
		virtual std::string preprocess( std::string rawData );


		/**
		 * Encode barcode data
		 *
		 * Required virtual method to encode data such that it can be later vectorized.
		 *
		 * @param[in]  cookedData  Data to encode
		 * @param[out] encodedData Encoded data in the form of a matrix
		 * @return True if data was encoded successfully
		 * @return False if data could not be encoded (condition not discoverable by validate())
		 */
		virtual bool encode( std::string   cookedData,
		                     Matrix<bool>& encodedData ) = 0;


		/**
		 * Vectorize encoded data
		 *
		 * Optional virtual method to convert encoded data into a list of drawing
		 * primitives which can later be rendered.
		 *
		 * @param[in] encodedData Data to vectorize
		 * @param[in,out] w Requested width of barcode (0 = auto size), vectorize will overwrite with actual width
		 * @param[in,out] h Requested height of barcode (0 = auto size), vectorize will overwrite with actual width
		 */
		virtual void vectorize( const Matrix<bool>& encodedData,
		                        double&             w,
		                        double&             h );


	private:
		/**
		 * Barcode2dBase Private data
		 */
		struct PrivateData;
		PrivateData *d;

	};

}


#endif // glbarcode_Barcode2dBase_h
