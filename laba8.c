#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10 // Maksimal'nyy razmer matritsy

// Funktsiya dlya vychisleniya opredelitelya matritsy
double opredelitel(double matritsa[MAX_SIZE][MAX_SIZE], int n) {
    double det = 0;
    if (n == 1) {
        return matritsa[0][0];
    }
    if (n == 2) {
        return matritsa[0][0] * matritsa[1][1] - matritsa[0][1] * matritsa[1][0];
    }
    
    double temp[MAX_SIZE][MAX_SIZE];
    for (int x = 0; x < n; x++) {
        int subi = 0;
        for (int i = 1; i < n; i++) {
            int subj = 0;
            for (int j = 0; j < n; j++) {
                if (j == x) continue;
                temp[subi][subj] = matritsa[i][j];
                subj++;
            }
            subi++;
        }
        det += (x % 2 == 0 ? 1 : -1) * matritsa[0][x] * opredelitel(temp, n - 1);
    }
    return det;
}

// Funktsiya dlya resheniya SLAU metodom Kramera
void reshitSistema(double matritsa[MAX_SIZE][MAX_SIZE], double b[MAX_SIZE], int n) {
    double det = opredelitel(matritsa, n);
    
    if (det == 0) {
        printf("Sistema ne imeyet yedinstvennogo resheniya.\n");
        return;
    }

    double rez[MAX_SIZE];
    
    for (int i = 0; i < n; i++) {
        double temp[MAX_SIZE][MAX_SIZE];

        // Sozdanie matritsy, zamenyayushchey i-y stolbets na vektor b
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                temp[j][k] = matritsa[j][k];
            }
            temp[j][i] = b[j];
        }

        rez[i] = opredelitel(temp, n) / det;
    }

    // Vyvod rezul'tata
    printf("Reshenie sistemy:\n");
    for (int i = 0; i < n; i++) {
        printf("x[%d] = %lf\n", i, rez[i]);
    }
}

int main() {
    int n;
    double matritsa[MAX_SIZE][MAX_SIZE], b[MAX_SIZE];

    printf("Vvedite razmernost' sistemy (N): ");
    scanf("%d", &n);

    printf("Vvedite matritsu koeffitsientov:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lf", &matritsa[i][j]);
        }
    }

    printf("Vvedite vektor svobodnykh chlenov:\n");
    for (int i = 0; i < n; i++) {
        scanf("%lf", &b[i]);
    }

    reshitSistema(matritsa, b, n);

    return 0;
}
