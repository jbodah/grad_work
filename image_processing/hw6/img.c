/* img.c 
   image io for cs545/ee545 
   
   compile string:
   cc -c img.c

*/

/* 03Aug97 NW,  First version */
/* 02Sep97 HW,  Split into read and read with file query */
/* 13Sep02 MAG, Completely cleaned up and rewritten */

/* includes */
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include "img.h"


/*** read a char image into a specified file ***/
img *read_img (char *prog_name, char *input_file) {
  image_file_header header;
  img *im;
  long cols, rows, colors; 
  size_t items_read;
  FILE *fp;  

  /* open file and check for errors */
  fp = fopen (input_file, "rb");
  if (fp == NULL) {
    fprintf (stderr, "%s: read_img, file ", prog_name);
    perror (input_file);
    exit (-1);
  }

  /* read header and check for errors */
  items_read = fread (&header, sizeof (header), 1, fp);
  if (ferror (fp)) {
    fprintf (stderr, "%s: read_img, file ", prog_name);
    perror (input_file);
    exit (-1);
  }

  if (items_read != 1) {
    fprintf (stderr, "%s: read_img, file %s", prog_name, input_file);
    fprintf (stderr, " expect to read 1 header item, actually read %d items\n",
	     items_read);
    exit (-1);
  }

  /* put msl and lsb together to get true values */
  cols = (header.cols_msb << 8) | header.cols_lsb;
  rows = (header.rows_msb << 8) | header.rows_lsb;
  colors = (header.colors_msb << 8) | header.colors_lsb;

  /* get an img struct to work with */
  im = create_img (prog_name, cols, rows, colors);

  /* read image data and check for errors */
  items_read = fread (im->image, 1, im->size, fp);
  if (ferror (fp)) {
    fprintf (stderr, "%s: read_img file ", prog_name);
    perror (input_file);
    exit (-1);
  }

  if (items_read != im->size) {
    fprintf (stderr, "%s: read_img, file %s", prog_name, input_file);
    fprintf (stderr, " expected %ld items, actually read %ld items\n",
	     im->size, items_read);
    exit (-1);
  }

  /* close file and check for error */
  if (fclose (fp) == EOF) {
    fprintf (stderr, "%s: read_wpi_or_non_wpi_img, file ", prog_name);
    perror (input_file);
    exit (-1);
  }

  /* success */
  return im; 
} /* end read_img */


/*** query user for file name and read image file ***/
img *read_user_specified_img_file (char *prog_name) {
  char file_name[IMG_FILE_NAME_LENGTH];
	
  printf ("Enter input file: ");
  scanf ("%s", file_name);
  return read_img (prog_name, file_name);
} /* end read_user_specified_img_file */


/*** write a char image into a specified file ***/
void write_img (char *prog_name, img *im, char *output_file) {
  image_file_header header;
  size_t items_written;
  FILE *fp;  

  /* open file and check for errors */
  fp = fopen (output_file, "wb");
  if (fp == NULL) {
    fprintf (stderr, "%s: write_img, file ", prog_name);
    perror (output_file);
    exit (-1);
  }

  /* store info in header as unsigned chars */
  header.cols_msb = (im->cols >> 8) & 255;
  header.cols_lsb = im->cols & 255;
  header.rows_msb = (im->rows >> 8) & 255;
  header.rows_lsb = im->rows & 255;
  header.colors_msb = (im->colors >> 8) & 255;
  header.colors_lsb = im->colors & 255;

  /* write header and check for errors */
  items_written = fwrite (&header, sizeof (header), 1, fp);
  if (ferror (fp)) {
    fprintf (stderr, "%s: write_img, file ", prog_name);
    perror (output_file);
    exit (-1);
  }

  if (items_written != 1) {
    fprintf (stderr, "%s: write_img, file %s", prog_name, output_file);
    fprintf (stderr, " expected to write 1 header item, actually wrote %d items\n",
	     items_written);
    exit (-1);
  }

  /* write iamge data and check for errors */
  items_written = fwrite (im->image, 1, im->size, fp);
  if (ferror (fp)) {
    fprintf (stderr, "%s: write_img, file ", prog_name);
    perror (output_file);
    exit (-1);
  }

  if (items_written != im->size) {
    fprintf (stderr, "%s: write_img, file %s", prog_name, output_file);
    fprintf (stderr, " expected to write %d data items, actually wrote %d items\n",
	     im->size, items_written);
    exit (-1);
  }

  /* close file and check for errors */
  if (fclose (fp) == EOF) {
    fprintf (stderr, "%s: write_img, file ", prog_name);
    perror (output_file);
    exit (-1);
  }
} /* end write_img */


/*** query user for file name and write char image file ***/
void write_user_specified_img_file (char *prog_name, img *im) {
  char file_name[IMG_FILE_NAME_LENGTH];

  printf ("Enter output file: ");
  scanf ("%s", file_name);
  write_img(prog_name, im, file_name);
} /* end write_user_specified_img_file */


/*** copy char image struct ***/
img *copy_img (char *prog_name, img *in) {
  img *out;
  unsigned char *in_pixel, *out_pixel;
  long cols, rows, colors, size; 
  
  /* if NULL in, then NULL out */
  if (in == NULL) { return NULL; }

  /* get image size, etc */
  cols = in->cols;
  rows = in->rows;
  colors = in->colors;
  size = in->size;
  
  /* create image struct with no data yet */
  out = create_img (prog_name, cols, rows, colors);
  
  in_pixel = in->image;
  out_pixel = out->image; 
  
  /* copy in to out */
  while (size-- > 0) { *out_pixel++ = *in_pixel++; } /* copy pixels */
  
  return out;
} /* end copy_img */


/*** create a char image struct ***/
img *create_img (char *prog_name, long cols, long rows, long colors) {
  img *im;
  unsigned char *pixels = NULL;
  long int size; 

  /* compute image size */
  size = cols * rows * colors;

  /* data checks */
  if (cols <= 0 || cols > IMG_MAX_COLS) {
    fprintf (stderr, "%s: create_img, cols %d out of range\n",
	     prog_name, cols);
    exit (-1);
  }
  if (rows <= 0 || rows > IMG_MAX_ROWS)  {
    fprintf (stderr, "%s: create_img, rows %d out of range\n",
	     prog_name, rows);
    exit (-1);
  }
  if (colors != 1 && colors != 3)  {
    fprintf (stderr, "%s: create_img, colors %d out of range\n",
	     prog_name, colors);
    exit (-1);
  }
	
  /* allocate img struct and check for errors */
  im = (img *) malloc(sizeof(img));
  if (im == NULL) {
    fprintf (stderr, "%s: create_img could not malloc img struct\n",
	     prog_name);
    exit (-1);
  }

  /* put values into img struct */
  im->cols = cols;
  im->rows = rows;
  im->colors = colors;
  im->size = size;

  /* allocate image data region and check for errors */
  im->image = pixels = (unsigned char *) malloc (size);
  if (im->image == NULL) {
    fprintf (stderr, "%s: create_img could not malloc %d img data\n",
	     prog_name, size);
    exit (-1);
  }

  /* erase the pixels */
  while (size-- > 0) { *pixels++ = IMG_WHITE; }

  return im; /* success */
} /* end create_img */


/*** destroy a char image struct ***/
void destroy_img(char *prog_name, img *im) {
  if (im == NULL) return; /* nothing to do */
  if (im->image != NULL) free(im->image); /* free data array */
  free(im);
} /* end destroy_img */


/* Copyright 1997 - 2002 Norman Wittels and Michael A. Gennert */
