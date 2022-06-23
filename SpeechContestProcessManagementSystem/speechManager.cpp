#include "speechManager.h"

// 构造函数
SpeechManager::SpeechManager()
{
	// 初始化属性
	this->initSpeech();

	// 创建选手
	this->createSpeaker();

	// 获取往届记录
	this->loadRecord();
}

// 展示菜单
void SpeechManager::showMenu()
{
	cout << "********************************************" << endl;
	cout << "*************  欢迎参加演讲比赛 ************" << endl;
	cout << "*************  1.开始演讲比赛  *************" << endl;
	cout << "*************  2.查看往届记录  *************" << endl;
	cout << "*************  3.清空比赛记录  *************" << endl;
	cout << "*************  0.退出比赛程序  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

// 退出系统
void SpeechManager::exitSystem()
{
	cout << "欢迎下次使用！" << endl;
	system("pause");
	exit(0);
}

// 初始化属性
void SpeechManager::initSpeech()
{
	// 容器保证为空
	this->v1.clear();
	this->v2.clear();
	this->v3.clear();
	this->iToSpeaker.clear();
	// 初始化比赛轮数
	this->index = 1;
	// 初始化记录容器
	this->record.clear();
}

// 初始化创建12名选手
void SpeechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "选手";
		name += nameSeed[i];

		Speaker sp;
		sp.name = name;
		for (int j = 0; j < 2; j++)
		{
			sp.score[j] = 0;
		}

		// 12名选手编号
		this->v1.push_back(i + 10001);

		// 选手编号以及对应的选手存放到map容器中
		this->iToSpeaker.insert({this->v1[i], sp});
	}
}

// 开始比赛 - 比赛流程控制
void SpeechManager::startSpeech()
{
	//第一轮比赛
	//1、抽签
	this->speechDraw();

	//2、比赛
	this->speechContest();

	//3、显示晋级结果
	this->showScore();

	//第二轮比赛
	this->index++;
	//1、抽签
	this->speechDraw();

	//2、比赛
	this->speechContest();

	//3、显示最终结果
	this->showScore();

	//4、保存分数
	this->saveRecord();

	// 重置比赛
	// 初始化属性
	this->initSpeech();

	// 创建选手
	this->createSpeaker();

	// 获取往届记录
	this->loadRecord();

	cout << "本届比赛完毕！" << endl;
	system("pause");
	system("cls");
}

// 抽签
void SpeechManager::speechDraw()
{
	srand((unsigned int)time(NULL)); // 随机种子

	cout << "第 << " << this->index << " >> 轮比赛选手正在抽签" << endl;
	cout << "---------------------" << endl;
	cout << "抽签后演讲顺序如下：" << endl;
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

// 比赛
void SpeechManager::speechContest()
{
	cout << "------------- 第" << this->index << "轮正式比赛开始：------------- " << endl;

	// 临时容器，保存 key-分数 value-选手编号
	multimap<double, int, greater<int>> groupScore;

	int num = 0; // 记录人员数，6个为1组

	vector<int> vContest; // 比赛的人员容器
	if (this->index == 1)
	{
		vContest = v1;
	}
	else
	{
		vContest = v2;
	}

	// 遍历所有参赛选手
	for (vector<int>::iterator it = vContest.begin(); it != vContest.end(); it++)
	{
		num++;

		// 评委打分
		deque<double> dq;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 41 + 60) * 1.0;  // 60 ~ 100
			dq.push_back(score);
		}

		// 排序
		sort(dq.begin(), dq.end(), greater<double>());
		// 去掉最高分和最低分
		dq.pop_front();												
		dq.pop_back();

		// 获取总分
		double sum = accumulate(dq.begin(), dq.end(), 0.0f);
		// 获取平均分
		double avg = sum / (double)dq.size();

		// 每个人平均分
		this->iToSpeaker[*it].score[this->index - 1] = avg;

		// 6个人一组，用临时容器保存
		groupScore.insert({ avg, *it });
		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "小组比赛名次：" << endl;
			for (multimap<double, int, greater<int>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "编号: " << it->second << " 姓名： " << this->iToSpeaker[it->second].name << " 成绩： " << this->iToSpeaker[it->second].score[this->index - 1] << endl;
			}

			int count = 0;
			// 取前三名
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
	cout << "------------- 第" << this->index << "轮比赛完毕  ------------- " << endl;
	system("pause");
}

// 显示比赛结果
void SpeechManager::showScore()
{
	cout << "---------第" << this->index << "轮晋级选手信息如下：-----------" << endl;
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
		cout << "选手编号：" << *it << " 姓名： " << iToSpeaker[*it].name << " 得分： " << iToSpeaker[*it].score[this->index - 1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");

	this->showMenu();
}

// 保存记录
void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app); // 用输出的方式打开文件  -- 写文件

	// 将每个人数据写入到文件中
	for (vector<int>::iterator it = v3.begin(); it != v3.end(); it++)
	{
		ofs << *it << ","
			<< iToSpeaker[*it].score[1] << ",";
	}
	ofs << endl;

	// 关闭文件
	ofs.close();

	cout << "记录已经保存" << endl;

	// 有记录了，文件不为空
	this->fileIsEmpty = false;
}

// 读取记录
void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in); // 输入流对象 读取文件

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

	// 文件不为空
	this->fileIsEmpty = false;

	ifs.putback(ch); // 读取的单个字符放回去

	string data;
	int index = 0;
	while (ifs >> data)
	{
		vector<string> v;

		int pos = -1;
		int start = 0;

		while (true)
		{
			pos = data.find(",", start); //从0开始查找 ','
			if (pos == -1)
			{
				break; //找不到break返回
			}
			string tmp = data.substr(start, pos - start); //找到了,进行分割 参数1 起始位置，参数2 截取长度
			v.push_back(tmp);
			start = pos + 1;
		}

		this->record.insert(make_pair(index, v));
		index++;
	}

	ifs.close();
}

// 显示往届得分
void SpeechManager::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "文件不存在，或记录为空！" << endl;
	}
	else
	{
		for (int i = 0; i < this->record.size(); i++)
		{
			cout << "第" << i + 1 << "届 " <<
				"冠军编号：" << this->record[i][0] << " 得分：" << this->record[i][1] << " "
				"亚军编号：" << this->record[i][2] << " 得分：" << this->record[i][3] << " "
				"季军编号：" << this->record[i][4] << " 得分：" << this->record[i][5] << endl;
		}
	}
	system("pause");
	system("cls");
}

// 清空记录
void SpeechManager::clearRecord()
{
	cout << "确认清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		// 打开模式 ios::trunc 如果存在删除文件并重新创建
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		// 初始化属性
		this->initSpeech();

		// 创建选手
		this->createSpeaker();

		// 获取往届记录
		this->loadRecord();

		cout << "清空成功！" << endl;
	}

	system("pause");
	system("cls");
}

// 析构函数
SpeechManager::~SpeechManager()
{

}