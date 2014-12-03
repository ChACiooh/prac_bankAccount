#include <fstream>
#include "bank_account.h"

/** Account **/
Account::Account(const string& name, unsigned int balance, double interest_rate)
: name_(name), balance_(balance), interest_rate_(interest_rate) {}
Account::~Account() {}

void Account::Deposit(unsigned int amount)
{
	balance_ += amount;
}

bool Account::Withdraw(unsigned int amount)
{
	if(balance_ >= amount)
	{
		balance_ -= amount;
		return true;
	}
	return false;
}

unsigned int Account::ComputeExpectedBalance(unsigned int n_years_later) const
{
	return static_cast<unsigned int>(balance_ * (1 + n_years_later * interest_rate_));
}
// Account end.


/** SavingAccount **/
SavingAccount::SavingAccount(const string& name, int balance, double interest_rate)
: Account(name, balance, interest_rate) {}
SavingAccount::~SavingAccount() {}

unsigned int SavingAccount::ComputeExpectedBalance(unsigned int n_years_later) const
{
	double rate = 1.0;
	for(unsigned int i=0;i<n_years_later;i++)	rate *= (1.0+interest_rate_);
	unsigned int res = static_cast<unsigned int>(balance_ * rate);
	return res;
}
// SavingAccount end.

/** etc functions **/
Account* CreateAccount(const string& type, const string& name, unsigned int balance, double interest_rate)
{
	Account* res = NULL;
	if(type == "checking")
	{
		res = new Account(name, balance, interest_rate);
	}
	else if(type == "saving")
	{
		res = new SavingAccount(name, balance, interest_rate);
	}
	return res;
}

bool SaveAccounts(const vector<Account*>& accounts, const string& filename)
{
	ofstream fp;
	try
	{
		fp.open(filename.c_str(), fstream::out);
		for(size_t i=0;i<accounts.size();i++)
			fp << accounts[i]->name() << " " << accounts[i]->type() << " " << accounts[i]->balance() << " " << accounts[i]->interest_rate() << endl;
	} catch(exception e) {
		if(fp.is_open())	fp.close();
		return false;
	}
	fp.close();
	return true;
}

bool LoadAccounts(const string& filename, vector<Account*>* accounts)
{
	ifstream fp;
	try
	{
		fp.open(filename.c_str(), fstream::in);
		accounts->clear();
		while(fp.good())
		{
			Account* ap;
			string name, type;
			int balance;
			double interest_rate;
			fp >> name >> type >> balance >> interest_rate;
			ap = CreateAccount(type, name, balance, interest_rate);
			if(ap != NULL)	accounts->push_back(ap);
		}
	} catch(exception e) {
		if(fp.is_open())	fp.close();
		return false;
	}
	fp.close();
	return true;
}
