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
	 * The Barcode class is the base class for all barcode implementations.  This class
	 * provides the public interfaces and basic infrastructure for all barcode implementations.
	 * Implementations would not typically directly implement this class, but instead would implement
	 * either Barcode1dBase (for 1D symbologies) or Barcode2dBase (for 2D symbologies).
	 *
	 * See Barcode1dBase or Barcode2dBase.
	 *
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
		 * Set accessor for "showText" property.
		 *
		 * @param[in] value Boolean value
		 *
		 * @returns A reference to this Barcode object for property chaining
		 *
		 * @sa showText()
		 */
		Barcode& setShowText( bool value );


		/**
		 * Get accessor for "showText" property.
		 *
		 * @returns Value of boolean "showText" property
		 *
		 * @sa setShowText()
		 */
		bool showText( void ) const;


		/**
		 * Set accessor for "checksum" property.
		 *
		 * @param[in] value Boolean value
		 *
		 * @returns A reference to this Barcode object for property chaining
		 *
		 * @sa checksum()
		 */
		Barcode& setChecksum( bool value );


		/**
		 * Get accessor for "checksum" property.
		 *
		 * @returns Value of boolean "checksum" property
		 *
		 * @sa setChecksum()
		 */
		bool checksum( void ) const;


		/**
		 * Build barcode from data.
		 *
		 * @param[in] data Data to encode in barcode
		 * @param[in] w    Requested width of barcode (0 = auto size)
		 * @param[in] h    Requested height of barcode (0 = auto size)
		 *
		 * @returns A reference to this Barcode object for chaining methods
		 */
		virtual Barcode& build( const std::string&    data,
		                        double                w = 0,
		                        double                h = 0 ) = 0;


		/**
		 * Render barcode using given Renderer object.
		 *
		 * @param[in] renderer A Renderer object
		 */
		void render( Renderer& renderer );


		/**
		 * Is barcode data empty?
		 *
		 * @return True if barcode data is empty
		 * @return False if barcode data is not empty
		 *
		 * @sa setIsEmpty()
		 */
		bool isEmpty( void ) const;


		/**
		 * Is barcode data valid?
		 *
		 * @return True if barcode data is valid
		 * @return False if barcode data is not valid for implemented barcode type
		 *
		 * @sa setIsDataValid()
		 */
		bool isDataValid( void ) const;


		/**
		 * Get actual width of barcode (may differ from requested width).
		 *
		 * @return Actual width of barcode (points)
		 *
		 * @sa setWidth()
		 */
		double width( void ) const;


		/**
		 * Get actual height of barcode (may differ from requested height).
		 *
		 * @return Actual height of barcode (points)
		 *
		 * @sa setHeight()
		 */
		double height( void ) const;


	protected:
		/**
		 * Clear drawing primitives.
		 */
		void clear( void );


		/**
		 * Add line drawing primitive (DrawingPrimitiveLine)
		 *
		 * To be used by build() implementations during vectorization.
		 *
		 * @image html figure-primitive-line.svg "Line primitive properties"
		 *
		 * @param[in] x X coordinate of line's origin (points)
		 * @param[in] y Y coordinate of line's origin (points)
		 * @param[in] w Bar width (points)
		 * @param[in] h Bar height (points)
		 */
		void addLine( double x, double y, double w, double h );


		/**
		 * Add box drawing primitive (DrawingPrimitiveBox)
		 *
		 * To be used by build() implementations during vectorization.
		 *
		 * @image html figure-primitive-box.svg "Box primitive properties"
		 *
		 * @param[in] x X coordinate of box's origin (points)
		 * @param[in] y Y coordinate of box's origin (points)
		 * @param[in] w Width of box (points)
		 * @param[in] h Height of box (points)
		 */
		void addBox( double x, double y, double w, double h );


		/**
		 * Add text drawing primitive (DrawingPrimitiveText)
		 *
		 * To be used by build() implementations during vectorization.
		 *
		 * @image html figure-primitive-text.svg "Text primitive properties"
		 *
		 * @param[in] x     X coordinate of text's origin (points)
		 * @param[in] y     Y coordinate of text's origin (points)
		 * @param[in] fsize Font size of text (points)
		 * @param[in] s     Text
		 */
		void addText( double x, double y, double fsize, const std::string& s );


		/**
		 * Add ring drawing primitive (DrawingPrimitiveRing)
		 *
		 * To be used by build() implementations during vectorization.
		 *
		 * @image html figure-primitive-ring.svg "Ring primitive properties"
		 *
		 * @param[in] x      X coordinate of ring's origin (points)
		 * @param[in] y      Y coordinate of ring's origin (points)
		 * @param[in] r      Radius of ring (points)
		 * @param[in] lwidth Line width of ring (points)
		 */
		void addRing( double x, double y, double r, double lwidth );


		/**
		 * Add hexagon drawing primitive (DrawingPrimitiveHexagon)
		 *
		 * To be used by build() implementations during vectorization.
		 *
		 * @image html figure-primitive-hexagon.svg "Hexagon primitive properties"
		 *
		 * @param[in] x X coordinate of hexagon's origin (points)
		 * @param[in] y Y coordinate of hexagon's origin (points)
		 * @param[in] h Height of hexagon (points)
		 */
		void addHexagon( double x, double y, double h );


		/**
		 * Set is empty property.
		 *
		 * To be used by build() implementations to indicate if input data is empty.
		 *
		 * @param[in] value Boolean value of flag
		 *
		 * @sa isEmpty()
		 */
		void setIsEmpty( bool value );


		/**
		 * Set is data valid property.
		 *
		 * To be used by build() implementations to indicate if input data is valid or not.
		 *
		 * @param[in] value Boolean value of flag
		 *
		 * @sa isDataValid()
		 */
		void setIsDataValid( bool value );


		/**
		 * Set new width of barcode.
		 *
		 * To be used by build() implementations to override requested width of barcode.
		 *
		 * @param[in] w Actual width of barcode (points)
		 *
		 * @sa width()
		 */
		void setWidth( double w );


		/**
		 * Set new height of barcode.
		 *
		 * To be used by build() implementations to override requested height of barcode.
		 *
		 * @param[in] h Actual height of barcode (points)
		 *
		 * @sa height()
		 */
		void setHeight( double h );


	private:
		/**
		 * Barcode Private data
		 */
		struct PrivateData;
		PrivateData *d;

	};

}


#endif // glbarcode_Barcode_h
