/**
 *  File: main.cpp
 *  Developer: Ruth Tonning
 *  Email: tonningr@studetn.vvc.edu
 *  Description: This program models a bank transaction statement. The user inputs the day, amount(deposited or
                 withdrawn), and description and the program prints the statement. It also provides the interest accrued
                 over 30 days(1 month) using the 'minimum' and 'average daily balance' methods.
 *  Date: 11/13/17
**/

#include <iostream>
#include <string>
#include <vector>

class Transaction
{
public:
   Transaction(); // Constructor for an object of class Transaction.
   void read(); // Reads in this transaction object.
   double set_amount() const {return m_amount;}; // An accessor function for the data field m_amount.
   void print() const; // Prints this transaction object.

private:
   int m_day;
   double m_amount;
   std::string m_description;
};

Transaction::Transaction()
{
   m_day = 0;
   m_amount = 0.0;
}

void Transaction::read()
{
   std::cin >> m_day;
   std::cin >> m_amount;
   std::cin.ignore();
   std::getline(std::cin, m_description);
}

void Transaction::print() const
{
   std::cout << "Day: " << m_day << std::endl;
   std::cout << "Amount: " << m_amount << std::endl;
   std::cout << "Description: " << m_description << std::endl;
}

class Bank_statement
{
public:
   Bank_statement(); // Constructor for an object of class Bank_statement.
   void get_transactions(); // Mutator function that reads in values and store them in a vector.
   double get_interest_min(); // Mutator function that computes the lowest value; determines 'minimum interest value'.
   double get_interest_avrg(); // Mutator function computes average value; determines 'average interest value'.
   void print_transactions() const; // Prints this bank_statement object.

private: 
   double m_min_day_bal;
   double m_avrg_day_bal;
   const double INT_RATE = 0.5;
   const int DAYS = 30;
   std::vector<Transaction> m_transactions;
};

Bank_statement::Bank_statement()
{
   m_min_day_bal = 0.0;
   m_avrg_day_bal = 0.0;
}

void Bank_statement::get_transactions()
{
   std::cout << "Please enter the day, amount, and description, separating each with a space." << std::endl;
   bool more = true;
   while(more)
   {
      Transaction t;
      t.read();
      m_transactions.push_back(t);
      std::cout << "Enter another (Y/N)";
      char response;
      std::cin >> response;
      if (response != 'y' && response != 'Y')
         more = false;
   }
}

double Bank_statement::get_interest_min()
{
   double m_min_day_bal = m_transactions[0].set_amount();
   for (int i = 1; i < m_transactions.size(); i++)
   {
      if (m_transactions[i].set_amount() < m_min_day_bal && m_transactions[i].set_amount() >= 0)
         m_min_day_bal = m_transactions[i].set_amount();
   }

   return (m_min_day_bal * DAYS * INT_RATE);
}

double Bank_statement::get_interest_avrg()
{
   double sum_of_elements = 0.0;
   for (int i = 0; i < m_transactions.size(); i++)
      sum_of_elements = sum_of_elements + m_transactions[i].set_amount();

   m_avrg_day_bal = sum_of_elements / m_transactions.size();

   return (m_avrg_day_bal * DAYS * INT_RATE);
}

void Bank_statement::print_transactions() const
{
   for (int i = 0; i < m_transactions.size(); i++)
      m_transactions[i].print();
}

int main()
{
   Bank_statement bank_statement;
   bank_statement.get_transactions();
   bank_statement.print_transactions();
   std::cout << std::endl;
   
   std::cout << "Interest accrued by the 'average daily balance' over 30 days with an interest rate of 0.5: " <<
   bank_statement.get_interest_avrg() << std::endl;
   
   std::cout << std::endl;

   std::cout << "Interest accrued by the 'minimum daily balance' over 30 days with an interest rate of 0.5: " <<
   bank_statement.get_interest_min() << std::endl;

   return 0;
}
