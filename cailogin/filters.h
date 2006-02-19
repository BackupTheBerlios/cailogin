/*
    Copyright (C) 2006  Stergiakis Alexandros

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
    02111-1307  USA
*/

// Enabled filters
#define SHIFTX_FILTER
#define SHIFTY_FILTER
#define COLORFGRAND_FILTER
#define COLORBGRAND_FILTER
#define COLORINVERT_FILTER
#define LINES_FILTER
#define NOISE_FILTER
#define DISTORTIONX_FILTER
#define DISTORTIONY_FILTER

// If you have deactivated any filter, update NUMOF_FILTERS accordingly
#define NUMOF_FILTERS 9
#define SHUFFLE_REPETITIONS 30

// Filter properties
#define XSHIFT 5
#define YSHIFT 3
#define XDISTORTION 1
#define YDISTORTION 1
#define NOISE_MAGNITUDE 25

#ifdef SHIFTX_FILTER
int shiftX(Digit *);
#endif

#ifdef SHIFTY_FILTER
int shiftY(Digit *);
#endif

#ifdef COLORFGRAND_FILTER
int colorFGRand(Digit *);
#endif

#ifdef COLOBFGRAND_FILTER
int colorBGRand(Digit *);
#endif

#ifdef COLORINVERT_FILTER
int colorInvert(Digit *);
#endif

#ifdef LINES_FILTER
int lines(Digit *);
#endif

#ifdef NOISE_FILTER
int noise(Digit *);
#endif

#ifdef DISTORTIONX_FILTER
int distortionX(Digit *);
#endif

#ifdef DISTORTIONY_FILTER
int distortionY(Digit *);
#endif

Digit * obscureDigit(Digit *);

void shuffle(int (*[])(Digit *));
