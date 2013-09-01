/*  Barcode.h
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

#ifndef glbarcode_Barcode_h
#define glbarcode_Barcode_h


#include <string>

#include "BarcodeOptions.h"
#include "Renderer.h"


namespace glbarcode
{

	/**
	 * @class Barcode Barcode.h glbarcode/Barcode.h
	 *
	 * Base class for all barcode types.
	 */
	class Barcode
	{

	protected:
		/**
		 * Default constructor.
		 */
		Barcode();


	public:
		/**
		 * Destructor.
		 */
		virtual ~Barcode();


		/**
		 * Render barcode using given Renderer object.
		 *
		 * @param renderer A Renderer object
		 */
		void render( Renderer &renderer );


		/**
		 * Is barcode data empty?
		 *
		 * @return True if barcode data is empty
		 * @return False if barcode data is not empty
		 */
		bool is_empty( void );


		/**
		 * Is barcode data valid?
		 *
		 * @return True if barcode data is valid
		 * @return False if barcode data is not valid for implemented barcode type
		 */
		bool is_data_valid( void );


		/**
		 * Get actual width of barcode (may differ from requested width).
		 *
		 * @return Actual width of barcode (points)
		 */
		double width( void );


		/**
		 * Get actual height of barcode (may differ from requested height).
		 *
		 * @return Actual height of barcode (points)
		 */
		double height( void );


	protected:
		/**
		 * Build barcode from parameters.  Used by constructors of derived classes.
		 *
		 * @param data Data to encode in barcode
		 * @param w Requested width of barcode (0 = auto size)
		 * @param h Requested height of barcode (0 = auto size)
		 * @param options Barcode options
		 */
		void build( std::string           data,
			    double                w,
			    double                h,
			    BarcodeOptions const& options );


		/**
		 * Validate barcode data.
		 *
		 * Required virtual method to test if data is valid for encoding with
		 * barcode type.
		 *
		 * @param raw_data Data to validate
		 * @param options Barcode options
		 * @return True if data is valid data for barcode type
		 * @return False if data is not valid data for barcode type
		 */
		virtual bool validate( std::string           raw_data,
				       BarcodeOptions const& options ) = 0;


		/**
		 * Preprocess barcode data.
		 *
		 * Optional virtual method to perform any transformation of the data needed
		 * before encoding.  (E.g. encoding an extended alphabet into a simpler one).
		 *
		 * @param raw_data Data to preprocess
		 * @param options Barcode options
		 * @return Preprocessed data
		 */
		virtual std::string preprocess( std::string           raw_data,
						BarcodeOptions const& options );


		/**
		 * Encode barcode data
		 *
		 * Required virtual method to encode data such that it can be later vectorized.
		 * The encoded data is usually a list of characters that represent an atomic
		 * barcode element (e.g. 'w' = a wide line & 'n' = a narrow line).
		 *
		 * @param cooked_data Data to encode
		 * @param options Barcode options
		 * @return Encoded data
		 */
		virtual std::string encode( std::string           cooked_data,
					    BarcodeOptions const& options ) = 0;


		/**
		 * Prepare text
		 *
		 * Optional virtual method to prepare text to be displayed as part of barcode.
		 *
		 * @param raw_data Data to prepare
		 * @param options Barcode options
		 * @return text in display form
		 */
		virtual std::string prepare_text( std::string           raw_data,
						  BarcodeOptions const& options );


		/**
		 * Vectorize encoded data
		 *
		 * Required virtual method to convert encoded data into a list of drawing
		 * primitives which can later be rendered.
		 *
		 * @param encoded_data Data to vectorize
		 * @param display_text Text to display
		 * @param cooked_data Original data prior to encoding (may be needed for sizing)
		 * @param w Requested width of barcode (0 = auto size)
		 * @param h Requested height of barcode (0 = auto size)
		 * @param options Barcode options
		 */
		virtual void vectorize( std::string           encoded_data,
					std::string           display_text,
					std::string           cooked_data,
					double                w,
					double                h,
					BarcodeOptions const& options ) = 0;


		/**
		 * Add line drawing primitive (DrawingPrimitiveLine)
		 *
		 * To be used by vectorize() implementations.
		 *
		 * @param x X coordinate of line's origin (points)
		 * @param y Y coordinate of line's origin (points)
		 * @param w Bar width (points)
		 * @param h Bar height (points)
		 */
		void add_line( double x, double y, double w, double h );


		/**
		 * Add box drawing primitive (DrawingPrimitiveBox)
		 *
		 * To be used by vectorize() implementations.
		 *
		 * @param x X coordinate of box's origin (points)
		 * @param y Y coordinate of box's origin (points)
		 * @param w Width of box (points)
		 * @param h Height of box (points)
		 */
		void add_box( double x, double y, double w, double h );


		/**
		 * Add text drawing primitive (DrawingPrimitiveText)
		 *
		 * To be used by vectorize() implementations.
		 *
		 * @param x X coordinate of text's origin (points)
		 * @param y Y coordinate of text's origin (points)
		 * @param fsize Font size of text (points)
		 * @param s Text
		 */
		void add_text( double x, double y, double fsize, std::string s );


		/**
		 * Add ring drawing primitive (DrawingPrimitiveRing)
		 *
		 * To be used by vectorize() implementations.
		 *
		 * @param x X coordinate of ring's origin (points)
		 * @param y Y coordinate of ring's origin (points)
		 * @param r Radius of ring (points)
		 * @param lwidth Line width of ring (points)
		 */
		void add_ring( double x, double y, double r, double lwidth );


		/**
		 * Add hexagon drawing primitive (DrawingPrimitiveHexagon)
		 *
		 * To be used by vectorize() implementations.
		 *
		 * @param x X coordinate of hexagon's origin (points)
		 * @param y Y coordinate of hexagon's origin (points)
		 * @param h Height of hexagon (points)
		 */
		void add_hexagon( double x, double y, double h );


		/**
		 * Set new width of barcode.
		 *
		 * To be used by vectorize() implementations to override requested width of barcode.
		 *
		 * @param w Actual width of barcode (points)
		 */
		void set_width( double w );


		/**
		 * Set new height of barcode.
		 *
		 * To be used by vectorize() implementations to override requested height of barcode.
		 *
		 * @param h Actual height of barcode (points)
		 */
		void set_height( double h );


	private:
		/**
		 * Barcode Private data
		 */
		struct PrivateData;
		PrivateData *d;

	};

}


#endif // glbarcode_Barcode_h
