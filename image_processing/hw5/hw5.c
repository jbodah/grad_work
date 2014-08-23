/***************************************************/
/* Programmer: Joshua Bodah                        */
/*                                                 */
/* CS 545 HW5                                      */
/***************************************************/


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "img.h"
#include "cimg.h"
#include "dft.h"

void pad( cimg *csrc_img, cimg *new_csrc_img ) ;
void ilpf( cimg *csrc_img, float cutoff ) ;
float dist( img *src_img, long u, long v ) ;
void chop( img *padded_src_img, char *dst_name ) ;
void g_noisify( cimg *csrc_img, double std_dev, double mean ) ;

// argv[1] = source name; argv[2] = output name; argv[3] = dft name; argv[4] = idft name
int main( int argc, char *argv[] ) {

  float cutoff ;

  // Input valdiation
  if( argc != 5 ) {
    printf( "\nError: expecting four arguments ( source, output, dft, idft )\n\n" ) ;
	return 0 ;
  }
  
  // I was having troubles passing this from the command line, so I just ask for user input
  printf( "\ncutoff = ? " ) ;
  scanf( "%f", &cutoff ) ;
  
  // We assume source image is greyscale
  cimg *csrc_img = img2cimg( argv[0], read_img( argv[0], argv[1] )) ;
  
  // Add Gaussian white noise to image
  // I just comment this out for part 1 of the homework
  g_noisify( csrc_img, 50.0, 50.0 ) ;
  
  // Pad input image with zeros
  // I didn't want to deal with memory allocation, so I just store the padded image here
  cimg *padded_csrc_img = create_cimg ( argv[0], csrc_img->cols * 2, csrc_img->rows * 2 ) ;
  pad( csrc_img, padded_csrc_img ) ;
  
  // Compute DFT and write to argv[3]
  dft( padded_csrc_img, argv[3] ) ;
  
  // Apply Ideal Low Pass Filter
  ilpf( padded_csrc_img, cutoff ) ;

  // Compute IDFT and write to argv[4]
  idft( padded_csrc_img, argv[4] ) ;
  
  // Read in padded IDFT and chop for output
  chop( read_img( argv[0], argv[4] ), argv[2] ) ;
  
  return 0 ;
}


// Add Gaussian white noise to image
// Partially based off of (http://www.dspguide.com/ch2/6.htm)
void g_noisify( cimg *csrc_img, double std_dev, double mean ) {

  double random_sum ;
  long i ;
  
  // Add scaled noise
  for( i = 0 ; i < csrc_img->size ; i++ ) {
    // Sum 3 random numbers between 0 and 1 & make zero-mean
    random_sum = ( rand() + rand() + rand() ) / (double)( RAND_MAX ) - 1.5 ;
    csrc_img->image[i].r += mean + std_dev * random_sum ;
  }
  
  write_img( "noise", dimg2img( "noise", re_part( "noise", csrc_img )), "noise_test.img" );
  printf( "\nNoise added\n\n" ) ;
}


// Pad input image with zeros
void pad( cimg *csrc_img, cimg *padded_csrc_img ) {

  long x, y ;
  
  // Keep source image in top left portion of padded image
  for( y = 0 ; y < csrc_img->rows ; y++ ) {
    for( x = 0 ; x < csrc_img->cols ; x++ ) {
	  padded_csrc_img->image[y * padded_csrc_img->cols + x].r = csrc_img->image[y * csrc_img->cols + x].r ;
	  padded_csrc_img->image[y * padded_csrc_img->cols + x].i = csrc_img->image[y * csrc_img->cols + x].i ;
	}
  }
  
  // Pad the rest of it with zeros
  for( y = csrc_img->rows ; y < padded_csrc_img->rows ; y++ ) {
    for( x = csrc_img->cols ; x < padded_csrc_img->cols ; x++ ) {
	  padded_csrc_img->image[y * padded_csrc_img->cols + x].r = 0 ;
	  padded_csrc_img->image[y * padded_csrc_img->cols + x].i = 0 ;
	}
  }
   printf( "\nImage padded\n\n" ) ;
}


// Ideal Low Pass Filter
void ilpf( cimg *csrc_img, float cutoff ) {

  img *H ; // H stores filter values
  long u, v ;
  
  H = create_img ( "ilpf", csrc_img->cols, csrc_img->rows, 1 ) ;
  
  // Initialize filter values based on cutoff
  for( v = 0 ; v < csrc_img->rows ; v++ ) {
    for( u = 0 ; u < csrc_img->cols ; u++ ) {
	  if( dist( H, u, v ) <= cutoff ) H->image[u * H->cols + v] = 1 ;
	  else H->image[u * H->cols + v] = 0 ;
	}
  }
  
  // Apply filter by array multiplication
  for( v = 0 ; v < csrc_img->rows ; v++ ) {
    for( u = 0 ; u < csrc_img->cols ; u++ ) {
	  csrc_img->image[u * csrc_img->cols + v].r *= H->image[u * H->cols + v] ;
	  csrc_img->image[u * csrc_img->cols + v].i *= H->image[u * H->cols + v] ;
	}
  }
  printf( "\nILPF applied successfully\n\n" ) ;
}


// D(u,v) = [(u - P/2)^2 + (v - Q/2)^2]^(1/2)
float dist( img *src_img, long u, long v ) {

  float temp = ( u - (float)src_img->cols / 2 ) * ( u - (float)src_img->cols / 2 ) + ( v - (float)src_img->rows / 2 ) * ( v - (float)src_img->rows / 2 ) ;

  return (float)sqrt( temp ) ;
}


// Unpad the image and write to disk
void chop( img *padded_src_img, char *dst_name ) {

  img *filtered_img = create_img( "chop", padded_src_img->cols / 2 , padded_src_img->rows / 2, 1 ) ; 
  long x, y ;
  
  // Copy real part from padded image into original image
  for( y = 0 ; y < filtered_img->rows ; y++ ) {
    for( x = 0 ; x < filtered_img->cols ; x++ )
	  filtered_img->image[y * filtered_img->cols + x] = padded_src_img->image[y * padded_src_img->cols + x] ;
  }
  
  // Write image for testing purposes
  write_img( "chop", filtered_img, dst_name );
  printf( "\nFiltered image successfully chopped and stored in %s\n\n", dst_name ) ;
}
