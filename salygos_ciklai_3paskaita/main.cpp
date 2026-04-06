#include <iostream>
using namespace std;

int main()
{
    string vaisius = "Agrastas";

    if (vaisius == "Vysnia")
    {
        cout << "Jus turite vysnia" << endl;
    } else if (vaisius == "Obuolys")
    {
        cout << "Jus turite obuoli" << endl;
    } else
    {
        cout << "Jus turite kitoki vaisiu" << endl;
    }

    int skaicius;

    cout << "Iveskite skaiciu: " << endl;
    cin >> skaicius;

    if (skaicius > 10 && skaicius % 5 == 0) {
        cout << "Jusu skaicius didesnis uz 10 ir dalijasi is 5" << endl;
    } else if (skaicius > 10 || skaicius % 4 == 0)
    {
        cout << "Jusu skaicius didesnis uz 10" << endl;
    } else
    {
        cout << "Jusu skaicius mazesnis uz 10" << endl;
    }

    return 0;

}