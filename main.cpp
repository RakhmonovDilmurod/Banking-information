#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>
#include <nlohmann/json.hpp>
#include <set>
#include <map>

namespace fs = std::filesystem;
using namespace std;
using json = nlohmann::json;

struct Borrower {
    int id;
    string first_name;
    string last_name;
    string date_of_birth;
    string passport_number;
};

struct Bank {
    int id;
    string name;
    string address;
};

struct Credit {
    int id;
    double amount;
    int count_of_month;
    double percent;
    string type;
    Borrower borrower;
    Bank bank;
    string car_model;
    string car_brand;
    string vin;
    string address_of_object;
    double square;
    string university_name;
    string university_address;

    double annuity_payment() {
        double monthly_interest_rate = percent / 100 / 12;
        double annuity_coefficient = (monthly_interest_rate * pow((1 + monthly_interest_rate), count_of_month)) /
                                     ((pow((1 + monthly_interest_rate), count_of_month)) - 1);
        return amount * annuity_coefficient;
    }
};

// Function to read data from JSON file
vector<Credit> read_data_from_json(const string& file_path) {
    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return {};
    }

    vector<Credit> credits;
    json j;
    file >> j;

    for (const auto& credit_json : j["credits"]) {
        Borrower borrower = {
            credit_json["Borrower"]["Id"],
            credit_json["Borrower"]["FirstName"],
            credit_json["Borrower"]["LastName"],
            credit_json["Borrower"]["DateOfBirth"],
            credit_json["Borrower"]["PassportNumber"]
        };

        Bank bank = {
            credit_json["Bank"]["Id"],
            credit_json["Bank"]["Name"],
            credit_json["Bank"]["Address"]
        };

        Credit credit = {
            credit_json["ID"],
            credit_json["Amount"],
            credit_json["CountOfMonth"],
            credit_json["Percent"],
            credit_json["Type"],
            borrower,
            bank,
            credit_json["CarModel"],
            credit_json["CarBrand"],
            credit_json["VIN"],
            credit_json["AddressOfObject"],
            credit_json["Square"],
            credit_json["UniversityName"],
            credit_json["UniversityAddress"]
        };

        credits.push_back(credit);
    }

    file.close();
    return credits;
}

// Function to print all credits
void get_all_credits(const vector<Credit>& credits) {
    cout << "ID кредита | Сумма кредита | Процентная ставка | Срок кредита | Тип кредита | Наименование банка | Фамилия и Имя заемщика" << endl;
    for (const auto& credit : credits) {
        cout << setw(10) << credit.id << " | " << setw(13) << credit.amount << " | " << setw(18) << credit.percent << " | "
             << setw(11) << credit.count_of_month << " | " << setw(11) << credit.type << " | "
             << setw(17) << credit.bank.name << " | " << credit.borrower.last_name << " " << credit.borrower.first_name << endl;
    }
}

void get_all_banks(const vector<Credit>& credits) {
    set<string> banks;
    for (const auto& credit : credits) {
        banks.insert(credit.bank.name);
    }
    cout << "Список всех банков:" << endl;
    for (const auto& bank : banks) {
        cout << bank << endl;
    }
}

void get_all_borrowers(const vector<Credit>& credits) {
    set<pair<string, string>> borrowers;
    for (const auto& credit : credits) {
        borrowers.insert({credit.borrower.last_name, credit.borrower.first_name});
    }
    cout << "Список всех заемщиков:" << endl;
    for (const auto& borrower : borrowers) {
        cout << borrower.first << " " << borrower.second << endl;
    }
}

void get_credits_by_type(const vector<Credit>& credits, const string& credit_type) {
    cout << "Список кредитов типа \"" << credit_type << "\":" << endl;
    for (const auto& credit : credits) {
        if (credit.type == credit_type) {
            cout << setw(10) << credit.id << " | " << setw(13) << credit.amount << " | " << setw(18) << credit.percent << " | "
                 << setw(11) << credit.count_of_month << " | " << setw(11) << credit.type << " | "
                 << setw(17) << credit.bank.name << " | " << credit.borrower.last_name << " " << credit.borrower.first_name << endl;
        }
    }
}

void add_new_credit(vector<Credit>& credits, const Credit& new_credit) {
    credits.push_back(new_credit);
    cout << "Новый кредит добавлен успешно." << endl;
}

void get_credits_by_borrower(const vector<Credit>& credits, const string& last_name) {
    cout << "Список кредитов для заемщика с фамилией \"" << last_name << "\":" << endl;
    for (const auto& credit : credits) {
        if (credit.borrower.last_name == last_name) {
            cout << setw(10) << credit.id << " | " << setw(13) << credit.amount << " | " << setw(18) << credit.percent << " | "
                 << setw(11) << credit.count_of_month << " | " << setw(11) << credit.type << " | "
                 << setw(17) << credit.bank.name << " | " << credit.borrower.last_name << " " << credit.borrower.first_name << endl;
        }
    }
}

int main() {
    string full_path_string = "information.json";
    vector<Credit> credits = read_data_from_json(full_path_string);

    int choice;
    do {
        cout << "Выберите действие:" << endl;
        cout << "1. Получить список всех кредитов" << endl;
        cout << "2. Получить список всех банков" << endl;
        cout << "3. Получить список всех заемщиков" << endl;
        cout << "4. Получить список кредитов по типу" << endl;
        cout << "5. Добавить новый кредит" << endl;
        cout << "6. Получить список кредитов для заданного заемщика" << endl;
        cout << "7. Выход" << endl;
        cout << "Введите номер действия: ";
        cin >> choice;

        switch (choice) {
            case 1:
                get_all_credits(credits);
                break;
            case 2:
                get_all_banks(credits);
                break;
            case 3:
                get_all_borrowers(credits);
                break;
            case 4: {
                string credit_type;
                cout << "Введите тип кредита (автокредит, ипотека или кредит на образование): ";
                cin >> credit_type;
                get_credits_by_type(credits, credit_type);
                break;
            }
           case 5: {
    cout << "Введите данные для нового кредита:" << endl;
    Credit new_credit;
    cout << "ID кредита: ";
    cin >> new_credit.id;
    cout << "Сумма кредита: ";
    cin >> new_credit.amount;
    cout << "Срок кредита в месяцах: ";
    cin >> new_credit.count_of_month;
    cout << "Процентная ставка: ";
    cin >> new_credit.percent;
    cout << "Тип кредита (автокредит, ипотека или кредит на образование): ";
    cin >> new_credit.type;
    cout << "ID заемщика: ";
    cin >> new_credit.borrower.id;
    cout << "Имя заемщика: ";
    cin >> new_credit.borrower.first_name;
    cout << "Фамилия заемщика: ";
    cin >> new_credit.borrower.last_name;
    cout << "Дата рождения заемщика (гггг-мм-дд): ";
    cin >> new_credit.borrower.date_of_birth;
    cout << "Номер паспорта заемщика: ";
    cin >> new_credit.borrower.passport_number;
    cout << "ID банка: ";
    cin >> new_credit.bank.id;
    cout << "Наименование банка: ";
    cin >> new_credit.bank.name;
    cout << "Адрес банка: ";
    cin >> new_credit.bank.address;
    
    if (new_credit.type == "автокредит") {
        cout << "Модель автомобиля: ";
        cin >> new_credit.car_model;
        cout << "Марка автомобиля: ";
        cin >> new_credit.car_brand;
        cout << "VIN код автомобиля: ";
        cin >> new_credit.vin;
    } else if (new_credit.type == "ипотека") {
        cout << "Адрес объекта ипотеки: ";
        cin >> new_credit.address_of_object;
        cout << "Площадь объекта ипотеки: ";
        cin >> new_credit.square;
    } else if (new_credit.type == "кредит на образование") {
        cout << "Название университета: ";
        cin >> new_credit.university_name;
        cout << "Адрес университета: ";
        cin >> new_credit.university_address;
    } else {
        cout << "Неверный тип кредита." << endl;
        break;
    }
    credits.push_back(new_credit);
    json j;
    for (const auto& credit : credits) {
        json credit_json = {
            {"ID", credit.id},
            {"Amount", credit.amount},
            {"CountOfMonth", credit.count_of_month},
            {"Percent", credit.percent},
            {"Type", credit.type},
            {"Borrower", {
                {"Id", credit.borrower.id},
                {"FirstName", credit.borrower.first_name},
                {"LastName", credit.borrower.last_name},
                {"DateOfBirth", credit.borrower.date_of_birth},
                {"PassportNumber", credit.borrower.passport_number}
            }},
            {"Bank", {
                {"Id", credit.bank.id},
                {"Name", credit.bank.name},
                {"Address", credit.bank.address}
            }}
        };
        if (credit.type == "автокредит") {
            credit_json["CarModel"] = credit.car_model;
            credit_json["CarBrand"] = credit.car_brand;
            credit_json["VIN"] = credit.vin;
        } else if (credit.type == "ипотека") {
            credit_json["AddressOfObject"] = credit.address_of_object;
            credit_json["Square"] = credit.square;
        } else if (credit.type == "кредит на образование") {
            credit_json["UniversityName"] = credit.university_name;
            credit_json["UniversityAddress"] = credit.university_address;
        }
        j["credits"].push_back(credit_json);
    }
    
    // Write JSON data to the file
    ofstream output_file(full_path_string);
    output_file << setw(4) << j << endl;
    output_file.close();
    
    cout << "Новый кредит успешно добавлен и записан в файл." << endl;
    break;
}

            case 6: {
                string last_name;
                cout << "Введите фамилию заемщика: ";
                cin >> last_name;
                get_credits_by_borrower(credits, last_name);
                break;
            }
            case 7:
                cout << "Программа завершена." << endl;
                break;
            default:
                cout << "Неверный выбор. Попробуйте еще раз." << endl;
        }

        cout << endl;
    } while (choice != 7);

    return 0;
}
