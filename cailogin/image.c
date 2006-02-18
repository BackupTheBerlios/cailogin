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

Image * mergeDigits(Digit *digit[]) {
	Image *image = (Image *) malloc(sizeof(Image));

	// Fill-in bitmap section
	int i, j, c;
	for(i = 0; i < CHARHEIGHT; i++)
		for(c = 0; c < DIGITSOUT; c++)
			for(j = 0; j < CHARWIDTH; j++)
				image->bitmap[i][c * CHARWIDTH + j] = digit[c]->bitmap[i][j];
	
	for(i = 0; i < DIGITSOUT; i++)
		free(digit[i]);
	
	// Fill-in header section
	image->header = (Header *) malloc(sizeof(Header));
	image->header->identifier[0] = 'B'; 
	image->header->identifier[1] = 'M'; 
	image->header->file_size = sizeof(Digit) * DIGITSOUT + sizeof(Header);
	image->header->reserved = 0;
	image->header->bitmap_data_offset = sizeof(Header);
	image->header->bitmap_header_size = 0x28;
	image->header->width = CHARWIDTH * DIGITSOUT;
	image->header->height = CHARHEIGHT;
	image->header->planes = 1;
	image->header->bits_per_pixel = 24;
	image->header->compression = 0;
	image->header->bitmap_data_size = sizeof(Digit) * DIGITSOUT;
	image->header->hresolution = 0x0B12;
	image->header->vresolution = 0x0B12;
	image->header->colors = 0;
	image->header->important_colors = 0;

	return image;
}

void writeImage(Image * image) {
	int size;
	
	// Output header first
	size = sizeof(Header);
	if(fwrite(image->header, 1, size, stdout) != size)
		WARNING("In writeImage(): Writen fewer bytes to output!")
	// Output pixels one by one
	size = sizeof(Digit) * DIGITSOUT;
	if(fwrite(image->bitmap, 1, size, stdout) != size)
		WARNING("In writeImage(): Writen fewer bytes to output!")
}

Digit * readDigit(unsigned short digit) {
	if(digit > 9) 
		ERROREXIT("In readDigit(): digit must be in the range 0 to 9")

	FILE *fp;
	char filename[MAXDIRLENGTH] = "";
	int offset;

	sprintf(filename, BITMAPSDIR "/%d.bmp", digit);
	if((fp = fopen(filename, "r")) == NULL) {
		fprintf(stderr, "ERROR: In readDigit(): Unable to open file %s.\n", filename);
		exit(ERROR_ENCOUNTERED);
	}

	// We'll locate the start of the bitmap section
	//  First find the offset, pointing to the start of the bitmap section
	if(fseek(fp, OFFSET_OF_BITMAP_OFFSET, SEEK_SET) != 0) { 
		fprintf(stderr, "ERROR: In readDigit(): Unable to seek into file %s.\n", filename);
		exit(ERROR_ENCOUNTERED);
	}
	//  Now jump to the start of the bitmap section
	fread(&offset, sizeof(unsigned int), 1, fp);
	if(fseek(fp, offset, SEEK_SET) != 0) {
		fprintf(stderr, "ERROR: In readDigit(): Unable to seek into file %s.\n", filename);
		exit(ERROR_ENCOUNTERED);
	}
	// Fill-in digit with data from the bitmap section
	Digit *c = (Digit *) malloc(sizeof(Digit));
	if(fread(c->bitmap, 1, CHARWIDTH * CHARHEIGHT * sizeof(Pixel), fp) != CHARWIDTH * CHARHEIGHT * sizeof(Pixel)) {
		fprintf(stderr, "ERROR: In readDigit(): Insufficient file size: %s\n", filename);
		exit(ERROR_ENCOUNTERED);
	}

	fclose(fp);

	return c;
}

void printDigit(Digit * digit) {
	int i, j;
	printf("\n____");
	for(i = 0; i < CHARWIDTH; i++)
		printf("___");
	for(i = 0; i < CHARHEIGHT; i++) {
		printf("\n%2d|",i+1);
		for(j = 0; j < CHARWIDTH; j++)
			printf((digit->bitmap[i][j].blue < 255 ||
				digit->bitmap[i][j].green < 255 ||
				digit->bitmap[i][j].red < 255) ? "###" : "   ");
		printf("|");
	}
	printf("\n----");
	for(i = 0; i < CHARWIDTH; i++)
		printf("---");
	printf("\n");
}

void printImage(Image * image) {
	int i, j;
	printf("\n___");
	for(i = 0; i < DIGITSOUT * CHARWIDTH; i++)
		printf("_");
	for(i = 0; i < CHARHEIGHT; i++) {
		printf("\n%2d|",i+1);
		for(j = 0; j < DIGITSOUT * CHARWIDTH; j++)
			printf((image->bitmap[i][j].blue < 255 ||
				image->bitmap[i][j].green < 255 ||
				image->bitmap[i][j].red < 255) ? "#" : " ");
		printf("|");
	}
	printf("\n---");
	for(i = 0; i < DIGITSOUT * CHARWIDTH; i++)
		printf("-");
	printf("\n");
}
