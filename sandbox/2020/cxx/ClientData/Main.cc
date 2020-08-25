#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iomanip>

#include "ClientData.h"

using namespace std;

enum class Choice {PRINT = 1, DISPLAY, UPDATE, NEW, DELETE, END};

void setClient(ClientData&, int, string&, string&, double);
Choice enterChoice();
void createTextFile(fstream&);
void displayRecords(fstream&);
void updateRecord(fstream&);
void newRecord(fstream&);
void deleteRecord(fstream&);
int getAccount(const char* const);
void outputLine(ostream&, const ClientData&);

int main(){
    fstream ioCredit{"records/credit.dat", ios::in | ios::out | ios::binary};

    // exit program if ofstream could not open file
    if (!ioCredit){
        cerr << "File could not be opened." << endl;
        exit(EXIT_FAILURE);
    }

    ClientData client; // constructor zeros out each data member

    Choice choice;

    while((choice = enterChoice()) != Choice::END) {
        switch (choice) {
            case Choice::PRINT: // create text file from record file
                createTextFile(ioCredit);
                break;
            case Choice::DISPLAY: // display records
                displayRecords(ioCredit);
                break;
            case Choice::UPDATE: // update record
                updateRecord(ioCredit);
                break;
            case Choice::NEW: // create record
                newRecord(ioCredit);
                break;
            case Choice::DELETE: // delete existing record
                deleteRecord(ioCredit);
                break;
            default: // display error if user does not select valid choice
                cerr << "Incorrect choice" << endl;
                break;
        }

        ioCredit.clear(); // reset end-of-file indicator
    }
}

// enable user to input menu choice
Choice enterChoice(){
    // display available options
    cout << "\nEnter your choice\n"
        << "1 - store a formatted text file of accounts\n"
        << "    called \"print.txt\" for printing\n"
        << "2 - display all records\n"
        << "3 - update an account\n"
        << "4 - add a new account\n"
        << "5 - delete an account\n"
        << "6 - end program\n? ";

    int menuChoice;
    cin >> menuChoice; // input menu selection from user
    return static_cast<Choice>(menuChoice);
}

// create formatted text file for printing
void createTextFile(fstream& readFromFile) {
    ofstream outPrintFile("print.txt", ios::out); // create text file

    //exit program if ofstream cannot create file
    if (!outPrintFile) {
        cerr << "File could not be created." << endl;
        exit(EXIT_FAILURE);
    }

    // output column heads
    outPrintFile << left << setw(10) << "Account" << setw(16) 
        << "Last Name" << setw(11) << "First Name" 
        << setw(10) << right << "Balance\n";

    // set file-position pointer to beginning of readFromFile
    readFromFile.seekg(0);

    // read first record from record file
    ClientData client;
    readFromFile.read(
        reinterpret_cast<char*>(&client), sizeof(ClientData));

    // copy all records from record file into text file
    while (!readFromFile.eof()) {
        // write single, non-empty record to text file
        if (client.getAccountNumber() != 0) {
            outputLine(outPrintFile,client);
        }

        //read next record from record file
        readFromFile.read(
            reinterpret_cast<char*>(&client),sizeof(ClientData));
    }
}

// display all records
void displayRecords(fstream& readFromFile){
    // output column heads
    cout << "\n";
    cout << left << setw(10) << "Account" << setw(16) 
        << "Last Name" << setw(11) << "First Name" 
        << setw(10) << right << "Balance\n";

    // set file-position pointer to beginning of readFromFile
    readFromFile.seekg(0);

    // read first record from record file
    ClientData client;
    readFromFile.read(
        reinterpret_cast<char*>(&client), sizeof(ClientData));

    // copy all records from record file into text file
    while (!readFromFile.eof()) {
        // write single, non-empty record to text file
        if (client.getAccountNumber() != 0) {
            outputLine(cout,client);
        }

        //read next record from record file
        readFromFile.read(
            reinterpret_cast<char*>(&client),sizeof(ClientData));
    }
}

// update balance in record
void updateRecord(fstream& updateFile) {
    // obtain number of account to update
    int accountNumber{getAccount("Enter account to update")};

    //move file-position pointer to correct record in file
    updateFile.seekg((accountNumber-1) * sizeof(ClientData));

    // create record object and read first record from file
    ClientData client;
    updateFile.read(reinterpret_cast<char*>(&client), sizeof(ClientData));

    // update record
    if (client.getAccountNumber() != 0) {
        outputLine(cout, client); // display the record

        // request user to specify transaction
        cout << "\nEnter charge (+) or payment (-): ";
        double transaction; // charge or payment
        cin >> transaction;

        // update record balance
        double oldBalance = client.getBalance();
        client.setBalance(oldBalance + transaction);
        outputLine(cout, client); // display the record

        // move file-position pointer to correct record in file
        updateFile.seekp((accountNumber - 1) * sizeof(ClientData));

        // write updated record over old record in file
        updateFile.write(
            reinterpret_cast<const char*>(&client), sizeof(ClientData));
    }
    else{ // display error if account does not exist
        cerr << "Account #" << accountNumber
            << " has no information.\n";
    }
}

// create and insert record
void newRecord(fstream& insertInFile){
    // obtain number of account to create
    int accountNumber{getAccount("Enter new account number")};

    //move file-position pointer to correct record in file
    insertInFile.seekg((accountNumber-1) * sizeof(ClientData));

    // read record from file
    ClientData client;
    insertInFile.read(reinterpret_cast<char*>(&client), sizeof(ClientData));

    // create record, if record does not previously exist
    if (client.getAccountNumber() == 0) {
        string lastName, firstName;
        double balance;

        // user enters last name, first name and balance
        cout << "Enter lastname, firstname and balance\n?";
        cin >> setw(15) >> lastName >> setw(10) >> firstName >> balance;

        // create ClientData Object
        setClient(client,accountNumber,lastName,firstName,balance);

        // move file-position pointer to correct record in file
        insertInFile.seekp((accountNumber-1) * sizeof(ClientData));

        // insert record in file
        insertInFile.write(
            reinterpret_cast<const char *>(&client),sizeof(ClientData));
    }
    else{ // display error if account already exists
        cerr << "Account #" << accountNumber
            << " already contains information.\n";
    }
}

void deleteRecord(fstream& deleteFromFile){
    // obtain number of account to delete
     int accountNumber{getAccount("Enter account number to delete")};

    //move file-position pointer to correct record in file
    deleteFromFile.seekg((accountNumber-1) * sizeof(ClientData));

    // read record from file
    ClientData client;
    deleteFromFile.read(reinterpret_cast<char*>(&client), sizeof(ClientData));

    // delete record, if record exists in file
    if (client.getAccountNumber() != 0) {
        ClientData blankClient; // create blank record

        //move file-position pointer to correct record in file
        deleteFromFile.seekg((accountNumber-1) * sizeof(ClientData));
        deleteFromFile.write(
            reinterpret_cast<const char*>(&blankClient), sizeof(ClientData));

        cout << "Account #" << accountNumber << " deleted.\n";
    }
    else{ // display error if record does not exist
        cerr << "Account #" << accountNumber << " is empty.\n";
    }
}

// obtain account-number value from user
int getAccount(const char* const prompt){
    int accountNumber;

    // obtain account-number value
    do{
        cout << prompt << " (1 - 100): ";
        cin >> accountNumber;
    }while(accountNumber < 1 || accountNumber > 100);

    return accountNumber;
}

void setClient(ClientData& client, int accountNumber, 
                string& lastName, string& firstName, double balance){
    client.setAccountNumber(accountNumber);
    client.setLastName(lastName);
    client.setFirstName(firstName);
    client.setBalance(balance);
}

// display single record
void outputLine(ostream& output, const ClientData& record){
    output << left << setw(10) << record.getAccountNumber()
        << setw(16) << record.getLastName()
        << setw(11) << record.getFirstName()
        << setw(10) << setprecision(2) << right << fixed
        << showpoint << record.getBalance() << endl;
}
