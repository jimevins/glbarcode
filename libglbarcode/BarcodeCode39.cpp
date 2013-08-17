/*  BarcodeCode39.cpp
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

#include "BarcodeCode39.h"

#include "Constants.h"

#include <ctype.h>
#include <algorithm>


using namespace glbarcode::Constants;


namespace
{
	/* Code 39 alphabet. Position indicates value. */
	const std::string alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ-. $/+%";

	/* Code 39 symbols. Position must match position in alphabet. */
	const std::string symbols[] = {
		/*        BsBsBsBsB */
		/* 0 */  "NnNwWnWnN",
		/* 1 */  "WnNwNnNnW",
		/* 2 */  "NnWwNnNnW",
		/* 3 */  "WnWwNnNnN",
		/* 4 */  "NnNwWnNnW",
		/* 5 */  "WnNwWnNnN",
		/* 6 */  "NnWwWnNnN",
		/* 7 */  "NnNwNnWnW",
		/* 8 */  "WnNwNnWnN",
		/* 9 */  "NnWwNnWnN",
		/* A */  "WnNnNwNnW",
		/* B */  "NnWnNwNnW",
		/* C */  "WnWnNwNnN",
		/* D */  "NnNnWwNnW",
		/* E */  "WnNnWwNnN",
		/* F */  "NnWnWwNnN",
		/* G */  "NnNnNwWnW",
		/* H */  "WnNnNwWnN",
		/* I */  "NnWnNwWnN",
		/* J */  "NnNnWwWnN",
		/* K */  "WnNnNnNwW",
		/* L */  "NnWnNnNwW",
		/* M */  "WnWnNnNwN",
		/* N */  "NnNnWnNwW",
		/* O */  "WnNnWnNwN",
		/* P */  "NnWnWnNwN",
		/* Q */  "NnNnNnWwW",
		/* R */  "WnNnNnWwN",
		/* S */  "NnWnNnWwN",
		/* T */  "NnNnWnWwN",
		/* U */  "WwNnNnNnW",
		/* V */  "NwWnNnNnW",
		/* W */  "WwWnNnNnN",
		/* X */  "NwNnWnNnW",
		/* Y */  "WwNnWnNnN",
		/* Z */  "NwWnWnNnN",
		/* - */  "NwNnNnWnW",
		/* . */  "WwNnNnWnN",
		/*   */  "NwWnNnWnN",
		/* $ */  "NwNwNwNnN",
		/* / */  "NwNwNnNwN",
		/* + */  "NwNnNwNwN",
		/* % */  "NnNwNwNwN"
	};

	const std::string frame_symbol = "NwNnWnWnN";

	/* Vectorization constants */
	const double MIN_X       = ( 0.01 *  PTS_PER_INCH );
	const double N           = 2.5;
	const double MIN_I       = MIN_X;
	const double MIN_HEIGHT  = ( 0.25 *  PTS_PER_INCH );
	const double MIN_QUIET   = ( 0.10 *  PTS_PER_INCH );

	const double MIN_TEXT_AREA_HEIGHT = 14.0;
	const double MIN_TEXT_SIZE        = 10.0;

}


namespace glbarcode
{

	/*
	 * Static Code39 barcode creation method
	 */
	Barcode* BarcodeCode39::create( std::string           data,
					double                w,
					double                h,
					BarcodeOptions const& options )
	{
		return new BarcodeCode39( data, w, h, options );
	}


	/*
	 * Code39 barcode constructor
	 */
	BarcodeCode39::BarcodeCode39( std::string           data,
				      double                w,
				      double                h,
				      BarcodeOptions const& options )
	{
		init( data, w, h, options );
	}


	/*
	 * Code39 data validation, implements Barcode::validate()
	 */
	bool BarcodeCode39::validate( std::string raw_data )
	{
		for ( int i = 0; i < raw_data.size(); i++ )
		{
			char c = toupper( raw_data[i] );

			if ( alphabet.find(c) == std::string::npos )
			{
				return false;
			}
		}

		return true;
	}


	/*
	 * Code39 data encoding, implements Barcode::encode()
	 */
	std::string BarcodeCode39::encode( std::string canon_data )
	{
		std::string code;

		/* Left frame symbol */
		code += frame_symbol;
		code += "i";

		int sum = 0;
		for ( int i=0; i < canon_data.size(); i++ )
		{
			int c_value = alphabet.find( toupper( canon_data[i] ) );

			code += symbols[c_value];
			code += "i";

			sum += c_value;
		}

		if ( m_options.m_checksum_flag )
		{
			code += symbols[sum % 43];
			code += "i";
		}

		/* Right frame bar */
		code += frame_symbol;

		return code;
	}


	/*
	 * Code39 prepare text for display, implements Barcode::prepare_text()
	 */
	std::string BarcodeCode39::prepare_text( std::string raw_data )
	{
		std::string display_text;

		for ( int i = 0; i < raw_data.size(); i++ )
		{
			display_text += toupper( raw_data[i] );
		}

		return display_text;
	}


	/*
	 * Code39 vectorization, implements Barcode::vectorize()
	 */
	void BarcodeCode39::vectorize( std::string coded_data,
				       std::string display_text )
	{
		/* determine width and establish horizontal scale */
		double data_size = m_cooked_data.size();
		double min_l;
		if (!m_options.m_checksum_flag)
		{
			min_l = (data_size + 2)*(3*N + 6)*MIN_X + (data_size + 1)*MIN_I;
		}
		else
		{
			min_l = (data_size + 3)*(3*N + 6)*MIN_X + (data_size + 2)*MIN_I;
		}
        
		double scale;
		if ( m_w == 0 )
		{
			scale = 1.0;
		}
		else
		{
			scale = m_w / (min_l + 2*MIN_QUIET);

			if ( scale < 1.0 )
			{
				scale = 1.0;
			}
		}
		double width = min_l * scale;

		/* determine text parameters */
		double h_text_area = scale * MIN_TEXT_AREA_HEIGHT;
		double text_size   = scale * MIN_TEXT_SIZE;

		/* determine height of barcode */
		double height = m_options.m_text_flag ? m_h - h_text_area : m_h;
		height = std::max( height, std::max( 0.15*width, MIN_HEIGHT ) );

		/* determine horizontal quiet zone */
		double x_quiet = std::max( (10 * scale * MIN_X), MIN_QUIET );

		/* Now traverse the code string and draw each bar */
		double x1 = x_quiet;
		for ( int i=0; i < coded_data.size(); i++ )
		{
			double lwidth;
				
			switch ( coded_data[i] )
			{

			case 'i':
				/* Inter-character gap */
				x1 += scale * MIN_I;
				break;

			case 'N':
				/* Narrow bar */
				lwidth = scale*MIN_X;
				add_line( x1, 0.0, lwidth, height );
				x1 += scale * MIN_X;
				break;

			case 'W':
				/* Wide bar */
				lwidth = scale*N*MIN_X;
				add_line( x1, 0.0, lwidth, height );
				x1 += scale * N * MIN_X;
				break;

			case 'n':
				/* Narrow space */
				x1 += scale * MIN_X;
				break;

			case 'w':
				/* Wide space */
				x1 += scale * N * MIN_X;
				break;

			default:
				// NOT REACHED
				break;
			}
		}

		if ( m_options.m_text_flag )
		{
			std::string starred_text = "*" + display_text + "*";
			add_text( x_quiet + width/2, height + (h_text_area-text_size)/2, text_size, starred_text );
		}

		/* Overwrite requested size with actual size. */
		m_w = width + 2*x_quiet;
		m_h = m_options.m_text_flag ? height + h_text_area : height;
	}

}
