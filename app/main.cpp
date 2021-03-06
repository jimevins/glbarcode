/*  main.cpp
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
#include "glbarcode/RendererEps.h"

#include <iostream>
#include <string>

#include <stdlib.h>
#include <getopt.h>


const std::string programName = "glbarcode";


void exitWithHint( void )
{
	std::cerr << "Try '" << programName << " --help' for more information" << std::endl;

	exit( EXIT_FAILURE );
}


void usage( void )
{
	using namespace glbarcode;

	std::cerr << "Usage:" << std::endl;
	std::cerr << "  " << programName << " [OPTION]... DATA" << std::endl;
	std::cerr << std::endl;
	std::cerr << "Options:" << std::endl;
	std::cerr << "  --help                display this help and exit" << std::endl;
	std::cerr << "  --usage               display this help and exit" << std::endl;
	std::cerr << "  -t, --type=TYPE       set barcode type" << std::endl;
	std::cerr << "  -w, --width=W         request barcode width (points, 1 point = 1/72 inch)" << std::endl;
	std::cerr << "  -h, --height=H        request barcode height (points, 1 point = 1/72 inch)" << std::endl;
	std::cerr << "  -x, --text            print text with barcode, if supported" << std::endl;
	std::cerr << "  -c, --checksum        include checksum in barcode, if supported" << std::endl;
	std::cerr << "  -f, --format=FORMAT   set output format" << std::endl;
	std::cerr << "  -o, --output=FILENAME set output filename" << std::endl;
	//std::cerr << "  -r, --resolution=PPI  set resolution (Pixels per Inch) for bitmap outputs" << std::endl;


	std::cerr << std::endl;
	std::cerr << "Supported barcode types:" << std::endl;

	TypeIdList typeIds = Factory::getSupportedTypes();
	for ( TypeIdList::iterator i = typeIds.begin(); i != typeIds.end(); i++ )
	{
		std::cerr << "  " << *i << std::endl;
	}

	std::cerr << std::endl;
	std::cerr << "Supported output formats:" << std::endl;
	std::cerr << "  svg" << std::endl;
	std::cerr << "  eps" << std::endl;

	std::cerr << std::endl;

	exit( EXIT_SUCCESS );
}


int main( int argc, char **argv )
{
	using namespace glbarcode;

	/*
	 * Initialize barcode factory
	 */
	Factory::init();


	/*
	 * Options and Data storage and initialization
	 */
	std::string type          = "code39";
	double      w             = 144;
	double      h             = 72;
	bool        textFlag      = false;
	bool        checksumFlag  = false;
	//double      ppi           = 72;
	std::string oformat       = "svg";
	std::string ofilename     = "-";

	std::string data;


	/*
	 * Option definitions for getopt_long()
	 */
	const char *short_options = "+t:w:h:xcr:f:o:";

	const struct option long_options[] = {
		{ "type",       required_argument, NULL, 't' },
		{ "width",      required_argument, NULL, 'w' },
		{ "height",     required_argument, NULL, 'h' },
		{ "text",       no_argument,       NULL, 'x' },
		{ "checksum",   no_argument,       NULL, 'c' },
		{ "format",     required_argument, NULL, 'f' },
		{ "output",     required_argument, NULL, 'o' },
		{ "resolution", required_argument, NULL, 'r' },
		{ "help",       no_argument,       NULL, 0 },
		{ "usage",      no_argument,       NULL, 0 },
		{ NULL, 0, NULL, 0 }
	};


	/*
	 * Parse options
	 */
	int c;
	while ( (c = getopt_long( argc, argv, short_options, long_options, NULL )) != -1 )
	{
		switch (c)
		{
		case 't':
			type = optarg;
			if ( !Factory::isTypeSupported( type ) )
			{
				std::cerr << argv[0] << ": unsupported barcode type -- '" << type << "'" << std::endl;
				exitWithHint();
			}
			break;
		case 'x':
			textFlag = true;
			break;
		case 'c':
			checksumFlag = true;
			break;
		case 'w':
			w = atof( optarg );
			break;
		case 'h':
			h = atof( optarg );
			break;
		case 'f':
			oformat = optarg;
			if ( (oformat != "svg") && (oformat != "eps") )
			{
				std::cerr << argv[0] << ": unsupported output format -- '" << oformat << "'" << std::endl;
				exitWithHint();
			}
			break;
		case 'o':
			ofilename = optarg;
			break;
		case 'r':
			//ppi = atof( optarg );
			break;
		case 0:
			usage();
			break;
		default:
			exitWithHint();
		}
	}

	/*
	 * Parse DATA (expect one and only one argument)
	 */
	if ( optind == argc )
	{
		std::cerr << argv[0] << ": missing barcode data" << std::endl;
		exitWithHint();
	}
	else if ( optind != (argc-1) )
	{
		std::cerr << argv[0] << ": too many arguments" << std::endl;
		exitWithHint();
	}
	else
	{
		data = argv[optind];
	}


	/*
	 * Build barcode
	 */
	Barcode* bc = Factory::createBarcode( type );
	bc->setShowText(textFlag).setChecksum(checksumFlag);
	bc->build( data, w, h );

	if ( bc == NULL )
	{
		std::cerr << "Error creating barcode of type '" << type << "'" << std::endl;
		exitWithHint();
	}
	if ( bc->isEmpty() )
	{
		std::cerr << argv[0] << ": barcode data is empty" << std::endl;
		exit( EXIT_FAILURE );
	}
	if ( !bc->isDataValid() )
	{
		std::cerr << argv[0] << ": invalid data for barcode type -- '" << type << "'" << std::endl;
		exit( EXIT_FAILURE );
	}


	/*
	 * Render barcode
	 */
	if ( oformat == "svg" )
	{
		bc->render( RendererSvg().setFilename( ofilename ) );
	}
	else if ( oformat == "eps" )
	{
		bc->render( RendererEps().setFilename( ofilename ) );
	}
	else
	{
		std::cerr << argv[0] << ": unknown renderer -- '" << oformat << "'" << std::endl;
		exit( EXIT_FAILURE );
	}


	/*
	 * Cleanup
	 */
	delete bc;
	exit( EXIT_SUCCESS );
}
