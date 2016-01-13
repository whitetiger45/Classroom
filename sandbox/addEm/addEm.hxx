#ifndef ADDEM_H
#define ADDEM_H

#include <cassert>
#include <cstdio>
#include <cstring>
#include <cctype>//isalum -> checks if character is alphanumeric
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <string>

using namespace std;

template<typename T>
class myList
{
public:
    typedef list<T> Library;//this is the library node (doubly linked list)
    typedef typename list<T>::iterator LibraryNode;//library node iterator
    typedef list< list<T> > myCompleteList;//this is the library node (doubly linked list)
    typedef typename list< list<T> >::iterator myCompleteListIter;//library node iterator
    typedef list<T> Item;//item node
    typedef typename list<T>::iterator ItemNode;//item node iterator
    typedef list< list<T> > Category;//this is the node that will store the library nodes that contain the item nodes
    typedef typename list< list<T> >::iterator CategoryNode;//this will iterate through the correspondance list


    void insertItem(string subject, string category, string message)
    {
        string newItem = "\nSubject: " + subject + " " + "\n" +
                "Category: " + category + "\n" + message + "\n________________________";//Combine the item into one string
        m_item.push_front(newItem);//put the item into the linked list

        if(categoryExists(category))//check if the category already exists
        {
            m_libIter = searchLibraryNodes(category);//if it exists, get a pointer to the node
            m_libIter = m_library.erase(m_libIter);//use the pointer to move the library node to the front of the list
            m_myCompleteList.push_front(m_item);//add the item to myCompleteList
            m_library.push_front(category);//add the category to the front of the library node
            m_categoryNode.push_front(m_library);//put the item at the front of the list
        }
        else
        {
            m_library.push_front(category);
            m_myCompleteList.push_front(m_item);
            m_categoryNode.push_front(m_library);
        }
    }

    void displayList()//This will display list by listing the library in the order they appear in the Library from the most recent to the oldest, i.e., from beginning of doubly-linked list of librarys, displaying the category and the number of items in the library.
    {
        m_categoryNodeIterator = m_categoryNode.begin();//first iterate through main list
        //http://stackoverflow.lib/questions/12280593/accessing-elements-of-a-list-of-lists-in-c

        m_myCompleteListIterator = m_myCompleteList.begin();

        cout << "\nYour List:\n==========================\n" ;
        for(m_libIter = m_library.begin(); m_libIter != m_library.end(); m_libIter++)
        {
            string cat = *m_libIter;
            unsigned int count = librarySize(cat);
            cout<<"Category: " << *m_libIter << "\n# of items (" << count << ")\n________________________\n";
            for(m_myCompleteListIterToItemIterator = (*m_myCompleteListIterator).begin(); m_myCompleteListIterToItemIterator != (*m_myCompleteListIterator).end(); m_myCompleteListIterToItemIterator++)
            {
                string catCheck = *m_myCompleteListIterToItemIterator;
                string subjectAsString("Subject: ");
                string categoryAsString("Category: \n");
                if(catCheck.find(cat) != string::npos)
                {
                    //std::cout << "\n***************\ndebugging: \n" << *m_myCompleteListIterToItemIterator << "\n";
                    //this is the sanity check for printing the complete list
                    size_t found = catCheck.find(cat);
                    size_t findSubject = catCheck.find("Subject: \n");
                    if(catCheck[found + (cat.length())] == '\n')
                    {
                        //std::cout << catCheck.substr(found, cat.length()) << "\nEnd Debug\n***************\n";
                        //sanity check to make sure items that contain a word that is also the name of a category do not get printed in the wrong list
                        if( catCheck[found-1] == ' ' && !(isalnum(catCheck[found-2])))
                        {
                            //cout<< *m_myCompleteListIterToItemIterator << "\n";//this line prints the entire item, we only want to print the subject and the message
                            std::cout << catCheck.substr(0, (found - categoryAsString.length())) << "\n";
                            std::cout << "Note: " << catCheck.substr(found+cat.length()+1) << "\n";
                        }
                    }
                }
            }
            cout<<"\n==========================\n";
        }
    }

    void displayList(string outputFilename)//Overloaded function
    {
        ofstream outputFile;//(outputFilename);
        m_categoryNodeIterator = m_categoryNode.begin();//first iterate through main list
        //http://stackoverflow.lib/questions/12280593/accessing-elements-of-a-list-of-lists-in-c

        m_myCompleteListIterator = m_myCompleteList.begin();
        outputFile.open(outputFilename, ios::out | ios::trunc );
        if (outputFile.is_open())
        {
            outputFile << "\nYour List:\n==========================\n" ;
            for(m_libIter = m_library.begin(); m_libIter != m_library.end(); m_libIter++)
            {
                string cat = *m_libIter;
                unsigned int count = librarySize(cat);
                outputFile <<"Category: " << *m_libIter << "\n# of items (" << count << ")\n________________________\n";
                for(m_myCompleteListIterToItemIterator = (*m_myCompleteListIterator).begin(); m_myCompleteListIterToItemIterator != (*m_myCompleteListIterator).end(); m_myCompleteListIterToItemIterator++)
                {
                    string catCheck = *m_myCompleteListIterToItemIterator;
                    string subjectAsString("Subject: ");
                    string categoryAsString("Category: \n");
                    if(catCheck.find(cat) != string::npos)
                    {
                        //std::cout << "\n***************\ndebugging: \n" << *m_myCompleteListIterToItemIterator << "\n";
                        //this is the sanity check for printing the complete list
                        size_t found = catCheck.find(cat);
                        size_t findSubject = catCheck.find("Subject: \n");
                        if(catCheck[found + (cat.length())] == '\n')
                        {
                            //std::cout << catCheck.substr(found, cat.length()) << "\nEnd Debug\n***************\n";
                            //sanity check to make sure items that contain a word that is also the name of a category do not get printed in the wrong list
                            if( catCheck[found-1] == ' ' && !(isalnum(catCheck[found-2])))
                            {
                                //cout<< *m_myCompleteListIterToItemIterator << "\n";//this line prints the entire item, we only want to print the subject and the message
                                outputFile << catCheck.substr(0, (found - categoryAsString.length())) << "\n";
                                outputFile << "Note: " << catCheck.substr(found+cat.length()+1) << "\n";
                            }
                        }
                    }
                }
                outputFile <<"\n==========================\n";
            }
            outputFile.close();
            cout << "\nResults have been written to yourList.txt file\n";
        }
        else cout << "\nUnable to open file!\n"; 
    }


    void displayCurrentListsAndSizes()//This will display list by listing the library in the order they appear in the Inbox from the most recent to the oldest, i.e., from beginning of doubly-linked list of librarys, displaying the category and the number of e-mails in the library.
    {
        m_categoryNodeIterator = m_categoryNode.begin();//first iterate through main list
        //http://stackoverflow.lib/questions/12280593/accessing-elements-of-a-list-of-lists-in-c

        m_myCompleteListIterator = m_myCompleteList.begin();
        unsigned int totalListCount = 0;
        cout << "\nYour Lists:\n==========================\n" ;
        for(m_libIter = m_library.begin(); m_libIter != m_library.end(); m_libIter++)
        {
            string cat = *m_libIter;
            unsigned int count = librarySize(cat);
            cout<< ++totalListCount << ") " << *m_libIter << " (" ;
            if(count > 1)
                cout << count << " items)\n";
            else
            cout << count << " item)\n";
        }
    }

    void displaySpecificCategoryList(string category)
    {
        m_categoryNodeIterator = m_categoryNode.begin();//first iterate through main list
        //http://stackoverflow.lib/questions/12280593/accessing-elements-of-a-list-of-lists-in-c

        m_myCompleteListIterator = m_myCompleteList.begin();
        bool categoryPrinted = false;
        
       if(!categoryExists(category))
        {
            if(islower(category[0]))
            {
                category[0] = toupper(category[0]);
                if(!categoryExists(category))
                {
                    cout << "\nCategory you entered does not exist in the library!\n";
                    return;
                }
            }
            else if(isupper(category[0]))
            {
                category[0] = tolower(category[0]);
                if(!categoryExists(category))
                {
                    cout << "\nCategory you entered does not exist in the library!\n";
                    return;
                }
            }
        }
        
        m_libIter = searchLibraryNodes(category);
        if(*m_libIter != category)
            return;

        unsigned int count = librarySize(category);
        cout << "\nYour Lists:\n==========================\n" ;
        cout<<"Category: " << *m_libIter << "\n# of items (" << count << ")\n________________________\n";
        for(m_myCompleteListIterToItemIterator = (*m_myCompleteListIterator).begin(); m_myCompleteListIterToItemIterator != (*m_myCompleteListIterator).end(); m_myCompleteListIterToItemIterator++)
        {
            string catCheck = *m_myCompleteListIterToItemIterator;
            string subjectAsString("Subject: ");
            string categoryAsString("Category: \n");
            if(catCheck.find(category) != string::npos)
            {
                //std::cout << "\n***************\ndebugging: \n" << *m_myCompleteListIterToItemIterator << "\n";
                //this is the sanity check for printing the complete list
                size_t found = catCheck.find(category);
                size_t findSubject = catCheck.find("Subject: \n");
                if(catCheck[found + (category.length())] == '\n')
                {
                    //std::cout << catCheck.substr(found, cat.length()) << "\nEnd Debug\n***************\n";
                    //sanity check to make sure items that contain a word that is also the name of a category do not get printed in the wrong list
                    if( catCheck[found-1] == ' ' && !(isalnum(catCheck[found-2])))
                    {
                        //cout<< *m_myCompleteListIterToItemIterator << "\n";//this line prints the entire item, we only want to print the subject and the message
                        std::cout << catCheck.substr(0, (found - categoryAsString.length())) << "\n";
                        std::cout << "Note: " << catCheck.substr(found+category.length()+1) << "\n";
                    }
                }
            }
        }
        cout<<"\n==========================\n";
    }

    void displaySpecificSubjectOnly(string category, string iSubject)
    {
        m_categoryNodeIterator = m_categoryNode.begin();//first iterate through main list
        //http://stackoverflow.lib/questions/12280593/accessing-elements-of-a-list-of-lists-in-c

        m_myCompleteListIterator = m_myCompleteList.begin();
        bool categoryPrinted = false;
        
        if(!categoryExists(category))
        {
            cout << "\nCategory you entered does not exist in the library!\n";
            return;
        }

        m_libIter = searchLibraryNodes(category);
        if(*m_libIter != category)
            return;

        unsigned int count = librarySize(category);
        cout << "\nYour Item:\n==========================\n" ;
        cout<<"\n________________________\n";
        for(m_myCompleteListIterToItemIterator = (*m_myCompleteListIterator).begin(); m_myCompleteListIterToItemIterator != (*m_myCompleteListIterator).end(); m_myCompleteListIterToItemIterator++)
        {
            string catCheck = *m_myCompleteListIterToItemIterator;
            string subjectAsString("Subject: ");
            string categoryAsString("Category: \n");
            if(catCheck.find(category) != string::npos)
            {
                //std::cout << "\n***************\ndebugging: \n" << *m_myCompleteListIterToItemIterator << "\n";
                //this is the sanity check for printing the complete list
                size_t found = catCheck.find(category);
                size_t findSubject = catCheck.find(iSubject);
                if(findSubject != string::npos)
                {
                    if(catCheck[found + (category.length())] == '\n')
                    {
                        //std::cout << catCheck.substr(found, cat.length()) << "\nEnd Debug\n***************\n";
                        //sanity check to make sure items that contain a word that is also the name of a category do not get printed in the wrong list
                        if( catCheck[found-1] == ' ' && !(isalnum(catCheck[found-2])))
                        {
                            //cout<< *m_myCompleteListIterToItemIterator << "\n";//this line prints the entire item, we only want to print the subject and the message
                            std::cout << catCheck.substr(0, (found - categoryAsString.length())) << "\n";
                            std::cout << "Note: " << catCheck.substr(found+category.length()+1) << "\n";
                        }
                    }
                }
            }
        }
        cout<<"\n==========================\n";
    }

    void displaySpecificCategoryList(string category, string outputFilename)//overloaded function
    {
        ofstream outputFile(outputFilename);
        m_categoryNodeIterator = m_categoryNode.begin();//first iterate through main list
        //http://stackoverflow.lib/questions/12280593/accessing-elements-of-a-list-of-lists-in-c

        m_myCompleteListIterator = m_myCompleteList.begin();
        bool categoryPrinted = false;
        
        if(!categoryExists(category))
        {
            cout << "\nCategory you entered does not exist in the library!\n";
            return;
        }

        m_libIter = searchLibraryNodes(category);
        if(*m_libIter != category)
            return;

        unsigned int count = librarySize(category);
        if (outputFile.is_open())
        {
            outputFile << "\nYour Lists:\n==========================\n" ;
            outputFile <<"Category: " << *m_libIter << "\n# of items (" << count << ")\n________________________\n";
            for(m_myCompleteListIterToItemIterator = (*m_myCompleteListIterator).begin(); m_myCompleteListIterToItemIterator != (*m_myCompleteListIterator).end(); m_myCompleteListIterToItemIterator++)
            {
                string catCheck = *m_myCompleteListIterToItemIterator;
                string subjectAsString("Subject: ");
                string categoryAsString("Category: \n");
                if(catCheck.find(category) != string::npos)
                {
                    //std::cout << "\n***************\ndebugging: \n" << *m_myCompleteListIterToItemIterator << "\n";
                    //this is the sanity check for printing the complete list
                    size_t found = catCheck.find(category);
                    size_t findSubject = catCheck.find("Subject: \n");
                    if(catCheck[found + (category.length())] == '\n')
                    {
                        //std::cout << catCheck.substr(found, cat.length()) << "\nEnd Debug\n***************\n";
                        //sanity check to make sure items that contain a word that is also the name of a category do not get printed in the wrong list
                        if( catCheck[found-1] == ' ' && !(isalnum(catCheck[found-2])))
                        {
                            //cout<< *m_myCompleteListIterToItemIterator << "\n";//this line prints the entire item, we only want to print the subject and the message
                            outputFile << catCheck.substr(0, (found - categoryAsString.length())) << "\n";
                            outputFile << "Note: " << catCheck.substr(found+category.length()+1) << "\n";
                        }
                    }
                }
            }
            outputFile <<"\n==========================\n";
            outputFile.close();
            cout << "\nResults have been written to yourList.txt file\n";
        }
        else cout << "\nUnable to open file!\n"; 

    }

    bool categoryExists(string category)
    {//a bool method for checking if a category already has been created
        for(m_libIter = m_library.begin(); m_libIter != m_library.end(); m_libIter++)
            if(*m_libIter == category)
            {
                return true;
            }
        return false;
    }

    unsigned int librarySize(string category)
    {//get the number of items that relate to a specific category
        unsigned int count = 0;

        m_myCompleteListIterator = m_myCompleteList.begin();


        for(m_myCompleteListIterToItemIterator = (*m_myCompleteListIterator).begin(); m_myCompleteListIterToItemIterator != (*m_myCompleteListIterator).end(); m_myCompleteListIterToItemIterator++)
        {
            string catCheck = *m_myCompleteListIterToItemIterator;
            if(catCheck.find(category) != string::npos)
            {
               //this is the sanity check for making sure we have the correct count
                size_t found = catCheck.find(category);
                if(catCheck[found + (category.length())] == '\n')
                    //sanity check to make sure items that contain a word that is also the name of a category do not update the count incorrectly
                    if( catCheck[found-1] == ' ' && !(isalnum(catCheck[found-2])))
                        count++;
            }
        }
        return count;
    }

    void deleteLibNodes(string category)
    {
//first remove from the wrapper which contains the librarys that store the item nodes
        m_myCompleteListIterator = m_myCompleteList.begin();
        for(m_myCompleteListIterToItemIterator = (*m_myCompleteListIterator).begin(); m_myCompleteListIterToItemIterator != (*m_myCompleteListIterator).end(); m_myCompleteListIterToItemIterator++)
        {
            string catCheck = *m_myCompleteListIterToItemIterator;
            if(catCheck.find(category) != string::npos)
                m_myCompleteListIterToItemIterator =  (*m_myCompleteListIterator).erase(m_myCompleteListIterToItemIterator);
        }
//now to remove from the library from the doubly linked list library node
        for(m_libIter = m_library.begin(); m_libIter != m_library.end(); m_libIter++)
        {
            string cat = *m_libIter;
            LibraryNode temp = searchLibraryNodes(cat);//get a pointer with the search librarys node pointer
            if(cat.find(category) != string::npos)
                m_libIter =  m_library.erase(temp);//this one uses the searchLibrarysNodes method
        }

//now to remove the item from doubly linked list item node
        for(m_itemIter = m_item.begin(); m_itemIter != m_item.end(); m_itemIter++)
        {
            string cat = *m_itemIter;
            if(cat.find(category) != string::npos)
                m_itemIter =  m_item.erase(m_itemIter);
        }
    }

    void deleteItem(string subject, string category)
    {
        //todo ** add check to make sure category exists
        if(librarySize(category) == 1)
        {
            deleteLibNodes(category);
            return;
        }
//first remove from the wrapper which contains the librarys that store the item nodes
        m_myCompleteListIterator = m_myCompleteList.begin();
        for(m_myCompleteListIterToItemIterator = (*m_myCompleteListIterator).begin(); m_myCompleteListIterToItemIterator != (*m_myCompleteListIterator).end(); m_myCompleteListIterToItemIterator++)
        {
            string subjCheck = *m_myCompleteListIterToItemIterator;
            if(subjCheck.find(subject) != string::npos)
                m_myCompleteListIterToItemIterator =  (*m_myCompleteListIterator).erase(m_myCompleteListIterToItemIterator);
        }
//now to remove from the library from the doubly linked list library node
        for(m_libIter = m_library.begin(); m_libIter != m_library.end(); m_libIter++)
        {
            string subj = *m_libIter;
            LibraryNode temp = searchLibraryNodes(subj);//get a pointer with the search librarys node pointer
            if(subj.find(subject) != string::npos)
                m_libIter =  m_library.erase(temp);//this one uses the searchLibrarysNodes method
        }

//to remove a single item from doubly linked list item node
        for(m_itemIter = m_item.begin(); m_itemIter != m_item.end(); m_itemIter++)
        {
            string subj = *m_itemIter;
            //std::cout << "\n***************\ndebugging: \nIter: " << *m_itemIter << "\nSubj for removing: " << subject;
            if(strcmp(subject.c_str(), subj.c_str()) == 0)
                m_itemIter =  m_item.erase(m_itemIter);
        }
    }

    void emptyEntireList()
    {
        m_myCompleteList.clear();
        m_library.clear();
        m_item.clear();
    }

    Library m_library;//this is the library node for the complete list
    LibraryNode m_libIter;//this is the main library node iterator
    myCompleteList m_myCompleteList;
    myCompleteListIter m_myCompleteListIterator;
    ItemNode m_myCompleteListIterToItemIterator;
    Item m_item;//this is the item node for the complete list
    ItemNode m_itemIter;//this is the item node iterator
    Category m_categoryNode;//this contains the library nodes that contain the items
    CategoryNode m_categoryNodeIterator;//this is the category node iterator
    LibraryNode m_categoryIterToLibraryIter;//this is used to dereference nodes of the category node since they are nodes within nodes

private:

    LibraryNode searchLibraryNodes(string category)//Searches the library for category using given string as the key for the search. It returns a pointer to the library node that matches the category, or the null pointer if no such node is found.   This function should be private, and will be needed for both insertions and deletion.
    {
        for(m_libIter = m_library.begin(); m_libIter != m_library.end(); m_libIter++)
            if(*m_libIter == category)
                return m_libIter;

        return LibraryNode(NULL);
    }

    ItemNode searchItemNodes(string category)//Searches the Items for an item with category as the key for the search. It returns a pointer to the library node that matches the category, or the null pointer if no such node is found.   This function should be private, and will be needed for both insertions and deletion.
    {
        ItemNode pointer(NULL);
        for(m_itemIter = m_item.begin(); m_itemIter != m_item.end(); m_itemIter++)
        {
            string cat = *m_itemIter;
            if(cat.find(category) != string::npos)
            {
                pointer = m_itemIter;
                return pointer;
            }
        }
        return pointer;
    }

    ItemNode searchMyCompleteListNodes(string category)
    {
        m_myCompleteListIterator = m_myCompleteList.begin();
        ItemNode pointer;
        for(m_myCompleteListIterToItemIterator = (*m_myCompleteListIterator).begin(); m_myCompleteListIterToItemIterator != (*m_myCompleteListIterator).end(); m_myCompleteListIterToItemIterator++)
        {
            string catCheck = *m_myCompleteListIterToItemIterator;
            if(catCheck.find(category) != string::npos)
                pointer = m_myCompleteListIterToItemIterator;
        }
        return pointer;
    }
};

#endif // ADDEM_H