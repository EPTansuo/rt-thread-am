#include <klib.h>
#include <rtthread.h>


//The strchr() function returns a pointer to the first occurrence of the character c in the string s.
char *strchr(const char *s, int c) {
  //assert(0);
  do{
    if(*s == c)
      return (char*)s;
  }while(*(s++));

  return NULL;
}

//The strrchr() function returns a pointer to the last occurrence of the character c in the string s.
char *strrchr(const char *s, int c) {
  //assert(0);
  char *ret = NULL;
  do{
    if(*s == c)
      ret = (char*)s;
  }while(*(s++));
  return ret;
}

char *strstr(const char *haystack, const char *needle) {
  return rt_strstr(haystack, needle);
}

long strtol(const char *restrict nptr, char **restrict endptr, int base) {
  assert(0);
}

char *strncat(char *restrict dst, const char *restrict src, size_t sz) {
  assert(0);
}
