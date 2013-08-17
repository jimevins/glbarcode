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
#include <list>

#include "Primitives.h"
#include "Renderer.h"


namespace glbarcode
{

	/**
	 * Base class for all barcode types
	 */
	class Barcode
	{
	public:
		/**
		 * Destructor
		 */
		virtual     ~Barcode();


		/**
		 * Render barcode using given Renderer object
		 *
		 * @param renderer a Renderer object
		 */
		void        render( Renderer &renderer );


		/**
		 * Is barcode data empty?
		 */
		bool        is_empty( void );


		/**
		 * Is barcode data valid?
		 */
		bool        is_data_valid( void );


		/**
		 * Get actual width of barcode (may differ from requested width)
		 */
		double      get_w( void );


		/**
		 * Get actual height of barcode (may differ from requested height)
		 */
		double      get_h( void );


	protected:
		/**
		 * Initialize and build barcode from parameters.
		 *
		 * @param data Data to encode in barcode
		 * @param w Requested width of barcode (0 = auto size)
		 * @param h Requested height of barcode (0 = auto size)
		 * @param text_flag Show text flag
		 * @param checksum_flag Add checksum flag (honored only if checksum is optional)
		 */
		void init( std::string data,
			   double      w,
			   double      h,
			   bool        text_flag,
			   bool        checksum_flag );


		/**
		 * Validate barcode data
		 *
		 * Required virtual method to test if data is valid for encoding with
		 * barcode type.
		 *
		 * @param data Data to validate
		 * @return true if data is valid data for barcode type
		 */
		virtual bool validate( std::string data ) = 0;


		/**
		 * Preprocess barcode data
		 *
		 * Optional virtual method to perform any transformation of the data needed
		 * before encoding.  (E.g. encoding an extended alphabet into a simpler one).
		 *
		 * @param raw_data Data to preprocess
		 * @return preprocessed data
		 */
		virtual std::string preprocess( std::string raw_data );


		/**
		 * Encode barcode data
		 *
		 * Required virtual method to encode data such that it can be later vectorized.
		 * The encoded data is usually a list of characters that represent an atomic
		 * barcode element (e.g. 'w' = a wide line & 'n' = a narrow line).
		 *
		 * @param cooked_data Data to preprocess
		 * @return encoded data
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
		 * @return encoded data
		 */
		virtual void vectorize( std::string encoded_data,
					std::string display_text ) = 0;


		/**
		 * Add line drawing primitive (PrimitiveLine)
		 *
		 * Used by vectorize implementation.
		 *
		 * @param x X coordinate of line's origin (points)
		 * @param y Y coordinate of line's origin (points)
		 * @param w Bar width (points)
		 * @param h Bar height (points)
		 */
		void add_line( double x, double y, double w, double h );


		/**
		 * Add box drawing primitive (PrimitiveBox)
		 *
		 * Used by vectorize implementation.
		 *
		 * @param x X coordinate of box's origin (points)
		 * @param y Y coordinate of box's origin (points)
		 * @param w Width of box (points)
		 * @param h Height of box (points)
		 */
		void add_box( double x, double y, double w, double h );


		/**
		 * Add text drawing primitive (PrimitiveText)
		 *
		 * Used by vectorize implementation.
		 *
		 * @param x X coordinate of text's origin (points)
		 * @param y Y coordinate of text's origin (points)
		 * @param fsize Font size of text (points)
		 * @param s Text
		 */
		void add_text( double x, double y, double fsize, std::string s );


		/**
		 * Add ring drawing primitive (PrimitiveRing)
		 *
		 * Used by vectorize implementation.
		 *
		 * @param x X coordinate of ring's origin (points)
		 * @param y Y coordinate of ring's origin (points)
		 * @param r Radius of ring (points)
		 * @param lwidth Line width of ring (points)
		 */
		void add_ring( double x, double y, double r, double lwidth );


		/**
		 * Add hexagon drawing primitive (PrimitiveHexagon)
		 *
		 * Used by vectorize implementation.
		 *
		 * @param x X coordinate of hexagon's origin (points)
		 * @param y Y coordinate of hexagon's origin (points)
		 * @param h Height of hexagon (points)
		 */
		void add_hexagon( double x, double y, double h );


	protected:
		std::string m_raw_data;       /**< Raw data */
		std::string m_cooked_data;    /**< Preprocessed data */
		std::string m_display_text;   /**< Text data to be displayed */
		std::string m_coded_data;     /**< Encoded data */

		double      m_w;              /**< Width of barcode (points) */
		double      m_h;              /**< Height of barcode (points) */
		bool        m_text_flag;      /**< Display text flag */
		bool        m_checksum_flag;  /**< Add checksum flag */

	private:
		bool        m_empty_flag;      /**< Empty data flag */
		bool        m_data_valid_flag; /**< Valid data flag */

		std::list<Primitive *> m_primitives; /**< List of drawing primitives */

	};

}


#endif // glbarcode_Barcode_h
