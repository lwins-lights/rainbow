#include <iostream>
#include <random>
#include <limits>
#include "lib/md5.h"
 
using namespace std;

typedef unsigned long long uint64;

const int p = 10007; // some prime

int n; // length of plaintext
int m; // size of alphabet
int l; // length of each chain
int num; // number of chains generated

uint64 N; // = m^n; size of the space of possible plaintext

vector < char > alphabet;

//unordered_map < string, string > rev; // given the end of a chain, return its start

string uint_to_plaintext(uint64 t) {
	string ret;
	bool init_zero;

	t %= N;
	ret = "";
	init_zero = true;
	for (int i = 0; i < n; i++) {
		if (t % m != 0 || !init_zero) { // initial 0's is mapped to "". this way we can generate plaintext of length < n.
			ret = ret + (char)(alphabet[t % m]);
			init_zero = false;
		}
		t /= m;
	}
	return ret;
}

string reduce(string h, int k) {
	uint64 t;
	string str;
	string ret;

	str = md5(h + to_string(k));
	//cout << h + to_string(k);
	//return "";
	t = 0;
	for (uint i = 0; i < str.length(); i++)
		t = t * p + (uint)(str[i]);
	return uint_to_plaintext(t);
}
 
int main(int argc, char *argv[])
{
    cout << "md5 of 'grape': " << md5("grape") << endl;

 	std::random_device rd;     //Get a random seed from the OS entropy device, or whatever
 	std::mt19937_64 eng(rd()); //Use the 64-bit Mersenne Twister 19937 generator and seed it with entropy.	

 	//Define the distribution, by default it goes from 0 to MAX(unsigned long long)
 	//or what have you.
 	std::uniform_int_distribution<unsigned long long> distr;	
 	//Generate random numbers
 	for(int n=0; n<40; n++)
   	std::cout << distr(eng) << ' ';
	std::cout << std::endl;

	n = 4; l = 2; m = 7;
	/* compute N = m^n */
 	N = 1;
 	for (int i = 0; i < n; i++)
 		N *= m;
 	
	cout << reduce("f0deb8685672bd383725eaf48bc13e10", 2);
    return 0;
}
