#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <Windows.h>
#define divider cout<<"\n====================================================================\n"// разделитель(нужен для упрощения написания меню)
using namespace std;
// Глобальные константы для хеш-таблицы
const int segNum = 100;//Число сегментов хеш-таблицы
const int attNum = segNum * (int)log(segNum);// Число попыток вставки ключа ( N*ln(n) )
struct CLIENT { // информация о клиенте
	string LicenseNum; //№ водительского удостоверения (RR AA NNNNNN)
	string Name; // ФИО
	string Passport; // Паспортные данные(серия, номер)
	string Adress; // Адрес
};

struct AUTO { // информация об автомобиле
	string Num; //№ машины (ANNNAA-NN)
	string Brand;// марка машины
	string Color;// цвет машины
	int Year;// год выпуска
	bool IsAvaible; // признак наличия
};

struct ISSUANCE { // информация о договоре об аренде
	string ClientLicense; //№ водительского удостоверения (RR AA NNNNNN)
	string AutoNum;//№ машины (ANNNAA-NN)
	string DateOfHire;// дата выдачи
	string DateOfReturn;// дата возврата
};

//Проверки:
//Проверки данных о клиенте
bool LicenseNumCheck(string Lnum){// проверка № водительского удостоверения
	bool flag = false;
		if (Lnum.length() == 12) {
		if ((Lnum[0] >= '0' && Lnum[0] <= '9') && (Lnum[1] >= '0' && Lnum[1] <= '9') && Lnum[2] == ' ')
			if (Lnum[3] == 'А' || Lnum[3] == 'В' || Lnum[3] == 'Е' || Lnum[3] == 'К' || Lnum[3] == 'М' || Lnum[3] == 'Н' || Lnum[3] == 'О'
				|| Lnum[3] == 'Р' || Lnum[3] == 'С' || Lnum[3] == 'Т' || Lnum[3] == 'У' || Lnum[3] == 'Х')
				if (Lnum[4] == 'А' || Lnum[4] == 'В' || Lnum[4] == 'Е' || Lnum[4] == 'К' || Lnum[4] == 'М' || Lnum[4] == 'Н' || Lnum[4] == 'О'
					|| Lnum[4] == 'Р' || Lnum[4] == 'С' || Lnum[4] == 'Т' || Lnum[4] == 'У' || Lnum[4] == 'Х')
					if (Lnum[5] == ' ' && (Lnum[6] >= '0' && Lnum[6] <= '9') && (Lnum[7] >= '0' && Lnum[7] <= '9')&& (Lnum[8] >= '0' && Lnum[8] <= '9')
						&& (Lnum[9] >= '0' && Lnum[9] <= '9')&& (Lnum[10] >= '0' && Lnum[10] <= '9')&& (Lnum[11] >= '0' && Lnum[1] <= '9'))
					{
						flag = true;					
					}
		}
		return flag;
}
bool PassportCheck(string passport){
	bool flag = false;
	if (passport.length() == 12) {
		if ((passport[0] >= '0' && passport[0] <= '9') && (passport[1] >= '0' && passport[1] <= '9') && passport[2] == ' ')
			if ((passport[3] >= '0' && passport[3] <= '9') && (passport[4] >= '0' && passport[4] <= '9') && passport[5] == ' ')
				if ((passport[6] >= '0' && passport[7] >= '0' && passport[8] >= '0' && passport[9] >= '0'&& passport[10] >= '0' && passport[11] >= '0') &&
					(passport[6] <= '9' && passport[7] <= '9'&& passport[8] <= '9'&& passport[9] <= '9'&& passport[10] <= '9' && passport[11] <= '9'))
					flag = true;
	}			
	return flag;
}
//Проверки данных об автомобиле
bool NumCheck(string num){
	bool flag = false;
	if (num.length() == 9)
	if (num[0] == 'А' || num[0] == 'В' || num[0] == 'Е' || num[0] == 'К' || num[0] == 'Ь' || num[0] == 'Н' || num[0] == 'О'
		|| num[0] == 'Р' || num[0] == 'С' || num[0] == 'Т' || num[0] == 'У' || num[0] == 'Х')
		if ((num[1] >= '0' && num[1] <= '9') && (num[2] >= '0' && num[2] <= '9') && (num[3] >= '0' && num[3] <= '9'))
			if (num[4] == 'А' || num[4] == 'В' || num[4] == 'Е' || num[4] == 'К' || num[4] == 'М' || num[4] == 'Н' || num[4] == 'О'
				|| num[4] == 'Р' || num[4] == 'С' || num[4] == 'Т' || num[4] == 'У' || num[4] == 'Х')
				if (num[5] == 'А' || num[5] == 'В' || num[5] == 'Е' || num[5] == 'К' || num[5] == 'М' || num[5] == 'Н' || num[5] == 'О'
					|| num[5] == 'Р' || num[5] == 'С' || num[5] == 'Т' || num[5] == 'У' || num[5] == 'Х')
					if (num[6] == '-' && (num[7] >= '0' && num[7] <= '9') && (num[8] >= '0' && num[8] <= '9'))
						flag = true;
	return flag;
}
bool YearCheck(int year){
	bool flag = false;
	if (cin.good())
		if (year >= 1880 && year <= 2020)
			flag = true;
	return flag;
}
//Проверки данных о договоре
bool DateCheck(string date){
	bool flag = false;
	if (date.length() == 10)
		if ((date[0] >= '0' && date[0] <= '9') && (date[1] >= '0' && date[1] <= '9') && date[2] == '.')
			if ((date[3] >= '0' && date[3] <= '9') && (date[4] >= '0' && date[4] <= '9') && date[5] == '.')
				if ((date[6] >= '0' && date[6] <= '9') && (date[7] >= '0' && date[7] <= '9') && (date[8] >= '0' && date[8] <= '9') && (date[9] >= '0' && date[9] <= '9'))
					flag = true;
	return flag;
}
//Общие проверки
bool StrCheck(string str){ // Проверка на соответствие типу string 
	if (cin.good())
		return true;
	else return false;
}
//работа с деревом (производится через рекурсивные функции)
struct ClientTree { //структура дерева поиска
	CLIENT cl;
	int h;
	ClientTree * left;
	ClientTree * right;
	ClientTree(CLIENT c) { cl = c; left = right = NULL; h = 1; }
};
int h(ClientTree* OurTree) { // вывод высоты узла
	return OurTree ? OurTree->h : 0;
}
int bFactor(ClientTree* OurTree) {// вывод показателя сбалансированности
	return h(OurTree->right) - h(OurTree->left);
}
void FixH(ClientTree* OurTree) {// корректировка высоты узла
	int hl = h(OurTree->left);
	int hr = h(OurTree->right);
	OurTree->h = (hl > hr ? hl : hr) + 1;
}
ClientTree* RotateRight(ClientTree* OurTree) { // правый поворот
	ClientTree* q = OurTree->left;
	OurTree->left = q->right;
	q->right = OurTree;
	FixH(OurTree);
	FixH(q);
	return q;
}
ClientTree* RotateLeft(ClientTree* OurTree) {// левый поворот 
	ClientTree* p = OurTree->right;
	OurTree->right = p->left;
	p->left = OurTree;
	FixH(OurTree);
	FixH(p);
	return p;
}
ClientTree* Balance(ClientTree* OurTree) {// балансировка узла 
	FixH(OurTree);
	if (bFactor(OurTree) == 2) {
		if (bFactor(OurTree->right) < 0)
			OurTree->right = RotateRight(OurTree->right);// большой левый поворот
		return RotateLeft(OurTree);
	}
	if (bFactor(OurTree) == -2) {
		if (bFactor(OurTree->left) > 0)
			OurTree->left = RotateLeft(OurTree->left); //большой правый поворот
		return RotateRight(OurTree);
	}
	return OurTree;
}
ClientTree* RegClient(ClientTree* OurTree,CLIENT cl) {// вставка узла в дерево
	if (!OurTree) return new ClientTree(cl);
	if (cl.LicenseNum < OurTree->cl.LicenseNum)
		OurTree->left = RegClient(OurTree->left, cl);
	else
		OurTree->right = RegClient(OurTree->right, cl);
	return Balance(OurTree);
}
ClientTree* FindMin(ClientTree* OurTree) {// поиск узла с минимальным ключом в дереве 
	return OurTree->left ? FindMin(OurTree->left) : OurTree;
}
ClientTree* RemoveMin(ClientTree* OurTree) {// удаление узла с минимальным ключом из дерева
	if (OurTree->left == 0)
		return OurTree->right;
	OurTree->left = RemoveMin(OurTree->left);
	return Balance(OurTree);
}
ClientTree* FindByLic(ClientTree* OurTree, string lnum) {//поиск по номеру водительского удостоверения
	if (!OurTree) return NULL;// если поиск неуспешен - возвращаем NULL
	if (lnum == OurTree->cl.LicenseNum)// Пользуясь упорядоченностью дерева, ищем нужную ветвь до совпадения ключей
		return OurTree;
	if (lnum < OurTree->cl.LicenseNum)
		return FindByLic(OurTree->left, lnum);
	else
		return FindByLic(OurTree->right, lnum);

}
bool FindInText(string text, string word) {// поиск совпадения слова в тексте
	bool flag = false;// по-умолчанию возвращаем ложь
	if (text.length() >= word.length()) {// если длина слова меньше, чем текста
		for (int i = 0; i < text.length(); i++) { // ищем совпадения первого символа слова и i-го символа текста
			int count = 1;
			if (text[i] == word[0])
				for (int j = 1; j < word.length(); j++) {// если нашли - считаем количество совпадений символов подряд
					if (text[i + j] == word[j])
						count++;
				}
			if (count == word.length())
			{//Если число совпадений подряд равно длине слова - прерываем работу цикла и возвращаем истину
				flag = true;
				break;
			}
		}
	}
	return flag;
}
void FindByName(ClientTree* OurTree, string nameToFind, int &count) {// поиск по имени или его фрагментам
	if (OurTree) {
		FindByName(OurTree->left, nameToFind, count);
		FindByName(OurTree->right, nameToFind, count);// осуществить обратный обход дерева
		if (FindInText(OurTree->cl.Name, nameToFind))// если совпадение найдено
		{// вывести данные о клиенте
			cout << OurTree->cl.LicenseNum << "\t" << OurTree->cl.Name << "\t" << OurTree->cl.Adress << endl; count++;
		}
	}
}
void FindByAdress(ClientTree* OurTree, string adressToFind, int &count) {// поиск по адресу или его фрагментам
	if (OurTree) {
		FindByAdress(OurTree->left, adressToFind, count);
		FindByAdress(OurTree->right, adressToFind, count);// осуществить обратный обход дерева
		if (FindInText(OurTree->cl.Adress, adressToFind))// если совпадение найдено
		{// вывести данные о клиенте
			cout << OurTree->cl.LicenseNum << "\t" << OurTree->cl.Name << "\t" << OurTree->cl.Adress << endl; count++;
		}
	}
}
ClientTree* DelClient(ClientTree* OurTree, string lnum) {// удаление узла из дерева
	if (!OurTree) return NULL;// если не нашли элемент или дерево пустое - вернуть NULL
	if (lnum < OurTree->cl.LicenseNum)// поиск по ветвям
		OurTree->left = DelClient(OurTree->left, lnum);
	else if (lnum > OurTree->cl.LicenseNum)
		OurTree->right = DelClient(OurTree->right, lnum);
	else {// при нахождении
		ClientTree* l = OurTree->left;// записать указатели на правого и левого потомков
		ClientTree* r = OurTree->right;
		delete OurTree;// удалить элемент
		if (!r) return l;// если правый потомок отсутствует - вернуть указатель на левый
		ClientTree* min = FindMin(r);// иначе - найти минимальный элемент в правом поддереве и сделать его вершиной 
		min->right = RemoveMin(r);
		min->left = l;
		OurTree = min;
		return Balance(OurTree);// сбалансировать дерево
	}
	return Balance(OurTree);
}
void Bypass(ClientTree*OurTree) { // вывод дерева по порядку обратного обхода
	if (OurTree) {
		Bypass(OurTree->left);
		Bypass(OurTree->right);
		cout << OurTree->cl.LicenseNum << "\t" << OurTree->cl.Name << "\t" << OurTree->cl.Adress << endl;
	}
}
void DelClientTree(ClientTree*OurTree) {// очистка дерева
	if (OurTree->left) { // проход по левым потомкам и их удаление
		DelClientTree(OurTree->left);
	}
	else
		delete OurTree->left;
	if (OurTree->right) // проход по правым потомкам и их удаление
		DelClientTree(OurTree->right);
	else
		delete OurTree->right;

	delete OurTree;
	OurTree = NULL;
}
void SaveTree(ClientTree*OurTree, ofstream &save) {// сохранение данных о клиентах в файл clienttree.txt (в порядке обратного обхода)
	if (OurTree) {
		SaveTree(OurTree->left, save);
		SaveTree(OurTree->right, save);
		if (StrCheck(OurTree->cl.Adress)&& LicenseNumCheck(OurTree->cl.LicenseNum)&&StrCheck(OurTree->cl.Name)&& PassportCheck(OurTree->cl.Passport))
			save << OurTree->cl.Adress << "\t" << OurTree->cl.LicenseNum << "\t" << OurTree->cl.Name << "\t" << OurTree->cl.Passport << "\n";
	}
}
ClientTree* LoadTree(ClientTree * OurTree){// загрузка данных о клиентах из файла clienttree.txt
	ifstream load("clienttree.txt", ios_base::in);
	if (load.is_open()) {
		while (!load.eof()) {
			CLIENT cl;
			getline(load, cl.Adress, '\t');
			getline(load, cl.LicenseNum, '\t');
			getline(load, cl.Name, '\t');
			getline(load, cl.Passport, '\n');
			if (StrCheck(cl.Adress) && LicenseNumCheck(cl.LicenseNum) && StrCheck(cl.Name) && PassportCheck(cl.Passport))
			OurTree = RegClient(OurTree, cl);
		}
	}
	load.close();
	return OurTree;
}
//работа со списком
struct IssuanceList {// структура списка договоров
	ISSUANCE is;
	IssuanceList *next;
	IssuanceList *prev;
};
IssuanceList* SortList(IssuanceList* head) //сортировка списка
{
	int NumOfElem = 0;
	IssuanceList* tmp = head;
	while(tmp->next)// считаем число элементов в списке
	{
		tmp = tmp->next; NumOfElem++;
	}
	NumOfElem++;
	if (NumOfElem > 1) {
		for (int i = NumOfElem - 1; i > 0; i--) {// делаем обратный проход по списку(сужаем неотсортированную часть)
			IssuanceList* Max = head, *tmp2 = head;
			for (int j = 0; j <= i; j++) {// Ищем максимальный эелемент в неотсортированной части
				if (tmp2->is.AutoNum > Max->is.AutoNum)
					Max = tmp2;
				tmp2 = tmp2->next;
			}
			ISSUANCE tmpToReshuffle = tmp->is;// Меняем данные максимального и текущего элементов
			tmp->is = Max->is;				  // (чтобы не переназначать указатели)
			Max->is = tmpToReshuffle;
			tmp = tmp->prev;
		}
	}
	return head;
}
IssuanceList* AddToList(IssuanceList* head, string license, string num, string DoH, string DoR) // добавление в список
{	//создаем новый элемент списка
	IssuanceList* NewElem = new IssuanceList;
	NewElem->is.AutoNum = num;
	NewElem->is.ClientLicense = license;
	NewElem->is.DateOfHire = DoH;
	NewElem->is.DateOfReturn = DoR;
	NewElem->next = NULL;
	NewElem->prev = NULL;
	if (!head) //Если список пуст - делаем новый элемент головой списка
		head = NewElem;
	else {// Иначе - добавляем элемент в конец списка
		IssuanceList*tmp = head;
		while (tmp->next) 
			tmp = tmp->next;
		tmp->next = NewElem;
		NewElem->prev = tmp;
		NewElem->next = NULL;
	}
	return SortList(head);// сортируем и возвращаем указатель на голову списка
}
IssuanceList* SearchInListByNum(IssuanceList*head, string NumToSearch) {// поиск по номеру авто
	while ( head != NULL && head->is.AutoNum != NumToSearch) 
		head = head->next;
	return head;
}
IssuanceList* SearchInListByLic(IssuanceList*head, string LicToSearch) {// поиск по номеру водительского удостоверения
	while (head != NULL && head->is.ClientLicense != LicToSearch)
		head = head->next;
	return head;
}
IssuanceList* DelFromList(IssuanceList*head, string NumToSearch){// удаление по номеру авто 
	IssuanceList * tmp = SearchInListByNum(head, NumToSearch);// осуществляем поиск по номеру
	tmp->prev->next = tmp->next;// связываем предыдущий и следующий элементы списка
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	delete tmp;// удаляем текущий элемент и зануляем указатель
	tmp = NULL;
	return SortList(head);// вызываем сортировку и возвращаем указатель на голову списка
}
void SaveList(IssuanceList* head) {// Сохранение списка в файл "issuances.txt"
	ofstream save("issuances.txt", ios_base::out | ios_base::trunc);
	if (save.is_open()) {
		while (head) {
			if (NumCheck(head->is.AutoNum) && LicenseNumCheck(head->is.ClientLicense) && DateCheck(head->is.DateOfHire) && DateCheck(head->is.DateOfReturn)) {
				save << head->is.AutoNum << "\t" << head->is.ClientLicense << "\t" << head->is.DateOfHire << "\t" << head->is.DateOfReturn << endl;
			}
			head = head->next;
		}
	}save.close();
}
IssuanceList* LoadList(IssuanceList*head) {
	ifstream load("issuances.txt", ios_base::in);
	if (load.is_open()){
		while (!load.eof()) {
			ISSUANCE iss;
			getline(load, iss.AutoNum, '\t');
			getline(load, iss.ClientLicense, '\t');
			getline(load, iss.DateOfHire, '\t');
			getline(load, iss.DateOfReturn, '\n');
			if (NumCheck(iss.AutoNum) && LicenseNumCheck(iss.ClientLicense) && DateCheck(iss.DateOfHire) && DateCheck(iss.DateOfReturn))
				head = AddToList(head, iss.ClientLicense, iss.AutoNum, iss.DateOfHire, iss.DateOfReturn);
		}
	}load.close();
	return head;
}
//работа с хэш-таблицей
int HashIt(string auNum) {//хеш-функция
	return  abs((int)(pow((int)auNum[0], 3) + pow((int)auNum[1], 3) + pow((int)auNum[2], 3) + pow((int)auNum[3], 3) + pow((int)auNum[4], 3) +
		pow((int)auNum[5], 3) + pow((int)auNum[6], 3) + pow((int)auNum[7], 3) + pow((int)auNum[8], 3) + pow((int)auNum[9], 3))) % segNum;
}
void create(AUTO ar[segNum]){// функция генерации пустой хеш-таблицы
	for (int i = 0; i < segNum; i++)
	{
		ar[i].Num = "";
		ar[i].Brand = "";
		ar[i].Color = "";
		ar[i].Year = -1;
		ar[i].IsAvaible = false;
	}
}
void addHashTable(AUTO ar[segNum], AUTO machine, bool& isFull) {// функция добавления данных в хеш-таблицу
	int attempt = 0, k = 0, l = 0;
	int i = HashIt(machine.Num);
	if (ar[i].Num == "")// если коллизии нет - записываем
	{
		ar[i].Num = machine.Num;
		ar[i].Brand = machine.Brand;
		ar[i].Color = machine.Color;
		ar[i].Year = machine.Year;
		ar[i].IsAvaible = machine.IsAvaible;
	}
	else{// если коллизия есть - делаем линейное опробование, пока не найдем свободное место, или не поймем, что таблица полна
		do{
			k++;
			if (k > attNum){
				isFull = true;
			}
			attempt = (i+k*3)%segNum;
		} while (ar[attempt].Num != ""||isFull);
		ar[attempt].Num = machine.Num;// записываем на пустое  место
		ar[attempt].Brand = machine.Brand;
		ar[attempt].Color = machine.Color;
		ar[attempt].Year = machine.Year;
		ar[attempt].IsAvaible = machine.IsAvaible;
	}
}
int searchByNum(AUTO ar[segNum], string num) {// поиск по номеру автомобиля
	int i = HashIt(num), k = 0, attempt = 0;
	int resInd = -1;
	if (ar[i].Num != num) {// если при вставке была коллизия
		do {
			k++;
			if (k > attNum){
				return resInd;
			}
			attempt = (i + k * 3)%segNum;
		} while (ar[attempt].Num != num);
		resInd = attempt;

	}
	else
		resInd = i;
	return resInd;
}
void searchByBrand(AUTO ar[segNum], string brand) {// линейный поиск автомобилей по марке
	for (int i = 0; i < segNum; i++) {
		if (ar[i].Brand == brand)
			cout << ar[i].Num << " " << ar[i].Brand << " " << ar[i].Color << " " << ar[i].Year << endl;
	}
}
bool removeHashTable(AUTO ar[segNum], string num){// функция удаления записи из хеш-таблицы
	bool flag = false;
	int i = searchByNum(ar, num);// Поиск нужного элемента
		if (i != -1)// стираем данные(если элемент найден)
		{
			flag = true;
			ar[i].Num = "";
			ar[i].Brand = "";
			ar[i].Color = "";
			ar[i].Year = -1;
			ar[i].IsAvaible = false;
		}
	return flag;// возвращаем отчет об удалении
}
bool deleteHashTable(AUTO ar[segNum]){//удаление всех данных из хеш-таблицы
	bool flag = false;
	for (int i = 0; i < segNum; i++)
	{
		if (ar[i].Num != "")
		{
			ar[i].Num = "";
			ar[i].Brand = "";
			ar[i].Color = "";
			ar[i].Year = -1;
			ar[i].IsAvaible = false;
			flag = true;
		}
	}
	return flag;
}
bool isTableEmpty(AUTO ar[segNum]){// проверка хеш-таблицы на пустоту
	int count = 0;
	for (int i = 0; i < segNum; i++)
		if (ar[i].Num != "")
			count++;
	if (count == 0)// если в таблице нет непустых ключей
		return true;
	else
		return false;
}
void showTable(AUTO ar[segNum]) {//функция отображения таблицы
	for (int i = 0; i < segNum; i++)
		if (ar[i].Num != "")
			cout << ar[i].Num << "\t" << ar[i].Brand << "\t" << ar[i].Color << endl;
}
void saveHashTable(AUTO ar[segNum]){// функция сохранения таблицы в файл "autotable.txt"
	ofstream save("autotable.txt", ios_base::out | ios_base::trunc);
	for (int i = 0; i < segNum; i++) {
		save << ar[i].Num << "\t" << ar[i].Brand << "\t" << ar[i].Color << "\t" << ar[i].Year << "\t" <<ar[i].IsAvaible << endl;
	}
}
void loadHashTable(AUTO ar[segNum]) {// функция загрузки таблицы из файла "autotable.txt"
	ifstream load("autotable.txt", ios_base::in);
	create(ar);
	if (load.is_open()) {
		for (int i = 0; i < segNum; i++) {
			getline(load, ar[i].Num, '\t');
			getline(load, ar[i].Brand, '\t');
			getline(load, ar[i].Color, '\t');
			load >> ar[i].Year;
			load.ignore(1);
			load >> ar[i].IsAvaible;
			load.ignore(1);
		}
		load.close();
	}
}
int main() {
	ClientTree *  Tree = NULL;// инициализация дерева
	IssuanceList * head = NULL;// списка
	AUTO HashTable[segNum];// хеш-таблицы
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int selector = -1;
	// Загрузка данных из файлов
	Tree = LoadTree(Tree);// дерева
	head = LoadList(head);// списка
	loadHashTable(HashTable);// хеш-таблицы
	// Меню
	while (selector)
	{
		int  ch = -1;
		divider;
		cout << "Главное меню:\n"
			<< "1 - Работа с информацией о клиентах\n"
			<< "2 - Работа с информацией об автомобилях\n"
			<< "3 - Работа с договорами о прокате\n"
			<< "0 - Выход из программы\n";
		divider;
		cin >> selector;
		system("cls");
		switch (selector) {
		default:
			cout << "Некорректный выбор\n";
			break;
		case 1:
			while (ch) {
				divider;
				cout << "Меню работы с информацией о клиентах:\n"
					<< "1 - Регистрация нового клиента\n"
					<< "2 - Снятие клиента с обслуживания\n"
					<< "3 - Просмотр всех зарегистрированных клиентов\n"
					<< "4 - Очистка данных о клиентах\n"
					<< "5 - Поиск клиента по № водительского удостоверения\n"
					<< "6 - Поиск клиента по ФИО\n"
					<< "7 - Поиск клиента по адресу\n"
					<< "0 - В главное меню\n";
				divider;
				cin >> ch;
				system("cls");
				CLIENT cl;
				IssuanceList* flist = NULL;
				ClientTree *  ftr = NULL;
				int flag = 0;
				switch (ch) {
				default:
					cout << "Некорректный выбор\n";
					break;
				case 1://Регистрация нового клиента
					system("cls");
					divider;
					cout << "Регистрация нового клиента";// шапка
					divider;
					cout << "Введите номер водительского удостоверения: ";//считывание данных из консоли и проверки
					cin.ignore(cin.rdbuf()->in_avail());
					getline(cin, cl.LicenseNum);
					while (!LicenseNumCheck(cl.LicenseNum))
					{
						cout << "Некорректный ввод номера водительского удостоверения, повторите попытку\n";
						cin.ignore(cin.rdbuf()->in_avail());
						getline(cin, cl.LicenseNum);
					}
					cout << "Введите ФИО: ";
					cin.ignore(cin.rdbuf()->in_avail());
					getline(cin, cl.Name);
					while (!StrCheck(cl.Name))
					{
						cout << "Некорректный ввод ФИО, повторите попытку\n";
						cin.ignore(cin.rdbuf()->in_avail());
						getline(cin, cl.Name);
					}
					cout << "Введите паспортные данные (серия и номер): ";
					cin.ignore(cin.rdbuf()->in_avail());
					getline(cin, cl.Passport);
					while (!PassportCheck(cl.Passport)) {
						cout << "Некорректный ввод паспортных данных, повторите попытку\n";
						cin.ignore(cin.rdbuf()->in_avail());
						getline(cin, cl.Passport);
					}
					cout << "Введите адрес: ";
					cin.ignore(cin.rdbuf()->in_avail());
					getline(cin, cl.Adress);
					while (!StrCheck(cl.Adress)) {
						cout << "Некорректный ввод адреса, повторите попытку\n";
						cin.ignore(cin.rdbuf()->in_avail());
						getline(cin, cl.Adress);
					}
					Tree = RegClient(Tree, cl);// вызвов функции добавления элемента в дерево
					break;
				case 2:
					system("cls");
					divider;
					cout << "Снятие клиента с обслуживания";// шапка
					divider;
					cout << "Введите номер водительского удостоверения: ";//считывание данных из консоли и проверки
					cin.ignore(cin.rdbuf()->in_avail());
					getline(cin, cl.LicenseNum);
					while (!LicenseNumCheck(cl.LicenseNum))
					{
						cout << "Некорректный ввод номера водительского удостоверения, повторите попытку\n";
						cin.ignore(cin.rdbuf()->in_avail());
						getline(cin, cl.LicenseNum);
					}
					Tree = DelClient(Tree, cl.LicenseNum);// вызвов функции удаления элемента из дерева
					break;
				case 3:
					system("cls");
					divider;
					cout << "Просмотр всех зарегистрированных клиентов";// шапка
					divider;
					if (Tree)// вывод дерева по обратному обходу или сообщение о пустоте списка
						Bypass(Tree);
					else
						cout << "Информация о клиентах отсутствует\n";
					break;
				case 4:
					system("cls");
					divider;
					cout << "Очистка данных о клиентах";//шапка
					divider;
					DelClientTree(Tree);//вызов функции очистки дерева
					Tree = NULL;
					cout << "Данные успешно удалены\n";
					break;
				case 5:
					system("cls");
					divider;
					cout << "Поиск клиента по № водительского удостоверения";// шапка
					divider;
					cout << "Введите номер водительского удостоверения:";//считывание данных из консоли и проверки
					cin.ignore(cin.rdbuf()->in_avail());
					getline(cin, cl.LicenseNum);
					while (!LicenseNumCheck(cl.LicenseNum))
					{
						cout << "Некорректный ввод номера водительского удостоверения, повторите попытку\n";
						cin.ignore(cin.rdbuf()->in_avail());
						getline(cin, cl.LicenseNum);
					}
					ftr = FindByLic(Tree, cl.LicenseNum);
					cout << "Результат поиска:\n";
					if (ftr) {// вывод найденных данных или сообщения об отсутствии
						cout << ftr->cl.LicenseNum << "\t" << ftr->cl.Name << "\t" << ftr->cl.Adress << endl;
						flist = SearchInListByLic(head, ftr->cl.LicenseNum);
						cout << "Номер выданного автомобиля: ";
						if (flist)
							cout << flist->is.AutoNum << endl;
						else cout << "нет выданных автомобилей\n";
					}
					else
						cout << "Клиент не найден\n";
					break;
				case 6:
					system("cls");
					divider;
					cout << "Поиск клиента по ФИО(или фрагментам ФИО)";// шапка
					divider;
					cout << "Введите ФИО: ";//считывание данных из консоли и проверки
					cin.ignore(cin.rdbuf()->in_avail());
					getline(cin, cl.Name);
					while (!StrCheck(cl.Name))
					{
						cout << "Некорректный ввод ФИО, повторите попытку\n";
						cin.ignore(cin.rdbuf()->in_avail());
						getline(cin, cl.Name);
					}
					cout << "Результаты поиска: \n";
					FindByName(Tree, cl.Name, flag);// вызов поиска по имени
					if (!flag)
						cout << "Клиентов с такими ФИО не найдено\n";
					break;
				case 7:
					system("cls");
					divider;
					cout << "Поиск клиента по адресу(или фрагментам адреса)";//шапка
					divider;
					cout << "Введите адрес: ";//считывание данных из консоли и проверки
					cin.ignore(cin.rdbuf()->in_avail());
					getline(cin, cl.Adress);
					while (!StrCheck(cl.Adress))
					{
						cout << "Некорректный ввод адреса, повторите попытку\n";
						cin.ignore(cin.rdbuf()->in_avail());
						getline(cin, cl.Adress);
					}
					cout << "Результаты поиска: \n";
					FindByAdress(Tree, cl.Adress, flag);//вызов поиска по адресу
					if (!flag)
						cout << "Клиентов с таким адресом не найдено\n";
					break;
				case 0:
					break;
				}
			}
			break;
		case 2:
			while (ch) {
				divider;
				cout << "Меню работы с информацией об автомобилях:\n"
					<< "1 - Добавление нового автомобиля\n"
					<< "2 - Удаление сведений об автомобиле\n"
					<< "3 - Просмотр всех имеющихся автомобилей\n"
					<< "4 - Очистка данных об автомобилях\n"
					<< "5 - Поиск автомобиля по регистрационному номеру\n"
					<< "6 - Поиск автомобиля по марке\n"
					<< "7 - Регистрация отправки автомобиля в ремонт\n"
					<< "8 - Регистрация прибытия автомобиля из ремонта\n"
					<< "0 - В главное меню\n";
				divider;
				cin >> ch;
				system("cls");
				bool flag = false, isFull = false;
				int i = -1;
				AUTO m;
				switch (ch) {
				default:
					cout << "Некорректный выбор\n";
					break;
				case 1:
					system("cls");
					divider;
					cout << "Добавление нового автомобиля в таблицу";//шапка
					divider;
					cout << "Введите номер автомобиля: ";//считывание данных из консоли и проверки
					cin.ignore(cin.rdbuf()->in_avail());
					getline(cin, m.Num);
					while (!NumCheck(m.Num)) {
						cout << "Номер автомобиля введен некорректно. Повторите попытку: ";
						cin.ignore(cin.rdbuf()->in_avail());
						getline(cin, m.Num);
					}
					cout << "Введите марку машины: ";
					cin.ignore(cin.rdbuf()->in_avail());
					getline(cin, m.Brand);
					while (!StrCheck(m.Brand)) {
						cout << "Марка машины введена некорректно. Повторите попытку: ";
						cin.ignore(cin.rdbuf()->in_avail());
						getline(cin, m.Brand);
					}
					cout << "введите цвет машины: ";
					getline(cin, m.Color);
					while (!StrCheck(m.Color)) {
						cout << "Цвет машины введен некорректно. Повторите попытку: ";
						cin.ignore(cin.rdbuf()->in_avail());
						getline(cin, m.Color);
					}
					cout << "Введите год выпуска машины: ";
					cin >> m.Year;
					while (!YearCheck(m.Year)) {
						cout << "Год выпуска машины введен некорректно. Повторите попытку: ";
						cin >> m.Year;
					}
					m.IsAvaible = true;
					if(!isFull)//если таблица не полна - добавить данные в таблицу
						addHashTable(HashTable, m, isFull);
					else cout << "Таблица полна, добавление невозможно!\n";
					break;
				case 2:
					system("cls");
					divider;
					cout << "Удаление сведений об автомобиле";// шапка
					divider;
					cout << "Введите номер автомобиля: ";//считывание данных из консоли и проверки
					cin.ignore(cin.rdbuf()->in_avail());
					getline(cin, m.Num);
					while (!NumCheck(m.Num)) {
						cout << "Номер автомобиля введен некорректно. Повторите попытку: ";
						cin.ignore(cin.rdbuf()->in_avail());
						getline(cin, m.Num);
					}
					flag = removeHashTable(HashTable, m.Num);// вызов функции удаления
					if (flag)// сообщение об успешном или неуспешном удалении
						cout << "Автомобиль с номером \"" << m.Num << "\" успешно удален из списка\n";
					else
						cout << "Автомобиль с номером \"" << m.Num << "\" отсутствует в списке\n";
					break;
				case 3:
					system("cls");
					divider;
					cout << "Просмотр всех имеющихся автомобилей";//шапка
					divider;
					if (isTableEmpty(HashTable))//если таблица не пуста
						cout << "Данные об автомобилях не найдены\n";
					else//вызвать функцию вывода таблицы
						showTable(HashTable);
					break;
				case 4:
					system("cls");
					divider;
					cout << "Очистка данных об автомобилях";//шапка
					divider;
					flag = deleteHashTable(HashTable);//вызов функции очистки таблицы
					if (flag)// вывод сообщения об очистке 
						cout << "Таблица успешно очищена\n";
					else
						cout << "Таблица уже пуста\n";
					break;
				case 5:
					system("cls");
					divider;
					cout << "Поиск автомобиля по регистрационному номеру";//шапка
					divider;
					cout << "Введите номер автомобиля: ";//считывание данных из консоли и проверки
					cin.ignore(cin.rdbuf()->in_avail());
					getline(cin, m.Num);
					while (!NumCheck(m.Num)) {
						cout << "Номер автомобиля введен некорректно. Повторите попытку: ";
						cin.ignore(cin.rdbuf()->in_avail());
						getline(cin, m.Num);
					}
					cout << "Результат поиска\n";
					i = searchByNum(HashTable, m.Num);//вызов функции поиска по номеру
					if (i != -1)//если авто есть - вывести данные о нем
					{
						cout << HashTable[i].Num << " " << HashTable[i].Brand << " " << HashTable[i].Color << endl;
						cout << "Данные о выдаче автомобиля в аренду: \n";
						if (HashTable[i].IsAvaible)
							cout << "Автомобиль доступен.\n";
						else
							cout << "Автомобиль выдан клиенту с номером водительского удостоверения \"" << SearchInListByNum(head, HashTable[i].Num)->is.ClientLicense << "\"\n";
					}
					else
						cout << "Автомобиль с таким номером не найден\n";
					break;
				case 6:
					system("cls");
					divider;
					cout << "Поиск автомобиля по марке";//шапка
					divider;
					cout << "Введите марку машины: ";//считывание данных из консоли и проверки
					cin.ignore(cin.rdbuf()->in_avail());
					getline(cin, m.Brand);
					while (!StrCheck(m.Brand)) {
						cout << "Марка машины введена некорректно. Повторите попытку: ";
						cin.ignore(cin.rdbuf()->in_avail());
						getline(cin, m.Brand);
					}
					searchByBrand(HashTable, m.Brand);// вызов функции поиска по марке
					break;
				case 7:
					system("cls");
					divider;
					cout << "Регистрация отправки автомобиля в ремонт";//шапка
					divider;
					cout << "Введите номер автомобиля: ";//считывание данных из консоли и проверки
					cin.ignore(cin.rdbuf()->in_avail());
					getline(cin, m.Num);
					while (!NumCheck(m.Num)) {
						cout << "Номер автомобиля введен некорректно. Повторите попытку: ";
						cin.ignore(cin.rdbuf()->in_avail());
						getline(cin, m.Num);
					}
					i = searchByNum(HashTable, m.Num);
					if (i != -1) {//если авто есть
						if (HashTable[i].IsAvaible) {//если авто доступно
							HashTable[i].IsAvaible = false;// переключить флаг на "недоступен"
							cout << "Отправка автомобиля в ремонт зарегистрирована\n";//вывести сообщение об успехе
						}
						else// иначе - сообщить о том, что авто уже недоступно
							cout << "Данный автомобиль не доступен для отправки в ремонт\n";
					}
					else {// иначе - вывести сообщение о том, что авто не найдено
						cout << "Автомобиль с таким номером не найден\n";
					}
					break;
				case 8:
					system("cls");
					divider;
					cout << "Регистрация прибытия автомобиля из ремонта";// шапка
					divider;
					cout << "Введите номер автомобиля: ";//считывание данных из консоли и проверки
					cin.ignore(cin.rdbuf()->in_avail());
					getline(cin, m.Num);
					while (!NumCheck(m.Num)) {
						cout << "Номер автомобиля введен некорректно. Повторите попытку: ";
						cin.ignore(cin.rdbuf()->in_avail());
						getline(cin, m.Num);
					}
					i = searchByNum(HashTable, m.Num);
					if (i != -1) {
						if (!HashTable[i].IsAvaible) {//если авто есть
							if (SearchInListByNum(head, HashTable[i].Num) == NULL) {//если авто недоступно и НЕ в аренде
								HashTable[i].IsAvaible = true;//установить флаг на "доступно"
								cout << "Прибытие автомобиля из ремонта зарегистрировано\n";// вывести сообщение об успехе
							}
							else cout << "Автомобиль находится в аренде, а не в ремонте.\n";// иначе - вывести предупреждение
						}
						else
							cout << "Данный автомобиль уже доступен\n";// иначе - сообщение о том, что авто уже доступно
					}
					else {
						cout << "Автомобиль с таким номером не найден\n";
					}
					break;
				case 0:
					break;
				}
			}
			break;
		case 3:
			while (ch) {
				divider;
				cout << "Меню работы с договорами о прокате:\n"
					<< "1 - Регистрация выдачи клиенту автомобиля на прокат\n"
					<< "2 - регистрация возврата автомобиля от клиента\n"
					<< "0 - В главное меню\n";
				divider;
				string lnum, aunum, DoH,DoR;
				cin >> ch;
				system("cls");
				switch (ch) {
				default:
					cout << "Некорректный выбор\n";
					break;
				case 1:
					divider;
					cout << "Регистрация выдачи клиенту автомобиля на прокат";//шапка
					divider;
					cout << "Введите номер водительского удостоверения: ";//считывание данных из консоли и проверки
					cin.ignore(cin.rdbuf()->in_avail());
					getline(cin, lnum);
					while (!LicenseNumCheck(lnum)|| !FindByLic(Tree,lnum))
					{
						if (!LicenseNumCheck(lnum)) {
							cout << "Некорректный ввод номера водительского удостоверения, повторите попытку\n";
							cin.ignore(cin.rdbuf()->in_avail());
							getline(cin, lnum);
						}else {
							cout << "Клиент с таким номером водительского удостоверения отсутствует в базе, повторите попытку\n";
							cin.ignore(cin.rdbuf()->in_avail());
							getline(cin, lnum);
						}
					}
					cout << "Введите номер автомобиля: ";
					cin.ignore(cin.rdbuf()->in_avail());
					getline(cin, aunum);
					while (!NumCheck(aunum) || (searchByNum(HashTable,aunum) == -1)) {
						if (!NumCheck(aunum)) {
							cout << "Номер автомобиля введен некорректно. Повторите попытку: ";
							cin.ignore(cin.rdbuf()->in_avail());
							getline(cin, aunum);
						}else{
							cout << "Автомобиля с данным регистрационным номером не обнаружено в базе. Повторите попытку: ";
							cin.ignore(cin.rdbuf()->in_avail());
							getline(cin, aunum);
						}
					}
					cout << "Введите дату выдачи автомобиля: ";
					cin.ignore(cin.rdbuf()->in_avail());
					getline(cin, DoH);
					while (!DateCheck(DoH)) {
						cout << "Дата выдачи автомобиля введена некорректно. Повторите попытку: ";
						cin.ignore(cin.rdbuf()->in_avail());
						getline(cin, DoH);
					}
					cout << "Введите дату возврата автомобиля: ";
					cin.ignore(cin.rdbuf()->in_avail());
					getline(cin, DoR);
					while (!DateCheck(DoR)) {
						cout << "Дата возврата автомобиля введена некорректно. Повторите попытку: ";
						cin.ignore(cin.rdbuf()->in_avail());
						getline(cin, DoR);
					}
					if (HashTable[searchByNum(HashTable, aunum)].IsAvaible) {//если авто доступно для выдачи
						head = AddToList(head, lnum, aunum, DoH, DoR);// зарегистрировать договор
						cout << "Выдача автомобиля успешно зарегистрирована\n";
						HashTable[searchByNum(HashTable, aunum)].IsAvaible = false;
					}
					else// иначе - вывести предупреждение
						cout << "Автомобиль с номером \"" << aunum <<"\"не доступен для выдачи\n";
					break;
				case 2:
					divider;
					cout << "Регистрация возврата автомобиля от клиента";// шапка
					divider;
					cout << "Введите номер автомобиля: ";//считывание данных из консоли и проверки
					cin.ignore(cin.rdbuf()->in_avail());
					getline(cin, aunum);
					while (!NumCheck(aunum) || (searchByNum(HashTable, aunum) == -1)) {
						if (!NumCheck(aunum)) {
							cout << "Номер автомобиля введен некорректно. Повторите попытку: ";
							cin.ignore(cin.rdbuf()->in_avail());
							getline(cin, aunum);
						}
						else {
							cout << "Автомобиля с данным регистрационным номером не обнаружено в базе. Повторите попытку: ";
							cin.ignore(cin.rdbuf()->in_avail());
							getline(cin, aunum);
						}
					}
					if (!HashTable[searchByNum(HashTable, aunum)].IsAvaible&& (SearchInListByNum(head,aunum)!= NULL)) {//если авто в аренде
						HashTable[searchByNum(HashTable, aunum)].IsAvaible = true;//установить доступность авто
						DelFromList(head, aunum);// удалить договор из списка
						cout << "Возврат автомобиля успешно зарегистрирован\n";
					}else
						cout << "Автомобиль с номером \"" << aunum << "\"в ремонте или уже свободен\n";
					break;
				case 0:
					break;
				}
			}
			break;
		case 0:
			divider;
			cout << "Работа завершена\n";
			divider;
			break;
		}
	}
	//Сохранение данных:
	ofstream save("clienttree.txt", ios_base::out | ios_base::trunc);
	SaveTree(Tree, save);// дерева
	SaveList(head);// списка
	saveHashTable(HashTable);// хеш-таблицы
	// Очистка памяти
	if (Tree) {// от дерева
		DelClientTree(Tree);
		Tree = NULL;
	}
	while (head) {// от списка
		IssuanceList*del = head;
		head = head->next;
		delete del;
		del = NULL;
	}
	head = NULL;
	system("pause");
}
