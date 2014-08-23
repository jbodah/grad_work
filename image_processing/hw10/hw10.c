/***************************************************/
/* Programmer: Joshua Bodah                        */
/*                                                 */
/* CS 545 HW10                                     */
/***************************************************/

// Assumptions: binary image, hard-coded kernel, bounds ignored (skip applying kernel here)

#include <stdio.h>
#include <stdlib.h>
#include "img.h"

#define CAP(a)               ((a<0) ? 0 : ((a>255) ? 255 : a)) 
#define DIFF(a,b)            (ABS(a - b))

// Inclusive between
#define BETWEEN(a,b,c)			 ((((a) >= (b)) && ((a) <= (c))) ? 1 : 0)

#define COLOR_SWAP(a)				 (a = ((a == IMG_WHITE) ? IMG_BLACK : IMG_WHITE))

typedef struct {
	int x ;
	int y ;
} coord_pair ;

typedef struct {
	coord_pair *coord ;
	int 				size ;
} kernel ;

void initialize_kernel( kernel *k ) ;

void erode_img( img *src_img, kernel *k ) ;
void dilate_img( img *src_img, kernel *k ) ;
void open_img( img *src_img, kernel *k ) ;
void close_img( img *src_img, kernel *k ) ;

void do_operation( img *src_img, img *dst_img, kernel *k, int code ) ;
void apply_operation( img *src_img, img *dst_img, kernel *k, int pixel_x, int pixel_y, int code ) ;

int	 get_pixel( img *src_img, int pixel_x, int pixel_y ) ;
void set_pixel( img *src_img, int pixel_x, int pixel_y, int new_value ) ;


// argv[1] = src_path
int main( int argc, char *argv[] ) {
  img *src_img = read_img( "hw10", argv[1] ) ;
	kernel *k ;
  int i ;
	
	k = malloc( sizeof( kernel )) ;
	
	k->size = 5 ;
	
	initialize_kernel( k ) ;
			
	erode_img( src_img, k ) ;
	dilate_img( src_img, k ) ;
	open_img( src_img, k ) ; 
	close_img( src_img, k ) ;
	
	return 0 ;
}



// Hard-coded initialization of kernel
void initialize_kernel( kernel *k ) {
	k->coord = malloc( k->size * sizeof( coord_pair )) ;

	k->coord[0].x = 1 ;
	k->coord[0].y = 0 ;
	k->coord[1].x = 0 ;
	k->coord[1].y = 0 ;
	k->coord[2].x = -1 ;
	k->coord[2].y = 0 ;
	k->coord[3].x = 0 ;
	k->coord[3].y = -1 ;
	k->coord[4].x = 0 ;
	k->coord[4].y = 1 ;
}


// Erode src_img and output "erode.img"
void erode_img( img *src_img, kernel *k ) {
	int i, j ;

	img *new_img = copy_img( "erode", src_img ) ;
	do_operation( src_img, new_img, k, 0 ) ;
	write_img( "erode", new_img, "erode.img" ) ;
}



// Dilate src_img and output "dilate.img"
void dilate_img( img *src_img, kernel *k ) {
	int i, j ;

	img *new_img = copy_img( "dilate", src_img ) ;
	do_operation( src_img, new_img, k, 1 ) ;
	write_img( "dilate", new_img, "dilate.img" ) ;
}


// Open src_img and output "open.img"
void open_img( img *src_img, kernel *k ) {
	int i, j ;

	img *new_img = copy_img( "open", src_img ) ;
	img *new2_img = copy_img( "open", src_img ) ;
	do_operation( src_img, new_img, k, 0 ) ;
	do_operation( new_img, new2_img, k, 1 ) ;
	write_img( "open", new2_img, "open.img" ) ;
}


// Close src_img and output "close.img"
void close_img( img *src_img, kernel *k ) {
	int i, j ;

	img *new_img = copy_img( "close", src_img ) ;
	img *new2_img = copy_img( "close", src_img ) ;
	do_operation( src_img, new_img, k, 1 ) ;
	do_operation( new_img, new2_img, k, 0 ) ;
	write_img( "close", new2_img, "close.img" ) ;
}



int bound_exceeded( img *src_img, kernel *k, int pixel_x, int pixel_y ) {
  int i ;

  for( i = 0 ; i < k->size ; i++ ) {
		if( !BETWEEN( pixel_x + k->coord[i].x, 0, src_img->cols - 1 ) ||
				!BETWEEN( pixel_y + k->coord[i].y, 0, src_img->rows - 1 ))
			return 1 ;
	}
	return 0 ;
}



void do_operation( img *src_img, img *dst_img, kernel *k, int code ) {
	int i, j ;
	
	for( j = 0 ; j < dst_img->rows ; j++ ) {
	  for( i = 0 ; i < dst_img->cols ; i++ ) {
     // Ignore pixel if applying kernel exceeds bounds
		  if( bound_exceeded( dst_img, k, i, j )) continue ;
		  else apply_operation( src_img, dst_img, k, i, j, code ) ;
		}
	}
}



void apply_operation( img *src_img, img *dst_img, kernel *k, int pixel_x, int pixel_y, int code ) {
  int i, color ;
	
	color = (( code == 0 ) ? IMG_WHITE : IMG_BLACK ); 
	
	for( i = 0 ; i < k->size ; i++ ) {
		if( get_pixel( src_img, pixel_x + k->coord[i].x, pixel_y + k->coord[i].y ) != color ) {
			COLOR_SWAP(color) ;
			break ;
		}
	}
	set_pixel( dst_img, pixel_x, pixel_y, color ) ;
}



int get_pixel( img *src_img, int pixel_x, int pixel_y ) {
	return src_img->image[pixel_y * src_img->cols + pixel_x] ;
}



void set_pixel( img *src_img, int pixel_x, int pixel_y, int new_value ) {
  src_img->image[pixel_y * src_img->cols + pixel_x] = new_value ;
}