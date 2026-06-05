#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_MENU_ITEMS = 50;

struct menuItemType {
    string menuItem;
    double menuPrice;
};

void getData(menuItemType menuList[], int &itemCount);

int main() {
    menuItemType menuList[MAX_MENU_ITEMS];
    int itemCount = 0;

    getData(menuList, itemCount);

    cout << "Nuskaityta elementu: " << itemCount << endl;

    return 0;
}
void getData(menuItemType menuList[], int &itemCount) {
    ifstream file("C:\\Users\\ignas\\CLionProjects\\darbas su failais\\menu.txt");
    if (!file.is_open()) return;

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