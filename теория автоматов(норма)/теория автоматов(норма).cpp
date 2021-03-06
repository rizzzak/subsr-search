#include "stdafx.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

inline bool strCompare(string& str, string& str2, int& xS)	//посимвольное сравнение строк xS-размер строки
{
	int k = 0;
	while (true)
	{
		if ((str[k] == str2[k]) && (k == xS - 1))
			return 1;
		else if (str[k] != str2[k])
			return 0;
		k++;
	}
}

inline int prefix(vector<string>& vec, string s)//построение префиксов образца P[i]
{
	int t = s.size();
	int k = 0;
	bool flag = 0;
	string tmp = s;
	for (int i = 1; i <= t; i++)		//проходит все варианты префиксов и добавляет их в вектор vec
	{
		tmp.resize(i);
		for (vector<string>::iterator iter = vec.begin(); iter != vec.end(); iter++)
		{
			k = iter->size();
			if ((tmp.size() == k) && (strCompare(tmp, *iter, k)))				//если строка уже есть в векторе, тогда выход из цикла
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0)							//строки в векторе нет -> добавляем
			vec.push_back(tmp);
		if (tmp == s)
			return vec.size();
		flag = 0;
		tmp = s;
	}
	return 0;
}
inline void strRDel(string& str, const int& k)		//удаление k первых символов в строке
{
	string newStr = "";
	for (int i = k; i <= str.size(); i++)
		newStr += str[i];
	str = newStr;
}
int findMaxSuff(string x, string y, int& vLength)	//поиск наиб суффикса
{
	string tmp = x;
	if (tmp.find('\0') == string::npos)			
		tmp += '\0';
	if (y.find('\0') == string::npos)
		y += '\0';
	int k = tmp.size();
	if ((k == 1) && (y.size() == 1))
		return 0;
	int max = 0;
	for (int i = 1; i <= vLength; i++)		//проходит все варианты суффиксов
	{
		if (k == y.size())										//длины строк совпадают 
			if ((strCompare(tmp, y, k))&&(max < k))				//сравнить строки и текущая длина суффикса больше предыдущих
				{
					max = k;
				}
		if (max != 0)
			return max;
		if (i < vLength)
			strRDel(tmp, 1);
		k--;
	}
	return 0;
}
int sigma(string x, vector<string> y, char c, int& vLength)
{
	x += c;						
	string s = x;
	int xS = x.size();
	int yS = y.size();
	vector<int> pair;			//пара вершина - длина суффикса
	vector<vector<int>> suffVec;
	int maxSuff = 0;			//длина суффикса
	int k = 0;					
	int qNum = 0;
	for (vector<string>::iterator iter = y.begin(); iter != y.end(); iter++)//проходим по каждому элементу в векторе
	{
		yS = iter->size();
		pair.push_back(qNum);
		if (xS > yS)//
		{
			strRDel(s, xS - yS);
			pair.push_back(findMaxSuff(s, *iter, yS));
		}
		else if (xS == yS)//если длины равны - сравнить их
		{
			pair.push_back(findMaxSuff(s, *iter, yS));
		}
		else				
		{
			pair.push_back(0);
		}
		s = x;
		
		
		suffVec.push_back(pair);
		pair.clear();
		qNum++;
	}
	qNum = 0;
	for (vector<vector<int>>::iterator iter = suffVec.begin(); iter != suffVec.end(); iter++)
		if (maxSuff < (*iter)[1])
		{
			maxSuff = (*iter)[1];
			qNum = (*iter)[0];
		}
	return qNum;	//возвращаем длину наиб суффикса
}
inline void encode(const char& in, char& out)
{
	if (((int)in > 31) && ((int)in < 127))	
	{
		if (((64 < (int)in) && (91 > (int)in)) || ((97 <= (int)in) && (122 >= (int)in)))	//если это буква
		{
			if (((int)in < 91) && ((int)in > 64))
			{
				out = (int)in - 65;
				return;
			}
			out = ((int)in) - 97;
		}
		else out = 26;
	}
	else
	{
		cout << "wrong symbol: " << in << " The programm will close in 5..";
		cin.ignore();
		cout << "4..";
		cin.ignore();
		cout << "3..";
		cin.ignore();
		cout << "2..";
		cin.ignore();
		cout << "1..";
		cin.ignore();
		exit(2);
	}
}
inline bool checkStr(const char& in)		//1-если буква, иначе - 0
{
	if (((64 < (int)in) && (91 > (int)in)) || ((97 <= (int)in) && (122 >= (int)in)))	//если это буква
	{
		return 1;	
	}
	return 0;
}
int menu()
{
	int x;
	cout << "Programm for searching of strings.\n\n";
	cout << "1. Input text with keyboard.\n";
	cout << "2. Input text with file (Filepath required).\n";
	cout << "\nPlease, choose needed type of input: ";
	cin >> x;
	switch (x)
	{
	case 1: system("cls"); return 1;
	case 2: system("cls"); return 2;
	default: cout << "wrong choice!\n"; system("pause"); exit(3);
	}

}
int main()
{
	const int lettersCount = 26;//константа, характеризует количество столбцов в матрице(векторе векторов)
	
	int x = menu();
	string str1;	
	string str2;
	string str;		//ввод 3х строк
	int strPos;
	int str1Pos;		//отнаяв от позиции 1 получим индекс в векторе
	int str2Pos;
	bool flag1;
	vector<string> strVec;
	strVec.push_back("");
	while(true){
		flag1 = true;
		cout << "\nPlease enter 1 example: ";
		cin >> str;
		for (int i = 0; i < str.size(); i++)
			if (checkStr(str[i]) == 0) flag1 = false;
		if (!flag1) cout << "\nWrong string. Try again.";
		else break;
	}
	while (true) {
		flag1 = true;
		cout << "\nPlease enter 2 example: ";
		cin >> str1;
		for (int i = 0; i < str1.size(); i++)
			if (checkStr(str1[i]) == 0) flag1 = false;
		if (!flag1) cout << "\nWrong string. Try again.";
		else break;
	}
	while (true) {
		flag1 = true;
		cout << "\nPlease enter 3 example: ";
		cin >> str2;
		for (int i = 0; i < str2.size(); i++)
			if (checkStr(str2[i]) == 0) flag1 = false;
		if (!flag1) cout << "\nWrong string. Try again.";
		else break;
	}
	cout << "\n";
	strPos = prefix(strVec, str);
	str1Pos = prefix(strVec, str1);
	str2Pos = prefix(strVec, str2);
	int maxSize = 0;
	for (vector<string>::iterator iter = strVec.begin(); iter != strVec.end(); iter++)
	{
		cout << *iter << "\n";
		if (maxSize <= iter->size())
			maxSize = iter->size();
	}
	int vecSize = strVec.size();			//количество элеметов в векторе, элементы находятся [0..vecSize-1]
	vector<int> deltaTmp;
	vector<int> deltaH;
	vector<vector<int>>deltaV;

	int k;//значения сигма-функции

	for (int q = 0; q <= vecSize; q++)		//находим значение перехода для каждого примера по строкам
	{
		for (int p = 0; p < lettersCount; p++)//и для каждой буквы по столбцам
		{
			if (q == vecSize)	//при заполнении состояния сбойной строки
			{
				deltaH = deltaV[0];
				deltaH[lettersCount] = 0;//столбец перехода к сбойной ведет также в 0(при повторных неверных символах)
			}
			else
			{
				k = sigma(strVec[q], strVec, (char)p + 97, vecSize);
				deltaH.push_back(k);
			}
		}			//окончился цикл, заполнили строку состояний
		if (q != vecSize)
		{
			deltaH.push_back(vecSize);
		}//заполняет стоблец(по ячейке) прочих символов
		
		deltaV.push_back(deltaH);//добавили строку в матрицу
		deltaH.clear();
	}
	for (vector<vector<int>>::iterator iter = deltaV.begin(); iter != deltaV.end(); iter++)		//вывод таблицы на экран
	{
		for (vector<int>::iterator iter2 = iter->begin(); iter2 != iter->end(); iter2++)
			cout << *iter2 << " ";
		cout << "\n";
	}
	if (x == 1)
	{
		char pCh[512] = { 0 };
		cout << "Please, enter the text: ";
		cin.get();					//забрали терминатор из потока
		cin.getline(pCh, 512, '\n');

		int n = 512;
		char c = ' ';
		int s = 0;
		k = 0;
		int tmp = 0;	//временная переменная для хранения координаты с в векторе векторов
		int* tmp1 = new int(0);
		int* tmp2 = new int(0);
		bool flag = false;
		while (pCh[k] != '\0')		//поиск слова в строке-массиве, новое состояние автомата находится в ячейке [s,c] вектора векторов
		{
			encode(pCh[k], c);//перекодировка символа
			tmp = (int)c;
			*tmp1 = 0;// Must be == s
			*tmp2 = 0;// Must be == c
			for (vector<vector<int>>::iterator iter = deltaV.begin(); iter != deltaV.end(); iter++)
			{
				if (*tmp1 == s)
					for (vector<int>::iterator iter2 = iter->begin(); iter2 != iter->end(); iter2++)
					{
						if (*tmp2 == tmp)
						{
							s = *iter2;
							flag = true;
							break;
						}
						(*tmp2)++;
					}
				if (flag == true)
					break;
				(*tmp1)++;
			}
			if (s == strPos - 1)
				cout << "expression 1 finded at" << k - str.size() + 2 << "position\n";
			else if (s == str1Pos - 1)
				cout << "expression 2 finded at" << k - str1.size() + 2 << "position\n";
			else if (s == str2Pos - 1)
				cout << "expression 3 finded at" << k - str2.size() + 2 << "position\n";
			k++;
			flag = false;
		}
		delete tmp1;
		delete tmp2;
	}
	else 
	{
		unsigned long cSymb = 0;//текущий сивол
		int n = 0;
		char pCh[25600];
		char c;		
		int s;		
		int tmp = 0;	//временная переменная для хранения координаты с в векторе векторов
		int* tmp1 = new int(0);
		int* tmp2 = new int(0);
		bool flag = false;
		string strr;
		ifstream file;
		do
		{
			cout << "\nEntrer filepath(full or X.txt if file is in directory with programm) of input file: ";
			cin >> strr;
			
			file.open(strr);
			if (file.is_open())
				break;
			else cout << "\nWrong filepath. Please, enter filepath again.";
		} while (true);
		while (!file.eof())
		{
			file.getline(pCh, 25600);
			n = 256;
			c = ' ';		//текущий символ
			s = 0;		//текущее состояние
			k = 0;
			flag = false;
			while (pCh[k] != '\0')		//поиск слова в строке-массиве, новое состояние автомата находится в ячейке [s,c] вектора векторов
			{
				cSymb++;
				encode(pCh[k], c);//перекодировка символа
				tmp = (int)c;
				*tmp1 = 0;// Must be == s
				*tmp2 = 0;// Must be == c
				for (vector<vector<int>>::iterator iter = deltaV.begin(); iter != deltaV.end(); iter++)
				{
					if (*tmp1 == s)
						for (vector<int>::iterator iter2 = iter->begin(); iter2 != iter->end(); iter2++)
						{
							if (*tmp2 == tmp)
							{
								s = *iter2;
								flag = true;
								break;
							}
							(*tmp2)++;
						}
					if (flag == true)
						break;
					(*tmp1)++;
				}
				if (s == strPos - 1)
					cout << "expression 1 finded at" << cSymb - str.size() + 2 << "position\n";
				else if (s == str1Pos - 1)
					cout << "expression 2 finded at" << cSymb - str1.size() + 2 << "position\n";
				else if (s == str2Pos - 1)
					cout << "expression 3 finded at" << cSymb - str2.size() + 2 << "position\n";
				k++;
				flag = false;
				
			}

		}
		delete tmp1;
		delete tmp2;
	}
	cout << "\n";
	system("pause");
	return 0;
}

