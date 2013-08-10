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

#include "libglbarcode/Factory.h"
#include "libglbarcode/RendererSvg.h"

#include <iostream>
#include <string>

#include <stdlib.h>
#include <getopt.h>


const std::string program_name = "glbarcode";


void exit_with_hint( void )
{
	std::cerr << "Try '" << program_name << " --help' for more information\n";

	exit( EXIT_FAILURE );
}


void usage( std::list<std::string> supported_types )
{
	std::cerr << "Usage:\n";
	std::cerr << "  " << program_name << " [OPTION]... DATA\n";
	std::cerr << "\n";
	std::cerr << "Options:\n";
	std::cerr << "  --help                display this help and exit\n";
	std::cerr << "  --usage               display this help and exit\n";
	std::cerr << "  -t, --type=TYPE       set barcode type\n";
	std::cerr << "  -x, --text            print text with barcode, if supported\n";
	std::cerr << "  -c, --checksum        include checksum in barcode, if supported\n";
	std::cerr << "  -w, --width=W         request barcode width (points, 1 point = 1/72 inch)\n";
	std::cerr << "  -h, --height=H        request barcode height (points, 1 point = 1/72 inch)\n";
	std::cerr << "  -r, --resolution=PPI  set resolution (Pixels per Inch) for bitmap outputs\n";


	std::cerr << "\n";
	std::cerr << "Supported barcode types:\n";

	std::list<std::string>::iterator type;

	for ( type = supported_types.begin(); type != supported_types.end(); type++ )
	{
		std::cerr << "  " << *type << "\n";
	}

	exit( EXIT_SUCCESS );
}


int main( int argc, char **argv )
{
	/*
	 * Get singleton instance of barcode factory
	 */
	glbarcode::Factory *factory = glbarcode::Factory::instance();


	/*
	 * Options and Data storage and initialization
	 */
	std::string type          = "code39";
	bool        text_flag     = false;
	bool        checksum_flag = false;
	double      w             = 144;
	double      h             = 72;
	double      ppi           = 72;

	std::string data;


	/*
	 * Option definitions for getopt_long()
	 */
	const char *short_options = "+t:xcw:h:r:";

	const struct option long_options[] = {
		{ "type",       required_argument, NULL, 't' },
		{ "text",       no_argument,       NULL, 'x' },
		{ "checksum",   no_argument,       NULL, 'c' },
		{ "width",      required_argument, NULL, 'w' },
		{ "height",     required_argument, NULL, 'h' },
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
			if ( !factory->is_type_supported( type ) )
			{
				std::cerr << argv[0] << ": unsupported barcode type -- '" << type << "'\n";
				exit_with_hint();
			}
			break;
		case 'x':
			text_flag = true;
			break;
		case 'c':
			checksum_flag = true;
			break;
		case 'w':
			w = atof( optarg );
			break;
		case 'h':
			h = atof( optarg );
			break;
		case 'r':
			ppi = atof( optarg );
			break;
		case 0:
			usage( factory->get_supported_types() );
			break;
		default:
			exit_with_hint();
		}
	}

	/*
	 * Parse DATA (expect one and only one argument)
	 */
	if ( optind == argc )
	{
		std::cerr << argv[0] << ": missing barcode data\n";
		exit_with_hint();
	}
	else if ( optind != (argc-1) )
	{
		std::cerr << argv[0] << ": too many arguments\n";
		exit_with_hint();
	}
	else
	{
		data = argv[optind];
	}


	/*
	 * Build barcode
	 */
	glbarcode::Barcode* bc = factory->create_barcode( type, data, w, h, text_flag, checksum_flag );

	if ( bc == NULL )
	{
		std::cerr << "Error creating barcode of type \"" << type << "\"\n";
		exit_with_hint();
	}
	if ( bc->is_empty() )
	{
		std::cerr << argv[0] << ": barcode data is empty\n";
		exit( EXIT_FAILURE );
	}
	if ( !bc->is_data_valid() )
	{
		std::cerr << argv[0] << ": invalid data for barcode type -- '" << type << "'\n";
		exit( EXIT_FAILURE );
	}


	/*
	 * Render barcode
	 */
	glbarcode::RendererSvg renderer;

	bc->render( renderer );


	/*
	 * Cleanup
	 */
	delete bc;
	exit( EXIT_SUCCESS );
}
