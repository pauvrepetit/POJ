#include <cstdlib>
#include <cstring>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

struct matrix {
    unsigned short value[30][30];
    int n;
    int m;

    matrix operator*(const matrix &m) const {
        matrix temp;
        temp.n = this->n;
        temp.m = this->m;
        for (int i = 0; i < this->n; i++) {
            for (int j = 0; j < this->n; j++) {
                temp.value[i][j] = 0;
                for (int k = 0; k < this->n; k++) {
                    temp.value[i][j] =
                        (temp.value[i][j] + this->value[i][k] * m.value[k][j]) %
                        this->m;
                }
            }
        }
        return temp;
    }
    matrix operator+(int i) const {
        matrix temp;
        temp = *this;
        for (int j = 0; j < this->n; j++) {
            temp.value[j][j] += i;
            temp.value[j][j] %= temp.m;
        }
        return temp;
    }
    matrix operator+(const matrix &m) const {
        matrix temp;
        temp = *this;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                temp.value[i][j] += m.value[i][j];
                temp.value[i][j] %= temp.m;
            }
        }
        return temp;
    }
};

matrix sum(matrix mat, int k);
matrix pow(matrix mat, int k);

int n, k, m;
int flag;
matrix matList[32];

int main() {
    flag = 0;
    cin >> n >> k >> m;
    matrix mat;
    mat.n = n;
    mat.m = m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> mat.value[i][j];
        }
    }
    mat = sum(mat, k);
    for (int i = 0; i < mat.n; i++) {
        for (int j = 0; j < mat.n; j++) {
            cout << mat.value[i][j];
            if (j != mat.n - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }
    return 0;
}

matrix sum(matrix mat, int k) {
    if (k == 1) {
        return mat;
    }
    if (k % 2 == 0) {
        return (pow(mat, k / 2) + 1) * sum(mat, k / 2);
    } else {
        return mat + mat * (pow(mat, k / 2) + 1) * sum(mat, k / 2);
    }
}

matrix pow(matrix mat, int k) {
    if (flag == 0) {
        matList[0] = mat;
        for (int i = 1; i < 32; i++) {
            matList[i] = matList[i - 1] * matList[i - 1];
        }
    }
    matrix temp;
    temp.m = mat.m;
    temp.n = mat.n;
    memset(temp.value, 0, sizeof(unsigned short) * 900);
    for (int i = 0; i < mat.n; i++) {
        temp.value[i][i] = 1;
    }

    unsigned int sign = 0x80000000u;
    int i = 31;
    while (sign != 0) {
        if ((sign & k) != 0) {
            temp = temp * matList[i];
        }
        i--;
        sign >>= 1;
    }
    return temp;
}
