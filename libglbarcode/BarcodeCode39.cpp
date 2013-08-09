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

#include "Consts.h"

#include <ctype.h>
#include <algorithm>


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
	const double MIN_X       = ( 0.01 *  glbarcode::consts::PTS_PER_INCH );
	const double N           = 2.5;
	const double MIN_I       = MIN_X;
	const double MIN_HEIGHT  = ( 0.25 *  glbarcode::consts::PTS_PER_INCH );
	const double MIN_QUIET   = ( 0.10 *  glbarcode::consts::PTS_PER_INCH );

	const double MIN_TEXT_AREA_HEIGHT = 14.0;
	const double MIN_TEXT_SIZE        = 10.0;

}


namespace glbarcode
{

	Barcode* BarcodeCode39::create( std::string data,
					double      w,
					double      h,
					bool        text_flag,
					bool        checksum_flag )
	{
		BarcodeCode39* barcode = new BarcodeCode39();

		barcode->init( data, w, h, text_flag, checksum_flag );

		return barcode;
	}


	/**
	 * Code39 data validation method
	 */
	bool BarcodeCode39::validate( std::string data )
	{
		for ( int i = 0; i < data.size(); i++ )
		{
			char c = toupper( data[i] );

			if ( alphabet.find(c) == std::string::npos )
			{
				return false;
			}
		}

		return true;
	}


	/**
	 * Code39 data encoding method
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

		if ( checksum_flag )
		{
			code += symbols[sum % 43];
			code += "i";
		}

		/* Right frame bar */
		code += frame_symbol;

		return code;
	}


	/**
	 * Code39 vectorize method
	 */
	void BarcodeCode39::vectorize( std::string coded_data,
				       std::string data,
				       std::string text )
	{
		/* determine width and establish horizontal scale */
		double min_l;
		if (!checksum_flag)
		{
			min_l = (data.size() + 2)*(3*N + 6)*MIN_X + (data.size() + 1)*MIN_I;
		}
		else
		{
			min_l = (data.size() + 3)*(3*N + 6)*MIN_X + (data.size() + 2)*MIN_I;
		}
        
		double scale;
		if ( w == 0 )
		{
			scale = 1.0;
		}
		else
		{
			scale = w / (min_l + 2*MIN_QUIET);

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
		double height = text_flag ? h - h_text_area : h;
		height = std::max( height, std::max( 0.15*width, MIN_HEIGHT ) );

		/* determine horizontal quiet zone */
		double x_quiet = std::max( (10 * scale * MIN_X), MIN_QUIET );

		/* Now traverse the code string and draw each bar */
		double x1 = x_quiet;
		for ( int i=0; i < coded_data.size(); i++ )
		{
				
			switch ( coded_data[i] )
			{

			case 'i':
				/* Inter-character gap */
				x1 += scale * MIN_I;
				break;

			case 'N':
				/* Narrow bar */
				add_box( x1, 0.0, (scale*MIN_X - consts::INK_BLEED), height );
				x1 += scale*MIN_X;
				break;

			case 'W':
				/* Wide bar */
				add_box( x1, 0.0, (scale*N*MIN_X - consts::INK_BLEED), height );
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

		if ( text_flag )
		{
			std::string starred_text = "*" + text + "*";
			add_text( x_quiet + width/2, height + (h_text_area-text_size)/2, text_size, starred_text );
		}

		/* Overwrite requested size with actual size. */
		w = width + 2*x_quiet;
		h = text_flag ? height + h_text_area : height;
	}

}
