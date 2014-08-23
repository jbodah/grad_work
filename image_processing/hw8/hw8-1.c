/***************************************************/
/* Programmer: Joshua Bodah                        */
/*                                                 */
/* CS 545 HW8-1                                    */
/***************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "img.h"

void resize( img *src_img, char *dst_name, float resize_factor ) ;


// argv[1] = img_src_path; argv[2] = img_dst_path; argv[3] = transformation
int main( int argc, char *argv[] ) {

	// Input
	img *src_img = read_img( "hw8", argv[1] ) ;

	// Resize input image by argv[3] and store in argv[2]
	resize( src_img, argv[2], strtof( argv[3], NULL )) ;
	 
  return 0 ;
}


// Nearest Neighbor
void resize( img *src_img, char *dst_name, float resize_factor ) {

	img *new_img ;
	// I choose to get rid of any fractional pixels in new size. 
	// This is accounted for by truncation via type casting
	long col_size = (long)( resize_factor * src_img->cols ) ;
	long row_size = (long)( resize_factor * src_img->rows ) ;
	long i, j, k, nn_j, nn_k ;
		
	// Create new image	
	new_img = create_img( "resize", col_size, row_size, src_img->colors ) ;
	
	// Interpolate
	// Iterate through positions of new_img and copy intensity values
	// from appropriate src_img pixels
	for( i = 0 ; i < new_img->colors ; i++ ) {
	  for( j = 0 ; j < new_img->rows ; j++ ) {
			// Find the nearest neighbor in src_img
			nn_j = (long)( j / resize_factor ) ;
			
			// Account for truncation errors
			if( j / resize_factor - nn_j >= 0.5 )
				nn_j++ ;
		  for( k = 0 ; k < new_img->cols ; k++ ) {
				// Find the nearest neighbor in src_img
				nn_k = (long)( k / resize_factor ) ;
				
				// Account for truncation errors
				if( k / resize_factor - nn_k >= 0.5 )
					nn_k++ ;
					
				// Copy value from nearest neighbor in src_img into new_img
				new_img->image[i * new_img->rows * new_img->cols + j * new_img->cols + k]
					= src_img->image[i * src_img->rows * src_img->cols + nn_j * src_img->cols + nn_k] ;
			}
		}
	}
	
	// Save resized image
	write_img( "resize", new_img, dst_name ) ;
}