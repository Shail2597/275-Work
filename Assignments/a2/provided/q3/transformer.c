#include <stdio.h>
#include <stdlib.h>

struct ImgDot {
  int r;
  int g;
  int b;
};

/* Read image from stdin */
struct ImgDot *load_picture(int *width, int *height) {
  char header_fmt[3];

  if (scanf("%2s", header_fmt) != 1) {
    return NULL;
  }

  if (header_fmt[0] != 'P' || header_fmt[1] != '3') {
    return NULL;
  }

  if (scanf("%d %d", width, height) != 2) {
    return NULL;
  }

  int color_max;
  if (scanf("%d", &color_max) != 1) {
    return NULL;
  }

  struct ImgDot *pic_data = malloc((*width) * (*height) * sizeof(struct ImgDot));
  if (pic_data == NULL) {
    return NULL;
  }

  for (int idx = 0; idx < (*width) * (*height); idx++) {
    if (scanf("%d %d %d", &pic_data[idx].r, &pic_data[idx].g, &pic_data[idx].b) != 3) {
      free(pic_data);
      return NULL;
    }
  }

  return pic_data;
}

/* Apply sepia filter */
void apply_sepia_effect(struct ImgDot *pic_data, int width, int height) {
  int num_pixels = width * height;

  for (int idx = 0; idx < num_pixels; idx++) {
    int oldR = pic_data[idx].r;
    int oldG = pic_data[idx].g;
    int oldB = pic_data[idx].b;

    int new_r = (int)(oldR * 0.393 + oldG * 0.769 + oldB * 0.189);
    int new_g = (int)(oldR * 0.349 + oldG * 0.686 + oldB * 0.168);
    int new_b = (int)(oldR * 0.272 + oldG * 0.534 + oldB * 0.131);

    if (new_r > 255)
      new_r = 255;
    if (new_g > 255)
      new_g = 255;
    if (new_b > 255)
      new_b = 255;

    pic_data[idx].r = new_r;
    pic_data[idx].g = new_g;
    pic_data[idx].b = new_b;
  }
}

/* Flip image horizontally */
void reverse_horizontally(struct ImgDot *pic_data, int width, int height) {
  for (int r_idx = 0; r_idx < height; r_idx++) {
    for (int c_idx = 0; c_idx < width / 2; c_idx++) {

      int left_pos = r_idx * width + c_idx;
      int right_pos = r_idx * width + (width - 1 - c_idx);

      struct ImgDot swap_temp = pic_data[left_pos];
      pic_data[left_pos] = pic_data[right_pos];
      pic_data[right_pos] = swap_temp;
    }
  }
}

/* Print image */
void output_picture(struct ImgDot *pic_data, int width, int height) {
  printf("P3\n");
  printf("%d %d\n", width, height);
  printf("255\n");

  for (int r_idx = 0; r_idx < height; r_idx++) {
    for (int c_idx = 0; c_idx < width; c_idx++) {
      int pos = r_idx * width + c_idx;
      if (c_idx > 0)
        printf(" ");
      printf("%d %d %d", pic_data[pos].r, pic_data[pos].g, pic_data[pos].b);
    }
    printf(" \n");
  }
}

int main(int argc, char *argv[]) {

  int do_flip = 0;
  int do_sepia = 0;

  for (int idx = 1; idx < argc; idx++) {
    if (argv[idx][0] == '-' && argv[idx][1] == 'f') {
      do_flip = 1;
    } else if (argv[idx][0] == '-' && argv[idx][1] == 's') {
      do_sepia = 1;
    }
  }

  int width, height;
  struct ImgDot *picture = load_picture(&width, &height);

  if (picture == NULL) {
    return 1;
  }

  if (do_sepia) {
    apply_sepia_effect(picture, width, height);
  }

  if (do_flip) {
    reverse_horizontally(picture, width, height);
  }

  output_picture(picture, width, height);

  free(picture);

  return 0;
}