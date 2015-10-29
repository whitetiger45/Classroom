#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <regex> 

#include "addEm.hxx"

#define func(n, a) void show##n(){std::cout << a ;}
func(Title, "Designer:Bryan Kanu\n\n       List Generator\n***************************\n")
func(Menu, "\n        *Main Menu*\n\nWhat would you like to do?\n__________________________\n\n1: Add item to list\n2: Display category and its associated items\n3: Display all lists\n4: Display categories & size of lists\n5: Remove item from list\n6: Remove category from list\n7: Clear all list contents\n8: Export your list to a text file\n9: Run sample program (read input from file & create lists)\n0: Exit application\n\nUser: ")
func(RemoveCategoryPrompt, "Enter the category you would like to remove from the list: ")
func(RemoveItemPrompt, "Enter the item you would like to remove from the list: ")
func(NextPartOfWordPrompt, "\nEnter the next part of your word: ")
#undef func

#define func(n, a) void add##n(){std::cout << a;}
func(Subject, "Enter a subject: ")
func(Category, "Enter a category: ")
func(Note, "Enter your note: ")
#undef func

#define func(n, a) void ask##n(){std::cout << a;}
func(AddMoreToSameCategory, "Would you like to add another item to the same category? [n/y]: ")
func(IfSureAboutListClear, "Are you sure you want to empty the entire list? [n/y]: ")

using namespace std;

enum {n, y};
char response[] = {'n', 'y'};

int main()
{
    showTitle();
    myList<string> test;
    int userChoice = 0;
    /*
    test.insertItem("hello world", "list class", "this is a test");
    test.insertItem("bob marley", "music", "just inputing random Items");
    test.insertItem("Lebron James", "NBA", "Good game last night!");
    test.insertItem("Junior Gong", "music", "what's with the new cd");
    test.insertItem("stephen marley", "list class", "Item three");
    test.displayList();
    cout<< endl <<"Size of music: " << test.librarySize("music") << "\n";
    test.deleteLibNodes("music");
    cout << endl << "=====music deleted=====\n\n";
    test.displayList();
    cout << endl <<"=========================="<< endl;*/
    bool useApp = true;
    do
    {
        showMenu();
        cin >> userChoice;
        if(!(isdigit(userChoice)))
            EXIT_FAILURE;
        if(userChoice > 10 || userChoice < 0)
            userChoice = 0;
        switch(userChoice)
        {
            case 1:
            {
                char cat[256], subj[256], note[256], user[2];
                bool userWantsToAddAnotherItemToSameCategory = false;
                addCategory(); 
                cin.ignore(); cin.getline(cat, 256);
                addSubject(); cin.getline(subj, 256);
                addNote(); cin.getline(note, 256);
                test.insertItem(string(subj), string(cat), string(note));

                askAddMoreToSameCategory();
                cin >> user;
                //std::cout << "response: " << user[0] << "\n";
                if(!(user[0] == response[n]) && !(user[0] == response[y]))
                    user[0] = response[n];
                int i = 0;
                userWantsToAddAnotherItemToSameCategory = (user[0] == response[n]) ? false : true;
                    while(userWantsToAddAnotherItemToSameCategory)
                    {
                        addSubject(); cin.ignore(); cin.getline(subj, 256);
                        addNote(); cin.getline(note, 256);
                        test.insertItem(string(subj), string(cat), string(note));
                        askAddMoreToSameCategory();
                        cin >> user;
                        //std::cout << "response loop [" << ++i << "]: " << user[0] << "\n";
                        userWantsToAddAnotherItemToSameCategory = (user[0] == response[n]) ? false : true;
                    }
                break;
            }
            case 2:
            {
                char userInputCategory[256];
                test.displayCurrentListsAndSizes();
                addCategory(); 
                cin.ignore(); 
                cin.getline(userInputCategory, 256);
                test.displaySpecificCategoryList(string(userInputCategory));
                break;
            }
            case 3:
            {
                test.displayList();
                break;
            }
            case 4:
            {
                test.displayCurrentListsAndSizes();
                break;
            }
            case 5:
            {
                char userInputSubject[256], userInputCategory[256];
                showRemoveCategoryPrompt();
                cin.ignore(); 
                cin.getline(userInputCategory, 256);
                showRemoveItemPrompt(); 
                cin.getline(userInputSubject, 256);
                test.deleteItem(string(userInputSubject), string(userInputCategory));
                break;
            }
            case 6:
            {
                char cat[256];
                showRemoveCategoryPrompt(); cin.ignore(); cin.getline(cat, 256);
                test.deleteLibNodes(string(cat));
                break;
            }
            case 7:
            {
                char user[2];
                askIfSureAboutListClear();
                cin >> user;
                if(!(user[0] == response[n]) && !(user[0] == response[y]))
                    user[0] = response[n];
                bool userWantsToEmptyList = false;
                userWantsToEmptyList = (user[0] == response[n]) ? false :true;
                if(userWantsToEmptyList)
                    test.emptyEntireList();
                else
                    cout << "The list has not been cleared\n";
                break;
            }
            case 8:
            {
                ofstream outputFile("yourList.txt");
                if (outputFile.is_open())
                {

                    //todo 
                    //1)overload display list function to take a file and write items to given file
                    //2)add option to ask if user wants to print entire list or a specific category within this case so not to overload menu options
                    //outputFile.close();
                    outputFile << "This is a test line\n";
                    cout << "\nResults have been written to yourList.txt file\n";
                }

                else cout << "Unable to open file"; 
                break;
            }
            case 9:
            {
                string line;
                ifstream inputFile ("presidents.txt");
                ofstream outputFile("results.txt");
                std::smatch sm;
                int i = 0;
                std::regex presLine("^([0-9]+). ([A-Za-z]+ ?[A-Z]*\.* [A-Za-z]+ ?[A-Za-z]*) .*.*.*((Democratic-Republican|Democrat|Republican|Whig|Federalist|Union)).*.*");
                if (inputFile.is_open() && outputFile.is_open())
                {
                    while ( getline (inputFile,line) )
                    {
                        std::regex_match (line,sm,presLine);
                        if(i++ == 0)
                            continue;
                        outputFile << sm[1]  << ") Name: " << sm[2] << ", Party: " << sm[3] << "\n";
                        test.insertItem(string(sm[2]), string(sm[3]), string(sm[1]));
                    }
                    inputFile.close();
                    outputFile.close();
                    cout << "\nResults have been written to results.txt file\n";
                }

                else cout << "Unable to open file"; 
                break;
            }
            case 0:
            {
                useApp = false;
                break;
            }
            default: 
                cout << "\nPlease enter a valid selection!\n";
        }
    }while(useApp);

    return 0;
}