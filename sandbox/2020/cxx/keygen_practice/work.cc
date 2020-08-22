// g++ -o work -std=c++17 work.cc
#include <ctime>
#include <iostream>

using namespace std;

int main(){
	
	srand(time(NULL));
	int goal{52650};//0xcdaa
	int key_length{9}, current{0}, i{0};
	string key;

	while(i <= key_length){
		int c = rand() % (93) + (33);
		key += (char)c;
		current += c * key_length * key_length;
		if(current >= goal) break;
		i++;
	}

	if(current == goal)
		cout << "try: " << key;

	return 0;
}
// https://stackoverflow.com/questions/229551/how-to-check-if-a-string-contains-a-substring-in-bash
// while(true); do round="$(./work)"; if [[ $round =~ "try" ]]; then key="$(echo $round | awk '{print $2}')"; status="$(./license $key)"; if [[ $status =~ "Good" ]]; then ./perm $key >> keys; echo -e "good key $key and its permutations written to file." ; break; fi; fi; sleep 1 ; done
