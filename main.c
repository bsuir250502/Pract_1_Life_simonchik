#include <stdio.h>
#include <stdlib.h>

#define string_size 256

int InputData(FILE * in_file)
{
    int number;
    char input_buffer[string_size];
    fgets(input_buffer, string_size, in_file);
    number = strtol(input_buffer, NULL, 10);
    return number;
}

void InputField(FILE * in_file, int **initial_field, int height,
                 int width)
{
    int i, j;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            initial_field[i][j] = getc(in_file) - '0';
        }
        getc(in_file);
    }
}

void OutputField(int **initial_field, int height, int width)
{
    int i, j;
    for (i = 0; i < height; i++) {
        printf("\n");
        for (j = 0; j < width; j++) {
            if (initial_field[i][j])
                printf("*");
            else
                printf(" ");
        }
    }
}

int NumNeighbors(int **initial_field, int height, int width, int i,int j)
{
    int up, down, right, left, num;
    if (i == 0) {
        (up = height - 1);
    } else {
        (up = i - 1);
    }
    if (j == 0) {
        (left = width - 1);
    } else {
        (left = j - 1);
    }
    if (i == height - 1) {
        (down = 0);
    } else {
        (down = i + 1);
    }
    if (j == width - 1) {
        (right = 0);
    } else {
        (right = j + 1);
    }
    return num =
        initial_field[up][j] + initial_field[down][j] +
        initial_field[i][left] + initial_field[i][right] +
        initial_field[up][left] + initial_field[up][right] +
        initial_field[down][left] + initial_field[down][right];
}

void NextGeneration(int **initial_field, int **modified_field, int height,int width)
{
    int i, j, num;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            num = NumNeighbors(initial_field, height, width, i, j);
            if ((num == 3) || (initial_field[i][j] && num == 2)) {
                modified_field[i][j] = 1;
            } else
                modified_field[i][j] = 0;
        }
    }
}

void CpyModifFieldInInitField(int **inital_field,int **modified_field, int height,int width)
{
    int i, j;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            inital_field[i][j] = modified_field[i][j];
        }
    }
}

void FOutputField(FILE * out_file, int **field, int height, int width)
{
    int i, j;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            fprintf(out_file, "%d", field[i][j]);
        }
        fprintf(out_file, "\n");
    }
}

void FreeField(int **field, int height)
{
    int i;
    for (i = 0; i < height; i++) {
        free(field[i]);
    }
    free(field);
}

int main()
{
    int i;
    FILE *in_file, *out_file;
    if (!(in_file = fopen("life.in", "r"))) {
        puts("ERROR unable to open file");
        return 0;
    }
    if (!(out_file = fopen("life.out", "w"))) {
        puts("ERROR unable to open file");
        return 0;
    }
    int height, width, num_of_generation;
    int **initial_field, **modified_field;
    height = InputData(in_file);
    width = InputData(in_file);
    num_of_generation = InputData(in_file);
    initial_field = (int **) calloc(height, sizeof(int *));
    for (i = 0; i < height; i++) {
        initial_field[i] = (int *) calloc(width, sizeof(int));
    }
    InputField(in_file, initial_field, height, width);
    modified_field = (int **) calloc(height, sizeof(int *));
    for (i = 0; i < height; i++) {
        modified_field[i] = (int *) calloc(width, sizeof(int));
    }
    for (i = 0; i < num_of_generation; i++) {
        NextGeneration(initial_field, modified_field, height, width);
        OutputField(modified_field, height, width);
        CpyModifFieldInInitField(initial_field, modified_field,height, width);
    }
    FOutputField(out_file, modified_field, height, width);
    fclose(in_file);
    fclose(out_file);
    FreeField(initial_field, height);
    FreeField(modified_field, height);
    return 0;
}