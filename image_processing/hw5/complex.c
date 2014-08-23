/* complex.c 
   complex image routines for cs545/ee545 
   
   compile string:
   cc -c complex.c

*/

/* 09Oct02 MAG,  First version */

/* includes */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "img.h"
#include "cimg.h"


/*** create a complex image struct ***/
cimg *create_cimg (char *prog_name, long cols, long rows) {
  cimg *im;
  complex *pixels = NULL;
  long int size; 

  /* compute image size */
  size = cols * rows;

  /* data checks */
  if (cols <= 0 || cols > IMG_MAX_COLS) {
    fprintf (stderr, "%s: create_cimg, cols %d out of range\n",
	     prog_name, cols);
    exit (-1);
  }
  if (rows <= 0 || rows > IMG_MAX_ROWS)  {
    fprintf (stderr, "%s: create_cimg, rows %d out of range\n",
	     prog_name, rows);
    exit (-1);
  }
	
  /* allocate cimg struct and check for errors */
  im = (cimg *) malloc (sizeof (cimg));
  if (im == NULL) {
    fprintf (stderr, "%s: create_cimg could not malloc cimg struct\n",
	     prog_name);
    exit (-1);
  }

  /* put values into cimg struct */
  im->cols = cols;
  im->rows = rows;
  im->size = size;

  /* allocate image data region and check for errors */
  im->image = pixels = (complex *) calloc (size, sizeof(complex));
  if (im->image == NULL) {
    fprintf (stderr, "%s: create_cimg could not calloc %d cimg data\n",
	     prog_name, size);
    exit (-1);
  }

  /* erase the pixels */
  while (size-- > 0) {
    pixels->r = 0.0;
    pixels->i = 0.0;
    pixels++;
  }

  return im; /* success */
} /* end create_cimg */


/*** create a complex image struct ***/
dimg *create_dimg (char *prog_name, long cols, long rows) {
  dimg *im;
  double *pixels = NULL;
  long int size; 

  /* compute image size */
  size = cols * rows;

  /* data checks */
  if (cols <= 0 || cols > IMG_MAX_COLS) {
    fprintf (stderr, "%s: create_dimg, cols %d out of range\n",
	     prog_name, cols);
    exit (-1);
  }
  if (rows <= 0 || rows > IMG_MAX_ROWS)  {
    fprintf (stderr, "%s: create_dimg, rows %d out of range\n",
	     prog_name, rows);
    exit (-1);
  }
	
  /* allocate dimg struct and check for errors */
  im = (dimg *) malloc (sizeof (dimg));
  if (im == NULL) {
    fprintf (stderr, "%s: create_dimg could not malloc dimg struct\n",
	     prog_name);
    exit (-1);
  }

  /* put values into dimg struct */
  im->cols = cols;
  im->rows = rows;
  im->size = size;

  /* allocate image data region and check for errors */
  im->image = pixels = (double *) calloc (size, sizeof(double));
  if (im->image == NULL) {
    fprintf (stderr, "%s: create_dimg could not calloc %d dimg data\n",
	     prog_name, size);
    exit (-1);
  }

  /* erase the pixels */
  while (size-- > 0) { *pixels++ = 0.0; }

  return im; /* success */
} /* end create_dimg */


/* convert img to cimg */
cimg *img2cimg (char *prog_name, img *in) {
  cimg *out;
  unsigned char *in_pixel;
  complex *out_pixel;
  long cols, rows, size; 
  
  /* if NULL in, then NULL out */
  if (in == NULL) { return NULL; }

  // check # of colors
  if (in->colors != 1) {
    fprintf (stderr, "%s: img2cimg only on greyscale, not %d colors\n",
	     prog_name, in->colors);
    exit (-1);
  }

  /* get image size, etc */
  cols = in->cols;
  rows = in->rows;
  size = in->size;
  
  /* create image struct with no data yet */
  out = create_cimg (prog_name, cols, rows);
  
  in_pixel = in->image;
  out_pixel = out->image; 
  
  /* copy in to out */
  while (size-- > 0) {
    out_pixel->r = *in_pixel;
    out_pixel->i = 0.0;
    out_pixel++;
    in_pixel++;
  } /* copy pixels */
  
  return out;
} /* end img2cimg */


/* convert img to dimg */
dimg *img2dimg (char *prog_name, img *in) {
  dimg *out;
  unsigned char *in_pixel;
  double *out_pixel;
  long cols, rows, size; 
  
  /* if NULL in, then NULL out */
  if (in == NULL) { return NULL; }

  // check # of colors
  if (in->colors != 1) {
    fprintf (stderr, "%s: img2dimg only on greyscale, not %d colors\n",
	     prog_name, in->colors);
    exit (-1);
  }

  /* get image size, etc */
  cols = in->cols;
  rows = in->rows;
  size = in->size;
  
  /* create image struct with no data yet */
  out = create_dimg (prog_name, cols, rows);
  
  in_pixel = in->image;
  out_pixel = out->image; 
  
  /* copy in to out */
  while (size-- > 0) {
    *out_pixel++ = (double) *in_pixel++;
  } /* copy pixels */
  
  return out;
} /* end img2dimg */


/* Extract real part */
dimg *re_part (char *prog_name, cimg *in) {
  dimg *out;
  complex *in_pixel;
  double *out_pixel;
  long cols, rows, size; 
  
  /* if NULL in, then NULL out */
  if (in == NULL) { return NULL; }

  /* get image size, etc */
  cols = in->cols;
  rows = in->rows;
  size = in->size;
  
  /* create image struct with no data yet */
  out = create_dimg (prog_name, cols, rows);
  
  in_pixel = in->image;
  out_pixel = out->image; 
  
  /* copy in to out */
  while (size-- > 0) {
    *out_pixel++ =  (in_pixel++)->r;
  } /* copy pixels */
  
  return out;
} /* end re_part */


/* Extract imaginary part */
dimg *im_part (char *prog_name, cimg *in) {
  dimg *out;
  complex *in_pixel;
  double *out_pixel;
  long cols, rows, size; 
  
  /* if NULL in, then NULL out */
  if (in == NULL) { return NULL; }

  /* get image size, etc */
  cols = in->cols;
  rows = in->rows;
  size = in->size;
  
  /* create image struct with no data yet */
  out = create_dimg (prog_name, cols, rows);
  
  in_pixel = in->image;
  out_pixel = out->image; 
  
  /* copy in to out */
  while (size-- > 0) {
    *out_pixel++ =  (in_pixel++)->i;
  } /* copy pixels */
  
  return out;
} /* end im_part */


/* Extract magnitude */
dimg *mg_part (char *prog_name, cimg *in) {
  dimg *out;
  complex *in_pixel;
  double *out_pixel;
  double real_part, imag_part;
  long cols, rows, size; 
  
  /* if NULL in, then NULL out */
  if (in == NULL) { return NULL; }

  /* get image size, etc */
  cols = in->cols;
  rows = in->rows;
  size = in->size;
  
  /* create image struct with no data yet */
  out = create_dimg (prog_name, cols, rows);
  
  in_pixel = in->image;
  out_pixel = out->image; 
  
  /* copy in to out */
  while (size-- > 0) {
    real_part = in_pixel->r;
    imag_part = in_pixel->i;
    *out_pixel++ = sqrt(real_part * real_part + imag_part * imag_part);
	//printf( "real = %f, im = %f, out = %f\n", real_part, imag_part, real_part * real_part + imag_part * imag_part ) ;
    in_pixel++;
  } /* copy pixels */
  
  return out;
} /* end mg_part */


/* Extract phase */
dimg *ph_part (char *prog_name, cimg *in) {
  dimg *out;
  complex *in_pixel;
  double *out_pixel;
  double real_part, imag_part;
  long cols, rows, size; 
  
  /* if NULL in, then NULL out */
  if (in == NULL) { return NULL; }

  /* get image size, etc */
  cols = in->cols;
  rows = in->rows;
  size = in->size;
  
  /* create image struct with no data yet */
  out = create_dimg (prog_name, cols, rows);
  
  in_pixel = in->image;
  out_pixel = out->image; 
  
  /* copy in to out */
  while (size-- > 0) {
    real_part = in_pixel->r;
    imag_part = in_pixel->i;
    *out_pixel++ =  atan2(imag_part, real_part);
    in_pixel++;
  } /* copy pixels */
  
  return out;
} /* end ph_part */


/* Without scaling */
img *dimg2img (char *prog_name, dimg *in) {
  img *out;
  double *in_pixel;
  unsigned char *out_pixel;
  long cols, rows, size; 
  
  /* if NULL in, then NULL out */
  if (in == NULL) { return NULL; }

  /* get image size, etc */
  cols = in->cols;
  rows = in->rows;
  size = in->size;
  
  /* create image struct with no data yet */
  out = create_img (prog_name, cols, rows, 1);
  
  in_pixel = in->image;
  out_pixel = out->image; 
  
  /* copy in to out */
  while (size-- > 0) {
    if (*in_pixel < IMG_BLACK) { *out_pixel = IMG_BLACK; }
    else if (*in_pixel >= IMG_WHITE) { *out_pixel = IMG_WHITE; }
    else *out_pixel = (unsigned char) (*in_pixel + 0.5);
    in_pixel++;
    out_pixel++;
  } /* copy pixels */
  
  return out;
} /* end dimg2img */


/* Scale to 0 - 255 */
img *dimg2img_scale (char *prog_name, dimg *in) {
  img *out;
  double *in_pixel;
  unsigned char *out_pixel;
  long cols, rows, size;
  long i;
  double min, max;
  double scale;
  
  /* if NULL in, then NULL out */
  if (in == NULL) { return NULL; }

  /* get image size, etc */
  cols = in->cols;
  rows = in->rows;
  size = in->size;
  
  /* find min, max, scale */
  in_pixel = in->image;
  min = max = *in_pixel;
  for (i = 0; i < size; i++) {
    if (*in_pixel < min) { min = *in_pixel; }
    if (*in_pixel > max) { max = *in_pixel; }
    in_pixel++;
  }
  scale = (IMG_WHITE - IMG_BLACK) / (max - min);

  /* create image struct with no data yet */
  out = create_img (prog_name, cols, rows, 1);
  
  in_pixel = in->image;
  out_pixel = out->image; 
  
  /* copy in to out */
  while (size-- > 0) {
    *out_pixel++ = (unsigned char) ( (*in_pixel++ - min) * scale);
  } /* copy pixels */
  
  return out;
} /* end dimg2img_scale */


/*** copy complex image struct ***/
cimg *copy_cimg (char *prog_name, cimg *in) {
  cimg *out;
  complex *in_pixel, *out_pixel;
  long cols, rows, size; 
  
  /* if NULL in, then NULL out */
  if (in == NULL) { return NULL; }

  /* get image size, etc */
  cols = in->cols;
  rows = in->rows;
  size = in->size;
  
  /* create image struct with no data yet */
  out = create_cimg (prog_name, cols, rows);
  
  in_pixel = in->image;
  out_pixel = out->image; 
  
  /* copy in to out */
  while (size-- > 0) {
    out_pixel->r = in_pixel->r;
    out_pixel->i = in_pixel->i;
    out_pixel++;
    in_pixel++;
  } /* copy pixels */
  
  return out;
} /* end copy_cimg */


/*** copy double image struct ***/
dimg *copy_dimg (char *prog_name, dimg *in) {
  dimg *out;
  double *in_pixel, *out_pixel;
  long cols, rows, size; 
  
  /* if NULL in, then NULL out */
  if (in == NULL) { return NULL; }

  /* get image size, etc */
  cols = in->cols;
  rows = in->rows;
  size = in->size;
  
  /* create image struct with no data yet */
  out = create_dimg (prog_name, cols, rows);
  
  in_pixel = in->image;
  out_pixel = out->image; 
  
  /* copy in to out */
  while (size-- > 0) {
    *out_pixel++ = *in_pixel++;
  } /* copy pixels */
  
  return out;
} /* end copy_dimg */


/*** destroy a complex image struct ***/
void destroy_cimg (char *prog_name, cimg *im) {
  if (im == NULL) return; /* nothing to do */
  if (im->image != NULL) free (im->image); /* free data array */
  free(im);
} /* end destroy_cimg */


/*** destroy a double image struct ***/
void destroy_dimg (char *prog_name, dimg *im) {
  if (im == NULL) return; /* nothing to do */
  if (im->image != NULL) free (im->image); /* free data array */
  free(im);
} /* end destroy_dimg */


/* Copyright 2002 Michael A. Gennert */
