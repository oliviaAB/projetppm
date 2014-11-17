
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



//============================================================================
//                           Function declarations
//============================================================================

//Creation of structure image with width, height, and an unsigned char table 
// filled with pixels
typedef struct
{
  int width;
  int height;
  u_char* pixel;
}image;

// Write the image contained in <data> (of size <width> * <height>)
// into plain RGB ppm file <file>
void ppm_write_to_file(image * image, char* filename);

// Read the image contained in plain RGB ppm file <file>
// into <data> and set <width> and <height> accordingly
// Warning: data is malloc_ed, don't forget to free it
void ppm_read_from_file(image* image, char* filename);

// Desaturate (transform to B&W) <image> (of size <width> * <height>)
void ppm_desaturate(image* image);

// Shrink image (of original size <width> * <height>) by factor <factor>
// <width> and <height> are updated accordingly
void ppm_shrink(image* image, int factor);

//============================================================================
//                                  Main
//============================================================================
int main(int argc, char* argv[])
{
  //--------------------------------------------------------------------------
  // Read file "gargouille.ppm" into image (width and height)
  //--------------------------------------------------------------------------
  image* myImage;
  myImage=(image*)malloc(sizeof(myImage));
  ppm_read_from_file(myImage, "gargouille.ppm");

  //--------------------------------------------------------------------------
  // Create a desaturated (B&W) copy of the image we've just read and
  // write it into "gargouille_BW.ppm"
  //--------------------------------------------------------------------------
  // Copy image into image_bw
  image* BWImage;
  BWImage=(image*)malloc(sizeof(BWImage));
  BWImage->width=myImage->width;
  BWImage->height=myImage->height;
  BWImage->pixel=(u_char*)malloc(3 * BWImage->width * BWImage->height *sizeof(u_char));
  memcpy(BWImage->pixel, myImage->pixel, 3 * BWImage->width * BWImage->height * sizeof(u_char));

  // Desaturate image_bw
  ppm_desaturate(BWImage);

  // Write the desaturated image into "gargouille_BW.ppm"
  ppm_write_to_file(BWImage, "gargouille_BW.ppm");

  // Free the desaturated image
  free(BWImage);

  //--------------------------------------------------------------------------
  // Create a resized copy of the image and
  // write it into "gargouille_small.ppm"
  //--------------------------------------------------------------------------
  // Copy image into image_small
  image* smallImage;
  smallImage=(image*)malloc(sizeof(BWImage));
  smallImage->width=myImage->width;
  smallImage->height=myImage->height;
  smallImage->pixel=(u_char*)malloc(3 * smallImage->width * smallImage->height *sizeof(u_char));
  memcpy(smallImage->pixel, myImage->pixel, 3 * smallImage->width * smallImage->height * sizeof(u_char));

  // Shrink image_small size 2-fold
  ppm_shrink(smallImage, 2);

  // Write the desaturated image into "gargouille_small.ppm"
  ppm_write_to_file(smallImage, "gargouille_small.ppm");

  // Free the not yet freed images
  free(myImage);
  free(smallImage);

  return 0;
}

//============================================================================
//                           Function declarations
//============================================================================
void ppm_write_to_file(image* image, char* filename)
{

  //Create the FILE
  FILE* ppm_output = fopen(filename, "wb");	

  // Write header
  fprintf(ppm_output, "P6\n%d %d\n255\n", image->width, image->height);

  // Write pixels
  fwrite(image->pixel, 3, image->width*image->height, ppm_output);

  fclose(ppm_output);
}

//-------------------------------------------------------------------------------

void ppm_read_from_file(image* image, char* filename)
{

  FILE* ppm_input = fopen(filename, "rb");

  // Read file header
  fscanf(ppm_input, "P6\n%d %d\n255\n", &(image->width), &(image->height));

  // Allocate memory according to width and height
  image->pixel = (u_char*) malloc(3 * (image->width) * (image->height) * sizeof(u_char));

  // Read the actual image data
  fread(image->pixel, 3, (image->width) * (image->height), ppm_input);

  fclose(ppm_input);
}

//--------------------------------------------------------------------------------

void ppm_desaturate(image* image)
{
  int x, y;

  // For each pixel ...
  for (x = 0 ; x < image->width ; x++)
  {
    for (y = 0 ; y < image->height ; y++)
    {
      u_int grey_lvl = 0;
      int rgb_canal;

      // Compute the grey level
      for (rgb_canal = 0 ; rgb_canal < 3 ; rgb_canal++)
      {
        grey_lvl += image->pixel[ 3 * (y * image->width + x) + rgb_canal ];
      }
      grey_lvl /= 3;
      assert(grey_lvl >= 0 && grey_lvl <=255);

      // Set the corresponding pixel's value in new_image
      memset(&(image->pixel[3 * (y * image->width + x)]), grey_lvl, 3);   //MAYBE AN ERROR	
    }
  }
}

//---------------------------------------------------------------------------------

void ppm_shrink(image* image, int factor)
{
  // Compute new image size and allocate memory for the new image
  int new_width   = (image->width) / factor;
  int new_height  = (image->height) / factor;
  u_char* new_image = (u_char*) malloc(3 * new_width * new_height * sizeof(*new_image));

  // Precompute factor^2 (for performance reasons)
  int factor_squared = factor * factor;

  // For each pixel of the new image...
  int x, y;
  for (x = 0 ; x < new_width ; x++)
  {
    for (y = 0 ; y < new_height ; y++)
    {
      // ... compute the average RGB values of the set of pixels (a square of side factor)
      // that correspond to the pixel we are creating.

      // Initialize RGB values for the new image's pixel
      u_int red   = 0;
      u_int green = 0;
      u_int blue  = 0;

      // Compute coordinates and index of the first (top-left) pixel from the
      // model image corresponding to the pixel we are creating
      int x0 = x * factor;
      int y0 = y * factor;
      int i0 = 3 * (y0 * (image->width) + x0);

      // Compute RGB values for the new pixel
      int dx, dy;
      for (dx = 0 ; dx < factor ; dx++)
      {
        for (dy = 0 ; dy < factor ; dy++)
        {
          // Compute the offset of the current pixel (in the model image)
          // with regard to the top-left pixel of the current "set of pixels"
          int delta_i = 3 * (dy * (image->width) + dx);

          // Accumulate RGB values
          red   += (image->pixel)[i0+delta_i];
          green += (image->pixel)[i0+delta_i+1];
          blue  += (image->pixel)[i0+delta_i+2];
        }
      }

      // Divide RGB values to get the mean values
      red   /= factor_squared;
      green /= factor_squared;
      blue  /= factor_squared;

      // Set new pixel's RGB values
      new_image[ 3 * (y * new_width + x) ]     = red;
      new_image[ 3 * (y * new_width + x) + 1 ] = green;
      new_image[ 3 * (y * new_width + x) + 2 ] = blue;
    }
  }

  // Update image size
  image->width  = new_width;
  image->height = new_height;

  // Update image
  //free(*image);
  image->pixel = new_image;
}

