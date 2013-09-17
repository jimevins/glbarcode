/*  BarcodeUpcBase.cpp
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

#include "BarcodeUpcBase.h"

#include "Constants.h"

#include <cctype>
#include <string>
#include <algorithm>
#include <iostream>


using namespace glbarcode::Constants;


namespace
{
	/*
	 * Symbology
	 */
	const std::string symbols[10][2] = {
		/*          Odd     Even  */
		/*    Left: sBsB    sBsB  */
		/*   Right: BsBs    ----  */
		/*                        */
		/* 0 */  { "3211", "1123" },
		/* 1 */  { "2221", "1222" },
		/* 2 */  { "2122", "2212" },
		/* 3 */  { "1411", "1141" },
		/* 4 */  { "1132", "2311" },
		/* 5 */  { "1231", "1321" },
		/* 6 */  { "1114", "4111" },
		/* 7 */  { "1312", "2131" },
		/* 8 */  { "1213", "3121" },
		/* 9 */  { "3112", "2113" }
	};

	const std::string s_symbol = "111";   /* BsB */
	const std::string e_symbol = "111";   /* BsB */
	const std::string m_symbol = "11111"; /* sBsBs */


	/*
	 * Parity selection
	 */
	typedef enum { P_ODD, P_EVEN } Parity;

	const Parity parity[10][6] = {
		/*                Pos 1,  Pos 2,  Pos 3,  Pos 4,  Pos 5,  Pos 6 */
		/* 0 (UPC-A) */ { P_ODD,  P_ODD,  P_ODD,  P_ODD,  P_ODD,  P_ODD  },
		/* 1         */ { P_ODD,  P_ODD,  P_EVEN, P_ODD,  P_EVEN, P_EVEN },
		/* 2         */ { P_ODD,  P_ODD,  P_EVEN, P_EVEN, P_ODD,  P_EVEN },
		/* 3         */ { P_ODD,  P_ODD,  P_EVEN, P_EVEN, P_EVEN, P_ODD  },
		/* 4         */ { P_ODD,  P_EVEN, P_ODD,  P_ODD,  P_EVEN, P_EVEN },
		/* 5         */ { P_ODD,  P_EVEN, P_EVEN, P_ODD,  P_ODD,  P_EVEN },
		/* 6         */ { P_ODD,  P_EVEN, P_EVEN, P_EVEN, P_ODD,  P_ODD  },
		/* 7         */ { P_ODD,  P_EVEN, P_ODD,  P_EVEN, P_ODD,  P_EVEN },
		/* 8         */ { P_ODD,  P_EVEN, P_ODD,  P_EVEN, P_EVEN, P_ODD  },
		/* 9         */ { P_ODD,  P_EVEN, P_EVEN, P_ODD,  P_EVEN, P_ODD  }
	};


	/*
	 * Constants
	 */
	const int    QUIET_MODULES   = 9;

	const double BASE_MODULE_SIZE      = ( 0.01 *  PTS_PER_INCH );
	const double BASE_FONT_SIZE        = 7;
	const double BASE_TEXT_AREA_HEIGHT = 11;
}


namespace glbarcode
{

	/*
	 * UPC data validation, implements Barcode1dBase::validate()
	 */
	bool BarcodeUpcBase::validate( std::string raw_data )
	{
		int n_digits = 0;

		for ( int i = 0; i < raw_data.size(); i++ )
		{
			if ( isdigit( raw_data[i] ) )
			{
				n_digits++;
			}
			else if ( raw_data[i] != ' ')
			{
				/* Only allow digits and spaces -- ignoring spaces. */
				return false;
			}
		}

		/* validate n_digits (call implementation from concrete class) */
		return validate_digits( n_digits );
	}


	/*
	 * UPC data encoding, implements Barcode1dBase::encode()
	 */
	std::string BarcodeUpcBase::encode( std::string cooked_data )
	{
		int sum_odd  = 0;
		int sum_even = m_first_digit_val;

		std::string code;

		/* Left frame symbol */
		code += s_symbol;

		/* Left 6 digits */
		for ( int i = 0; i < 6; i++ )
		{
			int c_value = cooked_data[i] - '0';
			code += symbols[ c_value ][ parity[ m_first_digit_val ][ i ] ];

			if ( (i & 1) == 0 )
			{
				sum_odd += c_value;
			}
			else
			{
				sum_even += c_value;
			}
		}

		/* Middle frame symbol */
		code += m_symbol;

		/* Right 5 digits */
		for ( int i = 6; i < 11; i++ )
		{
			int c_value = cooked_data[i] - '0';
			code += symbols[c_value][P_ODD];

			if ( (i & 1) == 0 )
			{
				sum_odd += c_value;
			}
			else
			{
				sum_even += c_value;
			}
		}

		/* Check digit */
		m_check_digit_val = (3*sum_odd + sum_even) % 10;
		if ( m_check_digit_val != 0 )
		{
			m_check_digit_val = 10 - m_check_digit_val;
		}
		code += symbols[m_check_digit_val][P_ODD];

		/* Right frame symbol */
		code += e_symbol;

		/* Append a final zero length space to make the length of the encoded string even. */
		/* This is because vectorize() handles bars and spaces in pairs. */
		code += "0";

		return code;
	}



	/*
	 * UPC prepare text for display, implements Barcode1dBase::prepare_text()
	 */
	std::string BarcodeUpcBase::prepare_text( std::string raw_data )
	{
		std::string display_text;

		for ( int i = 0; i < raw_data.size(); i++ )
		{
			if ( isdigit( raw_data[i] ) )
			{
				display_text += raw_data[i];
			}
		}

		display_text += (m_check_digit_val + '0');

		return display_text;
	}


	/*
	 * UPC vectorization, implements Barcode1dBase::vectorize()
	 */
	void BarcodeUpcBase::vectorize( std::string coded_data,
					std::string display_text,
					std::string cooked_data,
					double      &w,
					double      &h )
	{
		/* determine width and establish horizontal scale */
		int n_modules     = 7*(cooked_data.size()+1) + 11;

		double scale;
		if ( w == 0 )
		{
			scale = 1.0;
		}
		else
		{
			scale = w / ((n_modules + 2*QUIET_MODULES) * BASE_MODULE_SIZE);

			if ( scale < 1.0 )
			{
				scale = 1.0;
			}
		}
		double mscale = scale * BASE_MODULE_SIZE;

		double width       = mscale * (n_modules + 2*QUIET_MODULES);
		double x_quiet     = mscale * QUIET_MODULES;

		/* determine bar height */
		double h_text_area = scale * BASE_TEXT_AREA_HEIGHT;
		double h_bar1      = std::max( (h - h_text_area), width/2 );
		double h_bar2      = h_bar1 + h_text_area/2;

		/* determine text parameters */
		double text_size1    = scale * BASE_FONT_SIZE;
		double text_size2    = 0.75*text_size1;

		double text_x1_left  = x_quiet + mscale*(0.25*n_modules + 0.5*m_end_bars_modules - 0.75);
		double text_x1_right = x_quiet + mscale*(0.75*n_modules - 0.5*m_end_bars_modules + 0.75);
		double text_x2_left  = 0.5*x_quiet;
		double text_x2_right = 1.5*x_quiet + mscale*n_modules;

		double text_y1       = h_bar2 + text_size1/4;
		double text_y2       = h_bar2 + text_size2/4;


		/* now traverse the code string and draw each bar */
		int n_bars_spaces = coded_data.size() - 1; /* coded data has dummy "0" on end. */

		double x_modules = 0;
		for ( int i = 0; i < n_bars_spaces; i += 2 )
		{
			double h_bar;

			if ( ( (x_modules > m_end_bars_modules) && (x_modules < (n_modules/2-1))               ) ||
			     ( (x_modules > (n_modules/2+1)) && (x_modules < (n_modules-m_end_bars_modules)) ) )
			{
				h_bar = h_bar1;
			}
			else
			{
				h_bar = h_bar2;
			}

			/* Bar */
			int w_bar = coded_data[i] - '0';
			add_line( x_quiet + mscale*x_modules, 0.0, mscale*w_bar, h_bar );
			x_modules += w_bar;

			/* Space */
			int w_space = coded_data[i+1] - '0';
			x_modules += w_space;
		}

		/* draw text (call implementation from concrete class) */
		vectorize_text( display_text,
				text_size1, text_size2,
				text_x1_left, text_x1_right, text_y1,
				text_x2_left, text_x2_right, text_y2 );

		/* Overwrite requested size with actual size. */
		w = width;
		h = h_bar1 + h_text_area;
	}

}
