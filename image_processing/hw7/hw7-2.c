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
	
	// img_array stores old images, new_img_array stores new ones
  img *old_img, *tmp_img ;
  limg	*projection_limg ;
  long i, x, y ;
	FILE *fp ;
  
	/***********************************************************/
	/*                       PROJECTION                         /
	/***********************************************************/
	
	// Slightly modified from part one
	
	// Simplified variant of projection generation.
	// Since we are only concerned with theta = 0, pi/2
	// we can just sum up the rows/cols of the image
	
	// Read image
  old_img = read_img( "hw7", argv[1] ) ;
		
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
	projection_limg = create_limg( "hw7", old_img->cols, 2 ) ;
		
	// Initialize new_img_array[i]
	for( x = 0 ; x < projection_limg->size ; x++ ) projection_limg->image[x] = 0 ;
		
	// Get values for theta = 0
	// We can simply iterate the columns of the image since the impulse
	// function forces all other columns in the sum to zero (p370)
	for( x = 0 ; x < old_img->cols ; x++ ) {
	  for( y = 0 ; y < old_img->rows ; y++ ) {
		  projection_limg->image[0 * projection_limg->cols + x] += old_img->image[y * old_img->cols + x] ;
	  }
	}
		
	// Get values for theta = pi/2
	for( y = 0 ; y < old_img->rows ; y++ ) {
	  for( x = 0 ; x < old_img->cols ; x++ ) {
		  projection_limg->image[1 * projection_limg->cols + y] += old_img->image[y * old_img->cols + x] ;
	  }
	}
	
  /***********************************************************/
	/*                    BACKPROJECTION                        /
	/***********************************************************/
	
	// Initialize new images to store backprojection
	// Doesn't matter how we initialize; this is quickest for me
	img *back_img = read_img( "hw7", argv[1] ) ;
	limg *back_limg = create_limg( "hw7", back_img->cols, back_img->rows ) ;
	
		// Calculate backprojection
	for( x = 0 ; x < back_limg->cols ; x++ ) {
	  for( y = 0 ; y < back_limg->rows ; y++ ) {
		  // b(x,y) = p(x,0) + p(y/(pi/2))
		  back_limg->image[x * back_limg->rows + y] = (projection_limg->image[x] + projection_limg->image[projection_limg->cols + y]) ;
		}
	}
	
	// Scale back_limg to [0,255]
	long max = -1, min = 2147483645 ;
	
	// Find max/min intensities
	for( x = 0 ; x < back_limg->size ; x++ ) {
		max = MAX( back_limg->image[x], max ) ;
		min = MIN( back_limg->image[x], min ) ;
	}
	
	// Scale
	for( x = 0 ; x < back_limg->size ; x++ ) {
	  back_limg->image[x] = ( 255 * ( back_limg->image[x] - min )) / max ;	
	}
	
	// Copy from limg into img
	for( x = 0 ; x < back_img->size ; x++ ) {
		back_img->image[x] = (int)back_limg->image[x] ;
	}
	
  // Write	
	write_img( "hw7", back_img, "bp.img" ) ;
	
  return ;
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