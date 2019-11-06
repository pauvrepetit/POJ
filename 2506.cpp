#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

class BigNumber {
  public:
    string num;

    BigNumber() { this->num = ""; }

    BigNumber(string n) { this->num = n; }

    BigNumber operator+(const BigNumber &b) const {
        int len1 = this->num.length();
        int len2 = b.num.length();
        BigNumber result;
        while (len1 > 0 && len2 > 0) {
            len1--;
            len2--;
            result.num.insert(result.num.begin(),
                              this->num[len1] - '0' + b.num[len2]);
        }
        if (len1 > 0) {
            while (len1 > 0) {
                len1--;
                result.num.insert(result.num.begin(), this->num[len1]);
            }
        } else {
            while (len2 > 0) {
                len2--;
                result.num.insert(result.num.begin(), b.num[len2]);
            }
        }
        int len = result.num.length();
        for (int i = len - 1; i > 0; i--) {
            if (result.num[i] > '9') {
                result.num[i] -= 10;
                result.num[i - 1]++;
            }
        }
        if (result.num[0] > '9') {
            result.num[0] -= 10;
            result.num.insert(result.num.begin(), '1');
        }
        return result;
    }

    BigNumber operator*(int i) const {
        i -= '0';
        int len = this->num.length();
        BigNumber result;
        result.num = this->num;
        int mul, c;
        c = 0;
        for (int j = len - 1; j >= 0; j--) {
            mul = (result.num[j] - '0') * i + c;
            result.num[j] = mul % 10 + '0';
            c = mul / 10;
        }
        if (c != 0) {
            result.num.insert(result.num.begin(), c + '0');
        }
        return result;
    }

    BigNumber operator*(const BigNumber &b) const {
        BigNumber result;
        string zero = "";
        BigNumber temp;
        for (int i = this->num.length() - 1; i >= 0; i--) {
            temp.num = ((b * this->num[i]).num + zero);
            result = result + temp;
            zero += "0";
        }
        return result;
    }
};

BigNumber list[130];

BigNumber count(int n);

int main() {
    int n;
    while (cin >> n) {
        cout << count(n).num << endl;
    }
    return 0;
}

BigNumber count(int n) {
    if (n == 0 || n == 1) {
        return BigNumber("1");
    }
    if (n % 2 == 0) {
        BigNumber temp1;
        BigNumber temp2;
        if(list[n / 2].num == "") {
            list[n / 2] = count(n / 2);
        }
        if(list[n / 2 - 1].num == "") {
            list[n / 2 - 1] = count(n / 2 - 1);
        }
        temp1 = list[n / 2];
        temp2 = list[n / 2 - 1];
        return temp1 * temp1 + temp2 * temp2 * '2';
    } else {
        BigNumber temp1;
        BigNumber temp2;
        BigNumber temp3;
        if(list[n / 2].num == "") {
            list[n / 2] = count(n / 2);
        }
        if(list[n / 2 - 1].num == "") {
            list[n / 2 - 1] = count(n / 2 - 1);
        }
        if(list[n / 2 + 1].num == "") {
            list[n / 2 + 1] = count(n / 2 + 1);
        }
        temp1 = list[n / 2];
        temp2 = list[n / 2 + 1];
        temp3 = list[n / 2 - 1];
        return temp1 * temp2 + temp1 * temp3 * '2';
    }
}
