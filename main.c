#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int width, height, channels;
char *filename = "fox3.gif";

int main() {

  unsigned char *img = stbi_load(filename, &width, &height, &channels, 0);

  if (!img) {
    fprintf(stderr, "Cannot load file image %s\nReason: %s\n", filename, stbi_failure_reason());
    exit(0);
  }

  int gray_channels = 1;
  size_t img_size = width * height * channels;
  size_t gray_img_size = width * height * gray_channels;

  //unsigned char *gray_img = malloc(gray_img_size);

  uint8_t gray_img[gray_img_size];

  // go over each channel and copy average
  int c = 0;
  for(unsigned char *p = img; p != img + img_size; p += channels, c++) {
    gray_img[c] = (uint8_t)((*p + *(p + 1) + *(p + 2))/3.0);
    //*pg = (uint8_t)((*p + *(p + 1) + *(p + 2))/3.0);
    /*
    // transparency is copied over to 2nd channel - not used
    if(channels == 4) {
      *(pg + 1) = *(p + 3);
    }
    */
  }

  printf("Size of image: %d\n", img_size);
  printf("Width: %d\n", width);
  printf("Height: %d\n", height);
  printf("Channels: %d\n", channels);
  printf("Gray image size: %d\n", gray_img_size);

  char *buf = "{"; // open bracket

  for(int i=0; i < gray_img_size; i++) {
    uint8_t f = gray_img[i];
    asprintf(&buf,"%s%i",buf,f);
    if(i!=gray_img_size-1) { // Add a comma , after each but skip the last
      asprintf(&buf,"%s,",buf);
    }
  }

  asprintf(&buf,"%s}",buf); // closing backet

  printf("%s\n",buf);

  stbi_image_free(img);

  //printf(&imgWidth);

  return 0;
}