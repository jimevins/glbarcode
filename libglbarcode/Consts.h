/*  Constants.h
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

#ifndef glbarcode_Constants_h
#define glbarcode_Constants_h


namespace glbarcode
{

	namespace consts
	{

		const double PTS_PER_INCH = 72.0;
		const double PTS_PER_MM   =  2.83464566929;
		const double PTS_PER_CM   = 10*PTS_PER_MM;

		const double INK_BLEED   = ( 0.00325 * PTS_PER_INCH );
	}

}


#endif // glbarcode_Constants_h
