#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <string>
#include <cstring>
#include <cstdio>
using namespace std;

int counterRad = 0;
string checking(string s) { // sprawdzenie poprawnosci podanego ciagu oraz zamiana na lowcase
	for (unsigned int i = 0; i < s.size(); i++) {
		if (isdigit(s[i]))
			throw invalid_argument("Podany ciag jest niepoprawny");
		s[i] = tolower(s[i]);
	}
	return s;
}

int* countingSort(string str1, map<char, int> letterMap) {
	int N = str1.size();
	int* A = new int[N];
	int* B = new int[N];
	int counter = 0;

	for (int i = 0; i < N; i++) { // wypelnianie tablicy A liczbami z podanego ciagu
		auto l = letterMap.find(str1[i]);
		A[i] = l->second;
		counter++;
	}

	int max = A[0];
	for (int i = 0; i < N; i++) { // szukanie max w tablicy A
		if (A[i] > max) max = A[i]; counter++;
	}

	int* rank = new int[max + 1];
	for (int i = 0; i <= max; i++) { // zerowanie tablicy RANK
		rank[i] = 0; counter++;
	}

	for (int i = 0; i < N; i++) { // przechowywanie ilosi kazdej liczby
		rank[A[i]]++; counter++;
	}

	for (int i = 1; i <= max; i++) { // przechowywanie sumy elementow sumujac z poprzednim
		rank[i] += rank[i - 1]; counter++;
	}

	for (int i = N - 1; i >= 0; i--) { // znajdowanie indeksu kazdego elementu w tablicy rank i umieszczanie go w tablicy wynikowej
		B[rank[A[i]] - 1] = A[i]; counter++;
		rank[A[i]]--;
	}

	delete[]A;
	delete[]rank;
	//cout << counter << endl;
	return B;
}

void printTabInt(int tab[], int N) { // wypisywanie tablicy w liczbach
	for (int i = 0; i < N; i++) {
		cout << tab[i] << " ";
	}
	cout << endl;
}

void printTabChar(int tab[], int N) { // wypisywanie tablicy w znakach
	for (int i = 0; i < N; i++) {
		cout << char(tab[i]);
	}
	cout << endl;
}

size_t getMax(string array[], int N) { // znajdowanie max elementu
	size_t max = array[0].size();
	for (int i = 1; i < N; i++) {
		counterRad++;
		if (array[i].size() > max)
			max = array[i].size();
	}
	return max;
}

void countSort(string array[], int size, size_t k) {
	string* B = NULL; int* C = NULL;
	B = new string[size];
	C = new int[257];

	for (int i = 0; i < 257; i++) {
		C[i] = 0;
	}
	for (int i = 0; i < size; i++) {
		counterRad++;
		C[k < array[i].size() ? (int)(unsigned char)array[i][k] + 1 : 0]++;
	}

	for (int i = 1; i < 257; i++) {
		counterRad++;
		C[i] += C[i - 1];
	}

	for (int i = size - 1; i >= 0; i--) {
		counterRad++;
		B[C[k < array[i].size() ? (int)(unsigned char)array[i][k] + 1 : 0] - 1] = array[i];
		C[k < array[i].size() ? (int)(unsigned char)array[i][k] + 1 : 0]--;
	}

	for (int i = 0; i < size; i++) {
		counterRad++;
		array[i] = B[i];
	}

	delete[] B;
	delete[] C;
}

void radixSort(string array[], int r) {
	size_t max = getMax(array, r);
	for (size_t digit = max; digit > 0; digit--) {
		countSort(array, r, digit - 1);
	}

}


int main() {
	srand(time(NULL));

	char letter;
	map<char, int> letterMap;
	for (int i = 97; i <= 122; i++) { // mapowanie liter
		letterMap.insert(pair<char, int>(i, int(i)));
	}

    string str;
	string str1;
	int* countingSortStr;
	cout << "COUNTING SORT" << endl << endl;
	for(int i = 1; i <= 100; i += 10){
	//cout << "COUNTING SORT: Podaj ciag liter" << endl;
	
	//cin >> str;
	
		for (int j = 1; j <= i; j++) {
			str1 += 'a' + rand() % 26;
		}
	
	/*try { // sprawdzenie poprawnosci
		str1 = checking(str);
	}
	catch (invalid_argument& e) {
		cerr << e.what() << endl;
	}*/

		cout << str1 << endl;
	countingSortStr = countingSort(str1, letterMap);
	//cout << endl << "Tablica liczb(posortowanych): " << endl;
	//printTabInt(countingSortStr, str1.size());
	
	//cout << endl << "Tablica charow(posortowanych): " << endl;
	cout << "Sorted --> ";
	printTabChar(countingSortStr, str1.size());
	//cout << endl;
	str1 = "";
	}

	
	cout << endl << endl << "RADIX SORT" << endl << endl;
	string array[10] = { "" };
	int N = 0;
	int word_length;

	for (int i = 1; i <= 100; i += 10) {
		str1 = "";
		
		//cout << "RADIX SORT: Podaj kilka lancuchow o dlugosci nie wiekszej niz 20 (0 konczy pobieranie)" << endl;
		//while (true) {
			/*cin >> str;
			if (str == "0") break;
			try { // sprawdzenie poprawnosci
				str1 = checking(str);
			}
			catch (invalid_argument& e) {
				cerr << e.what() << endl;
			}*/
			
			word_length = (rand() % 20) + 1;
			for (int j = 1; j <= word_length; j++) {
				str1 += 'a' + rand() % 26;
			}
			
			array[N] = str1;
			N++;
		//}
		}

		for (size_t i = 0; i < sizeof(array) / sizeof(array[0]); i++) { // wypisywanie tablicy przed sortowaniem
			cout << array[i].c_str() << endl;
		}
		
		//cout << counterRad << endl;
		//counterRad = 0;
	
		int r;
		r = (int)(sizeof(array) / sizeof(array[0]));
		radixSort(array, r);
		cout << endl << "Sorted --> " << endl;
		for (size_t i = 0; i < sizeof(array) / sizeof(array[0]); i++) { // wypisywanie tablicy po sortowaniu
			cout << array[i].c_str() << endl;
		}
		
	
	delete[] countingSortStr;
	return 0;
}