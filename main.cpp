#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

const int MAX_MENU_ITEMS = 50;
const double PVM = 0.21;

struct menuItemType {
    string menuItem;
    double menuPrice;
};

void getData(menuItemType menuList[], int &itemCount);

void showMenu(const menuItemType menuList[], int itemCount);

void printCheck(const menuItemType menuList[], const int orderCount[], int itemCount);

int main() {
    menuItemType menuList[MAX_MENU_ITEMS];
    int itemCount = 0;

    getData(menuList, itemCount);

    if (itemCount == 0) return 1;

    int orderCount[MAX_MENU_ITEMS] = {0};

    showMenu(menuList, itemCount);

    int pasirinkimas, kiekis;
    char testi = 't';

    while (testi == 't' || testi == 'T') {
        cout << "\nIveskite patiekalo numeri: ";
        cin >> pasirinkimas;

        cout << "iveskite kieki: ";
        cin >> kiekis;

        orderCount[pasirinkimas - 1] += kiekis;

        cout << "Ar testi uzsakyma? (t/n): ";
        cin >> testi;
    }

    printCheck(menuList, orderCount, itemCount);

    return 0;
}

void getData(menuItemType menuList[], int &itemCount) {
    ifstream file("C:\\Users\\ignas\\CLionProjects\\darbas su failais\\menu.txt");
    if (!file.is_open()) {
        cout << "Klaida: nepavyko atidaryti failo" << endl;
        return;
    }

    string pavadinimas;
    double kaina;

    while (itemCount < MAX_MENU_ITEMS && file >> pavadinimas) {
        while (!(file >> kaina)) {
            file.clear();
            string tesinys;
            file >> tesinys;
            pavadinimas = pavadinimas + " " + tesinys;
        }

        menuList[itemCount].menuItem = pavadinimas;
        menuList[itemCount].menuPrice = kaina;
        itemCount++;
    }
    file.close();
}

void showMenu(const menuItemType menuList[], int itemCount) {
    cout << "--- Meniu---" << endl;
    for (int i = 0; i < itemCount; i++) {
        cout << i + 1 << ". " << left << setw(40) << menuList[i].menuItem
                << fixed << setprecision(2) << menuList[i].menuPrice << "EUR" << endl;
    }
    cout << "--------------" << endl;
}

void printCheck(const menuItemType menuList[], const int orderCount[], int itemCount) {
    ofstream outFile("C:\\Users\\ignas\\CLionProjects\\darbas su failais\\receipt.txt");
    double tarpineSuma = 0;

    cout << "\nAciu, kad apsilankete" << endl;
    cout << "Cekis\n" << endl;
    for (int i = 0; i < itemCount; i++) {
        if (orderCount[i] > 0) {
            double suma = menuList[i].menuPrice * orderCount[i];
            tarpineSuma += suma;
            cout << orderCount[i] << " " << suma << " EUR" << endl;
        }
    }
    double pvmSuma = tarpineSuma * PVM;
    double galutine = tarpineSuma + pvmSuma;

    cout << "\nMokesciai (21%): " << fixed << setprecision(2) << pvmSuma << " EUR" << endl;
    cout << "Galutine suma : " << fixed << setprecision(2) << galutine << " EUR" << endl;

    outFile << "Aciu, kad apsilankete" << endl;
    outFile << "Cekis\n" << endl;
    for (int i = 0; i < itemCount; i++) {
        if (orderCount[i] > 0) {
            double suma = menuList[i].menuPrice * orderCount[i];
            outFile << orderCount[i] << " " << left << setw(40) << menuList[i].menuItem
                    << fixed << setprecision(2) << suma << " EUR" << endl;
        }
    }
    outFile << "\nMokesciai (21%): " << fixed << setprecision(2) << pvmSuma << " EUR" << endl;
    outFile << "Galutine suma: " << fixed << setprecision(2) << galutine << " EUR" << endl;

    outFile.close();
    cout << "\nSaskaita issaugota Cekiu faile" << endl;
}
