#include <algorithm> 
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv){

	if(argc != 2){
		cout << "Usage: " << argv[0] << " <key>\n";
		exit(1);
	}
	
	string str = argv[1];

	do{
		cout << "key: " << str << endl;
	}while(next_permutation(str.begin(),str.end()));

	return 0;
}
