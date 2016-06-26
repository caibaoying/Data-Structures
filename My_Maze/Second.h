#include <iostream>
using namespace std;

//�Թ����� 
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#define mazefile "maze.txt"

using namespace std;
class Escape
{
public:
	int left;
	int forward;
	int right;
	friend ostream& operator<<(ostream& out, Escape& e);
	bool operator!();
};
ostream& operator<<(ostream& out, Escape& e) //����<< 
{
	if (e.left != 0) out << e.left << "��·�� ";
	if (e.forward != 0) out << e.forward << "��·�� ";
	if (e.right != 0) out << e.right << "��·�� ";
	return out;
}
bool Escape::operator!() //����! 
{
	if (this->left == 0 && this->forward == 0 && this->right == 0)
		return false;
	return true;
}
vector<Escape> ev;
vector<int> vi;
int _EXIT;
int ston(const string& s);
bool findex(int escape);
int main(int argc, char* argv[])
{

	string line;
	ifstream in(mazefile);
	Escape esc;
	int i = 0;
	while (getline(in, line))
	{
		int l = 0;
		string s;
		l = line.find(":");
		s = line.substr(0, l);
		line = line.substr(l + 1);  //��ȡð�ź���ַ��� 
		l = line.find(",");
		esc.left = ston(line.substr(0, l));  //ȡ�õ�һ������ǰ������ 
		line = line.substr(l + 1);
		l = line.find(",");
		esc.forward = ston(line.substr(0, l));//ȡ�õڶ�������ǰ������ 
		line = line.substr(l + 1);
		esc.right = ston(line);              //ȡ�õ���������ǰ������     
		ev.push_back(esc);
		if (!ev[i])
			cout << i << "��·��ͨ��" << ev[i] << endl;
		else
			cout << i << "��·������·��" << endl;
		i++;
	}
	cout << "��������Ҫ�����·�ڣ�";
	cin >> _EXIT;
	if (findex(1))
		cout << "1��·��->";
	for (int i = vi.size() - 1; i >= 0; i--)
		cout << vi[i] << "��·��->";

	cout << "EXIT" << endl;
	system("pause");
	return 0;
}

bool findex(int escape)  //�ݹ���� 
{
	if (escape>0)
	{
		if (escape == _EXIT) return true;
		if (findex(ev[escape].left))
		{
			vi.push_back(ev[escape].left);
			return true;
		}
		if (findex(ev[escape].forward))
		{
			vi.push_back(ev[escape].forward);
			return true;
		}
		if (findex(ev[escape].right))
		{
			vi.push_back(ev[escape].right);
			return true;
		}
	}
	return false;
}

int ston(const string& s)  //���ַ���ת��Ϊ���������� 
{
	const char* c = s.c_str();
	int num = 0;
	while (*c)
		num = num * 10 + (int)((*c++) - '0');
	return num;
}