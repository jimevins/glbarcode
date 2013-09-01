/*  Renderer.h
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

#ifndef glbarcode_Renderer_h
#define glbarcode_Renderer_h


#include <list>

#include "DrawingPrimitives.h"


namespace glbarcode
{

	/**
	 * @class Renderer Renderer.h glbarcode/Renderer.h
	 *
	 * Base class for all renderers.
	 */
	class Renderer
	{
	public:
		/**
		 * Render list of primitives.
		 *
		 * @param w Width of barcode bounding box (points)
		 * @param h Height of barcode bounding box (points)
		 * @param primitives List of drawing primitives
		 */
		void render( double w, double h, std::list<DrawingPrimitive*> primitives );


	protected:
		/**
		 * Draw begin.
		 * 
		 * Required virtual method to perform rendering setup, such as opening devices and/or
		 * initializing drawing contexts.
		 *
		 * @param w Width of barcode bounding box (points)
		 * @param h Height of barcode bounding box (points)
		 */
		virtual void draw_begin( double w, double h ) = 0;


		/**
		 * Draw end.
		 * 
		 * Required virtual method to perform rendering cleanup, such as closing devices
		 * and/or drawing contexts.
		 */
		virtual void draw_end( void ) = 0;


		/**
		 * Draw line primitive.
		 * 
		 * Required virtual method to draw or render DrawingPrimitiveLine.
		 *
		 * @param line Line primitive to draw
		 */
		virtual void draw_line( DrawingPrimitiveLine *line ) = 0;


		/**
		 * Draw box primitive.
		 * 
		 * Required virtual method to draw or render DrawingPrimitiveBox.
		 *
		 * @param box Box primitive to draw
		 */
		virtual void draw_box( DrawingPrimitiveBox *box ) = 0;


		/**
		 * Draw text primitive.
		 * 
		 * Required virtual method to draw or render DrawingPrimitiveText.
		 *
		 * @param text Text primitive to draw
		 */
		virtual void draw_text( DrawingPrimitiveText *text ) = 0;


		/**
		 * Draw ring primitive.
		 * 
		 * Required virtual method to draw or render DrawingPrimitiveRing.
		 *
		 * @param ring Ring primitive to draw
		 */
		virtual void draw_ring( DrawingPrimitiveRing *ring ) = 0;


		/**
		 * Draw hexagon primitive.
		 * 
		 * Required virtual method to draw or render DrawingPrimitiveHexagon.
		 *
		 * @param hexagon Hexagon primitive to draw
		 */
		virtual void draw_hexagon( DrawingPrimitiveHexagon *hexagon ) = 0;

	};

}

#endif // glbarcode_Renderer_h
