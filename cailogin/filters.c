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

#define XSHIFT 5
#define YSHIFT 3

Digit * obscureDigit(Digit * digit) {
	digit = shiftX(digit);
	digit = shiftY(digit);
	lines(digit);
	colorRand(digit);
	colorInvert(digit);

	return digit;
}

Digit * shiftX(Digit * digit) {
	int shift = (rand() % (XSHIFT * 2 + 1)) - XSHIFT;
	if(shift == 0) return digit;
	Digit * newDigit = (Digit *) malloc(sizeof(Digit));

	// Set background: white
	int i, j;
	for(j = 0; j < CHARHEIGHT; j++)
		for(i = 0; i < CHARWIDTH; i++) {
			newDigit->bitmap[j][i].blue = 255;
			newDigit->bitmap[j][i].green = 255;
			newDigit->bitmap[j][i].red = 255;
		}

	for(j = 0; j < CHARHEIGHT; j++)
		if(shift < 0)
			for(i = 0; i < CHARWIDTH + shift; i++)
				newDigit->bitmap[j][i] = digit->bitmap[j][i + -1 * shift];
		else if(shift > 0)
			for(i = 0; i < CHARWIDTH - shift; i++)
				newDigit->bitmap[j][i + shift] = digit->bitmap[j][i];
	free(digit);
	return newDigit;
}

Digit * shiftY(Digit * digit) {
	int shift = (rand() % (YSHIFT * 2) + 1) - YSHIFT;
	if(shift == 0) return digit;
	Digit * newDigit = (Digit *) malloc(sizeof(Digit));

	// Set background: white
	int i, j;
	for(j = 0; j < CHARHEIGHT; j++)
		for(i = 0; i < CHARWIDTH; i++) {
			newDigit->bitmap[j][i].blue = 255;
			newDigit->bitmap[j][i].green = 255;
			newDigit->bitmap[j][i].red = 255;
		}

	for(j = 0; j < CHARWIDTH; j++)
		if(shift < 0)
			for(i = 0; i < CHARHEIGHT + shift; i++)
				newDigit->bitmap[i][j] = digit->bitmap[i][j + -1 * shift];
		else if(shift > 0)
			for(i = 0; i < CHARHEIGHT - shift; i++)
				newDigit->bitmap[i + shift][j] = digit->bitmap[i][j];
	free(digit);
	return newDigit;
}

int colorRand(Digit * digit) {
	int blue = rand() % 256;
	int green = rand() % 256;
	int red = rand() % 256;

	int i, j;
	for(j = 0; j < CHARHEIGHT; j++)
		for(i = 0; i < CHARWIDTH; i++)
			if(digit->bitmap[j][i].blue != 255 &&
			   digit->bitmap[j][i].green != 255 &&
			   digit->bitmap[j][i].red != 255) {
				digit->bitmap[j][i].blue = blue;
				digit->bitmap[j][i].green = green;
				digit->bitmap[j][i].red = red;
			}

	return 0;
}

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
