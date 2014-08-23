/***************************************************/
/* Programmer: Joshua Bodah                        */
/*                                                 */
/* CS 545 HW9                                      */
/***************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "img.h"

#define CAP(a)               ((a<0) ? 0 : ((a>255) ? 255 : a)) 
#define DIFF(a,b)            (ABS(a - b))
#define NUMBER_OF_WEB_COLORS 6

unsigned char WEB_COLORS[NUMBER_OF_WEB_COLORS] = {0, 51, 102, 153, 204, 255} ;

void webify( img *, char * ) ;
unsigned char recolor_for_web( unsigned char ) ;

// argv[1] = src_path; argv[2] = dst_path
int main( int argc, char *argv[] ) {

  img *src_img = read_img( "hw9", argv[1] ) ;
	
	webify( src_img, argv[2] ) ;
	
	return 0 ;
}

// Create copy of src_img with web safe colors
void webify( img *src_img, char *dst_name ) {

  long pixel, color, old_pixel, new_pixel, error[3] = {0,0,0} ;
	
	img *dst_img = copy_img( "hw9", src_img ) ;
	
	// With dithering
	for( pixel = 0 ; pixel < dst_img->size / dst_img->colors ; pixel++ ) {
		for( color = 0 ; color < dst_img->colors ; color++ ) {
      old_pixel = CAP( dst_img->image[color * dst_img->rows * dst_img->cols + pixel] + error[color] ) ;
			new_pixel = CAP( recolor_for_web( old_pixel )) ;
			
			error[color] = old_pixel - new_pixel ;
			
			dst_img->image[color * dst_img->rows * dst_img->cols + pixel] = new_pixel ;
    }			
	}
		
	write_img( "hw9", dst_img, dst_name ) ;	
		
	return ;
}

// Round pixel_intensity to nearest web safe color
unsigned char recolor_for_web( unsigned char pixel_intensity ) {

  int smallest_diff = DIFF( pixel_intensity, WEB_COLORS[0] ) ;
  int i ;	
	
	for( i = 1 ; i < NUMBER_OF_WEB_COLORS ; i++ ) {
	  if( smallest_diff < DIFF( pixel_intensity, WEB_COLORS[i] ))
      break ;
    else
		  smallest_diff = DIFF( pixel_intensity, WEB_COLORS[i] ) ; 			
  }
	
  return WEB_COLORS[i-1] ;
}