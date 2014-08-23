/* cs545 read and print out the header of a raw digital image */
/* Written by Norman Wittels */
/* 08Mar97 - first version */
/* 02Sep97 - changed around includes and definitions */
/* 13Sep02 - rewritten by MAG to use img.h, img.c */

/* compile string:
   cc prt_hdr.c img.o  -o prt_hdr
*/

/* include eveything */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>
#include <time.h>
#include <float.h>
#include "img.h"


// Function prototypes
void print_help_and_exit ();
void display_hdr (img *);


int main(int argc, char **argv) {
  img *im;

  /* check number of args */
  if (argc != 2) { print_help_and_exit (); }

  im = read_img (argv[0], argv[1]);

  display_hdr (im);
  
  exit(0);
} // END main


void print_help_and_exit () {
  printf ("Usage: prt_hdr imagefile\n");
  exit (0);
} // END print_help_and_exit


void display_hdr (img *im) {
  printf ("cols   = %ld (width)\n", im->cols);
  printf ("rows   = %ld (height)\n", im->rows);
  printf ("colors = %ld\n", im->colors);
  printf ("size   = %ld\n", im->size);
} // END display_hdr
