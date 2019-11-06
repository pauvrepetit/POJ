/*
 * 字符串数字乘方
 */

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

string pow(string R, int n);
string mul(string, string);
string mul(string, char);
string add(string, string);

int main() {
    string R;
    string result;
    int n;
    int locDot;
    while (cin >> R >> n) {
        while (R[0] == '0') {
            R.erase(R.begin());
        }
        locDot = R.find('.');
        if (locDot != string::npos) {
            R.erase(locDot, 1);
        }
        result = pow(R, n);
        if (locDot == string::npos) {
            cout << result << endl;
        } else {
            locDot = R.length() - locDot;
            locDot *= n;
            if (locDot > result.length()) {
                cout << '.';
                for (int i = 0; i < locDot - result.length(); i++)
                    cout << '0';
                cout << result << endl;
            } else {
                cout << result.substr(0, result.length() - locDot);
                result.erase(0, result.length() - locDot);
                int len = result.length();
                for (int j = len - 1; j >= 0; j--) {
                    if (result[j] != '0')
                        break;
                    // result.pop_back();   // in c++98 there is not pop_back
                    // func in string
                    result.erase(result.end() - 1);
                }
                if (result.length() != 0)
                    cout << "." << result;
                cout << endl;
            }
        }
    }
}

string pow(string R, int n) {
    string result = R;
    for (int i = 1; i < n; i++)
        result = mul(result, R);
    return result;
}

string mul(string m1, string m2) {
    string result = "";
    string zero = "";

    for (int i = m2.length() - 1; i >= 0; i--) {
        result = add(result, mul(m1, m2[i]) + zero);
        zero += "0";
    }
    return result;
}

string mul(string m, char c) {
    for (int i = 0; i < m.length(); i++) {
        m[i] -= '0';
        m[i] *= (c - '0');
    }
    for (int i = m.length() - 1; i > 0; i--) {
        m[i - 1] += m[i] / 10;
        m[i] = m[i] % 10;
    }
    if (m[0] / 10) {
        m.insert(0, 1, m[0] / 10);
        m[1] = m[1] % 10;
    }
    for (int i = 0; i < m.length(); i++)
        m[i] += '0';
    return m;
}

string add(string a1, string a2) {
    string result = "";
    char c = 0; // 进位
    int length1 = a1.length();
    int length2 = a2.length();
    if (length1 > length2) {
        a2.insert(0, length1 - length2, '0');
    } else {
        a1.insert(0, length2 - length1, '0');
    }
    int length = a1.length();
    for (int i = length - 1; i >= 0; i--) {
        result.insert(0, 1, (a1[i] + a2[i] - '0' + c - '0') % 10 + '0');
        c = (a1[i] + a2[i] - '0' - '0' + c) / 10;
    }
    if (c)
        result.insert(0, 1, c + '0');
    return result;
}
