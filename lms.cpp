#include<iostream>
#include<fstream>
#include<time.h>
#include<windows.h>
#include<vector>

using namespace std;

HANDLE hStdin; 
DWORD fdwSaveOldMode;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int admin_login();
void admin_panel();
void ShowConsoleCursor(bool showFlag);
int srch_student();

vector<string> student_list;
vector<int> book_list;

int scr=0;
string reg;
string sname;
string eid;
string fname;

class book
{
	private:
		char book_name[50];
		char author[50];
	public:
		int bid;
		void getinfo()
		{
			cout<<"\n\nEnter the book id: ";
			cin>>bid;
			cin.ignore();
			cout<<"\nEnter book name: ";
			cin.getline(book_name,100);
			cout<<"\nEnter author name: ";
			cin.getline(author,100);
		}
		void disp()
		{
			cout<<endl<<bid<<"\t\t"<<book_name<<"\t\t"<<author;
		}
};

class student
{
	public:
		char name[50];
		char registration_no[50];
		char school[50];
		book issued_books[3];
		int nib=0;
	public:
			void create()
			{
				cout<<"\nADDING STUDENT DETAIS\n\n";
				cout<<"\nEnter the registration no: ";
				cin>>registration_no;
				cin.ignore();
				cout<<"\nEnter the name: ";
				cin.getline(name,100);
				cout<<"\nEnter the School: ";
				cin>>school;
			}
			
			void display()
			{
				cout<<registration_no<<"\t\t"<<name<<"\t\t"<<school<<endl;
			}
			
};

class faculty
{
	public:
		char name[50];
		char employee_id[50];
		char school[50];
	public:
			void create()
			{
				cout<<"\nCREATING EMPLOYEEs DETAILS\n";
				cout<<"Enter the employee_id: ";
				cin>>employee_id;
				cin.ignore();
				cout<<"Enter the name: ";
				cin.getline(name,100);
				cout<<"Enter school: ";
				cin>>school;
			}
			
			void display()
			{
				cout<<employee_id<<"\t\t"<<name<<"\t\t"<<school<<endl;
			}
			
};

class borrow
{
	private:
		tm *rqst_date;
		tm *ret_date;
		int fine;
	public:
		book b;
		student s;
		faculty f;
		void show_book()
		{
			b.disp();
		}
		void snew_request(student& x,book& y)
		{
			time_t curr=time(0);
			time_t ret=curr;
			s=x;
			b=y;
			rqst_date=localtime(&curr);
			tm *re=localtime(&ret);
			re->tm_mday+=14;
			//cout<<"ret "<<re->tm_mday;
			ret_date=localtime(&ret);
		}
		void fnew_request(faculty& x,book& y)
		{
			time_t curr=time(0);
			time_t ret=curr;
			f=x;
			b=y;
			rqst_date=localtime(&curr);
			tm *re=localtime(&ret);
			re->tm_mday+=14;
			//cout<<"ret "<<re->tm_mday;
			ret_date=localtime(&ret);
		}
		void calc_fine()
		{
			time_t curr=time(0);
			tm *today=localtime(&curr);
			if((today->tm_mon>ret_date->tm_mon)||(today->tm_mday>ret_date->tm_mday))
			{
				fine=2*(today->tm_mday-ret_date->tm_mday);
			}
			else
			{
				fine=0;
			}
		}
		void show_dates()
		{
			cout<<"\tIssue Date: "<<rqst_date->tm_mday<<" "<<1+rqst_date->tm_mon<<" "<<1900+rqst_date->tm_year;
			cout<<"\tReturn Date: "<<14+rqst_date->tm_mday<<" "<<1+rqst_date->tm_mon<<" "<<1900+rqst_date->tm_year;
			cout<<"\tFine: Rs."<<fine;
		}
};

void gotoXY(int x, int y) 
{ 
    CursorPosition.X = x; 
    CursorPosition.Y = y; 
    SetConsoleCursorPosition(console,CursorPosition); 
}

vector<string> split(const string &text, char sep) {
    vector<string> tokens;
    size_t start = 0, end = 0;
    while ((end = text.find(sep, start)) != string::npos) {
        if (end != start) {
          tokens.push_back(text.substr(start, end - start));
        }
        start = end + 1;
    }
    if (end != start) {
       tokens.push_back(text.substr(start));
    }
    return tokens;
}
student logged_in;
faculty flogged_in;

void delay(int a)
{
    clock_t start;
    start=clock();
    while(clock() - start < a)
    {

    }
}

void get_student()
{
	fstream nf;
	nf.open("student.txt",ios::in);
	student s;
	while(nf.read((char *)&s,sizeof(student)))
	{
		if(s.registration_no==reg)
		{
			logged_in=s;
		}
	}
	nf.close();
}
void get_faculty()
{
	fstream nf;
	nf.open("faculty.txt",ios::in);
	faculty f;
	while(nf.read((char *)&f,sizeof(faculty)))
	{
		if(f.employee_id==eid)
		{
			flogged_in=f;
		}
	}
	nf.close();
}
void StartUpProcesses()
{
	fstream nf;
	nf.open("student.txt",ios::in);
	student s;
	while(nf.read((char *)&s,sizeof(student)))
	{
		student_list.push_back(s.registration_no);
	}
	nf.close();
	nf.open("book.txt",ios::in);
	book b;
	while(nf.read((char *)&b,sizeof(book)))
	{
		book_list.push_back(b.bid);
	}
	nf.close();
}

void start_screen()
{
	system("cls");
	ShowConsoleCursor(false);
	int i,j,clk=0;
	scr=1;
	char title[]={"\n*****************************************Library Management System Version-0.5**************************************\n\n"};
	char credits[]={"Programmed By: \n"};
	while(title[clk]!='\0')           
    {                                 
        printf("%c", title[clk]);
        clk++;                      
        delay(20);                  
    }
    delay(200);
    cout<<"This is a brief description of the program: The main purpose of this project is to maintain easy circulation system using computers and to provide a friendly environment to maintain the details of books and library members.";
    clk=0;
    gotoXY(33,8);
    while(credits[clk]!='\0')
    {
    	printf("%c",credits[clk]);
    	clk++;
    	delay(40);
	}
	delay(100);
	gotoXY(33,10);
	cout<<"Piyush Dubey\t17BCE1285"<<endl;
	delay(80);
	gotoXY(33,12);
	cout<<"Udesh kumar\t17BCE1251"<<endl;
	delay(80);
	gotoXY(33,17);
	cout<<"\xDB Continue";
	gotoXY(33,19);
	cout<<"\xDB Quit";
}

void login_screen()
{
	system("cls");
	reg.clear();
	sname.clear();
	int clk=0;
	char title[]={"****************************************Welcome To Login Panel****************************************"};
	while(title[clk]!='\0')           
    {                                 
        printf("%c", title[clk]);
        clk++;                      
        delay(20);                  
    }
	scr=2;
	gotoXY(33,2);
	cout<<"\xDB Student Login";
	gotoXY(33,4);
	cout<<"\xDB Faculty Login";
	gotoXY(33,6);
	cout<<"\xDB Administrator Login";
	gotoXY(33,8);
	cout<<"\xDB Quit";
}

void student_panel()
{
	system("cls");
	ShowConsoleCursor(false);
	scr=4;
	int clk=0;
	char title[]={"****************************************Welcome To Student Panel****************************************"};
	while(title[clk]!='\0')           
    {                                 
        printf("%c", title[clk]);
        clk++;                      
        delay(20);                  
    }
    gotoXY(2,2);
    cout<<"Welcome "<<sname;
	gotoXY(30,3);
	cout<<"\xDB Display All Books";
	gotoXY(30,5);
	cout<<"\xDB Issue Book";
	gotoXY(30,7);
	cout<<"\xDB Return Book";
	gotoXY(30,9);
	cout<<"\xDB Search Book";
	gotoXY(30,11);
	cout<<"\xDB Go Back";
}

void student_login()
{
	ShowConsoleCursor(true);
	gotoXY(10,19);
	cout<<"Enter your registration number: ";
	cin.ignore();
	char c[10];
	int i = 0,flag=0;
    char b;
    for(i=0;;)
    {
        b=getchar();
        if((b>='a'&&b<='z')||(b>='A'&&b<='Z')||(b>='0'&&b<='9')||(b==' '))
        {
            c[i]=b;
            ++i;
            cout<<b;
        }
        if(b=='\b'&&i>=1)
        {
            cout<<"\b \b";
            --i;
        }
        if(b=='\r')
        {
            c[i]='\0';
            break;
        }
    }
    reg=c;
    get_student();
    ShowConsoleCursor(false);
	if(srch_student()==0)
	{
		gotoXY(10,20);
		cout<<"Wrong Input, Please try again";
		Sleep(1200);
		gotoXY(10,20);
		cout<<"                                       ";
		gotoXY(35,19);
		cout<<"                   ";
		student_login();
	}
	
}

int admin_login()
{
	//system("cls");
	ShowConsoleCursor(true);
	char usrname[50];
	gotoXY(10,19);
	cout<<"Enter Username: ";
	cin.ignore();
    int i = 0,flag=0;
    char b;
    for(i=0;;)
    {
        b=getchar();
        if((b>='a'&&b<='z')||(b>='A'&&b<='Z')||(b>='0'&&b<='9')||(b==' '))
        {
            usrname[i]=b;
            ++i;
            cout<<b;
        }
        if(b=='\b'&&i>=1)//if user typed backspace
            //i should be greater than 1.
        {
            cout<<"\b \b";//rub the character behind the cursor.
            --i;
        }
        if(b=='\r')//if enter is pressed
        {
            usrname[i]='\0';//null means end of string.
            break;//break the loop
        }
    }
	gotoXY(10,20);
	cout<<"Enter Password: ";
	cin.ignore();
	char pass[32];
    char a;
    for(i=0;;)
    {
        a=getchar();//stores char typed in a
        if((a>='a'&&a<='z')||(a>='A'&&a<='Z')||(a>='0'&&a<='9')||(a==' '))
            //check if a is numeric or alphabet
        {
            pass[i]=a;//stores a in pass
            ++i;
            cout<<"*";
        }
        if(a=='\b'&&i>=1)//if user typed backspace
            //i should be greater than 1.
        {
            cout<<"\b \b";//rub the character behind the cursor.
            --i;
        }
        if(a=='\r')//if enter is pressed
        {
            pass[i]='\0';//null means end of string.
            break;//break the loop
        }
    }
	gotoXY(10,22);
	//cout<<"Username: "<<usrname<<"\tPassword: "<<pass;
	ifstream of;
	of.open("admin.txt");
	char l[100];
	vector<string> line;
	while(!of.eof())
	{
		of.getline(l,100);
		line=split(l,',');
		if(line[0]==usrname)
		{
			if(line[1]==pass)
			{
				flag=1;
			}
			else
			{
				flag=2;
			}
		}
	}
	gotoXY(10,24);
	switch(flag)
	{
		case 0:
			cout<<"Username not found!";
			break;
		case 1:
			cout<<"Username and Password matched.";
			//admin_panel();
			Sleep(1200);
			return 1;
			break;
		case 2:
			cout<<"Wrong Password!";
			break;
	}
	of.close();
	ShowConsoleCursor(false);
	Sleep(1200);
	gotoXY(10,19);
	cout<<"                      ";
	gotoXY(10,20);
	cout<<"                      ";
	gotoXY(10,22);
	cout<<"                                                   ";
	gotoXY(10,24);
	cout<<"                                                   ";
	
}

void admin_panel()
{
	system("cls");
	ShowConsoleCursor(false);
	scr=3;
	int clk=0;
	char title[]={"\n****************************************Welcome To Admin Panel****************************************"};
	while(title[clk]!='\0')           
    {                                 
        printf("%c", title[clk]);
        clk++;                      
        delay(20);                  
    }
	gotoXY(34,3);
	cout<<"\xDB Add Student Details";
	gotoXY(34,5);
	cout<<"\xDB Display Student Details";
	gotoXY(34,7);
	cout<<"\xDB Add Faculty";
	gotoXY(34,9);
	cout<<"\xDB Display Faculty List";
	gotoXY(34,11);
	cout<<"\xDB Add Book";
	gotoXY(34,13);
	cout<<"\xDB Display Book List";
	gotoXY(34,15);
	cout<<"\xDB Add Administrator";
	gotoXY(34,17);
	cout<<"\xDB Delete Student Data";
	gotoXY(34,19);
	cout<<"\xDB Delete Faculty Data";
	gotoXY(34,21);
	cout<<"\xDB Delete Book Data";
	gotoXY(34,23);
	cout<<"\xDB Log Out";
}

void add_admin()
{
	system("cls");
	ShowConsoleCursor(true);
	string usrname,pass;
	ifstream of;
	of.open("admin.txt",ios::app);
	bool flag=false;
	do
	{
		flag=false;
		cout<<"\nEnter username: ";
		cin>>usrname;
		cout<<"\nEnter Password: ";
		cin>>pass;
		cout<<"\nUsername: "<<usrname<<"\tPassword: "<<pass;
		char l[100];
		vector<string> line;
		while(!of.eof())
		{
			of.getline(l,100);
			line=split(l,',');
			//cout<<line[0]<<endl;
			if(line[0]==usrname)
			{
				flag=true;
				cout<<"\n\nUsername already exists, Choose another.";
			}
		}
	}while(flag);
	of.close();
	ofstream nf;
	nf.open("admin.txt",ios::app);
	nf<<usrname<<","<<pass<<endl;
	nf.close();
	cout<<"\nNew Administrator account added.";
	Sleep(1200);
	ShowConsoleCursor(false);
}

void add_book()
{
	system("cls");
	ShowConsoleCursor(true);
	book temp;
	cout<<"ADDING NEW BOOK...\n"<<endl;
	temp.getinfo();
	fstream nf;
	nf.open("book.txt",ios::out|ios::app);
	nf.write((char*)&temp,sizeof(temp));
	nf.close();
	cout<<"\n\nBook Added To Database";
	Sleep(1200);
	ShowConsoleCursor(false);
}

void disp_books(int x)
{
	system("cls");
	scr=x;
	fstream nf;
	nf.open("book.txt",ios::in);
	book b;
	cout<<"BOOK ID\t\tBOOK NAME\t\t\tAUTHOR"<<endl;
	while(nf.read((char *)&b,sizeof(b)))
	{
		b.disp();
	}
	nf.close();
	gotoXY(80,20);
	cout<<"\xDB Go Back";
}

void srch_book(int x)
{
	fstream nf;
	nf.open("book.txt",ios::in);
	book b;
	int flag=0;
	while(nf.read((char *)&b,sizeof(b)))
	{
		if(b.bid==x)
		{
			b.disp();
			flag=1;
			break;
		}
	}
	if(flag==0)
	cout<<"No book with id "<<x<<" found!";
	nf.close();
}

void add_student()
{
	system("cls");
	ShowConsoleCursor(true);
	char ch='n';
	fstream fp;
	student stu;
	int i,flag=0;
	string st;
	fp.open("student.txt",ios::out|ios::app);
	do
	{
		flag=0;
		stu.create();
		st=stu.registration_no;
		for(i=0;i<student_list.size();i++)
		{
			if(student_list[i]==st) flag=1;
		}
		if(flag==0)
		{
			fp.write((char*)&stu,sizeof(student));
			StartUpProcesses();
		}
		else
		{
			cout<<"\nStudent already present";
		}
		cout<<"\n\nWanna add more(y|n)"<<endl;
		cin>>ch;
	}
	while(ch=='y'||ch=='Y');
	fp.close();
	ShowConsoleCursor(false);
}

int srch_student()
{
	fstream fp;
	student stu;
    string p;
	int flag=0;
    //cout<<"Enter the registration no of student to be search:"<<endl;
	//cin>>p;
	fp.open("student.txt",ios::in);
	while(fp.read((char *)&stu,sizeof(student)))
	{
		p=stu.registration_no;
		if(reg==p)
		{
			//cout<<stu.display();
			sname=stu.name;
			flag=1;
		}
	}
	fp.close();
	return flag;
}

void delete_student()
{
	system("cls");
	ShowConsoleCursor(true);
	int flag=0;
	student stu;
	string p,reg;
	fstream fp,nf;
	cout<<"\n\nEnter the Registration no. of student: ";
	cin>>reg;
	ShowConsoleCursor(false);
	fp.open("student.txt",ios::in);
	nf.open("temps.txt",ios::out);
	while(fp.read((char *)&stu,sizeof(student)))
	{
		p=stu.registration_no;
		if(reg==p)
		{
			
		}
		else
		{
			flag=1;
			nf.write((char*)&stu,sizeof(student));
		}
	}
	fp.close();
	nf.close();
	remove("student.txt");
	rename("temps.txt","student.txt");
	if(flag==1)	cout<<"\n\nStudent details deleted!";
	else cout<<"\n\nNo Such Student found!";
	StartUpProcesses();
	Sleep(1200);
}

void delete_faculty()
{
	system("cls");
	ShowConsoleCursor(true);
	int flag=0;
	faculty fac;
	string p,reg;
	fstream fp,nf;
	cout<<"\n\nEnter Faculty id: ";
	cin>>reg;
	ShowConsoleCursor(false);
	fp.open("faculty.txt",ios::in);
	nf.open("tempf.txt",ios::out);
	while(fp.read((char *)&fac,sizeof(faculty)))
	{
		p=fac.employee_id;
		if(reg==p)
		{
			
		}
		else
		{
			flag=1;
			nf.write((char*)&fac,sizeof(faculty));
		}
	}
	fp.close();
	nf.close();
	remove("faculty.txt");
	rename("tempf.txt","faculty.txt");
	if(flag==1)	cout<<"\n\nFaculty details deleted!";
	else cout<<"\n\nFaculty id not found!";
	StartUpProcesses();
	Sleep(1200);
}

void delete_book()
{
	system("cls");
	ShowConsoleCursor(true);
	int flag=0;
	book b;
	int p,reg;
	fstream fp,nf;
	cout<<"\n\nEnter Book id: ";
	cin>>reg;
	ShowConsoleCursor(false);
	fp.open("book.txt",ios::in);
	nf.open("tempb.txt",ios::out);
	while(fp.read((char *)&b,sizeof(book)))
	{
		p=b.bid;
		if(reg==p)
		{
			
		}
		else
		{
			flag=1;
			nf.write((char*)&b,sizeof(book));
		}
	}
	fp.close();
	nf.close();
	remove("book.txt");
	rename("tempb.txt","book.txt");
	if(flag==1)	cout<<"\n\nBook deleted!";
	else cout<<"\n\nBook id not found!";
	StartUpProcesses();
	Sleep(1200);
}

void disp_student()
{
	scr=5;
	system("cls");
	fstream fp;
	fp.open("student.txt",ios::in);
	cout<<"STUDENT LIST\n\n"<<endl;
	student s;
	while(fp.read((char *)&s,sizeof(student)))
	{
		s.display();
	}
	fp.close();
	gotoXY(80,20);
	cout<<"\xDB Go Back";
}

void faculty_panel()
{
	system("cls");
	ShowConsoleCursor(false);
	scr=7;
	int clk=0;
	char title[]={"****************************************Welcome To Faculty Panel****************************************"};
	while(title[clk]!='\0')           
    {                                 
        printf("%c", title[clk]);
        clk++;                      
        delay(20);                  
    }
    gotoXY(2,2);
    cout<<"Welcome "<<fname;
	gotoXY(30,3);
	cout<<"\xDB Display All Books";
	gotoXY(30,5);
	cout<<"\xDB Issue Book";
	gotoXY(30,7);
	cout<<"\xDB Return Book";
	gotoXY(30,9);
	cout<<"\xDB Go Back";
}

int srch_faculty()
{
	fstream fp;
	faculty fac;
    string p;
	int flag=0;
	fp.open("faculty.txt",ios::in);
	while(fp.read((char *)&fac,sizeof(faculty)))
	{
		p=fac.employee_id;
		if(eid==p)
		{
			fname=fac.name;
			flag=1;
		}
	}
	fp.close();
	return flag;
}

void faculty_login()
{
	ShowConsoleCursor(true);
	gotoXY(10,19);
	cout<<"Enter your employee id: ";
	cin.ignore();
	char c[10];
	int i = 0,flag=0;
    char b;
    for(i=0;;)
    {
        b=getchar();
        if((b>='a'&&b<='z')||(b>='A'&&b<='Z')||(b>='0'&&b<='9')||(b==' '))
        {
            c[i]=b;
            ++i;
            cout<<b;
        }
        if(b=='\b'&&i>=1)
        {
            cout<<"\b \b";
            --i;
        }
        if(b=='\r')
        {
            c[i]='\0';
            break;
        }
    }
    eid=c;
    get_faculty();
    ShowConsoleCursor(false);
	if(srch_faculty()==0)
	{
		gotoXY(10,20);
		cout<<"Wrong Input, Please try again";
		Sleep(1200);
		gotoXY(10,20);
		cout<<"                                       ";
		gotoXY(35,19);
		cout<<"                   ";
		faculty_login();
	}
	
}


void add_faculty()
{
	system("cls");
	ShowConsoleCursor(true);
	char ch;
	faculty stu;
	fstream fp;
	fp.open("faculty.txt",ios::out|ios::app);
	do
	{
		stu.create();
		fp.write((char*)&stu,sizeof(faculty));
		StartUpProcesses();
		cout<<"\n\nWanna add more(y|n)"<<endl;
		cin>>ch;
		
	}
	while(ch=='y'||ch=='Y');
	fp.close();
	ShowConsoleCursor(false);
}

void disp_faculty()
{
	scr=5;
	system("cls");
	fstream fp;
	fp.open("faculty.txt",ios::in);
	faculty s;
	cout<<"FACULTY LIST\n\n"<<endl;
	while(fp.read((char *)&s,sizeof(faculty)))
	{
		s.display();
	}
	fp.close();
	gotoXY(80,20);
	cout<<"\xDB Go Back";
}

void s_issue_book()
{
	system("cls");
	scr=9;
	int id;
	string p;
	fstream nf,fp,of,f1,f2;
	nf.open("book.txt",ios::in);
	book b,ib;
	student stu,fs,s;
	cout<<"BOOK ID\t\tBOOK NAME\t\t\tAUTHOR"<<endl;
	while(nf.read((char *)&b,sizeof(b)))
	{
		b.disp();
	}
	nf.close();
	gotoXY(0,15);
	ShowConsoleCursor(true);
	cout<<"Enter Book ID: ";
	cin>>id;
	ShowConsoleCursor(false);
	gotoXY(0,17);
	nf.open("book.txt",ios::in);
	while(nf.read((char *)&b,sizeof(b)))
	{
		if(b.bid==id)
		{
			b.disp();
			ib=b;
		}
	}
	nf.close();
	f1.open("borrow.txt",ios::out|ios::app);
	borrow i1;
	i1.snew_request(logged_in,ib);
	f1.write((char*)&i1,sizeof(borrow));
	f1.close();
	cout<<"\n\nBook Issued!";
	gotoXY(80,20);
	cout<<"\xDB Go Back";
}

void s_srch_book()
{
	system("cls");
	scr=9;
	int id;
	string p;
	book b;
	fstream nf,fp,of,f1,f2;
	gotoXY(0,15);
	ShowConsoleCursor(true);
	cout<<"Enter Book ID: ";
	cin>>id;
	ShowConsoleCursor(false);
	gotoXY(0,17);
	nf.open("book.txt",ios::in);
	while(nf.read((char *)&b,sizeof(b)))
	{
		if(b.bid==id)
		{
			b.disp();
		}
	}
	nf.close();
	gotoXY(80,20);
	cout<<"\xDB Go Back";
}

void f_issue_book()
{
	system("cls");
	scr=10;
	int id;
	string p;
	fstream nf,fp,of,f1,f2;
	nf.open("book.txt",ios::in);
	book b,ib;
	faculty f;
	cout<<"BOOK ID\t\tBOOK NAME\t\t\tAUTHOR"<<endl;
	while(nf.read((char *)&b,sizeof(b)))
	{
		b.disp();
	}
	nf.close();
	gotoXY(0,15);
	ShowConsoleCursor(true);
	cout<<"Enter Book ID: ";
	cin>>id;
	ShowConsoleCursor(false);
	gotoXY(0,17);
	nf.open("book.txt",ios::in);
	while(nf.read((char *)&b,sizeof(b)))
	{
		if(b.bid==id)
		{
			b.disp();
			ib=b;
		}
	}
	nf.close();
	f1.open("borrow.txt",ios::out|ios::app);
	borrow i1;
	i1.fnew_request(flogged_in,ib);
	f1.write((char*)&i1,sizeof(borrow));
	f1.close();
	cout<<"\n\nBook Issued!";
	gotoXY(80,20);
	cout<<"\xDB Go Back";
}

void s_return_book()
{
	system("cls");
	scr=9;
	string p;
	int i,j,ret_id;
	student stu,fs,ns;
	fs.nib=0;
	fstream fp,f1,f2;
	f1.open("borrow.txt",ios::in);
	borrow i1;
	while(f1.read((char*)&i1,sizeof(borrow)))
	{
		p=i1.s.registration_no;
		if(p==reg)
		{
			i1.show_book();
			i1.calc_fine();
			i1.show_dates();
		}
	}
	f1.close();
	int q;
	cout<<"\n\nEnter ID of the book to be returned: ";
	cin>>ret_id;
	f1.open("temp.txt",ios::out|ios::app);
	f2.open("borrow.txt",ios::in);
	while(f2.read((char*)&i1,sizeof(borrow)))
	{
		p=i1.s.registration_no;
		q=i1.b.bid;
		if((reg==p)&&(q=ret_id))
		{
			
		}
		else
		{
			f1.write((char*)&i1,sizeof(borrow));
		}
	}
	f2.close();
	f1.close();
	remove("borrow.txt");
	rename("temp.txt","borrow.txt");
	cout<<"\n\nBook Returned";
	gotoXY(80,20);
	cout<<"\xDB Go Back";
}
void f_return_book()
{
	system("cls");
	scr=10;
	string p;
	int i,j,ret_id;
	faculty f;
	//fs.nib=0;
	fstream fp,f1,f2;
	f1.open("borrow.txt",ios::in);
	borrow i1,i2;
	while(f1.read((char*)&i2,sizeof(borrow)))
	{
		p=i2.f.employee_id;
		if(p==eid)
		{
			i2.show_book();
			i2.calc_fine();
			i2.show_dates();
		}
	}
	f1.close();
	int q;
	cout<<"\n\nEnter ID of the book to be returned: ";
	cin>>ret_id;
	f1.open("temp.txt",ios::out);
	f2.open("borrow.txt",ios::in);
	while(f2.read((char*)&i1,sizeof(borrow)))
	{
		p=i1.f.employee_id;
		q=i1.b.bid;
		if((eid!=p)&&(q!=ret_id))
		{
			f1.write((char*)&i1,sizeof(borrow));
		}
	}
	f2.close();
	f1.close();
	remove("borrow.txt");
	rename("temp.txt","borrow.txt");
	cout<<"\n\nBook Returned";
	gotoXY(80,20);
	cout<<"\xDB Go Back";
}
void GetMousePosWin(MOUSE_EVENT_RECORD mer)
{
	int x,y,pass_check=0;
    INPUT_RECORD Inrec;
    DWORD evRead;
    HANDLE hStdIn;
    DWORD dwMode;
    bool Captured=false;

    hStdIn = GetStdHandle(STD_INPUT_HANDLE);
    dwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;

    if( SetConsoleMode( hStdIn, dwMode | ENABLE_MOUSE_INPUT) == TRUE)

        GetConsoleMode(hStdIn, &dwMode);
        SetConsoleMode(hStdIn, (dwMode & (ENABLE_MOUSE_INPUT)));


        do
        {
            PeekConsoleInput(hStdIn, &Inrec, 1, &evRead);

            if( evRead ) 
            { 
                ReadConsoleInput(hStdIn, &Inrec, 1, &evRead);
                x= Inrec.Event.MouseEvent.dwMousePosition.X ;
                y= Inrec.Event.MouseEvent.dwMousePosition.Y ;
                switch (Inrec.EventType )
                {

                case MOUSE_EVENT:
                    {
                        Captured = true;
                        gotoXY(0,27);
                        std::cout << "x->  " << x << " ";
                        gotoXY(10,27);
                        std::cout << "y->  " << y << " ";
                        break;  
                    }
                }
            }

        }while(!Captured);
	switch(scr)
	{
		case 1:
			if((x==33 && y==17) && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		    {
		        gotoXY(47,17);
		        cout << "\xFB";
		        gotoXY(33,23);
		        cout << "You picked continue";
		        Sleep(1200);
		        gotoXY(47,17);
		        cout << " ";
		        gotoXY(33,23);
		        cout << "                             ";
		        system("cls");
				login_screen();
		    }
		    if((x==33 && y==19)&& mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		    {
		    	gotoXY(47,19);
		    	cout<<"\xFB";
		    	gotoXY(33,23);
		    	cout<<"You Picked Quit";
		    	Sleep(1200);
		    	gotoXY(47,19);
		    	cout<<" ";
		    	gotoXY(33,23);
		    	cout<<"                   ";
		    	exit(0);
			}
			break;
		case 2:
			if((x==33 && y==2) && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		    {
		        gotoXY(53,2);
		        cout << "\xFB";
		        gotoXY(33,23);
		        cout << "You picked Student Login";
		        Sleep(1200);
		        gotoXY(53,2);
		        cout << " ";
		        gotoXY(33,23);
		        cout << "                             ";
		        student_login();
		        student_panel();
		        GetMousePosWin(mer);
		    }
		    if((x==33 && y==4) && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		    {
		        gotoXY(53,4);
		        cout << "\xFB";
		        gotoXY(33,23);
		        cout << "You picked Faculty Login";
		        Sleep(1200);
		        gotoXY(53,4);
		        cout << " ";
		        gotoXY(33,23);
		        cout << "                             ";
		        faculty_login();
		        faculty_panel();
		        GetMousePosWin(mer);
		    }
		    if((x==33 && y==6) && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		    {
		        gotoXY(55,6);
		        cout << "\xFB";
		        gotoXY(33,23);
		        cout << "You picked Administrator Login";
		        Sleep(1200);
		        gotoXY(55,6);
		        cout << " ";
		        gotoXY(33,23);
		        cout << "                                  ";
		        if(admin_login()==1)
				{
					admin_panel();
					GetMousePosWin(mer);
				}
		    }
		    if((x==33 && y==8) && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		    {
		        gotoXY(50,8);
		        cout << "\xFB";
		        gotoXY(33,23);
		        cout << "You Decided to Quit!";
		        Sleep(1200);
		        gotoXY(50,8);
		        cout << " ";
		        gotoXY(33,23);
		        cout << "                                  ";
		        exit(0);
		    }
		    break;
		case 3:
			if((x==34 && y==3) && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		    {
		        gotoXY(63,3);
		        cout << "\xFB";
		        gotoXY(33,27);
		        cout << "You Decided to add Student Details";
		        Sleep(1200);
		        gotoXY(63,3);
		        cout << " ";
		        gotoXY(33,23);
		        cout << "                                        ";
		        add_student();
		        admin_panel();
		        GetMousePosWin(mer);
		    }
		    if((x==34 && y==5) && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		    {
		        gotoXY(63,5);
		        cout << "\xFB";
		        gotoXY(33,27);
		        cout << "Displaying Student Details";
		        Sleep(1200);
		        gotoXY(63,5);
		        cout << " ";
		        gotoXY(33,23);
		        cout << "                                         ";
		        disp_student();
		        GetMousePosWin(mer);
		    }
		    if((x==34 && y==7) && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		    {
		        gotoXY(60,7);
		        cout << "\xFB";
		        gotoXY(33,27);
		        cout << "You Decided to add Faculty Details";
		        Sleep(1200);
		        gotoXY(60,7);
		        cout << " ";
		        gotoXY(33,23);
		        cout << "                                           ";
		        add_faculty();
		        admin_panel();
		        GetMousePosWin(mer);
		    }
		    if((x==34 && y==9) && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		    {
		        gotoXY(60,9);
		        cout << "\xFB";
		        gotoXY(33,27);
		        cout << "Displaying Faculty Details";
		        Sleep(1200);
		        gotoXY(60,9);
		        cout << " ";
		        gotoXY(33,23);
		        cout << "                                           ";
		        disp_faculty();
		        GetMousePosWin(mer);
		    }
		    if((x==34 && y==11) && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		    {
		        gotoXY(53,11);
		        cout << "\xFB";
		        gotoXY(33,27);
		        cout << "You Decided to add Book";
		        Sleep(1200);
		        gotoXY(53,11);
		        cout << " ";
		        gotoXY(33,23);
		        cout << "                             ";
		        add_book();
		        admin_panel();
		        GetMousePosWin(mer);
		    }
		    if((x==34 && y==13) && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		    {
		        gotoXY(53,13);
		        cout << "\xFB";
		        gotoXY(33,27);
		        cout << "Displaying Book List";
		        Sleep(1200);
		        gotoXY(53,13);
		        cout << " ";
		        gotoXY(33,23);
		        cout << "                             ";
		        disp_books(5);
		        GetMousePosWin(mer);
		    }
		    if((x==34 && y==15) && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		    {
		        gotoXY(60,15);
		        cout << "\xFB";
		        gotoXY(33,27);
		        cout << "You Decided to add New Administrator";
		        Sleep(1200);
		        gotoXY(60,15);
		        cout << " ";
		        gotoXY(33,23);
		        cout << "                                           ";
		        add_admin();
		        admin_panel();
		        GetMousePosWin(mer);
		    }
		    if((x==34 && y==17) && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		    {
		        gotoXY(60,17);
		        cout << "\xFB";
		        gotoXY(33,27);
		        cout << "You Decided to delete a student detail";
		        Sleep(1200);
		        gotoXY(60,17);
		        cout << " ";
		        gotoXY(33,27);
		        cout << "                                           ";
		        system("cls");
		        delete_student();
		        admin_panel();
		        GetMousePosWin(mer);
		    }
		    if((x==34 && y==19) && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		    {
		        gotoXY(60,19);
		        cout << "\xFB";
		        gotoXY(33,27);
		        cout << "You Decided to delete a faculty detail";
		        Sleep(1200);
		        gotoXY(60,19);
		        cout << " ";
		        gotoXY(33,27);
		        cout << "                                           ";
		        system("cls");
		        delete_faculty();
		        admin_panel();
		        GetMousePosWin(mer);
		    }
		    if((x==34 && y==21) && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		    {
		        gotoXY(60,21);
		        cout << "\xFB";
		        gotoXY(33,27);
		        cout << "You Decided to delete a book";
		        Sleep(1200);
		        gotoXY(47,21);
		        cout << " ";
		        gotoXY(33,27);
		        cout << "                                           ";
		        system("cls");
		        delete_book();
		        admin_panel();
		        GetMousePosWin(mer);
		    }
		    if((x==34 && y==23) && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		    {
		        gotoXY(47,23);
		        cout << "\xFB";
		        gotoXY(33,27);
		        cout << "Logging Out...";
		        Sleep(1200);
		        gotoXY(47,23);
		        cout << " ";
		        gotoXY(33,27);
		        cout << "                                           ";
		        system("cls");
		        login_screen();
		        GetMousePosWin(mer);
		    }
		    break;
		case 4:
			if((x==30 && y==3) && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		    {
		        gotoXY(53,3);
		        cout << "\xFB";
		        gotoXY(33,23);
		        cout << "Showing list of books";
		        Sleep(1200);
		        gotoXY(53,3);
		        cout << " ";
		        gotoXY(33,23);
		        cout << "                                        ";
		        disp_books(6);
		        GetMousePosWin(mer);
		    }
		    if((x==30 && y==5) && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		    {
		        gotoXY(53,5);
		        cout << "\xFB";
		        gotoXY(33,23);
		        cout << "You Decided to issue a book";
		        Sleep(1200);
		        gotoXY(53,5);
		        cout << " ";
		        gotoXY(33,23);
		        cout << "                                        ";
		        s_issue_book();
		        GetMousePosWin(mer);
		    }
		    if((x==30 && y==7) && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		    {
		        gotoXY(53,7);
		        cout << "\xFB";
		        gotoXY(33,23);
		        cout << "You Decided to return book";
		        Sleep(1200);
		        gotoXY(53,7);
		        cout << " ";
		        gotoXY(33,23);
		        cout << "                                        ";
		        s_return_book();
		        GetMousePosWin(mer);
		    }
		    if((x==30 && y==9) && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		    {
		        gotoXY(53,9);
		        cout << "\xFB";
		        gotoXY(33,23);
		        cout << "Searching Book";
		        Sleep(1200);
		        gotoXY(53,9);
		        cout << " ";
		        gotoXY(33,23);
		        cout << "                                        ";
		        system("cls");
		        s_srch_book();
		        GetMousePosWin(mer);
		    }
		    if((x==30 && y==11) && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		    {
		        gotoXY(53,11);
		        cout << "\xFB";
		        gotoXY(33,23);
		        cout << "You Decided to go back";
		        Sleep(1200);
		        gotoXY(53,11);
		        cout << " ";
		        gotoXY(33,23);
		        cout << "                                        ";
		        system("cls");
		        login_screen();
		        GetMousePosWin(mer);
		    }
		    break;
		case 5:
			if((x==80 && y==20) && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		    {
		        //gotoXY(,9);
		        //cout << "\xFB";
		        gotoXY(33,23);
		        cout << "Going Back...";
		        Sleep(1200);
		       //gotoXY(53,9);
		        //cout << " ";
		        gotoXY(33,23);
		        cout << "                                        ";
		        system("cls");
		        admin_panel();
		        Sleep(500);
		        GetMousePosWin(mer);
		    }
		    break;
		case 6:
			if((x==80 && y==20) && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		    {
		        //gotoXY(,9);
		        //cout << "\xFB";
		        gotoXY(33,23);
		        cout << "Going Back...";
		        Sleep(1200);
		       //gotoXY(53,9);
		        //cout << " ";
		        gotoXY(33,23);
		        cout << "                                        ";
		        system("cls");
		        student_panel();
		        GetMousePosWin(mer);
		    }
		    break;
		case 7:
			if((x==30 && y==3) && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		    {
		        gotoXY(53,3);
		        cout << "\xFB";
		        gotoXY(33,23);
		        cout << "Showing list of books";
		        Sleep(1200);
		        gotoXY(53,3);
		        cout << " ";
		        gotoXY(33,23);
		        cout << "                                        ";
		        disp_books(8);
		        GetMousePosWin(mer);
		    }
		    if((x==30 && y==5) && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		    {
		        gotoXY(53,5);
		        cout << "\xFB";
		        gotoXY(33,23);
		        cout << "You Decided to issue a book";
		        Sleep(1200);
		        gotoXY(53,5);
		        cout << " ";
		        gotoXY(33,23);
		        cout << "                                        ";
		        f_issue_book();
		        GetMousePosWin(mer);
		    }
		    if((x==30 && y==7) && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		    {
		        gotoXY(53,7);
		        cout << "\xFB";
		        gotoXY(33,23);
		        cout << "You Decided to return book";
		        Sleep(1200);
		        gotoXY(53,7);
		        cout << " ";
		        gotoXY(33,23);
		        cout << "                                        ";
		        f_return_book();
		        GetMousePosWin(mer);
		    }
		    if((x==30 && y==9) && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		    {
		        gotoXY(53,9);
		        cout << "\xFB";
		        gotoXY(33,23);
		        cout << "You Decided to go back";
		        Sleep(1200);
		        gotoXY(53,9);
		        cout << " ";
		        gotoXY(33,23);
		        cout << "                                        ";
		        system("cls");
		        login_screen();
		        GetMousePosWin(mer);
		    }
		    break;
		case 8:
			if((x==80 && y==20) && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		    {
		        //gotoXY(,9);
		        //cout << "\xFB";
		        gotoXY(33,23);
		        cout << "Going Back...";
		        Sleep(1200);
		       //gotoXY(53,9);
		        //cout << " ";
		        gotoXY(33,23);
		        cout << "                                        ";
		        system("cls");
		        faculty_panel();
		        GetMousePosWin(mer);
		    }
		    break;
		case 9:
			if((x==80 && y==20) && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		    {
		        gotoXY(33,23);
		        cout << "Going Back...";
		        Sleep(1200);
		        gotoXY(33,23);
		        cout << "                                        ";
		        system("cls");
		        student_panel();
		        GetMousePosWin(mer);
		    }
		    break;
		case 10:
			if((x==80 && y==20) && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		    {
		        gotoXY(33,23);
		        cout << "Going Back...";
		        Sleep(1200);
		        gotoXY(33,23);
		        cout << "                                        ";
		        system("cls");
		        faculty_panel();
		        GetMousePosWin(mer);
		    }
		    break;
	}
	
    
}

VOID ErrorExit (LPSTR lpszMessage) 
{ 
    fprintf(stderr, "%s\n", lpszMessage); 

    // Restore input mode on exit.

    SetConsoleMode(hStdin, fdwSaveOldMode);

    ExitProcess(0); 
}

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}


int main()
{
	ShowConsoleCursor(false);
    DWORD cNumRead, fdwMode, i; 
    INPUT_RECORD irInBuf[128]; 
    int counter=0;


    hStdin = GetStdHandle(STD_INPUT_HANDLE); 
    if (hStdin == INVALID_HANDLE_VALUE){
    	char ee[]="GetStdHandle";
        ErrorExit(ee); 
    }


    if (! GetConsoleMode(hStdin, &fdwSaveOldMode) ){
    	char ee[]="GetConsoleMode";
        ErrorExit(ee); 
    }


    fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT; 
    if (! SetConsoleMode(hStdin, fdwMode) ) {
    	char ee[]="SetConsoleMode";
		ErrorExit(ee); 
	}

	
	StartUpProcesses();
	start_screen();

    while (!counter)//++ <= 200) 
    { 
        
		char ee[]="ReadConsoleInput";
        if (! ReadConsoleInput( 
            hStdin,       
            irInBuf,      
            128,          
            &cNumRead) )  
            ErrorExit(ee); 

		
        for (i = 0; i < cNumRead; i++) 
        {
            switch(irInBuf[i].EventType) 
            { 
            case KEY_EVENT:
                break; 

            case MOUSE_EVENT: 
                GetMousePosWin(irInBuf[i].Event.MouseEvent);
                break; 

            case WINDOW_BUFFER_SIZE_EVENT:
                break; 

            case FOCUS_EVENT:

            case MENU_EVENT: 
                break; 

            default:
            	char ee[]="Unknown event type";
                ErrorExit(ee); 
                break; 
            } 
        }
    } 

    // Restore input mode on exit.

    SetConsoleMode(hStdin, fdwSaveOldMode);

    return 0; 
}
