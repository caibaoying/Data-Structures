#include <iostream>
using namespace std;

//迷宫问题 
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
ostream& operator<<(ostream& out, Escape& e) //重载<< 
{
	if (e.left != 0) out << e.left << "号路口 ";
	if (e.forward != 0) out << e.forward << "号路口 ";
	if (e.right != 0) out << e.right << "号路口 ";
	return out;
}
bool Escape::operator!() //重载! 
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
		line = line.substr(l + 1);  //获取冒号后的字符串 
		l = line.find(",");
		esc.left = ston(line.substr(0, l));  //取得第一个逗号前的数字 
		line = line.substr(l + 1);
		l = line.find(",");
		esc.forward = ston(line.substr(0, l));//取得第二个逗号前的数字 
		line = line.substr(l + 1);
		esc.right = ston(line);              //取得第三个逗号前的数字     
		ev.push_back(esc);
		if (!ev[i])
			cout << i << "号路口通向：" << ev[i] << endl;
		else
			cout << i << "号路口是死路！" << endl;
		i++;
	}
	cout << "请输入您要到达的路口：";
	cin >> _EXIT;
	if (findex(1))
		cout << "1号路口->";
	for (int i = vi.size() - 1; i >= 0; i--)
		cout << vi[i] << "号路口->";

	cout << "EXIT" << endl;
	system("pause");
	return 0;
}

bool findex(int escape)  //递归查找 
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

int ston(const string& s)  //将字符串转换为整数并返回 
{
	const char* c = s.c_str();
	int num = 0;
	while (*c)
		num = num * 10 + (int)((*c++) - '0');
	return num;
}