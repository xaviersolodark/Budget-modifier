#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>

using namespace std;

struct Transaction {
    double amount;
    string description;
};

class BudgetTracker {
private:
    map<string, double> budgets;
    map<string, vector<Transaction> > transactions;

public:
    BudgetTracker() {}

    void setBudget(const string& category, double amount) {
        budgets[category] = amount;
        transactions[category] = vector<Transaction>();
        cout << "Budget for " << category << " set to $" << fixed << setprecision(2) << amount << endl;
    }

    void addFunds(const string& category, double amount) {
        if (budgets.find(category) == budgets.end()) {
            cout << "No budget set for " << category << ". Please set a budget first." << endl;
            return;
        }
        budgets[category] += amount;
        cout << "$" << fixed << setprecision(2) << amount << " added to " << category
            << ". New total: $" << budgets[category] << endl;
    }

    void addExpense(const string& category, double amount, const string& description = "") {
        if (budgets.find(category) == budgets.end()) {
            cout << "No budget set for " << category << ". Please set a budget first." << endl;
            return;
        }

        double spent = 0.0;
        vector<Transaction> transList = transactions[category];
        for (size_t i = 0; i < transList.size(); i++) {
            spent += transList[i].amount;
        }
        double remaining = budgets[category] - spent;

        if (amount > remaining) {
            cout << "Warning: This expense ($" << fixed << setprecision(2) << amount
                << ") exceeds remaining budget ($" << remaining << ") for " << category << endl;
        }
        else {
            cout << "Expense of $" << fixed << setprecision(2) << amount
                << " added to " << category << endl;
        }

        Transaction newTrans;
        newTrans.amount = amount;
        newTrans.description = description;
        transactions[category].push_back(newTrans);
    }

    void viewBudget(const string& category) {
        if (budgets.find(category) == budgets.end()) {
            cout << "No budget set for " << category << endl;
            return;
        }

        double initial = budgets[category];
        double spent = 0.0;
        vector<Transaction> transList = transactions[category];
        for (size_t i = 0; i < transList.size(); i++) {
            spent += transList[i].amount;
        }
        double remaining = initial - spent;

        cout << "\nBudget Report for " << category << ":" << endl;
        cout << "Current Budget: $" << fixed << setprecision(2) << initial << endl;
        cout << "Total Spent: $" << spent << endl;
        cout << "Remaining: $" << remaining << endl;

        if (!transList.empty()) {
            cout << "\nTransactions:" << endl;
            for (size_t i = 0; i < transList.size(); i++) {
                string desc = transList[i].description.empty()
                    ? "Transaction " + to_string(i + 1)
                    : transList[i].description;
                cout << i + 1 << ". $" << fixed << setprecision(2)
                    << transList[i].amount << " - " << desc << endl;
            }
        }
    }

    void viewAllBudgets() {
        if (budgets.empty()) {
            cout << "No budgets set yet" << endl;
            return;
        }

        cout << "\nAll Budgets Summary:" << endl;
        map<string, double>::iterator it;
        for (it = budgets.begin(); it != budgets.end(); ++it) {
            string category = it->first;
            double initial = it->second;
            double spent = 0.0;
            vector<Transaction> transList = transactions[category];
            for (size_t i = 0; i < transList.size(); i++) {
                spent += transList[i].amount;
            }
            double remaining = initial - spent;
            cout << category << ": Current: $" << fixed << setprecision(2) << initial
                << " | Spent: $" << spent << " | Remaining: $" << remaining << endl;
        }
    }
};

int main() {
    BudgetTracker tracker;

    // Your specific budget categories with initial amounts
    vector<pair<string, double> > categories;
    categories.push_back(pair<string, double>("Social Budget", 4002.97));
    categories.push_back(pair<string, double>("Brotherhood", 3334.66));
    categories.push_back(pair<string, double>("House Budget", 2872.26));
    categories.push_back(pair<string, double>("Recruitment", 2601.12));
    categories.push_back(pair<string, double>("New Member Education", 1174.84));
    categories.push_back(pair<string, double>("Savings", 234.37));
    categories.push_back(pair<string, double>("IFC Expenses", 3000.00));
    categories.push_back(pair<string, double>("Historian", 423.50));
    categories.push_back(pair<string, double>("Philanthropy", 100.00));
    categories.push_back(pair<string, double>("Scholarship", 100.00));
    categories.push_back(pair<string, double>("Parent & Alumni", 100.00));

    // Initialize budgets
    for (size_t i = 0; i < categories.size(); i++) {
        tracker.setBudget(categories[i].first, categories[i].second);
    }

    while (true) {
        cout << "\nBudget Tracker Menu:" << endl;
        cout << "1. Add Expense" << endl;
        cout << "2. Add Funds to Budget" << endl;
        cout << "3. View Specific Budget" << endl;
        cout << "4. View All Budgets" << endl;
        cout << "5. Exit" << endl;

        int choice;
        cout << "Enter your choice (1-5): ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            cout << "\nAvailable categories:" << endl;
            for (size_t i = 0; i < categories.size(); i++) {
                cout << i + 1 << ". " << categories[i].first << endl;
            }
            int catNum;
            cout << "Select category number: ";
            cin >> catNum;
            cin.ignore();

            if (catNum >= 1 && catNum <= static_cast<int>(categories.size())) {
                string category = categories[catNum - 1].first;
                double amount;
                cout << "Enter expense amount: $";
                cin >> amount;
                cin.ignore();

                string desc;
                cout << "Enter description (optional, press Enter to skip): ";
                getline(cin, desc);

                tracker.addExpense(category, amount, desc);
            }
            else {
                cout << "Invalid category number" << endl;
            }
        }
        else if (choice == 2) {
            cout << "\nAvailable categories:" << endl;
            for (size_t i = 0; i < categories.size(); i++) {
                cout << i + 1 << ". " << categories[i].first << endl;
            }
            int catNum;
            cout << "Select category number: ";
            cin >> catNum;
            cin.ignore();

            if (catNum >= 1 && catNum <= static_cast<int>(categories.size())) {
                string category = categories[catNum - 1].first;
                double amount;
                cout << "Enter amount to add: $";
                cin >> amount;
                cin.ignore();

                tracker.addFunds(category, amount);
            }
            else {
                cout << "Invalid category number" << endl;
            }
        }
        else if (choice == 3) {
            cout << "\nAvailable categories:" << endl;
            for (size_t i = 0; i < categories.size(); i++) {
                cout << i + 1 << ". " << categories[i].first << endl;
            }
            int catNum;
            cout << "Select category number: ";
            cin >> catNum;
            cin.ignore();

            if (catNum >= 1 && catNum <= static_cast<int>(categories.size())) {
                tracker.viewBudget(categories[catNum - 1].first);
            }
            else {
                cout << "Invalid category number" << endl;
            }
        }
        else if (choice == 4) {
            tracker.viewAllBudgets();
        }
        else if (choice == 5) {
            cout << "Goodbye!" << endl;
            break;
        }
        else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
