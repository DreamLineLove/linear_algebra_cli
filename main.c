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

void input_three_equations(float e[3][4]);

void print_solution(float x, float y, float z);

void scalar_multiplication(float scalar, int row, int col, float input[row][col], float output[row][col]);

void matrix_multiplication(float inverse[3][3], float constants[3], float solution[3]);

void choose_option(int *first_time, int *option, char options[N_OPTIONS][MAX_STR]);

void gaussian_elimination(float output[3][4], int called_in_main);

void gauss_jordan_elimination();

float determinant_calculation(int called_in_main, int m_order, float matrix[m_order][m_order]);

void cramers_rule();

void inverse();

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
        float equations[3][4];
        float matrix[3][3];
        
        switch (option) {
            case 1:
            gaussian_elimination(equations, 1);
            break;
            case 2:
            gauss_jordan_elimination();
            break;
            case 3:
            determinant_calculation(1, 4, matrix);
            break;
            case 4:
            cramers_rule();
            break;
            case 5:
            inverse();
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

void input_three_equations(float e[3][4]) {
    for (int i = 0; i < 3; i++) {
        printf("Please input equation No.%d (x,y,z, total): ", i);
        scanf("%f %f %f %f", &e[i][0], &e[i][1], &e[i][2], &e[i][3]);
    }
    printf("===============================================\n");
}

void print_solution(float x, float y, float z) {
    printf("Here is the solution of these equations:\n");
    printf("(x,y,z) = (%.1f,%.1f,%.1f)\n", x, y, z);
    printf("===============================================\n");
}

void scalar_multiplication(float scalar, int row, int col, float input[row][col], float output[row][col]) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            output[i][j] = input[i][j] * scalar;
        }
    }
}

void matrix_multiplication(float inverse[3][3], float constants[3], float solution[3]) {
    for (int i = 0; i < 3; i++) {
        solution[i] = 0;
        for (int j = 0; j < 3; j++) {
            solution[i] += inverse[i][j] * constants[j];
        }
    }
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

void gaussian_elimination(float output[3][4], int called_in_main) {

    float equations[3][4];
    input_three_equations(equations);

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
            for (int n = i; n < 4; n++) {
                equations[i][n] = equations[i][n] / multiple;
            }
            for (int l = i + 1; l < 3; l++) {
                if (equations[l][i] == 0) continue;
                 
                float multiple = -(equations[l][i]);

                for (int m = i; m < 4; m++) {
                    equations[l][m] = equations[l][m] + (equations[i][m] * multiple);
                }
            }
        }
    }
    
    if (called_in_main) {
        printf("Here are the equations after using Gaussian Elimination:\n");
        char variable_matrix[3] = {'x', 'y', 'z'};
        for (int i = 0; i < 3; i++) {
            int j, count = 0;
            for (j = 0; j < 3; j++) {
                if (equations[i][j] != 0) {
                    if (count != 0 && equations[i][j] > 0) printf("+");
                    if (equations[i][j] != 1) { 
                        printf("%.1f", equations[i][j]);
                    }
                    count++;
                    printf("%c", variable_matrix[j]);
                }
            }
            printf(" = %.1f\n", equations[i][j]);
        }
        printf("===============================================\n");

        printf("Here is the augmented matrix after using Gaussian Elimination:\n");
        for (int i = 0; i < 3; i++) {
            int j;
            for (j = 0; j < 3; j++) printf("%.1f ", equations[i][j]);
            printf("| %.1f\n", equations[i][j]);
        }
        printf("===============================================\n");

        float x, y, z;
        z = equations[2][3];
        y = equations[1][3] - (equations[1][2] * z);
        x = equations[0][3] - (equations[0][1] * y) - (equations[0][2] * z);
        print_solution(x, y, z);
    } else {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 4; j++) {
                output[i][j] = equations[i][j];
            }
        }
    }
}

void gauss_jordan_elimination() {

    float equations[3][4];
    gaussian_elimination(equations, 0);
    char variable_matrix[3] = {'x', 'y', 'z'};
    for (int c = 2; c > 0; c--) {
        for (int r = c - 1; r >= 0; r--) {
            float multiple = -(equations[r][c]);
            for (int s = c; s < 4; s++) {
                equations[r][s] = equations[r][s] + (multiple * equations[c][s]);
            }
        }
    }
    
    printf("Here are the equations after using Gauss-Jordan Elimination:\n");
    for (int i = 0; i < 3; i++) {
        int j, count = 0;
        for (j = 0; j < 3; j++) {
            if (equations[i][j] != 0) {
                if (count != 0 && equations[i][j] > 0) printf("+");
                if (equations[i][j] != 1) { 
                    printf("%.1f", equations[i][j]);
                }
                count++;
                printf("%c", variable_matrix[j]);
            }
        }
        printf(" = %.1f\n", equations[i][j]);
    }
    printf("===============================================\n");

    print_solution(equations[0][3], equations[1][3], equations[2][3]);
}

float determinant_calculation(int called_in_main, int m_order, float minor[m_order][m_order]) {
    int order;
    if (called_in_main) {
        printf("Please input size of matrix (1-4): ");
        scanf("%d", &order);
    } else {
        order = m_order;
    }
    float determinant;

    if (order <= 1) {
        printf("Please input number: ");
        scanf("%f", &determinant);
    } else {
        float matrix[order][order];
        if (called_in_main) {
            for (int r = 0; r < order; r++) {
                for (int c = 0; c < order; c++) {
                    printf("Please input number in index [%d][%d]: ", r, c);
                    scanf("%f", &matrix[r][c]);
                }
            }
        } else {
            for (int r = 0; r < order; r++) {
                for (int c = 0; c < order; c++) {
                    matrix[r][c] = minor[r][c];
                }
            }
        }
        if (order == 2) {
            float main_diagonal = matrix[0][0] * matrix[1][1];
            float other_diagonal = -(matrix[0][1] * matrix[1][0]);
            determinant = main_diagonal + other_diagonal;
        }
        if (order == 3) {
            float down_sweep = matrix[0][0] * matrix[1][1] * matrix[2][2] + matrix[0][1] * matrix[1][2] * matrix[2][0] + matrix[0][2] * matrix[1][0] * matrix[2][1];
            float up_sweep = -(matrix[0][2] * matrix[1][1] * matrix[2][0]) - (matrix[0][0] * matrix[1][2] * matrix[2][1]) -(matrix[0][1] * matrix[1][0] * matrix[2][2]);
            determinant = up_sweep + down_sweep;
        }
        if (order == 4) {
            float cofactors[4];
            for (int i = 0; i < order; i++) {
                float multiple = (i % 2 == 0) ? 1.0 : -1.0;
                float minor[3][3];
                int l = 0, m = 0;
                for (int j = 0; j < order; j++) {
                    if (j == 0) continue;
                    for (int k = 0; k < order; k++) {
                        if (k == i) continue;
                        minor[l][m] = matrix[j][k];
                        m++;
                    }
                    l++;
                    m=0;
                }
                cofactors[i] = matrix[0][i] * multiple * determinant_calculation(0, 3, minor);
            }
            determinant = 0;
            for (int i = 0; i < 4; i++) {
                determinant += cofactors[i];
            }
        }
        if (called_in_main) {
            for (int r = 0; r < order; r++) {
                for (int c = 0; c < order; c++) {
                    printf("%.2f ", matrix[r][c]);
                }
                printf("\n");
            }
        }
    }
    if (called_in_main) {
        printf("===============================================\n");
        printf("Determinant of this matrix: %.2f\n", determinant);
        printf("===============================================\n");
    }
    return determinant;
}

void cramers_rule() {

    float equations[3][4];
    input_three_equations(equations);
    char variable_matrix[3] = {'x', 'y', 'z'};
    float coefficients[3][3], constants[3];
    float determinant, determinants[3];

    printf("Here are the equations:\n");
    for (int i = 0; i < 3; i++) {
        int j, count = 0;
        for (j = 0; j < 3; j++) {
            coefficients[i][j] = equations[i][j];
            if (equations[i][j] != 0) {
                if (count != 0 && equations[i][j] > 0) printf("+");
                if (equations[i][j] != 1) { 
                    printf("%.1f", equations[i][j]);
                }
                count++;
                printf("%c", variable_matrix[j]);
            }
        }
        printf(" = %.1f\n", equations[i][j]);
        constants[i] = equations[i][j];
    }
    determinant = determinant_calculation(0, 3, coefficients);
    printf("===============================================\n");

    for (int i = 0; i < 3; i++) {
        float Ai[3][3];
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                if (k != i) {
                    Ai[j][k] = coefficients[j][k];
                } else Ai[j][k] = constants[j];
            }
        }
        determinants[i] = determinant_calculation(0, 3, Ai);
    }

    printf("Here are the determinant of each variable:\n");
    printf("|A| = %.2f\n", determinant);
    for (int i = 0; i < 3; i++) {
        printf("|%c| = %.2f\n", variable_matrix[i], determinants[i]);
    }
    printf("===============================================\n");

    float x, y, z;
    x = determinants[0] / determinant;
    y = determinants[1] / determinant;
    z = determinants[2] / determinant;
    print_solution(x, y, z);
}

void inverse() {

    float equations[3][4];
    input_three_equations(equations);
    char variable_matrix[3] = {'x', 'y', 'z'};
    float coefficients[3][3], constants[3];
    float determinant, determinants[3];
    float cofactor_matrix[3][3], adjoint[3][3];
    float inverse[3][3], solution[3];

    printf("Here are the equations:\n");
    for (int i = 0; i < 3; i++) {
        int j, count = 0;
        for (j = 0; j < 3; j++) {
            coefficients[i][j] = equations[i][j];
            if (equations[i][j] != 0) {
                if (count != 0 && equations[i][j] > 0) printf("+");
                if (equations[i][j] != 1) { 
                    printf("%.1f", equations[i][j]);
                }
                count++;
                printf("%c", variable_matrix[j]);
            }
        }
        printf(" = %.1f\n", equations[i][j]);
        constants[i] = equations[i][j];
    }

    determinant = determinant_calculation(0, 3, coefficients);
    printf("Here is the determinant of A:\n");
    printf("|A| = %.2f\n", determinant);
    printf("===============================================\n");

    printf("Here is the cofactor of A:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            float minor[2][2];
            int m = 0, n = 0;
            for (int k = 0; k < 3; k++) {
                if (k == i) continue;
                for (int l = 0; l < 3; l++) {
                    if (l == j) continue;
                    minor[m][n] = coefficients[k][l];
                    n++;
                }
                m++;
                n=0;
            }
            float multiple = pow(-1, ((i+1)+(j+1)));
            cofactor_matrix[i][j] = multiple * determinant_calculation(0, 2, minor);
            printf("%.2f ", cofactor_matrix[i][j]);
        }
        printf("\n");
    }
    printf("===============================================\n");

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            adjoint[j][i] = cofactor_matrix[i][j];
        }
    }
    printf("Here is the adjoint of A:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%.2f ", adjoint[i][j]);
        }
        printf("\n");
    }
    printf("===============================================\n");

    scalar_multiplication(1/determinant, 3, 3, adjoint, inverse);
    matrix_multiplication(inverse, constants, solution);
    print_solution(solution[0], solution[1], solution[2]);
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
