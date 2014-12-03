#include <iostream>
#include "bank_account.h"

inline void Addition(vector<Account* >*);
void Show(vector<Account*>&, int year = 0);
void Delete(vector<Account*>&, const string&);

int main()
{
	vector<Account*> accounts;
    string cmd;
    do
	{
		cin >> cmd;
		if(cmd == "add")
		{
			Addition(&accounts);
		}
		else if(cmd == "show")
		{
			Show(accounts);
		}
		else if(cmd == "delete")
		{
			string name;
			cin >> name;
			Delete(accounts, name);
		}
		else if(cmd == "after")
		{
			int year;
			cin >> year;
			Show(accounts, year);
		}
		else if(cmd == "save")
		{
			string filename;
			cin >> filename;
			SaveAccounts(accounts, filename);
		}
		else if(cmd == "load")
		{
			string filename;
			cin >> filename;
			LoadAccounts(filename, &accounts);
		}
	} while(cmd != "quit");
    return 0;
}


void Addition(vector<Account*> *accounts)
{
	Account* ap;
	string name, type;
	int balance;
	double interest_rate;
	cin >> name >> type >> balance >> interest_rate;
	ap = CreateAccount(type, name, balance, interest_rate);
	if(ap != NULL)	accounts->push_back(ap);
}

void Show(vector<Account*>& accounts, int year)
{
	for(size_t i=0;i<accounts.size();i++)
	{
		cout << accounts[i]->name() << " " << accounts[i]->type() << " "
				<< accounts[i]->ComputeExpectedBalance(year) << " " << accounts[i]->interest_rate() << endl;
	}
}

void Delete(vector<Account*>& accounts, const string& name)
{
	size_t i;
	for(i=0;i<accounts.size();i++)
		if(name == accounts[i]->name())	break;

	if(i<accounts.size())
	{
		delete accounts[i];
		accounts.erase(accounts.begin()+i);
	}
}
