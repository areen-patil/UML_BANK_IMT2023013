//IMT2023013
//Areen Patil
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Account; 
class Transaction;
class Card;
class Cheque;
class FixedDeposit;
class Loan;

// USER CLASS
class User {
private:
    string username, password, email, phoneNumber;
    vector<Account*> accounts; // Composition (1 User -> N Accounts)
public:
    User(string u, string p, string e, string ph)
        : username(u), password(p), email(e), phoneNumber(ph) {}
    void login() { cout << username << " logged in.\n"; }
    void logout() { cout << username << " logged out.\n"; }
    void changePassword(string newPass) { password = newPass; cout << "Password changed.\n"; }
    void updatePhoneNumber(string ph) { phoneNumber = ph; cout << "Phone updated.\n"; }
    void updateEmail(string em) { email = em; cout << "Email updated.\n"; }
    void addAccount(Account* acc) { accounts.push_back(acc); }
};

// ACCOUNT CLASS
class Account {
private:
    string accountNumber, accountType;
    double balance;
    vector<Transaction*> transactions;   // Association
    vector<Card*> cards;                 // Association
    vector<Cheque*> cheques;             // Association
    vector<FixedDeposit*> fds;           // Aggregation
    vector<Loan*> loans;                 // Aggregation
public:
    Account(string num, string type, double bal)
        : accountNumber(num),accountType(type),balance(bal){}
    void deposit(double amount){balance += amount; cout <<"Deposited "<<amount<<". Balance: "<<balance<<"\n";}
    void withdraw(double amount){if(balance>=amount){balance-=amount; cout<<"Withdrew "<<amount<<". Balance: "<<balance<<"\n";} }
    void transfer(double amount,Account* target){
        if(balance>=amount){ balance-=amount; target->deposit(amount); cout<<"Transferred "<<amount<<"\n"; }
    }

    void addTransaction(Transaction* t) { transactions.push_back(t);}
    void addCard(Card* c){ cards.push_back(c); }
    void addCheque(Cheque* ch){ cheques.push_back(ch);}
    void addFD(FixedDeposit* fd) { fds.push_back(fd); }
    void addLoan(Loan* l){ loans.push_back(l);}
};

// TRANSACTION CLASS
class Transaction {
private:
    string transactionID, date, type;
    double amount;
public:
    Transaction(string id, double amt, string d, string t)
        : transactionID(id), amount(amt), date(d), type(t){}
    void execute(){cout<<"Transaction "<<transactionID<<" executed.\n";}
    void cancel(){cout<<"Transaction "<<transactionID<<" canceled.\n";}
    void getDetails(){cout<<"Transaction: "<<transactionID<<" Amount: "<<amount<<"\n";}
};

// CARD CLASS
class Card {
private:
    string cardNumber, expiryDate, CVV;
public:
    Card(string num, string exp, string cvv) : cardNumber(num), expiryDate(exp), CVV(cvv) {}
    void changePIN(){cout << "Card PIN changed.\n";}
    void checkBalance() { cout << "Balance checked using card.\n"; }
    void makePayment(double amt){cout<<"Payment of "<<amt<<" done using card.\n";}
};

// FIXED-DEPOIST CLASS
class FixedDeposit {
private:
    string depositID, maturityDate;
    double amount, interestRate;
public:
    FixedDeposit(string id, double amt, double rate, string date)
        : depositID(id), amount(amt), interestRate(rate), maturityDate(date) {}
    void create(){ cout << "FD created.\n";}
    void close(){ cout << "FD closed.\n";}
    void calculateInterest() { cout << "Interest on FD: "<<amount * interestRate << "\n"; }
    void getDetails(){ cout<<"FD: "<<depositID<<" Amount: "<<amount<<"\n"; }
};

// LOAN CLASS 
class Loan {
private:
    string loanID;
    double amount, interestRate;
    int duration;
public:
    Loan(string id, double amt, double rate, int dur)
    : loanID(id), amount(amt), interestRate(rate), duration(dur) {}
    void apply() { cout << "Loan applied.\n"; }
    void repay(double amt) { amount -= amt; cout << "Repaid " << amt << ". Remaining: " << amount << "\n"; }
    void calculateInterest() { cout << "Loan interest: " << amount * interestRate << "\n"; }
    void getDetails() { cout << "Loan: " << loanID << " Amount: " << amount << "\n"; }
};

//  CHEQUE CLASS
class Cheque {
private:
    string chequeNumber, payee, dateIssued;
    double amount;
public:
    Cheque(string num, double amt, string p, string date): chequeNumber(num), amount(amt), payee(p), dateIssued(date) {}
    void issue() { cout << "Cheque issued.\n"; }
    void cancel() { cout << "Cheque canceled.\n"; }
    void updateAmount(double newAmt) { amount = newAmt; cout << "Cheque updated: " << amount << "\n"; }
    void getDetails() { cout << "Cheque: " << chequeNumber << " Payee: " << payee << "\n"; }
};

// EMPLOYEE CLASS
class Employee {
protected:
    string employeeID, name, position;
    double salary;
public:
    Employee(string id, string n, string pos, double sal)
        : employeeID(id), name(n), position(pos), salary(sal) {}
    void checkIn() { cout << name << " checked in.\n"; }
    void checkOut() { cout << name << " checked out.\n"; }
    void performTask(string task) { cout << name << " performed: " << task << "\n"; }
};



// MANAGER INHERITANCE 
class Manager : public Employee {
private:
    double bonus;
public:
    Manager(string id, string n, string pos, double sal, double b)
        : Employee(id,n,pos,sal), bonus(b) {}
    void approveLoan() { cout << "Manager approved loan.\n"; }
};


// BRANCH class
class Branch {
private:
    string branchCode, address, manager;
    vector<Employee*> employees; // Association
public:
    Branch(string code, string addr, string m) : branchCode(code), address(addr), manager(m) {}
    void open() { cout << "Branch opened.\n"; }
    void close() { cout << "Branch closed.\n"; }
    void addEmployee(Employee* e) { employees.push_back(e); }
};
// ATM class
class ATM {
private:
    string ATMCode, location;
    double cashAvailable;
public:
    ATM(string code, string loc, double cash) : ATMCode(code), location(loc), cashAvailable(cash) {}
    void dispenseCash(double amt) { if(cashAvailable>=amt){cashAvailable-=amt; cout<<"Dispensed "<<amt<<"\n";} }
    void acceptDeposit(double amt) { cashAvailable+=amt; cout<<"Accepted deposit "<<amt<<"\n"; }
    void updateCashAvailable(double newAmt) { cashAvailable=newAmt; cout<<"ATM cash updated.\n"; }
    void displayBalance() { cout << "ATM Balance: " << cashAvailable << "\n"; }
    void changePIN() { cout << "ATM PIN change requested.\n"; }
};



// BANK CLASS
class Bank {
private:
    string name, address, IFSCCode;
    vector<Branch*> branches; // Aggregation
    vector<ATM*> atms;        // Aggregation
public:
    Bank(string n, string a, string i) : name(n), address(a), IFSCCode(i) {}
    void addBranch(Branch* b) { branches.push_back(b); cout << "Branch added.\n"; }
    void removeBranch() { cout << "Branch removed.\n"; }
    void addATM(ATM* a) { atms.push_back(a); cout << "ATM added.\n"; }
    void removeATM() { cout << "ATM removed.\n"; }
    void getBranchDetails(string code) { cout << "Details for branch: " << code << "\n"; }
};



// Main func 
int main() {
 // Multiple Users and Accounts (1:N)
 // Create Bank
    Bank bank("MyBank", "City Center", "IFSC001");

    // Users and Accounts (1:N)
    User u1("areen", "pass123", "areen@email.com", "9929959999");
    User u2("rohan", "rohanpas", "rohan@mail.com", "8884888688");
    User u3("dumbo", "dumbopa34s", "dumbo@gmail.com", "7777477787");

    Account a1("A001", "Savings", 10340);
    Account a2("A002", "Current", 5046);
    Account a3("A003", "Savings", 2780);
    Account a4("A004", "Current", 3780);

    u1.addAccount(&a1); 
    u1.addAccount(&a2);// areen has two accounts
    u2.addAccount(&a3);// bob has one account
    u3.addAccount(&a4);// alice has one account

    // User methods
    //users are logging in
    u1.login();
    u2.login();
    u3.login();
    //This is showing the updation of user profiles
    u1.changePassword("newpass123");
    u2.updatePhoneNumber("1234567890");
    u3.updateEmail("alice_new@gmail.com");

    // Account methods/operations
    a1.deposit(200);
    a2.withdraw(100);
    a3.deposit(500);
    a4.withdraw(200);
    a1.transfer(100, &a2);

    // Transaction (Association with Account)
    Transaction t1("T001", 200, "2025-09-09", "Deposit");
    Transaction t2("T002", 100, "2025-09-09", "Withdraw");
    Transaction t3("T003", 300, "2025-09-10", "Deposit");
    Transaction t4("T004", 400, "2025-09-11", "Withdraw");
    t1.execute();
    t2.cancel();
    t1.getDetails();
    a1.addTransaction(&t1);
    a2.addTransaction(&t2);
    a1.addTransaction(&t3);
    a1.addTransaction(&t4);

    // Card (Association with Account)
    Card c1("C001", "12/27", "123");
    Card c2("C002", "11/26", "456");
    Card c3("C003", "10/28", "789");
    Card c4("C004", "09/29", "012");
    c1.changePIN();
    c2.checkBalance();
    c1.makePayment(150);
    a1.addCard(&c1);
    a2.addCard(&c2);
    a1.addCard(&c3);
    a1.addCard(&c4);

    // Cheque (Association with Account)
    Cheque ch1("CH001", 500, "bob", "2025-09-09");
    Cheque ch2("CH002", 300, "alice", "2025-09-09");
    Cheque ch3("CH003", 700, "bob", "2025-09-10");
    Cheque ch4("CH004", 800, "alice", "2025-09-11");
    ch1.issue();
    ch2.cancel();
    ch1.updateAmount(600);
    ch2.getDetails();
    a1.addCheque(&ch1);
    a2.addCheque(&ch2);
    a1.addCheque(&ch3);
    a1.addCheque(&ch4);

    // FixedDeposit (Aggregation with Account)
    FixedDeposit fd1("FD001", 1000, 0.05, "2026-09-09");
    FixedDeposit fd2("FD002", 2000, 0.06, "2027-09-09");
    FixedDeposit fd3("FD003", 1500, 0.055, "2026-12-09");
    fd1.create();
    fd1.calculateInterest();
    fd1.getDetails();
    fd1.close();
    a1.addFD(&fd1);
    a1.addFD(&fd2);
    a1.addFD(&fd3);

    // Loan (Aggregation with Account)
    Loan l1("L001", 5000, 0.08, 12);
    Loan l2("L002", 3000, 0.07, 24);
    Loan l3("L003", 4000, 0.09, 36);
    l1.apply();
    l1.repay(1000);
    l1.calculateInterest();
    l1.getDetails();
    a1.addLoan(&l1);
    a1.addLoan(&l2);
    a1.addLoan(&l3);

    // Manager and Employee (Inheritance, 1:N)
    Manager m1("M001", "virat", "Manager", 60000, 5000);
    m1.approveLoan();
    m1.checkIn();
    m1.checkOut();
    m1.performTask("Review Accounts");

    Employee e1("E001", "John", "Clerk", 30000);
    Employee e2("E002", "Sara", "Cashier", 32000);
    e1.checkIn();
    e2.checkOut();
    e1.performTask("Update Passbook");

    // Branch (1:N Employees)
    Branch b1("B001", "Main Street", "Virat");
    b1.addEmployee(&e1);
    b1.addEmployee(&e2);
    b1.addEmployee(&m1);
    b1.open();
    b1.close();

    // Multiple Branches in Bank (1:N)
    Branch b2("B002", "Market Rd", "Mrs. Y");
    bank.addBranch(&b1);
    bank.addBranch(&b2);
    bank.removeBranch();
    bank.getBranchDetails("B001");

    // ATM (1:N in Bank)
    ATM atm1("ATM001", "Mall", 10000);
    ATM atm2("ATM002", "Airport", 20000);
    ATM atm3("ATM003", "Station", 15000);
    atm1.dispenseCash(2000);
    atm2.acceptDeposit(500);
    atm3.updateCashAvailable(18000);
    atm1.displayBalance();
    atm2.changePIN();
    bank.addATM(&atm1);
    bank.addATM(&atm2);
    bank.addATM(&atm3);
    bank.removeATM();

    // Users logging out
    u1.logout();
    u2.logout();
    u3.logout();

    return 0;
}
