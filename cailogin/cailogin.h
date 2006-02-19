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

#define ERROREXIT(str) { fprintf(stderr, "ERROR: " str); exit(1); }
#define WARNING(str) fprintf(stderr, "WARNING: " str);
#define CHARWIDTH 24
#define CHARHEIGHT 24
#define MAXDIGITSIN 32
#define DIGITSOUT 7
#define MAXLINELENGTH 100
#define MAXLINESNUM 300
#define CLEANUP_TIME 60
#define OFFSET_OF_BITMAP_OFFSET 10
#define IMAGE_BMP_CONTENTTYPE "Content-type: image/bmp\r\n\r\n"
#define MAXDIRLENGTH 100
#define ACCESS_CODE_MISMATCH 3
#define INVALID_ARGUMENTS 2
#define ERROR_ENCOUNTERED 1

typedef struct __attribute__ ((packed)) BMPPixel {
	unsigned char blue;
	unsigned char green;
	unsigned char red;
} Pixel;

typedef struct __attribute__ ((packed)) BMPDigit {
	Pixel bitmap[CHARHEIGHT][CHARWIDTH];
} Digit;

typedef struct __attribute__ ((packed)) BMPHeader {
	char identifier[2]; 
	unsigned int file_size;
	unsigned int reserved;
	unsigned int bitmap_data_offset;
	unsigned int bitmap_header_size;
	unsigned int width;
	unsigned int height;
	unsigned short planes;
	unsigned short bits_per_pixel;
	unsigned int compression;
	unsigned int bitmap_data_size;
	unsigned int hresolution;
	unsigned int vresolution;
	unsigned int colors;
	unsigned int important_colors;
} Header;

typedef struct __attribute__ ((packed)) BMPImage {
	Header *header;
	Pixel bitmap[CHARHEIGHT][CHARWIDTH * DIGITSOUT];
} Image;

Image * mergeDigits(Digit *digit[]);

void writeImage(Image *);

Digit * readDigit(unsigned short);

void printDigit(Digit *);

void printImage(Image *);
