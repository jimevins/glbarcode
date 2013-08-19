/*  test-svg-renderer.cpp
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

#include "glbarcode/Factory.h"
#include "glbarcode/RendererSvg.h"

#include <iostream>
#include <string>


int main( int argc, char **argv )
{
	glbarcode::RendererSvg renderer;

	if ( argc != 2 )
	{
		std::cerr << "Usage: " << argv[0] << "data";
	}

	glbarcode::BarcodeOptions options;
	glbarcode::Barcode* bc = glbarcode::Factory::instance()->create_barcode( "code39",
										 argv[1],
										 0, 0,
										 options );

	bc->render( renderer );

	delete bc;
}
