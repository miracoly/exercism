#include "series.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

slices_t slices(char* input_text, unsigned int substring_length) {
  if (!input_text || substring_length == 0) return (slices_t){0};
  const size_t len = strlen(input_text);
  if (len == 0 || len < substring_length) return (slices_t){0};

  size_t substring_count = len - substring_length + 1;
  char** sub = malloc(sizeof *sub * substring_count);
  if (!sub) return (slices_t){0};

  size_t built = 0;
  for (size_t i = 0; i < substring_count; ++i) {
    sub[i] = calloc(substring_length + 1, 1);
    if (!sub[i]) goto fail;

    memcpy(sub[i], input_text + i, substring_length);
    built++;
  }
  return (slices_t){
      .substring_count = substring_count,
      .substring = sub,
  };

fail:
  for (size_t i = 0; i < built; ++i) {
    free(sub[i]);
  }
  free(sub);

  return (slices_t){0};
}
