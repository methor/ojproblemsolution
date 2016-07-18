#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef enum { false, true } bool;

#define LEFT(y) ((y) * 2 + 1)
#define RIGHT(y) ((y) * 2 + 2)
#define PARENT(y) (((y) - 1) / 2)

void swap(int *p1, int *p2)
{
    int tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

struct heap {
    int *arr;
    int size;
    int cap;
    bool max;
};



void heapify(struct heap *h, int i)
{
    int *arr = h->arr;
    int size = h->size;
    bool max = h->max;

    int l = LEFT(i);
    int r = RIGHT(i);
    int largest = i;

    if (l < size)
    {
       if (max && l < h->size && arr[l] > arr[i]) 
           largest = l;
       else if (!max && l < h->size && arr[l] < arr[i])
           largest = l;
    }
    if (r < size)
    {
        if (max && r < h->size && arr[r] > arr[largest])
            largest = r;
        else if (!max && r < h->size && arr[r] < arr[largest])
            largest = r;
    }
    if (largest != i)
    {
        swap(arr + i, arr + largest);
        heapify(h, largest);
    }
}

void build_heap(struct heap *h)
{
    int i;
    for (i =PARENT(h->size - 1); i >= 0; i--)
        heapify(h, i);
}

int heap_extract(struct heap *h)
{
    int result = h->arr[0];
    swap(h->arr, h->arr + h->size - 1);
    h->size--;
    if (h->size > 0)
        heapify(h, 0);
    return result;
}

void heap_insert(struct heap *h, int i)
{
    if (h->size >= h->cap)
    {
        int cap = (h->size * 2 > 50) ? h->size * 2 : 50;
        int *arr = (int *)malloc(cap * sizeof(int));
        memcpy(arr, h->arr, h->size * sizeof(int));
        free(h->arr);
        h->arr = arr;
        h->cap = cap;
    }

    h->arr[h->size++] = i;
    int current = h->size - 1;
    int parent = PARENT(current);
    while (current != 0)
    {
        if (h->max)
        {
            int largest = parent;
            if (LEFT(parent) < h->size && h->arr[parent] < h->arr[LEFT(parent)])
                largest = LEFT(parent);
            if (RIGHT(parent) < h->size && h->arr[largest] < h->arr[RIGHT(parent)])
                largest = RIGHT(parent);

            if (largest == parent)
                break;
            else
                swap(h->arr + largest, h->arr + parent);
        }
        else
        {
            int smallest = parent;
            if (LEFT(parent) < h->size && h->arr[parent] > h->arr[LEFT(parent)])
                smallest = LEFT(parent);
            if (RIGHT(parent) < h->size && h->arr[smallest] > h->arr[RIGHT(parent)])
                smallest = RIGHT(parent);

            if (smallest == parent)
                break;
            else
                swap(h->arr + smallest, h->arr + parent);
        }
        current = parent;
        parent = PARENT(current);
    }



}

int get_head(struct heap *h)
{
    return h->arr[0];
}

int main()
{
    struct heap maxh, minh;
    maxh.arr = (int *)malloc(50 * sizeof(int));
    maxh.size = 0;
    maxh.cap = 50;
    maxh.max = true;

    minh.arr = (int *)malloc(50 * sizeof(int));
    minh.size = 0;
    minh.cap = 50;
    minh.max = false;

    /*FILE *fp = fopen("test.stdin", "r");*/
    /*FILE *fpo = fopen("test.myout", "w");*/

    int i;
    while ((fscanf(stdin, "%d ", &i)) > 0)
    {
        if (maxh.size == 0)
            heap_insert(&maxh, i);
        else if (minh.size > maxh.size)
        {
            int minhead = get_head(&minh);
            if (minhead < i)
            {
                heap_extract(&minh);
                heap_insert(&minh, i);
                heap_insert(&maxh, minhead);
            }
            else

            heap_insert(&maxh, i);
        }
        else if (minh.size < maxh.size)
        {
            int maxhead = get_head(&maxh);
            if (maxhead > i)
            {
                heap_extract(&maxh);
                heap_insert(&maxh, i);
                heap_insert(&minh, maxhead);
            }
            else
                heap_insert(&minh, i);
        }
        else
        {
            if (i < get_head(&minh))
                heap_insert(&maxh, i);
            else
                heap_insert(&minh, i);
        }
       
        if (minh.size <= maxh.size)
            fprintf(stdout, "%d ", get_head(&maxh));
        else
            fprintf(stdout, "%d ", get_head(&minh));
    }

    /*fclose(fp);*/
    /*fclose(fpo);*/

    return 0;
}
        







