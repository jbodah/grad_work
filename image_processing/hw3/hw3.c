/***************************************************/
/* Programmer: Joshua Bodah                        */
/*                                                 */
/* CS 545 HW3                                      */
/***************************************************/

#include <stdio.h>
#include "img.h"
#include <math.h>

void hw2_header() ;
img *find_img( char *img_name ) ;
void about_img( img *src_img ) ;
void gaussian( char *prog_name, char *dst_name ) ;
void mf( char *prog_name, char *src_name, img *src_img, char *dst_name ) ;

int main() {

  img *src_img ;
  char src_name[IMG_FILE_NAME_LENGTH] ;
  char dst_name[IMG_FILE_NAME_LENGTH] ;
  
  hw2_header() ; 						  					  	  // Intro text
  
  printf( "Input file (.img): " ) ;			   	  	  			  // Prompt user for file name
  scanf( "%s", &src_name ) ;          		  	  				  // Read file name
  
  src_img = find_img( src_name ) ; 							 	  // Load image
  about_img( src_img ) ; 				  					      // Display source image details
  gaussian( "hw2", "g.img" ) ;          					  	  // Creates an image having gaussian intensity
  mf( "hw2", src_name, src_img, "mf.img" ) ;            		  // Median filter
  
  return 0 ;
}


// Intro text about problem
void hw2_header() {
  printf( "\nCS 545 HW3 by Joshua Bodah\n--------------------------\n\n" ) ;
  printf( "Problem sections:\n\t1. Generate an image with gaussian intensity\n\t2. Process an image with a median filter\n\n" ) ;
}


// Tries to load image
img *find_img( char *img_name ) {

  img *im ;

  printf( "\nLoading %s...\n", img_name ) ; // Loading message

  // Read image
  im = read_img( "hw2", img_name ) ; 	  // read_img handles NULL exceptions 
  printf( "%s loaded\n", img_name ) ; 	  // Image found
  
  return im ;
}  


// Prints details about src_img
void about_img( img *src_img ) {
  printf( "\nImage details:\n\tColumns:\t%ld\n\tRows:\t\t%ld\n\tColors:\t\t%ld\n\tSize:\t\t%ld\n",
			src_img->cols, src_img->rows, src_img->colors, src_img->size );
}


// Generates a 600 x 600 grayscale image with gaussian intensity
// I wasn't sure if I would need to scale the float values for the
// Gaussian to convert them into integers properly, so I separate
// the Gaussian array in my code. This was unnecessary, but I left
// it this way since the code works with it anyways.
void gaussian( char *prog_name, char *dst_name ) {
  img *new_img ;
  long row, col ;
  float gaussian[600 * 600], power, A, center_x, center_y, scale ;
  
  new_img = create_img( prog_name, 600, 600, 1 ) ;
  
  // There is no exact center in the image, so I just used (300, 300) as the center
  center_x = center_y = 300 ; 
  
  // I set the scale in the code out of laziness. It could easily be changed to be set by user input
  scale = 100.0 ;
  
  // Given 8-bit image, A = 255
  A = 255.0 ;
  
  // Since there is only one color, we don't need the third for loop to iterate through the colors
  for( row = 0 ; row < 600 ; row++ ) {
	for( col = 0 ; col < 600 ; col++ ) {
	  // f( x, y ) = A * e^[-(( x - x_0 )^2 + ( y - y_0 )^2)/( 2 * scale^2 )]
	  power = -( pow( ((float) row)  - center_x, 2.0 ) + pow( ((float) col) - center_y, 2.0 )) / ( 2.0 * pow( scale, 2.0 )) ;
      gaussian[row * 600 + col] = A * exp( power ) ; 
	  new_img->image[row * 600 + col] = (int) gaussian[row * 600 + col] ;
	}
  }

  write_img( prog_name, new_img, dst_name ) ;
  printf( "\nAn image with gaussian intensity has been generated and stored in %s\n\n", dst_name ) ;
}


// Median filter
void mf( char *prog_name, char *src_name, img *src_img, char *dst_name ) {
  img *new_img ;
  long color, row, col ;
  int A[9], i, j, temp ;
  
  new_img = copy_img( prog_name, src_img ) ;
  
  for( color = 0 ; color < src_img->colors ; color++ ) {
    for( row = 0 ; row < src_img->rows ; row++ ) {
	  for( col = 0 ; col < src_img->cols ; col++ ) {
	    // Find median of 3x3 neighborhood. Sort then take A[4]
		// Ignore boundary pixels
		if( row-1 > 0 && col-1 > 0 && row+1 < src_img->rows && col+1 < src_img->cols ) {
		  A[0] = src_img->image[color * src_img->rows * src_img->cols + (row-1) * src_img->cols + (col-1)] ;
		  A[1] = src_img->image[color * src_img->rows * src_img->cols + (row-1) * src_img->cols + (col)] ;
		  A[2] = src_img->image[color * src_img->rows * src_img->cols + (row-1) * src_img->cols + (col+1)] ;
		  A[3] = src_img->image[color * src_img->rows * src_img->cols + (row)   * src_img->cols + (col-1)] ;
		  A[4] = src_img->image[color * src_img->rows * src_img->cols + (row)   * src_img->cols + (col)] ;
		  A[5] = src_img->image[color * src_img->rows * src_img->cols + (row)   * src_img->cols + (col+1)] ;
		  A[6] = src_img->image[color * src_img->rows * src_img->cols + (row+1) * src_img->cols + (col-1)] ;
		  A[7] = src_img->image[color * src_img->rows * src_img->cols + (row+1) * src_img->cols + (col)] ;
		  A[8] = src_img->image[color * src_img->rows * src_img->cols + (row+1) * src_img->cols + (col+1)] ;
		  
		  // Bubblesort from "Introduction to Algorithms" Cormen.
		  // Since we aren't concerned about performance I used bubblesort as it's easy to read/code
		  for( i = 0 ; i < 9 ; i++ ) {
			for( j = 9 ; j > i ; j-- ) {
			  if( A[j] < A[j - 1] ) {
			    temp = A[j] ;
				A[j] = A[j - 1] ;
				A[j - 1] = temp ;
			  }
			}
		  }
		
		  new_img->image[color * src_img->rows * src_img->cols + row * src_img->cols + col] = A[4] ;
		}
	  }
	}
  }  
  
  write_img( prog_name, new_img, dst_name ) ;
  printf( "\n%s has been processed through a median filter and stored in %s\n\n", src_name, dst_name ) ;
}
