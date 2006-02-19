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

#include<stdio.h>
#include<stdlib.h>
#include"cailogin.h"
#include"vars.h"
#include"filters.h"

#ifdef SHIFTX_FILTER
int shiftX(Digit * digit) {
	int shift = (rand() % (XSHIFT * 2 + 1)) - XSHIFT;
	if(shift == 0) return 0;

	int i, j;
	for(j = 0; j < CHARHEIGHT; j++)
		if(shift < 0) {
			for(i = 0; i < CHARWIDTH + shift; i++)
				digit->bitmap[j][i] = digit->bitmap[j][i + -1 * shift];
			for(i = CHARWIDTH + shift; i < CHARWIDTH; i++) {
				digit->bitmap[j][i].blue = 255;
				digit->bitmap[j][i].green = 255;
				digit->bitmap[j][i].red = 255;
			}
		}
		else if(shift > 0) {
			for(i = CHARWIDTH - shift - 1; i >= 0; i--)
				digit->bitmap[j][i + shift] = digit->bitmap[j][i];
			for(i = 0; i < shift; i++) {
				digit->bitmap[j][i].blue = 255;
				digit->bitmap[j][i].green = 255;
				digit->bitmap[j][i].red = 255;
			}
		}
	return 0;
}
#endif

#ifdef SHIFTY_FILTER
int shiftY(Digit * digit) {
	int shift = (rand() % (YSHIFT * 2 + 1)) - YSHIFT;
	if(shift == 0) return 0;

	int i, j;
	for(j = 0; j < CHARWIDTH; j++)
		if(shift < 0) {
			for(i = 0; i < CHARHEIGHT + shift; i++)
				digit->bitmap[i][j] = digit->bitmap[i + -1 * shift][j];
			for(i = CHARHEIGHT + shift; i < CHARHEIGHT; i++) {
				digit->bitmap[i][j].blue = 255;
				digit->bitmap[i][j].green = 255;
				digit->bitmap[i][j].red = 255;
			}
		}
		else if(shift > 0) {
			for(i = CHARHEIGHT - shift - 1; i >= 0; i--)
				digit->bitmap[i + shift][j] = digit->bitmap[i][j];
			for(i = 0; i < shift; i++) {
				digit->bitmap[i][j].blue = 255;
				digit->bitmap[i][j].green = 255;
				digit->bitmap[i][j].red = 255;
			}
		}
}
#endif

#ifdef COLORFGRAND_FILTER
int colorFGRand(Digit * digit) {
	int blue = rand() % 256;
	int green = rand() % 256;
	int red = rand() % 256;

	int i, j;
	for(j = 0; j < CHARHEIGHT; j++)
		for(i = 0; i < CHARWIDTH; i++)
			if(digit->bitmap[j][i].blue == 0 &&
			   digit->bitmap[j][i].green == 0 &&
			   digit->bitmap[j][i].red == 0) {
				digit->bitmap[j][i].blue = blue;
				digit->bitmap[j][i].green = green;
				digit->bitmap[j][i].red = red;
			}

	return 0;
}
#endif

#ifdef COLORINVERT_FILTER
int colorInvert(Digit * digit) {
	short whether = rand() % 2;

	int vector;
	if(whether == 1) {
		int i, j;
		for(j = 0; j < CHARHEIGHT; j++)
			for(i = 0; i < CHARWIDTH; i++) {
				vector = digit->bitmap[j][i].blue - 127;
				digit->bitmap[j][i].blue = (127 - vector == -1) ? 0 : 127 - vector;
				vector = digit->bitmap[j][i].green - 127;
				digit->bitmap[j][i].green = (127 - vector == -1) ? 0 : 127 - vector;
				vector = digit->bitmap[j][i].red - 127;
				digit->bitmap[j][i].red = (127 - vector == -1) ? 0 : 127 - vector;
			}
	}

	return 0;
}
#endif

#ifdef LINES_FILTER
int lines(Digit * digit) {
	
	int a, i, j;
	a = rand() % CHARHEIGHT;
	for(i = 0; i < CHARWIDTH; i++) {
		digit->bitmap[a][i].blue = 0;
		digit->bitmap[a][i].green = 0;
		digit->bitmap[a][i].red = 0;
	}
	a = rand() % CHARHEIGHT;
	for(j = 0; j < CHARWIDTH; j++) {
		digit->bitmap[j][a].blue = 0;
		digit->bitmap[j][a].green = 0;
		digit->bitmap[j][a].red = 0;
	}

	return 0;
}
#endif

#ifdef NOISE_FILTER
int noise(Digit * digit) {
	int i, x, y;
	for(i = 0; i < NOISE_MAGNITUDE; i++) {
		x = 1 + rand() % CHARWIDTH;
		y = 1 + rand() % CHARHEIGHT;

		digit->bitmap[y][x].blue = 0;
		digit->bitmap[y][x].green = 0;
		digit->bitmap[y][x].red = 0;
	}

	return 0;
}
#endif

#ifdef DISTORTIONX_FILTER
int distortionX(Digit * digit) {
	int shift;

	int i, j;
	for(j = 0; j < CHARHEIGHT; j++) {
		if(rand() % 2 == 1)
			shift = XDISTORTION;
		else 
			shift = -1 * XDISTORTION;
		if(shift < 0) {
			for(i = 0; i < CHARWIDTH + shift; i++)
				digit->bitmap[j][i] = digit->bitmap[j][i + -1 * shift];
			for(i = CHARWIDTH + shift; i < CHARWIDTH; i++) {
				digit->bitmap[j][i].blue = 255;
				digit->bitmap[j][i].green = 255;
				digit->bitmap[j][i].red = 255;
			}
		}
		else {
			for(i = CHARWIDTH - shift - 1; i >= 0; i--)
				digit->bitmap[j][i + shift] = digit->bitmap[j][i];
			for(i = 0; i < shift; i++) {
				digit->bitmap[j][i].blue = 255;
				digit->bitmap[j][i].green = 255;
				digit->bitmap[j][i].red = 255;
			}
		}
	}
}
#endif

#ifdef DISTORTIONY_FILTER
int distortionY(Digit * digit) {
	int shift;

	int i, j;
	for(j = 0; j < CHARWIDTH; j++) {
		if(rand() % 2 == 1)
			shift = YDISTORTION;
		else 
			shift = -1 * YDISTORTION;
		if(shift < 0) {
			for(i = 0; i < CHARHEIGHT + shift; i++)
				digit->bitmap[i][j] = digit->bitmap[i + -1 * shift][j];
			for(i = CHARHEIGHT + shift; i < CHARHEIGHT; i++) {
				digit->bitmap[i][j].blue = 255;
				digit->bitmap[i][j].green = 255;
				digit->bitmap[i][j].red = 255;
			}
		}
		else {
			for(i = CHARHEIGHT - shift - 1; i >= 0; i--)
				digit->bitmap[i + shift][j] = digit->bitmap[i][j];
			for(i = 0; i < shift; i++) {
				digit->bitmap[i][j].blue = 255;
				digit->bitmap[i][j].green = 255;
				digit->bitmap[i][j].red = 255;
			}
		}
	}
}
#endif

#ifdef COLORBGRAND_FILTER
int colorBGRand(Digit * digit) {
	int blue = rand() % 256;
	int green = rand() % 256;
	int red = rand() % 256;

	int i, j;
	for(j = 0; j < CHARHEIGHT; j++)
		for(i = 0; i < CHARWIDTH; i++)
			if(digit->bitmap[j][i].blue == 255 &&
			   digit->bitmap[j][i].green == 255 &&
			   digit->bitmap[j][i].red == 255) {
				digit->bitmap[j][i].blue = blue;
				digit->bitmap[j][i].green = blue;
				digit->bitmap[j][i].red = blue;
			}

	return 0;
}
#endif

Digit * obscureDigit(Digit * digit) {
	int (*filters[NUMOF_FILTERS])(Digit *);
	int nof = 0; // Number of filters
	
#ifdef DISTORTIONX_FILTER
	filters[nof] = distortionX;
	nof++;
#endif
#ifdef DISTORTIONY_FILTER
	filters[nof] = distortionY;
	nof++;
#endif
#ifdef SHIFTX_FILTER
	filters[nof] = shiftX;
	nof++;
#endif
#ifdef SHIFTY_FILTER
	filters[nof] = shiftY;
	nof++;
#endif
#ifdef LINES_FILTER
	filters[nof] = lines;
	nof++;
#endif
#ifdef NOISE_FILTER
	filters[nof] = noise;
	nof++;
#endif
#ifdef COLORFGRAND_FILTER
	filters[nof] = colorFGRand;
	nof++;
#endif
#ifdef COLORBGRAND_FILTER
	filters[nof] = colorBGRand;
	nof++;
#endif
#ifdef COLORINVERT_FILTER
	filters[nof] = colorInvert;
	nof++;
#endif

	shuffle(filters);
	int i, filters_num = rand() % NUMOF_FILTERS;
	for(i = 0; i <= filters_num; i++)
		(*filters[i])(digit);

	return digit;
}

void shuffle(int (*filters[])(Digit *)) {
	int (*temp)(Digit *);

	int i, r;
	for(i = 0; i < SHUFFLE_REPETITIONS; i++) {
		r = rand() % (NUMOF_FILTERS - 1);
		temp = filters[NUMOF_FILTERS - 1];
		filters[NUMOF_FILTERS - 1] = filters[r];
		filters[r] = temp;
	}
}
