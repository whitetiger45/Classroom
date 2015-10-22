/*    @file MadLibSimple.cpp    
      @author <Bryan Kanu>
      @date <10/21/14  

			@description This program prints out a simple mad lib hard-coded
			into this file.
*/

#include <iostream>
#include <cstdlib>

#include "expression.h"

using namespace std;

int main(){
  // Randomize number generator
  srand(time(0));
  // Example hard-coded grammar instance.
  Terminal* p1 = new Terminal("Bob");
  Terminal* p2 = new Terminal("Amy");
  
  Choice* person = new Choice();
  person->addExpression(p1);
  person->addExpression(p2);
  
  Terminal* v1 = new Terminal("ran");
  Terminal* v2 = new Terminal("walked");
  Terminal* v3 = new Terminal("crawled");
  
  Choice* action = new Choice();
  action->addExpression(v1);
  action->addExpression(v2);
  action->addExpression(v3);
    
  Terminal* w1 = new Terminal("through");
  Terminal* w2 = new Terminal("the");
  Terminal* w3 = new Terminal("crowd.");
  
  Sequence* s1 = new Sequence();
  s1->addExpression(person);
  s1->addExpression(action);
  s1->addExpression(w1);
  s1->addExpression(w2);
  s1->addExpression(w3);

  cout << s1->getString() << endl;
  cout << s1->getString() << endl;  

  // Return everything!
  delete s1;
}
