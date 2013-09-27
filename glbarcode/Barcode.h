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

#include "Renderer.h"


/**
 * Barcode base for CAPI
 */
extern "C" struct gbcBarcode {};


namespace glbarcode
{

	/**
	 * @class Barcode Barcode.h glbarcode/Barcode.h
	 *
	 * Base class for all barcode types.
	 */
	class Barcode : public gbcBarcode
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
		 * Set accessor for "show_text" parameter.
		 *
		 * @param value Boolean value
		 * @returns A reference to this Barcode object for parameter chaining
		 */
		Barcode& show_text( bool value );


		/**
		 * Get accessor for "show_text" parameter.
		 *
		 * @returns Value of boolean "show_text" parameter
		 */
		bool show_text( void ) const;


		/**
		 * Set accessor for "checksum" parameter.
		 *
		 * @param value Boolean value
		 * @returns A reference to this Barcode object for parameter chaining
		 */
		Barcode& checksum( bool value );


		/**
		 * Get accessor for "checksum" parameter.
		 *
		 * @returns Value of boolean "checksum" parameter
		 */
		bool checksum( void ) const;


		/**
		 * Build barcode from data.
		 *
		 * @param data Data to encode in barcode
		 * @param w Requested width of barcode (0 = auto size)
		 * @param h Requested height of barcode (0 = auto size)
		 */
		virtual void build( std::string           data,
				    double                w = 0,
				    double                h = 0 ) = 0;


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
		 * Clear drawing primitives.
		 */
		void clear( void );


		/**
		 * Add line drawing primitive (DrawingPrimitiveLine)
		 *
		 * To be used by vectorize() implementations.
		 *
		 * @image html figure-primitive-line.svg "Line primitive properties"
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
		 * @image html figure-primitive-box.svg "Box primitive properties"
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
		 * @image html figure-primitive-text.svg "Text primitive properties"
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
		 * @image html figure-primitive-ring.svg "Ring primitive properties"
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
		 * @image html figure-primitive-hexagon.svg "Hexagon primitive properties"
		 *
		 * @param x X coordinate of hexagon's origin (points)
		 * @param y Y coordinate of hexagon's origin (points)
		 * @param h Height of hexagon (points)
		 */
		void add_hexagon( double x, double y, double h );


		/**
		 * Set empty flag.
		 *
		 * To be used by build() implementations to indicate if input data is empty
		 *
		 * @param value Boolean value of flag
		 */
		void set_empty_flag( bool value );


		/**
		 * Set data valid flag.
		 *
		 * To be used by build() implementations to indicate if input data is valid or not
		 *
		 * @param value Boolean value of flag
		 */
		void set_data_valid_flag( bool value );


		/**
		 * Set new width of barcode.
		 *
		 * To be used by build() implementations to override requested width of barcode.
		 *
		 * @param w Actual width of barcode (points)
		 */
		void set_width( double w );


		/**
		 * Set new height of barcode.
		 *
		 * To be used by build() implementations to override requested height of barcode.
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
