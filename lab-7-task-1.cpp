#include <iostream>
#include <string>

using namespace std;

class Account {
protected:
    int accountNumber;
    double balance;
    string accountHolderName;
    string accountType;
    string transactionHistory[100];
    int historyCount;

public:
    Account(int accNum, double bal, const string& holderName, const string& type = "Generic")
        : accountNumber(accNum), balance(bal), accountHolderName(holderName), accountType(type), historyCount(0) {}

    virtual ~Account() {}

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            if (historyCount < 100) {
                transactionHistory[historyCount++] = "Deposit: +" + to_string(amount);
            }
            cout << "Deposit of $" << amount << " successful." << endl;
        } else {
            cout << "Invalid deposit amount." << endl;
        }
    }

    virtual void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            if (historyCount < 100) {
                transactionHistory[historyCount++] = "Withdrawal: -" + to_string(amount);
            }
            cout << "Withdrawal of $" << amount << " successful." << endl;
        } else {
            cout << "Insufficient funds or invalid amount." << endl;
        }
    }

    virtual double calculateInterest() const {
        return 0.0; 
    }

    void printStatement() const {
        cout << "Account Statement for Account #" << accountNumber << endl;
        cout << "Holder: " << accountHolderName << endl;
        cout << "Type: " << accountType << endl;
        cout << "Balance: $" << balance << endl;
        cout << "Transaction History:" << endl;
        for (int i = 0; i < historyCount; ++i) {
            cout << "  " << transactionHistory[i] << endl;
        }
    }

    void getAccountInfo() const {
        cout << "Account Info:" << endl;
        cout << "  Account Number: " << accountNumber << endl;
        cout << "  Holder: " << accountHolderName << endl;
        cout << "  Type: " << accountType << endl;
        cout << "  Balance: $" << balance << endl;
    }

    double getBalance() const {
        return balance;
    }
};

class SavingsAccount : public Account {
private:
    double interestRate;
    double minimumBalance;

public:
    SavingsAccount(int accNum, double bal, const string& holderName, double rate, double minBal)
        : Account(accNum, bal, holderName, "Savings"), interestRate(rate), minimumBalance(minBal) {}

    double calculateInterest() const override {
        return balance * (interestRate / 100.0);
    }

    void withdraw(double amount) override {
        if (amount > 0 && (balance - amount) >= minimumBalance) {
            Account::withdraw(amount);
        } else {
            cout << "Withdrawal failed: Minimum balance requirement." << endl;
        }
    }
};

class CheckingAccount : public Account {
private:
    double overdraftLimit;

public:
    CheckingAccount(int accNum, double bal, const string& holderName, double limit)
        : Account(accNum, bal, holderName, "Checking"), overdraftLimit(limit) {}

    void withdraw(double amount) override {
        if (amount > 0 && (balance - amount) >= -overdraftLimit) {
            Account::withdraw(amount); 
        } else {
            cout << "Withdrawal failed: Overdraft limit exceeded." << endl;
        }
    }
};

class FixedDepositAccount : public Account {
private:
    string maturityDate;
    double fixedInterestRate;

public:
    FixedDepositAccount(int accNum, double bal, const string& holderName, const string& maturity, double rate)
        : Account(accNum, bal, holderName, "Fixed Deposit"), maturityDate(maturity), fixedInterestRate(rate) {}

    double calculateInterest() const override {
        return balance * (fixedInterestRate / 100.0);
    }

    void withdraw(double amount) override {
        cout << "Withdrawal not allowed for Fixed Deposit Account." << endl;
    }
};

int main() {
    SavingsAccount savings(1001, 5000.0, "Alice Smith", 2.5, 1000.0);
    CheckingAccount checking(2001, 10000.0, "Bob Johnson", 2000.0);
    FixedDepositAccount fixed(3001, 20000.0, "Charlie Brown", "2024-12-31", 5.0);

    savings.deposit(2000.0);
    savings.withdraw(3000.0);
    savings.withdraw(4500.0); 

    checking.withdraw(11000.0);
    checking.withdraw(2000.0);

    fixed.deposit(5000.0);
    fixed.withdraw(1000.0);

    cout << "Savings Interest: $" << savings.calculateInterest() << endl;
    cout << "Fixed Deposit Interest: $" << fixed.calculateInterest() << endl;

    savings.printStatement();
    checking.printStatement();
    fixed.printStatement();

    return 0;
}