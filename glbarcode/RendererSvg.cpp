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

#include "Version.h"

#include <cstdio>


using namespace glbarcode::Version;

namespace glbarcode
{

	struct RendererSvg::PrivateData
	{
		std::string filename;  /**< Output filename for SVG file */
		FILE        *fp;
	};


	RendererSvg::RendererSvg()
	{
		d = new RendererSvg::PrivateData;

		d->filename = "";
	}


	RendererSvg::RendererSvg( std::string filename )
	{
		d = new RendererSvg::PrivateData;

		d->filename = filename;
	}


	RendererSvg::RendererSvg( const RendererSvg& from )
	{
		d = new RendererSvg::PrivateData;

		*d = *from.d;
	}


	RendererSvg::~RendererSvg()
	{
		delete d;
	}


	RendererSvg& RendererSvg::operator=( const RendererSvg& from )
	{
		*d = *from.d;

		return *this;
	}


	std::string RendererSvg::filename( void ) const
	{
		return d->filename;
	}


	RendererSvg& RendererSvg::setFilename( const std::string & filename )
	{
		d->filename = filename;

		return *this;
	}


	void RendererSvg::drawBegin( double w, double h )
	{
		if ( d->filename.empty() || ( d->filename == "-" ) )
		{
			d->fp = stdout;
		}
		else
		{
			d->fp = fopen( d->filename.c_str(), "w" );
		}

		fprintf( d->fp, "<?xml version=\"1.0\" standalone=\"no\"?>\n" );
		fprintf( d->fp, "<!-- Created with %s version %s (%s) -->\n",
			 PACKAGE_NAME.c_str(), PACKAGE_VERSION.c_str(), PACKAGE_URL.c_str() );
		fprintf( d->fp, "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"%f\" height=\"%f\" >\n",
			 w, h );
	}


	void RendererSvg::drawEnd( void )
	{
		fprintf( d->fp, "</svg>\n" );

		if ( !d->filename.empty() || ( d->filename != "-" ) )
		{
			fclose( d->fp );
		}
	}


	void RendererSvg::drawLine( const DrawingPrimitiveLine *line )
	{
		double x = line->x + line->w/2; /* Offset line origin by 1/2 line width. */

		fprintf( d->fp, "  <line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke-width=\"%f\" style=\"stroke:rgb(0,0,0)\" />\n",
			 x, line->y, x, line->y+line->h, line->w );
	}


	void RendererSvg::drawBox( const DrawingPrimitiveBox *box )
	{
		fprintf( d->fp, "  <rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" shape-rendering=\"crispEdges\" style=\"fill:rgb(0,0,0)\" />\n",
			box->x, box->y, box->w, box->h );
	}


	void RendererSvg::drawText( const DrawingPrimitiveText *text )
	{
		fprintf( d->fp, "  <text x=\"%f\" y=\"%f\" font-size=\"%f\" style=\"font-family:monospace;text-anchor:middle;fill:rgb(0,0,0)\" >%s</text>\n",
			 text->x, text->y, text->fsize, text->s.c_str() );
	}


	void RendererSvg::drawRing( const DrawingPrimitiveRing *ring )
	{
		fprintf( d->fp, "  <circle cx=\"%f\" cy=\"%f\" r=\"%f\" stroke-width=\"%f\" style=\"stroke:rgb(0,0,0)\" />\n",
			 ring->x, ring->y, ring->r, ring->lwidth );
	}


	void RendererSvg::drawHexagon( const DrawingPrimitiveHexagon *hexagon )
	{
		fprintf( d->fp, "  <polygon points=\"%f,%f %f,%f %f,%f %f,%f %f,%f %f,%f\" style=\"fill:rgb(0,0,0)\" />\n",
			 hexagon->x,                    hexagon->y,
			 hexagon->x + 0.433*hexagon->h, hexagon->y + 0.25*hexagon->h,
			 hexagon->x + 0.433*hexagon->h, hexagon->y + 0.75*hexagon->h,
			 hexagon->x,                    hexagon->y +      hexagon->h,
			 hexagon->x - 0.433*hexagon->h, hexagon->y + 0.75*hexagon->h,
			 hexagon->x - 0.433*hexagon->h, hexagon->y + 0.25*hexagon->h );
	}


}
