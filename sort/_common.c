#ifndef _COMMON_C
#define _COMMON_C

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

#endif // !_COMMON_C