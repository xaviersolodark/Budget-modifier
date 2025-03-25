/*
    Class definitions for the BudgetTracker class
*/

#include <iostream>
#include <iomanip>
#include "BudgetTracker.h"

using std::string;
using std::cout;
using std::endl;
using std::fixed;
using std::setprecision;
using std::to_string;

void BudgetTracker::setBudget(const string& category, double amount){

    budgets[category] = amount;
    transactions[category] = vector<Transaction>();
    cout << "Budget for " << category << " set to $" << fixed << setprecision(2) << amount << endl;

}

void BudgetTracker::addFunds(const string& category, double amount){

    if (budgets.find(category) == budgets.end()) {
        cout << "No budget set for " << category << ". Please set a budget first." << endl;
        return;
    }
    budgets[category] += amount;
    cout << "$" << fixed << setprecision(2) << amount << " added to " << category
        << ". New total: $" << budgets[category] << endl;

}

void BudgetTracker::addExpense(const string& category, double amount, const string& description){

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

void BudgetTracker::viewBudget(const string& category) {
    if (budgets.find(category) == budgets.end()){
        cout << "No budget set for " << category << endl;
        return;
    }

    double initial = budgets[category];
    double spent = 0.0;
    vector<Transaction> transList = transactions[category];
    for (size_t i = 0; i < transList.size(); i++){
        spent += transList[i].amount;
    }
    double remaining = initial - spent;

    cout << "\nBudget Report for " << category << ":" << endl;
    cout << "Current Budget: $" << fixed << setprecision(2) << initial << endl;
    cout << "Total Spent: $" << spent << endl;
    cout << "Remaining: $" << remaining << endl;

    if (!transList.empty()){
        cout << "\nTransactions:" << endl;
        for (size_t i = 0; i < transList.size(); i++){
            string desc = transList[i].description.empty()
                              ? "Transaction " + to_string(i + 1)
                              : transList[i].description;
            cout << i + 1 << ". $" << fixed << setprecision(2)
                 << transList[i].amount << " - " << desc << endl;
        }
    }
}

void BudgetTracker::viewAllBudgets(){

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
