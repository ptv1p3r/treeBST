
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include "eps.h"


void write_eps_header(FILE * file_ptr, char * title, int width, int height)
{
	fprintf(file_ptr, "%%!PS-Adobe-3.0 EPSF-3.0\n");
  	fprintf(file_ptr, "%%%%Title:%s\n", title);
  	fprintf(file_ptr, "%%%%BoundingBox: 0 0 %d %d \n", width, height);
  	fprintf(file_ptr, "%%%%EndComments\n");


   // write down all procedures
  	fprintf(file_ptr, "/arrowhead {%% stack: s x1 y1, current point: x0 y0\n");
	fprintf(file_ptr, "gsave\n");
	fprintf(file_ptr, "currentpoint   %% s x1 y1 x0 y0 \n");
	fprintf(file_ptr, "4 2 roll exch  %% s x0 y0 y1 x1 \n");
	fprintf(file_ptr, "4 -1 roll exch %% s y0 y1 x0 x1 \n");
	fprintf(file_ptr, "sub 3 1 roll   %% s x1-x2 y0 y1 \n");
	fprintf(file_ptr, "sub exch       %% s y0-y1 x1-x2 \n");
	fprintf(file_ptr, "atan rotate    %% rotate over arctan((y0-y1)/(x1-x2)) \n");
	fprintf(file_ptr, "dup scale      %% scale by factor s \n");
	fprintf(file_ptr, "-7 2 rlineto 1 -2 rlineto -1 -2 rlineto \n");
	fprintf(file_ptr, "closepath fill  %% fill arrowhead \n");
	fprintf(file_ptr, "grestore \n");
	fprintf(file_ptr, "newpath \n");
	fprintf(file_ptr, "} def \n");



}


void draw_line(FILE * file_ptr, rgb color, int x1, int y1, int x2, int y2, float width)
{
	fprintf(file_ptr, "%f %f %f setrgbcolor newpath %d %d moveto %d %d lineto %f setlinewidth stroke\n", color.r, color.g, color.b, x1, y1, x2, y2, width );
}

void draw_square(FILE * file_ptr, rgb color,  int x1, int y1, int x2, int y2, float width)
{
	fprintf(file_ptr, "%f %f %f setrgbcolor newpath %d %d moveto %d %d rlineto %d %d rlineto %d %d rlineto %d %d rlineto  closepath  %f setlinewidth stroke \n", 
	                 color.r, color.g, color.b, x1, y1, 0, y2, y2, 0, 0, -y2, -y2, 0, width );

}

void draw_arc(FILE * file_ptr, rgb color,  int x, int y, int radius, int start_angle, int end_angle, float width)
{
	 	fprintf(file_ptr, "%f %f %f setrgbcolor newpath %d %d %d %d %d arc closepath %f setlinewidth stroke \n", color.r, color.g, color.b, x, y, radius, start_angle, end_angle, width);

}

void draw_circle(FILE * file_ptr, rgb color,  int x, int y, int radius, float width)
{
	 	fprintf(file_ptr, "%f %f %f setrgbcolor newpath %d %d %d 0 360 arc closepath %f setlinewidth stroke \n", color.r, color.g, color.b, x, y, radius, width);

}


void draw_link(FILE * file_ptr, rgb color, int x1, int y1, int x2, int y2, int width)
{
	//fprintf(file_ptr, "\");
	fprintf(file_ptr, "%d %d translate\n", x1, y1);
	fprintf(file_ptr, "%f %f %f setrgbcolor 0 0 moveto %d %d lineto stroke\n", color.r, color.g, color.b, x2, y2 );
	fprintf(file_ptr, "newpath %d %d moveto %d 0 0 arrowhead \n", x2, y2, width);
	//fprintf(file_ptr, "grestore\n");

}

void draw_text(FILE * file_ptr, rgb color, int scale, int x, int y, char * text)
{
  fprintf(file_ptr, "/Times-Roman findfont %f %f %f setrgbcolor %d scalefont setfont newpath %d %d moveto (%s) show\n", 
  					color.r, color.g, color.b, scale, x, y, text);

}


void draw_array(FILE * file_ptr, int * array, int start, int end, int x, int y, int scale, rgb bgcolor, rgb fgcolor)
{
   int i;
   for(i = start ; i <= end ; i++)
   {
   	draw_square(file_ptr, bgcolor,  x + (i * scale * scale) , y , (scale * scale), (scale * scale), 1);
   	char str[10];
   	sprintf(str, "%d", array[i-1]);
   	draw_text(file_ptr, fgcolor, 20, (x + (i * scale * scale) ) + scale * scale /2 - scale, y + scale * scale /2 -scale, str);
   }
}


void draw_node(FILE * file_ptr, rgb color,  int x, int y, int radius, float width, int text_size, char * text)
{
	
	draw_circle(file_ptr, (rgb){0,1,0}, x, y, radius, width);
	draw_text(file_ptr, (rgb){0,0,0}, text_size, x - (text_size/2), y - (text_size/3), text);
}

void draw_tree(FILE * file_ptr, TREE node, float tree_height, int depth, float index, int x, int y)
{
	if(node != NULL)
	{

		TREE left = get_left(node);
		TREE right = get_right(node);

		ITEM node_item = get_item(node);



		
		char item[2];
		sprintf(item, "%d", get_item_key(node_item));
		draw_node(file_ptr, (rgb){0,1,0}, x, y, NODE_RADIUS, 3, TEXT_SIZE, item);
		
		float lindex = index * 2 - 1;
		float rindex = index * 2 + 1;
		depth = depth + 1;

		int lx = lindex * CANVAS_WIDTH*0.95 / (pow(2, depth) + 1);
		int rx = rindex * CANVAS_WIDTH*0.95 / (pow(2, depth) + 1);

        int ly = depth * CANVAS_HEIGHT*0.95 / tree_height;
        
	    int ry = ly;


	    // rotate
	    lx = lx * cos(PI) - ly * sin(PI);
	    rx = rx * cos(PI) - ry * sin(PI);
	    ly = - lx * sin(PI) + ly * cos(PI);
	    ry = ly;

	    // draw
	    draw_tree(file_ptr,  left, tree_height, depth, lindex, lx, ly);
	    draw_tree(file_ptr,  right, tree_height, depth, rindex, rx, ry);

	    if(left)
	    	draw_line(file_ptr, (rgb){0,0,1}, x, y - NODE_RADIUS, lx, ly + NODE_RADIUS , 5);
	    if(right)
	    	draw_line(file_ptr, (rgb){0,0,1}, x, y - NODE_RADIUS, rx , ry +  NODE_RADIUS , 5);
	}
}


