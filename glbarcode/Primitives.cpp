/*  Primitives.cpp
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

#include "Primitives.h"


namespace glbarcode
{

	PrimitiveLine::PrimitiveLine( double x, double y, double w, double h )
	{
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}


	PrimitiveBox::PrimitiveBox( double x, double y, double w, double h )
	{
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}


	PrimitiveText::PrimitiveText( double x, double y, double fsize, std::string s )
	{
		this->x     = x;
		this->y     = y;
		this->fsize = fsize;
		this->s     = s;
	}


	PrimitiveRing::PrimitiveRing( double x, double y, double r, double lwidth )
	{
		this->x      = x;
		this->y      = y;
		this->r      = r;
		this->lwidth = lwidth;
	}


	PrimitiveHexagon::PrimitiveHexagon( double x, double y, double h )
	{
		this->x = x;
		this->y = y;
		this->h = h;
	}

}
