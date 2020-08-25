#include <cstdlib>
#include <fstream>
#include <iostream>

#include "ClientData.h"

using namespace std;

int main(){
    fstream outCredit{"credit.dat", ios::in | ios::out | ios::binary};

    // exit program if ofstream could not open file
    if (!outCredit){
        cerr << "File could not be opened." << endl;
        exit(EXIT_FAILURE);
    }

    ClientData blankClient; // constructor zeros out each data member

    // output 100 blank records to file
    for (int i{0}; i < 100; ++i){
        outCredit.write(
            reinterpret_cast<const char*>(&blankClient), sizeof(ClientData));
    }

    cout << "Enter Account Number: ";
    int accountNumber; 
    string lastName, firstName;
    double balance;

    cin >> accountNumber; // read account number

    // user enters information, which is copied into file
    while (accountNumber > 0 && accountNumber <= 100) {
        // user enters last name, first name and balance
        cout << "Enter lastname, firstname and balance\n?";
        cin >> lastName >> firstName >> balance;

        // create ClientData Object
        ClientData client{accountNumber,lastName,firstName,balance};

        // seek position in file of user-specified record
        outCredit.seekp(
            (client.getAccountNumber() - 1) * sizeof(ClientData));

        // write user-specified information in file
        outCredit.write(
            reinterpret_cast<const char*>(&client), sizeof(ClientData));

        // enable user to enter another account
        cout << "Enter account number\n?";
        cin >> accountNumber;
    }
}
