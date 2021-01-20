#include <iostream>

using namespace std;

class Node{
	public:
		string data;
		Node* next;
		
		Node(){
			
			data = "";
			next = NULL;
		}
		
		Node(string data_ , Node* next_){
			data = data_;
			next = next_;
		}
};

class SinglyLinkedList{
	private:
			Node* head;
			Node* tail;
			
	public:
		SinglyLinkedList(){
			
			head = new Node();
			tail = new Node();
			
			head = NULL;
			tail = NULL;
		}
		
		
		void addAtHead(string data_){
			Node* newNode = new Node(data_,head);
			head = newNode;
		}
		
		void addAtTail(string data_){
			Node* newNode = new Node(data_,0);
			
			if (head == NULL){
				head = newNode;
				tail = newNode;
				newNode = 0;			
			}
			else{
				tail->next = newNode;
				tail = newNode;
			}
		}
		
		void add(string searchedData_ , string data_){
			Node* current = new Node();
			
			
			current = head;
			
			while(current->data != searchedData_){
				current = current->next;
			}
			
			Node* newNode = new Node(data_,current->next);
			current->next = newNode;
		}
		
		deleteAtHead(){	
		}
		deleteAtTail(){
		}
		deleteInBetween(){
		}
		
		search(){
		}
		
		void display()
		{
			Node *temp = new Node();
			temp=head;
			while(temp!=NULL)
			{
				cout<<temp->data<<endl;
				temp=temp->next;
			}
		}
	
};
