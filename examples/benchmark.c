#include <stdint.h>
#include <stdio.h>

struct xoshiro128_plus_enhanced_s {
  uint32_t a;
  uint32_t b;
  uint32_t c;
  uint32_t d;
  uint32_t e;
};

uint32_t xoshiro128_plus_enhanced(struct xoshiro128_plus_enhanced_s *s) {
  uint32_t block = s->b + s->e;

  s->a++;

  if (s->a < 1) {
    s->c += s->e;
    s->d ^= s->b;
    s->b += s->c;
    s->e ^= s->d;
    return block;
  }

  s->b = ((s->b << 17) | (s->b >> 15)) ^ s->d;
  s->d += 1111111111;
  s->e = (block << 13) | (block >> 19);
  return block;
}

void shell_sort_enhanced(size_t elements_count, uint32_t *elements) {
  uint32_t element;
  size_t gap = elements_count;
  size_t i;
  size_t j;

  while (gap > 15) {
    gap = (gap >> 5) + (gap >> 3);
    i = gap;

    while (i < elements_count) {
      element = elements[i];
      j = i;

      while (
        j >= gap &&
        elements[j - gap] > element
      ) {
        elements[j] = elements[j - gap];
        j -= gap;
      }

      elements[j] = element;
      i++;
    }
  }

  i = 1;
  gap = 0;

  while (i < elements_count) {
    element = elements[i];
    j = i;

    while (
      j > 0 &&
      elements[gap] > element
    ) {
      elements[j] = elements[gap];
      j = gap;
      gap--;
    }

    elements[j] = element;
    gap = i;
    i++;
  }
}

char bsearch_enhanced(size_t low, size_t high, uint32_t *haystack,
                      uint32_t needle, size_t *position) {
  size_t gap;

  if (haystack[low] < needle) {
    if (haystack[high] < needle) {
      return 0;
    }

    if (haystack[high] == needle) {
      *position = high;
      return 1;
    }

    high--;
    gap = high - low;

    if (gap > 2) {
      while (haystack[high] > needle) {
        while (haystack[high] > needle) {
          high -= gap >> 1;
          gap = (gap >> 1) + 1;
        }

        while (haystack[high] < needle) {
          high += gap >> 1;
          gap = (gap >> 1) + 1;
        }

        if (gap < 3) {
          break;
        }
      }
    }

    while (haystack[high] > needle) {
      high--;
    }

    if (haystack[high] == needle) {
      *position = high;
      return 1;
    }

    return 0;
  }

  if (haystack[low] == needle) {
    *position = low;
    return 1;
  }

  return 0;
}

int main(void) {
  struct xoshiro128_plus_enhanced_s s = {
    .a = 0,
    .b = 0,
    .c = 0,
    .d = 0,
    .e = 0
  };
  uint32_t haystack[1111111];
  size_t position;
  uint32_t result = 0;
  uint32_t i = 0;
  uint32_t j = 1111111;

  while (i < 1111111) {
    haystack[i] = xoshiro128_plus_enhanced(&s);
    i++;
  }

  shell_sort_enhanced(1111111, haystack);
  i = 0;

  while (i < 1111111) {
    if (bsearch_enhanced(0, 1111110, haystack, haystack[i], &position) > 0) {
      result += haystack[i] + position;
    }

    j--;

    if (bsearch_enhanced(0, j, haystack, haystack[i], &position) > 0) {
      result += haystack[i] + position;
    }

    i++;
  }

  i = 0;

  while (i < 1111111) {
    if (bsearch_enhanced(0, xoshiro128_plus_enhanced(&s) & 1048575, haystack,
                         haystack[i], &position) > 0) {
      result += haystack[i] + position;
    }

    i++;
  }

  haystack[0] = 0;
  haystack[1] = 1;
  i = 2;

  while (i < 1111111) {
    haystack[i] = 2;
    i++;
  }

  i = 1111111;

  while (i > 0) {
    i--;

    if (bsearch_enhanced(0, i, haystack, 1, &position) > 0) {
      result += haystack[i] + position;
    }
  }

  printf("The blocking result is %u.\n", result);
  return 0;
}
