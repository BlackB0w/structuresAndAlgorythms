#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <Windows.h>
#define divider cout<<"\n====================================================================\n"// �����������(����� ��� ��������� ��������� ����)
using namespace std;
// ���������� ��������� ��� ���-�������
const int segNum = 100;//����� ��������� ���-�������
const int attNum = segNum * (int)log(segNum);// ����� ������� ������� ����� ( N*ln(n) )
struct CLIENT { // ���������� � �������
	string LicenseNum; //� ������������� ������������� (RR AA NNNNNN)
	string Name; // ���
	string Passport; // ���������� ������(�����, �����)
	string Adress; // �����
};

struct AUTO { // ���������� �� ����������
	string Num; //� ������ (ANNNAA-NN)
	string Brand;// ����� ������
	string Color;// ���� ������
	int Year;// ��� �������
	bool IsAvaible; // ������� �������
};

struct ISSUANCE { // ���������� � �������� �� ������
	string ClientLicense; //� ������������� ������������� (RR AA NNNNNN)
	string AutoNum;//� ������ (ANNNAA-NN)
	string DateOfHire;// ���� ������
	string DateOfReturn;// ���� ��������
};

//��������:
//�������� ������ � �������
bool LicenseNumCheck(string Lnum){// �������� � ������������� �������������
	bool flag = false;
		if (Lnum.length() == 12) {
		if ((Lnum[0] >= '0' && Lnum[0] <= '9') && (Lnum[1] >= '0' && Lnum[1] <= '9') && Lnum[2] == ' ')
			if (Lnum[3] == '�' || Lnum[3] == '�' || Lnum[3] == '�' || Lnum[3] == '�' || Lnum[3] == '�' || Lnum[3] == '�' || Lnum[3] == '�'
				|| Lnum[3] == '�' || Lnum[3] == '�' || Lnum[3] == '�' || Lnum[3] == '�' || Lnum[3] == '�')
				if (Lnum[4] == '�' || Lnum[4] == '�' || Lnum[4] == '�' || Lnum[4] == '�' || Lnum[4] == '�' || Lnum[4] == '�' || Lnum[4] == '�'
					|| Lnum[4] == '�' || Lnum[4] == '�' || Lnum[4] == '�' || Lnum[4] == '�' || Lnum[4] == '�')
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
//�������� ������ �� ����������
bool NumCheck(string num){
	bool flag = false;
	if (num.length() == 9)
	if (num[0] == '�' || num[0] == '�' || num[0] == '�' || num[0] == '�' || num[0] == '�' || num[0] == '�' || num[0] == '�'
		|| num[0] == '�' || num[0] == '�' || num[0] == '�' || num[0] == '�' || num[0] == '�')
		if ((num[1] >= '0' && num[1] <= '9') && (num[2] >= '0' && num[2] <= '9') && (num[3] >= '0' && num[3] <= '9'))
			if (num[4] == '�' || num[4] == '�' || num[4] == '�' || num[4] == '�' || num[4] == '�' || num[4] == '�' || num[4] == '�'
				|| num[4] == '�' || num[4] == '�' || num[4] == '�' || num[4] == '�' || num[4] == '�')
				if (num[5] == '�' || num[5] == '�' || num[5] == '�' || num[5] == '�' || num[5] == '�' || num[5] == '�' || num[5] == '�'
					|| num[5] == '�' || num[5] == '�' || num[5] == '�' || num[5] == '�' || num[5] == '�')
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
//�������� ������ � ��������
bool DateCheck(string date){
	bool flag = false;
	if (date.length() == 10)
		if ((date[0] >= '0' && date[0] <= '9') && (date[1] >= '0' && date[1] <= '9') && date[2] == '.')
			if ((date[3] >= '0' && date[3] <= '9') && (date[4] >= '0' && date[4] <= '9') && date[5] == '.')
				if ((date[6] >= '0' && date[6] <= '9') && (date[7] >= '0' && date[7] <= '9') && (date[8] >= '0' && date[8] <= '9') && (date[9] >= '0' && date[9] <= '9'))
					flag = true;
	return flag;
}
//����� ��������
bool StrCheck(string str){ // �������� �� ������������ ���� string 
	if (cin.good())
		return true;
	else return false;
}
//������ � ������� (������������ ����� ����������� �������)
struct ClientTree { //��������� ������ ������
	CLIENT cl;
	int h;
	ClientTree * left;
	ClientTree * right;
	ClientTree(CLIENT c) { cl = c; left = right = NULL; h = 1; }
};
int h(ClientTree* OurTree) { // ����� ������ ����
	return OurTree ? OurTree->h : 0;
}
int bFactor(ClientTree* OurTree) {// ����� ���������� ������������������
	return h(OurTree->right) - h(OurTree->left);
}
void FixH(ClientTree* OurTree) {// ������������� ������ ����
	int hl = h(OurTree->left);
	int hr = h(OurTree->right);
	OurTree->h = (hl > hr ? hl : hr) + 1;
}
ClientTree* RotateRight(ClientTree* OurTree) { // ������ �������
	ClientTree* q = OurTree->left;
	OurTree->left = q->right;
	q->right = OurTree;
	FixH(OurTree);
	FixH(q);
	return q;
}
ClientTree* RotateLeft(ClientTree* OurTree) {// ����� ������� 
	ClientTree* p = OurTree->right;
	OurTree->right = p->left;
	p->left = OurTree;
	FixH(OurTree);
	FixH(p);
	return p;
}
ClientTree* Balance(ClientTree* OurTree) {// ������������ ���� 
	FixH(OurTree);
	if (bFactor(OurTree) == 2) {
		if (bFactor(OurTree->right) < 0)
			OurTree->right = RotateRight(OurTree->right);// ������� ����� �������
		return RotateLeft(OurTree);
	}
	if (bFactor(OurTree) == -2) {
		if (bFactor(OurTree->left) > 0)
			OurTree->left = RotateLeft(OurTree->left); //������� ������ �������
		return RotateRight(OurTree);
	}
	return OurTree;
}
ClientTree* RegClient(ClientTree* OurTree,CLIENT cl) {// ������� ���� � ������
	if (!OurTree) return new ClientTree(cl);
	if (cl.LicenseNum < OurTree->cl.LicenseNum)
		OurTree->left = RegClient(OurTree->left, cl);
	else
		OurTree->right = RegClient(OurTree->right, cl);
	return Balance(OurTree);
}
ClientTree* FindMin(ClientTree* OurTree) {// ����� ���� � ����������� ������ � ������ 
	return OurTree->left ? FindMin(OurTree->left) : OurTree;
}
ClientTree* RemoveMin(ClientTree* OurTree) {// �������� ���� � ����������� ������ �� ������
	if (OurTree->left == 0)
		return OurTree->right;
	OurTree->left = RemoveMin(OurTree->left);
	return Balance(OurTree);
}
ClientTree* FindByLic(ClientTree* OurTree, string lnum) {//����� �� ������ ������������� �������������
	if (!OurTree) return NULL;// ���� ����� ��������� - ���������� NULL
	if (lnum == OurTree->cl.LicenseNum)// ��������� ���������������� ������, ���� ������ ����� �� ���������� ������
		return OurTree;
	if (lnum < OurTree->cl.LicenseNum)
		return FindByLic(OurTree->left, lnum);
	else
		return FindByLic(OurTree->right, lnum);

}
bool FindInText(string text, string word) {// ����� ���������� ����� � ������
	bool flag = false;// ��-��������� ���������� ����
	if (text.length() >= word.length()) {// ���� ����� ����� ������, ��� ������
		for (int i = 0; i < text.length(); i++) { // ���� ���������� ������� ������� ����� � i-�� ������� ������
			int count = 1;
			if (text[i] == word[0])
				for (int j = 1; j < word.length(); j++) {// ���� ����� - ������� ���������� ���������� �������� ������
					if (text[i + j] == word[j])
						count++;
				}
			if (count == word.length())
			{//���� ����� ���������� ������ ����� ����� ����� - ��������� ������ ����� � ���������� ������
				flag = true;
				break;
			}
		}
	}
	return flag;
}
void FindByName(ClientTree* OurTree, string nameToFind, int &count) {// ����� �� ����� ��� ��� ����������
	if (OurTree) {
		FindByName(OurTree->left, nameToFind, count);
		FindByName(OurTree->right, nameToFind, count);// ����������� �������� ����� ������
		if (FindInText(OurTree->cl.Name, nameToFind))// ���� ���������� �������
		{// ������� ������ � �������
			cout << OurTree->cl.LicenseNum << "\t" << OurTree->cl.Name << "\t" << OurTree->cl.Adress << endl; count++;
		}
	}
}
void FindByAdress(ClientTree* OurTree, string adressToFind, int &count) {// ����� �� ������ ��� ��� ����������
	if (OurTree) {
		FindByAdress(OurTree->left, adressToFind, count);
		FindByAdress(OurTree->right, adressToFind, count);// ����������� �������� ����� ������
		if (FindInText(OurTree->cl.Adress, adressToFind))// ���� ���������� �������
		{// ������� ������ � �������
			cout << OurTree->cl.LicenseNum << "\t" << OurTree->cl.Name << "\t" << OurTree->cl.Adress << endl; count++;
		}
	}
}
ClientTree* DelClient(ClientTree* OurTree, string lnum) {// �������� ���� �� ������
	if (!OurTree) return NULL;// ���� �� ����� ������� ��� ������ ������ - ������� NULL
	if (lnum < OurTree->cl.LicenseNum)// ����� �� ������
		OurTree->left = DelClient(OurTree->left, lnum);
	else if (lnum > OurTree->cl.LicenseNum)
		OurTree->right = DelClient(OurTree->right, lnum);
	else {// ��� ����������
		ClientTree* l = OurTree->left;// �������� ��������� �� ������� � ������ ��������
		ClientTree* r = OurTree->right;
		delete OurTree;// ������� �������
		if (!r) return l;// ���� ������ ������� ����������� - ������� ��������� �� �����
		ClientTree* min = FindMin(r);// ����� - ����� ����������� ������� � ������ ��������� � ������� ��� �������� 
		min->right = RemoveMin(r);
		min->left = l;
		OurTree = min;
		return Balance(OurTree);// �������������� ������
	}
	return Balance(OurTree);
}
void Bypass(ClientTree*OurTree) { // ����� ������ �� ������� ��������� ������
	if (OurTree) {
		Bypass(OurTree->left);
		Bypass(OurTree->right);
		cout << OurTree->cl.LicenseNum << "\t" << OurTree->cl.Name << "\t" << OurTree->cl.Adress << endl;
	}
}
void DelClientTree(ClientTree*OurTree) {// ������� ������
	if (OurTree->left) { // ������ �� ����� �������� � �� ��������
		DelClientTree(OurTree->left);
	}
	else
		delete OurTree->left;
	if (OurTree->right) // ������ �� ������ �������� � �� ��������
		DelClientTree(OurTree->right);
	else
		delete OurTree->right;

	delete OurTree;
	OurTree = NULL;
}
void SaveTree(ClientTree*OurTree, ofstream &save) {// ���������� ������ � �������� � ���� clienttree.txt (� ������� ��������� ������)
	if (OurTree) {
		SaveTree(OurTree->left, save);
		SaveTree(OurTree->right, save);
		if (StrCheck(OurTree->cl.Adress)&& LicenseNumCheck(OurTree->cl.LicenseNum)&&StrCheck(OurTree->cl.Name)&& PassportCheck(OurTree->cl.Passport))
			save << OurTree->cl.Adress << "\t" << OurTree->cl.LicenseNum << "\t" << OurTree->cl.Name << "\t" << OurTree->cl.Passport << "\n";
	}
}
ClientTree* LoadTree(ClientTree * OurTree){// �������� ������ � �������� �� ����� clienttree.txt
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
//������ �� �������
struct IssuanceList {// ��������� ������ ���������
	ISSUANCE is;
	IssuanceList *next;
	IssuanceList *prev;
};
IssuanceList* SortList(IssuanceList* head) //���������� ������
{
	int NumOfElem = 0;
	IssuanceList* tmp = head;
	while(tmp->next)// ������� ����� ��������� � ������
	{
		tmp = tmp->next; NumOfElem++;
	}
	NumOfElem++;
	if (NumOfElem > 1) {
		for (int i = NumOfElem - 1; i > 0; i--) {// ������ �������� ������ �� ������(������ ����������������� �����)
			IssuanceList* Max = head, *tmp2 = head;
			for (int j = 0; j <= i; j++) {// ���� ������������ �������� � ����������������� �����
				if (tmp2->is.AutoNum > Max->is.AutoNum)
					Max = tmp2;
				tmp2 = tmp2->next;
			}
			ISSUANCE tmpToReshuffle = tmp->is;// ������ ������ ������������� � �������� ���������
			tmp->is = Max->is;				  // (����� �� ������������� ���������)
			Max->is = tmpToReshuffle;
			tmp = tmp->prev;
		}
	}
	return head;
}
IssuanceList* AddToList(IssuanceList* head, string license, string num, string DoH, string DoR) // ���������� � ������
{	//������� ����� ������� ������
	IssuanceList* NewElem = new IssuanceList;
	NewElem->is.AutoNum = num;
	NewElem->is.ClientLicense = license;
	NewElem->is.DateOfHire = DoH;
	NewElem->is.DateOfReturn = DoR;
	NewElem->next = NULL;
	NewElem->prev = NULL;
	if (!head) //���� ������ ���� - ������ ����� ������� ������� ������
		head = NewElem;
	else {// ����� - ��������� ������� � ����� ������
		IssuanceList*tmp = head;
		while (tmp->next) 
			tmp = tmp->next;
		tmp->next = NewElem;
		NewElem->prev = tmp;
		NewElem->next = NULL;
	}
	return SortList(head);// ��������� � ���������� ��������� �� ������ ������
}
IssuanceList* SearchInListByNum(IssuanceList*head, string NumToSearch) {// ����� �� ������ ����
	while ( head != NULL && head->is.AutoNum != NumToSearch) 
		head = head->next;
	return head;
}
IssuanceList* SearchInListByLic(IssuanceList*head, string LicToSearch) {// ����� �� ������ ������������� �������������
	while (head != NULL && head->is.ClientLicense != LicToSearch)
		head = head->next;
	return head;
}
IssuanceList* DelFromList(IssuanceList*head, string NumToSearch){// �������� �� ������ ���� 
	IssuanceList * tmp = SearchInListByNum(head, NumToSearch);// ������������ ����� �� ������
	tmp->prev->next = tmp->next;// ��������� ���������� � ��������� �������� ������
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	delete tmp;// ������� ������� ������� � �������� ���������
	tmp = NULL;
	return SortList(head);// �������� ���������� � ���������� ��������� �� ������ ������
}
void SaveList(IssuanceList* head) {// ���������� ������ � ���� "issuances.txt"
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
//������ � ���-��������
int HashIt(string auNum) {//���-�������
	return  abs((int)(pow((int)auNum[0], 3) + pow((int)auNum[1], 3) + pow((int)auNum[2], 3) + pow((int)auNum[3], 3) + pow((int)auNum[4], 3) +
		pow((int)auNum[5], 3) + pow((int)auNum[6], 3) + pow((int)auNum[7], 3) + pow((int)auNum[8], 3) + pow((int)auNum[9], 3))) % segNum;
}
void create(AUTO ar[segNum]){// ������� ��������� ������ ���-�������
	for (int i = 0; i < segNum; i++)
	{
		ar[i].Num = "";
		ar[i].Brand = "";
		ar[i].Color = "";
		ar[i].Year = -1;
		ar[i].IsAvaible = false;
	}
}
void addHashTable(AUTO ar[segNum], AUTO machine, bool& isFull) {// ������� ���������� ������ � ���-�������
	int attempt = 0, k = 0, l = 0;
	int i = HashIt(machine.Num);
	if (ar[i].Num == "")// ���� �������� ��� - ����������
	{
		ar[i].Num = machine.Num;
		ar[i].Brand = machine.Brand;
		ar[i].Color = machine.Color;
		ar[i].Year = machine.Year;
		ar[i].IsAvaible = machine.IsAvaible;
	}
	else{// ���� �������� ���� - ������ �������� �����������, ���� �� ������ ��������� �����, ��� �� ������, ��� ������� �����
		do{
			k++;
			if (k > attNum){
				isFull = true;
			}
			attempt = (i+k*3)%segNum;
		} while (ar[attempt].Num != ""||isFull);
		ar[attempt].Num = machine.Num;// ���������� �� ������  �����
		ar[attempt].Brand = machine.Brand;
		ar[attempt].Color = machine.Color;
		ar[attempt].Year = machine.Year;
		ar[attempt].IsAvaible = machine.IsAvaible;
	}
}
int searchByNum(AUTO ar[segNum], string num) {// ����� �� ������ ����������
	int i = HashIt(num), k = 0, attempt = 0;
	int resInd = -1;
	if (ar[i].Num != num) {// ���� ��� ������� ���� ��������
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
void searchByBrand(AUTO ar[segNum], string brand) {// �������� ����� ����������� �� �����
	for (int i = 0; i < segNum; i++) {
		if (ar[i].Brand == brand)
			cout << ar[i].Num << " " << ar[i].Brand << " " << ar[i].Color << " " << ar[i].Year << endl;
	}
}
bool removeHashTable(AUTO ar[segNum], string num){// ������� �������� ������ �� ���-�������
	bool flag = false;
	int i = searchByNum(ar, num);// ����� ������� ��������
		if (i != -1)// ������� ������(���� ������� ������)
		{
			flag = true;
			ar[i].Num = "";
			ar[i].Brand = "";
			ar[i].Color = "";
			ar[i].Year = -1;
			ar[i].IsAvaible = false;
		}
	return flag;// ���������� ����� �� ��������
}
bool deleteHashTable(AUTO ar[segNum]){//�������� ���� ������ �� ���-�������
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
bool isTableEmpty(AUTO ar[segNum]){// �������� ���-������� �� �������
	int count = 0;
	for (int i = 0; i < segNum; i++)
		if (ar[i].Num != "")
			count++;
	if (count == 0)// ���� � ������� ��� �������� ������
		return true;
	else
		return false;
}
void showTable(AUTO ar[segNum]) {//������� ����������� �������
	for (int i = 0; i < segNum; i++)
		if (ar[i].Num != "")
			cout << ar[i].Num << "\t" << ar[i].Brand << "\t" << ar[i].Color << endl;
}
void saveHashTable(AUTO ar[segNum]){// ������� ���������� ������� � ���� "autotable.txt"
	ofstream save("autotable.txt", ios_base::out | ios_base::trunc);
	for (int i = 0; i < segNum; i++) {
		save << ar[i].Num << "\t" << ar[i].Brand << "\t" << ar[i].Color << "\t" << ar[i].Year << "\t" <<ar[i].IsAvaible << endl;
	}
}
void loadHashTable(AUTO ar[segNum]) {// ������� �������� ������� �� ����� "autotable.txt"
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
	ClientTree *  Tree = NULL;// ������������� ������
	IssuanceList * head = NULL;// ������
	AUTO HashTable[segNum];// ���-�������
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int selector = -1;
	// �������� ������ �� ������
	Tree = LoadTree(Tree);// ������
	head = LoadList(head);// ������
	loadHashTable(HashTable);// ���-�������
	// ����
	while (selector)
	{
		int  ch = -1;
		divider;
		cout << "������� ����:\n"
			<< "1 - ������ � ����������� � ��������\n"
			<< "2 - ������ � ����������� �� �����������\n"
			<< "3 - ������ � ���������� � �������\n"
			<< "0 - ����� �� ���������\n";
		divider;
		cin >> selector;
		system("cls");
		switch (selector) {
		default:
			cout << "������������ �����\n";
			break;
		case 1:
			while (ch) {
				divider;
				cout << "���� ������ � ����������� � ��������:\n"
					<< "1 - ����������� ������ �������\n"
					<< "2 - ������ ������� � ������������\n"
					<< "3 - �������� ���� ������������������ ��������\n"
					<< "4 - ������� ������ � ��������\n"
					<< "5 - ����� ������� �� � ������������� �������������\n"
					<< "6 - ����� ������� �� ���\n"
					<< "7 - ����� ������� �� ������\n"
					<< "0 - � ������� ����\n";
				divider;
				cin >> ch;
				system("cls");
				CLIENT cl;
				IssuanceList* flist = NULL;
				ClientTree *  ftr = NULL;
				int flag = 0;
				switch (ch) {
				default:
					cout << "������������ �����\n";
					break;
				case 1://����������� ������ �������
					system("cls");
					divider;
					cout << "����������� ������ �������";// �����
					divider;
					cout << "������� ����� ������������� �������������: ";//���������� ������ �� ������� � ��������
					cin.ignore(cin.rdbuf()->in_avail());
					getline(cin, cl.LicenseNum);
					while (!LicenseNumCheck(cl.LicenseNum))
					{
						cout << "������������ ���� ������ ������������� �������������, ��������� �������\n";
						cin.ignore(cin.rdbuf()->in_avail());
						getline(cin, cl.LicenseNum);
					}
					cout << "������� ���: ";
					cin.ignore(cin.rdbuf()->in_avail());
					getline(cin, cl.Name);
					while (!StrCheck(cl.Name))
					{
						cout << "������������ ���� ���, ��������� �������\n";
						cin.ignore(cin.rdbuf()->in_avail());
						getline(cin, cl.Name);
					}
					cout << "������� ���������� ������ (����� � �����): ";
					cin.ignore(cin.rdbuf()->in_avail());
					getline(cin, cl.Passport);
					while (!PassportCheck(cl.Passport)) {
						cout << "������������ ���� ���������� ������, ��������� �������\n";
						cin.ignore(cin.rdbuf()->in_avail());
						getline(cin, cl.Passport);
					}
					cout << "������� �����: ";
					cin.ignore(cin.rdbuf()->in_avail());
					getline(cin, cl.Adress);
					while (!StrCheck(cl.Adress)) {
						cout << "������������ ���� ������, ��������� �������\n";
						cin.ignore(cin.rdbuf()->in_avail());
						getline(cin, cl.Adress);
					}
					Tree = RegClient(Tree, cl);// ������ ������� ���������� �������� � ������
					break;
				case 2:
					system("cls");
					divider;
					cout << "������ ������� � ������������";// �����
					divider;
					cout << "������� ����� ������������� �������������: ";//���������� ������ �� ������� � ��������
					cin.ignore(cin.rdbuf()->in_avail());
					getline(cin, cl.LicenseNum);
					while (!LicenseNumCheck(cl.LicenseNum))
					{
						cout << "������������ ���� ������ ������������� �������������, ��������� �������\n";
						cin.ignore(cin.rdbuf()->in_avail());
						getline(cin, cl.LicenseNum);
					}
					Tree = DelClient(Tree, cl.LicenseNum);// ������ ������� �������� �������� �� ������
					break;
				case 3:
					system("cls");
					divider;
					cout << "�������� ���� ������������������ ��������";// �����
					divider;
					if (Tree)// ����� ������ �� ��������� ������ ��� ��������� � ������� ������
						Bypass(Tree);
					else
						cout << "���������� � �������� �����������\n";
					break;
				case 4:
					system("cls");
					divider;
					cout << "������� ������ � ��������";//�����
					divider;
					DelClientTree(Tree);//����� ������� ������� ������
					Tree = NULL;
					cout << "������ ������� �������\n";
					break;
				case 5:
					system("cls");
					divider;
					cout << "����� ������� �� � ������������� �������������";// �����
					divider;
					cout << "������� ����� ������������� �������������:";//���������� ������ �� ������� � ��������
					cin.ignore(cin.rdbuf()->in_avail());
					getline(cin, cl.LicenseNum);
					while (!LicenseNumCheck(cl.LicenseNum))
					{
						cout << "������������ ���� ������ ������������� �������������, ��������� �������\n";
						cin.ignore(cin.rdbuf()->in_avail());
						getline(cin, cl.LicenseNum);
					}
					ftr = FindByLic(Tree, cl.LicenseNum);
					cout << "��������� ������:\n";
					if (ftr) {// ����� ��������� ������ ��� ��������� �� ����������
						cout << ftr->cl.LicenseNum << "\t" << ftr->cl.Name << "\t" << ftr->cl.Adress << endl;
						flist = SearchInListByLic(head, ftr->cl.LicenseNum);
						cout << "����� ��������� ����������: ";
						if (flist)
							cout << flist->is.AutoNum << endl;
						else cout << "��� �������� �����������\n";
					}
					else
						cout << "������ �� ������\n";
					break;
				case 6:
					system("cls");
					divider;
					cout << "����� ������� �� ���(��� ���������� ���)";// �����
					divider;
					cout << "������� ���: ";//���������� ������ �� ������� � ��������
					cin.ignore(cin.rdbuf()->in_avail());
					getline(cin, cl.Name);
					while (!StrCheck(cl.Name))
					{
						cout << "������������ ���� ���, ��������� �������\n";
						cin.ignore(cin.rdbuf()->in_avail());
						getline(cin, cl.Name);
					}
					cout << "���������� ������: \n";
					FindByName(Tree, cl.Name, flag);// ����� ������ �� �����
					if (!flag)
						cout << "�������� � ������ ��� �� �������\n";
					break;
				case 7:
					system("cls");
					divider;
					cout << "����� ������� �� ������(��� ���������� ������)";//�����
					divider;
					cout << "������� �����: ";//���������� ������ �� ������� � ��������
					cin.ignore(cin.rdbuf()->in_avail());
					getline(cin, cl.Adress);
					while (!StrCheck(cl.Adress))
					{
						cout << "������������ ���� ������, ��������� �������\n";
						cin.ignore(cin.rdbuf()->in_avail());
						getline(cin, cl.Adress);
					}
					cout << "���������� ������: \n";
					FindByAdress(Tree, cl.Adress, flag);//����� ������ �� ������
					if (!flag)
						cout << "�������� � ����� ������� �� �������\n";
					break;
				case 0:
					break;
				}
			}
			break;
		case 2:
			while (ch) {
				divider;
				cout << "���� ������ � ����������� �� �����������:\n"
					<< "1 - ���������� ������ ����������\n"
					<< "2 - �������� �������� �� ����������\n"
					<< "3 - �������� ���� ��������� �����������\n"
					<< "4 - ������� ������ �� �����������\n"
					<< "5 - ����� ���������� �� ���������������� ������\n"
					<< "6 - ����� ���������� �� �����\n"
					<< "7 - ����������� �������� ���������� � ������\n"
					<< "8 - ����������� �������� ���������� �� �������\n"
					<< "0 - � ������� ����\n";
				divider;
				cin >> ch;
				system("cls");
				bool flag = false, isFull = false;
				int i = -1;
				AUTO m;
				switch (ch) {
				default:
					cout << "������������ �����\n";
					break;
				case 1:
					system("cls");
					divider;
					cout << "���������� ������ ���������� � �������";//�����
					divider;
					cout << "������� ����� ����������: ";//���������� ������ �� ������� � ��������
					cin.ignore(cin.rdbuf()->in_avail());
					getline(cin, m.Num);
					while (!NumCheck(m.Num)) {
						cout << "����� ���������� ������ �����������. ��������� �������: ";
						cin.ignore(cin.rdbuf()->in_avail());
						getline(cin, m.Num);
					}
					cout << "������� ����� ������: ";
					cin.ignore(cin.rdbuf()->in_avail());
					getline(cin, m.Brand);
					while (!StrCheck(m.Brand)) {
						cout << "����� ������ ������� �����������. ��������� �������: ";
						cin.ignore(cin.rdbuf()->in_avail());
						getline(cin, m.Brand);
					}
					cout << "������� ���� ������: ";
					getline(cin, m.Color);
					while (!StrCheck(m.Color)) {
						cout << "���� ������ ������ �����������. ��������� �������: ";
						cin.ignore(cin.rdbuf()->in_avail());
						getline(cin, m.Color);
					}
					cout << "������� ��� ������� ������: ";
					cin >> m.Year;
					while (!YearCheck(m.Year)) {
						cout << "��� ������� ������ ������ �����������. ��������� �������: ";
						cin >> m.Year;
					}
					m.IsAvaible = true;
					if(!isFull)//���� ������� �� ����� - �������� ������ � �������
						addHashTable(HashTable, m, isFull);
					else cout << "������� �����, ���������� ����������!\n";
					break;
				case 2:
					system("cls");
					divider;
					cout << "�������� �������� �� ����������";// �����
					divider;
					cout << "������� ����� ����������: ";//���������� ������ �� ������� � ��������
					cin.ignore(cin.rdbuf()->in_avail());
					getline(cin, m.Num);
					while (!NumCheck(m.Num)) {
						cout << "����� ���������� ������ �����������. ��������� �������: ";
						cin.ignore(cin.rdbuf()->in_avail());
						getline(cin, m.Num);
					}
					flag = removeHashTable(HashTable, m.Num);// ����� ������� ��������
					if (flag)// ��������� �� �������� ��� ���������� ��������
						cout << "���������� � ������� \"" << m.Num << "\" ������� ������ �� ������\n";
					else
						cout << "���������� � ������� \"" << m.Num << "\" ����������� � ������\n";
					break;
				case 3:
					system("cls");
					divider;
					cout << "�������� ���� ��������� �����������";//�����
					divider;
					if (isTableEmpty(HashTable))//���� ������� �� �����
						cout << "������ �� ����������� �� �������\n";
					else//������� ������� ������ �������
						showTable(HashTable);
					break;
				case 4:
					system("cls");
					divider;
					cout << "������� ������ �� �����������";//�����
					divider;
					flag = deleteHashTable(HashTable);//����� ������� ������� �������
					if (flag)// ����� ��������� �� ������� 
						cout << "������� ������� �������\n";
					else
						cout << "������� ��� �����\n";
					break;
				case 5:
					system("cls");
					divider;
					cout << "����� ���������� �� ���������������� ������";//�����
					divider;
					cout << "������� ����� ����������: ";//���������� ������ �� ������� � ��������
					cin.ignore(cin.rdbuf()->in_avail());
					getline(cin, m.Num);
					while (!NumCheck(m.Num)) {
						cout << "����� ���������� ������ �����������. ��������� �������: ";
						cin.ignore(cin.rdbuf()->in_avail());
						getline(cin, m.Num);
					}
					cout << "��������� ������\n";
					i = searchByNum(HashTable, m.Num);//����� ������� ������ �� ������
					if (i != -1)//���� ���� ���� - ������� ������ � ���
					{
						cout << HashTable[i].Num << " " << HashTable[i].Brand << " " << HashTable[i].Color << endl;
						cout << "������ � ������ ���������� � ������: \n";
						if (HashTable[i].IsAvaible)
							cout << "���������� ��������.\n";
						else
							cout << "���������� ����� ������� � ������� ������������� ������������� \"" << SearchInListByNum(head, HashTable[i].Num)->is.ClientLicense << "\"\n";
					}
					else
						cout << "���������� � ����� ������� �� ������\n";
					break;
				case 6:
					system("cls");
					divider;
					cout << "����� ���������� �� �����";//�����
					divider;
					cout << "������� ����� ������: ";//���������� ������ �� ������� � ��������
					cin.ignore(cin.rdbuf()->in_avail());
					getline(cin, m.Brand);
					while (!StrCheck(m.Brand)) {
						cout << "����� ������ ������� �����������. ��������� �������: ";
						cin.ignore(cin.rdbuf()->in_avail());
						getline(cin, m.Brand);
					}
					searchByBrand(HashTable, m.Brand);// ����� ������� ������ �� �����
					break;
				case 7:
					system("cls");
					divider;
					cout << "����������� �������� ���������� � ������";//�����
					divider;
					cout << "������� ����� ����������: ";//���������� ������ �� ������� � ��������
					cin.ignore(cin.rdbuf()->in_avail());
					getline(cin, m.Num);
					while (!NumCheck(m.Num)) {
						cout << "����� ���������� ������ �����������. ��������� �������: ";
						cin.ignore(cin.rdbuf()->in_avail());
						getline(cin, m.Num);
					}
					i = searchByNum(HashTable, m.Num);
					if (i != -1) {//���� ���� ����
						if (HashTable[i].IsAvaible) {//���� ���� ��������
							HashTable[i].IsAvaible = false;// ����������� ���� �� "����������"
							cout << "�������� ���������� � ������ ����������������\n";//������� ��������� �� ������
						}
						else// ����� - �������� � ���, ��� ���� ��� ����������
							cout << "������ ���������� �� �������� ��� �������� � ������\n";
					}
					else {// ����� - ������� ��������� � ���, ��� ���� �� �������
						cout << "���������� � ����� ������� �� ������\n";
					}
					break;
				case 8:
					system("cls");
					divider;
					cout << "����������� �������� ���������� �� �������";// �����
					divider;
					cout << "������� ����� ����������: ";//���������� ������ �� ������� � ��������
					cin.ignore(cin.rdbuf()->in_avail());
					getline(cin, m.Num);
					while (!NumCheck(m.Num)) {
						cout << "����� ���������� ������ �����������. ��������� �������: ";
						cin.ignore(cin.rdbuf()->in_avail());
						getline(cin, m.Num);
					}
					i = searchByNum(HashTable, m.Num);
					if (i != -1) {
						if (!HashTable[i].IsAvaible) {//���� ���� ����
							if (SearchInListByNum(head, HashTable[i].Num) == NULL) {//���� ���� ���������� � �� � ������
								HashTable[i].IsAvaible = true;//���������� ���� �� "��������"
								cout << "�������� ���������� �� ������� ����������������\n";// ������� ��������� �� ������
							}
							else cout << "���������� ��������� � ������, � �� � �������.\n";// ����� - ������� ��������������
						}
						else
							cout << "������ ���������� ��� ��������\n";// ����� - ��������� � ���, ��� ���� ��� ��������
					}
					else {
						cout << "���������� � ����� ������� �� ������\n";
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
				cout << "���� ������ � ���������� � �������:\n"
					<< "1 - ����������� ������ ������� ���������� �� ������\n"
					<< "2 - ����������� �������� ���������� �� �������\n"
					<< "0 - � ������� ����\n";
				divider;
				string lnum, aunum, DoH,DoR;
				cin >> ch;
				system("cls");
				switch (ch) {
				default:
					cout << "������������ �����\n";
					break;
				case 1:
					divider;
					cout << "����������� ������ ������� ���������� �� ������";//�����
					divider;
					cout << "������� ����� ������������� �������������: ";//���������� ������ �� ������� � ��������
					cin.ignore(cin.rdbuf()->in_avail());
					getline(cin, lnum);
					while (!LicenseNumCheck(lnum)|| !FindByLic(Tree,lnum))
					{
						if (!LicenseNumCheck(lnum)) {
							cout << "������������ ���� ������ ������������� �������������, ��������� �������\n";
							cin.ignore(cin.rdbuf()->in_avail());
							getline(cin, lnum);
						}else {
							cout << "������ � ����� ������� ������������� ������������� ����������� � ����, ��������� �������\n";
							cin.ignore(cin.rdbuf()->in_avail());
							getline(cin, lnum);
						}
					}
					cout << "������� ����� ����������: ";
					cin.ignore(cin.rdbuf()->in_avail());
					getline(cin, aunum);
					while (!NumCheck(aunum) || (searchByNum(HashTable,aunum) == -1)) {
						if (!NumCheck(aunum)) {
							cout << "����� ���������� ������ �����������. ��������� �������: ";
							cin.ignore(cin.rdbuf()->in_avail());
							getline(cin, aunum);
						}else{
							cout << "���������� � ������ ��������������� ������� �� ���������� � ����. ��������� �������: ";
							cin.ignore(cin.rdbuf()->in_avail());
							getline(cin, aunum);
						}
					}
					cout << "������� ���� ������ ����������: ";
					cin.ignore(cin.rdbuf()->in_avail());
					getline(cin, DoH);
					while (!DateCheck(DoH)) {
						cout << "���� ������ ���������� ������� �����������. ��������� �������: ";
						cin.ignore(cin.rdbuf()->in_avail());
						getline(cin, DoH);
					}
					cout << "������� ���� �������� ����������: ";
					cin.ignore(cin.rdbuf()->in_avail());
					getline(cin, DoR);
					while (!DateCheck(DoR)) {
						cout << "���� �������� ���������� ������� �����������. ��������� �������: ";
						cin.ignore(cin.rdbuf()->in_avail());
						getline(cin, DoR);
					}
					if (HashTable[searchByNum(HashTable, aunum)].IsAvaible) {//���� ���� �������� ��� ������
						head = AddToList(head, lnum, aunum, DoH, DoR);// ���������������� �������
						cout << "������ ���������� ������� ����������������\n";
						HashTable[searchByNum(HashTable, aunum)].IsAvaible = false;
					}
					else// ����� - ������� ��������������
						cout << "���������� � ������� \"" << aunum <<"\"�� �������� ��� ������\n";
					break;
				case 2:
					divider;
					cout << "����������� �������� ���������� �� �������";// �����
					divider;
					cout << "������� ����� ����������: ";//���������� ������ �� ������� � ��������
					cin.ignore(cin.rdbuf()->in_avail());
					getline(cin, aunum);
					while (!NumCheck(aunum) || (searchByNum(HashTable, aunum) == -1)) {
						if (!NumCheck(aunum)) {
							cout << "����� ���������� ������ �����������. ��������� �������: ";
							cin.ignore(cin.rdbuf()->in_avail());
							getline(cin, aunum);
						}
						else {
							cout << "���������� � ������ ��������������� ������� �� ���������� � ����. ��������� �������: ";
							cin.ignore(cin.rdbuf()->in_avail());
							getline(cin, aunum);
						}
					}
					if (!HashTable[searchByNum(HashTable, aunum)].IsAvaible&& (SearchInListByNum(head,aunum)!= NULL)) {//���� ���� � ������
						HashTable[searchByNum(HashTable, aunum)].IsAvaible = true;//���������� ����������� ����
						DelFromList(head, aunum);// ������� ������� �� ������
						cout << "������� ���������� ������� ���������������\n";
					}else
						cout << "���������� � ������� \"" << aunum << "\"� ������� ��� ��� ��������\n";
					break;
				case 0:
					break;
				}
			}
			break;
		case 0:
			divider;
			cout << "������ ���������\n";
			divider;
			break;
		}
	}
	//���������� ������:
	ofstream save("clienttree.txt", ios_base::out | ios_base::trunc);
	SaveTree(Tree, save);// ������
	SaveList(head);// ������
	saveHashTable(HashTable);// ���-�������
	// ������� ������
	if (Tree) {// �� ������
		DelClientTree(Tree);
		Tree = NULL;
	}
	while (head) {// �� ������
		IssuanceList*del = head;
		head = head->next;
		delete del;
		del = NULL;
	}
	head = NULL;
	system("pause");
}
