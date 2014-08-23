#include <stdio.h>
#include <stdlib.h>
#include "img.h"

img *bilinear (char *prog_name, img *in, int n)
{
img *out;
long rows = in->rows;
long cols = in->cols;
long new_rows = rows*n;
long new_cols = cols*n;
out = create_img(prog_name, new_cols, new_rows, 1);
float x;
float y;
int i, j;
long x0, x1, y0, y1;
double r00, r01, r10, r11, rx0, rx1;
char rxy;
for (i=0; i<new_rows; i++)
  {
    for (j=0; j<new_cols; j++)
    {
      x = i*rows/new_rows;
      y = j*cols/new_cols;
      x0 = x-0.5;
      x1 = x+0.5;
      y0 = y-0.5;
      y1 = y+0.5;
      r00 = in->image[x0*cols+y0];
      r01 = in->image[x0*cols+y1];
      r10 = in->image[x1*cols+y0];
      r11 = in->image[x1*cols+y1];
      rx0 = r00 + (x-x0)*(r10-r00);
      rx1 = r01 + (x-x0)*(r11-r01);
      rxy = rx0 + (y-y0)*(rx1-rx0);
      out->image[i*new_cols+j] = rxy;
    }
  }
 
return out;
 
}

// argv[1] = img_src_path; argv[2] = img_dst_path; argv[3] = transformation
int main( int argc, char *argv[] ) {

	// Input
	img *src_img = read_img( "hw8", argv[1] ) ;

	write_img( "yo", bilinear( "yo", src_img, 3 ), "test.img" );
	 
  return 0 ;
}