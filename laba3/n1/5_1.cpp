#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

const int MAX_UNITS_PRODUCT = 10;
const int ZONES = 10, SECTIONS = 3, SHELVES = 1, POLKS = 5;
const int TOTAL_CELLS = ZONES * SECTIONS * SHELVES * POLKS;
const int TOTAL_CAPACITY = TOTAL_CELLS * MAX_UNITS_PRODUCT;

unordered_map<string, unordered_map<string, int>> tovar;

void ADD(const string& name, int qty, const string& address) {
    int currentQty = 0;
    if (tovar.count(address)) {
        for (const auto& it : tovar[address])
            currentQty += it.second;
    }

    if (currentQty + qty > MAX_UNITS_PRODUCT) {
        cout << "Ошибка: ячейка полная " << address << ". Сейчас: " << currentQty << ", максимум: " << MAX_UNITS_PRODUCT << "\n";
        return;
    }

    tovar[address][name] += qty;
    cout << "Добавлено " << qty << " " << name << " в ячейку " << address << "\n";
}

void REMOVE(const string& name, int qty, const string& address) {
    if (!tovar.count(address) || !tovar[address].count(name)) {
        cout << "Ошибка: товара '" << name << "' нет в ячейке " << address << "\n";
        return;
    }

    if (tovar[address][name] < qty) {
        cout << "Ошибка: недостаточно '" << name << "' в ячейке " << address << "\n";
        return;
    }
    cout << "Удалено " << qty << " '" << name << "' из ячейки " << address << "\n";
}

void INFO() {
    int used = 0;
    for (const auto& [address, contents] : tovar) {
        for (const auto& [name, qty] : contents)
            used += qty;
    }

    double percent = (100.0 * used) / TOTAL_CAPACITY;

    cout << fixed << setprecision(2);
    cout << "Заполненность склада: " << percent << "%\n";

    cout << "Содержимое занятых ячеек:\n";
    for (const auto& [address, contents] : tovar) {
        cout << address << ": ";
        for (const auto& [name, qty] : contents)
            cout << name << "(" << qty << ") ";
        cout << "\n";
    }

    int empty = TOTAL_CELLS - tovar.size();
    cout << "Пустых ячеек: " << empty << "\n";
}

int main() {
    string command;
    cout << "Перечень команд: ADD, REMOVE, INFO\n";

    while (true) {
        cout << "\nВведите команду: ";
        getline(cin, command);
        stringstream ss(command);
        string op, name, address;
        int qty;

        ss >> op;
        if (op == "ADD") {
            ss >> name >> qty >> address;
            ADD(name, qty, address);
        } else if (op == "REMOVE") {
            ss >> name >> qty >> address;
            REMOVE(name, qty, address);
        } else if (op == "INFO") {
            INFO();
        } else if (op == "") {
            break;
        }
        
    }

    return 0;
}