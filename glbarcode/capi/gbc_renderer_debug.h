/*  gbc_renderer_debug.h
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
 * @file glbarcode/capi/gbc_renderer_debug.h
 *
 * CAPI front-end to glbarcode::RendererDebug.
 */

#ifndef gbc_renderer_debug_h
#define gbc_renderer_debug_h


#include "gbc_renderer.h"


#ifdef __cplusplus
extern "C" {
#endif


	/**
	 * CAPI stand-in for glbarcode::RendererDebug.
	 */
	typedef struct gbcRenderer gbcRendererDebug;


	/**
	 * New RendererDebug object.
	 */
	gbcRendererDebug* gbc_renderer_debug_new( void );



#ifdef __cplusplus
}
#endif


#endif // gbc_renderer_debug_h
