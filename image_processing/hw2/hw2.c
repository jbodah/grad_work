/***************************************************/
/* Programmer: Joshua Bodah                        */
/*                                                 */
/* CS 545 HW2                                      */
/***************************************************/

// For the sharpening assignment I could not get sharpen.img to give me a correct result.
// If you see where I went wrong, please let me know!

#include <stdio.h>
#include "img.h"
#include <math.h>

#define CAP(a)               ((a<0) ? 0 : ((a>255) ? 255 : a)) 

void hw2_header() ;
img *find_img( char *img_name ) ;
void about_img( img *src_img ) ;
void sharpen( char *prog_name, char *src_name, img *src_img, char *dst_name ) ;
void histogram( char *prog_name, char *src_name, img *src_img, char *dst_name ) ;
void gray_level() ;

int main() {

  img *src_img ;
  char src_name[IMG_FILE_NAME_LENGTH] ;
  char dst_name[IMG_FILE_NAME_LENGTH] ;
  
  hw2_header() ; 						  					  	  // Intro text
  
  printf( "Input file (.img): " ) ;			   	  	  			  // Prompt user for file name
  scanf( "%s", &src_name ) ;          		  	  				  // Read file name
  
  src_img = find_img( src_name ) ; 							 	  // Load image
  about_img( src_img ) ; 				  					      // Display source image details
  sharpen( "hw2", src_name, src_img, "sharpen.img" ) ;        // Sharpen source image
  gray_level() ;                                                  // Problem 3 of HW2
  histogram( "hw2", src_name, src_img, "histo.img" ) ;            // Histogram equalization
  
  return 0 ;
}


// Intro text about problem
void hw2_header() {
  printf( "\nCS 545 HW2 by Joshua Bodah\n--------------------------\n\n" ) ;
  printf( "Problem sections:\n\t1. Write a program to sharpen an image by computing the Laplacian of the image and adding some amount c of that back to the original image\n\t2. Implement the histogram equalization method described in class\n\n" ) ;
}


// Tries to load image
img *find_img( char *img_name ) {

  img *im ;

  printf( "\nLoading %s...\n", img_name ) ; // Loading message

  // Read image
  im = read_img( "hw2", img_name ) ; 	  // read_img handles NULL exceptions 
  printf( "%s loaded\n", img_name ) ; 	  // Image found
  
  return im ;
}  


// Prints details about src_img
void about_img( img *src_img ) {
  printf( "\nImage details:\n\tColumns:\t%ld\n\tRows:\t\t%ld\n\tColors:\t\t%ld\n\tSize:\t\t%ld\n",
			src_img->cols, src_img->rows, src_img->colors, src_img->size );
}


// Sharpens the src_img by use of the Laplacian
void sharpen( char *prog_name, char *src_name, img *src_img, char *dst_name ) {
  img *new_img, *laplacian ;
  long color, row, col, i ;
  int sum, min, max ;
  
  new_img = copy_img( prog_name, src_img ) ;
  laplacian = copy_img( prog_name, src_img ) ;
  
  min = 256 ;
  
  /****************************************************************/
  // Calculate the Laplacian
  /****************************************************************/
  // I decided to use the book's version of the Laplacian
  for( color = 0 ; color < src_img->colors ; color++ ) {
    for( row = 0 ; row < src_img->rows ; row++ ) {
	  for( col = 0 ; col < src_img->cols ; col++ ) {	    			
		// If all 4-neighbors exist
		if( row-1 >= 0 && row+1 < src_img->rows && col-1 >= 0 && col+1 < src_img->cols ) {
		  sum = src_img->image[color * src_img->rows * src_img->cols + (row-1) * src_img->cols + col] ;  // f(x-1,y)
		      - src_img->image[color * src_img->rows * src_img->cols + (row+1) * src_img->cols + col] ;  // f(x+1,y)
		      - src_img->image[color * src_img->rows * src_img->cols + row * src_img->cols + (col-1)] ;  // f(x,y-1)
		      - src_img->image[color * src_img->rows * src_img->cols + row * src_img->cols + (col+1)] ;  // f(x,y+1)
	  	      + 4 * src_img->image[color * src_img->rows * src_img->cols + row * src_img->cols + col]  ;  // -4f(x,y)
		}
		
		// Else ignore point, don't sharpen
		else sum = 0 ;
		
		laplacian->image[color * src_img->rows * src_img->cols + row * src_img->cols + col] = sum ; // Store Laplacian of f(x,y) in L(x,y)

		if( sum < min ) min = sum ; // min used below to scale
	  }
	}
  }
  
  /****************************************************************/
  // Scale Laplacian
  /****************************************************************/
  /*
  // Find f_m
  for( i = 0 ; i < src_img->size ; i++ ) {
    laplacian->image[i] = (laplacian->image[i] - min) ;      // f_m
  }
  
  // Find max(f_m)
  max = 0 ;
  for( i = 0 ; i < src_img->size ; i++ ) {
    if( laplacian->image[i] > max ) max = laplacian->image[i] ;
  }
  
  // f_s = K[f_m/max(f_m)]
  for( i = 0 ; i < src_img->size ; i++ ) {
    laplacian->image[i] = 255 * laplacian->image[i] / max ;  // f_s
  }
  */
  write_img( prog_name, laplacian, "lp.img" ) ;   // For testing purposes
  
  /****************************************************************/
  // Calculate the new_img = src_img + c * laplacian
  /****************************************************************/
  // ( The mask in the instructions confused me as c = 4 didn't provide the Laplacian mask described in the text,
  //   so I added c of the Laplacian back to the original image )
  for( i = 0 ; i < new_img->size ; i++ ) {
	new_img->image[i] = src_img->image[i] + (1) * laplacian->image[i];  // g(x,y) = f(x,y) + c * L(x,y)  [c = -1]
  }	
  
	for( i = 0 ; i < new_img->size ; i++ ) {
	  new_img->image[i] = CAP( new_img->image[i] ) ;  
	}
	
  write_img( prog_name, new_img, dst_name ) ;
  printf( "\n%s has been sharpened and stored in %s\n\n", src_name, dst_name ) ;
}																			


// Assumes every gray level is rounded down
// Yields 192 gray levels
void gray_level() {
  int A[256], s, r, count = 0 ;

  for( r = 0 ; r < 256 ; r++ ) {
    A[r] = 0 ;
  }
	
  for( r = 0 ; r < 256 ; r++ ) {
    s = 16 * sqrt(r) ;
	A[s]++ ;
  }
  
  for( r = 0 ; r < 256 ; r++ ) {
    if( A[r] != 0 ) count++ ;
  }
	
  printf( "\n# of intensity values = %d\n", count ) ;
}


// Performs histogram equalization on src_img   
void histogram( char *prog_name, char *src_name, img *src_img, char *dst_name ) {
  img *new_img ;
  long color, row, col ;
  int  A[256], i, value ;
  
  new_img = copy_img( prog_name, src_img ) ;

  for( i = 0 ; i < 256 ; i++ ) {
    A[i] = 0 ;
  }
  
  // A[i] holds number of pixels with intensity i
  for( color = 0 ; color < src_img->colors ; color++ ) {
    for( row = 0 ; row < src_img->rows ; row++ ) {
	  for( col = 0 ; col < src_img->cols ; col++ ) {	
	    value = src_img->image[color * src_img->rows * src_img->cols + row * src_img->cols + col] ;
		A[value]++ ;
	  }
	}
  }

  // A[i] holds number of pixels with intensity <= i
  for( i = 1 ; i < 256 ; i++ ) {
	A[i] += A[i-1] ;
  }

  // Calculate new intensities and store values in new_img
  for( i = 0 ; i < src_img->size ; i++ ) {
	value = src_img->image[i] ;
    new_img->image[i]  =  A[value] * 255 / src_img->size ;
  }

  write_img( prog_name, new_img, dst_name ) ;
  printf( "\nHistogram equalization has been performed on %s and the result has been stored in %s\n\n", src_name, dst_name ) ;
}