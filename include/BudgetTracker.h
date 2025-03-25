/*
    Header file for the Budget Tracker Class
*/
#include <vector>
#include <string>
#include <map>

using std::map;
using std::vector;
using std::string;

#pragma once

struct Transaction {
    double amount;
    string description;
};

class BudgetTracker{
    private:
        map<string, double> budgets;
        map<string, vector<Transaction>> transactions;

    public:
        
        //constructor
        BudgetTracker(){}

        //sets a specific budget to a amount from user
        void setBudget(const string& category, double amount);

        //adds specific amount to budget
        void addFunds(const string& category, double amount);

        //takes money out of a specific budget
        void addExpense(const string& category, double amount, const string& description = "");


        void viewBudget(const string &category);
        void viewAllBudgets();
        
};
