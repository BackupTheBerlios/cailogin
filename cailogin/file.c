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
#include<time.h>
#include"cailogin.h"
#include"vars.h"

static struct entry {
	int imageid;
	int code;
	int timevalue;
} DB[MAXDBENTRIES];

int cleanupDB(void) {
	FILE *fd;
	int entriesKept = 0;
	char filename[MAXDIRLENGTH];

	sprintf(filename, DBDIR "cailogin.db");
	if((fd = fopen(filename, "r")) == NULL) {
		fprintf(stderr, "ERROR: In cleanupDB(): Unable to open file %s for reading.\n", filename);
		exit(ERROR_ENCOUNTERED);
	}

	{
	char line[MAXLINELENGTH];
	int id, t, code;
	while(fgets(line, MAXLINELENGTH, fd) != NULL && entriesKept < MAXDBENTRIES) {
		if(sscanf(line, "%d %d %d\n", &id, &code, &t) != 3) {
			fprintf(stderr, "ERROR: In cleanupDB(): Parse error in %s.\n", filename);
			exit(ERROR_ENCOUNTERED);
		}
		if(time(NULL) - t <= TIMETHRESHOLD) {
			DB[entriesKept].imageid = id;
			DB[entriesKept].code = code;
			DB[entriesKept].timevalue = t;
			entriesKept++;
		}
	}
	}

	fclose(fd);

	sprintf(filename, DBDIR "cailogin.db");
	if((fd = fopen(filename, "w")) == NULL) {
		fprintf(stderr, "ERROR: In cleanupDB(): Unable to open file %s for writing.\n", filename);
		exit(ERROR_ENCOUNTERED);
	}

	int i;
	for(i = 0; i < entriesKept; i++)
		fprintf(fd,"%d %d %d\n", DB[i].imageid, DB[i].code, DB[i].timevalue);

	fclose(fd);

	return entriesKept;
}

void addDBEntry(int imageid, int code) {
	// Check whether entry with same id exists
	if(getDBEntry(imageid) != -1) {
		fprintf(stderr, "WARNING: Overwriting older entry %d!\n", imageid);
		delDBEntry(imageid);	
	}
	
	FILE *fd;
	char filename[MAXDIRLENGTH];
	
	sprintf(filename, DBDIR "cailogin.db");
	if((fd = fopen(filename, "a")) == NULL) {
		fprintf(stderr, "ERROR: In addDBEntry(): Unable to open file %s for writing.\n", filename);
		exit(ERROR_ENCOUNTERED);
	}
	fprintf(fd,"%d %d %d\n", imageid, code, time(NULL));

	fclose(fd);
}

	
int getDBEntry(int imageid) {
	FILE *fd;
	char filename[MAXDIRLENGTH];
	
	sprintf(filename, DBDIR "cailogin.db");
	if((fd = fopen(filename, "r")) == NULL) {
		fprintf(stderr, "ERROR: In getDBEntry(): Unable to open file %s for reading.\n", filename);
		exit(ERROR_ENCOUNTERED);
	}

	char line[MAXLINELENGTH];
	int id, t, code = -1;

	while(fgets(line, MAXLINELENGTH, fd) != NULL) {
		if(sscanf(line, "%d %d %d", &id, &code, &t) != 3) {
			fprintf(stderr, "ERROR: In getDBEntry(): Parse error in %s.\n", filename);
			exit(ERROR_ENCOUNTERED);
		}
		if(id == imageid)
			break;
		else code = -1;
	}
	fclose(fd);

	return code;
}

void delDBEntry(int imageid) {
	FILE *fd;
	char filename[MAXDIRLENGTH];
	int entriesKept = 0;

	sprintf(filename, DBDIR "cailogin.db");
	if((fd = fopen(filename, "r")) == NULL) {
		fprintf(stderr, "ERROR: In delDBEntry(): Unable to open file %s for reading.\n", filename);
		exit(ERROR_ENCOUNTERED);
	}

	{
	char line[MAXLINELENGTH];
	int id, t, code;
	while(fgets(line, MAXLINELENGTH, fd) != NULL) {
		if(sscanf(line, "%d %d %d\n", &id, &code, &t) != 3) {
			fprintf(stderr, "ERROR: In delDBEntry(): Parse error in %s.\n", filename);
			exit(ERROR_ENCOUNTERED);
		}
		if(id != imageid) {
			DB[entriesKept].imageid = id;
			DB[entriesKept].code = code;
			DB[entriesKept].timevalue = t;
			entriesKept++;
		}
	}
	}

	fclose(fd);

	sprintf(filename, DBDIR "cailogin.db");
	if((fd = fopen(filename, "w")) == NULL) {
		fprintf(stderr, "ERROR: In cleanupDB(): Unable to open file %s for writing.\n", filename);
		exit(ERROR_ENCOUNTERED);
	}

	int i;
	for(i = 0; i < entriesKept; i++)
		fprintf(fd,"%d %d %d\n", DB[i].imageid, DB[i].code, DB[i].timevalue);

	fclose(fd);
}

void printDB(void) {
	FILE *fd;
	char filename[MAXDIRLENGTH];
	char line[MAXLINELENGTH];

	sprintf(filename, DBDIR "cailogin.db");
	if((fd = fopen(filename, "r")) == NULL) {
		fprintf(stderr, "ERROR: In delDBEntry(): Unable to open file %s for reading.\n", filename);
		exit(ERROR_ENCOUNTERED);
	}

	while(fgets(line, MAXLINELENGTH, fd) != NULL)
		printf("%s", line);

	fclose(fd);
}

void dumpDB(void) {
	FILE *fd;
	char filename[MAXDIRLENGTH];

	sprintf(filename, DBDIR "cailogin.db");
	if((fd = fopen(filename, "w")) == NULL) {
		fprintf(stderr, "ERROR: In delDBEntry(): Unable to open file %s for reading.\n", filename);
		exit(ERROR_ENCOUNTERED);
	}

	fclose(fd);
}
