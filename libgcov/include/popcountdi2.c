#include "popcountdi2.h"

const UQItype __popcount_tab[256] =
{
    0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4,1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
    1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
    1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
    2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
    1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
    2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
    2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
    3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,4,5,5,6,5,6,6,7,5,6,6,7,6,7,7,8
};

int __popcountdi2 (UDWtype x)
{
  /* Force table lookup on targets like AVR and RL78 which only
     pretend they have LIBGCC2_UNITS_PER_WORD 4, but actually
     have 1, and other small word targets.  */
#if __SIZEOF_INT__ > 2 && defined (POPCOUNTCST) && __CHAR_BIT__ == 8
  const DWunion uu = {.ll = x};
  UWtype x1 = uu.s.low, x2 = uu.s.high;
  x1 = x1 - ((x1 >> 1) & POPCOUNTCST (0x55));
  x2 = x2 - ((x2 >> 1) & POPCOUNTCST (0x55));
  x1 = (x1 & POPCOUNTCST (0x33)) + ((x1 >> 2) & POPCOUNTCST (0x33));
  x2 = (x2 & POPCOUNTCST (0x33)) + ((x2 >> 2) & POPCOUNTCST (0x33));
  x1 = (x1 + (x1 >> 4)) & POPCOUNTCST (0x0F);
  x2 = (x2 + (x2 >> 4)) & POPCOUNTCST (0x0F);
  x1 += x2;
  return (x1 * POPCOUNTCST (0x01)) >> (W_TYPE_SIZE - __CHAR_BIT__);
#else
  int i, ret = 0;

  for (i = 0; i < 2*W_TYPE_SIZE; i += 8)
    ret += __popcount_tab[(x >> i) & 0xff];

  return ret;
#endif
}
