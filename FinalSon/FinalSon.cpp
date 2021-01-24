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


int lastArrayFinder(string arrayName[]) {   //girilen arrayde bulunan en son elemanýn indexini return eder
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

void stringParse(string inputLine, char ParsingChar, string parcaci[], int counter) { //alýnan input stringini parsing char ile böler
	string temp;                                                        // dýsarýda tanýmlanmýs parcaci arrayinde tutar 
	//int counter = (lastArrayFinder(parcaci)+1);
	/*cout << "string parse iþleminin baþlayacaðý satir: ";
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

string path2Name(string str) {                            //PATH ÝLE ELDE ETTÝÐÝMÝZ YOLDA BULUNAN DOSYALARIN ÝSÝMLERÝNÝN AYRILMASI         
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
	if (!is_directory(p)) {                                                                         //BÖYLE BÝR DÝZÝN VAR MI KONTROLÜ

		cout << "Burada böyle bir klasör yok" << endl;
	}
	else {
		cout << "bulundugunuz directory: " << absolute(p) << endl;
		string dontWant = "FinalSon.exe";
		for (const auto& entry : directory_iterator(absolute(p))) {                                 //DOSYA ÝSÝMLERÝNÝ BULMA

		    cout << entry.path().string() << endl;

		  // dosyaNames_Path.insert({ path2Name(entry.path().string()), entry.path().string() });     //MAP ÝÇERÝSÝNE EKLEME
			if (!(entry.path().string() == absolute(p).string() + dontWant)) {
				dosyaNames.push(entry.path().string());
				cout << "bulunan dosya: " << entry.path().string() << endl;
			}

			//cout << "burada dosya var";
		}
	}
}

void fileOkuma(string dosyaName, string lines[]) {                    //dosyanýn ismi girilir
														//lines dýþarýda oluþturulmuþ ve satýrlarýn tutulacaðý arrayý belirtir

	string* pointerLine = lines;                        //satýrlarý tutan arrayin adresini tutar
	ifstream Challenges(dosyaName, ios::in);
	int i = 0;
	if (Challenges) { //dosya açýlýp açýlmadýðý sorgusu
		cout << "Belirlenen dosya ismi bu klasorde mevcut" << endl;
		cout << dosyaNames.top() << endl;

		dosyaNames.pop();
		while (!Challenges.eof()) {//dosyanýn sonuna gelene kadar bütün satýrlar 
								//okunur ve dýþarýda tanýmlý lines arrayine gönderilir
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

void fileProcess() {

	string LineParcalari[100];
	string DosyaninLineleri[100];
	dosyalariBul();
	map<char, int> integerValues;
	map<char, float>floatValues;
	for (int i = 0; i <= dosyaNames.size();i++) {            //BURADA i <  DOSYA SAYISI YAPMAN GEREKYÝÞRO
		/*cout << "dosya ad: "<<dosyaNames.top() << endl*/;
		fileOkuma(dosyaNames.top(), DosyaninLineleri);		//SEÇÝLEN SIRADAKÝ DOSYANIN SATIRLARI DOSYALÝNES ÝÇERÝSÝNE BÝR ÝNDEX OLARAK ATILDI		
		
		for (int i = 0; i <= lastArrayFinder(DosyaninLineleri); i++) {				//bütün satýrlar burada ayrý ayrý açýlýyor, satýrýn belirlendiði nokta
			cout << DosyaninLineleri[i] << endl;
			cout << "olusturulacak degisken sayisi: " << lastArrayFinder(DosyaninLineleri) << endl;
			
			stringParse(DosyaninLineleri[i], ' ', LineParcalari, i);			//line stringi alýndý ve parçalanarak lineparçalarýnýn içerisine atýldý

			for (int j = 0;j <= lastArrayFinder(LineParcalari);j++) {		//satýr içerisinde parçalarda gezilen yer saðlanan yer

				if (LineParcalari[j][0] >= 65 && LineParcalari[j][0] <= 122) {					//parçalar harf ise ascii 65 ile 122 arasýnda deðer alýr

					if (LineParcalari[j][1] == 'U' && LineParcalari[j][2] == 'T') {				// CIKTI ÝCÝN 3 TANE CHAR DEGERÝ DOÐRU OLMALI
						cout << " SONRAKI DEGER CIKTI" << endl;
					}
					else {
						cout << "BURADA BÝR HARF VAR" << endl;
					}

				}
				else if (LineParcalari[j][0] == 61) {										// = ascii kodu
					cout << "ATAMA OPERATORU VAR" << endl;
				}

				else if (LineParcalari[j][0] == 43) {										// + ascii kodu
					cout << "TOPLAMA OPERATORU VAR" << endl;
				}

				else if (LineParcalari[j][0] == 42) {										// * ascii kodu
					cout << "CARPMA OPERATORU VAR" << endl;
				}

				else if (LineParcalari[j][0] == 45) {										// - ascii kodu
					cout << "CIKARMA OPERATORU VAR" << endl;
				}

				else if (LineParcalari[j][0] == 47) {										//  '/'  ascii kodu
					cout << "BOLME OPERATORU VAR" << endl;
				}

				else if (LineParcalari[j][0] >= 48 && LineParcalari[j][0] <= 57) {			// alýnan degerler
					cout << "Burada bir deger var" << endl;
					for (int k = 0; k <= LineParcalari[j].length();k++) {
						if (LineParcalari[j][k] == 46) {									//sayýnýn içerisinde . deðer var ise bu deðer float veya double olarak saklanýr
							cout << "BURADA DOUBLE SAYI VAR" << endl;
							break;
							
						}
						else {
							cout << "sonraki basamaga bakiliyor " << endl;
							if (LineParcalari[j][k + 1] == '\0') {
								cout << "bu bir integer" << endl;
								break;
							}
						}
					}
				}



			}
			arraybosalt(LineParcalari);
		}
		cout << "Sonraki dosyaya geciliyor..." << endl;
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
