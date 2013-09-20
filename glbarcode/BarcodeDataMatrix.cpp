/*  BarcodeDataMatrix.cpp
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

#include "BarcodeDataMatrix.h"

#include "Constants.h"

#include <stdint.h>
#include <vector>
#include <cctype>
#include <algorithm>


using namespace glbarcode;
using namespace glbarcode::Constants;


namespace
{
	/* ASCII Encoding Codeword values */
	const uint8_t CW_PAD     = 129;
	const uint8_t CW_NUM_00  = 130;
	const uint8_t CW_UPSHIFT = 235;


	typedef struct
	{
		int   n_data_cw;
		int   n_xtotal;
		int   n_ytotal;
		int   n_blocks_1;
		int   n_blocks_2;
		int   n_data_cw_block_1;
		int   n_data_cw_block_2;
		int   n_rs_cw_block;
		int   a_select;
		int   n_xregions;
		int   n_yregions;
		int   n_xregion;
		int   n_yregion;
	} DMParameterEntry;

	const DMParameterEntry params[] =
	{
		{  1558, 144, 144, 8, 2, 166, 155, 62, 14, 6, 6, 22, 22 },
		{  1304, 132, 132, 8, 0, 163,   0, 62, 14, 6, 6, 20, 20 },
		{  1050, 120, 120, 6, 0, 175,   0, 68, 15, 6, 6, 18, 18 },
		{   816, 104, 104, 6, 0, 136,   0, 56, 13, 4, 4, 24, 24 },
		{   696,  96,  96, 4, 0, 174,   0, 68, 15, 4, 4, 22, 22 },
		{   576,  88,  88, 4, 0, 144,   0, 56, 13, 4, 4, 20, 20 },
		{   456,  80,  80, 4, 0, 114,   0, 48, 12, 4, 4, 18, 18 },
		{   368,  72,  72, 4, 0,  92,   0, 36, 10, 4, 4, 16, 16 },
		{   280,  64,  64, 2, 0, 140,   0, 56, 13, 4, 4, 14, 14 },
		{   204,  52,  52, 2, 0, 102,   0, 42, 11, 2, 2, 24, 24 },
		{   174,  48,  48, 1, 0, 174,   0, 68, 15, 2, 2, 22, 22 },
		{   144,  44,  44, 1, 0, 144,   0, 56, 13, 2, 2, 20, 20 },
		{   114,  40,  40, 1, 0, 114,   0, 48, 12, 2, 2, 18, 18 },
		{    86,  36,  36, 1, 0,  86,   0, 42, 11, 2, 2, 16, 16 },
		{    62,  32,  32, 1, 0,  62,   0, 36, 10, 2, 2, 14, 14 },
		{    44,  26,  26, 1, 0,  44,   0, 28,  9, 1, 1, 24, 24 },
		{    36,  24,  24, 1, 0,  36,   0, 24,  8, 1, 1, 22, 22 },
		{    30,  22,  22, 1, 0,  30,   0, 20,  7, 1, 1, 20, 20 },
		{    22,  20,  20, 1, 0,  22,   0, 18,  6, 1, 1, 18, 18 },
		{    18,  18,  18, 1, 0,  18,   0, 14,  5, 1, 1, 16, 16 },
		{    12,  16,  16, 1, 0,  12,   0, 12,  4, 1, 1, 14, 14 },
		{     8,  14,  14, 1, 0,   8,   0, 10,  2, 1, 1, 12, 12 },
		{     5,  12,  12, 1, 0,   5,   0,  7,  1, 1, 1, 10, 10 },
		{     3,  10,  10, 1, 0,   3,   0,  5,  0, 1, 1,  8,  8 },
		{     0,   0,   0, 0, 0,   0,   0,  0,  0, 0, 0,  0,  0 } /* End of Table */
	};


	const uint8_t a[16][68] =
	{
		/* 0. Factor table for 5 RS codewords */
		{
			228,  48,  15, 111,  62,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
			  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
			  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
			  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0
		},

		/* 1. Factor table for 7 RS codewords */
		{
			 23,  68, 144, 134, 240,  92, 254,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
			  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
			  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
			  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
		},

		/* 2. Factor table for 10 RS codewords */
		{
			 28,  24, 185, 166, 223, 248, 116, 255, 110,  61,   0,   0,   0,   0,   0,   0,   0,
			  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
			  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
			  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
		},

		/* 3. Factor table for 11 RS codewords */
		{
			175, 138, 205,  12, 194, 168,  39, 245,  60,  97, 120,   0,   0,   0,   0,   0,   0,
			  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
			  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
			  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
		},

		/* 4. Factor table for 12 RS codewords */
		{
			 41, 153, 158,  91,  61,  42, 142, 213,  97, 178, 100, 242,   0,   0,   0,   0,   0,
			  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
			  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
			  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
		},

		/* 5. Factor table for 14 RS codewords */
		{
			156,  97, 192, 252,  95,   9, 157, 119, 138,  45,  18, 186,  83, 185,   0,   0,   0,
			  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
			  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
			  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
		},

		/* 6. Factor table for 18 RS codewords */
		{
			 83, 195, 100,  39, 188,  75,  66,  61, 241, 213, 109, 129,  94, 254, 225,  48,	 90,
			188,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
			  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
			  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0
		},

		/* 7. Factor table for 20 RS codewords */
		{
			 15, 195, 244,   9, 233,  71, 168,   2, 188, 160, 153, 145, 253,  79, 108,  82,	 27,
			174, 186, 172,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
			  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
			  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0
		},

		/* 8. Factor table for 24 RS codewords */
		{
			 52, 190,  88, 205, 109,  39, 176,  21, 155, 197, 251, 223, 155,  21,   5, 172,	254,
			124,  12, 181, 184,  96,  50, 193,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
			  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
			  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0
		},

		/* 9. Factor table for 28 RS codewords */
		{
			211, 231,  43,  97,  71,  96, 103, 174,  37, 151, 170,  53,  75,  34, 249, 121,  17,
			138, 110, 213, 141, 136, 120, 151, 233, 168,  93, 255,   0,   0,   0,   0,   0,   0,
			  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
			  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0
		},

		/* 10. Factor table for 36 RS codewords */
		{
			245, 127, 242, 218, 130, 250, 162, 181, 102, 120,  84, 179, 220, 251,  80, 182,	229,
			 18,   2,   4,  68,  33, 101, 137,  95, 119, 115,  44, 175, 184,  59,  25, 225,  98,
			 81, 112,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
			  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0
		},

		/* 11. Factor table for 42 RS codewords */
		{
			 77, 193, 137,  31,  19,  38,  22, 153, 247, 105, 122,   2, 245, 133, 242,   8,	175,
			 95, 100,   9, 167, 105, 214, 111,  57, 121,  21,   1, 253,  57,  54, 101, 248, 202,
			 69,  50, 150, 177, 226,   5,   9,   5,   0,   0,   0,   0,   0,   0,   0,   0,   0,
			  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0
		},

		/* 12. Factor table for 48 RS codewords */
		{
			245, 132, 172, 223,  96,  32, 117,  22, 238, 133, 238, 231, 205, 188, 237,  87,	191,
			106,  16, 147, 118,  23,  37,  90, 170, 205, 131,  88, 120, 100,  66, 138, 186, 240,
			 82,  44, 176,  87, 187, 147, 160, 175,  69, 213,  92, 253, 225,  19,   0,   0,   0,
			  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0
		},

		/* 13. Factor table for 56 RS codewords */
		{
			175,   9, 223, 238,  12,  17, 220, 208, 100,  29, 175, 170, 230, 192, 215, 235,	150,
			159,  36, 223,  38, 200, 132,  54, 228, 146, 218, 234, 117, 203,  29, 232, 144, 238,
			 22, 150, 201, 117,  62, 207, 164,  13, 137, 245, 127,  67, 247,  28, 155,  43, 203,
			107, 233,  53, 143,  46,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0
		},

		/* 14. Factor table for 62 RS codewords */
		{
			242,  93, 169,  50, 144, 210,  39, 118, 202, 188, 201, 189, 143, 108, 196,  37,	185,
			112, 134, 230, 245,  63, 197, 190, 250, 106, 185, 221, 175,  64, 114,  71, 161,  44,
			147,   6,  27, 218,  51,  63,  87,  10,  40, 130, 188,  17, 163,  31, 176, 170,   4,
			107, 232,   7,  94, 166, 224, 124,  86,  47,  11, 204,   0,   0,   0,   0,   0,   0
		},

		/* 15. Factor table for 68 RS codewords */
		{
			220, 228, 173,  89, 251, 149, 159,  56,  89,  33, 147, 244, 154,  36,  73, 127,	213,
			136, 248, 180, 234, 197, 158, 177,  68, 122,  93, 213,  15, 160, 227, 236,  66, 139,
			153, 185, 202, 167, 179,  25, 220, 232,  96, 210, 231, 136, 223, 239, 181, 241,  59,
			 52, 172,  25,  49, 232, 211, 189,  64,  54, 108, 153, 132,  63,  96, 103,  82, 186
		}
	};


	const int Log[] =
	{
		-255, 255,   1, 240,   2, 225, 241,  53,   3,  38, 226, 133, 242,  43,  54, 210,
		   4, 195,  39, 114, 227, 106, 134,  28, 243, 140,  44,  23,  55, 118, 211, 234,
		   5, 219, 196,  96,  40, 222, 115, 103, 228,  78, 107, 125, 135,   8,  29, 162,
		 244, 186, 141, 180,  45,  99,  24,  49,  56,  13, 119, 153, 212, 199, 235,  91,
		   6,  76, 220, 217, 197,  11,  97, 184,  41,  36, 223, 253, 116, 138, 104, 193,
		 229,  86,  79, 171, 108, 165, 126, 145, 136,  34,   9,  74,  30,  32, 163,  84,
		 245, 173, 187, 204, 142,  81, 181, 190,  46,  88, 100, 159,  25, 231,  50, 207,
		  57, 147,  14,  67, 120, 128, 154, 248, 213, 167, 200,  63, 236, 110,  92, 176,
		   7, 161,  77, 124, 221, 102, 218,  95, 198,  90,  12, 152,  98,  48, 185, 179,
		  42, 209,  37, 132, 224,  52, 254, 239, 117, 233, 139,  22, 105,  27, 194, 113,
		 230, 206,  87, 158,  80, 189, 172, 203, 109, 175, 166,  62, 127, 247, 146,  66,
		 137, 192,  35, 252,  10, 183,  75, 216,  31,  83,  33,  73, 164, 144,  85, 170,
		 246,  65, 174,  61, 188, 202, 205, 157, 143, 169,  82,  72, 182, 215, 191, 251,
		  47, 178,  89, 151, 101,  94, 160, 123,  26, 112, 232,  21,  51, 238, 208, 131,
		  58,  69, 148,  18,  15,  16,  68,  17, 121, 149, 129,  19, 155,  59, 249,  70,
		 214, 250, 168,  71, 201, 156,  64,  60, 237, 130, 111,  20,  93, 122, 177, 150
	};


	const int Alog[] =
	{
		  1,   2,   4,   8,  16,  32,  64, 128,  45,  90, 180,  69, 138,  57, 114, 228,
		229, 231, 227, 235, 251, 219, 155,  27,  54, 108, 216, 157,  23,  46,  92, 184,
		 93, 186,  89, 178,  73, 146,   9,  18,  36,  72, 144,  13,  26,  52, 104, 208,
		141,  55, 110, 220, 149,   7,  14,  28,  56, 112, 224, 237, 247, 195, 171, 123,
		246, 193, 175, 115, 230, 225, 239, 243, 203, 187,  91, 182,  65, 130,  41,  82,
		164, 101, 202, 185,  95, 190,  81, 162, 105, 210, 137,  63, 126, 252, 213, 135,
		 35,  70, 140,  53, 106, 212, 133,  39,  78, 156,  21,  42,  84, 168, 125, 250,
		217, 159,  19,  38,  76, 152,  29,  58, 116, 232, 253, 215, 131,  43,  86, 172,
		117, 234, 249, 223, 147,  11,  22,  44,  88, 176,  77, 154,  25,  50, 100, 200,
		189,  87, 174, 113, 226, 233, 255, 211, 139,  59, 118, 236, 245, 199, 163, 107,
		214, 129,  47,  94, 188,  85, 170, 121, 242, 201, 191,  83, 166,  97, 194, 169,
		127, 254, 209, 143,  51, 102, 204, 181,  71, 142,  49,  98, 196, 165, 103, 206,
		177,  79, 158,  17,  34,  68, 136,  61, 122, 244, 197, 167,  99, 198, 161, 111,
		222, 145,  15,  30,  60, 120, 240, 205, 183,  67, 134,  33,  66, 132,  37,  74,
		148,   5,  10,  20,  40,  80, 160, 109, 218, 153,  31,  62, 124, 248, 221, 151,
		  3,   6,  12,  24,  48,  96, 192, 173, 119, 238, 241, 207, 179,  75, 150,   1
	};


	int ecc200_encode( const std::string & data, std::vector<uint8_t> & data_cw )
	{
		/*
		 * Encode data into codewords using ASCII encoding method.
		 */
		for ( int i = 0; i < data.size(); i++ )
		{
			uint8_t c = data[i];

			if ( c < 128 )
			{
				uint8_t c1 = data[i+1];

				if ( (i < (data.size()-1)) && isdigit(c) && isdigit(c1) )
				{
					/* 2-digit data 00 - 99 */
					data_cw.push_back( CW_NUM_00 + (c-'0')*10 + (c1-'0') );
					i++; /* skip next input char */
				}
				else
				{
					/* Simple ASCII data (ASCII value + 1) */
					data_cw.push_back( c + 1 );
				}
			}
			else
			{
				/* Extended ASCII range (128-255) */
				data_cw.push_back( CW_UPSHIFT );
				data_cw.push_back( c - 127 );
			}
		}

		return data_cw.size();
	}


	const DMParameterEntry * ecc200_best_size_params( int n_raw_cw )
	{

		if ( n_raw_cw > 1558 )
		{
			return NULL;
		}

		int i_param = 0;

		while ( n_raw_cw < params[i_param].n_data_cw )
		{
			i_param++;
		}

		return &params[i_param-1];
	}


	void ecc200_fill( std::vector<uint8_t> & data_cw, int n_raw_cw, int n_data_cw )
	{
		int n_fill_cw   = n_data_cw - n_raw_cw;

		if ( n_fill_cw > 0 )
		{
			data_cw.push_back( CW_PAD );
		}

		for ( int i = n_raw_cw + 1; i < n_data_cw; i++ )
		{
			int r = (149*(i+1))%253 + 1;
			data_cw.push_back( (CW_PAD + r) % 254 );
		}
	}


	void ecc200_rs_block( const std::vector<uint8_t> & data_cw,
			      std::vector<uint8_t>       & rs_cw,
			      int                          n,
			      int                          nc,
			      int                          a_select,
			      int                          offset,
			      int                          stride )
	{
		for ( int i = 0; i < n; i++ )
		{
			uint8_t k = rs_cw[offset] ^ data_cw[i*stride + offset];

			for ( int j = 0; j < (nc-1); j++ )
			{
				uint8_t c = a[a_select][nc-1-j];

				if ( k != 0 )
				{
					rs_cw[j*stride+offset] = rs_cw[(j+1)*stride + offset] ^ Alog[ (Log[k] + Log[c]) % 255 ];
				}
				else
				{
					rs_cw[j*stride+offset] = rs_cw[(j+1)*stride + offset];
				}
			}
			uint8_t c = a[a_select][0];
			if ( k != 0 )
			{
				rs_cw[(nc-1)*stride + offset] = Alog[ (Log[k] + Log[c]) % 255 ];
			}
			else
			{
				rs_cw[(nc-1)*stride + offset] = 0;
			}
		}
	}


	void module( Simple2dMatrix<bool> & matrix,
		     Simple2dMatrix<bool> & used,
		     int                    ix,
		     int                    iy,
		     uint8_t                codeword,
		     int                    bit )
	{
		if ( iy < 0 )
		{
			ix += 4 - ((matrix.ny()+4) % 8 );
			iy += matrix.ny();
		}

		if ( ix < 0 )
		{
			ix += matrix.nx();
			iy += 4 - ((matrix.nx()+4) % 8 );
		}

		used[iy][ix] = true;

		if ( codeword & (1 << bit) )
		{
			matrix[iy][ix] = true;
		}
	}


	void corner1( Simple2dMatrix<bool> & matrix,
		      Simple2dMatrix<bool> & used,
		      uint8_t                codeword )
	{
		int nx = matrix.nx();
		int ny = matrix.ny();

		module( matrix, used, 0,    ny-1, codeword, 7 );
		module( matrix, used, 1,    ny-1, codeword, 6 );
		module( matrix, used, 2,    ny-1, codeword, 5 );
		module( matrix, used, nx-2, 0,    codeword, 4 );
		module( matrix, used, nx-1, 0,    codeword, 3 );
		module( matrix, used, nx-1, 1,    codeword, 2 );
		module( matrix, used, nx-1, 2,    codeword, 1 );
		module( matrix, used, nx-1, 3,    codeword, 0 );
	}


	void corner2( Simple2dMatrix<bool> & matrix,
		      Simple2dMatrix<bool> & used,
		      uint8_t                codeword )
	{
		int nx = matrix.nx();
		int ny = matrix.ny();

		module( matrix, used, 0,    ny-3, codeword, 7 );
		module( matrix, used, 0,    ny-2, codeword, 6 );
		module( matrix, used, 0,    ny-1, codeword, 5 );
		module( matrix, used, nx-4, 0,    codeword, 4 );
		module( matrix, used, nx-3, 0,    codeword, 3 );
		module( matrix, used, nx-2, 0,    codeword, 2 );
		module( matrix, used, nx-1, 0,    codeword, 1 );
		module( matrix, used, nx-1, 1,    codeword, 0 );
	}


	void corner3( Simple2dMatrix<bool> & matrix,
		      Simple2dMatrix<bool> & used,
		      uint8_t                codeword )
	{
		int nx = matrix.nx();
		int ny = matrix.ny();

		module( matrix, used, 0,    ny-3, codeword, 7 );
		module( matrix, used, 0,    ny-2, codeword, 6 );
		module( matrix, used, 0,    ny-1, codeword, 5 );
		module( matrix, used, nx-2, 0,    codeword, 4 );
		module( matrix, used, nx-1, 0,    codeword, 3 );
		module( matrix, used, nx-1, 1,    codeword, 2 );
		module( matrix, used, nx-1, 2,    codeword, 1 );
		module( matrix, used, nx-1, 3,    codeword, 0 );
	}


	void corner4( Simple2dMatrix<bool> & matrix,
		      Simple2dMatrix<bool> & used,
		      uint8_t                codeword )
	{
		int nx = matrix.nx();
		int ny = matrix.ny();

		module( matrix, used, 0,    ny-1, codeword, 7 );
		module( matrix, used, nx-1, ny-1, codeword, 6 );
		module( matrix, used, nx-3, 0,    codeword, 5 );
		module( matrix, used, nx-2, 0,    codeword, 4 );
		module( matrix, used, nx-1, 0,    codeword, 3 );
		module( matrix, used, nx-3, 1,    codeword, 2 );
		module( matrix, used, nx-2, 1,    codeword, 1 );
		module( matrix, used, nx-1, 1,    codeword, 0 );
	}


	void utah( Simple2dMatrix<bool> & matrix,
		   Simple2dMatrix<bool> & used,
		   int                    ix,
		   int                    iy,
		   uint8_t                codeword )
	{
		module( matrix, used, ix-2, iy-2, codeword, 7 );
		module( matrix, used, ix-1, iy-2, codeword, 6 );
		module( matrix, used, ix-2, iy-1, codeword, 5 );
		module( matrix, used, ix-1, iy-1, codeword, 4 );
		module( matrix, used, ix,   iy-1, codeword, 3 );
		module( matrix, used, ix-2, iy,   codeword, 2 );
		module( matrix, used, ix-1, iy,   codeword, 1 );
		module( matrix, used, ix,   iy,   codeword, 0 );
	}


	void ecc200_fill_matrix( Simple2dMatrix<bool>       & matrix,
				 const std::vector<uint8_t> & data_cw )
	{
		matrix.fill( false );

		Simple2dMatrix<bool> used = matrix;

		int i  = 0;
		int ix = 0;
		int iy = 4;
		int nx = matrix.nx();
		int ny = matrix.ny();
		
		do {
			if ( (iy == ny)   && (ix == 0)                ) corner1( matrix, used, data_cw[i++] );
			if ( (iy == ny-2) && (ix == 0) && (nx%4 != 0) ) corner2( matrix, used, data_cw[i++] );
			if ( (iy == ny-2) && (ix == 0) && (nx%8 == 4) ) corner3( matrix, used, data_cw[i++] );
			if ( (iy == ny+4) && (ix == 2) && (nx%8 == 0) ) corner4( matrix, used, data_cw[i++] );

			do {
				if ( (iy < ny) && (ix >= 0) && !used[iy][ix] ) utah( matrix, used, ix, iy, data_cw[i++] );
				ix += 2;
				iy -= 2;
			} while ( (iy >= 0) && (ix < nx) );
			ix += 3;
			iy += 1;

			do {
				if ( (iy >= 0) && (ix < nx) && !used[iy][ix] ) utah( matrix, used, ix, iy, data_cw[i++] );
				ix -= 2;
				iy += 2;
			} while ( (iy < ny) && (ix >= 0) );
			ix += 1;
			iy += 3;

		} while  ( (iy < ny) || (ix < nx) );

		if ( !used[ny-1][nx-1] )
		{
			matrix[ny-1][nx-1] = true;
			matrix[ny-2][nx-2] = true;
		}
	}


	void finder_pattern( Simple2dMatrix<bool> & encoded_data, int x0, int y0, int nx, int ny )
	{
		for ( int ix = 0; ix < nx; ix++ )
		{
			encoded_data[y0+ny-1][x0+ix] = true;
		}

		for ( int iy = 0; iy < ny; iy++ )
		{
			encoded_data[y0+iy][x0] = true;
		}

		for ( int ix = 0; ix < nx; ix += 2 )
		{
			encoded_data[y0][x0+ix]   = true;
			encoded_data[y0][x0+ix+1] = false;
		}

		for ( int iy = 0; iy < ny; iy += 2 )
		{
			encoded_data[y0+iy][x0+nx-1]   = false;
			encoded_data[y0+iy+1][x0+nx-1] = true;
		}

	}

}


namespace glbarcode
{

	/*
	 * Static DataMatrix barcode creation method
	 */
	Barcode* BarcodeDataMatrix::create( void )
	{
		return new BarcodeDataMatrix();
	}


	/*
	 * DataMatrix data validation, implements Barcode2dBase::validate()
	 */
	bool BarcodeDataMatrix::validate( std::string raw_data )
	{
		return true;
	}


	/*
	 * DataMatrix data encoding, implements Barcode2dBase::encode()
	 */
	bool BarcodeDataMatrix::encode( std::string cooked_data, Simple2dMatrix<bool> & encoded_data )
	{
		std::vector<uint8_t> data_cw;

		/*
		 * Encode data into codewords
		 */
		int n_raw_cw = ecc200_encode( cooked_data, data_cw );

		/*
		 * Determine parameters for "best size"
		 */
		const DMParameterEntry * p = ecc200_best_size_params( n_raw_cw );
		if ( p == NULL )
		{
			return false;
		}
		encoded_data.resize( p->n_xtotal, p->n_ytotal );
			

		/*
		 * Fill any extra data codewords
		 */
		ecc200_fill( data_cw, n_raw_cw, p->n_data_cw );


		/*
		 * Calculate Reed-Solomon correction codewords
		 */
		std::vector<uint8_t> rs_cw( p->n_rs_cw_block*(p->n_blocks_1 + p->n_blocks_2), 0 );

		for ( int i_block = 0; i_block < p->n_blocks_1; i_block++ )
		{
			ecc200_rs_block( data_cw,
					 rs_cw,
					 p->n_data_cw_block_1,
					 p->n_rs_cw_block,
					 p->a_select,
					 i_block,
					 p->n_blocks_1 + p->n_blocks_2 );
		}

		for ( int i_block = p->n_blocks_1; i_block < (p->n_blocks_1 + p->n_blocks_2); i_block++ )
		{
			ecc200_rs_block( data_cw,
					 rs_cw,
					 p->n_data_cw_block_2,
					 p->n_rs_cw_block,
					 p->a_select,
					 i_block,
					 p->n_blocks_1 + p->n_blocks_2 );
		}

		data_cw.insert( data_cw.end(), rs_cw.begin(), rs_cw.end() );


		/*
		 * Create raw data matrix
		 */
		Simple2dMatrix<bool> matrix( p->n_xregions * p->n_xregion,
					     p->n_yregions * p->n_yregion );
		ecc200_fill_matrix( matrix, data_cw );



		/*
		 * Construct by separating out regions and inserting finder patterns
		 */
		int xstride = p->n_xregion + 2;
		int ystride = p->n_yregion + 2;

		for ( int i_xregion = 0; i_xregion < p->n_xregions; i_xregion++ )
		{
			for ( int i_yregion = 0; i_yregion < p->n_yregions; i_yregion++ )
			{
				Simple2dMatrix<bool> region = matrix.sub_matrix( i_xregion*p->n_xregion, i_yregion*p->n_yregion,
										 p->n_xregion, p->n_yregion );

				encoded_data.insert( i_xregion*xstride + 1, i_yregion*ystride + 1, region );
				finder_pattern( encoded_data, i_xregion*xstride, i_yregion*ystride, xstride, ystride );
			}
		}


		return true;
	}


}
