#include <iostream>
#include <string> 

#include "addEm.hxx"

#define func(n, a) void show##n(){std::cout << a ;}
func(Menu, "\nWhat would you like to do?\n__________________________\n\n1: Add item to list\n2: Display list\n3: Remove item from list\n4: Remove category from list\n5: Exit application\n\nUser: ")
func(RemoveCategoryPrompt, "Enter the category you would like to remove from the list: ")
func(RemoveItemPrompt, "Enter the item you would like to remove from the list (If subject is longer than one word, enter each word seperately): ")
func(NextPartOfWordPrompt, "\nEnter the next part of your word: ")
#undef func

#define func(n, a) void add##n(){std::cout << a;}
func(Subject, "Enter a subject: ")
func(Category, "Enter a category: ")
func(Note, "Enter your note: ")
#undef func

#define ask(n, a) void ask##n(){std::cout << a;}
ask(ConcatenateWord, "\nWould you like to concatenate your word? [y/n]: ")
ask(IfWordHasAnotherPart, "\nWould you like to enter more? [y/n]: ")

using namespace std;

enum {n, y};
char response[] = {'n', 'y'};

int main()
{
    myList<string> test;
    int userChoice = 0;
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
    cout << endl <<"=========================="<< endl;
    bool useApp = true;
    do
    {
        showMenu();
        cin >> userChoice;
        switch(userChoice)
        {
            case 1:
            {
                string cat, subj, note;
                addCategory(); cin >> cat;
                addSubject(); cin >> subj;
                addNote(); cin >> note;
                test.insertItem(subj, cat, note);
                break;
            }
            case 2:
            {
                test.displayList();
                break;
            }
            case 3:
            {
                string userInputSubject, userInputCategory, userWord;
                char userWantsToMakeLongerWord;
                bool extendWord = false;
                showRemoveCategoryPrompt(); cin >> userInputCategory;
                showRemoveItemPrompt(); cin >> userInputSubject;
                userWord = userInputSubject;
                askConcatenateWord();
                cin >> userWantsToMakeLongerWord;
                extendWord = (userWantsToMakeLongerWord == response[n]) ? false : true;
                while(extendWord)
                {
                    showNextPartOfWordPrompt();
                    cin >> userInputSubject;
                    userWord += " " + userInputSubject;
                    askIfWordHasAnotherPart();
                    cin >> userWantsToMakeLongerWord;
                    extendWord = (userWantsToMakeLongerWord == response[n]) ? false : true;
                }
                test.deleteItem(userWord, userInputCategory);
                break;
            }
            case 4:
            {
                string cat;
                showRemoveCategoryPrompt(); cin >> cat;
                test.deleteLibNodes(cat);
                break;
            }
            case 5:
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