#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <cstdio>
#include <unordered_map>
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

unordered_map < string, string > rev; // given the end of a chain, return its start

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

/*************************************************************************
 ** Usage: ./crack [n] [l] [alphabet] [table name] [hash file name]      *
 **                [plaintext file name]                                 *
 *************************************************************************/
 
int main(int argc, char *argv[]) {

	string ftabn, fptn, fhashn, ab;
	ifstream ftabs, fhashs;
	ofstream fpts;
	//FILE *ftabp, *fptp, *fhashp;
	string st, ed, h, tmp;
	int j;
	bool found;

	/* args */
	//cout << argc << endl;
	n = atoi(argv[1]);
	ab = argv[3];
	m = ab.length() + 1;
	alphabet.push_back('?');
	for (uint i = 0; i < ab.length(); i++)
		alphabet.push_back(ab[i]);
	l = atoi(argv[2]);
	num = atoi(argv[3]);
	ftabn = argv[4];
	fhashn = argv[5];
	fptn = argv[6];
	//cout << argv[3];
if (j % (timegap / l + 1) == 0) {
           printf("\rProgress: %.2lf%%", (double)(j)*100/num);
           fflush(stdout);
 		}
 	/* compute N = m^n */
 	N = 1;
 	for (int i = 0; i < n; i++)
 		N *= m;

 	/* load the table */
 	ftabs.open(ftabn);
 	while (getline(ftabs, st) && st.length() > 0) {
        getline(ftabs, ed);
        rev[ed] = st;
    }
    ftabs.close();
    /*
    unordered_map < string, string >::iterator iter;
    iter = rev.begin();
    while(iter != rev.end()) {
        cout << iter->first << " : " << iter->second << endl;
        iter++;
    }
    */
 	
 	/* main */
 	fhashs.open(fhashn);
 	fpts.open(fptn);
 	j = 0;
 	while (getline(fhashs, h)) {
 		j++;
 		found = false;
 		//cout << "Handling " << h << endl;
 		for (int k = 1; k <= l; k++) { // guess the position of h in a supposed chain
 			tmp = h;
 			for (int i = l - k + 1; i < l; i++) {
 				tmp = md5(reduce(tmp, i));
 				//cout << "tmp = " << tmp << endl;
 			}
 			tmp = reduce(tmp, l);
 			//cout << "tmp = " << tmp << endl;
 			if (rev.count(tmp) != 0) { // succeed in finding a matching chain
 				tmp = rev[tmp];
 				for (int i = 1; i <= l - k; i++) {
 					tmp = reduce(md5(tmp), i);
 				}
 				if (md5(tmp) == h) { // collision found
 					fpts << tmp << endl;
 					found = true;
 					break;
 				}
 			}
 		}
 		if (!found)
 			fpts << "*** NOT FOUND ***\n";
 		if (j % (timegap / l / l + 1) == 0) {
           printf("\rProgress: %d hashes processed", j);
           fflush(stdout);
 		}
 	}
 	printf("\n");
 	fhashs.close();
 	fpts.close();

 	//cout << md5("babf") << endl;
 	//cout << md5("daca") << endl;
 	//cout << reduce("f0deb8685672bd383725eaf48bc13e10", 2) << endl;

    return 0;
}
