/* 
---------- Linear Algebra Program -----------
Student ID: 6788236
Name: Zwe Nyan Zaw
Surname: Zaw
Section: 3 
-------------------------------------------
*/

#include <stdio.h>
#include <math.h>

#define N_OPTIONS 8

struct Point {
    float x;
    float y;
    float z;
};

void input_two_points(struct Point points[]);

struct Vector {
    float x_component;
    float y_component;
    float z_component;
};

struct Vector get_vector(struct Point p, struct Point q);

void print_vector(struct Vector a);

void choose_option(int *first_time, int *option, char options[N_OPTIONS][49+1]);

void magnitude_of_vector();
 
int main(void) {
    char options[N_OPTIONS][49+1] = {
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
            case 8:
            magnitude_of_vector();
            break;
        }

        printf("\n");

    } while (option != 0);

    return 0;
}

void input_two_points(struct Point points[]) {
    char desc[2][30] = {
        "first",
        "second"
    };

    for (int i = 0; i < 2; i++) {
        printf("Please input %s point (x,y,z): ", desc[i]);
        scanf("%f %f %f", &points[i].x, &points[i].y, &points[i].z);
    }
    printf("===============================================\n");
}

struct Vector get_vector(struct Point p, struct Point q) {
    struct Vector a;
    a.x_component = p.x - q.x;
    a.y_component = p.y - q.y;
    a.z_component = p.z - q.z;
    return a;
}

void print_vector(struct Vector a) {
    printf("< %.1f, %.1f, %.1f >", a.x_component, a.y_component, a.z_component);
}

void choose_option(int *first_time, int *option, char options[N_OPTIONS][49+1]) {

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

void magnitude_of_vector() {
    struct Point points[2];

    input_two_points(points);
    struct Vector a = get_vector(points[0], points[1]);

    printf("Here is the vector: ");
    print_vector(a);
    printf("\n");

    printf("Magnitude of these vectors: %.2f\n", sqrt(pow(a.x_component, 2) + pow(a.y_component, 2) + pow(a.z_component, 2)));
    printf("===============================================\n");
}
