/***************************************************/
/* Programmer: Joshua Bodah                        */
/*                                                 */
/* CS 545 HW6                                      */
/***************************************************/


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "img.h"
#include "cimg.h"
#include "dft.h"

void g_noisify( cimg *csrc_img, double std_dev ) ;
void wiener( cimg *csrc_img, double deg_func, double noise_power, dimg *source_power ) ;

// argv[1] = source image; argv[2] = control dft; argv[3] = noisy dft; argv[4] = filtered output
int main( int argc, char *argv[] ) {

  // Input valdiation
  if( argc != 5 ) {
    printf( "\nError: expecting arguments ( source, control dft, noisy dft, filtered output )\n\n" ) ;
	return 0 ;
  }
   
  // We assume source image is greyscale
  cimg *csrc_img = img2cimg( argv[0], read_img( argv[0], argv[1] )) ;
  
  // Compute DFT and write to argv[2]
  dft( csrc_img, argv[2] ) ;
  
  // Computer power spectrum of uncorrupted image
  dimg* source_power = mg_part( "hw6", csrc_img ) ;
  write_img( "hw6", dimg2img( "hw6", source_power ), "orig_mg.img" ) ; 

  // Reinitialize csrc_img so we can use it for noisy image
  csrc_img = img2cimg( argv[0], read_img( argv[0], argv[1] )) ;
   
  // Add Gaussian white noise to image
  // Stores noisy image as noise.img
  g_noisify( csrc_img, 10.0 ) ;
  
  // Compute noisy DFT and write to argv[3]
  dft( csrc_img, argv[3] ) ;
  
  // Apply Wiener filter MTF
  wiener( csrc_img, 1.0, 100.0, source_power ) ;
  
  // Compute IDFT and write to argv[3]
  idft( csrc_img, argv[4] ) ;
  
  return 0 ;
}



// Modified Wiener filter. Designed for this problem specifically
void wiener( cimg *csrc_img, double deg_func, double noise_power, dimg *source_power ) {

  long u, v ;
  
  dimg *wiener_img = create_dimg( "hw6", csrc_img->cols, csrc_img->rows ) ;
  
  for( v = 0 ; v < csrc_img->rows ; v++ ) {
    for( u = 0 ; u < csrc_img->cols ; u++ )
      wiener_img->image[v * csrc_img->cols + u] = (1.0/(1.0 + noise_power/source_power->image[v * csrc_img->cols + u])) ;
  }
  
  write_img( "hw6", dimg2img_scale( "hw6", wiener_img ), "filter.img" ) ;
  
  // Multiply DFT by Wiener filter MTF
  // Note: H(u,v) = 1 => H*(u,v) = 1
  for( v = 0 ; v < csrc_img->rows ; v++ ) {
    for( u = 0 ; u < csrc_img->cols ; u++ ) {
	  csrc_img->image[v * csrc_img->cols + u].r *= (1.0/(1.0 + noise_power/source_power->image[v * csrc_img->cols + u])) ;
	  csrc_img->image[v * csrc_img->cols + u].i *= (1.0/(1.0 + noise_power/source_power->image[v * csrc_img->cols + u])) ;
	}
  }
  
  write_img( "hw6", dimg2img( "hw6", re_part( "hw6", csrc_img )), "freq_dom_estimate.img" ) ;
}



// Add Gaussian white noise to image (modified from my last
// submission; this one doesn't let you set mean).
// Partially based off of (http://www.dspguide.com/ch2/6.htm)
void g_noisify( cimg *csrc_img, double std_dev ) {

int a,b,c, i;
float s;
srand(time(NULL));
/*this will seed your Psedo Random number generator with current time which will be different in each execution. If you dont use srand() you will get the same set of random numbers everytime you run you code!!*/
a=rand()%999;
b=rand()%999;
c=rand()%999;
s=a+b+c;
s=s-((998-1)/2);
s=s*sqrt(4/(999*998));
s=s*10;
  for( i = 0 ; i < csrc_img->size ; i++ ) 
    csrc_img->image[i].r += s ;
  
  // Write for testing
  write_img( "noise", dimg2img( "noise", re_part( "noise", csrc_img )), "corrupted.img" );
  printf( "\nNoise added\n\n" ) ;
}
