#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

/*#define FOUT 1*/

int comparint(const void *p1, const void *p2)
{
    int i1 = *(int const *)p1;
    int i2 = *(int const *)p2;
    if (i1 < i2)
        return -1;
    else if (i1 == i2)
        return 0;
    else
        return 1;
}

void generate(int size)
{
    FILE *fp = fopen("test.in","w");

    int N = RAND_MAX / 10;
    int M = size * 2;
    int in, im, i, j;

    im = 0, i = 0, j = 0;
    int *arr1 = (int *)malloc(size * sizeof(int));
    int *arr2 = (int *)malloc(size * sizeof(int));

    srand(time(NULL));

    for (in = 0; in < N && im < M; ++in) {
        int rn = N - in;
        int rm = M - im;
        if (rand() % rn < rm)    
        {
            /* Take it */
            if (i < size - 1 && (rand() % 2 == 0 || j >= size - 1))
            {
                arr1[i++] = in + 1; /* +1 since your range begins from 1 */
            }
            else
                arr2[j++] = in + 1;
            im++;
        }

    }

    assert(im == M);
    fprintf(fp, "%d\n", size);
    for (i = 0; i < size; i++)
    {
        fprintf(fp, "%d ", arr1[i]);
    }
    fprintf(fp, "\n");
    for (i = 0; i < size; i++)
    {
        fprintf(fp, "%d ", arr2[i]);
    }

    fclose(fp);
}

int main()
{
#ifdef GEN
    generate(1000000);
#endif

    int size, i = 0;
    int *arr1, *arr2;

#ifdef FOUT
    FILE *fp = fopen("test.in", "r");
    FILE *fpo = fopen("test.out", "w");
    fscanf(fp, "%d ", &size);
    arr1 = (int *)malloc(size * sizeof(int));
    arr2 = (int *)malloc(size * sizeof(int));
    while (i < size && (fscanf(fp, "%d ", &arr1[i])) > 0)
    {
        i++;
    }
    i = 0;
    while ((fscanf(fp, "%d ", &arr2[i])) > 0)
    {
        i++;
    }
    fclose(fp);
#else
    fscanf(stdin, "%d ", &size);
    arr1 = (int *)malloc(size * sizeof(int));
    arr2 = (int *)malloc(size * sizeof(int));
    while (i < size && (fscanf(stdin, "%d ", &arr1[i])) > 0)
    {
        i++;
    }
    i = 0;
    while ((fscanf(stdin, "%d ", &arr2[i])) > 0)
    {
        i++;
    }
#endif
#ifdef LOGN
    int i1 = 0, i2 = 0;
    for (i = 0; i < size - 1; i++)
    {
        if (arr1[i1] < arr2[i2])
        {
            i1++;
        }
        else
        {
            i2++;
        }
    }
    if (arr1[i1] < arr2[i2])
        printf("%d",arr1[i1]);
    else
        printf("%d",arr2[i2]);
#else
    int b1 = 0, e1 = size - 1, b2 = 0, e2 = size - 1;

    while (size != 1)
    {
        int mid = ((size % 2 == 0) ? size / 2 - 1 : size / 2);
        if (arr1[b1 + mid] < arr2[b2 + mid])
        {
            b1 += mid;
            e2 = b2 + mid;
            if (size % 2 == 0)
            {
                b1++;
            }
        }
        else
        {
            e1 = b1 + mid;
            b2 += mid;
            if (size % 2 == 0)
            {
                b2++;
            }
        }
        size = e1 - b1 + 1;
    }

    if (arr1[b1] < arr2[b2])
    {
#ifdef FOUT
        fprintf(fpo, "%d", arr1[b1]);
        fclose(fpo);
#else
        printf("%d", arr1[b1]);
#endif
    }
    else
    {
#ifdef FOUT
        fprintf(fpo, "%d", arr2[b2]);
        fclose(fpo);
#else
        printf("%d", arr2[b2]);
#endif
    }
#endif
}
