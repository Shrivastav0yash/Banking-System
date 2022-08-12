#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<cstdlib>
#include<conio.h>

using namespace std;

#define Min_Bal 500

class insufficientfunds{};

class Account
{
	private:
		long accnumber;
		string firstname;
		string lastname;
		float balance;
		static long nextaccnumber;
	
	public:
		Account()
		{	}	
		Account(string fname, string lname, float bal);
		long getAccNo()
		{
			return accnumber;
		}
		string getfirstname()
		{
			return firstname;
		}
		string getlastname()
		{
			return lastname;
		}
		float getbalance()
		{
			return balance;
		}
		
		void deposit(float amount);
		void withdraw(float amount);
		static void setlastaccnumber(long accnumber);
		static long getlastaccnumber();
		friend ofstream & operator<<(ofstream &ofs, Account &acc);
		friend ifstream & operator>>(ifstream &ifs, Account &acc);
		friend ostream & operator<<(ostream &os, Account &acc);
};

long Account::nextaccnumber = 0;

class Bank
{
	private:
		map<long,Account> accs ;
	public:
		Bank();
		Account OpenAcc(string fname, string lname, float balance);
		Account BalEnq(long accnumber);
		Account deposit(long accnumber, float amount);
		Account withdraw(long accnumber, float amount);
		void closeacc(long accnumber);
		void showallaccounts();
		~Bank();			
};

int main()
{
	Bank b;
	Account acc;
	
	int choice,v;
	string fname, lname;
	
	long accnumber;
	float balance;
	float amount;
	
	cout<<"\t\t\tWelcome to Bank"<<endl;
	v:
		cout<<"\t\tSelect options For Account"<<endl;
		cout<<"\t1.Open Account"<<endl;
		cout<<"\t2.Balance Enquiry"<<endl;
		cout<<"\t3.Deposit"<<endl;
		cout<<"\t4.Withdrawl"<<endl;
		cout<<"\t5.Close Account"<<endl;
		cout<<"\t6.Show All Accounts"<<endl;
		cout<<"\t7.Exit Bank System"<<endl;
		cin>>choice;
		switch(choice)
		{
			case 1:
				cout<<"Enter First name"<<endl;
				cin>>fname;
				cout<<"Enter Last Name"<<endl;
				cin>>lname;
				cout<<"Enter the Amount you Deposit at the time of Opening Account"<<endl;
				cin>>balance;
				if(balance<Min_Bal)
				{
					cout<<"Minimum balance for Account Opening is 500"<<endl;
				}
				else
				{
				acc = b.OpenAcc(fname,lname,balance);
				cout<<"Thankyou For Open Account in Our Bank"<<endl;
				cout<<acc;
				}
				goto v;
			case 2:
				cout<<"Enter Account number"<<endl;
				cin>>accnumber;
				acc = b.BalEnq(accnumber);
				cout<<"Your Accout Details"<<endl;
				cout<<acc;
				goto v;	
			case 3:
				cout<<"Enter Account Number"<<endl;
				cin>>accnumber;
				cout<<"Enter Amount"<<endl;
				cin>>balance;
				acc = b.deposit(accnumber, amount);
				cout<<"Your Account Details"<<endl;
				cout<<acc;
				goto v;
			case 4:
				cout<<"Enter Account Number"<<endl;
				cin>>accnumber;
				cout<<"Enter the Amount"<<endl;
				cin>>amount;
				acc = b.withdraw(accnumber,amount);
				cout<<"Your Account Details"<<endl;
				cout<<acc;
				goto v;
			case 5:
				cout<<"Enter Account Number"<<endl;
				cin>>accnumber;
				b.closeacc(accnumber);
				cout<<"Your Account is Closed"<<endl;
				cout<<acc;
				goto v;
			case 6:
				b.showallaccounts();
				goto v;
			case 7:
				cout<<"Thank you For your Time"<<endl;
				break;
			default:
				cout<<"Choose Correct Option wisely"<<endl;
				goto v;						
		}
	getch();
	return 0;		
}

Account::Account(string fname,string lname,float bal)
{
	nextaccnumber++;
	accnumber = nextaccnumber;
	firstname = fname;
	lastname = lname;
	balance = bal;
}

void Account::deposit(float amount)
{
	balance+=amount;
}

void Account::withdraw(float amount)
{	
	if((balance-amount)<Min_Bal)
	{
		throw insufficientfunds();
	}
	balance-=amount;
}

void Account::setlastaccnumber(long accnumber)
{
	nextaccnumber = accnumber;
}

long Account::getlastaccnumber()
{
	return nextaccnumber;
}

ofstream & operator<<(ofstream &ofs, Account &acc)
{
	ofs<<acc.accnumber<<endl;
	ofs<<acc.firstname<<endl;
	ofs<<acc.lastname<<endl;
	ofs<<acc.balance<<endl;
	return ofs;
}

ifstream & operator>>(ifstream &ifs, Account &acc)
{
	ifs>>acc.accnumber;
	ifs>>acc.firstname;
	ifs>>acc.lastname;
	ifs>>acc.balance;
	return ifs;
}

ostream & operator<<(ostream &os, Account &acc)
{
	os<<"First Name - "<<acc.getfirstname()<<"\tLast Name - "<<acc.getlastname()<<endl;
	os<<"Account Number - "<<acc.getAccNo()<<endl;
	os<<"Balance - "<<acc.getbalance()<<endl;
	return os;
}

Bank::Bank()
{
	Account acc;
	ifstream infile;
	
	infile.open("BANK DATA.txt");
	if(!infile)
	{
		//cout<<"ERROR FILE IS NOT HERE"<<endl;
		return;
	}
	
	while(!infile.eof()) //some function of ifstream in file handling
	{
		infile>>acc;
		accs.insert(pair<long,Account>(acc.getAccNo(),acc));
	}
	
	Account::setlastaccnumber(acc.getAccNo());
	
	infile.close();
}

Account Bank::OpenAcc(string fname,string lname,float balance)
{
	ofstream outfile;
	Account acc(fname,lname,balance);
	accs.insert(pair<long,Account>(acc.getAccNo(),acc));
	
	outfile.open("BANK DATA.txt",ios::trunc);
	map<long,Account>::iterator itr;
	
	for(itr = accs.begin();itr!=accs.end();itr++)
	{
		outfile<<itr->second;		
	}
	outfile.close();
	return acc;
}

Account Bank::BalEnq(long accnumber)
{
	map<long,Account>::iterator itr=accs.find(accnumber);
	return itr->second;
}

Account Bank::deposit(long accnumber,float amount)
{
	map<long,Account>::iterator itr=accs.find(accnumber);
	itr->second.deposit(amount);
	return itr->second;
}

Account Bank::withdraw(long accnumber,float amount)
{
	map<long,Account>::iterator itr=accs.find(accnumber);
	itr->second.deposit(amount);
	return itr->second;
}

void Bank::closeacc(long accnumber)
{
	map<long,Account>::iterator itr=accs.find(accnumber);
	cout<<"Account Delete - "<<itr->second<<endl;
	accs.erase(accnumber); //erase a particluar map value from the maps.
}

void Bank::showallaccounts()
{
	map<long,Account>::iterator itr;
	for(itr = accs.begin();itr!=accs.end();itr++)
	{
		cout<<"Account - "<<itr->first<<"\t"<<itr->second<<endl;
	}
}

Bank::~Bank()
{
	ofstream outfile;
	outfile.open("BANK DATA.txt",ios::trunc);
	map<long,Account>::iterator itr;
	for(itr = accs.begin();itr!=accs.end();itr++)
	{
		outfile<<itr->second;
	}
	outfile.close();
}



