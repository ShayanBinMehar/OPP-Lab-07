#include <iostream>
#include <string>

using namespace std;

class Currency {
protected:
    double amount;
    string currencyCode;
    string currencySymbol;
    double exchangeRate; 

public:
    Currency(double amount, const string& code, const string& symbol, double rate = 1.0)
        : amount(amount), currencyCode(code), currencySymbol(symbol), exchangeRate(rate) {}

    virtual ~Currency() {} 

    virtual double convertToBase() const {
        return amount * exchangeRate;
    }

    virtual double convertTo(const Currency& targetCurrency) const {
        double baseAmount = convertToBase();
        return baseAmount / targetCurrency.exchangeRate;
    }

    virtual void displayCurrency() const {
        cout << amount << " " << currencySymbol << " (" << currencyCode << ")" << endl;
    }
};

class Dollar : public Currency {
public:
    Dollar(double amount) : Currency(amount, "USD", "$", 1.0) {}

    void displayCurrency() const override {
        cout << "$ " << amount << " (USD)" << endl;
    }
};

class Euro : public Currency {
public:
    Euro(double amount, double rate) : Currency(amount, "EUR", "€", rate) {}

    void displayCurrency() const override {
        cout << "€ " << amount << " (EUR)" << endl;
    }
};

class Rupee : public Currency {
public:
    Rupee(double amount, double rate) : Currency(amount, "INR", "₹", rate) {}

    void displayCurrency() const override {
        cout << "₹ " << amount << " (INR)" << endl;
    }
};

int main() {
    Dollar usdAmount(100.0);
    Euro eurAmount(80.0, 1.10); 
    Rupee inrAmount(5000.0, 0.012); 

    cout << "USD Amount: ";
    usdAmount.displayCurrency();

    cout << "EUR Amount: ";
    eurAmount.displayCurrency();

    cout << "INR Amount: ";
    inrAmount.displayCurrency();

    double eurToUsd = eurAmount.convertTo(usdAmount);
    cout << "EUR to USD: " << eurToUsd << " USD" << endl;

    double inrToEur = inrAmount.convertTo(eurAmount);
    cout << "INR to EUR: " << inrToEur << " EUR" << endl;

    return 0;
}