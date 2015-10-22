#include <iostream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <map>
#include <string>

using namespace std;

// Fill in all classes here!  Implement here as well.

class Exp{

public: 

Exp(){};

virtual string getString() = 0;

};
/*
------------------------------------------------------
*/
class Terminal : public Exp{

public:	

Terminal(string word){

	this->word = word;
};	

virtual string getString(){
	
	return word;
}

protected: 
	
	string word;

};

/*
---------------------------------------------------------------
*/

class Sequence : public Exp{

public: 

virtual string getString(){
	
	stringstream ss;
	for(unsigned int i = 0; i < expression_storage_sequence.size(); i++){
		ss << expression_storage_sequence[i]->getString() << " ";
	}

	return ss.str();
}

void addExpression(Exp* thing){

	//Exp* some_thing= thing;

	expression_storage_sequence.push_back(thing);

}

protected:

vector<Exp*> expression_storage_sequence;


};

/*
---------------------------------------------------------------
*/

class Choice : public Exp{

public:

virtual string getString(){
	
	stringstream cs;

	int i = rand() % expression_storage_choice.size();
	//cout<<"vector length inside choice: " << expression_storage_choice.size() << endl;
	//for(int i = 0; i < expression_storage_choice.size(); i++)
		//cout<<"expression: " << i << " : " << expression_storage_choice[i]->getString() << endl;

	cs << expression_storage_choice[i]->getString();
	

	return cs.str();
}

void addExpression(Exp* thing){

	//Exp* some_choice= thing;

	expression_storage_choice.push_back(thing);

}

protected:

vector<Exp*> expression_storage_choice;	


};



/*
-------------------------------------------------------------------
*/

class Keyword : public Exp{

public: 

Keyword(map<string, Exp*>* mp, string keyword){
	the_map_pointer = mp;
	key_word = keyword;
}

Keyword(multimap<string, Exp*>* mp, string keyword){
	the_map_pointer2 = mp;
	key_word = keyword;
}


virtual string getString(){
	
	map<string, Exp*>::iterator it;
	it = the_map_pointer->find(key_word);

	bool found = true;
	string not_found;
	not_found = ":(";
	
	if(it == the_map_pointer->end()){
		found = false;
		return not_found;
	}

	else if(found)
		return (*the_map_pointer)[key_word]->getString();
}

protected:
	string key_word;
	map<string, Exp*>* the_map_pointer;
	multimap<string, Exp*>* the_map_pointer2;
};