#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <iomanip>
#include<cmath>
#include <algorithm>

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
    string type;
    Bank bank;
    Borrower borrower;
    string carModel;
    string carBrand;
    string vin;
    string addressOfObject;
    double square;
    string universityName;
    string universityAddress;

    CreditContract(int i = 0, double a = 0, int com = 0, double p = 0, const string& t = "", const Bank& b = Bank(), const Borrower& bo = Borrower(), const string& cm = "", const string& cb = "", const string& v = "", const string& ao = "", double s = 0, const string& un = "", const string& ua = "") : id(i), amount(a), countOfMonth(com), percent(p), type(t), bank(b), borrower(bo), carModel(cm), carBrand(cb), vin(v), addressOfObject(ao), square(s), universityName(un), universityAddress(ua) {}
};

vector<CreditContract> readCreditContractsFromFile(const string& filename) {
    vector<CreditContract> contracts;
    ifstream file(filename);

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            int id, countOfMonth;
            double amount, percent;
            string type, carModel, carBrand, vin, addressOfObject, universityName, universityAddress;
            getline(iss, type, ',');
            type.erase(remove(type.begin(), type.end(), '\"'), type.end());
            getline(iss, carModel, ',');
            carModel.erase(remove(carModel.begin(), carModel.end(), '\"'), carModel.end());
            getline(iss, carBrand, ',');
            carBrand.erase(remove(carBrand.begin(), carBrand.end(), '\"'), carBrand.end());
            getline(iss, vin, ',');
            vin.erase(remove(vin.begin(), vin.end(), '\"'), vin.end());
            getline(iss, addressOfObject, ',');
            addressOfObject.erase(remove(addressOfObject.begin(), addressOfObject.end(), '\"'), addressOfObject.end());
            getline(iss, universityName, ',');
            universityName.erase(remove(universityName.begin(), universityName.end(), '\"'), universityName.end());
            getline(iss, universityAddress, ',');
            universityAddress.erase(remove(universityAddress.begin(), universityAddress.end(), '\"'), universityAddress.end());
            getline(iss, type, ',');
            getline(iss, type, ',');
            getline(iss, type, ',');
            iss >> id >> amount >> countOfMonth >> percent;
            getline(iss, type, ',');
            getline(iss, type, ',');
            getline(iss, type, ',');
            int bankId, bankNameLength, bankAddressLength;
            iss >> bankId >> bankNameLength >> bankNameLength >> bankNameLength;
            string bankName(bankNameLength, ' ');
            iss >> bankName;
            string bankAddress;
            getline(iss, bankAddress, ',');
            getline(iss, type, ',');
            int borrowerId, firstNameLength, lastNameLength, dateOfBirthLength, passportNumberLength;
            iss >> borrowerId >> firstNameLength >> lastNameLength >> dateOfBirthLength >> passportNumberLength;
            string firstName(firstNameLength, ' ');
            iss >> firstName;
            string lastName;
            getline(iss, lastName, ',');
            lastName.erase(remove(lastName.begin(), lastName.end(), '\"'), lastName.end());
            string dateOfBirth;
            getline(iss, dateOfBirth, ',');
            dateOfBirth.erase(remove(dateOfBirth.begin(), dateOfBirth.end(), '\"'), dateOfBirth.end());
            string passportNumber;
            getline(iss, passportNumber, ',');
            passportNumber.erase(remove(passportNumber.begin(), passportNumber.end(), '\"'), passportNumber.end());

            Bank bank(bankId, bankName, bankAddress);
            Borrower borrower(borrowerId, firstName, lastName, dateOfBirth, passportNumber);

            CreditContract contract(id, amount, countOfMonth,percent, type, bank, borrower, carModel, carBrand, vin, addressOfObject, 0, universityName, universityAddress);
            contracts.push_back(contract);
        }
        file.close();
    }

    return contracts;
}

void displayCreditContract(const CreditContract& contract) {
    cout << left << setw(10) << contract.id << setw(15) << contract.amount << setw(15) << contract.percent << setw(15) << contract.countOfMonth << setw(15) << contract.type << setw(20) << contract.bank.name << setw(20) << contract.borrower.lastName << " " << contract.borrower.firstName << endl;
}

void displayAllCreditContracts(const vector<CreditContract>& contracts) {
    cout << "ID кредита | Сумма кредита | Процентная ставка | Срок кредита | Тип кредита | Наименование банка | Фамилия и Имя заемщика" << endl;
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

    cout << "ID кредита | Сумма кредита | Процентная ставка | Срок кредита | Тип кредита | Наименование банка | Фамилия и Имя заемщика" << endl;
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

    cout << "ID кредита | Сумма кредита | Процентная ставка | Срок кредита | Тип кредита | Наименование банка | Фамилия и Имя заемщика" << endl;
    for (const auto& contract : filteredContracts) {
        displayCreditContract(contract);
    }
}

CreditContract createNewCreditContract() {
    int id, countOfMonth;
    double amount, percent;
    string type, carModel, carBrand, vin, addressOfObject, universityName, universityAddress;
    cout << "Enter ID: ";
    cin >> id;
    cout << "Enter amount: ";
    cin >> amount;
    cout << "Enter count of month: ";
    cin >> countOfMonth;
    cout << "Enter percent: ";
    cin >> percent;
    cout << "Enter type: ";
    cin >> type;
    cout << "Enter car model: ";
    cin >> carModel;
    cout << "Enter car brand: ";
    cin >> carBrand;
    cout << "Enter vin: ";
    cin >> vin;
    cout << "Enter address of object: ";
    cin >> addressOfObject;
    cout << "Enter university name: ";
    cin >> universityName;
    cout << "Enter university address: ";
    cin >> universityAddress;

    Bank bank;
    Borrower borrower;

    CreditContract contract(id, amount, countOfMonth, percent, type, bank, borrower, carModel, carBrand, vin, addressOfObject, 0, universityName, universityAddress);
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