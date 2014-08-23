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

void dft( cimg *, char * ) ;
void idft( cimg *, char * ) ;
void dft_both( cimg *, char *, int ) ;

// argv[1] = source name; argv[2] = destination name; argv[3] = reality check name
int main( int argc, char *argv[] ) {

  // Input valdiation
  if( argc != 4 ) {
    printf( "\nError: expecting three file name arguments ( src_name, dst_name, rl_name )\n\n" ) ;
	return 0 ;
  }
  
  cimg *csrc_img = img2cimg( "dft", read_img( argv[0], argv[1] )) ;
  
  // Read src_name and compute dft. Store result in dst_name
  dft( csrc_img, argv[2] ) ;
  
  // Read dst_name (dft of src_name) and compute idft. Store result in rl_name
  idft( csrc_img, argv[3] ) ;
  
  return 0 ;
}


void dft( cimg *csrc_img, char *dst_name ) {
  dft_both( csrc_img, dst_name, 1 ) ;
  printf( "\nDFT successfully computed and stored in %s\n\n", dst_name ) ;
}


void idft( cimg *csrc_img, char *dst_name ) {
  dft_both( csrc_img, dst_name, -1 ) ;
  printf( "\nIDFT successfully computed and stored in %s\n\n", dst_name ) ;
}


// dft_type = 1 for DFT, dft_type = -1 for IDFT
void dft_both( cimg *csrc_img, char *dst_name, int dft_type ) {
  long x, y, u, v, i, M, N ;
  double factor, cos_factor, sin_factor ;
  cimg *cdft_img ;
  dimg *ddft_img, *dph_img, *dmg_img ;
  img *dst_img ;
  
  // Initialize M and N to match book
  M = csrc_img->cols ;
  N = csrc_img->rows ;
  
  // Initialize
  cdft_img = create_cimg ( "dft", M, N ) ;
  
  if( dft_type == 1 ) {
    // Premultiply by ( -1 )^( x + y ) to center
   	for( x = 0 ; x < M ; x++ ) {
	  for( y = 0 ; y < N ; y++ ) 		  
		csrc_img->image[y * M + x].r *= pow( -1, x + y ) ;
	}
  }

  // Compute DFT/IDFT
  for( u = 0 ; u < M ; u++ ) {
    for( v = 0 ; v < N ; v++ ) {
	  // Initialize F(u,v)
	  cdft_img->image[v * M + u].r = cdft_img->image[v * M + u].i = 0 ;
	  for( x = 0 ; x < M ; x++ ) {
	    for( y = 0 ; y < N ; y++ ) {
		  factor = dft_type * -2 * PI * ((u * x * N + v * y * M) / ((double)M * N ));
		  cos_factor = cos( factor ) ;
		  sin_factor = sin( factor ) ;
		  cdft_img->image[v * M + u].r += cos_factor * csrc_img->image[y * M + x].r -
     		  sin_factor * csrc_img->image[y * M + x].i ;
		  cdft_img->image[v * M + u].i += cos_factor * csrc_img->image[y * M + x].i +
     		  sin_factor * csrc_img->image[y * M + x].r ;
	    }
	  }
	  if( dft_type == -1 ) {
	  	cdft_img->image[v * M + u].r /= M * N ;
	    cdft_img->image[v * M + u].i /= M * N ;
	  }
	}
  }

  if( dft_type == 1 ) {
    // Store cdft_img for IDFT. Overwrites main::csrc_img
    for( u = 0 ; u < M ; u++ ) {
      for( v = 0 ; v < N ; v++ ) {
	    csrc_img->image[v * M + u].r = cdft_img->image[v * M + u].r ;
	    csrc_img->image[v * M + u].i = cdft_img->image[v * M + u].i ;
	  }
	}
	
    // Calculate Fourier spectrum and phase angle of DFT
    dph_img = ph_part( "dft", cdft_img ) ;
    dmg_img = mg_part( "dft", cdft_img ) ;  
 
    // Initialize
    ddft_img = create_dimg ( "dft", M, N ) ;
 
    // Restate DFT as product of Fourier spectrum and phase angle. Save in ddft_img
    for( i = 0 ; i < ddft_img->size ; i++ )
      ddft_img->image[i] = dph_img->image[i] * dmg_img->image[i] ;
  }
  
  else {
    for( x = 0 ; x < M ; x++ ) {
	  for( y = 0 ; y < N ; y++ ) 		  
		cdft_img->image[y * M + x].r *= pow( -1, x + y ) ;
	}
    ddft_img = re_part( "dft", cdft_img ) ;  // Take real part  
  }
  
  // Scale this result and save it as an img with name = dst_name
  write_img( "dft", dimg2img_scale( "dft", ddft_img ), dst_name ) ;
  
  return ;
}

