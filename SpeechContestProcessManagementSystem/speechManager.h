#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include <deque>
#include <fstream>
#include <ctime>
#include "Speaker.h"
using namespace std;

// �ݽ�������
class SpeechManager
{
public:
	// ���캯��
	SpeechManager();

	// չʾ�˵�
	void showMenu();

	// �˳�ϵͳ
	void exitSystem();

	// ��ʼ������
	void initSpeech();

	// ��ʼ������12��ѡ��
	void createSpeaker();

	// ��ʼ���� - �������̿���
	void startSpeech();

	// ��ǩ
	void speechDraw();

	// ����
	void speechContest();

	// ��ʾ�������
	void showScore();

	// �����¼
	void saveRecord();

	// ��ȡ��¼
	void loadRecord();

	// ��ʾ����÷�
	void showRecord();

	// ��ռ�¼
	void clearRecord();

	// ��������
	~SpeechManager();

public:
	// ����ѡ�� ���� 12��
	vector<int> v1;

	// ��һ�ֽ������� 6��
	vector<int> v2;

	// ʤ��ǰ�������� 3��
	vector<int> v3;

	// ��ű���Լ���Ӧ�ľ���ѡ�� ����
	map<int, Speaker> iToSpeaker;

	// ��������
	int index;

	// �ļ�Ϊ�յı�־
	bool fileIsEmpty;

	// �����¼
	map<int, vector<string>> record;
};