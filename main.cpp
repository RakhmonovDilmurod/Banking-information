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
    ifstream file("information.json");

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
            carModel.erase(remove(carModel.begin(), carModel.end(),'\"'), carModel.end());
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

            CreditContract contract(id, amount, countOfMonth, percent, type, bank, borrower, carModel, carBrand, vin, addressOfObject, 0, universityName, universityAddress);
            contracts.push_back(contract);
        }
        file.close();
    }

    return contracts;
}

void displayCreditContract(const CreditContract& contract) {
    cout << "ID: " << contract.id << ", Amount: " << contract.amount << ", Count of Month: " << contract.countOfMonth << ", Percent: " << contract.percent << ", Type: " << contract.type << ", Bank: " << contract.bank.name << ", Borrower: " << contract.borrower.lastName << " " << contract.borrower.firstName << endl;
}

void displayAllCreditContracts(const vector<CreditContract>& contracts) {
    for (const auto& contract : contracts) {
        displayCreditContract(contract);
    }
}

void displayAllBanks(const vector<CreditContract>& contracts) {
    map<int, string> bankMap;
    for (const auto& contract : contracts) {
        bankMap[contract.bank.id] = contract.bank.name;
    }

    cout << "Banks:" << endl;
    for (const auto& bank : bankMap) {
        cout << bank.first << ": " << bank.second << endl;
    }
}

void displayAllBorrowers(const vector<CreditContract>& contracts) {
    map<int, pair<string, string>> borrowerMap;
    for (const auto& contract : contracts) {
        borrowerMap[contract.borrower.id] = make_pair(contract.borrower.lastName, contract.borrower.firstName);
    }

    cout << "Borrowers:" << endl;
    for (const auto& borrower : borrowerMap) {
        cout << borrower.first << ": " << borrower.second.first << " " << borrower.second.second << endl;
    }
}

void displayCreditContractsByType(const vector<CreditContract>& contracts, const string& type) {
    vector<CreditContract> filteredContracts;
    for (const auto& contract : contracts) {
        if (contract.type == type) {
            filteredContracts.push_back(contract);
        }
    }

    cout << "Credit Contracts by Type: " << type << endl;
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

    cout << "Credit Contracts by Borrower: " << lastName << " " << firstName << endl;
    for (const auto& contract : filteredContracts) {
        displayCreditContract(contract);
    }
}

double calculateMonthlyAnnuityPayment(const CreditContract& contract) {
    double monthlyInterestRate = contract.percent / 12 / 100;
    double denominator = pow(1 + monthlyInterestRate, contract.countOfMonth) - 1;
    double coefficient = monthlyInterestRate * pow(1 + monthlyInterestRate, contract.countOfMonth) / denominator;

    return contract.amount * coefficient;
}

int main() {
    vector<CreditContract> contracts = readCreditContractsFromFile("information.json");

    while (true) {
        cout << "\nChoose an option:" << endl;
        cout << "1. Display all credit contracts" << endl;
        cout << "2. Display all banks" << endl;
        cout << "3. Display all borrowers" << endl;
        cout << "4. Display credit contracts by type" << endl;
        cout << "5. Display credit contracts by borrower" << endl;
        cout << "6. Add a new credit contract" << endl;
        cout << "7. Calculate monthly annuity payment" << endl;
        cout << "8. Exit" << endl;

        int choice;
        cin >> choice;

        if (choice == 1) {
            displayAllCreditContracts(contracts);
        } else if (choice == 2) {
            displayAllBanks(contracts);
        } else if (choice == 3) {
            displayAllBorrowers(contracts);
        } else if (choice == 4) {
            string type;
            cout << "Enter the type: ";
            cin >> type;
            displayCreditContractsByType(contracts, type);
        } else if (choice == 5) {
            string lastName, firstName;
            cout << "Enter the last name: ";
            cin >> lastName;
            cout << "Enter the first name: ";
            cin >> firstName;
            displayCreditContractsByBorrower(contracts, lastName, firstName);
        } else if (choice == 6) {
            // Add a new credit contract
        } else if (choice == 7) {
            int id;
            cout << "Enter the ID of the credit contract: ";
            cin >> id;
            for (auto& contract : contracts) {
                if (contract.id == id) {
                    double monthlyPayment = calculateMonthlyAnnuityPayment(contract);
                    cout << "Monthly Annuity Payment: " << fixed << setprecision(2) << monthlyPayment << endl;
                    break;
                }
            }
        } else if (choice == 8) {
            break;
        } else {
            cout << "Invalid option. Please try again." << endl;
        }
    }

    return 0;
}