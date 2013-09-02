/*  RendererEps.h
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

#ifndef glbarcode_RendererEps_h
#define glbarcode_RendererEps_h


#include "Renderer.h"


namespace glbarcode
{

	/**
	 * @class RendererEps RendererEps.h glbarcode/RendererEps.h
	 *
	 * Simple EPS Renderer.
	 *
	 * Renders Scalable Vector Graphics format to stdout.
	 */
	class RendererEps : public Renderer
	{
	public:
		/**
		 * Default Constructor (output goes to stdout).
		 */
		RendererEps();


		/**
		 * Constructor with output filename
		 */
		RendererEps( std::string filename );


		/**
		 * Copy Constructor
		 */
		RendererEps( const RendererEps& from );


		/**
		 * Destructor
		 */
		virtual ~RendererEps();


		/** Assignment operator.
		 *
		 * @param from The value to assign to this object.
		 *
		 * @return A reference to this object.
		 */
		RendererEps& operator=( const RendererEps& from );


		/** Get "filename" parameter
		 *
		 * @returns filename parameter
		 */
		std::string filename( void ) const;


		/** Set "filename" parameter
		 *
		 * @param filename new value of the output filename
		 * @returns reference to this RendererEps object for parameter chaining
		 */
		RendererEps& filename( const std::string & filename );


	private:
		/*
		 * Virtual methods implemented by EPS renderer.
		 */
		void draw_begin( double w, double h );
		void draw_end( void );
		void draw_line( DrawingPrimitiveLine *line );
		void draw_box( DrawingPrimitiveBox *box );
		void draw_text( DrawingPrimitiveText *text );
		void draw_ring( DrawingPrimitiveRing *ring );
		void draw_hexagon( DrawingPrimitiveHexagon *hexagon );

	private:
		/**
		 * Private data for EPS Renderer
		 */
		struct PrivateData;
		PrivateData *d;
	};

}

#endif // glbarcode_RendererEps_h
