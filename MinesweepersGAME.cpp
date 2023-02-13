#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FLUSH fflush(stdin)

void dificultate();
void incepator();
void mediu();
void expert();
void generator_joc();
void afisare_joc();
void selectare();
void bombe();
void afisare_joc_final();
void castigator();
void joaca_din_nou();
void sfarsit_joc();

int x, y;
int M, N;
float dif;
int total_mine = 0;
int mine = 0;
int joc[30][30];
int joc_gol[30][30];
int joc_final[30][30];

int main()
{
    printf("\t\tBun venit!\n");
    dificultate();
    return 0;
}

void dificultate()
{
    dif = 0;
    while ((dif != 1) && (dif != 2) && (dif != 3))
    {
        printf("\t\tAlege nivelul de dificultate(1-3) :");
        scanf_s("%f", &dif);
        FLUSH;
        if ((dif != 1) && (dif != 2) && (dif != 3))
        {
            printf("\t\tTe rog introdu 1, 2 sau 3 \n");
        }
    }

    if (dif == 1)
    {
        incepator();
    }
    else if (dif == 2)
    {
        mediu();
    }
    else if (dif == 3)
    {
        expert();
    }
    else if (dif == 4)
    {

    }
}

void incepator()
{
    M = 9;
    N = 9;
    total_mine = 10;
    generator_joc();
    selectare();
}

void mediu()
{
    M = 16;
    N = 16;
    total_mine = 40;
    generator_joc();
    selectare();
}

void expert()
{
    M = 16;
    N = 30;
    total_mine = 99;
    generator_joc();
    selectare();
}



void generator_joc()
{
    int i = 0, j = 0;

    srand(time(NULL));

    while (j < N)
    {
        while (i < M)
        {
            joc[i][j] = '-';
            joc_gol[i][j] = joc[i][j];
            joc_final[i][j] = joc[i][j];
            i++;
        }
        i = 0;
        j++;
    }
    mine = 0;
    while (mine < total_mine)
    {
        i = rand() % (M);
        j = rand() % (N);
        if (joc[i][j] != '*')
        {
            joc[i][j] = '*';
            joc_final[i][j] = joc[i][j];
            mine++;
        }
    }
    i = 0;
    j = 0;

    while (j < N)
    {
        while (i < M)
        {
            if (joc[i][j] != '*')
            {
                joc[i][j] = 0;
            }
            if ((joc[i - 1][j - 1] == '*') && (joc[i][j] != '*'))
            {
                joc[i][j]++;
            }
            if ((joc[i - 1][j] == '*') && (joc[i][j] != '*'))
            {
                joc[i][j]++;
            }
            if ((joc[i][j - 1] == '*') && (joc[i][j] != '*'))
            {
                joc[i][j]++;
            }
            if ((joc[i - 1][j + 1] == '*') && (joc[i][j] != '*'))
            {
                joc[i][j]++;
            }
            if ((joc[i + 1][j - 1] == '*') && (joc[i][j] != '*'))
            {
                joc[i][j]++;
            }
            if ((joc[i + 1][j] == '*') && (joc[i][j] != '*'))
            {
                joc[i][j]++;
            }
            if ((joc[i][j + 1] == '*') && (joc[i][j] != '*'))
            {
                joc[i][j]++;
            }
            if ((joc[i + 1][j + 1] == '*') && (joc[i][j] != '*'))
            {
                joc[i][j]++;
            }
            i++;
        }
        i = 0;
        j++;
    }
    i = 0;
    j = 0;
}

void afisare_joc()
{
    int i = 0, j = 0, z = 0;
    while (z < M)
    {
        if (z == 0)
        {
            printf("\t");
        }
        printf("|%d|\t", z);
        z++;
    }
    printf("\n\n");

    while (j < N)
    {
        printf("|%d|\t", j);
        while (i < M)
        {
            if (joc_gol[i][j] == '-')
            {
                printf("|%c|\t", joc_gol[i][j]);

            }
            else if (joc[i][j] == 0)
            {
                joc_gol[i][j] = ' ';
                printf("|%c|\t", joc_gol[i][j]);
            }
            else
            {
                printf("|%d|\t", joc_gol[i][j]);

            }
            i++;
        }
        printf("\n");
        i = 0;
        j++;
    }
}


void selectare()
{
    int q = 0, i = 0, j = 0, match = 0;
    afisare_joc();
    while (j < N)
    {
        while (i < M)
        {
            if (joc[i][j] == joc_gol[i][j])
            {
                match++;
            }
            i++;
        }
        i = 0;
        j++;
    }
    if (match == ((M * N) - total_mine))
    {
        castigator();
    }
    printf("\nIntr o valoare x , un spatiu, apoi valoarea y:");
    scanf_s("%d %d", &x, &y);
    FLUSH;
    if ((x >= M) || (x < 0) || (y < 0) || (y >= N))
    {
        printf("\nVa rog indroduceti valori incluse in interval\n");
        printf("\n  \n");

        selectare();
    }
    if (joc[x][y] == '*')
    {
        bombe();
    }
    if (joc_gol[x][y] != '-')
    {
        printf("\nVa rog introduceti o valoare care nu a fost deja introdusa\n");
        printf("\n  \n");
        selectare();
    }

    else
    {
        joc_gol[x][y] = joc[x][y];
        if (joc[x][y] == 0)
        {
            if (joc[x - 1][y - 1] == 0)
            {
                joc_gol[x - 1][y] = joc[x - 1][y];
            }
            if (joc[x - 1][y] == 0)
            {
                joc_gol[x - 1][y] = joc[x - 1][y];
            }
            if (joc[x][y - 1] == 0)
            {
                joc_gol[x][y - 1] = joc[x][y - 1];
            }
            if (joc[x - 1][y + 1] == 0)
            {
                joc_gol[x - 1][y + 1] = joc[x - 1][y + 1];
            }
            if (joc[x + 1][y - 1] == 0)
            {
                joc_gol[x + 1][y - 1] = joc[x + 1][y - 1];
            }
            if (joc[x + 1][y] == 0)
            {
                joc_gol[x + 1][y] = joc[x + 1][y];
            }
            if (joc[x][y + 1] == 0)
            {
                joc_gol[x][y + 1] = joc[x][y + 1];
            }
            if (joc[x + 1][y + 1] == 0)
            {
                joc_gol[x + 1][y + 1] = joc[x + 1][y + 1];
            }
        }
        selectare();
    }
}

void bombe()
{
    afisare_joc_final();
    printf("\n\t\tAti lovit o bomba %d,%d\n\t\tAti pierdut!!!!", x, y);
    joaca_din_nou();
}

void afisare_joc_final()
{
    int i = 0, j = 0, z = 0;
    while (z < M)
    {
        if (z == 0)
        {
            printf("\t");
        }
        printf("|%d|\t", z);
        z++;
    }
    printf("\n\n");

    while (j < N)
    {
        printf("|%d|\t", j);
        while (i < M)
        {
            printf("|%c|\t", joc_final[i][j]);
            i++;
        }
        printf("\n");
        i = 0;
        j++;
    }
}

void castigator()
{
    printf("\n\n\n\t\t\tAti castigat!!!!!\n\n\n");
    joaca_din_nou();
}

void joaca_din_nou()
{
    char option[2];
    printf("\n\t\tDoriti sa jucati din nou(Y/N)?:");
    scanf_s("%c", &option[0]);
    FLUSH;
    if ((option[0] == 'Y') || (option[0] == 'y'))
    {
        dificultate();
    }
    else if ((option[0] == 'N') || (option[0] == 'n'))
    {
        sfarsit_joc();
    }
    else
    {
        printf("Va rog introduceti Y sau N");
        joaca_din_nou();
    }
}

void sfarsit_joc()
{
    printf("\n\n\t\t Sfarsitul jocului!");
    exit(1);
}