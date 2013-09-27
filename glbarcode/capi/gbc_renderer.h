/*  gbc_renderer.h
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

/**
 * @file glbarcode/capi/gbc_renderer.h
 *
 * CAPI front-end to glbarcode::Renderer.
 */

#ifndef gbc_renderer_h
#define gbc_renderer_h


#ifdef __cplusplus
extern "C" {
#endif


	/**
	 * CAPI Base class for all renderers.
	 */
	typedef struct gbcRenderer gbcRenderer;
	

	/**
	 * Delete gbcRenderer object.
	 */
	void gbc_renderer_delete( gbcRenderer *bc );



#ifdef __cplusplus
}
#endif


#endif // gbc_renderer_h
