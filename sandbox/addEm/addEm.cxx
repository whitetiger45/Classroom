#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <regex> 

#include "addEm.hxx"

#define func(n, a) void show##n(){std::cout << a ;}
func(Title, "Designer:Bryan Kanu\n\n       List Generator\n***************************\n")
func(Menu, "\n        *Main Menu*\n\nWhat would you like to do?\n__________________________\n\n1: Add item to list\n2: Display category and its associated items\n3: Display all lists\n4: Display categories & size of lists\n5: Remove item from list\n6: Remove category from list\n7: Clear all list contents\n8: Export your list to a text file\n9: Run sample program (read input from file & create lists)\n0: Exit application\n\nUser: ")
func(Category_SubMenu, "\n*Type 'back' at any time to return to last menu*\nEnter a category: ")
func(RemoveCategoryPrompt, "\n*Type 'back' to return to last menu*\nEnter the category you would like to remove from the list: ")
func(RemoveItemPrompt, "Enter the item you would like to remove from the list: ")
func(DisplaySpecificSubjectFromCategoryPrompt, "\nWould you like to:\n__________________________\n\n1: Display specific item from a specific category\n2: Display the entire category\n3: Return to main menu\n\nUser: ")
func(ExportFullListOrSpecificCategoryPrompt, "\nPlease select an option\n__________________________\n1: Export a specific category only\n2: Export all\n3: Return to main menu\nUser: ")
#undef func

#define func(n, a) void add##n(){std::cout << a;}
func(Subject, "Enter a subject: ")
func(Category, "\nEnter a category: ")
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
    myList<string> app;
    int userChoice = 0;
    bool useApp = true;
    do
    {
        mainMenu:
        showMenu();
        cin >> userChoice;
        if(!(isdigit(userChoice)))
            EXIT_FAILURE;
        if(userChoice > 9 || userChoice < 0)
            userChoice = 0;
        switch(userChoice)
        {
//--------------------------------------------------------------------------------------------------------------------
            case 1:
            {
                char cat[256], subj[256], note[256], user[2];
                bool userWantsToAddAnotherItemToSameCategory = false;
                showCategory_SubMenu(); 
                cin.ignore(); cin.getline(cat, 256);

                if(string(cat) == "back" || string(cat) == "Back")
                    goto mainMenu;

                addSubject(); cin.getline(subj, 256);
                
                if(string(subj) == "back" || string(subj) == "Back")
                    goto mainMenu;

                addNote(); cin.getline(note, 256);

                if(string(note) == "back" || string(note) == "Back")
                    goto mainMenu;

                app.insertItem(string(subj), string(cat), string(note));

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

                    if(string(subj) == "back" || string(subj) == "Back")
                        goto mainMenu;

                    addNote(); cin.getline(note, 256);

                    app.insertItem(string(subj), string(cat), string(note));
                    askAddMoreToSameCategory();
                    cin >> user;
                    //std::cout << "response loop [" << ++i << "]: " << user[0] << "\n";
                    userWantsToAddAnotherItemToSameCategory = (user[0] == response[n]) ? false : true;
                }
                break;
            }
//--------------------------------------------------------------------------------------------------------------------
            case 2:
            {
                caseTwoSubMenu:
                char userInputCategory[256], userInputSubject[256];
                int userInputSubMenuChoice = 0;
                app.displayCurrentListsAndSizes();
                showDisplaySpecificSubjectFromCategoryPrompt();
                cin >> userInputSubMenuChoice;
                switch(userInputSubMenuChoice)
                {
                    case 1:
                    {
                        showCategory_SubMenu(); 
                        cin.ignore(); cin.getline(userInputCategory, 256);

                        if(string(userInputCategory) == "back" || string(userInputCategory) == "Back")
                            goto caseTwoSubMenu;

                        addSubject(); cin.getline(userInputSubject, 256);
                        if(string(userInputSubject) == "back" || string(userInputSubject) == "Back")
                            goto caseTwoSubMenu;
                            
                        app.displaySpecificSubjectOnly(string(userInputCategory), string(userInputSubject));
                        break;
                    }
                    case 2:
                    {
                        showCategory_SubMenu();
                        cin.ignore(); 
                        cin.getline(userInputCategory, 256);

                        if(string(userInputCategory) == "back" || string(userInputCategory) == "Back")
                            goto caseTwoSubMenu;

                        app.displaySpecificCategoryList(string(userInputCategory));
                        break;
                    }
                    case 3:
                    {
                        goto mainMenu;
                    }
                    default:
                        cout << "\nThe option you entered is invalid!\n";
                }
                break;
            }
//--------------------------------------------------------------------------------------------------------------------
            case 3:
            {
                app.displayList();
                break;
            }
//--------------------------------------------------------------------------------------------------------------------
            case 4:
            {
                app.displayCurrentListsAndSizes();
                break;
            }
//--------------------------------------------------------------------------------------------------------------------
            case 5:
            {
                char userInputSubject[256], userInputCategory[256];
                app.displayCurrentListsAndSizes();
                showRemoveCategoryPrompt();
                cin.ignore(); 
                cin.getline(userInputCategory, 256);

                if(string(userInputCategory) == "back" || string(userInputCategory) == "Back")
                    goto mainMenu;
                else if(!(app.categoryExists(userInputCategory)))
                {
                    cout << "\nThe category you entered does not exist!\n";
                    goto mainMenu;
                }
                
                app.displaySpecificCategoryList(string(userInputCategory));
                showRemoveItemPrompt(); 
                cin.getline(userInputSubject, 256);

                if(string(userInputCategory) == "back" || string(userInputCategory) == "Back")
                    goto mainMenu;

                app.deleteItem(string(userInputSubject), string(userInputCategory));

                break;
            }
//--------------------------------------------------------------------------------------------------------------------
            case 6:
            {
                char cat[256];
                showRemoveCategoryPrompt(); cin.ignore(); cin.getline(cat, 256);
                if(string(cat) == "back" || string(cat) == "Back")
                    goto mainMenu;
                app.deleteLibNodes(string(cat));
                break;
            }
//--------------------------------------------------------------------------------------------------------------------
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
                    app.emptyEntireList();
                else
                    cout << "The list has not been cleared\n";
                break;
            }
//--------------------------------------------------------------------------------------------------------------------
            case 8:
            {
                string fileName("yourList.txt");
                remove(fileName.c_str());
                int userSubChoice = 0;
                showExportFullListOrSpecificCategoryPrompt(); cin >> userSubChoice;
                switch(userSubChoice)
                {
                    case 1:
                    {
                        char userInputCategory[256];
                        app.displayCurrentListsAndSizes();
                        showCategory_SubMenu();
                        cin.ignore(); 
                        cin.getline(userInputCategory, 256);
                        if(string(userInputCategory) == "back" || string(userInputCategory) == "Back")
                            goto mainMenu;
                        app.displaySpecificCategoryList(userInputCategory,fileName);
                        break;
                    }
                    case 2:
                    {
                        app.displayList(fileName);
                        break;
                    }
                    case 3: 
                    {
                        goto mainMenu;
                    }
                    default:
                        cout << "\nThe option you entered is invalid!\n";
                }
                break;
            }
//--------------------------------------------------------------------------------------------------------------------
            case 9:
            {
                string line;
                ifstream inputFile ("presidents.txt");
                ofstream outputFile("results.txt");
                std::smatch sm;
                std::cmatch cm;
                int i = 0;
                int republicanYears = 0, democratYears = 0;
                std::regex presLine("^([0-9]+). ([A-Za-z]+ ?[A-Z]*\.* [A-Za-z]+ ?[A-Za-z]*),* .*((Democratic-Republican|Democrat|Republican|Whig|Federalist|Union)).*((\t18(41\t*|81\t*))|(18[0-9][0-9].* ?[0-9] )|(17|18|19|20)[0-9]+ ?- ?((17|18|19|20)[0-9]*)*).*");
                std::regex year("(\t[0-9]+|[0-9]+)?-?(.*)");
                if (inputFile.is_open() && outputFile.is_open())
                {
                    while ( getline (inputFile,line) )
                    {
                        std::regex_match (line,sm,presLine);
                        if(i++ == 0)
                            continue;
                        string yearLine = sm[5];
                        std::regex_match (yearLine.c_str(),cm,year);
                        outputFile << sm[1]  << ") Name: " << sm[2] << ", Party: " << sm[3] << ", Years: "<< sm[5] << "\n";
                        string note = "# ";
                        note += sm[1];
                        note += "\nYears: ";
                        note += sm[5];
                        std::string::size_type s_beginTerm;
                        std::string::size_type s_endTerm;
                        string beginTermString = cm.str(1);
                        string endTermString = cm.str(2);
                        if(strcmp(string(sm[2]).c_str(), "Barack Obama") == 0)
                        {
                            string numberOfYearsInOffice = to_string(8);
                            note+= "\nYears in Office: " + numberOfYearsInOffice + "\nTotal Years With A " +  string(sm[3]) + " In Office: ";
                            note+= to_string(democratYears + 8) + "\n";
                        }
                        if(beginTermString != "" && endTermString != "")
                        {
                            try 
                            {
                                int beginTermInt = std::stoi (beginTermString, &s_beginTerm);
                                int endTermInt = std::stoi (endTermString, &s_endTerm);
                                //cout << "\n***\nX: " << x << "\nY: " << y << "\n\n***";
                                if(endTermInt)
                                {
                                    string numberOfYearsInOffice = to_string(endTermInt - beginTermInt);
                                    note+= "\nYears in Office: " + numberOfYearsInOffice + "\nTotal Years With A " +  string(sm[3]) + " In Office: ";
                                    int numberOfYearsInOfficeInt = endTermInt - beginTermInt;
                                    if(strcmp(string(sm[3]).c_str(), "Republican") == 0 || strcmp(string(sm[3]).c_str(), "Whig") == 0
                                        || strcmp(string(sm[3]).c_str(), "Federalist") == 0)
                                    {
                                        republicanYears += numberOfYearsInOfficeInt;
                                        note += to_string(republicanYears) + "\n";
                                    }
                                    else if(strcmp(string(sm[3]).c_str(), "Democrat") == 0 || strcmp(string(sm[3]).c_str(), "Union") == 0)
                                    {
                                        democratYears += numberOfYearsInOfficeInt;
                                        note += to_string(democratYears) + "\n";
                                    }
                                }
                            }
                            catch (const std::invalid_argument& ia) 
                            {
                                //std::cerr << "Invalid argument: " << ia.what() << '\n';
                            }
                        }
                        else
                        {
                            //string numberOfYearsInOffice = (cm.str(1) != "2009") ? to_string(1) : to_string(8);
                            note+= "\nYears in Office: " + to_string(1) + "\nTotal Years With A " +  string(sm[3]) + " In Office: " ;
                            if(strcmp(string(sm[3]).c_str(), "Republican") == 0 || strcmp(string(sm[3]).c_str(), "Whig") == 0
                                || strcmp(string(sm[3]).c_str(), "Federalist") == 0)
                            {
                                republicanYears += 1;
                                note += to_string(republicanYears) + "\n";
                            }
                            else if(strcmp(string(sm[3]).c_str(), "Democrat") == 0 || strcmp(string(sm[3]).c_str(), "Union") == 0)
                            {
                                democratYears += 1;
                                note += to_string(democratYears) + "\n";
                            }
                        }
                        app.insertItem(string(sm[2]), string(sm[3]), note);
                    }
                    inputFile.close();
                    outputFile.close();
                    cout << "\nResults have been written to results.txt file\n";
                }

                else cout << "Unable to open file"; 
                break;
            }
//--------------------------------------------------------------------------------------------------------------------
            case 0:
            {
                useApp = false;
                break;
            }
//--------------------------------------------------------------------------------------------------------------------
            default: 
                cout << "\nPlease enter a valid selection!\n";
        }
    }while(useApp);

    return 0;
}