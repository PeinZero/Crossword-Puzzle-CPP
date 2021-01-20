#include <fstream>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <stack>
#include <cstring>
#include <windows.h>
#include "SinglyLinkedList.h"


class CrosswordPuzzle{
private:
	int SIZE;
	string hints[15];
	string database[15];
	
	int x_min , x_max  , y_min  , y_max ;
	
	char largeArray[100][100];
	char **smallArray;
	char temparray[100][100];
	char **smallTemparray;
	char **userArray;
	char **crosswordArray;
	SinglyLinkedList Hints_LL;

public:
	
	CrosswordPuzzle(){
		SIZE = 60;
		for (int i = 0 ; i < 100 ; i++ ){
			for(int j = 0 ; j < 100 ; j++){
				largeArray[i][j]= ' ';
				temparray[i][j] = ' ';
			}
		}
	}
	
	void ReadFromFile(){
		bool check[SIZE] = {false};
		fstream Input_File;
		fstream Hints_File;
		Input_File.open("Input.txt", ios::in);
		Hints_File.open("Hints.txt", ios::in);
		string hint;
		string input;
		int count = 0;
		int temp;
		
		srand(time(0));
		if(Input_File.is_open()){
			while(count != 15){
				temp = (rand() % SIZE);
				while(check[temp] == true){
//					cout << "repeated temp: " << temp << endl;
					temp = (rand() % SIZE);	
				}
//				cout << "temp: " << temp << endl;
				check[temp] = true;
				for(int i = 0; i <= temp; i++){
						fflush(stdin);
						getline(Input_File, input);
						fflush(stdin);
						getline(Hints_File, hint);
				}
				Input_File.close();
				Input_File.open("Input.txt", ios::in);
				Hints_File.close();
				Hints_File.open("Hints.txt", ios::in);
				database[count] = input;
				hints[count] = hint;
				count++;
			}
		}
		else{
			cout << "Input File does not exist";
			exit(1);
		}
		cout << endl << endl;
		for(int i = 0; i < 15; i++){
			cout << i << ": " << database[i] << " = " << hints[i] << endl;
		}
		Input_File.close();
	}
	
	
	void heapify(int n, int i){
	   int largest = i;
	   int l = 2*i + 1;
	   int r = 2*i + 2;
	   if (l < n && database[l].length() < database[largest].length()){
	     largest = l;
	 	}
	    if (r  < n && (database[r].length() < database[largest].length() )){
	     	largest = r;
		}
	    if (largest != i){
	     	swap(database[i], database[largest]);
	     	swap(hints[i], hints[largest]);
	     	heapify(n, largest);
	    }
	}
	
	void heapSort(){
	   for (int i = 15 / 2 - 1; i >= 0; i--)
	     heapify(15, i);
	     
	   for (int i=15-1; i>=0; i--)
	   {
	     swap(database[0], database[i]);
	     swap(hints[0], hints[i]);
	     heapify(i, 0);
	   }
	}
	
	void displayDatabase(){
		cout<<endl;
		for(int i = 0; i < 15; i++){
			cout << i << ": " << database[i] << " = " << hints[i] << endl;
		}
	}
	
	void insertInLargeArray(){
		int len = database[0].length();
		int count = 0;
		stack <string> s1, s2;
		for (int j = 49 ; j < 49 + len ; j++){
		 	largeArray[49][j] = database[0][count];
		 	if (count == 0){
//		 		system("pause");
		 		temparray[49][j] = '1';
			}
			else temparray[49][j] = '-';
		 	count++;
		}
		Hints_LL.addAtTail(hints[0]);
//		displayDatabase();
//		system("pause");
//		displayLargeArray();
		x_min = y_min = y_max = 49;
		x_max = 49+len;
		bool inserted = false;
		int dcount = 1;
		while(dcount < 10){
			for(int i = y_min; i <= y_max; i++){
				for(int j = x_min; j < x_max; j++){
					
					for (int k = 0 ; k < database[dcount].length() ; k++){
						inserted = false;
						if (largeArray[i][j] == database[dcount][k]){
							if((largeArray[i+1][j+1] != ' ') || (largeArray[i+1][j-1] != ' ') || (largeArray[i-1][j-1] != ' ') || (largeArray[i-1][j+1] != ' ')){
								continue;
							}
							if (largeArray[i][j-1] == ' ' && largeArray[i][j+1] == ' '){
								inserted = checkEmptySpace(i , j , k , database[dcount].length() , database[dcount] , 1);
							}
							else if (largeArray[i-1][j] == ' ' && largeArray[i+1][j] == ' ' ){
								inserted = checkEmptySpace(i , j , k , database[dcount].length() , database[dcount] , 0);
							}
							
							if (inserted == true){
								break;
							}
							else{
								s1.push(database[dcount]);
								s2.push(hints[dcount]);
							}
						}
					}
					
					if (inserted == true){
						break;
					}
				}
				
				if (inserted == true){
						break;
				}
			}
			
			dcount++;
		}
//		displayLargeArray();
//		system("pause");
		insertSmallArray();
	}
	
	
	void displayLargeArray(){
		cout<<endl;
		for (int i = 0 ; i < 100 ; i++){
			for (int j = 0 ; j < 100 ; j++){
				cout<<largeArray[i][j];
			}
			cout<<endl;
		}
	}
	
	bool checkEmptySpace(int i , int j , int k , int len , string newWord , int direction){
		bool es = true;
		int count = 0;
		
		int tempk = 0;
		char temp = largeArray[i][j];
//		cout<<"temp: "<< temp <<endl;
//		cout << "direction: " << direction << endl;
		largeArray[i][j] = ' ';
//		system("cls");
//		cout<<i<<" "<<j<<" "<<k<<" "<<len<<endl;
//		system("pause");

		if (direction == 1){
			for (int x = j - k ; x < j + len - k  ; x++){
//				cout<<"array value: "<<largeArray[i][x]<<endl;
//				system("pause");
				if(x == j+len - k - 1) // checking last letter of incoming new string
				{
					if (largeArray[i][j + len - k] != ' '){  //checking next letter after  last letter of incoming string
						largeArray[i][j] = temp;
						return false;
					}
					
					if ( largeArray[i][x] != ' ' ){
						if (largeArray[i][x] != newWord[len -1 ]){
							largeArray[i][j] = temp;
							return false;
						}
					}
					else if (largeArray[i][x] == ' ') {
						if (largeArray[i-1][x] != ' ' || largeArray[i+1][x] != ' '){
							largeArray[i][j] = temp;
							return false;
						}
					}
				}
				else if (x == j - k) { // checking first letter of incoming new string
					if (largeArray[i][j-k-1] != ' '){
						largeArray[i][j] = temp;
						return false;
					}
					
					if ( largeArray[i][x] != ' ' ){
						if (largeArray[i][x] != newWord[0] ){
							largeArray[i][j] = temp;
							return false;
						}
					}
					else if (largeArray[i][x] == ' ') {
						if (largeArray[i-1][x] != ' ' || largeArray[i+1][x] != ' '){
							largeArray[i][j] = temp;
							return false;
						}
					}
				}
				else if ( x == j){
					if (largeArray[i][x] != ' '){
						largeArray[i][j] = temp;
						return false;
					}
				}
				else{  	// checking middle letters of incoming new string
					if (largeArray[i][x] != ' '){
						if (largeArray[i][x] != newWord[tempk]){
							largeArray[i][j] = temp;
							return false;
						}
					}
					else if (largeArray[i][x] == ' '){
						if (largeArray[i-1][x] != ' ' || largeArray[i+1][x] != ' '){
							largeArray[i][j] = temp;
							return false;
						}
					}
				}
				
				tempk++;
			}
			if (es == true){
				if (j - k < x_min){
					x_min = j - k;
				}
				if ( j - k + len > x_max){
					x_max = j - k + len;
				}
				
//				cout<<"here1b"<<endl;
				for (int x = j - k ; x < j + len - k ; x++){
					
					largeArray[i][x] = newWord[count];
					
					if(count == 0){
						temparray[i][x] = '1';	
					}
					else{
						if (temparray[i][x] != '1' || temparray[i][x] == ' ' ){
							temparray[i][x] = '-';
						}
					}
					count++;
				}
				for(int i = 0; i < 15; i++){
					if(newWord == database[i]){
						Hints_LL.addAtTail(hints[i]);
					}
				}
				
			}
		}
		else {
			for (int x = i - k ; x < i + len - k  ; x++){
//				cout<<"array value: "<<largeArray[x][j]<<endl;
//				system("pause");
				if(x == i + len - k - 1) // checking last letter of incoming new string
				{
					if (largeArray[x + 1][j] != ' '){
						largeArray[i][j] = temp;
						return false;
					}
					
					if ( largeArray[x][j] != ' ' ){
						if (largeArray[x][j] != newWord[len - 1]){
							largeArray[i][j] = temp;
							return false;
						}
					}
					else if (largeArray[x][j] == ' ') {
						if (largeArray[x][j-1] != ' ' || largeArray[x][j+1] != ' '){
							largeArray[i][j] = temp;
							return false;
						}
					}
				}
				
				else if (x == i - k) { // checking first letter of incoming new string
					if (largeArray[x-1][j] != ' '){
						largeArray[i][j] = temp;
						return false;
					}
					
					if ( largeArray[x][j] != ' ' ){
						if (largeArray[x][j] != newWord[0] ){
							largeArray[i][j] = temp;
							return false;
						}
					}
					else if (largeArray[x][j] == ' ') {
						if (largeArray[x][j-1] != ' ' || largeArray[x][j+1] != ' '){
							largeArray[i][j] = temp;
							return false;
						}
					}
				}
				else if ( x == i){
					if (largeArray[x][j] != ' '){
						largeArray[i][j] = temp;
						return false;
					}
				}
				else{  	// checking middle letters of incoming new string
					if (largeArray[x][j] != ' '){
						if (largeArray[x][j] != newWord[tempk]){
							largeArray[i][j] = temp;
							return false;
						}
					}
					else if (largeArray[x][j] == ' '){
						if (largeArray[x][j-1] != ' ' || largeArray[x][j+1] != ' '){
							largeArray[i][j] = temp;
							return false;
						}
					}
				}
				
				tempk++;
				
				
			}
			if (es == true){
				if (i - k < y_min){
					y_min = i - k;
				}
				if ( i - k + len > y_max){
					y_max = i - k + len;
				}
				
//				cout<<"here0b"<<endl;
				for (int x = i - k ; x < i + len - k ; x++){
					if(count == 0){
						temparray[x][j] = '1';	
					}
					else{
						if (temparray[x][j] != '1' || temparray[x][j] == ' ' ){
							temparray[x][j] = '-';
						}
					}
					
					largeArray[x][j] = newWord[count];
					count++;
				}
				for(int i = 0; i < 15; i++){
					if(newWord == database[i]){
						Hints_LL.addAtTail(hints[i]);
					}
				}
			}
		}	
//		system("pause");
//		system("pause");
//		displayLargeArray();
		return true;
	}
	
	void insertSmallArray(){
		smallArray = new char* [y_max - y_min];
		smallTemparray = new char* [y_max - y_min];
		userArray = new char* [y_max - y_min];
		crosswordArray = new char* [y_max - y_min];
		
		for (int i = 0 ; i < y_max - y_min ; i++){
			smallArray[i] = new char [x_max - x_min ];
			smallTemparray[i] = new char [x_max - x_min];
			userArray[i] = new char [x_max - x_min ];
			crosswordArray[i] = new char [x_max - x_min ];
		}
		
		
		for (int i =  y_min ;  i < y_max ; i++){
			for (int j = x_min ; j < x_max ; j++ ){
				smallArray[i-y_min][j-x_min] = largeArray[i][j];
				smallTemparray[i-y_min][j-x_min] = temparray[i][j];
				userArray[i-y_min][j-x_min] = temparray[i][j];
				crosswordArray[i-y_min][j-x_min] = temparray[i][j];
			}
		}
		
		y_max = y_max - y_min;
		x_max = x_max - x_min;
		
		
		
	}
	
	void displaySmallArray(){ 
		cout<<endl<<endl<<endl;
		
		for (int i = 0 ; i < y_max ; i++){
			for (int j = 0 ; j < x_max ; j++){
				cout<<smallArray[i][j]<<"  ";
			}
			cout<<endl<<endl;
		}
		
		cout<<endl<<endl<<endl;
		
	}
	
	void SmallTempArray(){
		char count = '1';
		for (int i = 0 ; i < y_max ; i++){
			for (int j =0 ; j < x_max ; j++){
				if (smallTemparray[i][j] == '1'){
					smallTemparray[i][j] = count;
					count++;
				}
			}
		}
		
		for (int i = 0 ; i < y_max ; i++){
			for (int j =0 ; j < x_max ; j++){
				userArray[i][j] = smallTemparray[i][j];
				crosswordArray[i][j] = smallTemparray[i][j];
			}
		}
	}
	
	void displaySmallTempArray(){
		
		for (int i = 0 ; i < y_max ; i++){
			for (int j = 0 ; j < x_max ; j++){
				cout<<smallTemparray[i][j]<<"  ";
			}
			cout<<endl<<endl;
		}
		
		cout<<endl<<endl<<endl;
	}
	
	displayUserArray(){
		
		cout<<endl<<endl<<endl;
		cout<<"          YOUR CROSSWORD"<<endl;
		for (int i = 0 ; i < y_max ; i++){
			for (int j = 0 ; j < x_max ; j++){
				cout<<userArray[i][j]<<"  ";
			}
			cout<<endl<<endl;
		}
		
	}
	
	void displayCrossword(){
		char count = '1';
//		system("cls");
		
		cout<<endl;
		for (int i = 0 ; i <= x_max*0.35 ; i++){
			cout<<"   ";
		}
		cout<<"CROSSWORD"<<endl;
		cout<<" ";
		for (int i = 0 ; i < x_max ; i++){
			cout<<"___";
		}
		cout<<endl;
		cout<<"|";
		for (int i = 0 ; i < x_max ; i++){
				cout<<"   ";
			}
		cout<<"|"<<endl;
		
		for (int i = 0 ; i < y_max ; i++){
			
			for (int j = -1 ; j < x_max ; j++){
				if (j != -1){
					
					if (crosswordArray[i][j] >= 'a' && crosswordArray[i][j] <= 'z'){
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
					}
					cout<<crosswordArray[i][j];
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					cout<<"  ";	
				}
				else cout<<"|";
			}
			cout<<"|"<<endl;
			if (i == y_max -1){
				cout<<"|";
				for (int i = 0 ; i < x_max ; i++){
					cout<<"___";
				}
				cout<<"|";
			}
			else{
				cout<<"|";
				for (int i = 0 ; i < x_max ; i++){
					cout<<"   ";
				}
				cout<<"|"<<endl;
				
			}	
		}
		cout<<endl;
		cout << "\n\n\t\tHints\n" << endl;
		Hints_LL.display();	
	}
	
	void userinput(){
		char position , direction;
		while(1){
			cout<<endl<<endl;
			cout<<"ENTER 0 TO STOP PLAYING."<<endl;
			cout<<"ENTER E to rage quit."<<endl;
			cout<<"Enter at which position you want to enter a letter: ";
			cin >> position;
			if (position == '0'){
				break;
			}
			else if (position == 'E'){
				system("cls");
				displaySmallArray();
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
				cout<<"Thanks for Playing."<<endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				exit(1);
			}
			cout<<"Enter A to add letter to the words across."<<endl;
			cout<<"Enter D to add letter to the words down."<<endl;
			cin >> direction;
			direction = toupper(direction);
			
			for (int i = 0 ; i < y_max ; i++){
				for (int j = 0 ; j < x_max ; j++){
					if (smallTemparray[i][j] == position){
						int row = i , column = j;
						char letter;
						
						if (direction == 'D'){
							if (userArray[i+1][j] != ' '){
								while(1){	
									if (row >= y_max ) {
										break;
									}
									else if (smallTemparray[row][j] == ' ' ){
										break;
									}
									fflush(stdin);
									letter = getch();
									letter = tolower(letter);
									cout<<letter<<endl;
									userArray[row][j] = letter;
									row++;
									
								}
							}
							else{
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
								cout<<"Cannot insert down"<<endl;
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								system("pause");
							}
							
						}
						else if (direction == 'A'){
							if (userArray[i][j+1] != ' '){
								while(1){	
									if (column >= x_max ) {
										break;
									}
									else if (smallTemparray[i][column] == ' ' ){
										break;
									}
									fflush(stdin);
									letter = getch();
									letter = tolower(letter);
									cout<<letter;
									userArray[i][column] = letter;
									column++;
								}
							}
							else{
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
								cout<<"Cannot insert across"<<endl;
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								system("pause");
							}
							
						}
						else {
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
							cout<<"Can only be entered Across or Down."<<endl;
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							system("pause");
						}
						system("cls");
						CheckCrossword(i , j  , direction);
//						displaySmallArray();
						displayCrossword();
						displayUserArray();
						
					}
				}
			}
		}
	}
	
	void CheckCrossword(int row , int column ,  char direction){
		int i = row ,j = column;
		if (direction == 'D'){
			while(1){
				if (i >= y_max ){
					break;
				}
				else if(userArray[i][j] == ' ' ){
					break;
				}
				if (userArray[i][j] != smallArray[i][j] ){
					return;
				}
				i++;
			}
			
			i = row ; j = column;
			
			while(1){
				if (i >= y_max ){
					break;
				}
				else if(userArray[i][j] == ' ' ){
					break;
				}
				crosswordArray[i][j] = userArray[i][j];
				i++;
			}

		}
		else{
			while(1){
				if (userArray[i][j] == ' '){
					break;
				}
				else if   (j >= x_max ){
					break;
				}
				
				if (userArray[i][j] != smallArray[i][j] ){
					return;
				}
				j++;
			}
			
			i = row ; j = column;
			while(1){
				
				if (userArray[i][j] == ' '){
					break;
				}
				else if   (j >= x_max){
					break;
				}
				crosswordArray[i][j] = userArray[i][j];
				j++;
			}
		}
			
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		cout<<endl<<"CORRECT WORD GUESSED."<<endl;
		Beep(800,500);
		Sleep(50);
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		
		for (int i = 0 ; i < y_max ; i++){
			for (int j = 0 ; j < x_max ; j++){
				if (crosswordArray[i][j] == '-'){
					return;
				}
			}
		}
		
		system("cls");
		
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		cout<<"You Finished the crossword. Thanks for Playing."<<endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		
		for (int i = 5 ; i < 11 ; i++){
			Beep(i*100 , 200);
			Sleep(50);
		}
		for (int i = 11 ; i >= 5 ; i--){
			Beep(i*100 , 200);
			Sleep(50);
		}			
		exit(1);
	}
};




int main(){
	CrosswordPuzzle CW;
	CW.ReadFromFile();
	CW.heapSort();
//	CW.displayDatabase();
	CW.insertInLargeArray();
	system("cls");
//	CW.displaySmallArray();
	CW.SmallTempArray();
	CW.displayCrossword();
	CW.userinput();

}
