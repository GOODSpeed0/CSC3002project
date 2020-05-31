/*
 *File: login_system.h
 * -----------------
 * This interface defines the LoginSystem class.
 */

#ifndef LOGIN_SYSTEM_H
#define LOGIN_SYSTEM_H

#include <iostream>
#include <string>
#include <map>
#include <array>
using namespace std;

struct User
{
    string username;
    string password;
};


/*
 * Class: LoginSystem
 * --------------------
 *
 */
class LoginSystem
{
public:

    /*
     * LoginSystem constructor and destructor
     * Usage: LoginSystem
     * -----------------------------------
     * The constructor initializes an LoginSystem
     */
    LoginSystem();

    /*
     * Destructor
     * Usage: ~LoginSystem();
     * -----------------------------------
     * The destructor is reponsible for freeing heap storage.
     */
    ~LoginSystem();

    /*
     * Methods: SystemRegister
     * Usage: LoginSystem.SystemRegister(string username, string password)
     * -----------------------------------
     */
    bool SystemRegister(string username, string password);

    /*
     * Methods: SystemEnter
     * Usage: LoginSystem.SystemEnter(string username, string password)
     * -----------------------------------
     */
    bool SystemEnter(string username, string password);

private:

    /* instance variables */

    map<string, string> DataBase;

    /*
     * Methods: getPassword
     * Usage: string password = LoginSystem.getPassword();
     * -----------------------------------
     *
     */
    string getPassword(string username);


    /*
     * Methods: isMatched
     * Usage: bool isMatched = LoginSystem.isMatched(string username, string password);
     * -----------------------------------
     *
     */
    bool isMatched(string username, string password);

    /*
     * Methods: isExsited
     * Usage: bool isExisted = LoginSystem.isExisted(string username);
     * -----------------------------------
     *
     */
    bool isExisted(string username);

};


#endif // LOGIN_SYSTEM_H
