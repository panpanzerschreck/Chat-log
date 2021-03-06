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
#include <chrono>

using namespace std;

void mode();
void mnl();
void dmo();
void uto();
void newuser();
void newmessage();
int maxUsers = 4000;


struct Node
{
    message* data;
    Node* prev;
    Node* next;
};
struct message
{
    string text;
    int id;
    user sendFrom;
    user sendTo;
    std::chrono::time_point timeSent;
    message* prev;
    message* next;
};
struct user
{
    int id;
    int name;
};
int main()
{
    string binpath = "manuallog.bin";
    string txtpath = "manuallog.txt";
    fopen(tpath);
    fopen(bpath);
    mode();
    cin.get();
    return 0;
}

void mode() {
    cout << "Choose work mode: 1.Manual/t2.Demo/t3.Auto.";
    int a;
    cin >> a;
    if ( a = 1)
    {
        mnl();
    }
    else if (a = 2)
    {
        dmo();
    }
    else if (a = 3)
    {
        uto();
    }
    else
    {
        mode();
    }
}
void mnl() {
    newuser();
    newmessage();
}

void newuser() {
    cout << "Enter your username" << endl;
    string username;
    cin >> username;
    for (int i = 0; i < maxUsers; i++)
    {
        if (username == ) {
            new user;
        }
    }


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
