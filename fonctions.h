

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
