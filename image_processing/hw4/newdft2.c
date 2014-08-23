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
void dft_both( img *, char *, int ) ;

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
  dft_both( src_img, dst_name, 1 ) ;
  printf( "\nDFT successfully computed and stored in %s\n\n", dst_name ) ;
}

void idft( img *src_img, char *dst_name ) {
  dft_both( src_img, dst_name, -1 ) ;
  printf( "\nIDFT successfully computed and stored in %s\n\n", dst_name ) ;
}

// dft_type = 1 for DFT, dft_type = -1 for IDFT
void dft_both( img *src_img, char *dst_name, int dft_type ) {
  long x, y, u, v, i, M, N ;
  double sum_r, sum_i ;
  cimg *cdft_img, *cintermediate_img ;
  dimg *ddft_img, *dph_img, *dmg_img ;
  img *dst_img ;
  
  // Initialize M and N to match book
  M = src_img->cols ;
  N = src_img->rows ;
  
  // Initialize
  cdft_img = create_cimg ( "dft", M, N ) ;
  cintermediate_img = create_cimg ( "dft", M, N ) ; 
 
  if( dft_type == 1 ) {
    // Premultiply by ( -1 )^( x + y ) to center
    for( x = 0 ; x < M ; x++ ) {
	  for( y = 0 ; y < N ; y++ ) src_img->image[y * M + x] *= pow( -1, x + y ) ;
	}
  }
   
  // Compute DFT/IDFT  
  // Compute cintermediate_img = F(x,v)
  for( v = 0 ; v < N ; v++ ) {
    for( x = 0 ; x < M ; x++ ) {
	  sum_r = 0 ;
	  sum_i = 0 ;
	  for( y = 0 ; y < N ; y++ ) {
	    sum_r += src_img->image[y * M + x] * cos( dft_type * -2 * PI * v * y / (double)N ) ;
		sum_i += src_img->image[y * M + x] * sin( dft_type * -2 * PI * v * y / (double)N ) ;
	  }
	  cintermediate_img->image[v * M + x].r = sum_r ;
	  cintermediate_img->image[v * M + x].i = sum_i ;
	}
  }
	
  // Compute cintermediate_img = F(u,v)
  for( u = 0 ; u < M ; u++ ) {
    for( v = 0 ; v < N ; v++ ) {
	  sum_r = 0 ;
	  sum_i = 0 ;
	  for( x = 0 ; x < M ; x++ ) {
	  	sum_r += cintermediate_img->image[v * M + u].r * cos( dft_type * -2 * PI * u * x / (double)M ) ;
		sum_i += cintermediate_img->image[v * M + u].i * sin( dft_type * -2 * PI * u * x / (double)M ) ;
	  }
	  cdft_img->image[v * M + u].r = sum_r ;
	  cdft_img->image[v * M + u].i = sum_i ;
	}
  }
  
  if( dft_type == -1 ) {
    // 1/MN constant
    for( u = 0 ; u < M ; u++ ) {
      for( v = 0 ; v < N ; v++ ) {
	  	cdft_img->image[v * M + u].r /= M * N ;
	    cdft_img->image[v * M + u].i /= M * N ;
	  }
	}
  }
  
  if( dft_type == 1 ) { 
    // Calculate Fourier spectrum and phase angle of DFT
    dph_img = ph_part( "dft", cdft_img ) ;
    dmg_img = mg_part( "dft", cdft_img ) ;  
 
    // Initialize 
    ddft_img = create_dimg ( "dft", M, N ) ;
 
    // Restate DFT as product of Fourier spectrum and phase angle. Save in ddft_img
    for( i = 0 ; i < M * N ; i++ )
      ddft_img->image[i] = dph_img->image[i] * dmg_img->image[i] ;
  }
  
  else ddft_img = re_part( "dft", cdft_img ) ;
	
  // Scale this result and save it as an img with name = dst_name
  write_img( "dft", dimg2img_scale( "dft", ddft_img ), dst_name ) ;  
  
  return ;
}

