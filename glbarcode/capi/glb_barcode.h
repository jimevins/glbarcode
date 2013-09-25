/*  glb_barcode.h
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

#ifndef glb_barcode_h
#define glb_barcode_h


#include "glb_renderer.h"

#include <stdbool.h>


#ifdef __cplusplus
extern "C" {
#endif


	/**
	 * @struct glbBarcode glb-barcode.h glbarcode/capi/glb-barcode.h
	 *
	 * CAPI Base class for all barcode types.
	 */
	typedef struct glbBarcode glbBarcode;
	

	/**
	 * Delete glbBarcode object.
	 */
	void glb_barcode_delete( glbBarcode *bc );


	/**
	 * Set accessor for "show_text" parameter.
	 *
	 * @param value Boolean value
	 */
	void glb_barcode_set_show_text( glbBarcode *bc, bool value );


	/**
	 * Get accessor for "show_text" parameter.
	 *
	 * @returns Value of boolean "show_text" parameter
	 */
	bool glb_barcode_get_show_text( glbBarcode *bc );


	/**
	 * Set accessor for "checksum" parameter.
	 *
	 * @param value Boolean value
	 */
	void glb_barcode_set_checksum( glbBarcode *bc, bool value );


	/**
	 * Get accessor for "checksum" parameter.
	 *
	 * @returns Value of boolean "checksum" parameter
	 */
	bool glb_barcode_get_checksum( glbBarcode *bc );


	/**
	 * Build barcode from data.
	 *
	 * @param data Data to encode in barcode
	 * @param w Requested width of barcode (0 = auto size)
	 * @param h Requested height of barcode (0 = auto size)
	 */
	void glb_barcode_build( glbBarcode *bc,
				char       *data,
				double      w,
				double      h);


	/**
	 * Render barcode using given Renderer object.
	 *
	 * @param renderer A glbRenderer object
	 */
	void glb_barcode_render( glbBarcode  *bc,
				 glbRenderer *renderer );


	/**
	 * Is barcode data empty?
	 *
	 * @return True if barcode data is empty
	 * @return False if barcode data is not empty
	 */
	bool glb_barcode_is_empty( glbBarcode *bc );


	/**
	 * Is barcode data valid?
	 *
	 * @return True if barcode data is valid
	 * @return False if barcode data is not valid for implemented barcode type
	 */
	bool glb_barcode_is_data_valid( glbBarcode *bc );


	/**
	 * Get actual width of barcode (may differ from requested width).
	 *
	 * @return Actual width of barcode (points)
	 */
	double glb_barcode_get_width( glbBarcode *bc );


	/**
	 * Get actual height of barcode (may differ from requested height).
	 *
	 * @return Actual height of barcode (points)
	 */
	double glb_barcode_get_height( glbBarcode *bc );



#ifdef __cplusplus
}
#endif


#endif // glb_barcode_h
