
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Image.h"


//============================================================================
//                                  Main
//============================================================================
int main(int argc, char* argv[])
{
  //--------------------------------------------------------------------------
  // Read file "gargouille.ppm" into image (width and height)
  //--------------------------------------------------------------------------
  
  Image myImage=Image();
  myImage.ppm_read_from_file("gargouille.ppm");

  //--------------------------------------------------------------------------
  // Create a desaturated (B&W) copy of the image we've just read and
  // write it into "gargouille_BW.ppm"
  //--------------------------------------------------------------------------
  // Copy image into image_bw
  Image BWImage=Image(myImage);

  // Desaturate image_bw
  BWImage.ppm_desaturate();

  // Write the desaturated image into "gargouille_BW.ppm"
  BWImage.ppm_write_to_file("gargouille_BWTEST.ppm");

  //--------------------------------------------------------------------------
  // Create a resized copy of the image and
  // write it into "gargouille_small.ppm"
  //--------------------------------------------------------------------------
  // Copy image into image_small
  Image smallImage=Image(myImage);

  // Shrink image_small size 2-fold
  smallImage.ppm_shrink(2);

  // Write the desaturated image into "gargouille_small.ppm"
  smallImage.ppm_write_to_file("gargouille_small.ppm");

}
