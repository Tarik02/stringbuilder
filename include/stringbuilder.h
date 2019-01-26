#ifndef STRINGBUILDER_H
#define STRINGBUILDER_H

#include <stddef.h>

#if defined(_MSC_VER)
    //  Microsoft 
    #define SB_EXPORT __declspec(dllexport)
    #define SB_IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
    //  GCC
    #define SB_EXPORT __attribute__((visibility("default")))
    #define SB_IMPORT
#else
    //  do nothing and hope for the best?
    #define SB_EXPORT
    #define SB_IMPORT
    #pragma warning Unknown dynamic link import/export semantics.
#endif

typedef struct stringbuilder stringbuilder_t;

SB_EXPORT stringbuilder_t *sb_create(void);
SB_EXPORT void sb_destroy(stringbuilder_t *sb);

SB_EXPORT void sb_char(stringbuilder_t *sb, char c);
SB_EXPORT void sb_str(stringbuilder_t *sb, const char *str);
SB_EXPORT void sb_strl(stringbuilder_t *sb, const char *str, size_t len);
SB_EXPORT void sb_printf(stringbuilder_t *sb, const char *format, ...);

SB_EXPORT void sb_clear(stringbuilder_t *sb);

SB_EXPORT size_t sb_len(const stringbuilder_t *sb);
SB_EXPORT const char *sb_get(const stringbuilder_t *sb);

#undef SB_EXPORT
#undef SB_IMPORT

#endif // STRINGBUILDER_H
