#include <algorithm>
#include <cstdio>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::sort;

int getTelNum();
void outputNum(int, int);

int main() {
    int num;
    int flag = 0;
    cin >> num;
    getchar();
    int *telNum = new int[num];
    for (int i = 0; i < num; i++)
        telNum[i] = getTelNum();
    sort(telNum, telNum + num);
    for (int i = 0; i < num - 1; i++) {
        int count = 1;
        if (telNum[i] == telNum[i + 1]) {
            flag = 1;
            while (telNum[i] == telNum[i + 1] && i < num - 1) {
                i++;
                count++;
            }
            outputNum(telNum[i], count);
        }
    }
    if (flag == 0)
        cout << "No duplicates." << endl;
    delete[] telNum;
    return 0;
}

int getTelNum() {
    char c;
    int telNum = 0;
    while ((c = getchar()) != '\n') {
        if (c == '-')
            continue;
        if (c >= '0' && c <= '9')
            telNum = telNum * 10 + c - '0';
        else if (c == 'A' || c == 'B' || c == 'C')
            telNum = telNum * 10 + 2;
        else if (c == 'D' || c == 'E' || c == 'F')
            telNum = telNum * 10 + 3;
        else if (c == 'G' || c == 'H' || c == 'I')
            telNum = telNum * 10 + 4;
        else if (c == 'J' || c == 'K' || c == 'L')
            telNum = telNum * 10 + 5;
        else if (c == 'M' || c == 'N' || c == 'O')
            telNum = telNum * 10 + 6;
        else if (c == 'P' || c == 'R' || c == 'S')
            telNum = telNum * 10 + 7;
        else if (c == 'T' || c == 'U' || c == 'V')
            telNum = telNum * 10 + 8;
        else if (c == 'W' || c == 'X' || c == 'Y')
            telNum = telNum * 10 + 9;
        else
            continue;
    }
    return telNum;
}

void outputNum(int telNum, int count) {
    int tel1 = telNum / 10000;
    int tel2 = telNum % 10000;
    if (tel1 >= 100)
        cout << tel1;
    else if (tel1 >= 10)
        cout << "0" << tel1;
    else
        cout << "00" << tel1;
    cout << "-";
    if (tel2 >= 1000)
        cout << tel2;
    else if (tel2 >= 100)
        cout << "0" << tel2;
    else if (tel2 >= 10)
        cout << "00" << tel2;
    else
        cout << "000" << tel2;
    cout << " " << count << endl;
    return;
}