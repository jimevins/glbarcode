/*  glb_renderer_eps.cpp
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

#include "glb_renderer_eps.h"

#include <glbarcode/RendererEps.h>



using namespace glbarcode;



glbRenderer *glb_renderer_eps_new( void )
{
	return new RendererEps();
}


void glb_renderer_eps_set_filename( glbRenderer *renderer, char *value )
{
	static_cast<RendererEps*>(renderer)->filename( value );
}


const char *glb_renderer_eps_get_filename( glbRenderer *renderer )
{
	return static_cast<RendererEps*>(renderer)->filename().c_str();
}




