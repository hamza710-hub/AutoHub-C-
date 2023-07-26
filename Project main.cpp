#include <iostream>
#include <fstream>
#include <conio.h>
#include <iomanip>
#include <cstdio>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

using namespace std;

int a = 0;

class Car{   //Class Car
	public:
	char type[20];
	char color[20];
	int seatingCapacity;
};

class  Brand : public Car{    //Inherited from Car
	public:
		char brand[20],carModelName[20];
		int manufacturingYear,cc,chasisNumber,price;
	
	void getData(){  //Method inside Brand 
	cout << "\n\t\t Enter details of the Car:";
	cout<< "\n\t\t Note: Please press SPACE key before giving Input of the BRAND.\n";
	ofstream fout;  //File Pointer initialised;
	fout.open("mine.doc" ,ios::app);  //Opening File;
		fout << "\n\n";
		cout << "\n\n\t\tBRAND: ";	//Getting Input from Brand
		
			cin.ignore();
		
		cin.getline(brand,20);  
		fout << "\nBRAND: "<< brand; //Writing Brand in a doc file
		cout << "\t\tCAR MODEL NAME: ";	//Car Model Name
		cin.getline(carModelName, 20);
		fout<< "\nCAR MODEL NAME: " <<carModelName;		
		
		cout << "\t\tType: ";	//Type
		cin.getline(type, 20);
		fout << "\nType: "<< type;

		cout << "\t\tColor: ";	//Color
		cin.getline(color, 20);
		fout<< "\nColor: " << color;
		
		cout << "\t\tSeating Capacity(in Persons): ";	//Seating Capacity
		cin >> seatingCapacity;
		fout<< "\nSeating Capacity(in Persons): " << seatingCapacity;
		
		cout << "\t\tManufacturing Year: ";	//Yeat
		cin >> manufacturingYear;
		fout<< "\nManufacturing Year: " << manufacturingYear;
		
		cout << "\t\tCubic Centimeters (CC): ";	//CC
		cin >> cc;
		fout<< "\nCubic Centimeters (CC): " << cc << " CC";
		
		cout << "\t\tChasis Number: ";	//Chasis Num
		srand(time(0));
	    chasisNumber = (rand() % (999999 - 100000 + 1)) + 100000;
		cout << chasisNumber;
		fout<< "\nChasis Number: " << chasisNumber;
		
		cout << "\n\t\tPrice (PKR): ";	//Price
		cin >> price;
		fout<< "\nPrice (PKR):  " << price;
		
		fout<< "\n\n\n";
	
		fout.close();  //Closing the fILE
	}	
	
	
	void showData(){ 
			  //Showing car Object
		cout<<"\n\t\tThe details of the searched car:";
		cout << "\n";
		cout << "\n\t\tBRAND: "<< brand;	    
		cout<< "\n\t\tCAR MODEL NAME: " <<carModelName;
		cout << "\n\t\tType: "<< type;	
		cout<< "\n\t\tColor: " << color;
		cout<< "\n\t\tSeating Capacity(in Persons): " << seatingCapacity;
		cout<< "\n\t\tManufacturing Year: " << manufacturingYear;
		cout<< "\n\t\tCubic Centimeters (CC): " << cc << " CC";
		cout<< "\n\t\tChasis Number: " << chasisNumber;
		cout<< "\n\t\tPrice (PKR):  " << price;
	}
	
}; //Class Ends here;

//User Customer

class Customer{   //Class Customer
	public:
		char name[30],address[100];
		int id;
		
		void userData(){     //Method to get Buyer's Detail
				cout << "\n\t\tEnter your details to confirm the Purchase:";
						cout << "\n\t\tBuyer's Name:";
						cin.ignore();		
						cin.getline(name,20);
						cout<<"\n\t\tBuyer's Address: ";
						cin.getline(address,30);
						cout<<"\n\t\tBuyer's ID no. : ";
						cin >> id;
		}
};




void showImage(char w[20]){  //Function that displays Image of the Car that is searched
					
        //Image Showing feature starts				
	char path[] = "F:\\Final Project\\carImages\\";
    char buf[256];

    strcpy(buf, path);
    strcat(buf, w);
    strcat(buf, ".jpg");	
    puts(buf);
	ShellExecute(0,"open",buf,NULL,NULL,SW_NORMAL);  //Image showing command
		//Image showing feature ends	
}

void writeRecord(){
	
	
	fstream F;
	Brand b1;
	F.open("cardata.dat" ,ios :: app | ios :: binary);

	if(F.fail()){
		cout << "Cant open File";
	}
	else{
		b1.getData();
		a = 1;
		F.write((char*)&b1,sizeof(b1));
	}
	F.close();
}

void searchRecord(){
	fstream F;
	Brand b1;
	int n;
	F.open("cardata.dat", ios :: in | ios :: binary);
	if(F.fail()){
		cout << "The file is not there or curropted or is on vacation.";
	}
	else{
		int chk = 0;
		int test;
		cout << "\n\n\tEnter CHASIS NO. of the car you wish to search:";
		cin >> test;
		while(F.read((char*)&b1,sizeof(b1))){
			if(b1.chasisNumber == test){
				b1.showData();
				//Using showImage Feature
				cout << "\n\n Press 'Y' to see the image of the Car:";
				char inp ;
				inp = getch();
				if(inp == 'y' || inp == 'Y'){
					showImage(b1.carModelName);  //Function called here
				}
				chk = 1;
				break;
			}
		}
		if(chk == 0){
			cout <<"\nSorry! No Car goes by that Name :-(";
		}
	}
	F.close();
}

void buyingTheCar(){
	Customer c1;  //Objects is initialised
	fstream F;
	Brand b1;  //Object is initialised
	int n,z;
	F.open("cardata.dat", ios :: in | ios :: binary);
	if(F.fail()){
		cout << "The file is not there or curropted or is on vacation.";
	}
	else{
		int chk = 0;
		char test[20];
		cout << "Enter the Car name to Buy:";
		cin >> test;
		while(F.read((char*)&b1,sizeof(b1))){
			if(strcmp(b1.carModelName, test) == 0){
				cout << "\n\nDetails of Car you want to Buy:\n";
				b1.showData();
				//Using showImage Feature
				cout << "\n\n Press Y to see the image:";
				char inp ;
				inp = getch();
				if(inp == 'y' || inp == 'Y'){
					showImage(b1.carModelName);  //Function called here	
					
							//Taking Buyer's Details
							c1.userData();
					//Displaying Slip in the Console
							cout << "\n\n";
							cout << "\n\t\tBuyer's Name: "<< c1.name;	 
							cout<< "\n\t\tBuyer's Address: " <<c1.address;	
							cout << "\n\t\tBuyer's Identification Number (ID): "<< c1.id;
							cout << "\n\t\tCar Bought: "<<b1.carModelName;
							cout<< "\n\n\n";	
					//Writing Reciept in a text file
							ofstream fout;
							fout.open("customer.txt" ,ios::app);  //File Open
							fout << "\n\n";
							fout << "\nBuyer's Name: "<< c1.name;	 
							fout<< "\nBuyer's Address: " <<c1.address;	
							fout << "\nBuyer's Identification Number (ID): "<< c1.id;
							fout << "\nCar Bought: "<<b1.carModelName;
							fout<< "\n\n\n";	
							fout.close(); 	//File Closed	
				}
				chk = 1;
				break;
			} 			
	
		}
		if(chk == 0){
			cout <<"\nThe Record not Found";
		}
	}
	F.close();
	
	
}




main(){
	system("color 3f");


	char choice;
	
do{	
		system("cls");
		char option;

	cout << "\t\t __________________________________"<<endl;
	cout << "\t\t|----------------------------------|"<<endl;
	cout << "\t\t|----------------------------------|"<<endl;
	cout << "\t\t|  CAR SHOWROOM MANAGEMENT SYSTEM  |" <<endl;
	cout << "\t\t|----------------------------------|"<<endl;
	cout << "\t\t|----------------------------------|"<<endl;
	cout << "\t\t|__________________________________|"<<endl;
	
	cout <<"\n\n\n\t\t1. Inserting a Car(press I)" << endl;
	cout <<"\t\t2. Searching a Car (press S)" << endl;
	cout <<"\t\t3. Buy a Car(Press B)"<<endl;	
	cout <<"\t\t4. Project info (press A)" << endl;
	cout <<"\t\t5. Exit Program (press E)" << endl;	

	option = getch();
	switch(option){
		case 'I':
		case 'i':
			system("cls");
			writeRecord();
			break;
			
		case 'S':
		case 's':
			system("cls");
			searchRecord();
			break;
		case 'A':
		case 'a':
			system ("cls");
			cout << "\n\t\tProject Name: Car Showroom Management System";
			cout << "\n\t\tSubject : Object Oriented Programming";
			cout << "\n\n\t\tProject Members:";
			cout << "\n\n\t\t1.Ghazanfar Mustufa Mirza 20201-28514";
			cout << "\n\t\t2.Khanzada Ali Haider 20201-27320";
			cout<< "\n\t\t3.Hamza Ali 20201-28615";
			cout <<"\n\n\t\tInstructor : Ma'am Urooj Yusuf Khan";
			cout << "\n\n\t\t ";
			break;
		case 'B':
		case 'b':
			system ("cls");
			buyingTheCar();
			break;
		case 'E':
		case 'e':
			exit(3);
			break;
		default :
			cout << "\n\t\tWrong value entered;";
		
}
	cout << "\n\n\t\tPress any key to exit\n\t\tPress M to return to main";
	choice = getch();
	
} while(choice == 'M' || choice == 'm');
	cout << "\n\nThe Program will now EXIT. You Happy?\n\n";

}


