#include <iostream>
#include <fstream>
#include <string>
// #include <conio.h>
#include <queue>
using namespace std;

struct Process
{
	string name;	//Process Name
	int exeTime;	//Execution Time
	int arrTime;	//Arrival Time
};

int sizeOfLines(ifstream &in);
void readProcesses(ifstream &in, queue<Process> &Q, const int arrTime);
ifstream &operator>> (ifstream &in, Process &p);
ostream &operator<< (ostream &cout, const Process &p);
void displayQueue(queue<Process> &m);
int main()
{
	ifstream in;int waitTime = 0;int turnTime = 0;int totalTime = 0;
	float avgWaitTime = 0;float avgTurnTime = 0;int count = 0;
	queue<Process> Q;
	in.open("readylist.txt");
	if (!in || in.peek() == -1)	{cout << "No processes found!" << endl;         exit(0);}
	readProcesses(in, Q, 0);
	while (in.peek() != -1 || !Q.empty())
	{count++;
   	 waitTime = totalTime - Q.front().arrTime;
		for (int i = 1; i <= Q.front().exeTime; i++)
		{totalTime++;
		    if (totalTime % 20== 0)
			{cout << "\nPress <Enter> to continue...\n" << endl;
			      
				while (1)
				{char c = _getch();
				  if (c == '\r'){   displayQueue(Q); readProcesses(in, Q, totalTime);  		break;}
				}
			}
		}
		turnTime = totalTime - Q.front().arrTime;
		avgWaitTime += waitTime;		avgTurnTime += turnTime;
        cout<<endl<<"Program Executed:\t";
		cout << Q.front() << ", " << waitTime << ", " << turnTime << endl;
		Q.pop();
	}
	avgWaitTime /= count;
	avgTurnTime /= count;
	cout<<endl<<"Now,No process in the ready queue.Queue is empty.....!"<<endl;
	cout << "\n\nAverage Waiting Time: " << avgWaitTime << endl;
	cout << "Average Turnaround Time: " << avgTurnTime << endl;
	in.close();
}
ifstream &operator>> (ifstream &in, Process &p){getline(in, p.name,' '); in >> p.exeTime;	in.ignore(); return in;}

ostream &operator<< (ostream &out, const Process &p){	out << p.name << ", " << p.exeTime;	return out; }

int sizeOfLines(ifstream &in){
	
	int size = 0;     in.seekg(0);
	while (!in.eof() && in.peek() != -1){in.ignore(100, '\n');    size++;}
	in.seekg(0);     return size;}
	
void readProcesses(ifstream &in, queue<Process> &Q, const int arrTime){
	int size = sizeOfLines(in);
	if (size > 0)
	{int size1 = size + Q.size();    Process current_process;	bool flag = !Q.empty();
		if (flag)
		{ current_process = Q.front();	Q.pop();
			size1--;	}
		Process *list = new Process[size1];
		for (int i = 0; i < size; i++){in >> list[i];   list[i].arrTime = arrTime;}
		in.close();
		ofstream out("readylist.txt", ios::trunc);
		out.close();
		in.open("readylist.txt");
		for (int i = 0; size < size1; i++){list[size++] = Q.front();  Q.pop();}
		cout << "The contents of ready queue are:" << endl;
               
		if (flag){Q.push(current_process);	cout << Q.front() << endl;}
		for (int i = 0; i < size1; i++){Q.push(list[i]);   cout << list[i] << endl;}
		delete []list;cout << endl << endl;
	}
	
}
void displayQueue(queue<Process> &m){
	queue<Process> t = m;
	cout << endl << "Processes in ready queue are:" << endl;
	while (!t.empty())
	{cout << t.front().name << "," << t.front().exeTime << " " << endl;  	t.pop();}
}

