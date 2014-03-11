#include "../xrope.h"

#include <stdio.h>

int testng;

#define test(x) do {                            \
    int r__ = (x);                              \
    if (! r__) {                                \
      puts("test fail: " #x);                   \
      testng = 1;                               \
    } else {                                    \
      puts("test success: " #x);                \
    }                                           \
  } while (0)

void
run()
{
  char text[] = "Hello my name is Yuichi";
  xrope *x, *y, *z, *w, *v;
  int i;

  x = xr_new_imbed(text + 15, 1);
  y = xr_new_imbed(text + 16, 7);
  z = xr_cat(x, y);
  XROPE_DECREF(x);
  XROPE_DECREF(y);
  x = xr_new_imbed(text + 9, 2);
  y = xr_new_imbed(text + 11, 4);
  w = xr_cat(x, y);
  XROPE_DECREF(x);
  XROPE_DECREF(y);
  x = xr_new_imbed(text, 6);
  y = xr_new_imbed(text + 6, 3);
  v = xr_cat(x, y);
  XROPE_DECREF(x);
  XROPE_DECREF(y);
  y = xr_cat(w, z);
  x = xr_cat(v, y);
  XROPE_DECREF(y);
  XROPE_DECREF(z);
  XROPE_DECREF(w);
  XROPE_DECREF(v);

  test(xr_len(x) == strlen(text));

  test(xr_at(x, 3) == text[3]);
  test(xr_at(x, 10) == text[10]);
  test(xr_at(x, 15) == text[15]);

  test(strcmp(xr_cstr(x), text) == 0);
  test(xr_cstr(x) == xr_cstr(x)); /* properly cached? */

  y = xr_sub(x, 13, xr_len(x));
  test(strcmp(xr_cstr(y), text + 13) == 0);
  XROPE_DECREF(x);
  XROPE_DECREF(y);

  x = xr_new_imbed(text + 15, 1);
  for (i = 0; i < 10000000; ++i) {
    y = x;
    z = xr_new_imbed(text + 15, 1);
    x = xr_cat(y, z);
    XROPE_DECREF(y);
    XROPE_DECREF(z);
  }
  test(strlen(xr_cstr(x)) == 10000001);
  XROPE_DECREF(x);
}

int
main()
{
  puts("----test started...----");

  run();

  if (testng) {
    puts("----test failed---");
    return 1;
  }
  else {
    puts("----test successfully finished----");
    return 0;
  }
}
