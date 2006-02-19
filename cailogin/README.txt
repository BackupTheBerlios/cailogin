OVERVIEW

CAILogin (Counter-AI Login) is a tiny image-based user verification program 
to accompany web-page logins. It's especially appropriate for embedded systems,
since it is written in standard C and can be very well used from within CGI shell 
scripts. Though small in size, CAILogin is very robust and secure.

HOW IT WORKS

Operation takes place in the steps.

First your CGI script have to ask from CAILogin to prepare an image, which will be later on requested. The image is distinguished from other from the supplied image ID. The image ID can be a random number, but it should preferably be a counter, to avoid collisions of image ID among different generated images.

	cailogin --request 123

At any time the script can get the image by issuing:

	 cailogin --image  123

The output from this command is actually the binary image itself. This output has to be forwarded to the web browser by the CGI script, through an <img> tag (check accompanying login.cgi script). Note that the actual code displayed on the generated image is only know to CAILogin, and not to the CGI script or to any other party.

Finally, user's response will be validated against CAILogin's records, with this command:

	cailogin --check 123 87654321

Where '87654321' is the user supplied access code. The entry on the database, will be then removed automatically. 

Other than this way, an image ID will be removed from the DB, after 10 minutes time of not been checked. You should make sure that no two images have the same ID during this interval. A good practice to enforce this, is to use a counter for the image ID. The counter will inevitably loop after some time, but you have to make use that this time is more that 10 minutes. If during that period a new entry request arrived with the same image ID, the older one will be overwritten by the newer.

CAILogin stores every mapping of image ID to generated code number on a text 
file (cailogin.db), which (for security reasons) should not be readable or writable by the web server or the CGI script. When CAILogin is installed system-wide, this is guaranteed, by setting the ownership of cailogin.db to root and permissions to 0600. You can of course install CAILogin locally on your user account. But then you have to make sure that the aforementioned requirement is met.

For security reasons, CAILogin's DB file should at no means be installed under cgi-bin or htdocs or any other directory, accessible from the Internet.

As you might have guessed, CAILogin's DB file is comprised from entries with three fields each:
|Image ID|Corresponding Code Number|Time that this entry has been introduced|

Currently the length of the generated access code is fixed, seven decimal (0-9) digits  long. On every digit, one or more filters (for obscuration) are applied. 

Currently supported filters are:
	* Vertical shift
	* Horizontal shift
	* Value invert
	* Random FG color
	* Random BG color
	* Random lines
	* Random noise
	* Distortion
	* TODO: Blurring
	* TODO: Scaling
	* TODO: Rotation

You can affect which filters are used, at compile time. To do this edit filters.h.

SECURITY

CAILogin is very secure, as long as the CAILogin DB is only readable (and
writable) by CAILogin alone. CAILogin is installed as root:root, so
normally this should do the trick. 

In case you are concerned about how random are the generated image codes, 
CAILogin uses /dev/urandom which is an excellent true random number generator.

BITMAPS

CAILogin comes with some default bitmaps, one for every decimal number. 
However, you can very well substitute them with bitmaps of you own choice, 
as long as they meet the following requirements:

BMP is the only currently supported bitmap format. The dimensions must be 24x24
plus 24bit color. Finally, for the time being, you can only have one bitmap
per number (and only numbers, not letters).

SYNTAX

   -r --request <ImageID>               Request a user verification
                                        image with ID <ImageID>

   -c --check <ImageID> <AccessCode>    Check validity of previously
                                        requested image of ID <ImageID>,
                                        against user-supplied <AccessCode>

   -i --image <ImageID>                 Get generated image with random
                                        code for <ImageID>

   -d --delete <ImageID>                Remove entry with <ImageID> from
                                        database

   -u --dump                            Initialize database

   -p --print                           Print database

   -v --version                         Print version of CAILogin

   -h --help                            This help message

EXAMPLE
Execute:
	make -f Makefile.example
and then copy example/ dir in you cgi-bin and experiment with.

LICENCE

CAILogin is distributed under GPLv2 or any newer (of your choice).
