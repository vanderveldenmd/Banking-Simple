#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

const int MAX_ACCOUNTS = 5;
const int PASSWORD_WIDTH = 10;
const int BALANCE_FIELD = 11;
const int ID_BANK1 = 1132;
const int ID_BANK2 = 3763;
const int ID_BANK3 = 6741;
const int ZERO = 0;
const int NOT_FOUND = -1;
const int ONE = 1;

const double BASIC_INTEREST = .001;
const double NOW_INTEREST = .0015;
const double MONEYMARKET_INTEREST = .002;
const double PREMIER_INTEREST = .0035;

const char NOW_ACCOUNT = 'N';
const char MONEYMARKET_ACCOUNT = 'M';

enum AccountType { BASIC, NOW, MONEYMARKET, PREMIER };
enum Action { ADD = 'A', DEPOSIT = 'D', WITHDRAWAL = 'W', REMOVE = 'R', 
              PRINT = 'P', INTEREST = 'I' };

class Bank
{
private:
   string accounts[MAX_ACCOUNTS];
   string passwords[MAX_ACCOUNTS];
   double balances[MAX_ACCOUNTS];
   AccountType types[MAX_ACCOUNTS];
   int numAccounts;

public:
   Bank()
   {
      numAccounts = 0;
      return;
   }

   //---------------------------------------------------------------------
   // Find takes an account number and returns the location of that
   // account within the arrays. Or it returns a constant if the account
   // is not found.
   // 
   // params( in )      
   //---------------------------------------------------------------------
   int Find( const string account )
   {
      for (int n = ZERO; n < numAccounts; n++)
      {
         if (account == accounts[n])
            return n;
      }
      return NOT_FOUND;
   }

   //---------------------------------------------------------------------
   // This method will determine what kind of interest the user has 
   // entered for their account. It checks the input versus a const enum 
   // and will set to the appropriate account type. Will set to basic as
   // a default.
   // params( in, in )      
   //---------------------------------------------------------------------
   void SetAccountType(const int index, const char type)
   {
      if (type == NOW_ACCOUNT)
         types[index] = NOW;
      else if (type == MONEYMARKET_ACCOUNT)
         types[index] = MONEYMARKET;
      else if (type == PRINT)
         types[index] = PREMIER;
      else
         types[index] = BASIC;
      return;
   }

   //---------------------------------------------------------------------
   // This method checks a password input against the password in the 
   // class array. It returns true if the two match and false if the two
   // strings do not match.
   // 
   // params( in, in )      
   //---------------------------------------------------------------------
   bool PasswordCheck(const string password, const int index )
   {
      if (password == passwords[index])
      {
         return true;
      }
      else
      {
         return false;
      }
   }

   //---------------------------------------------------------------------
   // Add adds a new account to the bank. It will not add if the bank is 
   // full or if the account exists. Add will also take a password and 
   // account type.
   // 
   // params( )      
   //---------------------------------------------------------------------
   void Add()
   {
      string account_number, Password;
      char account_type;
      cin >> account_number >> Password >> account_type;
      if (Find(account_number) != NOT_FOUND)
      {
         cout << "Account already exists for " << account_number << endl;
         return;
      }
      else if (numAccounts >= MAX_ACCOUNTS)
      {
         cout << "Can't handle any more accounts" << endl;
         return;
      }
      else
      {
         cout << "Account added for " << account_number << endl;
         accounts[numAccounts] = account_number;
         passwords[numAccounts] = Password;
         balances[numAccounts] = double(ZERO);
         SetAccountType(numAccounts, account_type);
      }
      numAccounts++;
      return;
   }

   //---------------------------------------------------------------------
   // Deposit will check to see if an account exists, if it does exist, it
   // will add the deposit amount to the total balance.
   //     
   // 
   // params( )      
   //---------------------------------------------------------------------
   void Deposit()
   {
      string account_number, Password;
      double amount;
      cin >> account_number >> Password >> amount;
      int index = Find(account_number);
      if (index == NOT_FOUND)
      {
         cout << "No deposit - No account for " << account_number << endl;
         return;
      }
      if (!PasswordCheck(Password, index))
      {
         cout << "No deposit - Incorrect password for " << account_number 
              << endl;
         return;
      }
      balances[index] += amount;
      cout << "Deposit of $" << amount << " for " << account_number 
           << endl;
      return;
   }

   //---------------------------------------------------------------------
   // This method checks if a user has enough money in their account and
   // will withdraw as much as necessary or possible. This also checks
   // that the account exists.
   // 
   // params( )      
   //---------------------------------------------------------------------
   void Withdrawal()
   {
      string account_number, Password;
      double amount;
      cin >> account_number >> Password >> amount;
      int index = Find(account_number);
      if (index == NOT_FOUND)
      {
         cout << "No withdrawal - No account for " << account_number 
              << endl;
         return;
      }
      if (!PasswordCheck(Password, index))
      {
         cout << "No withdrawal - Incorrect password for " 
              << account_number << endl;
         return;
      }
      if (amount > balances[index])
      {
         cout << "Not enough in account " << account_number 
              << " - Entire balance given out: " << balances[index]
              << endl;
         balances[index] = double(ZERO);
         return;
      }
      balances[index] -= amount;
      cout << "Withdrawal of $" << amount << " for " << account_number 
           << endl;
      return;
   }

   //---------------------------------------------------------------------
   // Remove checks to see if an account exists, than it removes the
   // account from all of the arrays.
   //     
   // 
   // params( )      
   //---------------------------------------------------------------------
   void Remove()
   {
      string account_number;
      cin >> account_number;
      int index = Find(account_number);
      if (index == NOT_FOUND)
      {
         cout << "Can't remove account " << account_number 
              << " - Account doesn't exist" << endl;
         return;
      }
      cout << "Account removed for " << account_number 
           << " - Entire balance given out: $" << balances[index] << endl;
      Resort(index);
      numAccounts--;
   }

   //---------------------------------------------------------------------
   // This method reorders the accounts by moving all of the account
   // information down in the array. This is done along the remove method
   // to delete an account from the bank.
   // 
   // params( in )      
   //---------------------------------------------------------------------
   void Resort(const int index)
   {
      for (int n = index; n < numAccounts - ONE; n++)
      {
         accounts[n] = accounts[n + ONE];
         balances[n] = balances[n + ONE];
         passwords[n] = passwords[n + ONE];
         types[n] = types[n + ONE];
      }
      return;
   }

   //---------------------------------------------------------------------
   // Print lists all the account numbers and their corresponding 
   // balances within that bank.
   //     
   // 
   // params( )      
   //---------------------------------------------------------------------
   void Print()
   {
      cout << "List of Accounts" << endl;
      for (int n = ZERO; n < numAccounts; n++)
      {
         cout << setw(PASSWORD_WIDTH) << accounts[n] 
              << setw(BALANCE_FIELD) << balances[n] << endl;
      }
      return;
   }

   //---------------------------------------------------------------------
   // This method adds interest to all of the account balances.
   //   
   //     
   // 
   // params( )      
   //---------------------------------------------------------------------
   void Interest()
   {
      for (int n = ZERO; n < numAccounts; n++)
      {
         if (types[n] == BASIC)
            balances[n] += balances[n] * BASIC_INTEREST;
         else if (types[n] == PREMIER)
            balances[n] += balances[n] * PREMIER_INTEREST;
         if (types[n] == MONEYMARKET)
            balances[n] += balances[n] * MONEYMARKET_INTEREST;
         if (types[n] == NOW)
            balances[n] += balances[n] * NOW_INTEREST;
      }

      cout << "Interest added to the accounts" << endl;
      return;
   }
};

void ProcessCommandForBank(Bank & tempBank);



int main()
{
   cout << fixed << showpoint << setprecision(2);
   Bank Bank1, Bank2, Bank3;
   int bank_number;
   cin >> bank_number;
   while (cin)
   {
      cout << bank_number << ": ";
      if (bank_number == ID_BANK1)
         ProcessCommandForBank(Bank1);
      else if (bank_number == ID_BANK2)
         ProcessCommandForBank(Bank2);
      else
         ProcessCommandForBank(Bank3);
      cin >> bank_number;
   }
   cout << "Normal Termination of Bank Program.";
   return 0;
}

//------------------------------------------------------------------------
// This function takes in input and performs the appropriate task.
//   
// params( inout )      
//------------------------------------------------------------------------
void ProcessCommandForBank(Bank & tempBank)
{
   char command;
   cin >> command;
   switch (command)
   {
      case ADD:
         tempBank.Add();
         break;
      case DEPOSIT:
         tempBank.Deposit();
         break;
      case WITHDRAWAL:
         tempBank.Withdrawal();
         break;
      case REMOVE:
         tempBank.Remove();
         break;
      case PRINT:
         tempBank.Print();
         break;
      default:
         tempBank.Interest();
         break;
   }
   return;
}