#include <stdio.h>
#include <stdlib.h>

struct FlexString {
  char *data_ptr;
  unsigned int str_len;
  unsigned int capacity;
};

void init_string(struct FlexString *fs) {
  fs->capacity = 4;
  fs->str_len = 0;
  fs->data_ptr = malloc(4);
}

void free_string(struct FlexString *fs) { 
  free(fs->data_ptr); 
}

void append_char(struct FlexString *fs, char ch) {
  if (fs->str_len == fs->capacity) {
    fs->capacity *= 2;
    char *new_buffer = malloc(fs->capacity);

    for (unsigned int i = 0; i < fs->str_len; i++) {
      new_buffer[i] = fs->data_ptr[i];
    }

    free(fs->data_ptr);
    fs->data_ptr = new_buffer;
  }

  fs->data_ptr[fs->str_len] = ch;
  fs->str_len++;
}

void clear_string(struct FlexString *fs) { 
  fs->str_len = 0; 
}

/* Updated to print just the raw string content */
void print_string(struct FlexString *fs) {
  for (unsigned int i = 0; i < fs->str_len; i++) {
    printf("%c", fs->data_ptr[i]);
  }
  printf("\n");
}

/* Updated to match your specific multi-line requirement */
void print_string_info(struct FlexString *fs) {
  printf("String: \"");
  for (unsigned int i = 0; i < fs->str_len; i++) {
    printf("%c", fs->data_ptr[i]);
  }
  printf("\"\n");
  printf("Length: %u\n", fs->str_len);
  printf("Capacity: %u\n", fs->capacity);
}

void copy_string(struct FlexString *dest, struct FlexString *src) {
  clear_string(dest);
  for (unsigned int i = 0; i < src->str_len; i++) {
    append_char(dest, src->data_ptr[i]);
  }
}

void concatenate_strings(struct FlexString *res, struct FlexString *s1, struct FlexString *s2) {
  struct FlexString temp_str;
  init_string(&temp_str);

  for (unsigned int i = 0; i < s1->str_len; i++) {
    append_char(&temp_str, s1->data_ptr[i]);
  }

  for (unsigned int i = 0; i < s2->str_len; i++) {
    append_char(&temp_str, s2->data_ptr[i]);
  }

  free(res->data_ptr);
  res->data_ptr = temp_str.data_ptr;
  res->str_len = temp_str.str_len;
  res->capacity = temp_str.capacity;
}

int main() {
  struct FlexString s_a, s_b, s_c, s_d;

  init_string(&s_a);
  init_string(&s_b);
  init_string(&s_c);
  init_string(&s_d);

  char command;

  while (1) {
    if (scanf(" %c", &command) != 1) {
      break;
    }

    if (command == 'q') {
      break;
    }

    if (command == 'r' || command == 'a') {
      char dest_id;
      scanf(" %c", &dest_id);

      struct FlexString *current_str;

      if (dest_id == 'a') current_str = &s_a;
      else if (dest_id == 'b') current_str = &s_b;
      else if (dest_id == 'c') current_str = &s_c;
      else current_str = &s_d;

      int next_char;
      while ((next_char = getchar()) != EOF) {
        if (next_char != ' ' && next_char != '\t' && next_char != '\n' && next_char != '\r') {
          break;
        }
      }

      if (next_char == '"') {
        if (command == 'r') clear_string(current_str);
        int input_char;
        while ((input_char = getchar()) != EOF) {
          if (input_char == '"') break;
          append_char(current_str, input_char);
        }
      } else if (next_char != EOF) {
        if (command == 'r') clear_string(current_str);
        append_char(current_str, next_char);
        int input_char;
        while ((input_char = getchar()) != EOF) {
          if (input_char == ' ' || input_char == '\t' || input_char == '\n' || input_char == '\r')
            break;
          append_char(current_str, input_char);
        }
      }
    }

    else if (command == 'p') {
      char dest_id;
      scanf(" %c", &dest_id);

      if (dest_id == 'a') print_string(&s_a);
      else if (dest_id == 'b') print_string(&s_b);
      else if (dest_id == 'c') print_string(&s_c);
      else print_string(&s_d);
    }

    else if (command == 'd') {
      char dest_id;
      scanf(" %c", &dest_id);

      if (dest_id == 'a') print_string_info(&s_a);
      else if (dest_id == 'b') print_string_info(&s_b);
      else if (dest_id == 'c') print_string_info(&s_c);
      else print_string_info(&s_d);
    }

    else if (command == 'c') {
      char res_id, src1_id, src2_id;
      scanf(" %c %c %c", &res_id, &src1_id, &src2_id);

      struct FlexString *res_ptr, *ptr1, *ptr2;

      if (res_id == 'a') res_ptr = &s_a;
      else if (res_id == 'b') res_ptr = &s_b;
      else if (res_id == 'c') res_ptr = &s_c;
      else res_ptr = &s_d;

      if (src1_id == 'a') ptr1 = &s_a;
      else if (src1_id == 'b') ptr1 = &s_b;
      else if (src1_id == 'c') ptr1 = &s_c;
      else ptr1 = &s_d;

      if (src2_id == 'a') ptr2 = &s_a;
      else if (src2_id == 'b') ptr2 = &s_b;
      else if (src2_id == 'c') ptr2 = &s_c;
      else ptr2 = &s_d;

      concatenate_strings(res_ptr, ptr1, ptr2);
    }
  }

  free_string(&s_a);
  free_string(&s_b);
  free_string(&s_c);
  free_string(&s_d);

  return 0;
}