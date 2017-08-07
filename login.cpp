#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>





//****************************************************************************************************************
// class definition


class librarian
{
	long username[20];
	long password[20];
 public:
	void input()
	{
	cout<<"Enter the username: ";
	getname(username);
	cout<<endl;
	cout<<"Enter the password: ";
	getpass(password);
	cout<<endl;
	}

	int access( long [], long []);
	};

	int librarian::access( long ename[20], long epass[20] )
	{  int flag=0;
			for( int i=0;i<20;i++)
			if ( ename[i]==username[i] && epass[i]==password[i] )
					flag=1;
			return flag;
	}



//****************************************************************************************************************

//****************************************************************************************************************
// login function

void login()
{
	librarian l;
	char ch;
	int c=0, access_value=0 , v;
	long uname[20], upass[20];
 start: clrscr();
	gotoxy(30,10);
	cout<<"Username: ";
	getname(uname);
	gotoxy(30,12);
	cout<<"Password: ";
	getpass(upass);
	c++;

//opening binary file

	ifstream filein;
	filein.open("librarian.dat",ios::in||ios::binary);
	while(!filein.eof())
	{
		filein.read((char*)&l,sizeof(l));
		access_value=l.access(uname,upass);

	}
	filein.close();
	ch=getch();


//binary file closed

	if( access_value )
		{
		gotoxy(0,14);
		cout<<"Access granted.....press any key to continue";
		ch=getch();
		}
	else
		{
		gotoxy(0,14);
		if( c<10 )
			{ v=10-c;
			cout<<"Access denied.....you have "<<v<<" tries left. press any key to retry.";
			ch=getch();
			goto start;
			}
		else 	exit(0);
		}

}

//****************************************************************************************************************



//****************************************************************************************************************
//main function

void main()
	{
	char ch;
	librarian l1;
//creating binary file to store the data

	ofstream file;
	file.open("librarian.dat",ios::out||ios::binary);
	file.write((char*)&l1,sizeof(l1));
	l1.input();
	file.close();
//closing the binary file

	login();
	ch=getch();
	}


