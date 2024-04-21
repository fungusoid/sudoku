#include <stdio.h>

int puzzle[9 * 9] = {
    0, 0, 0, 6, 0, 4, 0, 0, 7,
    0, 4, 0, 0, 9, 0, 0, 0, 0,
    9, 0, 0, 0, 0, 0, 0, 0, 8,
    0, 0, 0, 0, 1, 9, 5, 0, 0,
    7, 0, 4, 0, 0, 2, 6, 0, 0,
    0, 2, 0, 0, 6, 5, 0, 4, 0,
    0, 0, 0, 0, 0, 1, 2, 0, 0,
    0, 6, 3, 8, 0, 0, 9, 0, 0,
    0, 0, 0, 2, 0, 0, 0, 3, 0
};

#define xy(x, y) ((x) + (y) * 9)

int get(int x, int y)
{
    return puzzle[xy(x, y)];
}

void put(int x, int y, int n)
{
    puzzle[xy(x, y)] = n;
}

int test(int x, int y, int n)
{
    if (get(x, y) != 0) return 0;

    for (int i = 0; i < 9; i++)
        if (get(i, y) == n || get(x, i) == n) return 0;

    int bx = (x / 3) * 3, by = (y / 3) * 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (get(bx + i, by + j) == n) return 0;

    return 1;
}

int go_deep(int x, int y)
{
    int nx = x + 1, ny = y;
    int last = 0;
    if (nx == 9)
    {
        nx = 0;
        ny++;
        if (ny == 9) last = 1;
    }
    if (get(x, y))
    {
        if (last) return 1;
        else return go_deep(nx, ny);
    }
    else
    {
        for (int n = 1; n <= 9; n++)
        {
            if (test(x, y, n))
            {
                put(x, y, n);
                if (last) return 1;
                if (go_deep(nx, ny)) return 1;
                put(x, y, 0);
            }
        }
        return 0;
    }
}

int solve()
{
    return go_deep(0, 0);
}

void print()
{
    for (int y = 0; y < 9; y++)
    {
        for (int x = 0; x < 9; x++)
            printf("%d", get(x, y));
        printf("\n");
    }
}

int main()
{
    solve();
    print();
    return 0;
}