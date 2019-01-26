#include "stringbuilder.h"
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static const size_t stringbuilder_default_size = 32;

struct stringbuilder {
  char *buffer;
  size_t allocated;
  size_t length;
};

stringbuilder_t *sb_create(void) {
  stringbuilder_t *sb = calloc(1, sizeof(stringbuilder_t));

  sb->buffer = malloc(stringbuilder_default_size);
  sb->buffer[0] = '\0';
  sb->allocated = stringbuilder_default_size;
  sb->length = 0;

  return sb;
}

void sb_destroy(stringbuilder_t *sb) {
  if (sb == NULL) return;

  free(sb->buffer);
  free(sb);
}

static void sb_ensure_space(stringbuilder_t *sb, size_t space) {
  if (sb == NULL || space == 0) return;

  if (sb->allocated >= sb->length + space + 1) return;

  while (sb->allocated < sb->length + space + 1) {
    sb->allocated <<= 1;
    if (sb->allocated == 0) {
        sb->allocated--;
    }
  }

  sb->buffer = realloc(sb->buffer, sb->allocated);
}

void sb_char(stringbuilder_t *sb, char c) {
  sb_ensure_space(sb, 1);
  sb->buffer[sb->length] = c;
  ++sb->length;
  sb->buffer[sb->length] = '\0';
}

void sb_str(stringbuilder_t *sb, const char *str) {
  sb_strl(sb, str, 0);
}

void sb_strl(stringbuilder_t *sb, const char *str, size_t len) {
  if (len == 0) {
    len = strlen(str);
  }
  if (len == 0) return;

  sb_ensure_space(sb, len);
  memcpy(sb->buffer + sb->length, str, len);
  sb->length += len;
  sb->buffer[sb->length] = '\0';
}

void sb_printf(stringbuilder_t *sb, const char *format, ...) {
  va_list va;

  va_start(va, format);
  size_t len = vsnprintf(NULL, 0, format, va);
  va_end(va);

  sb_ensure_space(sb, len);

  va_start(va, format);
  vsnprintf(sb->buffer + sb->length, len + 1, format, va);
  va_end(va);

  sb->length += len;
  sb->buffer[sb->length] = '\0';
}

void sb_clear(stringbuilder_t *sb) {
  sb->length = 0;
  sb->buffer[0] = '\0';
}

size_t sb_len(const stringbuilder_t *sb) {
  return sb->length;
}

const char *sb_get(const stringbuilder_t *sb) {
  return sb->buffer;
}
