/*
	Problem Requirements: 
		- Generate a valid key of size 7 < k < 11
		- Sum of individual ordinal values used in proposed key must be > 1000
*/
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#define MAX_SIZE 10
#define TARGET 1000

using namespace std;

int main() {
    int x = 0;
    string y = "123456";
    int z = 0;
   /* for(char c : y)
        x += c;
     cout << "x: " << x << endl; */

    string key = "";
    // key += (char)63;
    // key += (char)72;
    int sum = 0, i = 0, t = TARGET, r = 0, badKeys = 0, off = 0;
    srand(time(NULL));
    do{
    	r = (100 - r < 0) ? rand() % (93) + (33) : rand() % (93-off) + (33 + off);
    	key += (char)(r);
        sum += key[i++];
        t -= key[i-1];
        off = 100 - r;
        // cout << "\n** Debug ** [vals: {r: " << r << ", off: "<< (100 - r) << ", t: "<< t <<"}]\n";
		
		if(i == MAX_SIZE && sum < TARGET)
		{
			cout << "Bad key generated: "<< key << "\nInvalid sum: " << sum << "\nRegenerating...";
			cout << "\n---------------------------\n";
			key = key[i-1];
			sum = key[i-1];
			t = TARGET - key[i-1];
			i = 1;
			badKeys++;
		}

    }while(i < MAX_SIZE+1 && sum < TARGET);

    cout << "Valid key: " << key << "\nlength: " << key.length();
    cout << "\nValid sum: " << sum << "\npoints remaining (target-sum): " << t;
    cout << "\nNumber of invalid keys generated before valid key found: " << badKeys << endl;

    return 0;
}
