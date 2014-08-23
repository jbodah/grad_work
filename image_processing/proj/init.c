#include <stdio.h>
#include <stdlib.h>
#include "img.h"
#include "tif.h"
#include "init.h"

// Init
motion_vector *init_motion_vector( int blocks_size ) {
	int i ;

	motion_vector *mv = malloc( sizeof( motion_vector )) ;	
	
	for( i = 0 ; i < blocks_size ; i++ ) {
		mv[i] = malloc( sizeof( motion )) ;
	}
	return mv ;
} 

// Initialize coordinates for blocks
block_set *initialize_ref_blocks( img *ref_img ) {
  int i, j, k, l, n = 0 ;

	block_set *ref = malloc( sizeof( block_set )) ;
	
	ref->size_x = ref_img->cols / FACTOR ;
	ref->size_y = ref_img->rows / FACTOR ;
	ref->size		= ref->size_x * ref->size_y ;
	
	for( i = 0 ; i < ref->size ; i+++ ) {
		ref->block = malloc( ref->size * sizeof( block )) ;
	}
	
	// Initialize block coordinates
	// Don't overlap
	// Set base pixel
	for( i = 0 ; i < ref_img->cols - FACTOR ; i += FACTOR ) {
		for( j = 0 ; j < ref_img->rows - FACTOR ; j += FACTOR ) {
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
	next->size	 = next->size_x * ref->size_y ;
	
	for( i = 0 ; i < next->size ; i+++ ) {
		next->block = malloc( ref->size * sizeof( block )) ;
	}
	
	// Initialize block coordinates
	// Don't overlap
	// Set base pixel
	for( i = 0 ; i < next_img->cols - FACTOR ; i++ ) {
		for( j = 0 ; j < next_img->rows - FACTOR ; j++ ) {
			// Initialize each block
			for( k = 0 ; k < FACTOR ; k++ ) {
				for( l = 0 ; l < FACTOR ; l++ ) {
					next->block[n].pair[k][l].x = i + k ;
					next->block[n].pair[k][l].y = j + l ;
				}
			}	
			if( n > next->size - 1 ) printf( "\nError in init ref_blocks\n" ) ;
			n++ ;
		}
	}
	return next ;
}