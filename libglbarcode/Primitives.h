/*  Primitives.h
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

#ifndef glbarcode_Primitives_h
#define glbarcode_Primitives_h


#include <string>


namespace glbarcode
{

	/**
	 * Base class for all drawing primitives
	 */
	class Primitive
	{
	public:
		/**
		 * Destructor
		 */
		virtual ~Primitive() { }

		double x;    /**< X coordinate of primitive's origin (points). */
		double y;    /**< Y coordinate of primitive's origin (points). */
	};


	/**
	 * A solid vertical line drawing primitive.
	 *
	 *
	 *     @ =  origin (x,y) from top left corner of barcode
	 *
	 *              +--@--+
	 *              |     |
	 *              |     |
	 *              |     |
	 *              |     | length
	 *              |     |
	 *              |     |
	 *              |     |
	 *              +-----+
	 *               width
	 *
	 *
	 * All units are in points ( 1 point = 1/72 inch ).
	 */
	class PrimitiveLine : public Primitive
	{
	public:
		/**
		 * Line constructor
		 *
		 * @param x X coordinate of line's origin (points)
		 * @param y Y coordinate of line's origin (points)
		 * @param length Line length (points)
		 * @param width Line width (points)
		 */
		PrimitiveLine( double x, double y, double length, double width );

		double  length;    /**< Line length (points). */
		double  width;     /**< Line width (points). */
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
	class PrimitiveBox : public Primitive
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
		PrimitiveBox( double x, double y, double w, double h );

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
	class PrimitiveText : public Primitive
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
		PrimitiveText( double x, double y, double fsize, std::string s );

		double       fsize;    /**< Font size of text (points). */
		std::string  s;        /**< Text. */
	};


	/**
	 * A ring (an open circle) drawing primitive.
	 *
	 *
	 *     @ = origin (x,y) is centre of circle
	 *
	 *                v  line_width
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
	class PrimitiveRing : public Primitive
	{
	public:
		/**
		 * Ring constructor
		 *
		 * @param x X coordinate of ring's origin (points)
		 * @param y Y coordinate of ring's origin (points)
		 * @param r Radius of ring (points)
		 * @param line_width Line width of ring (points)
		 */
		PrimitiveRing( double x, double y, double r, double line_width );

		double  r;             /**< Radius of ring (points). */
		double  line_width;    /**< Line width of ring (points). */
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
	class PrimitiveHexagon : public Primitive
	{
	public:
		/**
		 * Hexagon constructor
		 *
		 * @param x X coordinate of hexagon's origin (points)
		 * @param y Y coordinate of hexagon's origin (points)
		 * @param h Height of hexagon (points)
		 */
		PrimitiveHexagon( double x, double y, double h );

		double  h;    /**< Height of hexagon (points). */
	};

}


#endif // glbarcode_Primitives_h
