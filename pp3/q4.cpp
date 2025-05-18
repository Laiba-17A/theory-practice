//part a
#include <iostream>
#include <string>
#include <vector>

class Stock {
protected:
    std::string symbol;
    std::string companyName;
    double price;
    int availableQuantity;
    int maxQuantityPerInvestor;
    int stockCategoryQuantity;

public:
    Stock(std::string sym, std::string comp, double pr, int availQty, int maxQty, int catQty)
        : symbol(sym), companyName(comp), price(pr), availableQuantity(availQty),
          maxQuantityPerInvestor(maxQty), stockCategoryQuantity(catQty) {}

    virtual ~Stock() {}

    std::string getSymbol() const { return symbol; }
    std::string getCompanyName() const { return companyName; }
    double getPrice() const { return price; }
    int getAvailableQuantity() const { return availableQuantity; }
    int getMaxQuantityPerInvestor() const { return maxQuantityPerInvestor; }

    virtual bool isEligibleToBuy(int purchaseQuantity) const {
        if (purchaseQuantity <= 0) {
            std::cout << "Error: Invalid purchase quantity." << std::endl;
            return false;
        }
        if (purchaseQuantity > maxQuantityPerInvestor) {
            std::cout << "Error: Purchase quantity exceeds max limit per investor." << std::endl;
            return false;
        }
        if (purchaseQuantity > availableQuantity) {
            std::cout << "Error: Not enough stock available." << std::endl;
            return false;
        }
        return true;
    }

    virtual void displayInfo() const {
        std::cout << "Symbol: " << symbol << ", Company: " << companyName
                  << ", Price: " << price << ", Available: " << availableQuantity
                  << ", Max/Investor: " << maxQuantityPerInvestor
                  << ", CategoryQty: " << stockCategoryQuantity << std::endl;
    }
//part c
    bool operator!=(const Stock& other) const {
        return (symbol != other.symbol || companyName != other.companyName);
    }
};

class TechStock : public Stock {
public:
    TechStock(std::string sym, std::string comp, double pr, int availQty, int maxQty, int catQty)
        : Stock(sym, comp, pr, availQty, maxQty, catQty) {}

    bool isEligibleToBuy(int purchaseQuantity) const override {
        if (!Stock::isEligibleToBuy(purchaseQuantity)) return false;

        if (purchaseQuantity % 10 != 0) {
            std::cout << "Error: TechStock purchase quantity must be a multiple of 10." << std::endl;
            return false;
        }
        if (purchaseQuantity > 100) {
            std::cout << "Error: TechStock max purchase limit is 100." << std::endl;
            return false;
        }
        return true;
    }
};

class PharmaStock : public Stock {
public:
    PharmaStock(std::string sym, std::string comp, double pr, int availQty, int maxQty, int catQty)
        : Stock(sym, comp, pr, availQty, maxQty, catQty) {}

    bool isEligibleToBuy(int purchaseQuantity) const override {
        if (!Stock::isEligibleToBuy(purchaseQuantity)) return false;

        if (purchaseQuantity < 50) {
            std::cout << "Error: PharmaStock purchase quantity must be at least 50." << std::endl;
            return false;
        }
        if (purchaseQuantity % 5 != 0) {
            std::cout << "Error: PharmaStock purchase quantity must be a multiple of 5." << std::endl;
            return false;
        }
        return true;
    }
};

//part b
class Investor {
protected:
    std::string name;
    std::string CNIC;
    std::string email;
    int availableFunds;
    bool hasLoan;

public:
    Investor(std::string n, std::string c, std::string e, int funds, bool loan)
        : name(n), CNIC(c), email(e), availableFunds(funds), hasLoan(loan) {}

    virtual bool canBuyStock(Stock& stock, int purchaseQuantity) = 0;

    int getAvailableFunds() const { return availableFunds; }
    bool getHasLoan() const { return hasLoan; }
};

class DayTrader : public Investor {
public:
    DayTrader(std::string n, std::string c, std::string e, int funds, bool loan)
        : Investor(n, c, e, funds, loan) {}

    bool canBuyStock(Stock& stock, int purchaseQuantity) override {
        if (hasLoan) {
            std::cout << "Error: DayTrader has a loan and cannot purchase stocks." << std::endl;
            return false;
        }

        double totalPrice = stock.getPrice() * purchaseQuantity;
        if (totalPrice > availableFunds) {
            std::cout << "Error: Insufficient funds for DayTrader to buy the stock." << std::endl;
            return false;
        }

        return stock.isEligibleToBuy(purchaseQuantity);
    }
};

class LongTermInvestor : public Investor {
public:
    LongTermInvestor(std::string n, std::string c, std::string e, int funds, bool loan)
        : Investor(n, c, e, funds, loan) {}

    bool canBuyStock(Stock& stock, int purchaseQuantity) override {
        if (hasLoan && availableFunds < 50000) {
            std::cout << "Error: LongTermInvestor has a loan and insufficient funds (< 50000)." << std::endl;
            return false;
        }

        if (purchaseQuantity > stock.getMaxQuantityPerInvestor()) {
            std::cout << "Error: Purchase quantity exceeds allowed max per investor." << std::endl;
            return false;
        }

        return stock.isEligibleToBuy(purchaseQuantity);
    }
};

