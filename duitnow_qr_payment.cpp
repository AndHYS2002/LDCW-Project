#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <ctime>

using namespace std;

// Structure to store transaction details
struct Transaction {
    string transactionID;
    string paymentType;
    double amount;
    double cashback;
    double serviceFee;
    double finalAmount;
    double balanceBefore;
    double balanceAfter;
    string timestamp;
    string status;
};

// Function to generate transaction ID
string generateTransactionID() {
    time_t now = time(0);
    return "TXN" + to_string(now);
}

// Function to get current timestamp
string getCurrentTimestamp() {
    time_t now = time(0);
    char buffer[80];
    struct tm* timeinfo = localtime(&now);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    return string(buffer);
}

// Function to display main menu
void displayMainMenu() {
    cout << "\n" << string(60, '=') << endl;
    cout << "    DuitNow QR Payment System - Malaysia" << endl;
    cout << "    Fostering Inclusive Digital Payments" << endl;
    cout << string(60, '=') << endl;
}

// Function to display payment type menu
void displayPaymentTypeMenu() {
    cout << "\n--- SELECT PAYMENT TYPE ---" << endl;
    cout << "1. Food & Beverages" << endl;
    cout << "2. Shopping & Retail" << endl;
    cout << "3. Bills & Utilities" << endl;
    cout << "4. Peer-to-Peer Transfer" << endl;
    cout << "5. Donation" << endl;
    cout << "6. Exit" << endl;
    cout << "Enter your choice (1-6): ";
}

// Function to get payment type details
void getPaymentTypeDetails(int choice, string& paymentType, double& cashbackRate, double& serviceFeeRate, bool& isHighRisk) {
    switch(choice) {
        case 1: // Food & Beverages
            paymentType = "Food & Beverages";
            cashbackRate = 0.05;  // 5% cashback
            serviceFeeRate = 0.0; // No service fee
            isHighRisk = false;
            break;
        case 2: // Shopping & Retail
            paymentType = "Shopping & Retail";
            cashbackRate = 0.03;  // 3% cashback
            serviceFeeRate = 0.0; // No service fee
            isHighRisk = false;
            break;
        case 3: // Bills & Utilities
            paymentType = "Bills & Utilities";
            cashbackRate = 0.01;  // 1% cashback
            serviceFeeRate = 0.01; // 1% service fee
            isHighRisk = false;
            break;
        case 4: // Peer-to-Peer Transfer
            paymentType = "Peer-to-Peer Transfer";
            cashbackRate = 0.0;   // No cashback
            serviceFeeRate = 0.0; // No service fee
            isHighRisk = false;
            break;
        case 5: // Donation
            paymentType = "Donation";
            cashbackRate = 0.0;   // No cashback
            serviceFeeRate = 0.0; // No service fee
            isHighRisk = false;
            break;
        default:
            paymentType = "Invalid";
            break;
    }
}

// Function to check if transaction is high-risk
bool checkHighRiskTransaction(double amount, double balance, const string& paymentType) {
    // High-risk if amount > 50% of balance
    if (amount > (balance * 0.5)) {
        return true;
    }
    // High-risk if amount > RM 5000
    if (amount > 5000) {
        return true;
    }
    return false;
}

// Function to display high-risk warning
void displayHighRiskWarning(double amount, double balance) {
    cout << "\n" << string(60, '!') << endl;
    cout << "⚠️  HIGH-RISK TRANSACTION WARNING ⚠️" << endl;
    cout << string(60, '!') << endl;
    cout << "This transaction amount (" << fixed << setprecision(2) << "RM " << amount << ") is:" << endl;
    if (amount > (balance * 0.5)) {
        cout << "• More than 50% of your current balance (RM " << balance << ")" << endl;
    }
    if (amount > 5000) {
        cout << "• Exceeding RM 5,000 threshold" << endl;
    }
    cout << "\nPlease verify this transaction carefully." << endl;
    cout << string(60, '!') << endl;
}

// Function to process payment
bool processPayment(double& balance, const string& paymentType, double amount, 
                   double& cashback, double& serviceFee, double& finalAmount, Transaction& txn) {
    
    // Check balance sufficiency
    if (amount > balance) {
        cout << "\n❌ PAYMENT FAILED!" << endl;
        cout << "Insufficient balance." << endl;
        cout << "Required: RM " << fixed << setprecision(2) << amount << endl;
        cout << "Available: RM " << balance << endl;
        return false;
    }
    
    // Get payment type details
    double cashbackRate = 0.0;
    double serviceFeeRate = 0.0;
    bool isHighRisk = false;
    
    if (paymentType == "Food & Beverages") {
        cashbackRate = 0.05;
        serviceFeeRate = 0.0;
    } else if (paymentType == "Shopping & Retail") {
        cashbackRate = 0.03;
        serviceFeeRate = 0.0;
    } else if (paymentType == "Bills & Utilities") {
        cashbackRate = 0.01;
        serviceFeeRate = 0.01;
    } else if (paymentType == "Peer-to-Peer Transfer") {
        cashbackRate = 0.0;
        serviceFeeRate = 0.0;
    } else if (paymentType == "Donation") {
        cashbackRate = 0.0;
        serviceFeeRate = 0.0;
    }
    
    // Calculate cashback and service fee
    cashback = amount * cashbackRate;
    serviceFee = amount * serviceFeeRate;
    finalAmount = amount + serviceFee - cashback;
    
    // Check if final amount exceeds balance
    if (finalAmount > balance) {
        cout << "\n❌ PAYMENT FAILED!" << endl;
        cout << "Insufficient balance after calculating service fees." << endl;
        cout << "Final Amount Required: RM " << fixed << setprecision(2) << finalAmount << endl;
        cout << "Available: RM " << balance << endl;
        return false;
    }
    
    // Store transaction details
    txn.transactionID = generateTransactionID();
    txn.paymentType = paymentType;
    txn.amount = amount;
    txn.cashback = cashback;
    txn.serviceFee = serviceFee;
    txn.finalAmount = finalAmount;
    txn.balanceBefore = balance;
    txn.balanceAfter = balance - finalAmount;
    txn.timestamp = getCurrentTimestamp();
    txn.status = "SUCCESS";
    
    // Update balance
    balance = balance - finalAmount;
    
    return true;
}

// Function to display transaction receipt
void displayTransactionReceipt(const Transaction& txn) {
    cout << "\n" << string(60, '=') << endl;
    cout << "              TRANSACTION RECEIPT" << endl;
    cout << string(60, '=') << endl;
    cout << "Transaction ID: " << txn.transactionID << endl;
    cout << "Timestamp: " << txn.timestamp << endl;
    cout << "Payment Type: " << txn.paymentType << endl;
    cout << string(60, '-') << endl;
    cout << "Original Amount:    RM " << fixed << setprecision(2) << txn.amount << endl;
    
    if (txn.serviceFee > 0) {
        cout << "Service Fee (+):     RM " << txn.serviceFee << endl;
    }
    
    if (txn.cashback > 0) {
        cout << "Cashback (-):        RM " << txn.cashback << endl;
    }
    
    cout << string(60, '-') << endl;
    cout << "Final Amount:       RM " << txn.finalAmount << endl;
    cout << string(60, '-') << endl;
    cout << "Balance Before:     RM " << txn.balanceBefore << endl;
    cout << "Balance After:      RM " << txn.balanceAfter << endl;
    cout << string(60, '=') << endl;
    cout << "✓ " << txn.status << " - Payment Completed Successfully" << endl;
    cout << string(60, '=') << endl;
}

// Function to get valid input
double getValidAmount() {
    double amount;
    while (true) {
        cin >> amount;
        if (cin.fail() || amount <= 0) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Please enter a positive number: ";
        } else {
            cin.ignore(10000, '\n');
            return amount;
        }
    }
}

double getValidBalance() {
    double balance;
    while (true) {
        cin >> balance;
        if (cin.fail() || balance < 0) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Please enter a valid balance: ";
        } else {
            cin.ignore(10000, '\n');
            return balance;
        }
    }
}

int main() {
    double balance = 0.0;
    int mainChoice = 0;
    bool firstRun = true;
    
    displayMainMenu();
    
    // Initial balance setup
    while (true) {
        cout << "\nEnter your initial wallet balance (RM): ";
        balance = getValidBalance();
        
        if (balance >= 0) {
            cout << "✓ Wallet initialized with balance: RM " << fixed << setprecision(2) << balance << endl;
            break;
        }
    }
    
    // Main transaction loop
    while (true) {
        displayPaymentTypeMenu();
        
        int choice;
        cin >> choice;
        cin.ignore(10000, '\n');
        
        if (choice == 6) {
            cout << "\n" << string(60, '=') << endl;
            cout << "Thank you for using DuitNow QR Payment System!" << endl;
            cout << "Final Balance: RM " << fixed << setprecision(2) << balance << endl;
            cout << string(60, '=') << endl;
            break;
        }
        
        if (choice < 1 || choice > 5) {
            cout << "Invalid choice! Please select 1-6." << endl;
            continue;
        }
        
        // Get payment type details
        string paymentType;
        double cashbackRate = 0.0;
        double serviceFeeRate = 0.0;
        bool isHighRisk = false;
        
        getPaymentTypeDetails(choice, paymentType, cashbackRate, serviceFeeRate, isHighRisk);
        
        if (paymentType == "Invalid") {
            cout << "Invalid payment type! Please try again." << endl;
            continue;
        }
        
        // Display selected payment type
        cout << "\n--- PAYMENT DETAILS ---" << endl;
        cout << "Selected Payment Type: " << paymentType << endl;
        cout << "Current Balance: RM " << fixed << setprecision(2) << balance << endl;
        
        // Get payment amount
        cout << "Enter payment amount (RM): ";
        double amount = getValidAmount();
        
        // Check for high-risk transaction
        if (checkHighRiskTransaction(amount, balance, paymentType)) {
            displayHighRiskWarning(amount, balance);
            
            cout << "\nDo you want to proceed? (y/n): ";
            char confirm;
            cin >> confirm;
            cin.ignore(10000, '\n');
            
            if (confirm != 'y' && confirm != 'Y') {
                cout << "\n⚠️ Transaction cancelled by user." << endl;
                continue;
            }
        }
        
        // Process payment
        double cashback = 0.0;
        double serviceFee = 0.0;
        double finalAmount = 0.0;
        Transaction txn;
        
        if (processPayment(balance, paymentType, amount, cashback, serviceFee, finalAmount, txn)) {
            displayTransactionReceipt(txn);
        }
        
        // Ask if user wants to make another transaction
        cout << "\nWould you like to make another transaction? (y/n): ";
        char continueChoice;
        cin >> continueChoice;
        cin.ignore(10000, '\n');
        
        if (continueChoice != 'y' && continueChoice != 'Y') {
            cout << "\n" << string(60, '=') << endl;
            cout << "Thank you for using DuitNow QR Payment System!" << endl;
            cout << "Final Balance: RM " << fixed << setprecision(2) << balance << endl;
            cout << string(60, '=') << endl;
            break;
        }
    }
    
    return 0;
}
