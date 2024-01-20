#include<bits/stdc++.h>
using namespace std;

struct Process
{
    int pID;    //? Process ID
    int aT;     //? Arrival Time
    int bT;     //? Burst Time
    int cT;     //? Completion Time
    int wT;     //? Waiting Time
    int tT;     //? Turnaround Time
};

bool compareProcess(Process p1, Process p2)
{
    return p1.aT < p2.aT;
}

int main()
{
    freopen("input.txt", "r", stdin);
    int _numProcesses;
    cout<<"Enter the number of processes: ";
    cin>> _numProcesses;

    vector<Process> _processes(_numProcesses);

    for(int i=0; i< _numProcesses; i++)
    {
        cout<<"Enter arrival time and burst time for process "<<i+1<<": ";
        cin>>_processes[i].aT >>_processes[i].bT;

        _processes[i].pID = i+1; //*Assinging the process ID's
    }
    fclose(stdin);

    //* Sort process based on arrival time
    sort(_processes.begin(), _processes.end(), compareProcess);

    //* Calculating CT, TT and WT
    int cT = 0;
    for(int i=0; i<_numProcesses; i++)
    {
        if(_processes[i].aT > cT)
        {
            cT = _processes[i].aT;
        }
        _processes[i].cT = cT + _processes[i].bT;
        _processes[i].tT = _processes[i].cT - _processes[i].aT;     //? Turnaround Time = Completiion Time - Arrival Time
        _processes[i].wT = _processes[i].tT - _processes[i].bT;     //? Waiting Time = Turnaround Time - Brust Time
        cT = _processes[i].cT;                                      //? Updating the completion time
    }


    //* Printing the process scheduling table
    cout<<"\n Process Scheduling Table: \n";
    cout<<"Process ID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for(const Process& p : _processes)
    {
        cout<< p.pID << "\t\t"
            <<p.aT<<"\t\t"
            <<p.bT<<"\t\t"
            <<p.cT<<"\t\t"
            <<p.tT<<"\t\t"
            <<p.wT<<endl;
    }

    //* Calculating the average waiting time
    int totat_wT = 0;
    for(const Process& p: _processes)
    {
        totat_wT += p.wT;
    }
    float average_wT = static_cast<float>(totat_wT) / _numProcesses;    //? Average Waiting Time = Total Waiting Time / Number of Processes

    cout<<"Average Waiting Time: "<<average_wT<<endl;

    return 0;
}