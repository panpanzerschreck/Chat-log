// Chat log.cpp : This file contains the 'main' function. Program execution begins and ends there.

//Інформація про повідомлення у децентралізованій соціальній мережі (є багато серверів, на кожному сервері до 40000 користувачів, повідомлення в рамках одного серверу).

//Для кожного повідомлення зберігаються такі дані: текст повідомлення; точна дата і час відправлення повідомлення; користувач-автор повідомлення; адресат повідомлення 
//(існує спеціальний адресат, що позначає повідомлення для всіх); тип повідомлення – 
//новини, питання, відповідь на питання, запрошення на подію, коментар до іншого повідомлення; оцінка повідомлення від системи боротьби зі спамом (дійсне невід’ємне число, чим ближче до 0 – тим менше шансів, що це спам). 

//Критерії пошуку: Повідомлення, що містять заданий фрагмент тексту; повідомлення з оцінкою у заданому діапазоні від заданого автора; 
//повідомлення заданого типу, надіслані до заданого часу.




#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <chrono>
#include <vector>
#define TXT_PATH "txtlog.txt"

using namespace std;


const int maxUsers = 4000;


struct Message
{
	string text;
	string type;
	size_t id;
	float rate;
	string sentFrom;
	string sentTo;
	time_t timeSent;
	Message(string text = "text", string type = "type", size_t id = 0, float rate = 0, string sentFrom = "text", string sentTo = "text") {
		static int newId = 0;

		this->text = text;
		this->id = newId++;
		this->type = type;
		this->rate = rate;
		this->sentFrom = sentFrom;
		this->sentTo = sentTo;
		
		this->timeSent = time(NULL);
	}
};
struct Node
{
	Node* prev;
	Node* next;
	Message* message;
	Node(Node* prev = nullptr, Node* next = nullptr, Message* message = nullptr) {
		this->prev = prev;
		this->next = next;
		this->message = message;
	}
};

struct DoublyLinkedList {
	Node* begin;
	Node* end;
	size_t size;

	DoublyLinkedList() {
		begin = nullptr;
		end = begin;
		size = 0;
	}

	Node* add(Message* message)
	{
		Node* newItem = new Node(this->end, nullptr, message);
		
		
		if (this->begin == nullptr) {
			this->begin = newItem;
		}else{ this->end->next = newItem; }
		this->end = newItem;
		this->size++;
		return newItem;
	}



	vector<Message*>  searchText(string tofind) {

		vector<Message*> result;
		Node* current = begin;

		while (current = current->next) {
			if (current->message->text.find(tofind)) {
				result.push_back(current->message);
			}
		}

		return result;

	}


	vector<Message*>  searchAuthor(string author, float from, float to) {

		vector<Message*> result;
		Node* current = begin;

		while (current = current->next) {
			if (author == current->message->sentFrom && current->message->rate<to && current->message->rate >from) {
				result.push_back(current->message);
			}
		}

		return result;

	}

	vector<Message*> searchType(string type, time_t until) { 

		vector<Message*> result;
		Node* current = begin;

		while (current = current->next) {
			if (type == current->message->type) {
				result.push_back(current->message);
			}
		}

		return result;
	}

	void print() {
		Node* current = begin;
		while (current) {
			if (current->message) {
				cout << current->message->id << " " << current->message->type << " " << current->message->rate << " " << current->message->sentFrom << " " << current->message->sentTo << " " << current->message->text << " " << current->message->timeSent << endl;
				
			}
			current = current->next;
		}
		cout << endl;
	}

	void print(Message* current) {
		cout << current->id << " " << current->rate << " " << current->sentFrom << " " << current->sentTo << " " << current->text << " " << current->timeSent << endl; 
		cout << endl;
	}

	Message* removeNode(Node* node) {
		if (node->prev)
		{
			node->prev->next = node->next;
		}
		if (node->next)
		{
			node->next->prev = node->prev;
		}
		this->size--;

		return node->message; 
	}

	Message* removeByIndex(size_t indexToRemove) {
		if (indexToRemove >= this->size) {
			return NULL;
		}
		bool fromBegin = false;
		if (indexToRemove < size / 2) {
			fromBegin = true;
		}
		Node* current = fromBegin ? begin : end;
		int currentIndex = fromBegin ? 0 : size - 1;
		while (current) {
			if (currentIndex == indexToRemove) {
				return removeNode(current);
			}
			if (fromBegin)
			{
				current = current->next;
				currentIndex++;
			}
			else
			{
				current = current->prev;
				currentIndex--;
			}

		}
		return NULL;
	}
	void iterate(Node** currentPtr, int* indexPtr, bool fromBegin) {

		if (fromBegin)
		{
			*currentPtr = (*currentPtr)->next;
			(*indexPtr)++;
		}
		else
		{
			*currentPtr = (*currentPtr)->prev;
			(*indexPtr)--;
		}
	}

	Message* getByIndex(size_t indexTochange) {
		if (indexTochange >= this->size) {
			return NULL;
		}
		bool fromBegin = indexTochange < size / 2;
		Node* current = fromBegin ? begin : end;
		int currentIndex = fromBegin ? 0 : size - 1;
		while (current) {
			if (currentIndex == indexTochange) {
				return current->message; 
			}
			current = current->next;
		}

		return NULL;
	}
};


 ostream& operator <<(ostream& os, Node* node) {

	os << node->message->text << node->message->type << node->message->id << node->message->rate << node->message->sentFrom << node->message->sentTo << node->message->timeSent;
	return os;
}


int main()
{
	DoublyLinkedList messages;
	//string binpath = "manuallog.bin";
	
	fstream ftxt;
	//fstream fbin;
	ftxt.open(TXT_PATH, fstream::in | fstream::out);

	string text;
	string type;
	int id;
	float rate;
	string sentFrom;
	string sentTo;
	time_t timeSent;


	while (!ftxt.eof())
	{
		ftxt >> text;
		ftxt >> type;
		ftxt >> id;
		ftxt >> rate;
		ftxt >> sentFrom;
		ftxt >> sentTo;
		ftxt >> timeSent;
		messages.add(new Message(text, type, id, rate, sentFrom, sentTo));
	}

	//  fbin.open(binpath, fstream::in | fstream::out | fstream::app);
	cout << "Choose work mode: 1.Manual/t2.Demo/t3.Auto." << endl;
	int a = 0;
	cin >> a;
	if (a == 1)
	{
		cout << "Choose what to do: 1.Add/t2.Delete/t3.Change/t4.Search." << endl;
		int b;
		cin >> b;
		if (b == 1)
		{
			string text;
			cout << "Enter text" << endl;
			cin >> text;
			string type;
			cout << "Enter type" << endl;
			cin >> type;
			float rate;
			cout << "Enter rate" << endl;
			cin >> rate;
			string sentFrom;
			cout << "Enter name of the user who sent message" << endl;
			cin >> sentFrom;
			string sentTo;
			cout << "Enter name of the user who received message" << endl;
			cin >> sentTo;
			size_t id = 4000;
			messages.add(new Message(text, type, id, rate, sentFrom, sentTo)); 

		}
		else if (b == 2)
		{
			size_t id;
			cout << "Enter index to delete" << endl;
			cin >> id;
			messages.removeByIndex(id);
		}
		else if (b == 3)
		{
			size_t id;
			cout << "Enter index to change" << endl;
			cin >> id;
			cout << "Enter new text" << endl;
			cin >> messages.getByIndex(id)->text;
		}
		else
		{
			cout << "Choose what to search: 1.Messages with certain text /n2.Messages sent by certain author and with certain rate/n3.Messages of certain type, sent until certain time" << endl;
			int o;
			cin >> o;
			if (o == 1)
			{
				cout << "Enter your text" << endl;
				string txttof;
				cin >> txttof;
				vector<Message*> messagesVector = messages.searchText(txttof);
				for (Message* message: messagesVector)
				{
					messages.print(message);
				}
			}
			else if (o == 2)
			{
				cout << "Enter author, lower rate and higher rate" << endl;
				string authtof;
				cin >> authtof;
				float from, to;
				cin >> from;
				cin >> to;
				vector<Message*> messagesVector = messages.searchAuthor(authtof, from, to);
				for (Message* message : messagesVector)
				{
					messages.print(message);
				}
			}
			else {
				cout << "Enter type and time" << endl;
				string type;
				cin >> type;
				time_t time;
				cin >> time;
				vector<Message*> messagesVector = messages.searchType(type, time);
				for (Message* message : messagesVector)
				{
					messages.print(message);
				}
			}

		}
	}
	/*  else if (a = 3)
	  {
		  while()
	  }
	  else
	  {

	  }*/
	messages.print();
	for (size_t i = 0; i < messages.size; i++)
	{
		ftxt << messages.begin;
		messages.removeByIndex(0);
		messages.print();
	}
	ftxt.close();
	//fbin.close();
	cin.get();
	return 0;
}


