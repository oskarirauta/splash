
/**
 * Clue Media Experience
 * usage.c - Splash configuration and workflow implementation
 */

#ifndef __USAGE_H__
#define __USAGE_H__

void usageTitle();
void usageCommon(char *fn);
void usageEmpty(char *fn);
void usageUsage(char *fn);
void usageMessages(char *fn);
void usageImages(char *fn);
void usageShapes(char *fn);
void usageDisplay(char *fn);
void usageCoords(char *fn);
void usageSystem(char *fn);
void usageAll(char *fn);
void usage(char *fn, bool images, bool messages, bool shapes, bool display, bool coords, bool sys);
bool parseUsage(int argc, char **argv);

#endif
