/*  Primitive.h
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

#ifndef glbarcode_Primitive_h
#define glbarcode_Primitive_h


#include <string>


namespace glbarcode
{

	/**
	 * Base class for all drawing primitives
	 */
	class Primitive
	{
	public:
		virtual ~Primitive() { }

		double x;
		double y;
	};


	/**
	 * A solid box drawing primitive.
	 *
	 *<programlisting>
	 *
	 * @ =  origin (x,y) from top left corner of barcode
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
	 *</programlisting>
	 *
	 * All units are in points ( 1 point = 1/72 inch ).
	 */
	class PrimitiveBox : public Primitive
	{
	public:
		PrimitiveBox( double x, double y, double w, double h );

		double  w;
		double  h;
	};


	/**
	 * A character string drawing primitive.
	 *
	 *<programlisting>
	 *
	 * @ =  origin (x,y) from top left corner of barcode
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
	 *</programlisting>
	 *
	 * All units are in points ( 1 point = 1/72 inch ).
	 */
	class PrimitiveText : public Primitive
	{
	public:
		PrimitiveText( double x, double y, double fsize, std::string s );

		double       fsize;
		std::string  s;
	};


	/**
	 * A ring (an open circle) drawing primitive.
	 *
	 *<programlisting>
	 *
	 * @ = origin (x,y) is centre of circle
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
	 *</programlisting>
	 *
	 * All units are in points ( 1 point = 1/72 inch ).
	 */
	class PrimitiveRing : public Primitive
	{
	public:
		PrimitiveRing( double x, double y, double r, double line_width );

		double  r;
		double  line_width;
	};


	/**
	 * A solid regular hexagon (oriented with vertexes at top and bottom) drawing primitive.
	 *
	 *<programlisting>
	 *
	 * @ = origin (x,y) is top of hexagon
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
	 *</programlisting>
	 *
	 * All units are in points ( 1 point = 1/72 inch ).
	 */
	class PrimitiveHexagon : public Primitive
	{
	public:
		PrimitiveHexagon( double x, double y, double h );

		double  h;
	};

}


#endif // glbarcode_Primitive_h
