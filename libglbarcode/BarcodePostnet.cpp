/*  BarcodePostnet.cpp
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

#include "BarcodePostnet.h"

#include "Constants.h"

#include <ctype.h>
#include <algorithm>


using namespace glbarcode::Constants;


namespace
{
	/*
	 * Encoding symbology
	 */
	const std::string symbols[] = {
		/* 0 */ "11000",
		/* 1 */ "00011",
		/* 2 */ "00101",
		/* 3 */ "00110",
		/* 4 */ "01001",
		/* 5 */ "01010",
		/* 6 */ "01100",
		/* 7 */ "10001",
		/* 8 */ "10010",
		/* 9 */ "10100"
	};

	const std::string frame_symbol = "1";


	/*
	 * Constants
	 */
	const double POSTNET_BAR_WIDTH      = ( 0.02    * PTS_PER_INCH );
	const double POSTNET_FULLBAR_HEIGHT = ( 0.125   * PTS_PER_INCH );
	const double POSTNET_HALFBAR_HEIGHT = ( 0.05    * PTS_PER_INCH );
	const double POSTNET_BAR_PITCH      = ( 0.04545 * PTS_PER_INCH );
	const double POSTNET_HORIZ_MARGIN   = ( 0.125   * PTS_PER_INCH );
	const double POSTNET_VERT_MARGIN    = ( 0.04    * PTS_PER_INCH );

}


namespace glbarcode
{

	/*
	 * Static Postnet barcode creation method
	 */
	Barcode* BarcodePostnet::create( std::string data,
					 double      w,
					 double      h,
					 bool        text_flag,
					 bool        checksum_flag )
	{
		return new BarcodePostnet( data, w, h, text_flag, checksum_flag );
	}


	/*
	 * Postnet barcode constructor
	 */
	BarcodePostnet::BarcodePostnet( std::string data,
					double      w,
					double      h,
					bool        text_flag,
					bool        checksum_flag )
	{
		init( data, w, h, text_flag, checksum_flag );
	}


	/*
	 * Postnet validate number of digits
	 */
	bool BarcodePostnet::validate_digits( int n_digits )
	{
		/* Accept any valid USPS POSTNET length. */
		return (n_digits == 5) || (n_digits == 9) || (n_digits == 11);
	}


	/*
	 * Postnet data validation, implements Barcode::validate()
	 */
	bool BarcodePostnet::validate( std::string raw_data )
	{
		int n_digits = 0;
		for ( int i = 0; i < raw_data.size(); i++ )
		{
			if ( isdigit( raw_data[i] ) )
			{
				n_digits++;
			}
			else if ( (raw_data[i] != '-') && (raw_data[i] != ' ') )
			{
				/* Only allow digits, dashes, and spaces. */
				return false;
			}
		}

		return validate_digits( n_digits );
	}


	/*
	 * Postnet data encoding, implements Barcode::encode()
	 */
	std::string BarcodePostnet::encode( std::string canon_data )
	{
		std::string code;

		/* Left frame bar */
		code += frame_symbol;

		/* process each digit, adding approptiate symbol */
		int sum = 0;
		for ( int i = 0; i < canon_data.size(); i++ )
		{
			if ( isdigit( canon_data[i] ) )
			{
				/* Only translate the digits (0-9) */
				int d = canon_data[i] - '0';
				code += symbols[d];
				sum += d;
			}
		}

		/* Create mandatory correction character */
		code += symbols[ (10 - (sum % 10)) % 10 ];

		/* Right frame bar */
		code += frame_symbol;

		return code;
	}


	/*
	 * Postnet vectorization, implements Barcode::vectorize()
	 */
	void BarcodePostnet::vectorize( std::string coded_data,
					std::string display_text )
	{
		double x = POSTNET_HORIZ_MARGIN;
		for ( int i=0; i < coded_data.size(); i++ )
		{
			double length, width;

			double y = POSTNET_VERT_MARGIN;

			switch ( coded_data[i] )
			{
			case '0':
				y += POSTNET_FULLBAR_HEIGHT - POSTNET_HALFBAR_HEIGHT;
				length = POSTNET_HALFBAR_HEIGHT;
				break;
			case '1':
				length = POSTNET_FULLBAR_HEIGHT;
				break;
			default:
				// Not reached
				break;
			}
			width = POSTNET_BAR_WIDTH;

			add_line( x, y, width, length );

			x += POSTNET_BAR_PITCH;
		}

		/* Overwrite requested size with actual size. */
		m_w = x + POSTNET_HORIZ_MARGIN;
		m_h = POSTNET_FULLBAR_HEIGHT + 2 * POSTNET_VERT_MARGIN;
	}

}
