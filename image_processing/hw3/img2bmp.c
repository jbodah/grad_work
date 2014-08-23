/* img2bmp.c
   Michael A. Gennert
   13 Sept 2002

   Convert an image from .img format to .bmp format

   Input parameters:
   input = input file
   output = output file

   Compile String:
     cc img2bmp.c img.o -o img2bmp -O
*/

#include <stdio.h>
#include "img.h"
#include "bmp.h"


// Function prototypes
void print_help_and_exit ();
void write_bmp_img (char *, img *, char *);
void pack_bytes (unsigned char[], long, int);

int main (int argc, char** argv) {
  img *input_img;

  if (argc != 3) { print_help_and_exit (); }

  input_img = read_img (argv[0], argv[1]);

  write_bmp_img (argv[0], input_img, argv[2]);
  
  exit (0);
} // END main


void print_help_and_exit () {
  printf ("Usage: img2bmp input output\n");
  exit (0);
} // END print_help_and_exit


void write_bmp_img (char *prog_name, img *im, char *output_file) {
  FILE *fp;
  bmp_hdr bh;
  unsigned char pixel[3];
  int i;
  unsigned char *r, *g, *b;

  /*  Length of each line = # of columns + padding length
      Must be a multiple of 4 so that line ends on a quad byte boundary. */
  long valid_data_line_length, line_length; 
  long padding_length; 
  unsigned char padding[] = { 0, 0, 0 }; /* Need at most 3 bytes of padding */

  long col, row;

  if (im->colors != 1 && im->colors != 3) {
    fprintf (stderr, "%s: write_bmp_img, can only handle 3 colors, not %d\n",
	     prog_name, im->colors);
    exit (-1);
  }

  /* 3 bytes per pixel */
  valid_data_line_length = 3 * im->cols;
  /* pad to multiple of 4 */
  padding_length = 4 - (valid_data_line_length % 4);
  /* ensure that 0 <= padding < 4 */
  padding_length = padding_length % 4;
  line_length = valid_data_line_length + padding_length;

  bh.BMP_signature[0] = 'B'; 
  bh.BMP_signature[1] = 'M'; 
  pack_bytes (bh.BMP_filesize, sizeof(bmp_hdr) + im->rows * line_length, 4); 
  pack_bytes (bh.BMP_reserved, 0, 4);
  pack_bytes (bh.BMP_dataoffset, sizeof(bmp_hdr), 4);
  pack_bytes (bh.BMP_size, 40, 4);
  pack_bytes (bh.BMP_width, im->cols, 4);
  pack_bytes (bh.BMP_height, im->rows, 4);
  pack_bytes (bh.BMP_planes, 1, 2);
  pack_bytes (bh.BMP_bitcount, 24, 2);
  pack_bytes (bh.BMP_compression, 0, 4); 
  pack_bytes (bh.BMP_imagesize, 0, 4);
  pack_bytes (bh.BMP_xpixelsperm, 0, 4);
  pack_bytes (bh.BMP_ypixelsperm, 0, 4);
  pack_bytes (bh.BMP_colorsused, 0, 4);
  pack_bytes (bh.BMP_colorsimportant, 0, 4);


  fp = fopen (output_file, "wb");
  if (fp == NULL) {
    fprintf (stderr, "%s: write_bmp_img, file ", prog_name);
    perror (output_file);
    exit (-1);
  }

  if (fwrite(&bh, 1, sizeof(bmp_hdr), fp) != sizeof(bmp_hdr)) {
    fprintf (stderr, "%s: write_bmp_img, could not write header for %s\n",
	    prog_name, output_file);
    exit (-1);
  }

  if (im->colors == 1) { r = g = b = im->image; } // greyscale
  else { // RGB color
    r = im->image;
    g = r + im->rows * im->cols;
    b = g + im->rows * im->cols;
  }

  for (row = im->rows - 1; row >= 0; row--) {
    for (col = 0; col < im->cols; col++) {
      /* write valid data */
      pixel[2] = *(r + col + row * im->cols);
      pixel[1] = *(g + col + row * im->cols);
      pixel[0] = *(b + col + row * im->cols);
      if (fwrite(pixel, 3, 1, fp) != 1) { 
	fprintf (stderr, "%s: write_bmp_img, could not write pixel for %s\n",
		 prog_name, output_file);
	exit (-1);
      }
    } // end for col
    
    /* write padding */
    if (padding_length > 0) {
      if (fwrite(padding, padding_length, 1, fp) != 1) { 
	fprintf (stderr, "%s: write_bmp_img, could not write padding for %s\n",
		 prog_name, output_file);
	exit (-1);
      } // end write padding
    } // end for row
  }

  if (fclose (fp) == EOF) {
    fprintf (stderr, "%s: write_bmp_img, file ", prog_name);
    perror (output_file);
    exit (-1);
  }

} // END write_bmp_img


void pack_bytes (unsigned char dst[], long src, int bytes) {
  int i;
  for (i = 0; i < bytes; i++) {
    dst[i] = (src >> (8*i)) & 255;
  }  
} // END pack_bytes
