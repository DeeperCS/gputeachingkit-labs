
#include "stdio.h"
#include "assert.h"
#include "limits.h"
#include "stdlib.h"
#include "string.h"
#include "sys/stat.h"

static char base_dir[] = "./TextHistogram/Dataset/";
const size_t NUM_BINS  = 128;

static void _mkdir(const char *dir) {
  char tmp[PATH_MAX];
  char *p = NULL;
  size_t len;

  snprintf(tmp, sizeof(tmp), "%s", dir);
  len = strlen(tmp);
  if (tmp[len - 1] == '/')
    tmp[len - 1] = 0;
  for (p = tmp + 1; *p; p++)
    if (*p == '/') {
      *p = 0;
      mkdir(tmp, S_IRWXU);
      *p = '/';
    }
  mkdir(tmp, S_IRWXU);
}

static void compute(unsigned int *bins, const char *input, int num) {
  for (int i = 0; i < num; ++i) {
    ++bins[(unsigned int)input[i]];
  }
}

static char *generate_data(size_t n) {
  char *data = (char *)malloc(n + 1);
  for (unsigned int i = 0; i < n; i++) {
    data[i] = (rand() % (128 - 32)) + 32; // random printable character
  }
  data[n] = 0; // null-terminated
  return data;
}

static char *strjoin(const char *s1, const char *s2) {
  char *result = (char *)malloc(strlen(s1) + strlen(s2) + 1);
  strcpy(result, s1);
  strcat(result, s2);
  return result;
}

static void write_data_str(char *file_name, const char *data, int num) {
  FILE *handle = fopen(file_name, "w");
  for (int ii = 0; ii < num; ii++) {
    fprintf(handle, "%c", *data++);
  }
  fflush(handle);
  fclose(handle);
}

static void write_data_int(char *file_name, unsigned int *data, int num) {
  FILE *handle = fopen(file_name, "w");
  fprintf(handle, "%d", num);
  for (int ii = 0; ii < num; ii++) {
    fprintf(handle, "\n%d", *data++);
  }
  fflush(handle);
  fclose(handle);
}

static void create_dataset_fixed(int datasetNum, const char *str) {
  char dir_name[PATH_MAX];
  sprintf(dir_name, "%s/%d", base_dir, datasetNum);
  _mkdir(dir_name);

  char *input_file_name  = strjoin(dir_name, "/input.txt");
  char *output_file_name = strjoin(dir_name, "/output.raw");

  unsigned int *output_data =
      (unsigned int *)calloc(NUM_BINS, sizeof(unsigned int));

  compute(output_data, str, strlen(str));

  write_data_str(input_file_name, str, strlen(str));
  write_data_int(output_file_name, output_data, NUM_BINS);

  free(output_data);
  free(input_file_name);
  free(output_file_name);
}

static void create_dataset_random(int datasetNum, size_t input_length) {
  char dir_name[PATH_MAX];
  sprintf(dir_name, "%s/%d", base_dir, datasetNum);
  _mkdir(dir_name);

  char *input_file_name  = strjoin(dir_name, "/input.txt");
  char *output_file_name = strjoin(dir_name, "/output.raw");

  char *str = generate_data(input_length);
  unsigned int *output_data =
      (unsigned int *)calloc(NUM_BINS, sizeof(unsigned int));

  compute(output_data, str, input_length);

  write_data_str(input_file_name, str, input_length);
  write_data_int(output_file_name, output_data, NUM_BINS);

  free(str);
  free(output_data);
  free(input_file_name);
  free(output_file_name);
}

int main() {
  create_dataset_fixed(0, "the quick brown fox jumps over the lazy dog");
  create_dataset_fixed(1, "gpu teaching kit - accelerated computing");
  create_dataset_random(2, 16);
  create_dataset_random(3, 513);
  create_dataset_random(4, 511);
  create_dataset_random(5, 1);
  return 0;
}