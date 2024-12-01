#include <stdio.h>
#include <math.h>

#define N_OPTIONS 8
#define MAX_STR 50 // 49+1

struct Object {
    float x;
    float y;
    float z;
};

void input_two_objects(struct Object objects[], char *name);

struct Vector {
    float x_component;
    float y_component;
    float z_component;
};

struct Vector get_vector(struct Object p, struct Object q);

void print_vector(struct Vector a, char front, char back);

// struct Equation {
//     float x_coefficient;;
//     float y_coefficient;
//     float z_coefficient;
//     float constant;
// };

void input_three_equations(float e[3][4]);

void choose_option(int *first_time, int *option, char options[N_OPTIONS][MAX_STR]);

void gaussian_elimination();

void dot_product();

void cross_product();

void magnitude_of_vector();
 
int main(void) {
    char options[N_OPTIONS][MAX_STR] = {
        "Gaussian Elimination",
        "Gaussian - Jordan Elimination",
        "Find determinant",
        "Cramer's Rule",
        "Inverse of a matrix",
        "Dot product",
        "Cross product",
        "Find magnitude of vector",
    };
    int option, first_time = 1;

    do {
        choose_option(&first_time, &option, options);
        
        switch (option) {
            case 1:
            gaussian_elimination();
            break;
            case 6:
            dot_product();
            break;
            case 7:
            cross_product();
            case 8:
            magnitude_of_vector();
            break;
        }

        printf("\n");

    } while (option != 0);

    return 0;
}

void input_two_objects(struct Object objects[], char *name) {
    char desc[2][30] = {
        "first",
        "second"
    };

    for (int i = 0; i < 2; i++) {
        printf("Please input %s %s (x,y,z): ", desc[i], name);
        scanf("%f %f %f", &objects[i].x, &objects[i].y, &objects[i].z);
    }
    printf("===============================================\n");
}

struct Vector get_vector(struct Object p, struct Object q) {
    struct Vector a;
    a.x_component = p.x - q.x;
    a.y_component = p.y - q.y;
    a.z_component = p.z - q.z;
    return a;
}

void print_vector(struct Vector a, char front, char back) {
    printf("%c%.1f, %.1f, %.1f%c", front, a.x_component, a.y_component, a.z_component, back);
}

// void input_three_equations(struct Equation e[]) {
//     for (int i = 0; i < 2; i++) {
//         printf("Please input equation No.%d (x,y,z, total): ", i);
//         scanf("%f %f %f %f", &e[i].x_coefficient, &e[i].y_coefficient, &e[i].z_coefficient, &e[i].constant);
//     }
//     printf("===============================================\n");
// }

void input_three_equations(float e[3][4]) {
    for (int i = 0; i < 3; i++) {
        printf("Please input equation No.%d (x,y,z, total): ", i);
        scanf("%f %f %f %f", &e[i][0], &e[i][1], &e[i][2], &e[i][3]);
    }
    printf("===============================================\n");
}

void choose_option(int *first_time, int *option, char options[N_OPTIONS][MAX_STR]) {

    if (*first_time == 1) {
        printf("Welcome to linear algebra program.\n");
        printf("===============================================\n");

        for (int i = 0; i < N_OPTIONS; i++) {
            printf("%d. %s\n", i+1, options[i]);
        }
        printf("0. End the program\n");

        printf("===============================================\n");

        *first_time = 0;

        printf("Please input the method that you want to use: ");
        scanf("%d", option);
        printf("===============================================\n");

    } else {
        printf("What you want to use next?\n");
        printf("===============================================\n");

        for (int i = 0; i < N_OPTIONS; i++) {
            printf("%d. %s\n", i+1, options[i]);
        }
        printf("0. End the program\n");

        printf("===============================================\n");
        printf("Please input the method that you want to use: ");
        scanf("%d", option);
        printf("===============================================\n");

    }
}

void gaussian_elimination() {
    // struct Equation equations[3];
    // input_three_equations(equations);
    //
    // for (int i = 0; i < 2; i++) {
    //     if (equations[i].x)
    // }

    float equations[3][4];
    input_three_equations(equations);

    // for (int i = 0; i < 3; i++) {
    //     for (int j = 0; j < 4; j++) {
    //         printf("%.1f ", equations[i][j]);
    //     }
    //     printf("\n");
    // }

    for (int i = 0; i < 3; i++) {
        if (equations[i][i] == 0) {
            float temp;
            for (int j = i; j < 3; j++) {
                if (equations[j][i] == 0) {
                    for (int k = 0; k < 4; k++) {
                        float temp = equations[i][k];
                        equations[i][k] = equations[j][k];
                        equations[j][k] = temp;
                    }
                }
            }
        } 

        if (equations[i][i] != 0) {
            float multiple = equations[i][i];
            // equations[i][i] = equations[i][i] / equations[i][i];
            for (int n = i; n < 4; n++) {
                equations[i][n] = equations[i][n] / multiple;
            }
            for (int l = i + 1; l < 3; l++) {
                if (equations[l][i] == 0) continue;
                 
                float multiple = -(equations[l][i]);

                for (int m = i; m < 4; m++) {
                    equations[l][m] = equations[l][m] + (equations[i][m] * multiple);
                    // printf("%.1f ", equations[l][m]);
                }
            }
        }
    }
    
    printf("Here are the augmented matrix after using Gaussian Elimination:\n");
    char variable_mat[3] = {'x', 'y', 'z'};
    for (int i = 0; i < 3; i++) {
        int j, count = 0;
        for (j = 0; j < 3; j++) {
            if (equations[i][j] != 0) {
                if (count != 0 && equations[i][j] > 0) printf("+");
                if (equations[i][j] != 1) { 
                    printf("%.1f", equations[i][j]);
                }
                count++;
                printf("%c", variable_mat[j]);
            }
        }
        printf(" = %.1f\n", equations[i][j]);
    }
    printf("===============================================\n");
    // printf("\n");

    // for (int i = 0; i < 3; i++) {
    //     for (int j = 0; j < 4; j++) {
    //         printf("%.1f ", equations[i][j]);
    //     }
    //     printf("\n");
    // }
}

void dot_product() {
    struct Object vectors[2];
    input_two_objects(vectors, "vector");

    printf("Dot product of these vectors: %.2f\n", vectors[0].x * vectors[1].x + vectors[0].y * vectors[1].y + vectors[0].z * vectors[1].z );
    printf("===============================================\n");
}

void cross_product() {
    struct Object vectors[2];
    input_two_objects(vectors, "vector");

    struct Vector a;
    a.x_component = vectors[0].y * vectors[1].z - vectors[0].z * vectors[1].y;
    a.y_component = vectors[0].z * vectors[1].x - vectors[0].x * vectors[1].z;
    a.z_component = vectors[0].x * vectors[1].y - vectors[0].y * vectors[1].x;

    printf("Cross product of these vectors:\n");
    if (a.x_component >= 0) printf("+");
    printf("%.1fi", a.x_component);
    if (a.y_component >= 0) printf("+");
    printf("%.1fj", a.y_component);
    if (a.z_component >= 0) printf("+");
    printf("%.1fk\n", a.z_component);

    print_vector(a, '(', ')');
    printf("\n===============================================\n");
}

void magnitude_of_vector() {
    struct Object points[2];
    input_two_objects(points, "point");

    struct Vector a = get_vector(points[0], points[1]);
    printf("Here is the vector: ");
    print_vector(a, '<', '>');
    printf("\n");

    printf("Magnitude of these vectors: %.2f\n", sqrt(pow(a.x_component, 2) + pow(a.y_component, 2) + pow(a.z_component, 2)));
    printf("===============================================\n");
}
