#include<stdio.h>
#include<stdlib.h>

int input_data(FILE * field)
{
    int number;
    if (!(fscanf(field, "%d", &number))) {
        puts("ERROR");
        exit(0);
    }
    return number;
}

int **input_field(FILE * field, int width, int height)
{
    int i, j, **in_field;
    in_field = (int **) calloc(width, sizeof(int *));
    for (i = 0; i < width; i++) {
        in_field[i] = (int *) calloc(height, sizeof(int));
    }
    for (i = 0; i < width; i++) {
        for (j = 0; j < height; j++) {
            if (!(fscanf(field, "%d", &in_field[i][j]))) {
                puts("ERROR");
                exit(0);
            }
        }
    }
    return in_field;
}

void output_field(int **initial_field, int width, int height)
{
    int i, j;
    for (i = 0; i < width; i++) {
        printf("\n");
        for (j = 0; j < height; j++) {
            printf("%d", initial_field[i][j]);
        }
    }
    printf("\n");
}


int main()
{
    FILE *field;
    if (!(field = fopen("life.in", "r"))) {
        puts("ERROR unable to open file");
        return 0;
    }
    int width, height, num_of_generation;
    int **initial_field;
    width = input_data(field);
    height = input_data(field);
    num_of_generation = input_data(field);
    initial_field = input_field(field, width, height);
    printf("width of field = %d\n", width);
    printf("height of field = %d\n", height);
    printf("num of generation = %d\n\nINITIAL_FILD:\n", num_of_generation);
    output_field(initial_field, width, height);
    fclose(field);
    return 0;
}
