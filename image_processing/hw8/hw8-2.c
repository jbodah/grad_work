/***************************************************/
/* Programmer: Joshua Bodah                        */
/*                                                 */
/* CS 545 HW8-2                                    */
/***************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "img.h"

#define DIST(a,b) (MAX(a,b) - MIN(a,b))

void resize( img *src_img, char *dst_name, float resize_factor ) ;


// argv[1] = img_src_path; argv[2] = img_dst_path; argv[3] = transformation
int main( int argc, char *argv[] ) {

	// Input
	img *src_img = read_img( "hw8", argv[1] ) ;

	// Resize input image by argv[3] and store in argv[2]
	resize( src_img, argv[2], strtof( argv[3], NULL )) ;
	 
  return 0 ;
}


// Bilinear
// Note: I'm getting errors around the edges of my images. I couldn't
// 	track down the source of this error. Aside from that, everything should
//  work just fine.
void resize( img *src_img, char *dst_name, float resize_factor ) {

	img *new_img ;
	// I choose to get rid of any fractional pixels in new size. 
	// This is accounted for by truncation via type casting
	long col_size = (long)( resize_factor * src_img->cols ) ;
	long row_size = (long)( resize_factor * src_img->rows ) ;
	long i, j, k, temp_j, temp_k ;
	float actual_j, actual_k ;
		
	// Create new image	
	new_img = create_img( "resize", col_size, row_size, src_img->colors ) ;
	
	// Interpolate
	// Iterate through positions of new_img and copy intensity values
	// from appropriate src_img pixels
	for( i = 0 ; i < new_img->colors ; i++ ) {
	  for( k = 0 ; k < new_img->rows ; k++ ) {
			actual_k = k / resize_factor ;
		  temp_k = (long)actual_k ;
		  for( j = 0 ; j < new_img->cols ; j++ ) {
				actual_j = j / resize_factor ;
				temp_j = (long)actual_j ;
				
				// Find closest neighbors by finding which quadrant of the source pixel 
				// the interpolated pixel lands in. Sets temp_i and temp_j to the indices of
				// the second quadrant pixel of the 2x2 neighborhood
				if( actual_k < 0.5 + temp_k ) {      			  // Either first or second quadrant of source pixel
				  if( actual_j < 0.5 + temp_j ) {  				  // Second quadrant
						temp_j-- ;
						temp_k-- ;
					}
					else temp_k-- ;												    // First quadrant						
				}
				else {																      // Either third or fourth quadrant
				  if( actual_j < 0.5 + temp_j ) temp_j-- ;  // Third quadrant
					//else 															      // Fourth quadrant
				}
				
				// Fix bounds
				if( temp_j == -1 ) temp_j++ ;
				else if( temp_j > src_img->cols - 1 ) temp_j-- ; 
				if( temp_k == -1 ) temp_k++ ;
				else if( temp_k > src_img->rows - 1 ) temp_k-- ;
							
				// WRT 2x2 neighborhood:
				// 1st quad = temp_j+1, temp_k
				// 2nd quad = temp_j, temp_k
				// 3rd quad = temp_j, temp_k+1
				// 4th quad = temp_j+1, temp_k+1		
				
				// Assign weighted average to new pixel
				// Note 0.5 and 1.5 signify the center of the pixel
			  new_img->image[i * new_img->rows * new_img->cols + k * new_img->cols + j]
					= 
							// Add 1st quad
					    DIST(temp_j + 1.5, actual_j) * DIST(temp_k + 0.5, actual_k)
					    * src_img->image[i * src_img->rows * src_img->cols + temp_k * src_img->cols + (temp_j + 1)] 
							
							// Add 2nd quad
						+ DIST(temp_j + 0.5, actual_j) * DIST(temp_k + 0.5, actual_k)
					    * src_img->image[i * src_img->rows * src_img->cols + temp_k * src_img->cols + temp_j] 
							
							// Add 3rd quad
						+ DIST(temp_j + 0.5, actual_j) * DIST(temp_k + 1.5, actual_k)
					    * src_img->image[i * src_img->rows * src_img->cols + (temp_k + 1) * src_img->cols + temp_j]
							
							// Add 4th quad
						+ DIST(temp_j + 1.5, actual_j) * DIST(temp_k + 1.5, actual_k)
					    * src_img->image[i * src_img->rows * src_img->cols + (temp_k + 1) * src_img->cols + (temp_j + 1)] ;	
			}
		}
	}
	
	// Save resized image
	write_img( "resize", new_img, dst_name ) ;
}