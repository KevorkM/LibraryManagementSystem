#pragma once

#include <iostream>
#include <fstream>
#include <conio.h>
#include <process.h>
#include <string.h>
#include <iomanip>

using namespace std;

class Book {

public:
	char bno[6];
	char bname[50];
	char aname[20];

public:
	void CreateBook() {
		cout << "\n New book entry... \n";
		cout << "\n Enter the new book number: ";
		cin >> bno;

		cout << "\n Enter the name of the book";
		gets_s(bname);
		cout << "\n \n Enter the authors name";
		gets_s(aname);
		cout << "\n\nBook created";
	}
	void ShowBook() {
		cout << "\nBook Number: " << bno;
		cout << "\nBook Name: ";
		puts(bname);
		cout << "Authors name: ";
		puts(aname);
	}
	void ModifyBook() {
		cout << "Book number: " << bno;
		cout << "\n Modify book name: ";
		gets_s(bname);
		cout << "\n Modify Authors name of book: ";
		gets_s(aname);
	}
	char retbno() {
		return bno[6];
	}
	void report() { cout << bno << setw(30) << bname << setw(30) << aname << endl; }
};
class student {

	char admno[6];
	char name[20];
	char stbno[6];
	int token;

public:
	void create_student() {
		clrscr();

		cout << "\n New Student Entry...\n";
		cout << "\n Enter the admission number: ";
		cin >> admno;

		cout << "\n\n Enter the name of the student: ";
		gets_s(name);
		
		token = 0;
		stbno[0] = '/0';

		cout << "\n\n Student Record Created...";
	}

	void ShowStudent() {

		cout << "\nAdmission number: " << admno;
		cout << "\nStudentNumber: ";
		puts(name);
		cout << "\n Number of book issued: " << token;

		if (token == 1)
			cout << "\n Book number" << stbno;
	}

	void modifyStudent() {
		cout << "\nAdmission number: " << admno;
		cout << "\n Modify students name: ";
		gets_s(name);
	}

	char* retadmno() {return admno;}

	char* retstbno() { return stbno; }
	
	int rettoken() { return token; }

	void AddToken() { token = 0; }

	void resetToken() { token = 0; }

	void getstbno(char t[]) { strcpy(stbno,t); }

	void report() { cout << "\t" << admno << setw(20) << name << setw(10) << token << endl; }
};


//global declaration for stream object , object
fstream fp, fp1;
Book bk;
student st;


//function to write file
void WriteBook() {
	char ch;
	fp.open("book.dat", ios::out | ios::app);
	do {
		clrscr();
		bk.CreateBook();
		fp.write((char*)&bk, sizeof(Book));
		cout << "\n\n Do you want to add more record? (Y/N)? ";
		cin >> ch;

	} while (ch == 'y' || ch == 'Y');
	fp.close();
}
void WriteStudent() {
	char ch;
	fp.open("student.dat", ios::out | ios::app);
	do {
		st.create_student();
		fp.write((char*)&st, sizeof(student));
		cout << "\n\n Do you want to add more record? ( Y/N)?";
		cin >> ch;
	} while (ch == 'y' || ch == 'Y');
	fp.close();
}


// function to read record from file
void DisplaySpb(char n[]) {
	cout << "\n Book Details\n";
	int flag = 0;
	fp.open("book.dat", ios::in);
	while (fp.read((char*)&bk, sizeof(Book))) {

		if (strcmpi(bk.retbno(), n) == 0) {
			bk.ShowBook();
			flag = 1;
		}
	}
	fp.close();
	if (flag == 0)
		cout << "\n\n Book does not exist";

}

void DisplaySps(char n[]) {
	cout << "\n Student Details\n";

	int flag = 0;
	fp.open("student.dat", ios::in);
	while (fp.read((char*)&st, sizeof(student))) {
		if (strcmpi(st.retadmno(), n) == 0) {
			st.ShowStudent();
			flag = 1;
		}
	}
	fp.close();
	if (flag == 0)
		cout << "\n Student does not exist";
	getch();
}

//function to modify the record file of the student
void modifyBook() {
	char n[6];
	int found = 0;
	clrscr();
	cout << "\n\nModify book record";
	cout << "\n\n Enter the book number";
	cin >> n;

	fp.open("book.dat", ios::in | ios::out);
	while (fp.read((char*)&bk, sizeof(Book)) && found == 0) {
		if (strcmpi(bk.retbno(), n) == 0) {
			bk.ShowBook();
			cout << "\nEnter the new details of the book" << endl;
			bk.ModifyBook();
			int pos = -1 * sizeof(bk);
			fp.seekp(pos, ios::cur);
			fp.write((char*)&bk, sizeof(Book));
			cout << "\n\n\t Record Updated";
			found = 1;

		}
	}
	fp.close();
	if (found == 0)
		cout << "\n\n Record not found";
	getch();
}

void modifyStudent() {
	char n[6];
	int found = 0;
	clrscr();
	cout << "\n\n\t Modify student record.";
	cout << "\n\n\tEnter the admission number of the student";
	cin >> n;
	fp.open("student.dat", ios::in | ios::out);

	while (fp.read((char*)&st, sizeof(student)) && found == 0) {
		
		if (strcmpi(st.retadmno(), n) == 0) {
			st.ShowStudent();
			cout << "\n Enter the new details of the student" << endl;
			st.modifyStudent();
			int pos = -1 * sizeof(st);
			fp.seekp(pos, ios::cur);
			fp.write((char*)&st, sizeof(student));
			cout << "\n\n\t Record Updated";
			found = 1;
		}

}
	fp.close();
	if (found == 0)
		cout << "\n\n Record not found";
	getch();
}

// function to delete record files

void deleteStudent() {
	char n[6];
	int flag = 0;
	clrscr();
	cout << "\n'n\n\t Delete Student!";
	cout << "\n\n Enter the admission number of the student you want to delete: ";
	cin >> n;
	fp.open("student.dat", ios::in | ios::out);
	fstream fp2;
	fp2.open("Temp.dat", ios::out);
	fp.seekg(0, ios::beg);
	while (fp.read((char*)&st, sizeof(student))) {

		if (strcmp(st.retadmno(), n) != 0)
			fp2.write((char*)&st, sizeof(student));

	else
		flag = 1;
	}
	fp2.close();
	fp.close();
	remove("student.dat");
	rename("Temp.dat", "student.dat");
	if (flag == 1)
		cout << "\n\n\t Record Deleted!";
	else
		cout << "\n\n Record not found!";
	getch();
}

void DeleteBook() {
	char n[6];
	clrscr();
	cout << "\n\n\n\tDelete book!";
	cout << "\n'nEnter the book number you want to delete:";
	cin >> n;

	fp.open("book.dat", ios::in | ios::out);
	fstream fp2;
	fp2.open("Temp.dat", ios::out);
	fp.seekg(0, ios::beg);

	while (fp.read((char*)&bk, sizeof(Book))) {
		if (strcmpi(bk.retbno(), n) != 0) {
			fp2.write((char*)&bk, sizeof(Book));
		}
	}
	fp2.close();
	fp.close();
	remove("book.dat");
	rename("temp.dat", "book.dat");
	cout << "\n\n\tRecord Deleted!";
	getch();
}

// function to display all student list

void DisplayAlls() {
	clrscr();

	fp.open("student.dat", ios::in);
	if (!fp) {
		cout << "Error!!! File could not be opened";
		getch();
		return;
	}

	cout << "\n\n\t\tStudent list \n\n";
	cout << "\n";
	cout << "\tAdmission number: " << setw(10) << "Name" << setw(20) << "Book issued\n";

	while (fp.read((char*)&st, sizeof(student)))
	{
		st.report();
	}

	fp.close();
	getch();
}

//function to display books list

void DisplayAllb() {
	clrscr();
	fp.open("book.dat", ios::in);

	if (!fp) {
		cout << "ERROR!!! File could not be opened";
		getch();
		return;
	}

	cout << "\n\n\t\tSTUDENT LIST\n\n";
	cout << "\tBook Number: " << setw(20) << "Book name" << setw(25) << "Author\n";

	while (fp.read((char*)&bk, sizeof(Book))) {
		bk.report();
	}
	fp.close();
	getch();
}

//function to issue book

void BookIssue() {
	char sn[6], bn[6];
	int found = 0, flag = 0;
	clrscr();

	cout << "\n\nBook issue!";
	cout << "\n\n\t Enter the students account number.";
	cin >> sn;
	fp.open("student.dat", ios::in | ios::out);
	fp1.open("book.dat", ios::in | ios::out);

	while (fp.read((char*)&st, sizeof(student)) && found == 0)
	{
		if (strcmpi(st.retadmno(), sn) == 0) {
			found = 1;

			if (st.rettoken() == 0) {
				cout << "\n\n\t Enter the book number";
				cin >> bn;

				while (fp1.read((char*)&bk, sizeof(Book))&& flag==0) {
					if (strcmpi(bk.retbno(), bn) == 0) {
						bk.ShowBook();
						flag = 1;
						st.AddToken();
						st.getstbno(bk.retbno());
						int pos = -1 * sizeof(st);
						fp.seekp(pos, ios::cur);
						fp.write((char*)&st, sizeof(student));
						cout<<"\n\n\t Book issued successfully\n\n please not: write current date in backside of the book and submit within 15 days fine Rs. 1 for each day after the 15 days period";
					
					}
				}
				if (flag == 0)
					cout << "Book does not exist";

			}
			else
				cout << "You have not returned the last book";
		}
	}
	if (found == 0)
		cout << "Student record does not exist!";
		getch();
		fp.close();
		fp1.close();
}

// function to deposit book
void BookDeposit()
{
	char sn[6], bn[6];
	int found = 0, flag = 0, day, fine;
	clrscr();
	cout << "\n\nBOOK DEPOSIT ...";
	cout << "\n\n\tEnter The student’s admission no.";
	cin >> sn;
	fp.open("student.dat", ios::in | ios::out);
	fp1.open("book.dat", ios::in | ios::out);
	while (fp.read((char*)&st, sizeof(student)) && found == 0)
	{
		if (strcmpi(st.retadmno(), sn) == 0)
		{
			found = 1;
			if (st.rettoken() == 1)
			{
				while (fp1.read((char*)&bk, sizeof(Book)) && flag == 0)
				{
					if (strcmpi(bk.retbno(), st.retstbno()) == 0)
					{
						bk.ShowBook();
						flag = 1;
						cout << "\n\nBook deposited in no. of days";
						cin >> day;
						if (day > 15)
						{
							fine = (day - 15) * 1;
							cout << "\n\nFine has to deposited Rs. " << fine;
						}
						st.resetToken();
						int pos = -1 * sizeof(st);
						fp.seekp(pos, ios::cur);
						fp.write((char*)&st, sizeof(student));
						cout << "\n\n\t Book deposited successfully";
					}
				}
				if (flag == 0)
					cout << "Book no does not exist";
			}
			else
				cout << "No book is issued..please check!!";
		}
	}
	if (found == 0)
		cout << "Student record not exist...";
	getch();
	fp.close();
	fp1.close();
}


// introduction to function

void intro() {
	
	clrscr();
	gotoxy(35, 11);
	cout << "Library";
	gotoxy(35, 14);
	cout << "Management";
	gotoxy(35, 17);
	cout << "System";
	cout << "\n\n Made by: Your name here";
	cout << "\n\n School: School name here";
	getch();

}

// Administrator meny function

void AdminMenu() {

	clrscr();
	int ch2;

	cout << "\n\n\n\tADMINISTRATOR MENU";
	cout << "\n\n\t1.CREATE STUDENT RECORD";
	cout << "\n\n\t2.DISPLAY ALL STUDENTS RECORD";
	cout << "\n\n\t3.DISPLAY SPECIFIC STUDENT RECORD ";
	cout << "\n\n\t4.MODIFY STUDENT RECORD";
	cout << "\n\n\t5.DELETE STUDENT RECORD";
	cout << "\n\n\t6.CREATE BOOK ";
	cout << "\n\n\t7.DISPLAY ALL BOOKS ";
	cout << "\n\n\t8.DISPLAY SPECIFIC BOOK ";
	cout << "\n\n\t9.MODIFY BOOK ";
	cout << "\n\n\t10.DELETE BOOK ";
	cout << "\n\n\t11.BACK TO MAIN MENU";
	cout << "\n\n\tPlease Enter Your Choice (1-11) ";
	cin >> ch2;

	switch (ch2) {
	case 1: 
		clrscr();
		WriteStudent();
		break;
	case 2:
		DisplayAlls();
		break;
	case 3:
		char num[6];
		clrscr();
		cout << "\n\n\t Please enter the admission number";
		cin >> num;
		DisplaySps(num);
		break;
	case 4:
		modifyStudent();
		break;
	case 5:
		deleteStudent();
		break;
	case 6:
		clrscr();
		WriteBook();
		break;
	case 7:
		DisplayAllb();
		break;
	case 8:
		char num[6];
		clrscr();
		cout << "\n\n\tPlease enter the book number.";
		cin >> num;
		DisplaySpb(num);
		break;
	case 9:
		modifyBook();
		break;
	case 10:
		DeleteBook();
		break;
	case 11:
		return;
	default:
		cout << "\a";
	}
}

void main() {

	char ch;
	intro();
	do {
		clrscr();
		cout << "\n\n\n\tMain Menu";
		cout << "\n\n\t01. BOOK Issue";
		cout << "\n\n\t02. Book Deposit";
		cout << "\n\n\t03. Administrator Menu";
		cout << "\n\n\t04. EXIT";
		cout << "\n\n\tPlease Select Your Option (1-4) ";
		ch = getche();

		switch (ch) {
		case 1:
			clrscr();
			BookIssue();
			break;
		case 2:
			BookDeposit();
			break;
		case 3:
			AdminMenu();
			break;
		case 4:
			exit(0);
		default:
			cout << "\a";
		}
	} while (ch != '4');
}

void clrscr(){}