 #include <stdlib.h>
 #include <string.h>
 #include <stdio.h>
 #define N 100
 #define M 30
 int main(int argc, char* argv[]) {
    char a[N][M];
    int n, i;
    scanf("%d", &n);
    for (i=0; i<n; i++)
       scanf("%s", &a[i]);
    qsort(a, n, sizeof(a[0]), strcmp);
    for (i=0; i<n; i++)
       printf("%s\n", a[i]);
    return 0;
 }