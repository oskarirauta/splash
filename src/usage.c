
/**
 * Clue Media Experience
 * usage.c - Splash configuration and workflow implementation
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <libgen.h>

#include "usage.h"
#include "constants.h"
#include "utils.h"

void usageTitle()
{

	printf("splash v%s\r\n", VERSION);
	printf("forked from: https://github.com/stefandmn/Splash\r\n");
	printf("author: Oskari Rauta\r\n\n");
}

void usageCommon(char *fn) {

	usageTitle();
	printf("Usage:\r\n");
	printf("\t%s [args]\r\n", fn);
}

void usageEmpty(char *fn) {

	usageTitle();
	printf("Usage:\r\n");
	printf("\t%s [args]\r\n", fn);
	printf("\nUse --help or --help all to get help on usage.\r\n");
	printf("\n");
}

void usageUsage(char *fn) {

	usageTitle();
	printf("Usage:\r\n");
	printf("\t%s --help [cagegory1] [category2] [..]\r\n", fn);

	printf("\n* Help *\r\n");

	printf("\nTo display help on usage, prepare command with option --help following a single category or list of categories\r\n");
	printf("to query help for, or you can also use category all. Categories are written in lower case letters and separated\r\n");
	printf("spaces.\r\n");

	printf("Available categories are:\r\n");
	printf(" - images\r\n");
	printf(" - messages\r\n");
	printf(" - shapes\r\n");
	printf(" - display\r\n");
	printf(" - coordinates\r\n");
	printf(" - system\r\n");
	printf(" - all, which selects all above categories usages to outputted to screen\r\n");

	printf("\nExamples:\r\n");
	printf("  %s --help system\r\n", fn);
	printf("  %s --help images system\r\n", fn);
	printf("  %s --help all\r\n", fn);
	printf("\n");

}

void usageMessages(char *fn) {

	printf("\n* Messages *\r\n");

	printf("\nTo display text messages on the screen you have to prepare a command with the following options:\r\n");
	printf(" - fontfile - refers a TTF file which should be the font name to display the required text message.\r\n");
	printf("   In case the font file is already deployed in shared data path:\r\n");
	printf("   %s/fonts - you can refer only the filename without path or extension.\r\n", RESPATH);
	printf("   By default three font files are includes: bold.ttf, regular.ttf and teletext.ttf\r\n");
	printf(" - fontsize - indicates the height of the text letters\r\n");
	printf(" - fontcolor - sets the message text's color. Splash accept a HEX color format, with or without hash sign.\r\n");
	printf(" - fontspacing - sets the space between letters, default value: 3 pixels.\r\n");

	printf("\nExamples:\r\n");
	printf("  %s --message=\"Sample message\" -x100 -y200\r\n", fn);
	printf("  %s --message=\"Sample message\" -x100 -y200 -properties=\"fontcolor=#ff0000,fontsize=30,fontfile=teletext\"\r\n", fn);
	printf("  %s --message=\"Sample message\" -x100 -y200 -properties=\"fontcolor=ff00ff,fontfile=/root/resources/arial.ttf\"\r\n", fn);
}

void usageImages(char *fn) {

	printf("\n* Images *\r\n");

	printf("\nTo display images on the screen you have to build a command with the options described below:\r\n");

#if (defined WITH_JPG || defined WITH_BMP)
	printf(" - image - path to image, unless image is in PNG format and it is deployed in shared data path\r\n");
	printf("   %s/images ; in that case, just use filename without path or extension.\r\n", RESPATH);
#else
	printf(" - image - path to image, unless it is deployed in shared data path %s/images\r\n", RESPATH);
	printf("   in that case, just use filename wotuhout path or extension.\r\n");
#endif

	printf(" - rotate - rotate specified image with 90, 180 or 270 degrees - corresponding to input values: 1, 2, 3\r\n");
	printf(" - enlarge - displays the image to the whole area of the screen. It is a boolean value, accepts values, likes, y, yes, true\r\n");
	printf(" - stretch - displays the image to the whole area of the screen by in stretching mode.\r\n\tIt is also a boolean value, the possible value are described above.\r\n");

	printf("\nSupported formats: PNG");

#if (defined WITH_JPG && defined WITH_BMP)
	printf(", JPG and BMP\r\n");
#else
#ifdef WITH_JPG
	printf(" and JPG\r\n");
#elif (defined WITH_BMP)
	printf(" and BMP\r\n");
#else
	printf("\r\n");
#endif
#endif

	printf("\nExamples:\r\n");
	printf("  %s --image=splash\r\n", fn);
	printf("  %s --image=%s/images/splash.jpg -x100 -y100\r\n", fn, RESPATH);
	printf("  %s -i %s/images/splash.jpg --xpoint=100 -ypoint= --properties=\"rotate=1\"\r\n", fn, RESPATH);
}

void usageShapes(char *fn) {

	printf("\n* Shapes *\r\n");

	printf("\nTo display graphical shapes, you have to prepare a command to specify what shape is needed and\r\n");
	printf("additional options (dedicated per type of shape) for specific formatting.\r\n");

	printf("\nShape types:\r\n");
	printf(" - line - draw a simple line from point (x,y) to point (x2,y2)\r\n");
	printf(" - hline - draw a horizontal line (having the same X for both points - not needed to be specified for the second point)\r\n");
	printf(" - vline - draw a vertical line (having the same Y for both points - not needed to be specified for the second point)\r\n");
	printf(" - circle - draw a circle giving the center coordinates - single (x,y) point, and the radius\r\n");
	printf(" - rectangle - draw a rectangle providing a initial position and width and height dimensions.\r\n");
	printf(" - progressbar - draw a progress bar control as a derived shape from rectangle.\r\n");

	printf("\nAll graphical formatting options of line, hline and vline shapes are:\r\n\n");
	printf(" - linecolor - specifies the color of the line in HEX format\r\n");
	printf(" - x2point - horizontal target coordinate\r\n");
	printf(" - y2point - vertical target coordinate\r\n");

	printf("\nExamples:\r\n");
	printf("  %s --shape=line -x100 -y100 --properties=\"x2point=200,y2point=200,linecolor=#00FF00\"\r\n", fn);
	printf("  %s --shape=hline -x100 -y100 --properties=\"x2point=200,linecolor=#00FF00\"\r\n", fn);

	printf("\nThe graphical formatting options for rectangle shapes are:\r\n");
	printf(" - linecolor - specifies the color of the line in HEX format\r\n");
	printf(" - fillcolor - specifies the color of the rectangle area in HEX format\r\n");
	printf(" - width - describes the width of the rectangle\r\n");
	printf(" - height - describes the height of the rectangle\r\n");
	printf(" - linewidth - specifies the thickness of the rectangle border\r\n");

	printf("\nExamples:\r\n");
	printf("  %splas --shape=rectangle -x100 -y100 --properies=\"width=200,height=100,linecolor=#00FF00\"\r\n", fn);
	printf("  %splas --shape=rectangle -x500 -y500 --properies=\"width=200,height=200,linecolor=#000FF0,linewidth=5,fillcolor=#FF0000\"\r\n", fn);

	printf("\nThe graphical formatting options for circle shapes are:\r\n");
	printf(" - linecolor - specifies the color of the line in HEX format\r\n");
	printf(" - fillcolor - specifies the color of the circle area in HEX format\r\n");
	printf(" - radius - describes the radius of the circle\r\n");
	printf(" - linewidth - specifies the thickness of the circle border\r\n");

	printf("\nExamples:\r\n");
	printf("  %s --shape=circle -x500 -y500 --properies=\"radius=200,linecolor=#00FF00\"\r\n", fn);
	printf("  %s --shape=circle -x500 -y500 --properies=\"radius=200,linecolor=#00FF00,linewidth=5\"\r\n", fn);

	printf("\nThe graphical formatting options for progressbars are:\r\n");
	printf(" - percent - shows how much of the total area is occupied by barcolor color.\r\n");
	printf(" - linecolor - specifies the color of the line in HEX format\r\n");
	printf(" - barcolor - specifies the color of the rectangle area in HEX format which is already filled in, and described\r\n");
	printf("   the percent part of internal rectangle area described by the progressbar control. If this color is not specified \r\n");
	printf("   than it will be considered white (#FFFFFF color to fill it in when the percent value is bigger than 0)\r\n");
	printf(" - backgroundcolor - describe the color that suppose to be in the inner part of the progressbar control when \r\n");
	printf("   the fill in percentage is 0 or less than 0 (when is less the color area is figure it out in the right side of the\r\n");
	printf("   control). If no color is specified than it will default to black color (#000000)\r\n");
	printf(" - width - describes the width of the progressbar control\r\n");
	printf(" - height - describes the height of the progressbar control\r\n");
	printf(" - linewidth - specifies the thickness of the progressbar border\r\n");

	printf("\nExamples:\r\n");
	printf("  %s --shape=progressbar -x500 -y500 --properties=\"width=400,height=50,linecolor=#0000FF,linewidth=4,barcolor=#F0F0F0\"\r\n", fn);
	printf("  %s --shape=progressbar --ypoint=-34 --properties=\"width=500,height=50,linewidth=4,percent=-30\"\r\n", fn);
}

void usageDisplay(char *fn) {

	printf("\n* Display options *\r\n");
	printf("\nDisplay options make the application 'to appear' dynamic and to build simple execution workflows to create\r\n");
	printf("graphical screens from shell commands. Below are described the execution options that, together with specific\r\n");
	printf("object options make the execution process flawless. In addition, the application is designed to keep in memory\r\n");
	printf("each executed command and if two consecutive commands are executed specifying the same object type the\r\n");
	printf("previous one will be wiped from the screen (it is considered that the position and the graphical format properties\r\n");
	printf("have been changed and the object will be moved or overdrawn with other coordinates). To prevent such behaviour\r\n");
	printf("various display options from the list below can be combined to obtain a different experience.\r\n");

	printf("\nAvailable options are:\r\n");
	printf(" - reset - resets/clears the entire screen area (delete all drawn objects) and make the screen black\r\n");
	printf(" - console - creates a graphical terminal over frame buffer (a canvas area able to render graphical objects). In \r\n");
	printf("   case this option is not specified the command will use the existent graphical console.\r\n");
	printf(" - keep - use this option to keep the object on the screen even if the command is repeated for the same object\r\n");
	printf("   type with or without the same graphical coordinates and properties. This options allow the internal workflow to\r\n");
	printf("   be execute but will avoid wiping of previous object type. The command will still go in memory to know\r\n");
	printf("   previous execution step but will not be used for wiping.\r\n");
	printf(" - wipe - wipes whatever object type was drawn before (not necessarily to be drawn previously). The color\r\n");
	printf("   properties are not important for this type of command but it is really important to specify the same content\r\n");
	printf("   (message text or image or shape type)\r\n");
	printf(" - head - it has the same behaviour like --keep, the difference is that the command keeps the object on the \r\n");
	printf("   screen but is not asking the workflow because is skip it. So, when you are using this option the command will\r\n");
	printf("   not go in memory, will just simple display the object on the screen.\r\n");

	printf("\nExamples:\r\n");
	printf("  %s --message=\"%s\" --xpoint=-2021 -y5 --head\r\n", fn, DISTRIBUTION);
	printf("  %s --message=\"%s\" --xpoint=-2021 -y5 --head\r\n", fn, DISTRIBUTION);
	printf("  %s --message=\"System Setup\" -x5 -y5 --wipe\r\n", fn);
	printf("  %s --image=splash --console --reset\r\n", fn);
}

void usageCoords(char *fn) {

	printf("\n* Relative coordinates *\r\n");
	printf("\nJust to have flexibility render the graphical objects (messages, shapes and images) on any graphical\r\n");
	printf("console (display - monitors, TVs, custom displays) it was implemented a mechanism to render the object\r\n");
	printf("using relative coordinates. The way to define such relative coordinates considering the total height\r\n");
	printf("and width of the screen; the relative coordinate is actually a fraction between two numbers; just to\r\n");
	printf("differentiate it by regular coordinates the relative coordinates have negative values.\r\n");

	printf("\nThe fraction contains at least two digits and a value like -12 means 1/2 from screen height or width.\r\n");
	printf("So mean -12 screen center. A number like -34 means 3/4 from the height or width; -2021 means 20/21 from\r\n");
	printf("screen width or height, so very close to the right/down limit of the screen. A number like -110 means 1/10\r\n");
	printf("from the height or width of the screen, so very close to the left/top limit of the screen.\r\n");

	printf("\nThe relative coordinate are applicable only to the origin coordinates options -x or --xpoint, and -y or --ypoint,\r\n");
	printf("and in case no values are are specified to these options, relative values will be considered - always referring\r\n");
	printf("to middle of the screen.\r\n");

	printf("\nExamples:\r\n");
	printf("  %s --image=splash\r\n", fn);
	printf("  %s --message=\"%s\" --xpoint=-12 -y5 --\r\n", fn, DISTRIBUTION);

	printf("\nExamples above display splash.png centered and \"%s\" text at position of\r\n", DISTRIBUTION);
	printf("screen width - ( screen width * 1/2 or 0.5 or half ) which is also at the center of screen.\r\n");
}

void usageSystem(char *fn) {

	printf("\n* System *\r\n");
	printf("\nWhen it's time to end your splash display, you can use option exit.\r\n");
	printf("If needed, you can add a delay of selected amount of seconds before\r\n");
	printf("exiting.\r\n");

	printf("\nExamples:\r\n");
	printf("  %s --exit\r\n", fn);
	printf("  %s --exit=5\r\n", fn);

	printf("\nLast example delays exiting with 5 seconds.\r\n");
}

void usageAll(char *fn) {

	usageCommon(fn);
	usageImages(fn);
	usageMessages(fn);
	usageShapes(fn);
	usageDisplay(fn);
	usageCoords(fn);
	usageSystem(fn);
	printf("\r\n");
}

void usage(char *fn, bool images, bool messages, bool shapes, bool display, bool coords, bool sys) {

	if ( !images && !messages && !shapes && !display && !coords && !sys ) {
		usageUsage(fn);
		return;
	}

	usageCommon(fn);

	if ( images )
		usageImages(fn);

	if ( messages )
		usageMessages(fn);

	if ( shapes )
		usageShapes(fn);

	if ( display )
		usageDisplay(fn);

	if ( coords )
		usageCoords(fn);

	if ( sys )
		usageSystem(fn);

	printf("\r\n");
}

bool parseUsage(int argc, char **argv) {

	if ( argc <= 1 ) {
		usageEmpty(basename(argv[0]));
		return true;
	}

	bool wantHelp = false;
	bool helpHelp = false;
	bool helpImg = false;
	bool helpMsg = false;
	bool helpShp = false;
	bool helpDsp = false;
	bool helpCoord = false;
	bool helpSys = false;
	bool helpAll = false;

	for ( int i = 0; i < argc; i++ ) {

		if (strcmp(argv[i], "--help") == 0 || (strcmp(argv[i], "-help") == 0 ))
			wantHelp = true;

		if ( !wantHelp ) continue;
		else if (strcmp(argv[i], "help") == 0 || strcmp(argv[i], "usage") == 0 )
			helpHelp = true;
		else if (strcmp(argv[i], "image") == 0 || strcmp(argv[i], "images") == 0 || strcmp(argv[i], "img") == 0 )
			helpImg = true;
		else if (strcmp(argv[i], "messages") == 0 || strcmp(argv[i], "messages") == 0 || strcmp(argv[i], "msg") == 0 )
			helpMsg = true;
		else if (strcmp(argv[i], "shape") == 0 || strcmp(argv[i], "shapes") == 0 || strcmp(argv[i], "shp") == 0 )
			helpShp = true;
		else if (strcmp(argv[i], "display") == 0 || strcmp(argv[i], "displays") == 0 || strcmp(argv[i], "dsp") == 0 )
			helpDsp = true;
		else if (strcmp(argv[i], "coordinate") == 0 || strcmp(argv[i], "coordinates") == 0 || strcmp(argv[i], "coords") == 0 || strcmp(argv[i], "coord") == 0 )
			helpCoord = true;
		else if (strcmp(argv[i], "system") == 0 || strcmp(argv[i], "sys") == 0 )
			helpSys = true;
		else if (strcmp(argv[i], "all") == 0 ) {
			helpAll = true;
			break;
		}
	}

	if ( wantHelp && helpAll ) {
		usageAll(basename(argv[0]));
		return true;
	} else if ( wantHelp && helpHelp && !helpImg && !helpMsg && !helpShp && !helpDsp && !helpCoord && !helpSys ) {
		usageUsage(basename(argv[0]));
		return true;
	} else if ( wantHelp ) {
		usage(basename(argv[0]), helpImg, helpMsg, helpShp, helpDsp, helpCoord, helpSys);
		return true;
	} else if ( wantHelp && !helpHelp && !helpImg && !helpMsg && !helpShp && !helpDsp && !helpCoord && !helpSys ) {
		usageEmpty(basename(argv[0]));
		return true;
	}

	return false;
}
