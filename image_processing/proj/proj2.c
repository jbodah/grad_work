
#include <stdio.h>
#include <stdlib.h>
#include "img.h"
#include "tif.h"

// Inclusive between
#define BETWEEN(a,b,c)			 		((((a) >= (b)) && ((a) <= (c))) ? 1 : 0)
#define DIST_SQUARED(a,b,x,y)		((a - x)*(a - x) + (b - y)*(b - y))
#define DIFF(a,b)            		(a - b)
#define FACTOR									14


typedef struct {
  int x ;
	int y ;
} coord_pair ;

typedef struct {
	coord_pair pair[FACTOR][FACTOR] ; // Stores indices
} block ;

int get_pixel( img *src_img, int pixel_x, int pixel_y ) ;
int get_pixel_w_color( img *src_img, int pixel_x, int pixel_y, int color ) ;
int get_pixel_single( img *src_img, int i ) ;
int get_pixel_single_w_color( img *src_img, int i, int color ) ;

void set_pixel( img *src_img, int pixel_x, int pixel_y, int new_value ) ;
void set_pixel_w_color( img *src_img, int pixel_x, int pixel_y, int color, int new_value ) ;
void set_pixel_single( img *src_img, int i, int new_value ) ;
void set_pixel_single_w_color( img *src_img, int i, int color, int new_value ) ;

void   block_match( img *ref_img, img *next_img, int cutoff, int m ) ;
void   print_block( block *some_block ) ;
block *initialize_blocks( block *blocks, int blocks_in_x, int blocks_in_y, img *ref_img ) ;
float  calculate_sad( img *ref_img, block *ref_block, img *next_img, block *next_block ) ;
int    get_pixel_from_block_pair( img *src_img, block *src_block, int i, int j ) ;
void   paint_blocks( img *ref_img, img *next_img, block *ref_blocks, coord_pair *motion_vector, int blocks_size, int m ) ;
int 	 block_dist( block *block_ptr1, block *block_ptr2 ) ;

void threshold( img *src_img, int lo_value, int hi_value ) ;


// MAIN
// argv[1] = ref_img 			argv[2] = next_img		argv[3] = cutoff_dist
// argv[4] = paint_index	argv[5] = lo_thresh		argv[6] = hi_thresh
int main( int argc, char *argv[] ) {

  // cut img to 620 x 88
	// break into FACTORxFACTOR squares
	// search 7 blocks out

  img *ref_img  = read_img( "main", argv[1] ) ;
	img *next_img = read_img( "main", argv[2] ) ;
	
	//threshold( ref_img, atoi( argv[5] ), atoi( argv[6] )) ;
	//threshold( next_img, atoi( argv[5] ), atoi( argv[6] )) ;
	
  block_match( ref_img, next_img, atoi( argv[3] ), atoi( argv[4] )) ;

	return 0 ;
}

void threshold( img *src_img, int lo_value, int hi_value ) {
	int i ;

	for( i = 0 ; i < src_img->size ; i++ ) { 
	  if( BETWEEN( get_pixel_single( src_img, i ), lo_value, hi_value ))
		  set_pixel_single( src_img, i, get_pixel_single( src_img, i )) ;
	  else
		  set_pixel_single( src_img, i, 255 ) ;
	}
}

// Block match ref_img and next_img
void block_match( img *ref_img, img *next_img, int cutoff, int m ) {

  int i, j, k, l ;

  // break ref_img into FACTORxFACTOR blocks
	int blocks_in_x = ref_img->cols / FACTOR ; // 155
	int blocks_in_y = ref_img->rows / FACTOR ; // 22
	int blocks_size = blocks_in_x * blocks_in_y ;
	block *ref_blocks, *next_blocks ;
	float min_sad_vector[blocks_size] ;
	float temp ;
	
	coord_pair motion_vector[blocks_size] ;  // block-to-block link

	//int cutoff_dist_squared = cutoff * cutoff ;
		
	ref_blocks  =	initialize_blocks( ref_blocks, blocks_in_x, blocks_in_y, ref_img ) ;
	next_blocks = initialize_blocks( next_blocks, blocks_in_x, blocks_in_y, next_img ) ;

/*
	for( i = 0 ; i < 1500 ; i++ ) {
	  printf( "\nBLOCK %d\n", i ) ;
	  print_block( &next_blocks[i] ) ;
	}
*/

	printf( "blocks_size = %d\n", blocks_size ) ;

	// Doesn't overlap blocks
	for( i = 0 ; i < blocks_size ; i++ ) {
		min_sad_vector[i] = -1 ;
		for( j = 0 ; j < blocks_size ; j++ ) {
		  // Don't compare with self
		  if( i == j ) continue ;

			// Don't consider blocks that are too far
			if( !BETWEEN( ABS( DIFF( ref_blocks[i].pair[0][0].x, next_blocks[j].pair[0][0].x )), 0, cutoff ))
				continue ;
				
			if( !BETWEEN( ABS( DIFF( ref_blocks[i].pair[0][0].y, next_blocks[j].pair[0][0].y )), 0, cutoff ))
				continue ;	
				
			temp = calculate_sad( ref_img, &ref_blocks[i], next_img, &next_blocks[j] ) ;

			if( min_sad_vector[i] == -1 || temp < min_sad_vector[i] ) {
			  if( i == 734 ) printf( "\ni = %d ; val = %f\n", i, temp ) ; 
				min_sad_vector[i]  = temp ;
				motion_vector[i].x = DIFF( ref_blocks[i].pair[0][0].x, next_blocks[j].pair[0][0].x ) ;
				motion_vector[i].y = DIFF( ref_blocks[i].pair[0][0].y, next_blocks[j].pair[0][0].y ) ;
			}
		}
	}
	
	paint_blocks( ref_img, next_img, ref_blocks, motion_vector, blocks_size, m ) ;
}


// m = ref_blocks index to paint
void paint_blocks( img *ref_img, img *next_img, block *ref_blocks, coord_pair *motion_vector, int blocks_size, int m ) {

  int i, j, k, l, color ;

  img *painted_ref_img  = create_img( "paint", ref_img->cols,  ref_img->rows,  3 ) ;
  img *painted_next_img = create_img( "paint", next_img->cols, next_img->rows, 3 ) ;
	
	// Copy images over
	for( i = 0 ; i < ref_img->size ; i++ ) {
	  for( color = 0 ; color < 3 ; color++ ) {
	    set_pixel_single_w_color( painted_ref_img,  i, color, ref_img->image[i] ) ;
		  set_pixel_single_w_color( painted_next_img, i, color, next_img->image[i] ) ;
		}
	}
	
	k = FACTOR ; 				// kxk paint block
	
	int ref_x = ref_blocks[m].pair[0][0].x ;
	int ref_y = ref_blocks[m].pair[0][0].y ;
	
	// Paint images
	for( i = 0 ; i < k ; i++ ) {
	  for( j = 0 ; j < k ; j++ ) {
		  if(( i == 0 || i == k-1 ) || ( j == 0 || j == k-1 )) {
				for( color = 0 ; color < 1 ; color++ ) {
					set_pixel_w_color( painted_ref_img,  ref_x + i, ref_y + j, color, 255 ) ;
					set_pixel_w_color( painted_next_img, ref_x + i + motion_vector[m].x, ref_y + j + motion_vector[m].y, color, 255 ) ;
				}
				for( color = 1 ; color < 3 ; color++ ) {
					set_pixel_w_color( painted_ref_img,  ref_x + i, ref_y + j, color, 0 ) ;
					set_pixel_w_color( painted_next_img, ref_x + i + motion_vector[m].x, ref_y + j + motion_vector[m].y, color, 0 ) ;
				}
			}
		}
	}
	
	write_tiff( "paint", painted_ref_img,  "pref.tif" ) ;
	write_tiff( "paint", painted_next_img, "pnext.tif" ) ;
}



/*
int get_block_x_position( block *block_ptr, int blocks_in_x ) {
	return block_ptr->
}

int get_block_y_position( block *block_ptr ) {
	return block_ptr->
}
*/



// Calculate SAD for two blocks
float calculate_sad( img *ref_img, block *ref_block, img *next_img, block *next_block ) {
  int i, j ;
  float sum = 0	;

  for( i = 0 ; i < FACTOR ; i++ ) {
	  for( j = 0 ; j < FACTOR ; j++ ) {
		  sum += ABS( DIFF( get_pixel_from_block_pair( ref_img, ref_block, i, j ), get_pixel_from_block_pair( next_img, next_block, i, j )));
		}
	}
	return sum ;
}









int block_dist( block *block_ptr1, block *block_ptr2 ) {
  int a = block_ptr1->pair[0][0].x ;
	int b = block_ptr1->pair[0][0].y ;
	int x = block_ptr2->pair[0][0].x ;
	int y = block_ptr2->pair[0][0].y ;
	return DIST_SQUARED( a, b, x, y ) ;
}


int get_pixel_from_block_pair( img *src_img, block *src_block, int i, int j ) {
  return get_pixel( src_img, src_block->pair[i][j].x, src_block->pair[i][j].y ) ;
}


// Initialize coordinates for blocks
block *initialize_blocks( block *block_ptr, int blocks_in_x, int blocks_in_y, img *src_img ) {
  int i, j, k, l, n = 0 ;
	
	// Malloc up an image-ful of blocks
	block_ptr = malloc( blocks_in_x * blocks_in_y * sizeof( block ))  ;

	// Initialize block coordinates
  for( j = 0 ; j < blocks_in_y * FACTOR ; j += FACTOR ) {
    for( i = 0 ; i < blocks_in_x * FACTOR ; i += FACTOR ) {
		  for( k = 0 ; k < FACTOR ; k++ ) {
			  for( l = 0 ; l < FACTOR ; l++ ) {
					block_ptr[n].pair[k][l].x = i + k ;
					block_ptr[n].pair[k][l].y = j + l ;
				}
			}	
			n++ ;
		}
	}
	return block_ptr ;
}


void print_block( block *some_block ) {
  int i, j ;
	
	for( j = 0 ; j < FACTOR ; j++ ) {
    for( i = 0 ; i < FACTOR ; i++ ) {
		  printf( "(%d, %d) = %d, %d\n", i, j, some_block->pair[i][j].x, some_block->pair[i][j].y ) ;
		}
  }
}


// getters + setters

int get_pixel( img *src_img, int pixel_x, int pixel_y ) {
	return src_img->image[pixel_y * src_img->cols + pixel_x] ;
}

int get_pixel_w_color( img *src_img, int pixel_x, int pixel_y, int color ) {
	return src_img->image[color * src_img->cols * src_img->rows + pixel_y * src_img->cols + pixel_x] ;
}

int get_pixel_single( img *src_img, int i ) {
	return src_img->image[i] ;
}

int get_pixel_single_w_color( img *src_img, int i, int color ) {
	return src_img->image[color * src_img->cols * src_img->rows + i] ;
}

void set_pixel( img *src_img, int pixel_x, int pixel_y, int new_value ) {
  src_img->image[pixel_y * src_img->cols + pixel_x] = new_value ;
}

void set_pixel_w_color( img *src_img, int pixel_x, int pixel_y, int color, int new_value ) {
  src_img->image[color * src_img->cols * src_img->rows + pixel_y * src_img->cols + pixel_x] = new_value ;
}

void set_pixel_single( img *src_img, int i, int new_value ) {
  src_img->image[i] = new_value ;
}

void set_pixel_single_w_color( img *src_img, int i, int color, int new_value ) {
  src_img->image[color * src_img->cols * src_img->rows + i] = new_value ;
}