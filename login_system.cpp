#include "login_system.h"
#include <iostream>
#include <map>

using namespace std;

LoginSystem::LoginSystem(){

//    DataBase.insert(pair<string, string> ("group 37", "37"));
    DataBase.insert(map<string, string>::value_type("group37","37"));

}


LoginSystem::~LoginSystem(){
    DataBase.clear();
}

bool LoginSystem::SystemRegister(string username, string password){

    if (isExisted(username)){
        cout << "This username already exists! Please try again." << endl;
        return false;
    }
    else{
        DataBase.insert(map<string,string>::value_type(username, password));
        cout << "System username register succeed!!!" << endl;
        return true;
    }

}

bool LoginSystem::SystemEnter(string username, string password){
    if (!isExisted(username)){
        cout << "username invalid!!!" << endl;
        return false;
    }
    else{
        if (!isMatched(username, password)){
            cout << "The password does not match the username" << endl;
            return false;
        }
        else{
            cout << "Success!!!" << endl;
            cout << "Hello " << username << "!!!" << endl;
            return true;
        }
    }
}

string LoginSystem::getPassword(string username){
    if (!isExisted(username)){
        cout << "username invalid. Please try again" << endl;
        return "-1";
    }
    else
    {
        return DataBase[username];
    }
}

bool LoginSystem::isExisted(string username){

    if (DataBase.count(username)==0){
        return false;
    }
    else{
        return true;
    }
}


bool LoginSystem::isMatched(string username, string password){
    if (DataBase[username]==password){
        return true;
    }
    else{
        return false;
    }
}


