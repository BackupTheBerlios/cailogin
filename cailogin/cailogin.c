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
#include<string.h>
#include"cailogin.h"
#include"vars.h"

#define HELPMSG "\
CAILogin Web-Login Image Verification Program\n\
\n\
   -r --request <ImageID>		Request a user verification\n\
					image with ID <ImageID>\n\
\n\
   -c --check <ImageID> <AccessCode>	Check validity of previously\n\
					requested image of ID <ImageID>,\n\
					against user-supplied <AccessCode>\n\
\n\
   -i --image <ImageID>			Get generated image with random\n\
					code for <ImageID>\n\
\n\
   -d --delete <ImageID>		Remove entry with <ImageID> from\n\
					database\n\
\n\
   -u --dump				Initialize database\n\
\n\
   -p --print				Print database\n\
\n\
   -v --version				Print version of CAILogin\n\
\n\
   -h --help				This help message\n\
\n\
\n\
CAILogin, Copyright (C) 2006 Stergiakis Alexandros\n\
CAILogin comes with ABSOLUTELY NO WARRANTY. This is free\n\
software, and you are welcome to redistribute it under certain\n\
conditions; check accompaning COPYING file for details.\n\
"

static void mysrand(void);
static int power10(int);

int main(int argc, int *argv[]) {
	int imageid, code;

		if(argc < 2) {printf("%s", HELPMSG); exit(INVALID_ARGUMENTS);}
		
		if(strcmp((char*) argv[1],"-r") == 0 || 
		   strcmp((char*) argv[1],"--request") == 0) {

		  if(argc != 3)
		   {printf("Invalid number of arguments. Try %s -h\n", argv[0]); exit(INVALID_ARGUMENTS);}

		  if(!(imageid = atol((char *) argv[2])))
		   {printf("Image ID must be a decimal number. Try %s -h\n", *argv[0]); exit(INVALID_ARGUMENTS);}
			
			cleanupDB();
			mysrand();
			addDBEntry(imageid, 1 + (rand() % 9999999));
			printf("Database updated.\n\n");
			return 0;

		} else if(strcmp((char*) argv[1],"-c") == 0 || 
			  strcmp((char*) argv[1],"--check") == 0) {

		  if(argc != 4)
		   {printf("Invalid number of arguments. Try %s -h\n", argv[0]); exit(INVALID_ARGUMENTS);}

		  if(!(imageid = atol((char *) argv[2])))
		   {printf("Image ID must be a decimal number. Try %s -h\n", *argv[0]); exit(INVALID_ARGUMENTS);}
			
		  if(!(code = atol((char *) argv[3])))
		   {printf("Access code must be a decimal number. Try %s -h\n", *argv[0]); exit(INVALID_ARGUMENTS);}
			
			cleanupDB();
			if(code == getDBEntry(imageid)) {
				printf("Match succedded. Removing entry..\n\n");
				delDBEntry(imageid);
			} else {
				printf("Match failure.\n\n");
				return(ACCESS_CODE_MISMATCH);
			}
			return 0;

		} else if(strcmp((char*) argv[1],"-i") == 0 || 
		   strcmp((char*) argv[1],"--image") == 0) {

		  if(argc != 3)
		   {printf("Invalid number of arguments. Try %s -h\n", argv[0]); exit(INVALID_ARGUMENTS);}

		  if(!(imageid = atol((char *) argv[2])))
		   {printf("Image ID must be a decimal number. Try %s -h\n", *argv[0]); exit(INVALID_ARGUMENTS);}

			cleanupDB();
			if(!(imageid = atol((char *) argv[2])))
				exit(ERROR_ENCOUNTERED);
			if((code = getDBEntry(imageid)) == -1)
				exit(ERROR_ENCOUNTERED);

			Digit *digit[DIGITSOUT];
		
			mysrand();
			int i, pow, rem;
			for(i = 0; i < DIGITSOUT; i++) {
				pow = power10(DIGITSOUT-1-i);
				rem = code / pow;
				digit[i] = readDigit(rem);
				digit[i] = obscureDigit(digit[i]);
				code -= pow * rem;
			}
	
			Image *image = mergeDigits(digit);
			printf(IMAGE_BMP_CONTENTTYPE);
			writeImage(image);
			return 0;

		} else if(strcmp((char*) argv[1],"-v") == 0 || 
		   strcmp((char*) argv[1],"--version") == 0) {

			printf("\nCAILogin Version %s.\n\n", VERSION);
			return 0;

		} else if(strcmp((char*) argv[1],"-d") == 0 || 
		   strcmp((char*) argv[1],"--delete") == 0) {

		  if(argc != 3)
		   {printf("Invalid number of arguments. Try %s -h\n", argv[0]); exit(INVALID_ARGUMENTS);}

		  if(!(imageid = atol((char *) argv[2])))
		   {printf("Image ID must be a decimal number. Try %s -h\n", *argv[0]); exit(INVALID_ARGUMENTS);}
		  
			cleanupDB();
			delDBEntry(imageid);
			printf("Entry successfuly removed.\n\n");
			return 0;

		} else if(strcmp((char*) argv[1],"-p") == 0 || 
		   strcmp((char*) argv[1],"--print") == 0) {

			cleanupDB();
			printDB();
			return 0;

		} else if(strcmp((char*) argv[1],"-u") == 0 || 
		   strcmp((char*) argv[1],"--dump") == 0) {

			cleanupDB();
			dumpDB();
			printf("Dadabase entries successfuly dumped.\n\n");
			return 0;

		} else 	printf("%s", HELPMSG);

	return 0;
}

static void mysrand(void) {
	FILE *fd;

	if((fd = fopen("/dev/urandom", "r")) == NULL) {
		fprintf(stderr, "ERROR: In mysrand(): Unable to open file /dev/urandom for reading.\n");
		exit(ERROR_ENCOUNTERED);
	}

	int seed;
	fread(&seed, sizeof(unsigned int), 1, fd);
	srand(seed);

	fclose(fd);
}

static int power10(int a) {
	int result = 1;
	
	int i;
	for(i = 0; i < a; i++)
		result *= 10;

	return result;
}
