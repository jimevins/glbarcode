/*  gbc_renderer_svg.cpp
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

#include "gbc_renderer_svg.h"

#include <glbarcode/RendererSvg.h>



using namespace glbarcode;



gbcRendererSvg *gbc_renderer_svg_new( void )
{
	return new RendererSvg();
}


void gbc_renderer_svg_set_filename( gbcRendererSvg *renderer, char *value )
{
	static_cast<RendererSvg*>(renderer)->filename( value );
}


const char *gbc_renderer_svg_get_filename( gbcRendererSvg *renderer )
{
	return static_cast<RendererSvg*>(renderer)->filename().c_str();
}




