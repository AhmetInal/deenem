// FinalSon.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <stack>
#include <map>
#include <queue>

using namespace std;
using namespace std::filesystem;

stack<string> dosyaNames;
map<string, float> values;
int lastArrayFinder(string arrayName[]);
void stringParse(string inputLine, char ParsingChar, string parcaci[], int counter);
void reverseStr(string& str);
string path2Name(string str);
void dosyalariBul();
void fileOkuma(string dosyaName, string lines[]);
void arraybosalt(string bosaltaray[]);
void fileProcess();


int main()
{
	fileProcess();

}


int lastArrayFinder(string arrayName[]) {   //girilen arrayde bulunan en son eleman�n indexini return eder
	string* temp;
	temp = arrayName;
	for (int i = 0;i < 30;++i) {
		if (*temp == "") {

			return i - 1;
		}
		else {
			temp++;
		}
	}
	return -1;
}

void stringParse(string inputLine, char ParsingChar, string parcaci[], int counter) { //al�nan input stringini parsing char ile b�ler
	string temp;                                                        // d�sar�da tan�mlanm�s parcaci arrayinde tutar 
	//int counter = (lastArrayFinder(parcaci)+1);
	/*cout << "string parse i�leminin ba�layaca�� satir: ";
	cout << (counter + 1) << endl;*/
	string* tutturgac;

	tutturgac = (parcaci);

	inputLine += " ";
	for (std::string::iterator it = inputLine.begin(); it < inputLine.end(); ++it) {

		if (*it == ParsingChar) {

			*tutturgac = temp;
			tutturgac++;
			temp.clear();
		}
		else if (!(*it == ParsingChar)) {
			temp += *it;

		}

	}
}

void reverseStr(string& str)
{
	int n = str.length();


	for (int i = 0; i < n / 2; i++)
		swap(str[i], str[n - i - 1]);
}

string path2Name(string str) {                            //PATH �LE ELDE ETT���M�Z YOLDA BULUNAN DOSYALARIN �S�MLER�N�N AYRILMASI         
	string temp = "";
	reverseStr(str);
	for (int i = 0;i < (int)str.size();i++)
	{
		if (str[i] == 92)
		{
			break;
		}
		else {
			temp += str[i];
		}
	}
	reverseStr(temp);
	return temp;

}

void dosyalariBul() {
	// C:\\Users\\furkan\\Desktop\\final cpp\\testortami
	//C:\\Users\\ahmet\\Desktop\\cppdeneme
	path p("C:\\Users\\ahmet\\Desktop\\cppdeneme");
	if (!is_directory(p)) {                                                                         //B�YLE B�R D�Z�N VAR MI KONTROL�

		cout << "Burada b�yle bir klas�r yok" << endl;
	}
	else {
		cout << "bulundugunuz directory: " << absolute(p) << endl;
		string dontWant = "FinalSon.exe";
		for (const auto& entry : directory_iterator(absolute(p))) {                                 //DOSYA �S�MLER�N� BULMA



			if (entry.path().extension() == ".inp")
			{
				dosyaNames.push(entry.path().string());
				cout << "bulunan dosya: " << entry.path().filename() << endl;
			}

		}
	}
}

void fileOkuma(string dosyaName, string lines[]) {                    //dosyan�n ismi girilir
														//lines d��ar�da olu�turulmu� ve sat�rlar�n tutulaca�� array� belirtir

	string* pointerLine = lines;                        //sat�rlar� tutan arrayin adresini tutar
	ifstream Challenges(dosyaName, ios::in);
	int i = 0;
	if (Challenges) { //dosya a��l�p a��lmad��� sorgusu
		cout << "Belirlenen dosya ismi bu klasorde mevcut" << endl;
		cout << dosyaNames.top() << endl;

		dosyaNames.pop();
		while (!Challenges.eof()) {//dosyan�n sonuna gelene kadar b�t�n sat�rlar 
								//okunur ve d��ar�da tan�ml� lines arrayine g�nderilir
			getline(Challenges, *lines);
			lines++;
		}
		Challenges.close();
	}
	else {
		cout << "dosya bulunamadi" << endl;
	}
}

void arraybosalt(string bosaltaray[]) {
	for (int i = 0; i < sizeof(bosaltaray); i++) {
		bosaltaray[i] = "";
	}

}

int whatisThis(string whatis) { // 0- Ad 1- Rakam 2- operand manas�na gelmektedir

	if (whatis[0] >= 65 && whatis[0] <= 122) {					//par�alar harf ise ascii 65 ile 122 aras�nda de�er al�r

		/*cout << "BURADA B�R HARF VAR" << endl;*/
		return 0;

	}

	else if (whatis[0] == 43) {										// + ascii kodu
		/*cout << "TOPLAMA OPERATORU VAR" << endl;*/
		return 2;
	}

	else if (whatis[0] == 42) {										// * ascii kodu
		///*cout << "CARPMA OPERATORU VAR" << endl;*/
		return 2;
	}

	else if (whatis[0] == 45) {										// - ascii kodu
		/*cout << "CIKARMA OPERATORU VAR" << endl;*/
		return 2;
	}

	else if (whatis[0] == 47) {										//  '/'  ascii kodu
		/*cout << "BOLME OPERATORU VAR" << endl;*/
		return 2;
	}

	else if (whatis[0] >= 48 && whatis[0] <= 57) {			// al�nan degerler
		/*cout << "Burada bir deger var" << endl;*/
		return 1;
	}
	else {
		return -1;
	}
}
	


void satirIsleme(string parcalar[]) {
	// ({ "A","=" ,"5" })

	if (parcalar[1][0] == 61) {

		if (parcalar[3][0] == 43) {

			auto new_Value = values.at(parcalar[2]) + values.at(parcalar[4]);
			values.insert({ parcalar[0],new_Value });
		}
		int nedirBu = whatisThis(parcalar[2]);
		if (nedirBu == 0) {
			values.insert({ parcalar[0],values.at(parcalar[2]) });
		}
		else if (nedirBu == 1) {
			values.insert({ parcalar[0],stof(parcalar[2]) });
		}		
		/*cout << "degeriniz: " << values.at(parcalar[0]) << endl;;*/
	}


	else {

		cout << values.at(parcalar[1]) << endl;
	}
}
void fileProcess() {

	string LineParcalari[100];
	string DosyaninLineleri[100];
	dosyalariBul();
	map<char, int> integerValues;
	map<char, float>floatValues;
	for (unsigned int i = 0; i <= dosyaNames.size();i++) {            //BURADA i <  DOSYA SAYISI YAPMAN GEREKY��RO
		values.clear();
		/*cout << "dosya ad: "<<dosyaNames.top() << endl*/;
		fileOkuma(dosyaNames.top(), DosyaninLineleri);		//SE��LEN SIRADAK� DOSYANIN SATIRLARI DOSYAL�NES ��ER�S�NE B�R �NDEX OLARAK ATILDI		

		for (int i = 0; i <= lastArrayFinder(DosyaninLineleri); i++) {				//b�t�n sat�rlar burada ayr� ayr� a��l�yor, sat�r�n belirlendi�i nokta
			cout << DosyaninLineleri[i] << endl;
			cout << "olusturulacak degisken sayisi: " << lastArrayFinder(DosyaninLineleri) << endl;

			stringParse(DosyaninLineleri[i], ' ', LineParcalari, i);			//line stringi al�nd� ve par�alanarak linepar�alar�n�n i�erisine at�ld�


			for (int j = 0;j <= lastArrayFinder(LineParcalari);j++) {		//sat�r i�erisinde par�alarda gezilen yer sa�lanan yer

				satirIsleme(LineParcalari);


			}
			arraybosalt(LineParcalari);
		}
		cout << "Sonraki dosyaya geciliyor...\n----------------------------------------------------" << endl;
		arraybosalt(DosyaninLineleri);
	}

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
