#include "speechManager.h"

// ���캯��
SpeechManager::SpeechManager()
{
	// ��ʼ������
	this->initSpeech();

	// ����ѡ��
	this->createSpeaker();

	// ��ȡ�����¼
	this->loadRecord();
}

// չʾ�˵�
void SpeechManager::showMenu()
{
	cout << "********************************************" << endl;
	cout << "*************  ��ӭ�μ��ݽ����� ************" << endl;
	cout << "*************  1.��ʼ�ݽ�����  *************" << endl;
	cout << "*************  2.�鿴�����¼  *************" << endl;
	cout << "*************  3.��ձ�����¼  *************" << endl;
	cout << "*************  0.�˳���������  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

// �˳�ϵͳ
void SpeechManager::exitSystem()
{
	cout << "��ӭ�´�ʹ�ã�" << endl;
	system("pause");
	exit(0);
}

// ��ʼ������
void SpeechManager::initSpeech()
{
	// ������֤Ϊ��
	this->v1.clear();
	this->v2.clear();
	this->v3.clear();
	this->iToSpeaker.clear();
	// ��ʼ����������
	this->index = 1;
	// ��ʼ����¼����
	this->record.clear();
}

// ��ʼ������12��ѡ��
void SpeechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "ѡ��";
		name += nameSeed[i];

		Speaker sp;
		sp.name = name;
		for (int j = 0; j < 2; j++)
		{
			sp.score[j] = 0;
		}

		// 12��ѡ�ֱ��
		this->v1.push_back(i + 10001);

		// ѡ�ֱ���Լ���Ӧ��ѡ�ִ�ŵ�map������
		this->iToSpeaker.insert({this->v1[i], sp});
	}
}

// ��ʼ���� - �������̿���
void SpeechManager::startSpeech()
{
	//��һ�ֱ���
	//1����ǩ
	this->speechDraw();

	//2������
	this->speechContest();

	//3����ʾ�������
	this->showScore();

	//�ڶ��ֱ���
	this->index++;
	//1����ǩ
	this->speechDraw();

	//2������
	this->speechContest();

	//3����ʾ���ս��
	this->showScore();

	//4���������
	this->saveRecord();

	// ���ñ���
	// ��ʼ������
	this->initSpeech();

	// ����ѡ��
	this->createSpeaker();

	// ��ȡ�����¼
	this->loadRecord();

	cout << "���������ϣ�" << endl;
	system("pause");
	system("cls");
}

// ��ǩ
void SpeechManager::speechDraw()
{
	srand((unsigned int)time(NULL)); // �������

	cout << "�� << " << this->index << " >> �ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "---------------------" << endl;
	cout << "��ǩ���ݽ�˳�����£�" << endl;
	if (this->index == 1)
	{
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "---------------------" << endl;
	system("pause");
	cout << endl;
}

// ����
void SpeechManager::speechContest()
{
	cout << "------------- ��" << this->index << "����ʽ������ʼ��------------- " << endl;

	// ��ʱ���������� key-���� value-ѡ�ֱ��
	multimap<double, int, greater<int>> groupScore;

	int num = 0; // ��¼��Ա����6��Ϊ1��

	vector<int> vContest; // ��������Ա����
	if (this->index == 1)
	{
		vContest = v1;
	}
	else
	{
		vContest = v2;
	}

	// �������в���ѡ��
	for (vector<int>::iterator it = vContest.begin(); it != vContest.end(); it++)
	{
		num++;

		// ��ί���
		deque<double> dq;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 41 + 60) * 1.0;  // 60 ~ 100
			dq.push_back(score);
		}

		// ����
		sort(dq.begin(), dq.end(), greater<double>());
		// ȥ����߷ֺ���ͷ�
		dq.pop_front();												
		dq.pop_back();

		// ��ȡ�ܷ�
		double sum = accumulate(dq.begin(), dq.end(), 0.0f);
		// ��ȡƽ����
		double avg = sum / (double)dq.size();

		// ÿ����ƽ����
		this->iToSpeaker[*it].score[this->index - 1] = avg;

		// 6����һ�飬����ʱ��������
		groupScore.insert({ avg, *it });
		if (num % 6 == 0)
		{
			cout << "��" << num / 6 << "С��������Σ�" << endl;
			for (multimap<double, int, greater<int>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "���: " << it->second << " ������ " << this->iToSpeaker[it->second].name << " �ɼ��� " << this->iToSpeaker[it->second].score[this->index - 1] << endl;
			}

			int count = 0;
			// ȡǰ����
			for (multimap<double, int, greater<int>>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++)
			{
				if (this->index == 1)
				{
					v2.push_back((*it).second);
				}
				else
				{
					v3.push_back((*it).second);
				}
			}

			groupScore.clear();

			cout << endl;
		}
	}
	cout << "------------- ��" << this->index << "�ֱ������  ------------- " << endl;
	system("pause");
}

// ��ʾ�������
void SpeechManager::showScore()
{
	cout << "---------��" << this->index << "�ֽ���ѡ����Ϣ���£�-----------" << endl;
	vector<int> v;
	if (this->index == 1)
	{
		v = v2;
	}
	else
	{
		v = v3;
	}

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "ѡ�ֱ�ţ�" << *it << " ������ " << iToSpeaker[*it].name << " �÷֣� " << iToSpeaker[*it].score[this->index - 1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");

	this->showMenu();
}

// �����¼
void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app); // ������ķ�ʽ���ļ�  -- д�ļ�

	// ��ÿ��������д�뵽�ļ���
	for (vector<int>::iterator it = v3.begin(); it != v3.end(); it++)
	{
		ofs << *it << ","
			<< iToSpeaker[*it].score[1] << ",";
	}
	ofs << endl;

	// �ر��ļ�
	ofs.close();

	cout << "��¼�Ѿ�����" << endl;

	// �м�¼�ˣ��ļ���Ϊ��
	this->fileIsEmpty = false;
}

// ��ȡ��¼
void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in); // ���������� ��ȡ�ļ�

	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	// �ļ���Ϊ��
	this->fileIsEmpty = false;

	ifs.putback(ch); // ��ȡ�ĵ����ַ��Ż�ȥ

	string data;
	int index = 0;
	while (ifs >> data)
	{
		vector<string> v;

		int pos = -1;
		int start = 0;

		while (true)
		{
			pos = data.find(",", start); //��0��ʼ���� ','
			if (pos == -1)
			{
				break; //�Ҳ���break����
			}
			string tmp = data.substr(start, pos - start); //�ҵ���,���зָ� ����1 ��ʼλ�ã�����2 ��ȡ����
			v.push_back(tmp);
			start = pos + 1;
		}

		this->record.insert(make_pair(index, v));
		index++;
	}

	ifs.close();
}

// ��ʾ����÷�
void SpeechManager::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "�ļ������ڣ����¼Ϊ�գ�" << endl;
	}
	else
	{
		for (int i = 0; i < this->record.size(); i++)
		{
			cout << "��" << i + 1 << "�� " <<
				"�ھ���ţ�" << this->record[i][0] << " �÷֣�" << this->record[i][1] << " "
				"�Ǿ���ţ�" << this->record[i][2] << " �÷֣�" << this->record[i][3] << " "
				"������ţ�" << this->record[i][4] << " �÷֣�" << this->record[i][5] << endl;
		}
	}
	system("pause");
	system("cls");
}

// ��ռ�¼
void SpeechManager::clearRecord()
{
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		// ��ģʽ ios::trunc �������ɾ���ļ������´���
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		// ��ʼ������
		this->initSpeech();

		// ����ѡ��
		this->createSpeaker();

		// ��ȡ�����¼
		this->loadRecord();

		cout << "��ճɹ���" << endl;
	}

	system("pause");
	system("cls");
}

// ��������
SpeechManager::~SpeechManager()
{

}