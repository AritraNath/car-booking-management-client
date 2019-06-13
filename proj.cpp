#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdlib.h>
//#include <unistd.h>
#include <algorithm>

using namespace std;

int delay = 3000000;

void clrscr()
{
    system("@cls||clear");
}

template<typename T> void printEle(T t, const int& width)
{
    const char sep    = ' ';
    cout << left << setw(width) << setfill(sep) << t;
}

template <typename T> std::string NumberToString ( T Number )
{
     std::ostringstream ss;
     ss << Number;
     return ss.str();
}

void heading1()
{
	cout<<"\n\n\t\t\t\t\t\t ***** DASHCAR EASY BOOKING PORTAL *****\n";
	cout<<"    \t\t\t\t\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n";
}

void quit()
{
	clrscr();
	heading1();
	cout<<"\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t ***** THANK YOU FOR USING OUR SERVICE, THE APPLICATION WILL NOW TERMINATE!! *****\n\n\n";
	//sleep(delay);
	clrscr();
	exit(0);
}

int heading()
{
	int ch;
	clrscr();
	heading1();
	cout<<"\n\n   Welcome, to the DashCar Booking Portal. Dashcars is India's most trusted and recommended car rental services with doorstep car delivery!\n   Hassle free booking & No hidden Charges. All India Permit & 24*7 Road Assistance.You can choose and rent a car from Bangalore to Delhi,\n   Kolkata, Vizag, Pune, Mysore and many more.\n\n\n ";
	cout<<"\n\n   Select an option to begin...\n\n   1. BOOK a new ride\n   2. VIEW your rides\n   3. MODIFY existing rides\n   4. CANCEL your ride.\n   5. EXIT\n\n";
	cout<<"\n   Enter your option: ";
	cin>>ch;
	return ch;
}

class passenger
{
	public:
	int dd,mm,yy;
	float cst;
	string name, ph, destn;
	void getdata()
	{
		clrscr();
		heading1();
		cout << "\n  Enter passenger details & ride details...\n\n";
		cout<<"\n  Enter the passenger name: ";
		cin>>name;
		cout<<"  Enter phone number: ";
		cin>>ph;

		do
		{
			cout<<"  Enter date of journey (DD/MM/YY): ";
			cin>>dd>>mm>>yy;
			if(dd>31||mm>12)
				cout<<"\n\n\t\t  ***** ERROR !! YOU'VE SELECTED AN INVALID DATE !!! CHOOSE AGAIN *****\n\n";
		}
		while(dd>31||mm>12);

	}
	void dest()
	{
		cout<<"  Enter your destination (Source is BANGALORE): ";
		cin>>destn;
	}
	void calFare(int bf)
	{
		class trvCost
		{
			public:
			string city;
			float cost;
		};

		trvCost t;
		ifstream in;

		in.open("cost.dat", ios::in);
		if(!in)
		{
			cout<<"\n\n\n\t\t  ***** ERROR 12, FILE COULD NOT BE OPENED *****\n\n";
    		quit();
		}
		int i = 0;

		while(!in.eof())
		{

			in >> t.city;
			in >> t.cost;

			if(destn == t.city)
				cst = t.cost * bf;

			i++;
		}
		in.close();
		cout<<"\n\n  Congratulations your ride to "<<destn<<" is scheduled on "<<dd<<"/"<<mm<<"/"<<yy<<".\n  Your total fare is Rs."<<cst<<endl<<endl;

	}
};

class car:public passenger
{

	public:
	bool type;
	int basefare;
	char ch;

	void save2file()
	{
		ofstream out;
		out.open("bookings.dat", ios::out|ios::app);
		out << name << " " << ph << " " << dd << " " << mm << " " << yy << " " << type << " " << destn << " " << cst << "\n";
        out.close();
    }

    void delete1()
	{
		int count = 0;
		char ch = 'n';
		ifstream in;

		in.open("bookings.dat");

		cout<<"\n\n  Enter the customer's name for whom you'd like to cancel the booking: ";
		string n;
		cin >> n;
		transform(n.begin(), n.end(), n.begin(), ::toupper);

		in >> name;
        	transform(name.begin(), name.end(), name.begin(), ::toupper);
		in >> ph >> dd >> mm >> yy >> type >> destn >> cst;
		while(in)
		{
			if(n == name)
				++count;
			in >> name;
        	transform(name.begin(), name.end(), name.begin(), ::toupper);
			in >> ph >> dd >> mm >> yy >> type >> destn >> cst;

		}

		cout << "\n\n  " << count << " matching records found in database...";
		if(count > 0)
		{
			cout << " Are you sure, you want to cancel " << n << "'s booking? : ";
			cin >> ch;
		}

		cout << endl << endl;
		in.close();

		if(ch == 'y' || ch == 'Y')
		{
			ofstream out;
			out.open("temp");
			in.open("bookings.dat");
				in >> name;
       			 transform(name.begin(), name.end(), name.begin(), ::toupper);
	        in >> ph >> dd >> mm >> yy >> type >> destn >> cst;
			while(in)
			{
				if(n == name)
					goto next;
				out<<name<<" "<<ph<<" "<<dd<<" "<<mm<<" "<<yy<<" "<<type<<" "<<destn<<" "<<cst<<"\n";
			next:
				in >> name;
        		transform(name.begin(), name.end(), name.begin(), ::toupper);
				in >> ph >> dd >> mm >> yy >> type >> destn >> cst;

			}
			in.close();
			out.close();
			remove("bookings.dat");
			rename("temp","bookings.dat");
			clrscr();
			heading1();
			cout << "\n\n  " << n <<"'s Booking has been cancelled.\n\n";
		}

	}

    void display()
    {
    	string date;
 	    const int nameWidth = 20;
 	    cout << endl;
 	    cout << "\t\t\t\t\t\t\t ALL SCHEDULED BOOKINGS";
 	    cout << "\n\t\t\t\t\t\t\t ~~~~~~~~~~~~~~~~~~~~~~\n\n";
		cout<<"\t\b\b~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
		cout<<"\n\t  No.\t\t\b\b\b\b\b Name\t\t\b Contact No.\t\t\b\b\b\b\b Vehicle Type\t\b Destination\t    DOJ\t\t\t\b Total Fare\n";
		cout<<"\t\b\b~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    	cout << endl << endl;
		int i = 1;
        ifstream in;
        in.open("bookings.dat",ios::in);
        if(!in)
        {
            cout<<"\n\n\n\t\t  ***** ERROR 12, FILE COULD NOT BE OPENED *****\n\n";
            exit(0);
        }

        in>>name;
        transform(name.begin(), name.end(), name.begin(), ::toupper);
        in>>ph>>dd>>mm>>yy>>type>>destn>>cst;
        transform(destn.begin(), destn.end(), destn.begin(), ::toupper);
        string cst1 = "Rs." + NumberToString(cst);
        date = NumberToString(dd) + "/" + NumberToString(mm) + "/" + NumberToString(yy);
        while(!in.eof())
        {
            printEle(" ", 10);
            printEle(i, 10);
            printEle(name, nameWidth);
			printEle(ph, nameWidth);
			type?(printEle("SUV", nameWidth)):(printEle("SEDAN", nameWidth));
			printEle(destn, nameWidth);
			printEle(date, nameWidth);
			printEle(cst1, nameWidth);
			cout<<endl;
            in>>name;
            transform(name.begin(), name.end(), name.begin(), ::toupper);
            in>>ph>>dd>>mm>>yy>>type>>destn>>cst;
            transform(destn.begin(), destn.end(), destn.begin(), ::toupper);
            cst1 = "Rs." + NumberToString(cst);
            date = NumberToString(dd) + "/" + NumberToString(mm) + "/" + NumberToString(yy);
            i++;
        }
        in.close();
		cout << endl;
		cout<<"\t\b\b~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
		cout<<"\n\t\t\t\t\t\t\t ***** END OF RECORD ******\n";
		cout<<"\t\b\b~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    	cout << endl << endl;
	}
	void gCar()
	{
		cout<<"\n   Select Car type to proceed....\n\n   1. Sedan (4 seater) @ Rs. 6/KM\n   2. SUV (8 seater) @ Rs. 11/KM\n\n\n\n   Enter your choice: ";
		cin>>ch;
		switch(ch)
		{
			case '1': getdata();
			          	type = 0;
						basefare = 7;
						dest();
						calFare(basefare);
						save2file();
						break;

			case '2': getdata();
						type = 1;
			            basefare = 11;
			            dest();
			            calFare(basefare);
			            save2file();
			            break;

			default : quit();
	    }
	 }

};

int main()
{

		int ch;
		char ch1;
		car c;
		do
		{
			ch = heading();
			switch(ch)
			{
				case 1: clrscr();
						heading1();
						c.gCar();
						break;

				case 2: clrscr();
						heading1();
						c.display();
						break;

				case 3: clrscr();
						heading1();
						cout<<"\n\n\n  To Modify data, go back to main menu, delete the existing booking and then add a new booking with the updated details.\n\n\n";
						break;

				case 4: clrscr();
						heading1();
						c.display();
						c.delete1();
						break;

				default: quit();
			}
			cout<<"\n\n  DO YOU WANT TO GO BACK TO THE MAIN MENU (Y/N): ";
			cin>>ch1;
			if(ch1 == 'N'|| ch1 == 'n')
				quit();
		}
		while(ch1 == 'y'||ch1 == 'Y');
}
