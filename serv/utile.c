#include "utile.h"

int append(int *list, int to_add, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (list[i] == to_add)
            return i;
        else if (list[i] < 0)
        {
            list[i] = to_add;
            return i;
        }
    }
    return -1;
}
