#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main() {
    int p, e, i, d;
    cin >> p >> e >> i >> d;
    int count = 0;
    while (!(p == -1 && e == -1 && i == -1 && d == -1)) {
        count++;
        for (int j = d + 1; j <= d + 21252; j++) {
            if (((j - p) % 23) == 0 && ((j - e) % 28) == 0 &&
                ((j - i) % 33) == 0) {
                cout << "Case " << count << ": the next triple peak occurs in "
                     << j - d << " days." << endl;
                break;
            }
        }
        cin >> p >> e >> i >> d;
    }
    return 0;
}