/***************************************************/
/* Programmer: Joshua Bodah                        */
/*                                                 */
/* CS 545 HW1                                      */
/***************************************************/

#include <stdio.h>
#include "img.h"

void hw1_header() ;
img *find_img( char *img_name ) ;
void about_img( img *src_img ) ;
void create_rotation_of( char *prog_name, char *src_name, img *src_img, char *dst_name ) ;
void invert( char *prog_name, char *src_name, img *src_img, char *dst_name ) ;
void blur( char *prog_name, char *src_name, img *src_img, char *dst_name ) ;
void shrink( char *prog_name, char *src_name, img *src_img, char *dst_name ) ;

int main() {

  img *src_img ;
  char src_name[IMG_FILE_NAME_LENGTH] ;
  char dst_name[IMG_FILE_NAME_LENGTH] ;
  
  hw1_header() ; 						  					  	  // Intro text
  
  printf( "Input file (.img): " ) ;			   	  	  			  // Prompt user for file name
  scanf( "%s", &src_name ) ;          		  	  				  // Read file name
  
  src_img = find_img( src_name ) ; 							 	  // Load image
  about_img( src_img ) ; 				  					      // Display source image details
  create_rotation_of( "hw1", src_name, src_img, "rotate.img" ) ;  // Create rotated copy
  invert( "hw1", src_name, src_img, "invert.img" ) ;			  // Create inverted copy
  blur( "hw1", src_name, src_img, "blur.img" ) ;			      // Create blurred copy
  shrink( "hw1", src_name, src_img, "shrink.img" ) ;			  // Create shrunken copy
  
  
  return 0 ;
}

// Intro text about problem
void hw1_header() {
  printf( "\nCS 545 HW1 by Joshua Bodah\n--------------------------\n\n" ) ;
  printf( "Problem sections:\n\t1. Rotate image 90 degrees in some direction\n\t2. Invert the image\n\t3. Replace each pixel by the average of four adjacent pixels in some direction\n\t4. Make a picture one-half the number of pixels in each direction\n\n" ) ;
}

// Tries to load image
img *find_img( char *img_name ) {

  img *im ;

  printf( "\nLoading %s...\n", img_name ) ; // Loading message

  // Read image
  im = read_img( "hw1", img_name ) ; 	  // read_img handles NULL exceptions 
  printf( "%s loaded\n", img_name ) ; 	  // Image found
  
  return im ;
}  

// Prints details about src_img
void about_img( img *src_img ) {
  printf( "\nImage details:\n\tColumns:\t%ld\n\tRows:\t\t%ld\n\tColors:\t\t%ld\n\tSize:\t\t%ld\n",
			src_img->cols, src_img->rows, src_img->colors, src_img->size );
}

// Generates a new image of the src_image rotated clockwise 90 degrees
void create_rotation_of( char *prog_name, char *src_name, img *src_img, char *dst_name ) {
  img *new_img ;
  long color, row, col ;
  
  new_img = create_img( prog_name, src_img->rows, src_img->cols, src_img->colors ) ;
  
  for( color = 0 ; color < src_img->colors ; color++ ) {
    for( row = 0 ; row < src_img->rows ; row++ ) {
	  for( col = 0 ; col < src_img->cols ; col++ ) {
		new_img->image[color * new_img->rows * new_img->cols
						+ col * new_img->cols 
						+ new_img->cols - 1 - row]
						=
						src_img->image[color * src_img->rows * src_img->cols
										+ row * src_img->cols
										+ col] ;
	  }
	}
  }

  write_img( prog_name, new_img, dst_name ) ;
  printf( "\n%s has been rotated clockwise 90 degrees and stored in %s\n\n", src_name, dst_name ) ;
 }
 
//Generates an inverted copy of the src_image
void invert( char *prog_name, char *src_name, img *src_img, char *dst_name ) {
  img *new_img ;
  long color, row, col ;
  
  new_img = copy_img( prog_name, src_img ) ;
  
  for( color = 0 ; color < src_img->colors ; color++ ) { 
	for( row = 0 ; row < src_img->rows ; row++ ) {
	  for( col = 0 ; col < src_img->cols ; col++ ) {
		new_img->image[color * src_img->rows * src_img->cols
						+ row * src_img->cols
						+ col]
						=
						255 - src_img->image[color * src_img->rows * src_img->cols
											+ row * src_img->cols
											+ col] ;
	  }
	}
  } 

  write_img( prog_name, new_img, dst_name ) ;
  printf( "\n%s has been inverted and stored in %s\n\n", src_name, dst_name ) ;
 }
 
//Generates an blurred copy of the src_image. Blurs with 4-neighbors
void blur( char *prog_name, char *src_name, img *src_img, char *dst_name ) {
  img *new_img ;
  int count ;
  long color, row, col, avg ;
  
  new_img = copy_img( prog_name, src_img ) ;
  
  for( color = 0 ; color < src_img->colors ; color++ ) { 
	for( row = 0 ; row < src_img->rows ; row++ ) {
	  for( col = 0 ; col < src_img->cols ; col++ ) {
		
		count = 1 ;
		avg = src_img->image[color * src_img->rows * src_img->cols + row * src_img->cols + col] ;
		
		if( row-1 >= 0 ) {
		  count++ ;
		  avg += src_img->image[color * src_img->rows * src_img->cols + (row-1) * src_img->cols + col] ;
		}
		
		if( row+1 < src_img->rows ) {
		  count++ ;
		  avg += src_img->image[color * src_img->rows * src_img->cols + (row+1) * src_img->cols + col] ;
		}
		
		if( col-1 >= 0 ) {
		  count++ ;
		  avg += src_img->image[color * src_img->rows * src_img->cols + row * src_img->cols + (col-1)] ;
		}
		
		if( col+1 < src_img->cols ) {
		  count++ ;
		  avg += src_img->image[color * src_img->rows * src_img->cols + row * src_img->cols + (col+1)] ;
		}
		
		new_img->image[color * src_img->rows * src_img->cols + row * src_img->cols + col] = avg / count ;
	  }
	}
  } 

  write_img( prog_name, new_img, dst_name ) ;
  printf( "\n%s has been blurred and stored in %s\n\n", src_name, dst_name ) ;
 }
 
 //Generates an shrunken copy of the src_image
void shrink( char *prog_name, char *src_name, img *src_img, char *dst_name ) {
  img *new_img ;
  int count ;
  long color, row, col, avg ;
  
  new_img = create_img( prog_name, src_img->cols/2, src_img->rows/2, src_img->colors ) ;
  
  for( color = 0 ; color < new_img->colors ; color++ ) {
    for( row = 0 ; row < new_img->rows ; row++ ) {
	  for( col = 0 ; col < new_img->cols ; col++ ) {
	  
		count = 1 ;
		avg = src_img->image[color * src_img->rows * src_img->cols + 2*row * src_img->cols + 2*col] ;
		
		if( row+1 < src_img->rows ) {
		  count++ ;
		  avg += src_img->image[color * src_img->rows * src_img->cols + (2*row+1) * src_img->cols + 2*col] ;
		  if( col+1 < src_img->cols ) {
			count++ ;
			avg += src_img->image[color * src_img->rows * src_img->cols + (2*row+1) * src_img->cols + (2*col+1)] ;
		  }
		}
		
		if( col+1 < src_img->cols ) {
		  count++ ;
		  avg += src_img->image[color * src_img->rows * src_img->cols + 2*row * src_img->cols + (2*col+1)] ;
		}
				
		new_img->image[color * new_img->rows * new_img->cols + row * new_img->cols + col] = avg / count ;
	  }
	}
  }

  write_img( prog_name, new_img, dst_name ) ;
  printf( "\n%s has been shrunken and stored in %s\n\n", src_name, dst_name ) ;
 }