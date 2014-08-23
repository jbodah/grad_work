/* file cimg.h - header file for cs545 complex image format */
/* 26Sep02 MAG wrote it */


/*** type definitions ***/
typedef struct {
  double r;
  double i;
} complex;

typedef struct {
  long cols;
  long rows;
  long size;     /* cols * rows */
  complex *image;
} cimg;

typedef struct {
  long cols;
  long rows;
  long size;     /* cols * rows */
  double *image;
} dimg;


/*** function prototypes ***/
/* all prototypes now take prog_name as 1st arg */
cimg *create_cimg (char *, long, long);            /* create comple image */
dimg *create_dimg (char *, long, long);            /* create double image */

cimg *img2cimg (char *, img *);                    /* convert img to cimg */
dimg *img2dimg (char *, img *);                    /* convert img to dimg */

dimg *re_part (char *, cimg *);                    /* Extract real part */
dimg *im_part (char *, cimg *);                    /* Extract imaginary part */
dimg *mg_part (char *, cimg *);                    /* Extract magnitude */
dimg *ph_part (char *, cimg *);                    /* Extract phase */

img *dimg2img (char *, dimg *);                    /* Without scaling */
img *dimg2img_scale (char *, dimg *);              /* Scale to 0 - 255 */

cimg *copy_cimg (char *, cimg *);                  /* duplicate image struct */
dimg *copy_dimg (char *, dimg *);                  /* duplicate image struct */
void destroy_cimg (char *, cimg *);                /* destroy image struct */
void destroy_dimg (char *, dimg *);                /* destroy image struct */

/* Copyright 2002 Michael A. Gennert */
