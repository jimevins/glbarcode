/*  gbc_barcode.h
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
 * @file glbarcode/capi/gbc_barcode.h
 *
 * CAPI front-end to glbarcode::Barcode.
 */

#ifndef gbc_barcode_h
#define gbc_barcode_h


#include "gbc_renderer.h"

#include <stdbool.h>


#ifdef __cplusplus
extern "C" {
#endif


	/**
	 * CAPI Base class for all barcode types.
	 */
	typedef struct gbcBarcode gbcBarcode;
	

	/**
	 * Delete gbcBarcode object.
	 *
	 * @param bc pointer to barcode object
	 */
	void gbc_barcode_delete( gbcBarcode *bc );


	/**
	 * Set accessor for "show_text" parameter.
	 *
	 * @param bc pointer to barcode object
	 *
	 * @param value Boolean value
	 */
	void gbc_barcode_set_show_text( gbcBarcode *bc, bool value );


	/**
	 * Get accessor for "show_text" parameter.
	 *
	 * @param bc pointer to barcode object
	 *
	 * @returns Value of boolean "show_text" parameter
	 */
	bool gbc_barcode_get_show_text( gbcBarcode *bc );


	/**
	 * Set accessor for "checksum" parameter.
	 *
	 * @param bc pointer to barcode object
	 * @param value Boolean value
	 */
	void gbc_barcode_set_checksum( gbcBarcode *bc, bool value );


	/**
	 * Get accessor for "checksum" parameter.
	 *
	 * @param bc pointer to barcode object
	 *
	 * @returns Value of boolean "checksum" parameter
	 */
	bool gbc_barcode_get_checksum( gbcBarcode *bc );


	/**
	 * Build barcode from data.
	 *
	 * @param bc pointer to barcode object
	 * @param data Data to encode in barcode
	 * @param w Requested width of barcode (0 = auto size)
	 * @param h Requested height of barcode (0 = auto size)
	 */
	void gbc_barcode_build( gbcBarcode *bc,
				char       *data,
				double      w,
				double      h);


	/**
	 * Render barcode using given Renderer object.
	 *
	 * @param bc pointer to barcode object
	 * @param renderer A gbcRenderer object
	 */
	void gbc_barcode_render( gbcBarcode  *bc,
				 gbcRenderer *renderer );


	/**
	 * Is barcode data empty?
	 *
	 * @param bc pointer to barcode object
	 *
	 * @return True if barcode data is empty
	 * @return False if barcode data is not empty
	 */
	bool gbc_barcode_is_empty( gbcBarcode *bc );


	/**
	 * Is barcode data valid?
	 *
	 * @param bc pointer to barcode object
	 *
	 * @return True if barcode data is valid
	 * @return False if barcode data is not valid for implemented barcode type
	 */
	bool gbc_barcode_is_data_valid( gbcBarcode *bc );


	/**
	 * Get actual width of barcode (may differ from requested width).
	 *
	 * @param bc pointer to barcode object
	 *
	 * @return Actual width of barcode (points)
	 */
	double gbc_barcode_get_width( gbcBarcode *bc );


	/**
	 * Get actual height of barcode (may differ from requested height).
	 *
	 * @param bc pointer to barcode object
	 *
	 * @return Actual height of barcode (points)
	 */
	double gbc_barcode_get_height( gbcBarcode *bc );



#ifdef __cplusplus
}
#endif


#endif // gbc_barcode_h
