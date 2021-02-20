/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Byung Jeon
 * Date        : September 23, 2020
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
	size_t count=0;
	for (size_t i=0; i<s.length(); i++){;
		if((s[i]==tolower(s[i])) && (isalpha(s[i]))){
			count++;
		}
	}
	if (count==s.length()){
		return true;
	}
	else{ return false;
	}
}


bool all_unique_letters(const string &s){
	unsigned int mystr=0;
	unsigned int setter=0;
	size_t i=0;
	while(i < s.length()){
		setter = 1 <<(s[i]-'a');
		if((mystr & setter) == 0){
			mystr = mystr|setter;
			setter=0;
			i++;
		}
		else{
			return false;
		}
	}
	return true;
}

int main(int argc, char * const argv[]) {
    if (argc !=2){
    	cerr << "Usage: "<<argv[0]<<" <string>"<<endl;
    	return 1;
    }
    if(!is_all_lowercase(argv[1])){
		cerr <<"Error: String must contain only lowercase letters."<<endl;
		return 1;
	}
    if(!all_unique_letters(argv[1])){
		cout <<"Duplicate letters found."<<endl;
		return 0;
	}
    if(all_unique_letters(argv[1])){
		cout <<"All letters are unique."<<endl;
		return 0;
	}
}


