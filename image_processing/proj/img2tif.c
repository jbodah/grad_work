/* cs545 F97/98, transform a gray-scale or color digital image into a tiff image */
/* Written by Norman Wittels */
/* 20Mar97	first version */
/* 28Mar97	Updated to TIFF v6, fixed a problem with a tag, added all "required" tags */
/* 30Apr97	Updated to include 24-bit rgb color */
/* 13Sep02      Use img.c */

/* compile string:
   cc img2tif.c img.o -o img2tif
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>
#include <time.h>
#include <float.h>
#include "img.h"
#include "tif.h"


/*
int main (int argc, char **argv) {
  char file_name[IMG_FILE_NAME_LENGTH];
  int cols, rows, colors;
  img *im;
  long int size, strip;
  unsigned char *p2im; 


  if (argc != 3) { print_help_and_exit (); }

  im = read_img (argv[0], argv[1]);

  write_tiff (argv[0], im, argv[2]);

  exit (0);
} // END main
*/


void write_tiff (char *prog_name, img *im, char *output_file) {
  FILE *f;
  long strip;

  /* open file and check for errors */
  f = fopen (output_file, "wb");
  if (f == NULL) {
    fprintf (stderr, "%s: write_tiff, file ", prog_name);
    perror (output_file);
    exit (-1);
  }

  /* write the tiff header */
  fputc('M',f); fputc('M',f);  /* byte order */
  fputc(0,f); fputc(42,f); /* "version" number */
  fputc(0,f); fputc(0,f); fputc(0,f); fputc(0x10,f); /* ifd offset */
  
  /* write the ifd */
  fseek(f,0x10,SEEK_SET); /* beginning of ifd */
  fputc(0,f); fputc(14,f); /* number of entries */

  fputc(0x00,f); fputc(0xfe,f); /* tag 254 - NEW SUBFILE TYPE */
  fputc(0x00,f); fputc(0x04,f); /* type LONG */
  fputc(0x00,f); fputc(0x00,f); fputc(0x00,f); fputc(0x01,f); /* only 1 of them */
  fputc(0x00,f); fputc(0x00,f); fputc(0x00,f); fputc(0x00,f); /* the usual */

  fputc(0x01,f); fputc(0x00,f); /* tag 256 - I_WIDTH */
  fputc(0x00,f); fputc(0x04,f); /* type LONG */
  fputc(0x00,f); fputc(0x00,f); fputc(0x00,f); fputc(0x01,f); /* only 1 of them */
  fputc(0x00,f); fputc(0x00,f); fputc(im->cols / 256 % 256,f); fputc(im->cols % 256,f); /* the data */

  fputc(0x01,f); fputc(0x01,f); /* tag 257 - I_LENGTH */
  fputc(0x00,f); fputc(0x04,f); /* type LONG */
  fputc(0x00,f); fputc(0x00,f); fputc(0x00,f); fputc(0x01,f); /* only 1 of them */
  fputc(0x00,f); fputc(0x00,f); fputc(im->rows / 256 % 256,f); fputc(im->rows % 256,f); /* the data */
	
  fputc(0x01,f); fputc(0x02,f); /* tag 258 - BITS_PER_SAMPLE */
  fputc(0x00,f); fputc(0x03,f); /* type SHORT */

  if (im->colors == 1) { /* 8-bit grayscale */
    fputc(0x00,f); fputc(0x00,f); fputc(0x00,f); fputc(0x01,f); /* only 1 of them */
    fputc(0x00,f); fputc(0x08,f); fputc(0x00,f); fputc(0x00,f); /* the data - one byte per pixel */
  } /* end if(colors == 1) */
  else if (im->colors == 3) {  /* 24-bit color */
    fputc(0x00,f); fputc(0x00,f); fputc(0x00,f); fputc(0x03,f); /* three of them */
    fputc(0x00,f); fputc(0x00,f); fputc(0x01,f); fputc(0x20,f); /* location of the data */
  } /* end if(colors == 3) */
	
  fputc(0x01,f); fputc(0x03,f); /* tag 259 - COMPRESSION */
  fputc(0x00,f); fputc(0x03,f); /* type SHORT */
  fputc(0x00,f); fputc(0x00,f); fputc(0x00,f); fputc(0x01,f); /* only 1 of them */
  fputc(0x00,f); fputc(0x01,f); fputc(0x00,f); fputc(0x00,f); /* no compression */
  
  fputc(0x01,f); fputc(0x06,f); /* tag 262 - PHOTOMETRIC INTERPRETATION */
  fputc(0x00,f); fputc(0x03,f); /* type SHORT */
  fputc(0x00,f); fputc(0x00,f); fputc(0x00,f); fputc(0x01,f); /* only 1 of them */
  if (im->colors == 1) {
    fputc(0x00,f); fputc(0x01,f); fputc(0x00,f); fputc(0x00,f); /* grayscale level; Black is zero */
  } /* end if(colors) */
  else if (im->colors == 3) {
    fputc(0x00,f); fputc(0x02,f); fputc(0x00,f); fputc(0x00,f); /* 24-bit rgb color; Black is zero */
  } /* end if(colors) */
	
  fputc(0x01,f); fputc(0X11,f); /* tag 273 - STRIP OFFSETS */
  fputc(0x00,f); fputc(0x04,f); /* type LONG */
  if (im->colors == 1) {
    fputc(0x00,f); fputc(0x00,f); fputc(0x00,f); fputc(0x01,f); /* only 1 of them */
    fputc(0x00,f); fputc(0x00,f); fputc(0x03,f); fputc(0x00,f); /* beginning of first (and only) strip */
  } /* end if(colors) */
  else if (im->colors == 3) {
    fputc(0x00,f); fputc(0x00,f); fputc(0x00,f); fputc(0x03,f); /* 3 of them */
    fputc(0x00,f); fputc(0x00,f); fputc(0x01,f); fputc(0x30,f); /* offset of first strip offset */
  } /* end if(colors) */

  fputc(0x01,f); fputc(0x15,f); /* tag 277 - SAMPLES PER PIXEL */
  fputc(0x00,f); fputc(0x03,f); /* type SHORT */
  fputc(0x00,f); fputc(0x00,f); fputc(0x00,f); fputc(0x01,f); /* only 1 of them */
  if (im->colors == 1) { /* 8-bit grayscale */
    fputc(0x00,f); fputc(0x01,f); fputc(0x00,f); fputc(0x00,f); /* one sample per pixel */
  } /* end if(colors) */
  else if (im->colors == 3) { /* 24-bit rgb color */
    fputc(0x00,f); fputc(0x03,f); fputc(0x00,f); fputc(0x00,f); /* three samples per pixel */
  } /* end if(colors) */
	
  fputc(0x01,f); fputc(0x16,f); /* tag 278 - ROWS PER STRIP */
  fputc(0x00,f); fputc(0x04,f); /* type LONG */
  fputc(0x00,f); fputc(0x00,f); fputc(0x00,f); fputc(0x01,f); /* only 1 of them */
  fputc(0x00,f); fputc(0x00,f); fputc(im->rows /256 % 256,f); fputc(im->rows % 256,f); /* the count */
  
  fputc(0x01,f); fputc(0x17,f); /* tag 279 - STRIP BYTE COUNTS */
  fputc(0x00,f); fputc(0x04,f); /* type LONG */
  
  if (im->colors == 1) {
    fputc(0x00,f); fputc(0x00,f); fputc(0x00,f); fputc(0x01,f); /* only 1 of them */
    fputc(im->size / 256 / 256 / 256 % 256, f);
    fputc(im->size / 256 / 256 % 256, f);
    fputc(im->size / 256 % 256,f);
    fputc(im->size % 256,f); /* the count */
  } /* end if(color) */
  else if (im->colors == 3) {
    fputc(0x00,f); fputc(0x00,f); fputc(0x00,f); fputc(0x03,f); /* three of them */
    fputc(0x00,f); fputc(0x00,f); fputc(0x01,f); fputc(0x60,f); /* location of first item */
  } /* end if(color) */
	
  fputc(0x01,f); fputc(0x1A,f); /* tag 282 - X_RESOLUtiON */
  fputc(0x00,f); fputc(0x05,f); /* type RATIONAL */
  fputc(0x00,f); fputc(0x00,f); fputc(0x00,f); fputc(0x01,f); /* only 1 of them */
  fputc(0x00,f); fputc(0x00,f); fputc(0x01,f); fputc(0x00,f); /* location of the data */
	
  fputc(0x01,f); fputc(0x1B,f); /* tag 283 - Y_RESOLUTION */
  fputc(0x00,f); fputc(0x05,f); /* type RATIONAL */
  fputc(0x00,f); fputc(0x00,f); fputc(0x00,f); fputc(0x01,f); /* only 1 of them */
  fputc(0x00,f); fputc(0x00,f); fputc(0x01,f); fputc(0x10,f); /* location of the data */
  
  fputc(0x01,f); fputc(0x1C,f); /* tag 284 - PLANAR_CONFIGURATION */
  fputc(0x00,f); fputc(0x03,f); /* type SHORT */
  fputc(0x00,f); fputc(0x00,f); fputc(0x00,f); fputc(0x01,f); /* only 1 of them */
  fputc(0x00,f); fputc(0x02,f); fputc(0x00,f); fputc(0x00,f); /* planar format */

  fputc(0x01,f); fputc(0x28,f); /* tag 296 - RESOLUTION_UNIT */
  fputc(0x00,f); fputc(0x03,f); /* type SHORT */
  fputc(0x00,f); fputc(0x00,f); fputc(0x00,f); fputc(0x01,f); /* only 1 of them */
  fputc(0x00,f); fputc(0x02,f); fputc(0x00,f); fputc(0x00,f); /* default value - inches */
  
  fputc(0,f); fputc(0,f); fputc(0,f); fputc(0,f); /* there is no other ifd */
  
  fseek(f,0x100,SEEK_SET); /* X_RESOLUTION data */	
  fputc(0,f); fputc(0,f); fputc(0,f); fputc(72,f); /* 72/inch is default */
  fputc(0,f); fputc(0,f); fputc(0,f); fputc(1,f);
  fseek(f,0x110,SEEK_SET); /* Y_RESOLUTION data */	
  fputc(0,f); fputc(0,f); fputc(0,f); fputc(72,f); /* 72/inch is default */
  fputc(0,f); fputc(0,f); fputc(0,f); fputc(1,f);
  fseek(f,0x120,SEEK_SET); /* BITS_PER_SAMPLE data */	
  fputc(0x00,f); fputc(0x08,f); /* one byte per color */
  fputc(0x00,f); fputc(0x08,f);
  fputc(0x00,f); fputc(0x08,f);

  fseek(f,0x130,SEEK_SET); /* STRIP_OFFSETS data */	
  strip = 0x300; /* beginning of red strip */
  fputc(strip / 256 / 256 / 256 % 256, f);
  fputc(strip / 256 / 256 % 256, f);
  fputc(strip / 256 % 256,f);
  fputc(strip % 256,f);
  strip = im->size / 3 + 0x300; /* beginning of green strip */
  fputc(strip / 256 / 256 / 256 % 256, f);
  fputc(strip / 256 / 256 % 256, f);
  fputc(strip / 256 % 256,f);
  fputc(strip % 256,f);
  strip = 2 * im->size / 3 + 0x300; /* beginning of blue strip */
  fputc(strip / 256 / 256 / 256 % 256, f);
  fputc(strip / 256 / 256 % 256, f);
  fputc(strip / 256 % 256,f);
  fputc(strip % 256,f);
  fseek(f,0x160,SEEK_SET); /* STRIP_BYTE_COUNTS data */	
  fputc(im->size / 3 / 256 / 256 / 256 % 256, f); /* red */
  fputc(im->size / 3 / 256 / 256 % 256, f);
  fputc(im->size / 3 / 256 % 256,f);
  fputc(im->size / 3 % 256,f);
  fputc(im->size / 3 / 256 / 256 / 256 % 256, f); /* green */
  fputc(im->size / 3 / 256 / 256 % 256, f);
  fputc(im->size / 3 / 256 % 256,f);
  fputc(im->size / 3 % 256,f);
  fputc(im->size / 3 / 256 / 256 / 256 % 256, f); /* blue */
  fputc(im->size / 3 / 256 / 256 % 256, f);
  fputc(im->size / 3 / 256 % 256,f);
  fputc(im->size / 3 % 256,f);

  fseek(f,0x300,SEEK_SET); /* where to begin writing data */	
  fwrite(im->image,1,im->size,f); /* write the data */
  destroy_img(prog_name, im); /* clean up */
} /* end write_tiff */

 /*** set all pixels to a color ***/
void erase_img(img *img, unsigned char *color_ptr)
	{
	int size = img->cols * img->rows;
	int pixel = 0; int color = 0; /* loop counters */
	unsigned char *image_ptr = img->image; /* pointer to pixel data */
	for (color = 0; color < img->colors; color++) /* loop through color planes */
		{
		for (pixel=0;pixel<size;pixel++) /* loop through pixels within a color plane */
			*(image_ptr++) = *color_ptr; /* write a pixel */
		color_ptr++; /* go to next color */
		} /* end for(color) */
	} /* end erase_img() */


void print_help_and_exit () {
  printf ("Usage: img2tif input output\n");
  exit (0);
} // END print_help_and_exit

/* Copyright 1997 - 2002, Norman Wittels and Michael A. Gennert */

