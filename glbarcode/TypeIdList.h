/*  TypeIdList.h
 *
 *  Copyright (C) 2013-2014  Jim Evins <evins@snaught.com>
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

#ifndef glbarcode_TypeIdList_h
#define glbarcode_TypeIdList_h

#include "Barcode.h"

#include <string>
#include <list>


namespace glbarcode
{
	/**
	 * @class TypeIdList TypeIdList.h glbarcode/TypeIdList.h
	 *
	 * List of barcode type ID strings.
	 */
	class TypeIdList : public std::list<std::string>
	{
	};

}


#endif // glbarcode_TypeIdList_h
