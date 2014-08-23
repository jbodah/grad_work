// Super-resolution implementation
// Last update: 12/4/2011
// Joshua Bodah

#include <stdio.h>
#include "img.h"
#include "cimg.h"
#include <math.h>
#include <stdlib.h>

#define PI     3.1415926536

/* FUNCTION PROTOTYPES */

//double plug_into_map_estimator;
void load_lr_frames( dimg **y, int size ) ;

void initialize_hr_img( dimg *z, int sr_ratio, dimg *lr_frame ) ;

void write_dimg( char *prog_name, dimg *src_dimg, char *dst_name ) {
	write_img( prog_name, dimg2img( prog_name, src_dimg ), dst_name ) ;
}

void resize( dimg *src_dimg, dimg *dst_dimg, float resize_factor ) ;


/* MAIN */

void main() {
	int i, j, n ; 					// iteration counter
	long avg ;
	dimg *z ;   					  // estimate of HR image
	dimg *y[14] ; 					// LR frames
	double weight = 1/9 ;   // weight of HR pixel in LR pixel

	// Load LR frames into y
	load_lr_frames( y, 9 ) ;
	
	z = create_dimg( "main", 3 * y[0]->cols, 3 * y[0]->rows ) ;
	dimg *f = create_dimg( "main", 3 * y[0]->cols, 3 * y[0]->rows ) ;
	
	n = 0 ;
	
	for( i = 0 ; i < z->rows ; i++ ) {
	  for( j = 0 ; j < z->cols ; j++ ) { 
		  n = (n+1)%9 ;
		  z->image[i*z->cols + j] = y[n]->image[(i/3)*y[n]->cols + (j/3)] ; ;
		}
	}
	
  for( i = 0 ; i < f->size - 2 ; i++ ) {
		f->image[i] = (z->image[i] + z->image[i+1] + z->image[i+2])/3 ;
	}
	
	write_dimg( "z", f, "test.img" ) ;
	
	return;
}



// Size unnecessary since I hard-coded names
void load_lr_frames( dimg **y, int size ) {
  
	int i ;
	
	printf( "\nLoading low-res frames...\n" ) ;
	
	y[0] = img2dimg( "load_lr_frames", read_img( "load_lr_frames", "31.img" )) ;
	y[1] = img2dimg( "load_lr_frames", read_img( "load_lr_frames", "32.img" )) ;
	y[2] = img2dimg( "load_lr_frames", read_img( "load_lr_frames", "33.img" )) ;
	y[3] = img2dimg( "load_lr_frames", read_img( "load_lr_frames", "34.img" )) ;
	y[4] = img2dimg( "load_lr_frames", read_img( "load_lr_frames", "35.img" )) ;
	y[5] = img2dimg( "load_lr_frames", read_img( "load_lr_frames", "36.img" )) ;
	y[6] = img2dimg( "load_lr_frames", read_img( "load_lr_frames", "37.img" )) ;
	y[7] = img2dimg( "load_lr_frames", read_img( "load_lr_frames", "38.img" )) ;
	y[8] = img2dimg( "load_lr_frames", read_img( "load_lr_frames", "39.img" )) ;
	y[9] = img2dimg( "load_lr_frames", read_img( "load_lr_frames", "40.img" )) ;
	y[10] = img2dimg( "load_lr_frames", read_img( "load_lr_frames", "41.img" )) ;
	y[11] = img2dimg( "load_lr_frames", read_img( "load_lr_frames", "42.img" )) ;
	y[12] = img2dimg( "load_lr_frames", read_img( "load_lr_frames", "43.img" )) ;
	y[13] = img2dimg( "load_lr_frames", read_img( "load_lr_frames", "44.img" )) ;
	
	printf( "\nLow-res frames loaded\n" ) ;
}

