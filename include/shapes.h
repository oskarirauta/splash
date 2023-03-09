
/**
 * Clue Media Experience
 *  
 * shapes.h - file containing primitive drawing operation functions.
 *
 * The library has the possibility to draw a circle, a rectangle, a point,
 * and other primitive operations and also, you can update the screen 
 * using the flip function.
 */


#ifndef __SHAPES_H__
#define __SHAPES_H__


#include "utils.h"


#define DEFSHP_COLOR	"#96C2E5"


/**
 * Update command properties with missing attributes, depending by
 * the command that has to be executed.
 * 
 * @param data command data structure
 * @return improved command data structure
 */
CmdData SetShapeProps(CmdData data);

void DrawShape(CmdData data);

void OverdrawShape(CmdData data);

void DrawLine(CmdData data);

void WipeLine(CmdData data);

void DrawRectangle(CmdData data);

void WipeRectangle(CmdData data);

void DrawCircle(CmdData data);

void WipeCircle(CmdData data);

void DrawProgressBar(CmdData data);

void WipeProgressBar(CmdData data);

int __drawPixel(int x, int y, int32_t rgba);
void __drawHorizontalLine(int x, int y, int x2, long color);
void __drawVerticalLine(int x, int y, int y2, int32_t color);
void __drawLine(int x1, int y1, int x2, int y2, int32_t color);
void __drawCircle(int xc, int yc, int radius, int32_t linecolor, int linewidth, int32_t fillcolor);
void __drawRectangle(int xc, int yc, int width, int height, int32_t linecolor, int linewidth, int32_t fillcolor);

int __drawProcessBar(int xc, int yc, int width, int height, int percent, int32_t linecolor, int linewidth, int32_t barcolor, int32_t backgroundcolor);

#endif
