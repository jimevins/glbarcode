/*  RendererSvg.cpp
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

#include "RendererSvg.h"

#include "Constants.h"

#include <cstdio>


using namespace glbarcode::Constants;

namespace glbarcode
{

	void RendererSvg::draw_begin( double w, double h )
	{
		printf( "<?xml version=\"1.0\" standalone=\"no\"?>\n" );
		printf( "<!-- Created with %s version %s (%s) -->\n",
			PACKAGE_NAME.c_str(), PACKAGE_VERSION.c_str(), PACKAGE_URL.c_str() );
		printf( "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"%f\" height=\"%f\" >\n",
			w, h );
	}


	void RendererSvg::draw_end( void )
	{
		printf( "</svg>\n" );
	}


	void RendererSvg::draw_line( DrawingPrimitiveLine *line )
	{
		double x = line->x + line->w/2; /* Offset line origin by 1/2 line width. */

		printf( "  <line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke-width=\"%f\" style=\"stroke:rgb(0,0,0)\" />\n",
			x, line->y, x, line->y+line->h, line->w );
	}


	void RendererSvg::draw_box( DrawingPrimitiveBox *box )
	{
		printf( "  <rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"fill:rgb(0,0,0)\" />\n",
			box->x, box->y, box->w, box->h );
	}


	void RendererSvg::draw_text( DrawingPrimitiveText *text )
	{
		printf( "  <text x=\"%f\" y=\"%f\" font-size=\"%f\" style=\"font-family:monospace;text-anchor:middle;fill:rgb(0,0,0)\" >%s</text>\n",
			text->x, text->y+text->fsize, text->fsize, text->s.c_str() );
	}


	void RendererSvg::draw_ring( DrawingPrimitiveRing *ring )
	{
		printf( "  <circle cx=\"%f\" cy=\"%f\" stroke-width=\"%f\" style=\"stroke:rgb(0,0,0)\" />\n",
			ring->x, ring->y, ring->r, ring->lwidth );
	}


	void RendererSvg::draw_hexagon( DrawingPrimitiveHexagon *hexagon )
	{
		printf( "  <polygon points=\"%f,%f %f,%f %f,%f %f,%f %f,%f %f,%f\" style=\"fill:rgb(0,0,0)\" />\n",
			hexagon->x,                    hexagon->y,
			hexagon->x + 0.433*hexagon->h, hexagon->y + 0.25*hexagon->h,
			hexagon->x + 0.433*hexagon->h, hexagon->y + 0.75*hexagon->h,
			hexagon->x,                    hexagon->y +      hexagon->h,
			hexagon->x - 0.433*hexagon->h, hexagon->y + 0.75*hexagon->h,
			hexagon->x - 0.433*hexagon->h, hexagon->y + 0.25*hexagon->h );
	}


}
