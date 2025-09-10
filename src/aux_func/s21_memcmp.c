#include "../s21_matrix.h"

int s21_memcmp(const void *str1, const void *str2, int n) {
  int test = 0;
  const unsigned char *ptr1 = str1;
  const unsigned char *ptr2 = str2;
  int flag = 1;

  if (str1 == NULL && str2 == NULL)
    test = 0;

  else if (str1 == NULL)
    test = -1;

  else if (str2 == NULL)
    test = 1;

  else if (n == 0)
    test = 0;

  else {
    while (n-- && flag) {
      if (*ptr1 != *ptr2) {
        test = (*ptr1 < *ptr2) ? -1 : 1;
        flag = 0;
      }
      ptr1++;
      ptr2++;
    }
  }

  return test;
}
