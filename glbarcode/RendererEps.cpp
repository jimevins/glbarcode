/*  RendererEps.cpp
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

#include "RendererEps.h"

#include "Constants.h"

#include <cstdio>


using namespace glbarcode::Constants;

namespace glbarcode
{

	struct RendererEps::PrivateData
	{
		std::string filename;  /**< Output filename for EPS file */
		FILE        *fp;
	};


	RendererEps::RendererEps()
	{
		d = new RendererEps::PrivateData;

		d->filename = "";
	}


	RendererEps::RendererEps( std::string filename )
	{
		d = new RendererEps::PrivateData;

		d->filename = filename;
	}


	RendererEps::RendererEps( const RendererEps& from )
	{
		d = new RendererEps::PrivateData;

		*d = *from.d;
	}


	RendererEps::~RendererEps()
	{
		delete d;
	}


	RendererEps& RendererEps::operator=(const RendererEps& from)
	{
		*d = *from.d;

		return *this;
	}


	std::string RendererEps::filename( void ) const
	{
		return d->filename;
	}


	RendererEps& RendererEps::filename( const std::string & filename )
	{
		d->filename = filename;

		return *this;
	}


	void RendererEps::draw_begin( double w, double h )
	{
		if ( d->filename.empty() || ( d->filename == "-" ) )
		{
			d->fp = stdout;
		}
		else
		{
			d->fp = fopen( d->filename.c_str(), "w" );
		}

		fprintf( d->fp, "%%!PS-Adobe-3.0 EPSF-3.0\n" );
		fprintf( d->fp, "%%%%Creator: %s version %s (%s)\n",
			PACKAGE_NAME.c_str(), PACKAGE_VERSION.c_str(), PACKAGE_URL.c_str() );
		fprintf( d->fp, "%%%%BoundingBox: 0 0 %f %f\n", w, h );
		fprintf( d->fp, "gsave\n" );
		fprintf( d->fp, "0 %f translate\n", h );
		fprintf( d->fp, "1 -1 scale\n" );
		fprintf( d->fp, "0 setgray\n" );
	}


	void RendererEps::draw_end( void )
	{
		fprintf( d->fp, "grestore\n" );
		fprintf( d->fp, "%%EOF\n" );

		if ( !d->filename.empty() || ( d->filename != "-" ) )
		{
			fclose( d->fp );
		}
	}


	void RendererEps::draw_line( DrawingPrimitiveLine *line )
	{
		double x = line->x + line->w/2; /* Offset line origin by 1/2 line width. */

		fprintf( d->fp, "newpath %f %f moveto 0 %f rlineto %f setlinewidth stroke\n",
			 x, line->y, line->h, line->w );
	}


	void RendererEps::draw_box( DrawingPrimitiveBox *box )
	{
		fprintf( d->fp, "newpath %f %f moveto %f 0 rlineto 0 %f rlineto %f 0 rlineto closepath fill\n",
			 box->x, box->y, box->w, box->h, -box->w );
	}


	void RendererEps::draw_text( DrawingPrimitiveText *text )
	{
		fprintf( d->fp, "gsave\n" );
		fprintf( d->fp, "%f %f translate\n", text->x, text->y );
		fprintf( d->fp, "1 -1 scale\n" );
		fprintf( d->fp, "/monospace findfont %f scalefont setfont\n", text->fsize );
		fprintf( d->fp, "newpath 0 0 moveto (%s) dup stringwidth pop 2 div neg 0 rmoveto show\n",
			 text->s.c_str() );
		fprintf( d->fp, "grestore\n" );
	}


	void RendererEps::draw_ring( DrawingPrimitiveRing *ring )
	{
		fprintf( d->fp, "newpath %f %f %f 0 360 arc closepath %f setlinewidth stroke\n",
			 ring->x, ring->y, ring->r, ring->lwidth );
	}


	void RendererEps::draw_hexagon( DrawingPrimitiveHexagon *hexagon )
	{
		fprintf( d->fp, "newpath %f %f moveto %f %f lineto %f %f lineto %f %f lineto %f %f lineto %f %f lineto closepath fill\n",
			 hexagon->x,                    hexagon->y,
			 hexagon->x + 0.433*hexagon->h, hexagon->y + 0.25*hexagon->h,
			 hexagon->x + 0.433*hexagon->h, hexagon->y + 0.75*hexagon->h,
			 hexagon->x,                    hexagon->y +      hexagon->h,
			 hexagon->x - 0.433*hexagon->h, hexagon->y + 0.75*hexagon->h,
			 hexagon->x - 0.433*hexagon->h, hexagon->y + 0.25*hexagon->h );
	}


}
