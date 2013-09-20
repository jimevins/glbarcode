/*  test-datamatrix.cpp
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

#include "glbarcode/BarcodeFactory.h"
#include "glbarcode/RendererSvg.h"


using namespace glbarcode;

int main( int argc, char **argv )
{
	glbarcode::BarcodeFactory* factory = glbarcode::BarcodeFactory::instance();
	glbarcode::Barcode*        bc;

	bc = factory->create_barcode( "datamatrix" );

	bc->build( "Abc", 0, 0 );
	bc->render( RendererSvg().filename( "datamatrix-01.svg" ) );

	bc->build( "Abcd", 0, 0 );
	bc->render( RendererSvg().filename( "datamatrix-02.svg" ) );

	bc->build( "Abcde", 0, 0 );
	bc->render( RendererSvg().filename( "datamatrix-03.svg" ) );

	bc->build( "Abcdef", 0, 0 );
	bc->render( RendererSvg().filename( "datamatrix-04.svg" ) );

	bc->build( "Abcdefg", 0, 0 );
	bc->render( RendererSvg().filename( "datamatrix-05.svg" ) );

	bc->build( "Abcdefghi", 0, 0 );
	bc->render( RendererSvg().filename( "datamatrix-06.svg" ) );

	bc->build( "Abcdefghijk", 0, 0 );
	bc->render( RendererSvg().filename( "datamatrix-07.svg" ) );

	bc->build( "Abcdefghijklmnopqrs", 0, 0 );
	bc->render( RendererSvg().filename( "datamatrix-08.svg" ) );

	bc->build( "Abcdefghijklmnopqrstuvwxyz", 0, 0 );
	bc->render( RendererSvg().filename( "datamatrix-09.svg" ) );

	bc->build( "AbcdefghijklmnopqrstuvwxyzABCDEFG", 0, 0 );
	bc->render( RendererSvg().filename( "datamatrix-10.svg" ) );

	bc->build( "AbcdefghijklmnopqrstuvwxyzABCDEFGHIJ", 0, 0 );
	bc->render( RendererSvg().filename( "datamatrix-11.svg" ) );

	bc->build( "AbcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", 0, 0 );
	bc->render( RendererSvg().filename( "datamatrix-12.svg" ) );

	bc->build( "AbcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()-+", 0, 0 );
	bc->render( RendererSvg().filename( "datamatrix-13.svg" ) );

	bc->build( "AbcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()-+ZYXWVUTSRQPONMLKJIHGFEDCBA", 0, 0 );
	bc->render( RendererSvg().filename( "datamatrix-14.svg" ) );

	bc->build( "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam", 0, 0 );
	bc->render( RendererSvg().filename( "datamatrix-15.svg" ) );

	delete bc;
}
