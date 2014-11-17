
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"


//============================================================================
//                                  Main
//============================================================================
int main(int argc, char* argv[])
{
  //--------------------------------------------------------------------------
  // Read file "gargouille.ppm" into image (width and height)
  //--------------------------------------------------------------------------
  
  image* myImage=new image;
  ppm_read_from_file(myImage, "gargouille.ppm");

  //--------------------------------------------------------------------------
  // Create a desaturated (B&W) copy of the image we've just read and
  // write it into "gargouille_BW.ppm"
  //--------------------------------------------------------------------------
  // Copy image into image_bw
  image* BWImage= new image;
  BWImage->width=myImage->width;
  BWImage->height=myImage->height;
  BWImage->pixel=new u_char[3 * BWImage->width * BWImage->height];
  memcpy(BWImage->pixel, myImage->pixel, 3 * BWImage->width * BWImage->height * sizeof(u_char));

  // Desaturate image_bw
  ppm_desaturate(BWImage);

  // Write the desaturated image into "gargouille_BW.ppm"
  ppm_write_to_file(BWImage, "gargouille_BW.ppm");

  // Free the desaturated image
  delete(BWImage);

  //--------------------------------------------------------------------------
  // Create a resized copy of the image and
  // write it into "gargouille_small.ppm"
  //--------------------------------------------------------------------------
  // Copy image into image_small
  image* smallImage=new image;
  smallImage->width=myImage->width;
  smallImage->height=myImage->height;
  smallImage->pixel=new u_char[3 * smallImage->width * smallImage->height];
  memcpy(smallImage->pixel, myImage->pixel, 3 * smallImage->width * smallImage->height * sizeof(u_char));

  // Shrink image_small size 2-fold
  ppm_shrink(smallImage, 2);

  // Write the desaturated image into "gargouille_small.ppm"
  ppm_write_to_file(smallImage, "gargouille_small.ppm");

  // Free the not yet freed images
  delete(myImage);
  delete(smallImage);

  return 0;
}


  
