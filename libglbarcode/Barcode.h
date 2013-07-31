/*  Barcode.h
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

#ifndef glbarcode_Barcode_h
#define glbarcode_Barcode_h


#include <string>
#include <list>

#include "Primitive.h"
#include "Renderer.h"


namespace glbarcode
{

	/**
	 * Base class for all barcode types
	 */
	class Barcode
	{
	public:
		void        render( Renderer &renderer );

		bool        is_empty( void );
		bool        is_data_valid( void );

		double      get_w( void );
		double      get_h( void );

		/*
		 * Build barcode from parameters.
		 */
		void                build( bool text_flag, bool checksum_flag, double w, double h, std::string data );

	protected:
		/*
		 * Virtual methods called by construct method.
		 */
		virtual bool        validate(     std::string data ) = 0;

		virtual std::string preprocess(   std::string data );

		virtual std::string encode(       std::string canon_data ) = 0;

		virtual void        vectorize(    std::string coded_data,
						  std::string cooked_data,
						  std::string display_text ) = 0;

		virtual std::string prepare_text( std::string data );

		/*
		 * Used by vectorize implementations.
		 */
		void add_box(     double x, double y, double w, double h );
		void add_string(  double x, double y, double fsize, std::string s );
		void add_ring(    double x, double y, double r, double line_width );
		void add_hexagon( double x, double y, double h );

	protected:
		bool        text_flag;
		bool        checksum_flag;
		double      w;
		double      h;

	private:
		std::string data;

		bool        empty_flag;
		bool        data_valid_flag;

		std::list<Primitive *> primitives;

	};

}


#endif // glbarcode_Barcode_h
