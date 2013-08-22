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
	 * A solid vertical line drawing primitive.
	 *
	 *
	 *     @ =  origin (x,y) from top left corner of barcode
	 *
	 *              @-----+
	 *              |     |
	 *              |     |
	 *              |     |
	 *              |     | h
	 *              |     |
	 *              |     |
	 *              |     |
	 *              +-----+
	 *                 w
	 *
	 *
	 * All units are in points ( 1 point = 1/72 inch ).
	 */
	class DrawingPrimitiveLine : public DrawingPrimitive
	{
	public:
		/**
		 * Line constructor
		 *
		 * @param x X coordinate of line's origin (points)
		 * @param y Y coordinate of line's origin (points)
		 * @param w Line width (points)
		 * @param h Line height (points)
		 */
		DrawingPrimitiveLine( double x, double y, double w, double h );

		double  w;    /**< Line width (points). */
		double  h;    /**< Line length (points). */
	};


	/**
	 * A solid box drawing primitive.
	 *
	 *
	 *     @ =  origin (x,y) from top left corner of barcode
	 *
	 *              @---------+
	 *              |         |
	 *              |         |
	 *              |         |
	 *              |         | h
	 *              |         |
	 *              |         |
	 *              |         |
	 *              +---------+
	 *                   w
	 *
	 *
	 * All units are in points ( 1 point = 1/72 inch ).
	 */
	class DrawingPrimitiveBox : public DrawingPrimitive
	{
	public:
		/**
		 * Box constructor
		 *
		 * @param x X coordinate of box's origin (points)
		 * @param y Y coordinate of box's origin (points)
		 * @param w Width of box (points)
		 * @param h Height of box (points)
		 */
		DrawingPrimitiveBox( double x, double y, double w, double h );

		double  w;    /**< Width of box (points). */
		double  h;    /**< Height of box (points). */
	};


	/**
	 * A character string drawing primitive.
	 *
	 *
	 *     @ =  origin (x,y) from top left corner of barcode
	 *
	 *              ____        _  ------------------
	 *             /    \      | |                  ^
	 *            /  /\  \     | |                  |
	 *           /  /__\  \    | |___     ____      |
	 *          /  ______  \   | ._  \   /  __|     | ~fsize
	 *         /  /      \  \  | |_)  | |  (__      |
	 *        /__/        \__\ |_.___/   \____|     |
	 *                                              v
	 *                           @ ------------------
	 *                           x = horizontal center
	 *
	 *
	 * All units are in points ( 1 point = 1/72 inch ).
	 */
	class DrawingPrimitiveText : public DrawingPrimitive
	{
	public:
		/**
		 * Text constructor
		 *
		 * @param x X coordinate of text's origin (points)
		 * @param y Y coordinate of text's origin (points)
		 * @param fsize Font size of text (points)
		 * @param s Text
		 */
		DrawingPrimitiveText( double x, double y, double fsize, std::string s );

		double       fsize;    /**< Font size of text (points). */
		std::string  s;        /**< Text. */
	};


	/**
	 * A ring (an open circle) drawing primitive.
	 *
	 *
	 *     @ = origin (x,y) is centre of circle
	 *
	 *              lwidth
	 *                |
	 *                v
	 *           _.-""""-._
	 *         .'   ____   `.
	 *        /   .'  ^ `.   \
	 *       |   /        \   |
	 *       |   |    @---|---|------
	 *       |   \        /   |     |
	 *        \   `.____.'   /      | r
	 *         `._    ...._.'.......v
	 *            `-....-'
	 *
	 *
	 * All units are in points ( 1 point = 1/72 inch ).
	 */
	class DrawingPrimitiveRing : public DrawingPrimitive
	{
	public:
		/**
		 * Ring constructor
		 *
		 * @param x X coordinate of ring's origin (points)
		 * @param y Y coordinate of ring's origin (points)
		 * @param r Radius of ring (points)
		 * @param lwidth Line width of ring (points)
		 */
		DrawingPrimitiveRing( double x, double y, double r, double lwidth );

		double  r;        /**< Radius of ring (points). */
		double  lwidth;   /**< Line width of ring (points). */
	};


	/**
	 * A solid regular hexagon (oriented with vertexes at top and bottom) drawing primitive.
	 *
	 *
	 *     @ = origin (x,y) is top of hexagon
	 *
	 *                  @ ------------------
	 *              _-"   "-_              ^
	 *          _-"           "-_          |
	 *       +"                   "+       |
	 *       |                     |       |
	 *       |                     |       |
	 *       |                     |       | h
	 *       |                     |       |
	 *       |                     |       |
	 *       +_                   _+       |
	 *         "-_             _-"         |
	 *            "-_       _-"            |
	 *               "-_ _-"               v
	 *                  " ------------------
	 *
	 *
	 * All units are in points ( 1 point = 1/72 inch ).
	 */
	class DrawingPrimitiveHexagon : public DrawingPrimitive
	{
	public:
		/**
		 * Hexagon constructor
		 *
		 * @param x X coordinate of hexagon's origin (points)
		 * @param y Y coordinate of hexagon's origin (points)
		 * @param h Height of hexagon (points)
		 */
		DrawingPrimitiveHexagon( double x, double y, double h );

		double  h;    /**< Height of hexagon (points). */
	};

}


#endif // glbarcode_DrawingPrimitives_h
