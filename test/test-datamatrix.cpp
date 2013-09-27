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

#include "glbarcode/Factory.h"
#include "glbarcode/RendererSvg.h"


using namespace glbarcode;

int main( int argc, char **argv )
{
	std::string alpha_data( "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()-+ZYXWVUTSRQPONMLKJIHGFEDCBA"
				"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()-+ZYXWVUTSRQPONMLKJIHGFEDCBA"
				"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()-+ZYXWVUTSRQPONMLKJIHGFEDCBA"
				"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()-+ZYXWVUTSRQPONMLKJIHGFEDCBA"
				"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()-+ZYXWVUTSRQPONMLKJIHGFEDCBA"
				"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()-+ZYXWVUTSRQPONMLKJIHGFEDCBA"
				"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()-+ZYXWVUTSRQPONMLKJIHGFEDCBA"
				"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()-+ZYXWVUTSRQPONMLKJIHGFEDCBA"
				"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()-+ZYXWVUTSRQPONMLKJIHGFEDCBA"
				"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()-+ZYXWVUTSRQPONMLKJIHGFEDCBA"
				"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()-+ZYXWVUTSRQPONMLKJIHGFEDCBA"
				"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()-+ZYXWVUTSRQPONMLKJIHGFEDCBA"
				"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()-+ZYXWVUTSRQPONMLKJIHGFEDCBA"
				"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()-+ZYXWVUTSRQPONMLKJIHGFEDCBA"
				"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()-+ZYXWVUTSRQPONMLKJIHGFEDCBA"
				"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()-+ZYXWVUTSRQPONMLKJIHGFEDCBA"
				"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()-+ZYXWVUTSRQPONMLKJIHGFEDCBA" );

	std::string numeric_data( "1234567890" );


	glbarcode::Factory* factory = glbarcode::Factory::instance();
	glbarcode::Barcode* bc;

	bc = factory->create_barcode( "datamatrix" );


	bc->build( alpha_data.substr( 0, 1 ), 0, 0 );
	bc->render( RendererSvg().filename( "datamatrix-10x10-1a.svg" ) );

	bc->build( alpha_data.substr( 0, 2 ), 0, 0 );
	bc->render( RendererSvg().filename( "datamatrix-10x10-2a.svg" ) );

	bc->build( alpha_data.substr( 0, 3 ), 0, 0 );
	bc->render( RendererSvg().filename( "datamatrix-10x10-3a.svg" ) );


	bc->build( alpha_data.substr( 0, 4 ), 0, 0 );
	bc->render( RendererSvg().filename( "datamatrix-12x12-4a.svg" ) );

	bc->build( numeric_data, 0, 0 );
	bc->render( RendererSvg().filename( "datamatrix-12x12-10n.svg" ) );


	bc->build( alpha_data.substr( 0, 6 ), 0, 0 );
	bc->render( RendererSvg().filename( "datamatrix-14x14-6a.svg" ) );


	bc->build( alpha_data.substr( 0, 9 ), 0, 0 );
	bc->render( RendererSvg().filename( "datamatrix-16x16-9a.svg" ) );


	bc->build( alpha_data.substr( 0, 15 ), 0, 0 );
	bc->render( RendererSvg().filename( "datamatrix-18x18-15a.svg" ) );


	bc->build( alpha_data.substr( 0, 19 ), 0, 0 );
	bc->render( RendererSvg().filename( "datamatrix-20x20-19a.svg" ) );


	bc->build( alpha_data.substr( 0, 25 ), 0, 0 );
	bc->render( RendererSvg().filename( "datamatrix-22x22-25a.svg" ) );


	bc->build( alpha_data.substr( 0, 31 ), 0, 0 );
	bc->render( RendererSvg().filename( "datamatrix-24x24-31a.svg" ) );


	bc->build( alpha_data.substr( 0, 40 ), 0, 0 );
	bc->render( RendererSvg().filename( "datamatrix-26x26-40a.svg" ) );


	bc->build( alpha_data.substr( 0, 50 ), 0, 0 );
	bc->render( RendererSvg().filename( "datamatrix-32x32-50a.svg" ) );


	bc->build( alpha_data.substr( 0, 65 ), 0, 0 );
	bc->render( RendererSvg().filename( "datamatrix-36x36-65a.svg" ) );


	bc->build( alpha_data.substr( 0, 100 ), 0, 0 );
	bc->render( RendererSvg().filename( "datamatrix-40x40-100a.svg" ) );


	bc->build( alpha_data.substr( 0, 125 ), 0, 0 );
	bc->render( RendererSvg().filename( "datamatrix-44x44-125a.svg" ) );


	bc->build( alpha_data.substr( 0, 150 ), 0, 0 );
	bc->render( RendererSvg().filename( "datamatrix-48x48-150a.svg" ) );


	bc->build( alpha_data.substr( 0, 175 ), 0, 0 );
	bc->render( RendererSvg().filename( "datamatrix-52x52-175a.svg" ) );


	bc->build( alpha_data.substr( 0, 250 ), 0, 0 );
	bc->render( RendererSvg().filename( "datamatrix-64x64-250a.svg" ) );


	bc->build( alpha_data.substr( 0, 300 ), 0, 0 );
	bc->render( RendererSvg().filename( "datamatrix-72x72-300a.svg" ) );


	bc->build( alpha_data.substr( 0, 400 ), 0, 0 );
	bc->render( RendererSvg().filename( "datamatrix-80x80-400a.svg" ) );


	bc->build( alpha_data.substr( 0, 500 ), 0, 0 );
	bc->render( RendererSvg().filename( "datamatrix-88x88-500a.svg" ) );


	bc->build( alpha_data.substr( 0, 600 ), 0, 0 );
	bc->render( RendererSvg().filename( "datamatrix-96x96-600a.svg" ) );


	bc->build( alpha_data.substr( 0, 800 ), 0, 0 );
	bc->render( RendererSvg().filename( "datamatrix-104x104-800a.svg" ) );


	bc->build( alpha_data.substr( 0, 1000 ), 0, 0 );
	bc->render( RendererSvg().filename( "datamatrix-120x120-1000a.svg" ) );


	bc->build( alpha_data.substr( 0, 1200 ), 0, 0 );
	bc->render( RendererSvg().filename( "datamatrix-132x132-1200a.svg" ) );


	bc->build( alpha_data.substr( 0, 1500 ), 0, 0 );
	bc->render( RendererSvg().filename( "datamatrix-144x144-1500a.svg" ) );


	delete bc;
}
