#include <stdio.h>

float add_list(float array[], int lim);

int main()
{
    float list[] = {1, 2, 3, 4, 5, 6};
    printf("%.1f", add_list(list, 5));

    return 0;
}

/* add_list: takes a list of real numbers and returns its sum upto a specified size */
float add_list(float array[], int lim)
{
    if (lim == 0)
        return 0;
    return array[lim-1] + add_list(array, lim-1);
}