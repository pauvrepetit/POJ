#include <cstdio>
#include <cstring>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int num[4000];
int A[2][4000];
int B[2][4000];

int main() {
    int n, b;
    int temp;
    cin >> n >> b;
    for (int i = 0; i < n; i++) {
        scanf("%d", &temp);
        num[i] = temp;
    }

    memset(A, 0x80, sizeof(int) * 2 * 4000);
    memset(B, 0x80, sizeof(int) * 2 * 4000);

    int l;
    int max = 0;

    A[0][0] = 0;
    B[0][1] = 0;
    // shit the init
    
    for (int i = 1; i < n; i++) {
        l = i % 2;
        for (int j = 0; j <= b && j <= (i + 1); j++) {
            A[l][j] = std::max(A[!l][j], B[!l][j]);
            if (j >= 1)
                B[l][j] = std::max(B[!l][j - 1] + num[i], A[!l][j - 1]);
        }
    }
    max = std::max(A[l][b], B[l][b]);

    memset(A, 0x80, sizeof(int) * 2 * 4000);
    memset(B, 0x80, sizeof(int) * 2 * 4000);

    B[0][1] = num[0];
    for (int i = 1; i < n; i++) {
        l = i % 2;
        for (int j = 0; j <= b && j <= (i + 1); j++) {
            A[l][j] = std::max(A[!l][j], B[!l][j]);
            if (j >= 1)
                B[l][j] = std::max(B[!l][j - 1] + num[i], A[!l][j - 1]);
        }
    }
    max = std::max(max, B[l][b]);
    cout << max << endl;

    return 0;
}