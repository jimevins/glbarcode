/*  glb_renderer_eps.h
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

#ifndef glb_renderer_eps_h
#define glb_renderer_eps_h


#include "glb_renderer.h"


#ifdef __cplusplus
extern "C" {
#endif


	/**
	 * New RendererEps object.
	 */
	glbRenderer* glb_renderer_eps_new( void );


	/**
	 * Set accessor for "filename" parameter.
	 *
	 * @param value Filename
	 */
	void glb_renderer_eps_set_filename( glbRenderer *renderer, char *value );


	/**
	 * Get accessor for "filename" parameter.
	 *
	 * @returns Value of boolean "filename" parameter
	 */
	const char *glb_renderer_eps_get_filename( glbRenderer *renderer );



#ifdef __cplusplus
}
#endif


#endif // glb_renderer_eps_h
