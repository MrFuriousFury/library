#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>



//****************************************************************************************************************
// function definitions


long binary( long m )
	{
	int i=0, j, p;
	long binary_array[20], bin=0;
	while( m>0 )
		{
		binary_array[i]=m%2;
		m=m/2;
		i++;
		}
	for ( j=i-1;j>=0;j--,p++ )
		{
		bin+= pow(10,j)*binary_array[j];
		}
	return bin;
	}

void encrypt( long array[20] )  // array conatains the ascii value of either password or username
	{
	int l;
	long m,n;
	for( l=0;l<20;l++)
		{
		m=array[l];
		n=binary(m);
		array[l]=m+n;
		}
	}

void getname( long user[20] )   // user/uname array stores the ascii value of entered username characeters
	{
	char ch;
	int i,j,flag=0;
	long k;
	for( i=0;i<20;i++ )
		{
			ch=getch();
			if( ch!=13 )
				{
				k=ch;          //k stores the ascii value
				user[i]=k;
				cout<<ch;
				}
			else
				for( j=i;j<20;j++)
					 {user[j]=0;
					 flag=1;
					 }
	  if(flag)
		i=j;
		}
	encrypt(user);

	}

void getpass( long pass[20] ) // pass/upass array stores the ascii value of entered password characters
	{
	char ch;
	int i,j,flag=0;
	long k;
	for( i=0;i<20;i++ )
		{
		ch=getch();
		if( ch!=13 )
			{
			k=ch;          //k stores the ascii value
			pass[i]=k;
			cout<<"*";
			}
		else
		  for(j=i;j<20;j++)
				 {pass[j]=0;
				 flag=1;}

		  if (flag)
			i=j;

		}
		encrypt(pass);
	}

//****************************************************************************************************************



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

//****************************************************************************************************************
