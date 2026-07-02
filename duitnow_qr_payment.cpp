#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <stdexcept>

using namespace std;

struct Transaction {
    string id;
    string type;
    double amount;
    double finalAmount;
    double balanceAfter;
};

string getTimestamp() {
    time_t now = time(0);
    return to_string(now);
}

double getNumber(string prompt) {
    string input;
    double value;

    while (true) {
        cout << prompt;
        getline(cin, input);

        try {
            value = stod(input);
            if (value < 0) throw invalid_argument("negative");
            return value;
        } catch (...) {
            cout << "Invalid input. Try again.\n";
        }
    }
}

string getType(int choice) {
    switch (choice) {
        case 1: return "Food & Beverages";
        case 2: return "Shopping & Retail";
        case 3: return "Bills & Utilities";
        case 4: return "Transfer";
        case 5: return "Donation";
        default: return "Invalid";
    }
}

void receipt(Transaction t) {
    cout << "\n================ RECEIPT ================\n";
    cout << "Transaction ID: " << t.id << "\n";
    cout << "Type: " << t.type << "\n";
    cout << "Amount: RM " << fixed << setprecision(2) << t.amount << "\n";
    cout << "Final Amount: RM " << t.finalAmount << "\n";
    cout << "Balance After: RM " << t.balanceAfter << "\n";
    cout << "========================================\n";
}

int main() {
    double balance = getNumber("Enter wallet balance: ");

    while (true) {
        cout << "\n====== MENU ======\n";
        cout << "1. Food\n2. Shopping\n3. Bills\n4. Transfer\n5. Donation\n6. Exit\n";
        cout << "Choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 6) break;

        string type = getType(choice);
        if (type == "Invalid") {
            cout << "Invalid choice.\n";
            break;
        }

        cout << "Selected: " << type << "\n";

        double amount = getNumber("Enter amount: ");

        double cashbackRate = 0, feeRate = 0;

        switch (choice) {
            case 1: cashbackRate = 0.05; break;
            case 2: cashbackRate = 0.03; break;
            case 3: cashbackRate = 0.01; feeRate = 0.01; break;
        }

        bool highRisk = (amount > balance * 0.5 || amount > 5000);

        if (highRisk) {
            cout << "\nWARNING: High-risk transaction!\n";
        }

        double cashback = amount * cashbackRate;
        double fee = amount * feeRate;
        double finalAmount = amount + fee - cashback;

        if (finalAmount > balance) {
            cout << "Insufficient balance.\n";
            continue;
        }

        Transaction t;
        t.id = "TXN" + getTimestamp();
        t.type = type;
        t.amount = amount;
        t.finalAmount = finalAmount;
        t.balanceAfter = balance - finalAmount;

        balance = t.balanceAfter;

        receipt(t);

        cout << "Continue? (y/n): ";
        char c;
        cin >> c;
        cin.ignore();

        if (c != 'y' && c != 'Y') break;
    }

    cout << "\nFinal balance: RM " << balance << "\n";
    return 0;
}