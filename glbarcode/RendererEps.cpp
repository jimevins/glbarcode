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

#include "Version.h"

#include <cstdio>


using namespace glbarcode::Version;

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


	RendererEps::RendererEps( const std::string& filename )
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


	RendererEps& RendererEps::operator=( const RendererEps& from )
	{
		*d = *from.d;

		return *this;
	}


	std::string RendererEps::filename( void ) const
	{
		return d->filename;
	}


	RendererEps& RendererEps::setFilename( const std::string& filename )
	{
		d->filename = filename;

		return *this;
	}


	void RendererEps::drawBegin( double w, double h )
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


	void RendererEps::drawEnd( void )
	{
		fprintf( d->fp, "grestore\n" );
		fprintf( d->fp, "%%EOF\n" );

		if ( !d->filename.empty() || ( d->filename != "-" ) )
		{
			fclose( d->fp );
		}
	}


	void RendererEps::drawLine( double x, double y, double w, double h )
	{
		double x1 = x + w/2; /* Offset line origin by 1/2 line width. */

		fprintf( d->fp, "newpath %f %f moveto 0 %f rlineto %f setlinewidth stroke\n",
			 x1, y, h, w );
	}


	void RendererEps::drawBox( double x, double y, double w, double h )
	{
		fprintf( d->fp, "newpath %f %f moveto %f 0 rlineto 0 %f rlineto %f 0 rlineto closepath fill\n",
			 x, y, w, h, -w );
	}


	void RendererEps::drawText( double x, double y, double size, const std::string& text )
	{
		fprintf( d->fp, "gsave\n" );
		fprintf( d->fp, "%f %f translate\n", x, y );
		fprintf( d->fp, "1 -1 scale\n" );
		fprintf( d->fp, "/monospace findfont %f scalefont setfont\n", size );
		fprintf( d->fp, "newpath 0 0 moveto (%s) dup stringwidth pop 2 div neg 0 rmoveto show\n",
			 text.c_str() );
		fprintf( d->fp, "grestore\n" );
	}


	void RendererEps::drawRing( double x, double y, double r, double w )
	{
		fprintf( d->fp, "newpath %f %f %f 0 360 arc closepath %f setlinewidth stroke\n", x, y, r, w );
	}


	void RendererEps::drawHexagon( double x, double y, double h )
	{
		fprintf( d->fp, "newpath %f %f moveto %f %f lineto %f %f lineto %f %f lineto %f %f lineto %f %f lineto closepath fill\n",
			 x,           y,
			 x + 0.433*h, y + 0.25*h,
			 x + 0.433*h, y + 0.75*h,
			 x,           y +      h,
			 x - 0.433*h, y + 0.75*h,
			 x - 0.433*h, y + 0.25*h );
	}


}
