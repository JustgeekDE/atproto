#include "dce_common.h"
#include "dce_utils.h"

int dce_ishex(char c)
{
    return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F');
}

char dce_htoi(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    return -1;
}

int dce_expect_number(const char** buf, size_t *psize, int def_val)
{
    size_t s = *psize;
    if (s == 0)
        return def_val;
    
    int result = 0;
    int i;
    const char* b = *buf;
    for (i = 0; i < s; ++i, ++b)
    {
        int x = *b - '0';
        if (x < 0 || x > 9)
            break;
        result = result * 10 + x;
    }
    
    if (i == 0)
        return def_val;
    
    *psize -= i;
    *buf += i;
    return result;
}

void dce_itoa(int val, char* buf, size_t bufsize, size_t* outsize)
{
    char negative = val < 0;
    int digits[10];
    int i;
    for (i = 0; val > 0; ++i)
    {
        int div = val / 10;
        digits[i] = val - div * 10;
        val = div;
    }
    if (bufsize < i + negative)
    {
        *outsize = 0;
        return;
    }
    
    char* start = buf;
    if (negative)
    {
        *buf = '-';
        ++buf;
    }
    for (; i>=0; --i, ++buf)
    {
        *buf = '0' + digits[i];
    }
    *outsize = buf - start;
}

void dce_itoa_zeropad(int val, char* buf, size_t bufsize)
{
    int digits[10];
    int i;
    for (i = 0; val > 0; ++i)
    {
        int div = val / 10;
        digits[i] = val - div * 10;
        val = div;
    }
    
    for (int j = 0; j < bufsize - i; ++j, ++buf)
        *buf = '0';
    for (; i>=0; --i, ++buf)
        *buf = '0' + digits[i];
}
