
#include <stdio.h>
#include <stdlib.h>
#include "img.h"
#include "tif.h"

// Inclusive between
#define BETWEEN(a,b,c)			 		((((a) >= (b)) && ((a) <= (c))) ? 1 : 0)
#define DIST_SQUARED(a,b,x,y)		((a - x)*(a - x) + (b - y)*(b - y))
#define DIFF(a,b)            		(a - b)
#define FACTOR									20

typedef struct {
  int x ;
  int y ;
} coord_pair ;

typedef struct {
  coord_pair pair[FACTOR][FACTOR] ; // Stores indices
} block ;

typedef struct {
  block *block ;
  int  	 size_x ;
  int  	 size_y ;
  long 	 size ; // Total size
} block_set ;

typedef struct {
	int   x ;
	int   y ;
	float min_sad ;
} motion ;

typedef struct {
	motion *displacement ;
} motion_vector ;

block_set 		*initialize_ref_blocks( img *ref_img ) ;
block_set 		*initialize_next_blocks( img *next_img ) ;
motion_vector *init_motion_vector( int blocks_size ) ;

void   block_match( img *ref_img, img *next_img, int cutoff, int m ) ;
void   print_block( block *some_block ) ;
float  calculate_sad( img *ref_img, block *ref_block, img *next_img, block *next_block ) ;
void 	 paint_blocks( img *ref_img, img *next_img, block_set *ref_blocks, motion_vector *mv, int m ) ;
void 	 threshold( img *src_img, int lo_value, int hi_value ) ;
void 	 compare_blocks( motion_vector *mv, img *ref_img, block *ref_block, img *next_img, block *next_block, int cutoff, int i, int print ) ;

// Getters + Setters
int  get_pixel( img *src_img, int pixel_x, int pixel_y ) ;
int  get_pixel_w_color( img *src_img, int pixel_x, int pixel_y, int color ) ;
int  get_pixel_single( img *src_img, int i ) ;
int  get_pixel_single_w_color( img *src_img, int i, int color ) ;
void set_pixel( img *src_img, int pixel_x, int pixel_y, int new_value ) ;
void set_pixel_w_color( img *src_img, int pixel_x, int pixel_y, int color, int new_value ) ;
void set_pixel_single( img *src_img, int i, int new_value ) ;
void set_pixel_single_w_color( img *src_img, int i, int color, int new_value ) ;

// MAIN
// argv[1] = ref_img 			argv[2] = next_img		argv[3] = cutoff_dist
// argv[4] = paint_index	argv[5] = lo_thresh		argv[6] = hi_thresh
int main( int argc, char *argv[] ) {

  img *ref_img  = read_img( "main", argv[1] ) ;
	img *next_img = read_img( "main", argv[2] ) ;
	
	//threshold( ref_img, atoi( argv[5] ), atoi( argv[6] )) ;
	//threshold( next_img, atoi( argv[5] ), atoi( argv[6] )) ;
	
  block_match( ref_img, next_img, atoi( argv[3] ), atoi( argv[4] )) ;

	return 0 ;
}


// Block match ref_img and next_img
void block_match( img *ref_img, img *next_img, int cutoff, int m ) {

  int i, j, k, l, print ;
		
	float temp ;
	
	// Init
	block_set *ref_blocks  =	initialize_ref_blocks( ref_img ) ;
	block_set *next_blocks = initialize_next_blocks( next_img ) ;

	// Stores motions from ref_block to next_block as well as min_sad calculated		
	motion_vector *mv = init_motion_vector( ref_blocks->size ) ; 
	
	// For each ref_block, find next_block with min_sad
	
	for( i = 0 ; i < ref_blocks->size ; i++ ) {
		mv->displacement[i].min_sad = -1 ;
		for( j = 0 ; j < next_blocks->size ; j++ ) {
			if( i == m ) print = 1 ;
			else print = 0 ;
			
			// FOR PRINTING ONLY
			if( i != m ) continue ;
			
			if( ref_blocks->block[i].pair[0][0].x == next_blocks->block[j].pair[0][0].x
					&& ref_blocks->block[i].pair[0][0].y == next_blocks->block[j].pair[0][0].y )
					continue ;
			// Don't consider blocks that are too far
			if( !BETWEEN( ABS( DIFF( ref_blocks->block[i].pair[0][0].x, next_blocks->block[j].pair[0][0].x )), 0, cutoff ))
				continue ;	
			if( !BETWEEN( ABS( DIFF( ref_blocks->block[i].pair[0][0].y, next_blocks->block[j].pair[0][0].y )), 0, cutoff ))
				continue ;	
				
			compare_blocks( mv, ref_img, &ref_blocks->block[i], next_img, &next_blocks->block[j], cutoff, i, print ) ;
		}
	}
	paint_blocks( ref_img, next_img, ref_blocks, mv, m ) ;
}

// m = ref_blocks index to paint
void paint_blocks( img *ref_img, img *next_img, block_set *ref_blocks, motion_vector *mv, int m ) {

  int i, j, k, l, color ;

  img *pr_img = create_img( "paint", ref_img->cols,  ref_img->rows,  3 ) ;
  img *pn_img = create_img( "paint", next_img->cols, next_img->rows, 3 ) ;
	
	// Copy images over
	for( i = 0 ; i < ref_img->size ; i++ ) {
	  for( color = 0 ; color < 3 ; color++ ) {
	    set_pixel_single_w_color( pr_img,  i, color, ref_img->image[i] ) ;
		  set_pixel_single_w_color( pn_img,  i, color, next_img->image[i] ) ;
		}
	}
	
	k = FACTOR ; 				// kxk paint block
	
	int ref_x = ref_blocks->block[m].pair[0][0].x ;
	int ref_y = ref_blocks->block[m].pair[0][0].y ;
	
	printf( "\n\nmv.x = %d", 				mv->displacement[m].x ) ;
	printf( "\nmv.y = %d", 					mv->displacement[m].y ) ;
	printf( "\nmv.min_sad = %f\n", 	mv->displacement[m].min_sad ) ;
	printf( "\nref.x = %d", 				ref_x ) ;
	printf( "\nref.y = %d\n", 			ref_y ) ;
	printf( "\nnext.x = %d", 				mv->displacement[m].x + ref_x ) ;
	printf( "\nnext.y = %d\n\n", 		mv->displacement[m].y + ref_y ) ;
	
	// Paint images
	for( i = 0 ; i < k ; i++ ) {
	  for( j = 0 ; j < k ; j++ ) {
		  if(( i == 0 || i == k-1 ) || ( j == 0 || j == k-1 )) {
				for( color = 0 ; color < 1 ; color++ ) {
					set_pixel_w_color( pr_img,  ref_x + i, ref_y + j, color, 255 ) ;
					set_pixel_w_color( pn_img, ref_x + i + mv->displacement[m].x, ref_y + j + mv->displacement[m].y, color, 255 ) ;
				}
				for( color = 1 ; color < 3 ; color++ ) {
					set_pixel_w_color( pr_img,  ref_x + i, ref_y + j, color, 0 ) ;
					set_pixel_w_color( pn_img, ref_x + i + mv->displacement[m].x, ref_y + j + mv->displacement[m].y, color, 0 ) ;
				}
			}
		}
	}
	
	write_tiff( "paint", pr_img,  "pref.tif" ) ;
	write_tiff( "paint", pn_img, 	"pnext.tif" ) ;
}


// Init
motion_vector *init_motion_vector( int blocks_size ) {
	int i ;

	motion_vector *mv = malloc( sizeof( motion_vector )) ;	
	
	mv->displacement = malloc( blocks_size * sizeof( motion )) ;

	return mv ;
} 

// Initialize coordinates for blocks
block_set *initialize_ref_blocks( img *ref_img ) {
  int i, j, k, l, n = 0 ;

	block_set *ref = malloc( sizeof( block_set )) ;
	
	ref->size_x = ref_img->cols / FACTOR ;
	ref->size_y = ref_img->rows / FACTOR ;
	ref->size		= ref->size_x * ref->size_y ;
	
	ref->block = malloc( ref->size * sizeof( block )) ;
	
	
	// Initialize block coordinates
	// Don't overlap
	// Set base pixel
	for( j = 0 ; j < ref_img->rows - FACTOR ; j += FACTOR ) {
		for( i = 0 ; i < ref_img->cols - FACTOR ; i += FACTOR ) {
			// Initialize each block
			for( k = 0 ; k < FACTOR ; k++ ) {
				for( l = 0 ; l < FACTOR ; l++ ) {
					ref->block[n].pair[k][l].x = i + k ;
					ref->block[n].pair[k][l].y = j + l ;
				}
			}	
			if( n > ref->size - 1 ) printf( "\nError in init ref_blocks\n" ) ;
			n++ ;
		}
	}
	return ref ;
}

// Initialize coordinates for blocks
block_set *initialize_next_blocks( img *next_img ) {
  int i, j, k, l, n = 0 ;

	block_set *next = malloc( sizeof( block_set )) ;
	
	next->size_x = next_img->cols - FACTOR ;
	next->size_y = next_img->rows - FACTOR ;
	next->size	 = next->size_x * next->size_y ;
	
	next->block = malloc( next->size * sizeof( block )) ;
	
	// Initialize block coordinates
	// Don't overlap
	// Set base pixel
	for( j = 0 ; j < next_img->rows - FACTOR ; j++ ) {
		for( i = 0 ; i < next_img->cols - FACTOR ; i++ ) {
			// Initialize each block
			for( k = 0 ; k < FACTOR ; k++ ) {
				for( l = 0 ; l < FACTOR ; l++ ) {
					next->block[n].pair[k][l].x = i + k ;
					next->block[n].pair[k][l].y = j + l ;
				}
			}	
			if( n > next->size - 1 ) printf( "\nError in init next_blocks\n" ) ;
			n++ ;
		}
	}
	return next ;
}

void compare_blocks( motion_vector *mv, img *ref_img, block *ref_block, img *next_img, block *next_block, int cutoff, int i, int print ) {
	float curr_sad ;

  if( ref_block->pair[0][0].x == next_block->pair[0][0].x
			&& ref_block->pair[0][0].y == next_block->pair[0][0].y )
		return ;

	// Don't consider blocks that are too far
	if( !BETWEEN( ABS( DIFF( ref_block->pair[0][0].x, next_block->pair[0][0].x )), 0, cutoff ))
		return ;	
	if( !BETWEEN( ABS( DIFF( ref_block->pair[0][0].y, next_block->pair[0][0].y )), 0, cutoff ))
		return ;	
	
	curr_sad = calculate_sad( ref_img, ref_block, next_img, next_block ) ;

	if( curr_sad == mv->displacement[i].min_sad && print == 1 )
		printf( "\ncurr_sad == min_sad" ) ;
	if( mv->displacement[i].min_sad == -1 || curr_sad < mv->displacement[i].min_sad ) {
		if( print == 1 ) printf( "\ncurr_sad replaced min_sad" ) ;
		mv->displacement[i].min_sad = curr_sad ;
		mv->displacement[i].x 			= DIFF( next_block->pair[0][0].x, ref_block->pair[0][0].x ) ;
		mv->displacement[i].y  			= DIFF( next_block->pair[0][0].y, ref_block->pair[0][0].y ) ;
	}
}

// Calculate SAD for two blocks
float calculate_sad( img *ref_img, block *ref_block, img *next_img, block *next_block ) {
  int i, j ;
  float sum = 0	;
	coord_pair r_pair, n_pair ;

  for( i = 0 ; i < FACTOR ; i++ ) {
	  for( j = 0 ; j < FACTOR ; j++ ) {
			r_pair = ref_block->pair[i][j] ;
			n_pair = next_block->pair[i][j] ;
		  sum += ABS( DIFF( get_pixel( ref_img, r_pair.x, r_pair.y ), get_pixel( next_img, n_pair.x, n_pair.y )));
		}
	}
	return sum ;
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