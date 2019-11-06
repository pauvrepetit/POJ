#include <cstdio>
#include <cstdlib>
#include <algorithm>

using std::binary_search;

int main() {
    int len1, len2;
    scanf("%d", &len1);
    short *array1 = (short *)malloc(sizeof(short) * len1);
    for (int i = 0; i < len1; i++) {
        scanf("%hd", &array1[i]);
    }
    scanf("%d", &len2);
    short *array2 = (short *)malloc(sizeof(short) * len2);
    for (int i = 0; i < len2; i++) {
        scanf("%hd", &array2[i]);
    }

    int selectNum;
    for (int i = 0; i < len2; i++)
    {
        selectNum = array2[i];
        if(binary_search(array1, array1 + len1, 10000 - selectNum) == true) {
            printf("YES\n");
            return 0;
        }
    }
    printf("NO\n");
    return 0;
}