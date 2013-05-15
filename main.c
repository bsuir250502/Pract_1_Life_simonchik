#include <stdio.h>
#include <stdlib.h>

#define string_size 256

int input_data(FILE * in_file)
{
    int number;
    char input_buffer[string_size];
    fgets(input_buffer, string_size, in_file);
    number = strtol(input_buffer, NULL, 10);
    return number;
}

void input_field(FILE * in_file, int **initial_field, int height,
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

void output_field(int **initial_field, int height, int width)
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

int num_of_neighbors(int **initial_field, int height, int width, int i,
                     int j)
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


void next_generation(int **initial_field, int **modified_field, int height,
                     int width)
{
    int i, j, num;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            num = num_of_neighbors(initial_field, height, width, i, j);
            if ((num == 3) || (initial_field[i][j] && num == 2)) {
                modified_field[i][j] = 1;
            } else
                modified_field[i][j] = 0;
        }
    }
}

void cpy_modif_field_in_init_field(int **inital_field,
                                   int **modified_field, int height,
                                   int width)
{
    int i, j;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            inital_field[i][j] = modified_field[i][j];
        }
    }
}

void fOutputField(FILE * out_file, int **field, int height, int width)
{
    int i, j;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            fprintf(out_file, "%d", field[i][j]);
        }
        fprintf(out_file, "\n");
    }
}

void freeField(int **field, int height)
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
    height = input_data(in_file);
    width = input_data(in_file);
    num_of_generation = input_data(in_file);
    initial_field = (int **) calloc(height, sizeof(int *));
    for (i = 0; i < height; i++) {
        initial_field[i] = (int *) calloc(width, sizeof(int));
    }
    printf("%d%d", height, width);
    input_field(in_file, initial_field, height, width);
    modified_field = (int **) calloc(height, sizeof(int *));
    for (i = 0; i < height; i++) {
        modified_field[i] = (int *) calloc(width, sizeof(int));
    }
    for (i = 0; i < num_of_generation; i++) {
        next_generation(initial_field, modified_field, height, width);
        output_field(modified_field, height, width);

        cpy_modif_field_in_init_field(initial_field, modified_field,
                                      height, width);
    }
    fOutputField(out_file, modified_field, height, width);
    fclose(in_file);
    fclose(out_file);
    freeField(initial_field, height);
    freeField(modified_field, height);
    return 0;
}
