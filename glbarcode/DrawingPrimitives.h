/*  DrawingPrimitives.h
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

#ifndef glbarcode_DrawingPrimitives_h
#define glbarcode_DrawingPrimitives_h


#include <string>


namespace glbarcode
{

	/**
	 * @class DrawingPrimitive DrawingPrimitives.h glbarcode/DrawingPrimitives.h
	 *
	 * Base class for all drawing primitives
	 */
	class DrawingPrimitive
	{
	public:
		/**
		 * Destructor
		 */
		virtual ~DrawingPrimitive() { }

		double x;    /**< X coordinate of primitive's origin (points). */
		double y;    /**< Y coordinate of primitive's origin (points). */
	};


	/**
	 * @class DrawingPrimitiveLine DrawingPrimitives.h glbarcode/DrawingPrimitives.h
	 *
	 * A solid vertical line drawing primitive.
	 *
	 * @image html figure-primitive-line.svg "Line primitive properties"
	 *
	 */
	class DrawingPrimitiveLine : public DrawingPrimitive
	{
	public:
		/**
		 * Line constructor
		 *
		 * @param[in] x X coordinate of line's origin (points)
		 * @param[in] y Y coordinate of line's origin (points)
		 * @param[in] w Line width (points)
		 * @param[in] h Line height (points)
		 */
		DrawingPrimitiveLine( double x, double y, double w, double h );

		double  w;    /**< Line width (points). */
		double  h;    /**< Line length (points). */
	};


	/**
	 * @class DrawingPrimitiveBox DrawingPrimitives.h glbarcode/DrawingPrimitives.h
	 *
	 * A solid box drawing primitive.
	 *
	 * @image html figure-primitive-box.svg "Box primitive properties"
	 *
	 */
	class DrawingPrimitiveBox : public DrawingPrimitive
	{
	public:
		/**
		 * Box constructor
		 *
		 * @param[in] x X coordinate of box's origin (points)
		 * @param[in] y Y coordinate of box's origin (points)
		 * @param[in] w Width of box (points)
		 * @param[in] h Height of box (points)
		 */
		DrawingPrimitiveBox( double x, double y, double w, double h );

		double  w;    /**< Width of box (points). */
		double  h;    /**< Height of box (points). */
	};


	/**
	 * @class DrawingPrimitiveText DrawingPrimitives.h glbarcode/DrawingPrimitives.h
	 *
	 * A character string drawing primitive.
	 *
	 * @image html figure-primitive-text.svg "Text primitive properties"
	 *
	 */
	class DrawingPrimitiveText : public DrawingPrimitive
	{
	public:
		/**
		 * Text constructor
		 *
		 * @param[in] x     X coordinate of text's origin (points)
		 * @param[in] y     Y coordinate of text's origin (points)
		 * @param[in] fsize Font size of text (points)
		 * @param[in] s     Text
		 */
		DrawingPrimitiveText( double x, double y, double fsize, const std::string& s );

		double       fsize;    /**< Font size of text (points). */
		std::string  s;        /**< Text. */
	};


	/**
	 * @class DrawingPrimitiveRing DrawingPrimitives.h glbarcode/DrawingPrimitives.h
	 *
	 * A ring (an open circle) drawing primitive.
	 *
	 * @image html figure-primitive-ring.svg "Ring primitive properties"
	 *
	 */
	class DrawingPrimitiveRing : public DrawingPrimitive
	{
	public:
		/**
		 * Ring constructor
		 *
		 * @param[in] x      X coordinate of ring's origin (points)
		 * @param[in] y      Y coordinate of ring's origin (points)
		 * @param[in] r      Radius of ring (points)
		 * @param[in] lwidth Line width of ring (points)
		 */
		DrawingPrimitiveRing( double x, double y, double r, double lwidth );

		double  r;        /**< Radius of ring (points). */
		double  lwidth;   /**< Line width of ring (points). */
	};


	/**
	 * @class DrawingPrimitiveHexagon DrawingPrimitives.h glbarcode/DrawingPrimitives.h
	 *
	 * A solid regular hexagon (oriented with vertexes at top and bottom) drawing primitive.
	 *
	 * @image html figure-primitive-hexagon.svg "Hexagon primitive properties"
	 *
	 */
	class DrawingPrimitiveHexagon : public DrawingPrimitive
	{
	public:
		/**
		 * Hexagon constructor
		 *
		 * @param[in] x X coordinate of hexagon's origin (points)
		 * @param[in] y Y coordinate of hexagon's origin (points)
		 * @param[in] h Height of hexagon (points)
		 */
		DrawingPrimitiveHexagon( double x, double y, double h );

		double  h;    /**< Height of hexagon (points). */
	};

}


#endif // glbarcode_DrawingPrimitives_h
