#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <iomanip>
#include<cmath>
#include <algorithm>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

struct Bank {
    int id;
    string name;
    string address;

    Bank(int i = 0, const string& n = "", const string& a = "") : id(i), name(n), address(a) {}
};

struct Borrower {
    int id;
    string firstName;
    string lastName;
    string dateOfBirth;
    string passportNumber;

    Borrower(int i = 0, const string& fn = "", const string& ln = "", const string& dob = "", const string& pn = "") : id(i), firstName(fn), lastName(ln), dateOfBirth(dob), passportNumber(pn) {}
};

struct CreditContract {
    int id;
    double amount;
    int countOfMonth;
    double percent;
    double square;
    string type;
    Bank bank;
    Borrower borrower;
    string carModel;
    string carBrand;
    string vin;
    string addressOfObject;
    string universityName;
    string universityAddress;

    CreditContract(int i = 0, double a = 0, int com = 0, double p = 0, const string& t = "", const Bank& b = Bank(), const Borrower& bo = Borrower(), const string& cm = "", const string& cb = "", const string& v = "", const string& ao = "", double s = 0.0, const string& un = "", const string& ua = "") : id(i), amount(a), countOfMonth(com), percent(p), type(t), bank(b), borrower(bo), carModel(cm), carBrand(cb), vin(v), addressOfObject(ao), square(s), universityName(un), universityAddress(ua) {}
};

vector<CreditContract> readCreditContractsFromFile(const string& filename) {
    vector<CreditContract> contracts;
    ifstream file(filename);

    if (file.is_open()) {
        json j;
        file >> j;

        for (auto& el : j) {
            int id, countOfMonth;
            double amount, percent, square;
            string type, carModel, carBrand, vin, addressOfObject, universityName, universityAddress;
            Bank bank;
            Borrower borrower;

            id = el["id"];
            amount = el["amount"];
            countOfMonth = el["countOfMonth"];
            percent = el["percent"];
            type = el["type"];
            bank.id = el["bank"]["id"];
            bank.name = el["bank"]["name"];
            bank.address = el["bank"]["address"];
            borrower.id = el["borrower"]["id"];
            borrower.firstName = el["borrower"]["firstName"];
            borrower.lastName = el["borrower"]["lastName"];
            borrower.dateOfBirth = el["borrower"]["dateOfBirth"];
            borrower.passportNumber = el["borrower"]["passportNumber"];
            carModel = el["carModel"];
            carBrand = el["carBrand"];
            vin = el["vin"];
            addressOfObject = el["addressOfObject"];
            square = el["square"];
            universityName = el["universityName"];
            universityAddress = el["universityAddress"];

            CreditContract contract(id, amount, countOfMonth, percent, type, bank, borrower, carModel, carBrand, vin, addressOfObject, square, universityName, universityAddress);
            contracts.push_back(contract);
        }
    }

    return contracts;
}

void writeCreditContractsToFile(const vector<CreditContract>& contracts, const string& filename) {
    json j;

    for (const auto& contract : contracts) {
        json c;
        c["id"] = contract.id;
        c["amount"] = contract.amount;
        c["countOfMonth"] = contract.countOfMonth;
        c["percent"] = contract.percent;
        c["type"] = contract.type;
        c["bank"]["id"] = contract.bank.id;
        c["bank"]["name"] = contract.bank.name;
        c["bank"]["address"] = contract.bank.address;
        c["borrower"]["id"] = contract.borrower.id;
        c["borrower"]["firstName"] = contract.borrower.firstName;
        c["borrower"]["lastName"] = contract.borrower.lastName;
        c["borrower"]["dateOfBirth"] = contract.borrower.dateOfBirth;
        c["borrower"]["passportNumber"] = contract.borrower.passportNumber;
        c["carModel"] = contract.carModel;
        c["carBrand"] = contract.carBrand;
        c["vin"] = contract.vin;
        c["addressOfObject"] = contract.addressOfObject;
        c["square"] = contract.square;
        c["universityName"] = contract.universityName;
        c["universityAddress"] = contract.universityAddress;

        j.push_back(c);
    }

    ofstream file(filename);
    file << j.dump(4);
}

void displayCreditContract(const CreditContract& contract) {
    cout << left << setw(10) << contract.id << setw(15) << contract.amount << setw(15) << contract.percent << setw(15) << contract.countOfMonth;

    if (contract.type == "auto") {
        cout << setw(15) << contract.type << setw(20) << contract.bank.name << setw(20) << contract.borrower.lastName << " " << contract.borrower.firstName << setw(15) << contract.carModel << setw(15) << contract.carBrand << setw(15) << contract.vin << endl;
    } else if (contract.type == "mortgage") {
        cout << setw(15) << contract.type << setw(20) << contract.bank.name << setw(20) << contract.borrower.lastName << " " << contract.borrower.firstName << setw(15) << contract.addressOfObject << setw(15) << contract.square << endl;
    } else if (contract.type == "education") {
        cout << setw(15) << contract.type << setw(20) << contract.bank.name << setw(20) << contract.borrower.lastName << " " << contract.borrower.firstName << setw(15) << contract.universityName << setw(15) << contract.universityAddress << endl;
    }
}

void displayAllCreditContracts(const vector<CreditContract>& contracts) {
    cout << "ID кредита | Сумма кредита | Процентная ставка | Срок кредита | Тип кредита | Наименование банка | Фамилия и Имя заемщика";

    if (contracts[0].type == "auto") {
        cout << setw(15) << "Модель авто" << setw(15) << "Марка авто" << setw(15) << "VIN код" << endl;
    } else if (contracts[0].type == "mortgage") {
        cout << setw(15) << "Адрес объекта" << setw(15) << "Площадь" << endl;
    } else if (contracts[0].type == "education") {
        cout << setw(15) << "Название университета" << setw(15) << "Адрес университета" << endl;
    }

    for (const auto& contract : contracts) {
        displayCreditContract(contract);
    }
}

void displayAllBanks(const vector<CreditContract>& contracts) {
    map<int, string> bankIds;
    for (const auto& contract : contracts) {
        if (bankIds.find(contract.bank.id) == bankIds.end()) {
            bankIds[contract.bank.id] = contract.bank.name;
        }
    }

    cout << "ID банка | Наименование банка" << endl;
    for (const auto& bank : bankIds) {
        cout << left << setw(10) << bank.first << setw(20) << bank.second << endl;
    }
}

void displayAllBorrowers(const vector<CreditContract>& contracts) {
    map<int, pair<string, string>> borrowerIds;
    for (const auto& contract : contracts) {
        if (borrowerIds.find(contract.borrower.id) == borrowerIds.end()) {
            borrowerIds[contract.borrower.id] = make_pair(contract.borrower.lastName, contract.borrower.firstName);
        }
    }

    cout << "ID заемщика | Фамилия заемщика | Имя заемщика" << endl;
    for (const auto& borrower : borrowerIds) {
        cout << left << setw(10) << borrower.first << setw(20) << borrower.second.first << setw(20) << borrower.second.second << endl;
    }
}

void displayCreditContractsByType(const vector<CreditContract>& contracts, const string& type) {
    vector<CreditContract> filteredContracts;
    for (const auto& contract : contracts) {
        if (contract.type == type) {
            filteredContracts.push_back(contract);
        }
    }

    cout << "ID кредита | Сумма кредита | Процентная ставка | Срок кредита | Тип кредита | Наименование банка | Фамилия и Имя заемщика";

    if (filteredContracts[0].type == "auto") {
        cout << setw(15) << "Модель авто" << setw(15) << "Марка авто" << setw(15) << "VIN код" << endl;
    } else if (filteredContracts[0].type == "mortgage") {
        cout << setw(15) << "Адрес объекта" << setw(15) << "Площадь" << endl;
    } else if (filteredContracts[0].type == "education") {
        cout << setw(15) << "Название университета" << setw(15) << "Адрес университета" << endl;
    }

    for (const auto& contract : filteredContracts) {
        displayCreditContract(contract);
    }
}

void displayCreditContractsByBorrower(const vector<CreditContract>& contracts, const string& lastName, const string& firstName) {
    vector<CreditContract> filteredContracts;
    for (const auto& contract : contracts) {
        if (contract.borrower.lastName == lastName && contract.borrower.firstName == firstName) {
            filteredContracts.push_back(contract);
        }
    }

    cout << "ID кредита | Сумма кредита | Процентная ставка | Срок кредита | Тип кредита | Наименование банка | Фамилия и Имя заемщика";

    if (filteredContracts[0].type == "auto") {
        cout << setw(15) << "Модель авто" << setw(15) << "Марка авто" << setw(15) << "VIN код" << endl;
    } else if (filteredContracts[0].type == "mortgage") {
        cout << setw(15) << "Адрес объекта" << setw(15) << "Площадь" << endl;
    } else if (filteredContracts[0].type == "education") {
        cout << setw(15) <<"Название университета" << setw(15) << "Адрес университета" << endl;
    }

    for (const auto& contract : filteredContracts) {
        displayCreditContract(contract);
    }
}

CreditContract createNewCreditContract() {
    int id, countOfMonth;
    double amount, percent,square;
    string type, carModel, carBrand, vin, addressOfObject, universityName, universityAddress;
    Bank bank;
    Borrower borrower;

    cout << "Enter ID: ";
    cin >> id;
    cout << "Enter amount: ";
    cin >> amount;
    cout << "Enter count of month: ";
    cin >> countOfMonth;
    cout << "Enter percent: ";
    cin >> percent;
    cout << "Enter type (auto/mortgage/education): ";
    cin >> type;

    if (type == "auto") {
        cout << "Enter car model: ";
        cin >> carModel;
        cout << "Enter car brand: ";
        cin >> carBrand;
        cout << "Enter VIN: ";
        cin >> vin;
    } else if (type == "mortgage") {
        cout << "Enter address of object: ";
        cin >> addressOfObject;
        cout << "Enter square: ";
        cin >> square;
    } else if (type == "education") {
        cout << "Enter university name: ";
        cin >> universityName;
        cout << "Enter university address: ";
        cin >> universityAddress;
    }

    cout << "Enter bank id: ";
    cin >> bank.id;
    cout << "Enter bank name: ";
    cin.ignore();
    getline(cin, bank.name);
    cout << "Enter bank address: ";
    getline(cin, bank.address);

    cout << "Enter borrower id: ";
    cin >> borrower.id;
    cout << "Enter borrower first name: ";
    cin >> borrower.firstName;
    cout << "Enter borrower last name: ";
    cin >> borrower.lastName;
    cout << "Enter borrower date of birth: ";
    cin >> borrower.dateOfBirth;
    cout << "Enter borrower passport number: ";
    cin >> borrower.passportNumber;

    CreditContract contract(id, amount, countOfMonth, percent, type, bank, borrower, carModel, carBrand, vin, addressOfObject, square, universityName, universityAddress);
    return contract;
}

double calculateMonthlyAnnuityPayment(const CreditContract& contract) {
    double monthlyInterestRate = contract.percent / 12 / 100;
    double divisor = pow(1 + monthlyInterestRate, contract.countOfMonth) - 1;
    double coefficient = monthlyInterestRate * pow(1 + monthlyInterestRate, contract.countOfMonth) / divisor;
    return coefficient * contract.amount;
}

int main() {
    vector<CreditContract> contracts = readCreditContractsFromFile("information.json");

    while (true) {
        cout << "1. Display all credit contracts\n2. Display all banks\n3. Display all borrowers\n4. Display credit contracts by type\n5. Display credit contracts by borrower\n6. Create new credit contract\n7. Calculate monthly annuity payment\n8. Exit\n";
        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            displayAllCreditContracts(contracts);
            break;
        case 2:
            displayAllBanks(contracts);
            break;
        case 3:
            displayAllBorrowers(contracts);
            break;
        case 4: {
            cout << "Enter type: ";
            string type;
            cin >> type;
            displayCreditContractsByType(contracts, type);
            break;
        }
        case 5: {
            cout << "Enter last name: ";
            string lastName;
            cin >> lastName;
            cout << "Enter first name: ";
            string firstName;
            cin >> firstName;
            displayCreditContractsByBorrower(contracts, lastName, firstName);
           break;
        }
        case 6:
            contracts.push_back(createNewCreditContract());
            writeCreditContractsToFile(contracts, "information.json");
            break;
        case 7: {
            cout << "Enter ID: ";
            int id;
            cin >> id;
            for (auto& contract : contracts) {
                if (contract.id == id) {
                    cout << "Monthly annuity payment: " << calculateMonthlyAnnuityPayment(contract) << endl;
                    break;
                }
            }
            break;
        }
        case 8:
            return 0;
        default:
            cout << "Invalid choice\n";
            break;
        }
    }

    return 0;
}