#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include "lib/md5.h"
 
using namespace std;

typedef unsigned long long uint64;

const int p = 10007; // some prime
const int timegap = 10000; // report the progress per [timegap] computations

int n; // length of plaintext
int m; // size of alphabet
int l; // length of each chain
int num; // number of chains generated

uint64 N; // = m^n; size of the space of possible plaintext

vector < char > alphabet;

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
	if (ret.length() == 0)
		ret = "?"; // special rule: no empty string allowed
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

/*************************************************************************
 ** Usage: ./gen_table [n] [l] [num] [alphabet] [file name]             **
 *************************************************************************/
 
int main(int argc, char *argv[]) {

	string st, ed, foutn, ab;
	FILE *fp;

	/* args */
	//cout << argc << endl;
	n = atoi(argv[1]);
	ab = argv[4];
	m = ab.length() + 1;
	alphabet.push_back('?');
	for (uint i = 0; i < ab.length(); i++)
		alphabet.push_back(ab[i]);
	l = atoi(argv[2]);
	num = atoi(argv[3]);
	foutn = argv[5];
	//cout << argv[3];

	/* Initialization for random() := distr(eng) */

	std::random_device rd;     // Get a random seed from the OS entropy device, or whatever
 	std::mt19937_64 eng(rd()); // Use the 64-bit Mersenne Twister 19937 generator and seed it with entropy.
 	std::uniform_int_distribution<unsigned long long> distr(0,0xFFFFFFFFFFFFFFFF); // Define the distribution.	
    //reduce("hello",2);

 	/* compute N = m^n */
 	N = 1;
 	for (int i = 0; i < n; i++)
 		N *= m;
 	/*
 	for (int i = 1; i < 100; i++)
 		cout << reduce("hello", i) << " " << distr(eng) << endl;
 	cout << "---------------------------\n";
 	*/

 	fp = fopen(foutn.c_str(), "w");
 	for (int j = 1; j <= num; j++) {
 		ed = st = uint_to_plaintext(distr(eng));
 		//cout << st;
 		for (int i = 1; i <= l; i++) {
 			ed = reduce(md5(ed), i);
 			//cout << " |-> " << ed;
 		}
 		//cout << endl;
 		fprintf(fp, "%s\n%s\n", st.c_str(), ed.c_str());
 		if (j % (timegap / l + 1) == 0) {
           printf("\rProgress: %.2lf%%               ", (double)(j)*100/num);
           fflush(stdout);
 		}
 	}
 	printf("\n");
 	fclose(fp);

    return 0;
}
