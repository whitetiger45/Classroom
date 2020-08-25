/* 
    How to Program, 10/e - Dietel
    Fig. 14.10-Fig. 14.13
*/
#include "ClientData.h"
#include <string>
using namespace std;

// default ClientData constructor
ClientData::ClientData(int accountNumberValue, const string& lastName,
    const string& firstName, double balanceValue)
    : accountNumber(accountNumberValue), balance(balanceValue){
    setLastName(lastName);
    setFirstName(firstName);
}

// set account-number value
void ClientData::setAccountNumber(int accountNumberValue){
    accountNumber = accountNumberValue;
}

// get account-number value
int ClientData::getAccountNumber() const {
    return accountNumber;
}

// set last-name value
void ClientData::setLastName(const std::string& lastNameString){
    //copy at most 15 characters from string to lastName
    size_t length{lastNameString.size()};
    length = (length < 15 ? length : 14);
    lastNameString.copy(lastName,length);
    lastName[length] = '\0'; // append null char to lastName
}

// get last-name value
std::string ClientData::getLastName() const{
    return lastName;
}

// set first-name value
void ClientData::setFirstName(const std::string& firstNameString){
    //copy at most 15 characters from string to firstName
    size_t length{firstNameString.size()};
    length = (length < 10 ? length : 9);
    firstNameString.copy(firstName,length);
    firstName[length] = '\0'; // append null char to firstName
}

// get last-name value
std::string ClientData::getFirstName() const{
    return firstName;
}    

// set balance value
void ClientData::setBalance(double balanceValue){
    balance = balanceValue;
}

// get balance value
double ClientData::getBalance() const{
    return balance;
}
