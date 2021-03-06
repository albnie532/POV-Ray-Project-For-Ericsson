/*******************************************************************************
 * stringutilities.cpp
 *
 * This module implements string utility functions.
 *
 * ---------------------------------------------------------------------------
 * Persistence of Vision Ray Tracer ('POV-Ray') version 3.7.
 * Copyright 1991-2013 Persistence of Vision Raytracer Pty. Ltd.
 *
 * POV-Ray is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * POV-Ray is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * ---------------------------------------------------------------------------
 * POV-Ray is based on the popular DKB raytracer version 2.12.
 * DKBTrace was originally written by David K. Buck.
 * DKBTrace Ver 2.0-2.12 were written by David K. Buck & Aaron A. Collins.
 * ---------------------------------------------------------------------------
 * $File: //depot/public/povray/3.x/source/base/stringutilities.cpp $
 * $Revision: #1 $
 * $Change: 6069 $
 * $DateTime: 2013/11/06 11:59:40 $
 * $Author: chrisc $
 *******************************************************************************/

#include <cctype>
#include <cstdarg>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>

// configbase.h must always be the first POV file included within base *.cpp files
#include "configbase.h"

#include "stringutilities.h"

// this must be the last file included
#include "base/povdebug.h"

namespace pov_base
{

/*****************************************************************************
*
* FUNCTION
*
*   pov_stricmp
*
* INPUT
*   
* OUTPUT
*   
* RETURNS
*   
* AUTHOR
*
*   POV-Ray Team
*   
* DESCRIPTION
*
*   Since the stricmp function isn't available on all systems, we've
*   provided a simplified version of it here.
*
* CHANGES
*
*   -
*
******************************************************************************/

int pov_stricmp(const char *s1, const char *s2)
{
	char c1, c2;

	while((*s1 != 0) && (*s2 != 0))
	{
		c1 = *s1++;
		c2 = *s2++;

		c1 = (char)toupper(c1);
		c2 = (char)toupper(c2);

		if(c1 < c2)
			return -1;
		if(c1 > c2)
			return 1;
	}

	if(*s1 == 0)
	{
		if(*s2 == 0)
			return 0;
		else
			return -1;
	}
	else
		return 1;
}

/*****************************************************************************
*
* FUNCTION
*
*   pov_tsprintf
*
* INPUT
*   
* OUTPUT
*   
* RETURNS
*   
* AUTHOR
*
*   POV-Ray Team
*   
* DESCRIPTION
*
*   Since the stricmp function isn't available on all systems, we've
*   provided a simplified version of it here.
*
* CHANGES
*
*   -
*
******************************************************************************/

const char *pov_tsprintf(const char *format,...)
{
	va_list marker;

	static char pov_tsprintf_buffer[1024];

	va_start(marker, format);
	vsnprintf(pov_tsprintf_buffer, 1023, format, marker);
	va_end(marker);

	return pov_tsprintf_buffer;
}

}
