#include<stdio.h>
#include<stdlib.h>

int input_data(FILE * in_field)
{
    int number;
    if (!(fscanf(in_field, "%d", &number))) {
        puts("ERROR");
        exit(0);
    }
    return number;
}

void input_field(FILE * in_field, int **initial_field, int width,int height)
{
    int i, j;
    for (i = 0; i < width; i++) {
        for (j = 0; j < height; j++) {
            if (!(fscanf(in_field, "%d", &initial_field[i][j]))) {
                puts("ERROR");
                exit(0);
            }
        }
    }
}

void output_field(int **initial_field, int width, int height)
{
    int i, j;
    for (i = 0; i < width; i++) {
        printf("\n");
        for (j = 0; j < height; j++) {
            if (initial_field[i][j])
                printf("*");
            else
                printf(" ");
        }
    }
}

int num_of_neighbors(int **initial_field, int width, int height, int i,
                     int j)
{
    int up, down, right, left, num;
    if (j == 0) {
        (up = height - 1);
    } else {
        (up = j - 1);
    }
    if (i == 0) {
        (left = width - 1);
    } else {
        (left = i - 1);
    }
    if (j == height - 1) {
        (down = 0);
    } else {
        (down = j + 1);
    }
    if (i == width - 1) {
        (right = 0);
    } else {
        (right = i + 1);
    }
    return num =
        initial_field[i][up] + initial_field[i][down] +
        initial_field[left][j] + initial_field[right][j]
        + initial_field[left][up] + initial_field[right][up] +
        initial_field[left][down] + initial_field[right][down];
}


void next_generation(int **initial_field, int **modified_field, int width,
                     int height)
{
    int i, j, num;
    for (i = 0; i < width; i++) {
        for (j = 0; j < height; j++) {
            num = num_of_neighbors(initial_field, width, height, i, j);
            if ((num == 3) || (initial_field[i][j] && num == 2)) {
                modified_field[i][j] = 1;
            } else
                modified_field[i][j] = 0;
        }
    }
}

void cpy_modif_field_in_init_field(int **inital_field, int **modified_field, int width, int heigth)
{
    int i, j;
    for (i = 0; i < width; i++) {
        for (j = 0; j < heigth; j++) {
            inital_field[i][j] = modified_field[i][j];
        }
    }
}

void fOutputField(FILE * out_field, int **field, int width, int height)
{
    int i, j;
    for (i = 0; i < width; i++) {
        for (j = 0; j < height; j++) {
            fprintf(out_field, "%d", field[i][j]);
        }
        fprintf(out_field, "\n");
    }
}

void freeField(int **field, int width)
{
    int i;
    for (i = 0; i < width; i++) {
        free(field[i]);
    }
    free(field);
}

int main()
{
    int i;
    FILE *in_field, *out_field;
    if (!(in_field = fopen("life.in", "r"))) {
        puts("ERROR unable to open file");
        return 0;
    }
    if (!(out_field = fopen("life.out", "w"))) {
        puts("ERROR unable to open file");
        return 0;
    }
    int width, height, num_of_generation;
    int **initial_field, **modified_field;
    width = input_data(in_field);
    height = input_data(in_field);
    num_of_generation = input_data(in_field);
    initial_field = (int **) calloc(width, sizeof(int *));
    for (i = 0; i < width; i++) {
        initial_field[i] = (int *) calloc(height, sizeof(int));
    }
    input_field(in_field, initial_field, width, height);
    output_field(initial_field, width, height);
    modified_field = (int **) calloc(width, sizeof(int *));
    for (i = 0; i < width; i++) {
        modified_field[i] = (int *) calloc(height, sizeof(int));
    }
    for (i = 0; i < num_of_generation; i++) {
        next_generation(initial_field, modified_field, width, height);
        output_field(modified_field, width, height);
        cpy_modif_field_in_init_field(initial_field, modified_field, width,
                                      height);
        system("clear");
    }
    fOutputField(out_field, modified_field, width, height);
    fclose(in_field);
    fclose(out_field);
    freeField(initial_field, width);
    freeField(modified_field, width);
    return 0;
}
