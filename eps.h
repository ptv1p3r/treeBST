
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include "tree.h"

#ifndef _EPS_
#define MAX_SCALE 12.0f            // resolution scale for the canvase
#define CANVAS_WIDTH 5200
#define CANVAS_HEIGHT 5200
#define SQURE_SCALE 6.0f
#define TEXT_SIZE 50		 
#define	NODE_RADIUS 35
#define PI 3.14

typedef struct _rgb
{
	float r;
	float g; 
	float b;
}rgb;

void write_eps_header(FILE * file_ptr, char * title, int width, int height);

void draw_line(FILE * file_ptr, rgb color, int x1, int y1, int x2, int y2, float width);

void draw_square(FILE * file_ptr, rgb color,  int x1, int y1, int x2, int y2, float width);

void draw_arc(FILE * file_ptr, rgb color,  int x, int y, int radius, int start_angle, int end_angle, float width);

void draw_circle(FILE * file_ptr, rgb color,  int x, int y, int radius, float width);

void draw_link(FILE * file_ptr, rgb color, int x1, int y1, int x2, int y2, int width);

void draw_text(FILE * file_ptr, rgb color, int scale, int x, int y, char * text);

void draw_array(FILE * file_ptr, int * array, int start, int end, int x, int y, int scale, rgb bgcolor, rgb fgcolor);

void draw_node(FILE * file_ptr, rgb color,  int x, int y, int radius, float width, int text_size, char * text);

void draw_tree(FILE * file_ptr, TREE node, float tree_height, int depth, float index, int x, int y);

#endif
