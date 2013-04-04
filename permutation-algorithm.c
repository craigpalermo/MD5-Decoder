#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int i, n, m;
    int *a;
    char s[] = "ABCDEFGHIJKLMNOPabcdefghijklmnopqrstuvwxyz0123456789";

    n = sizeof s - 1;
    m = 3;

    a = malloc(m * sizeof *a);
    if (!a) abort();
    for (i = 0; i < m; ++i)
        a[i] = 0;

    do {
        for (i = m - 1; i >= 0; --i)
            putchar(s[a[i]]);
        putchar('\n');

        for (i = 0; i < m; ++i)
            if (++a[i] < n) break; else a[i] = 0;
    } while (i < m);

    putchar('\n');
    free(a);

    return 0;
}
