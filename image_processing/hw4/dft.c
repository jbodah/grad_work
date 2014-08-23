/***************************************************/
/* Programmer: Joshua Bodah                        */
/*                                                 */
/* CS 545 HW4                                      */
/***************************************************/

#include <stdio.h>
#include <math.h>
#include "img.h"
#include "cimg.h"

#define PI 3.14159265

void dft( img *, char * ) ;
void idft( img *, char * ) ;

// argv[1] = source name; argv[2] = destination name; argv[3] = reality check name
int main( int argc, char *argv[] ) {

  // Input valdiation
  if( argc != 4 ) {
    printf( "\nError: expecting three file name arguments ( src_name, dst_name, rl_name )\n\n" ) ;
	return 0 ;
  }
  
  // Read src_name and compute dft. Store result in dst_name
  dft( read_img( argv[0], argv[1] ), argv[2] ) ;
  
  // Read dst_name (dft of src_name) and compute idft. Store result in rl_name
  idft( read_img( argv[0], argv[2] ), argv[3] ) ;
  
  return 0 ;
}

void dft( img *src_img, char *dst_name ) {
  // x iterates src_img->cols
  // y iterates src_img->rows
  // u iterates cdft_img->cols
  // v iterates cdft_img->rows
  // i is a general iterator variable
  // pre holds a constant -1 or 1
  // cdft_img holds the complex version of the DFT
  // ddft_img holds the double version of the DFT
  // dph_img holds the phase angle calculated from cdft_img
  // dmg_img holds the magnitude calculated from cdft_img
  // dst_img holds the final image to write
  long x, y, u, v, i ;
  int pre ;
  cimg *cdft_img ;
  dimg *ddft_img, *dph_img, *dmg_img ;
  img *dst_img ;
  
  // Initialize
  cdft_img = create_cimg ( "dft", src_img->cols, src_img->rows ) ;
  
  // Pre-multiply by ( -1 )^( x + y ) to center DFT
  // I was having trouble with pow function, so I used this work around
  // This assumes an even number of rows and an even number columns in image
  pre = 1 ;
  for( x = 0 ; x < src_img->cols ; x++ ) {
    for( y = 0 ; y < src_img->rows ; y++ ) {
	  src_img->image[y * src_img->cols + x] *= pre ;
	  pre *= -1 ;
	}
  }
  
  // Compute DFT
  // Iterate through each pixel of cdft_img
  for( u = 0 ; u < cdft_img->cols ; u++ ) {
    for( v = 0 ; v < cdft_img->rows ; v++ ) {
	  // Initialize sum to 0
	  cdft_img->image[v * cdft_img->cols + u].r = cdft_img->image[v * cdft_img->cols + u].i = 0 ;
	  // Compute DFT
      for( x = 0 ; x < src_img->cols ; x++ ) {
	    for( y = 0 ; y < src_img->rows ; y++ ) {
		  cdft_img->image[v * cdft_img->cols + u].r += cos( 2 * PI * (u * x / (double)cdft_img->cols + v * y / (double)cdft_img->rows )) * src_img->image[y * src_img->cols + x] ;
		  cdft_img->image[v * cdft_img->cols + u].i += sin( 2 * PI * (u * x / (double)cdft_img->cols + v * y / (double)cdft_img->rows )) * - src_img->image[y * src_img->cols + x] ;
	    }
	  }
	}
  }
      
  // Calculate Fourier spectrum and phase angle of DFT
  dph_img = ph_part( "dft", cdft_img ) ;
  dmg_img = mg_part( "dft", cdft_img ) ;  
 
  // Initialize
  ddft_img = img2dimg( "dft", src_img ) ;
 
  // Restate DFT as product of Fourier spectrum and phase angle. Save in ddft_img
  for( i = 0 ; i < ddft_img->size ; i++ )
    ddft_img->image[i] = dph_img->image[i] * dmg_img->image[i] ;
	
  // Scale this result and save it as an img with name = dst_name
  write_img( "dft", dimg2img_scale( "dft", ddft_img ), dst_name ) ;
  
  printf( "\nDFT successfully computed and stored in %s\n\n", dst_name ) ;
  
  return ;
}

void idft( img *src_img, char *dst_name ) {
  // x iterates src_img->cols
  // y iterates src_img->rows
  // u iterates cdft_img->cols
  // v iterates cdft_img->rows
  // i is a general iterator variable
  // cidft_img holds the complex version of the IDFT
  long x, y, u, v, i ;
  cimg *cidft_img ;

  // Initialize
  cidft_img = create_cimg ( "dft", src_img->cols, src_img->rows ) ;

  // Compute IDFT
  for( u = 0 ; u < cidft_img->cols ; u++ ) {
    for( v = 0 ; v < cidft_img->rows ; v++ ) {
	  // Initialize IDFT values to 0
	  cidft_img->image[v * cidft_img->cols + u].r = cidft_img->image[v * cidft_img->cols + u].i = 0 ;
      for( x = 0 ; x < src_img->cols ; x++ ) {
	    for( y = 0 ; y < src_img->rows ; y++ ) {
		  cidft_img->image[v * cidft_img->cols + u].r += cos( 2 * PI * (u * x / (double)cidft_img->cols + v * y / (double)cidft_img->rows )) * src_img->image[y * src_img->cols + x] ;
		  cidft_img->image[v * cidft_img->cols + u].i += sin( 2 * PI * (u * x / (double)cidft_img->cols + v * y / (double)cidft_img->rows )) * src_img->image[y * src_img->cols + x] ;
	    }
	  }
	  cidft_img->image[v * cidft_img->cols + u].r /= (double)cidft_img->size ;
	  cidft_img->image[v * cidft_img->cols + u].i /= (double)cidft_img->size ;
	}
  }
  
  // Testing, not sure if this would work on filtered images.
  // Might need a method other than simple conversion to img
  for( i = 0 ; i < cidft_img->size ; i++ ) {
    if( cidft_img->image[v * cidft_img->cols + u].i != 0 )
      printf( "Non-zero imaginary part in IDFT\n" ) ;
  }
  
  // Take only real part returned by IDFT (returns dimg). Scale this and save it as an img with name = dst_name
  write_img( "dft", dimg2img_scale( "dft", re_part( "dft", cidft_img )), dst_name ) ;
  
  printf( "\nIDFT successfully computed and stored in %s\n\n", dst_name ) ;
  
  return ;
}

