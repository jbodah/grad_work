/***************************************************/
/* Programmer: Joshua Bodah                        */
/*                                                 */
/* CS 545 HW7                                      */
/***************************************************/

// Note: I pad images in this program. When I graphed these padded images
//   I ignored lines which were generated due to padding. This data remains
//   in my files, and I remove it from my text file manually.

#include <stdio.h>
#include <math.h>
#include "img.h"

// Same thing as an img, it just stores longs
typedef struct {
  long cols;
  long rows;
  long size;     /* cols * rows */
  long *image;
} limg;

void to_file( limg *some_img, char *name ) ;
limg *create_limg (char *prog_name, long cols, long rows) ;

void main( int argc, char *argv[] ) {

  if( argc != 4 ) {
    printf( "\nExpecting arguments: three .img files\n\n" ) ;
    return ;
  }
	
	// img_array stores old images, new_img_array stores new ones
  img *old_img, *tmp_img ;
  limg	*limg_array[3] ;
  long i, x, y ;
	FILE *fp ;
  
	// Simplified variant of projection generation.
	// Since we are only concerned with theta = 0, pi/2
	// we can just sum up the rows/cols of the image
  for( i = 0 ; i < 3 ; i++ ) {
		// Read image
    old_img = read_img( "hw7", argv[i+1] ) ;
		
	  // I assume the input image is square, so I pad images that aren't square
		if( old_img->cols != old_img->rows ) {
			
			tmp_img = create_img( "hw7", MAX( old_img->cols, old_img->rows ), MAX( old_img->cols, old_img->rows ), 1 ) ;
			
			// Initialize tmp_img to zeroes
			for( x = 0 ; x < tmp_img->size ; x++ ) tmp_img->image[x] = 0 ;
			
			// Copy old image into temp image
			for( y = 0 ; y < old_img->rows ; y++ ) {
			  for( x = 0 ; x < old_img->cols ; x++ ) {
				  tmp_img->image[y * tmp_img->cols + x] = old_img->image[y * old_img->cols + x] ;
				}
		  }
			
			// Replace old image with padded image
			old_img = tmp_img ;
		}
		
		// Note: projections will be stored in the format:
		//   The first half of the image array will store the first
		//   phi_max - phi_min numbers corresponding to theta = 0.
		//   The second half will store the numbers corresponding to
		// 	 theta = pi/2. We assume phi to increment one pixel at a time,
		//   so phi_min = 0 and phi_max = old_img->cols - 1
		limg_array[i] = create_limg( "hw7", old_img->cols, 2 ) ;
		
		// Initialize new_img_array[i]
		for( x = 0 ; x < limg_array[i]->size ; x++ ) limg_array[i]->image[x] = 0 ;
				
		// Get values for theta = 0
		// We can simply iterate the columns of the image since the impulse
		// function forces all other columns in the sum to zero (p370)
	  for( x = 0 ; x < old_img->cols ; x++ ) {
		  for( y = 0 ; y < old_img->rows ; y++ ) {
			  limg_array[i]->image[0 * limg_array[i]->cols + x] += old_img->image[y * old_img->cols + x] ;
		  }
	  }
				
	  // Get values for theta = pi/2
	  for( y = 0 ; y < old_img->rows ; y++ ) {
		  for( x = 0 ; x < old_img->cols ; x++ ) {
			  limg_array[i]->image[1 * limg_array[i]->cols + y] += old_img->image[y * old_img->cols + x] ;
		  }
	  }
	}
	
	// Store projection values in a text file
	to_file( limg_array[0], "0.txt" ) ;
	to_file( limg_array[1], "1.txt" ) ;
  to_file( limg_array[2], "2.txt" ) ;
		
  return ;
}



// Prints contents to a text file
void to_file( limg *some_img, char *name ) {

  long x, y ;
  FILE *fp = fopen( name , "a+" ) ;
	
	for( y = 0 ; y < some_img->rows ; y++ ) {
	  for( x = 0 ; x < some_img->cols ; x++ ) {
		  fprintf( fp, "%ld\r", some_img->image[y * some_img->cols + x] ) ; 
			// Used for debugging
			// fprintf( fp, "(%d,%d) ", y, x ) ; 
		}
		fprintf( fp, "\n\r\n\r\n\r" ) ; 
	}
	fclose( fp ) ;
}



// Pretty much a copy of create_dimg
limg *create_limg (char *prog_name, long cols, long rows) {
  limg *im;
  double *pixels = NULL;
  long int size; 

  /* compute image size */
  size = cols * rows;

  /* data checks */
  if (cols <= 0 || cols > IMG_MAX_COLS) {
    fprintf (stderr, "%s: create_limg, cols %d out of range\n",
	     prog_name, cols);
    exit (-1);
  }
  if (rows <= 0 || rows > IMG_MAX_ROWS)  {
    fprintf (stderr, "%s: create_limg, rows %d out of range\n",
	     prog_name, rows);
    exit (-1);
  }
	
  /* allocate limg struct and check for errors */
  im = (limg *) malloc (sizeof (limg));
  if (im == NULL) {
    fprintf (stderr, "%s: create_limg could not malloc limg struct\n",
	     prog_name);
    exit (-1);
  }

  /* put values into limg struct */
  im->cols = cols;
  im->rows = rows;
  im->size = size;

  /* allocate image data region and check for errors */
  im->image = pixels = (double *) calloc (size, sizeof(double));
  if (im->image == NULL) {
    fprintf (stderr, "%s: create_limg could not calloc %d limg data\n",
	     prog_name, size);
    exit (-1);
  }

  /* erase the pixels */
  while (size-- > 0) { *pixels++ = 0.0; }

  return im; /* success */
} /* end create_limg */