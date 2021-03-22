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

using namespace std;



int maxUsers = 4000;



struct Node
{
    Node* prev;
    Node* next;
    string text;
    string type;
    size_t id;
    float rate;
    string sentFrom;
    string sentTo;
    time_t timeSent;
    Node(string text = "text", string type = "type", size_t id = 1, float rate = 0, string sentFrom = "text", string sentTo = "text", Node* prev = nullptr, Node* next = nullptr) {
        this->text = text;
        this->id = id;
        this->type = type;
        this->rate = rate;
        this->sentFrom = sentFrom;
        this->sentTo = sentTo;
        this->timeSent = time(NULL);
        this->prev = prev;
        this->next = next;
    }
};
struct doublyLinkedList {
    Node* begin;
    Node* end;
    size_t size;

    doublyLinkedList() {
        begin = nullptr;
        end = nullptr;
        size = 0;
    }


    Node* add(string text, string type, size_t id, float rate, string sentFrom, string sentTo)
    {
        Node* newItem = new Node(text, type, id, rate, sentFrom, sentTo, this->end);
        if (end) {
            this->end->next = newItem;
        }else {
            this->begin = newItem;
        }
        this->end = newItem;
        newItem->id = this->size;
        this->size++;
        return newItem;
    }

    Node* searchText(string tofind) {
            Node* current = begin;
            while (current) {
                if (current->text.find(tofind))
                {
                    return(current);
                }
                current = current->next;
            }
    }
    Node* searchAuthor(string author, float from, float to) {
        Node* current = begin;
        while (current) {
            if (author == current->sentFrom) {
                if (current->rate<to && current->rate >from)
                {
                    return(current);
                }
            }
            current = current->next;
        }
        return nullptr;

    }

    Node* searchType(string type, time_t until) {
        Node* current = begin;
        while (current->timeSent< until) {
            if (type == current->type) {
                    return(current);
            }
            current = current->next;
        }
    }

    void print() {
        Node* current = begin;
        while (current) {
            cout << current->id << " " << current->rate << " " << current->sentFrom << " " << current->sentTo << " " << current->text << " " << current->timeSent << endl;
            current = current->next;
        }
        cout << endl;
    }
    void print(Node* current) {
        cout << current->id << " " << current->rate << " " << current->sentFrom << " " << current->sentTo << " " << current->text << " " << current->timeSent << endl;
        cout << endl;
    }


    bool removeByIndex(size_t indexToRemove) {
        if (indexToRemove >= this->size) {
            return false;
        }
        bool fromBegin = false;
        if (indexToRemove<size/2){
            fromBegin = true;
        }
        Node* current = fromBegin?begin:end;
        int currentIndex = fromBegin ? 0 : size - 1;
        while (current){
            if (currentIndex == indexToRemove) {
                if (current->prev){
                    current->prev->next = current->next;
                }
                else
                {
                    this->begin = current->next;
                }
                if (current->next) {
                    current->next->prev = current->prev;
                }
                else
                {
                    this->end = current->prev;
                }
                delete current;
                this->size--;
                return true;
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
        return false;
    }

    bool changeByIndex(size_t indexTochange, string newText) {
        if (indexTochange >= this->size) {
            return false;
        }
        bool fromBegin = false;



        if (indexTochange < size / 2) {
            fromBegin = true;
        }
        Node* current = fromBegin ? begin : end;
        int currentIndex = fromBegin ? 0 : size - 1;
        while (current) {
            if (currentIndex == indexTochange) {
                Node* changed = new Node(newText, current->type, current->id, current->rate, current->sentFrom, current->sentTo,  current->prev, current->next);
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
        
        
        return false;
    }
};

istream& operator >>(istream is, Node& node) {

    is >> node.text >> node.type >> node.id >>  node.rate >> node.sentFrom >> node.sentTo >> node.timeSent;
    return is;
}


int main()
{
    doublyLinkedList messages;
    //string binpath = "manuallog.bin";
    string txtpath = "txtlog.txt";
    fstream ftxt;
    //fstream fbin;
    ftxt.open(txtpath, fstream::in | fstream::out | fstream::app);

    while (!ftxt.eof())
    {
        string text;
        string type;
        int id;
        float rate;
        string sentFrom;
        string sentTo;
        time_t timeSent;
        ftxt >> text;
        ftxt >> type;
        ftxt >> id;
        ftxt >> rate;
        ftxt >> sentFrom;
        ftxt >> sentTo; 
        ftxt >> timeSent;
        messages.add(text, type, id, rate, sentFrom, sentTo);
    }
    
  //  fbin.open(binpath, fstream::in | fstream::out | fstream::app);
    cout << "Choose work mode: 1.Manual/t2.Demo/t3.Auto." << endl;
    int a=0;
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
            messages.add(text, type, id, rate, sentFrom, sentTo);

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
            string newText;
            cout << "Enter new text" << endl;
            cin >> newText;
            messages.changeByIndex(id, newText);
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
                messages.print(messages.searchText(txttof));
            }
            else if (o == 2)
            {
                cout << "Enter author, lower rate and higher rate" << endl;
                string authtof;
                cin >> authtof;
                float from, to;
                cin >> from;
                cin >> to;
                messages.print(messages.searchAuthor(authtof, from, to));
            }
            else {
                cout << "Enter type and time" << endl;
                string type;
                cin >> type;
                time_t time;
                cin >> time;
                messages.print(messages.searchType(type, time));
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
    while (messages.begin)
    {

        ftxt << messages.begin;
        messages.removeByIndex(0);
    }
    ftxt.close();
    //fbin.close();
    cin.get();
    return 0;
}






// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
