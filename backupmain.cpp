#include <iostream>
#include <vector>

#include "field.h"
#include "ship.h"
#include "manager.h"
#include "abilityManager.h"

using namespace std;

int main() {
    int size;
    while (1) {
        try {
            cout << "Введите размер поля: ";
            cin >> size;
            if (cin.fail() || size < 2 || size > 20) {
                throw IncorrectFieldSize("Ошибка ввода! Размер поля - это число от 2 до 20.");
            }
            break;
        } catch (IncorrectFieldSize& e) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << e.what() << '\n';
        }
    }

    int ships[4];
    cout << "Игра морской бой начинается." << '\n';
    for (int i = 0; i < 4; i++) {
        while (1) {
            try {
                cout << "Введите количество кораблей длины " << i + 1 << ": ";
                cin >> ships[i];
                if (cin.fail() || ships[i] < 0 || ships[i] > 10) {
                    throw IncorrectQuantity("Ошибка ввода! Количество кораблей - это число от 0 до 10.");
                }
                break;
            } catch (IncorrectQuantity& e) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << e.what() << '\n';
            }
        }
    }

    int countShip = ships[0] + ships[1] + ships[2] + ships[3];
    shipManager managers(countShip, ships);
    Field userfield(size, &managers);
    userfield.create_field();

    for (int j = 0; j < 4; j++) {
        if (ships[j] > 0) {
            cout << "Введите координаты и ориентацию кораблей в формате x y 0, где 0 обозначает горизонтальное расположение, а 1 вертикальное. Длина: " << j + 1 << '\n';
        }
        for (int i = 0; i < ships[j]; i++) {
            int x, y, orientation;
            flag_error = 0;
            while (1) {
                try {
                    cout << "x y orientation: ";
                    cin >> x >> y >> orientation;
                    if (cin.fail()) {
                        throw invalid_argument("Ошибка ввода! Пожалуйста, введите целые числа.");
                    }
                    if (flag_error == 0) {
                        managers.create_ship(j + 1, orientation, x, y);
                        userfield.put_ship();
                    } else {
                        Ship& current_ship = managers.getship();
                        current_ship.setorientation(orientation);
                        current_ship.input_coordinates(x, y);
                        userfield.put_ship();
                    }
                    break;
                } catch (IncorrectCoordinatesException& e) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << e.what() << '\n';
                    flag_error = 1;
                } catch (PlaceShipException& e) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << e.what() << e.getxerror() << ' ' << e.getyerror() << '\n';
                    flag_error = 1;
                } catch (invalid_argument& e) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << e.what() << '\n';
                }
            }
        }
    }

    AbilityManager abilitymanager(&userfield, &managers);
    int number_ships = managers.getnumbership();

    while (1) {
        if (!abilitymanager.is_empty()) {
            string flag_ability;
            cout << "Чтобы активировать способность, введите Y: ";
            cin >> flag_ability;
            if (flag_ability == "Y") {
                cout << "Активирована способность.\n";
                abilitymanager.apply_ability();
            } else {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        int x, y;
        while (1) {
            try {
                cout << "Введите координаты для атаки. x y: ";
                cin >> x >> y;
                if (cin.fail()) {
                    throw IncorrectCoordinatesException("Ошибка ввода! Пожалуйста, введите целые числа.");
                }
                userfield.attack_segment(x, y);
                break;
            } catch (IncorrectCoordinatesException& e) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << e.what() << '\n';
            }
        }

        userfield.print_field_user();
        cout << endl;
        userfield.print_field_opponent();

        if (number_ships - managers.getnumbership() >= 1) {
            abilitymanager.add_ability();
            number_ships = managers.getnumbership();
        }
    }

    return 0;
}
