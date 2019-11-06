#include <cstdio>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

class Haab {
  public:
    int day;
    int month;
    int year;

    Haab(int d, int m, int y) {
        day = d;
        month = m;
        year = y;
    }

    int getAllDay() { return year * 365 + month * 20 + day; }
};

class Tzolkin {
  public:
    int month;
    int day;
    int year;

    Tzolkin(int allDay) {
        year = allDay / 260;
        month = (allDay % 260) % 13 + 1;
        day = (allDay % 260) % 20;
    }
};

int transMonth(string);
string transDay(int);

int main() {
    int num;
    int day, year;
    string strMonth;
    cin >> num;
    cout << num << endl;
    for (int i = 0; i < num; i++) {
        cin >> day;
        getchar();
        getchar();
        cin >> strMonth >> year;
        Haab haab(day, transMonth(strMonth), year);
        Tzolkin tzolkin(haab.getAllDay());
        cout << tzolkin.month << " " << transDay(tzolkin.day) << " "
             << tzolkin.year << endl;
    }

    return 0;
}

// pop, no, zip, zotz, tzec, xul, yoxkin, mol, chen, yax, zac, ceh, mac, kankin,
// muan, pax, koyab, cumhu
int transMonth(string strMonth) {
    if (strMonth == "pop")
        return 0;
    if (strMonth == "no")
        return 1;
    if (strMonth == "zip")
        return 2;
    if (strMonth == "zotz")
        return 3;
    if (strMonth == "tzec")
        return 4;
    if (strMonth == "xul")
        return 5;
    if (strMonth == "yoxkin")
        return 6;
    if (strMonth == "mol")
        return 7;
    if (strMonth == "chen")
        return 8;
    if (strMonth == "yax")
        return 9;
    if (strMonth == "zac")
        return 10;
    if (strMonth == "ceh")
        return 11;
    if (strMonth == "mac")
        return 12;
    if (strMonth == "kankin")
        return 13;
    if (strMonth == "muan")
        return 14;
    if (strMonth == "pax")
        return 15;
    if (strMonth == "koyab")
        return 16;
    if (strMonth == "cumhu")
        return 17;
    return 18;
}

string transDay(int day) {
    string dayName[] = {"imix",  "ik",    "akbal", "kan",   "chicchan",
                        "cimi",  "manik", "lamat", "muluk", "ok",
                        "chuen", "eb",    "ben",   "ix",    "mem",
                        "cib",   "caban", "eznab", "canac", "ahau"};
    return dayName[day];
}