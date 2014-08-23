/* cs545 F02, transform a tiff image into a digital image */
/* Written by Michael A. Gennert */

/* compile string:
   cc tif2img.c img.o -o tif2img -ltiff
*/

#include <stdlib.h>
#include <stdio.h>
#include <tiffio.h>
#include "img.h"

/* prototypes */
void print_help_and_exit ();
img *read_tiff (char *, char *); 

int main (int argc, char **argv) {
  img *im;

  /* check number of args */
  if (argc != 3) { print_help_and_exit (); }

  im = read_tiff (argv[0], argv[1]);

  write_img (argv[0], im, argv[2]);

  exit (0);
} // END main

img *read_tiff (char *prog_name, char *input_file) {
  img *im = NULL;

  TIFF * tif;
  uint32 w, h;
  size_t npixels;
  uint32* raster;

  int colors;
  unsigned char *im_data;
  long row, col;
  
  tif = TIFFOpen (input_file, "r");
  if (tif == NULL) {
    fprintf (stderr, "%s: Error opening tiff file %s\n", prog_name, input_file);
    exit (-1);
  }

  // Get TIFF size
  TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &w);
  TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &h);
  npixels = w * h;
  raster = (uint32*) _TIFFmalloc(npixels * sizeof (uint32));

  if (raster == NULL) {
    fprintf (stderr, "%s: TIFFmalloc unable to allocate %dl pixels\n",
	     prog_name, npixels);
    exit (-1);
  }

  if (!TIFFReadRGBAImage(tif, w, h, raster, 0)) {
    fprintf (stderr, "%s: TIFFReadRGBAImage error\n",
	     prog_name);
    exit (-1);
  }

  colors = 1; // Someday figure out the actual number of colors

  im = create_img (prog_name, w, h, colors);

  im_data = im->image;
  for (row = h - 1; row >= 0; row--) {
    for (col = 0; col < w; col++) {
    *(im_data++) = (unsigned char) ( ( (int)TIFFGetR (raster[row * w + col]) +
				       (int)TIFFGetG (raster[row * w + col]) +
				       (int)TIFFGetB (raster[row * w + col]) )
				     / 3);
    }
  }

  return im;
} // END read_tiff

void print_help_and_exit () {

  printf ("Usage: tif2img input output\n");
  exit (0);
} // END print_help_and_exit

/* Copyright 2002 Michael A. Gennert */

