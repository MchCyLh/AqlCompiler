#pragma once

#include "outputTable.h"
using namespace std;


void fengexian(int length) {
	cout << "+";
	for (int i = 0; i < length; i++) {
		cout << "-";
	}
}

//��ӡ�ָ���
void totalfengexian(int* maxlen, int colnumsize) {
	for (int i = 0; i < colnumsize; i++) {
		fengexian(maxlen[i]);
	}
	cout << "+" << endl;
}

//�õ����ֵĳ���
int getNumLength(int num) {
	int len = 0;
	do {
		len++;
		num /= 10;
	} while (num / 10 > 0);
	return len;
}

//����ÿ��vector������г���
int getMaxLength(vector<Record_Cell> v) {
	int i;
	int maxlength = -1;
	for (i = 0; i < v.size(); i++) {
		//����������ֺ�����֮��ĳ���
		int temp = v[i].content.length() + 4 + getNumLength(v[i].begin) + getNumLength(v[i].end);
		if (temp > maxlength)
			maxlength = temp;
	}
	return maxlength + 2;  //ǰ���������ո��2
}


void outputTable(string tablename, Table &table) {
	int colnumsize = table.size();
	cout << "View: " << tablename << endl;
	map<string, vector<Record_Cell> >::iterator it;
	string* colnumname = new string[colnumsize];   //����
	vector<Record_Cell>* v = new vector<Record_Cell>[colnumsize];   //ÿһ�е�Ԫ��
	int* maxlen = new int[colnumsize];
	int index = 0;
	int maxVectorSize = 0;
	for (it = table.begin(); it != table.end(); it++) {
		v[index] = it->second;
		colnumname[index] = it->first;
		if (v[index].size() > maxVectorSize)
			maxVectorSize = v[index].size();
		maxlen[index] = getMaxLength(v[index]);
		index++;
	}

	int i, j, k;

	totalfengexian(maxlen, colnumsize);

	//��ӡ������
	for (i = 0; i < colnumsize; i++) {
		cout << "| " << colnumname[i];
		for (k = 0; k < maxlen[i] - colnumname[i].length() - 1; k++) {
			cout << " ";
		}
	}
	cout << "|" << endl;

	totalfengexian(maxlen, colnumsize);

	for (j = 0; j < maxVectorSize; j++) {
		for (i = 0; i < colnumsize; i++) {
			if (j < v[i].size()) {
				cout << "| " << v[i][j].content << ":(" << v[i][j].begin << "," << v[i][j].end << ")";
				//������󳤶ȾͲ��ո�
				for (k = 0; k < maxlen[i] - v[i][j].content.length() - 5 - getNumLength(v[i][j].begin) - getNumLength(v[i][j].end); k++) {
					cout << " ";
				}
			}
			else {
				cout << "| ";
				for (k = 0; k < maxlen[i] - 1; k++) {
					cout << " ";
				}
			}
		}
		cout << "|" << endl;
	}

	totalfengexian(maxlen, colnumsize);

	cout << maxVectorSize << " rows in set" << endl;
}

