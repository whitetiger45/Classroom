/*    @file MadLib.cpp    
      @author <Bryan Kanu>
      @date <10/21/14>  

      @description This program accepts a grammar instance text file and 
      prints out a random instance from that grammar.
*/

#include <iostream>
#include <cstdlib>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <fstream>  
#include <cstring> 
#include <sstream>
#include <iterator>
#include <algorithm>      

#include "expression.h"

using namespace std;

Exp* parse(map<string, Exp*>* keywords, string input){
// Fill me in! figure out what type of expr it is in parse, do recursively
    string line_inside_parse = input;
    string new_line_after_parse_extraction;
    string expression;
    string terminal_in_sequence_as_string;
    string key_word_inside_parse_as_string;

   // cout<<"line_inside_parse before parsing: "<< line_inside_parse << endl;
    //cout<< "line size before find and loop: " << input.size() << endl;

    int count = 0;
    //Exp* Parsed_Text;

   
    ///this if is where we start looking for choices   
      size_t pos = line_inside_parse.find('|');
      if(line_inside_parse.find('|') != string::npos){

                Choice* ret = new Choice();
                expression = line_inside_parse.substr(0, pos);
                //cout<<"expression after extraction: "<< expression << endl;
                line_inside_parse = line_inside_parse.substr(pos + 1);

                ret->addExpression(parse(keywords, expression));

                if(line_inside_parse.size() == 0)
                      return ret;
                pos = line_inside_parse.find('|'); 
              while(pos != string::npos){
                      //cout<<"\n**inside while inside**" << endl;
                      pos = line_inside_parse.find('|'); 
                      //cout<<"rest of line after extraction: "<< line_inside_parse << endl;
                      expression = line_inside_parse.substr(0, pos);
                      //cout<<"\nexpression ["<<count<<"] : " << expression << endl;
                      pos = line_inside_parse.find('|');
                      count++;
                      //if(line_inside_parse.find('>') < pos)
                        //  expression = line_inside_parse.substr(0, string::npos);

                      if(pos != string::npos){
                          line_inside_parse = line_inside_parse.substr(pos + 1);
                          //cout<<"rest of line after extraction: "<< line_inside_parse << endl;
                      }    
                      else{
                        expression = line_inside_parse.substr(0, string::npos);
                        //cout<<"expression inside | search: " << expression << endl;
                        ret->addExpression(parse(keywords, expression));
                        //cout<<"rest of line after extraction: "<< line_inside_parse << endl;
                        return ret;
                      }  
                      //Parsed_Text = ret;
                      ret->addExpression(parse(keywords, expression));
                       
                }


        } 

    ///this else if is where we start looking for sequences 



    else if(line_inside_parse.find(' ') != string::npos){
     
              pos = line_inside_parse.find(' ');
              //if(pos != string::npos){
              //cout<<"\nim inside sequence: " << line_inside_parse << endl;
              Sequence* ret = new Sequence();
              int count= 0;
                //size_t pos2 = line_inside_parse.find('|');
                    while(pos != string::npos){
                         

                          expression = line_inside_parse.substr(0, pos);
                          //expression2 = line_inside_parse.substr(0, pos2);
                          line_inside_parse= line_inside_parse.substr(pos + 1);

                          //cout<<"expression after extraction inside sequence: "<< expression << endl;
                          

                          //cout<<"line after extraction: "<< line_inside_parse << endl;

                          
                          count++;
                          //cout<<"count: " << count << endl;
                          pos = line_inside_parse.find(' ');
                         
                          ret->addExpression(parse(keywords, expression));


                        //  ret->addExpression(parse(keywords, expression));
                    }
                    if(pos == string::npos){
                          //expression = line_inside_parse.substr(0, string::npos);
                         // cout<<"line_inside_parse before ret: " << line_inside_parse << endl;
                          ret->addExpression(parse(keywords, line_inside_parse));
                          return ret;
                    }
                    return ret;
              }

//////////This else if is where we look for keywords
      else if(line_inside_parse.find('<') != string::npos){
          //cout<<"\n\nline inside keyword before extraction: " << line_inside_parse << endl;
              string found_keyword=  line_inside_parse.substr(1, line_inside_parse.size()-1);
              
              //cout<<"\ni'm inside keyword!\n" << endl;
              pos = line_inside_parse.find('<');
              found_keyword.erase(found_keyword.size()-1, 1);




              Keyword* ret = new Keyword(keywords, found_keyword);

              //cout<<"\nline after keyword extracted down at end before return: "<< found_keyword << endl;
              //ret2->addExpression(parse(keywords, line_inside_parse));


              return ret;
          }

 ///if the input gets down here it must be a terminal
 
          else{

                expression = line_inside_parse;
                //cout<<"expression at end of loop so must be terminal: " << expression << endl;
                Terminal* ret = new Terminal(expression);
            
            return ret;

          }


  }

int main(int argc, char* argv[]){
//code example used was that shown  in the example solutions produced by Viveka Aggarwal
//https://github.uc.edu/CS2-Fall2014/ExamplesSolutions/blob/master/Solutions/02/printstats_HW2.cpp
//http://cs.dvc.edu/HowTo_Cparse.html
    int input = 0;
    char* input_file_name;
    //bool invalid_input = true;

    while(input != -1){
         if (argc != 2){
                  cout<<"\nYou must include a text document filename on the command text_file_line!\n";
                  cout<<"Format: <text document>.txt\n" << endl;
                  exit(EXIT_SUCCESS);
              }

        input_file_name = *(argv + 1);
        break;

             
    }
   // cout<< "\nfile name: " << input_file_name << "\n" << endl;    
    /*
    open file and get length of file
    */
    ifstream file;
    file.open(input_file_name);
    file.seekg(0, file.end);
    int length = file.tellg();
    file.seekg(0, file.beg);

    
    string text_file_line;
    string text_file_expression;
    string text_file_expressions_after_extraction;
    vector<string> stored_lines_vector;
    vector<string> stored_keywords_vector;
    string keyword_in_text;
    int loop_count = 0;

    map<string, Exp*> keyword_map;
    map<string, Exp*>::iterator it= keyword_map.begin();

    //http://www.cplusplus.com/forum/beginner/70805/
    //http://stackoverflow.com/questions/16074980/parse-a-file-in-c-and-ignore-some-characters
    //Sequence* test_this = new Sequence();

    if(file.is_open()){
        
        while(file.good()){
              
              getline(file, text_file_line);
              size_t pos= text_file_line.find(':');
              //int count = 0;

        
            if(pos != string::npos){
                  keyword_in_text = text_file_line.substr(0, pos);
                  stored_keywords_vector.push_back(keyword_in_text);//keywords vector
                  //cout<<"keyword: " << keyword_in_text << endl;
                  stored_lines_vector.push_back(text_file_line.substr(pos + 1));//lines vector after colon extracted

                  keyword_map[keyword_in_text] = parse(&keyword_map, stored_lines_vector[loop_count]);
                  //cout<< endl;

            }

            loop_count++;
            
        }
        file.close();

    }
      //cout<< "this map contains: " << endl;

//this is my iterator for the keyword map

    for(it = keyword_map.begin(); it != keyword_map.end(); ++it){
                            
        //cout<<"[keyword] " << it->first << " => " << (it->second)->getString() << endl;

                
    }
    //cout<< endl;


    if(length <= 0){
        cout<<"Invalid text document!\nFormat: <text document>.txt\n";
        exit(EXIT_SUCCESS);   
    }
    //cout<<"length of text: " << length << endl;

  // Randomize number generator
  srand(time(0));

  // Open file

  // Create map of keywords to expressions

  map<string, Exp*> m;
  
  Choice* action = new Choice();
  Exp* k1 = new Keyword(&m, "house");
  Terminal* v1 = new Terminal("ran");
  Terminal* v2 = new Terminal("walked");
  Terminal* v3 = new Terminal("crawled");
  

  action->addExpression(v1);
  action->addExpression(v2);
  action->addExpression(v3);
  action->addExpression(k1);
  //m["house"] = action;
  //cout<< "m: " << m["house"]->getString() << endl;

  
  // For every text_file_line in the file, send the right side to parse
  // and put the resuling Expression pointer into the map.
    //m[--keyword--] = parse(&m, --right side of text_file_line--);
  
  // Get start expression and print out sentence!

  Exp* s1 = keyword_map["start"];

  cout << s1->getString() << endl; 

  // Return all memory back to OS.
}