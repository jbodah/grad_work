/* bmp.h
   Michael A. Gennert
   12 Sept 1002

   MS .bmp image format

   Header contains 14 bytes:
   signature = 2 bytes = "BM"
   fileSize = 4 bytes
   reserved = 4 bytes = 0
   dataOffset = 4 bytes = file offset to raster data

   InfoHeader contains 40 bytes:
   size = 4 bytes = size of info header = 40
   width = 4 bytes
   height = 4 bytes
   planes = 2 bytes = 1
   bitCount = 2 bytes = bits per pixel = 24 for RGB
   compression = 4 bytes = 0 for no compression
   imageSize = 4 bytes = 0 for no compression
   xPixelsPerM = 4 bytes = X pixels per M = 0
   yPixelsPerM = 4 bytes = Y pixels per M = 0
   colorsUsed = 4 bytes = number of actually used colors
   colorsImportant = 4 bytes = 0 if all important

   And 2 byte padding so it ends on an even byte boundary.
*/

// Image IO header structure
typedef struct bmp_hdr {
  char BMP_signature[2];  
  unsigned char BMP_filesize[4];
  unsigned char BMP_reserved[4];
  unsigned char BMP_dataoffset[4];
  unsigned char BMP_size[4];
  unsigned char BMP_width[4];
  unsigned char BMP_height[4];
  unsigned char BMP_planes[2];
  unsigned char BMP_bitcount[2];
  unsigned char BMP_compression[4];
  unsigned char BMP_imagesize[4];
  unsigned char BMP_xpixelsperm[4];
  unsigned char BMP_ypixelsperm[4];
  unsigned char BMP_colorsused[4];
  unsigned char BMP_colorsimportant[4];
  char BMP_unused[2];
} bmp_hdr;

