#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int pid;
    int aT;
    int bT;
    int cT;
    int tT;
    int wT;
};

bool compareProcesses(Process p1, Process p2) {
    return p1.aT < p2.aT;
}

int main() {
    int num_processes;
    cout << "Enter the number of processes: ";
    cin >> num_processes;

    vector<Process> processes(num_processes);

    for (int i = 0; i < num_processes; i++) {
        cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
        cin >> processes[i].aT >> processes[i].bT;
        processes[i].pid = i + 1; // Assign process IDs
    }

    sort(processes.begin(), processes.end(), compareProcesses);

    //* Calculate waiting time using Gantt Chart
    int current_time = 0;
    for (int i = 0; i < num_processes; i++) {
        if (processes[i].aT > current_time) {
            current_time = processes[i].aT;
        }
        processes[i].wT = current_time - processes[i].aT; //? Calculate waiting time directly
        current_time += processes[i].bT;
    }

    //* Now calculate completion time and turnaround time using waiting time
    for (int i = 0; i < num_processes; i++) {
        processes[i].cT = processes[i].aT + processes[i].wT + processes[i].bT;
        processes[i].tT = processes[i].cT - processes[i].aT;
    }

    // Print the process scheduling table
    cout << "\nProcess Scheduling Table:\n";
    cout << "Process ID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (const Process& p : processes) {
        cout << p.pid << "\t\t"
             << p.aT << "\t\t"
             << p.bT << "\t\t"
             << p.cT << "\t\t"
             << p.tT << "\t\t"
             << p.wT << endl;
    }

    // Calculate and print average turnaround time and waiting time
    int total_turnaround_time = 0, total_waiting_time = 0;
    for (const Process& p : processes) {
        total_turnaround_time += p.tT;
        total_waiting_time += p.wT;
    }
    float average_turnaround_time = static_cast<float>(total_turnaround_time) / num_processes;
    float average_waiting_time = static_cast<float>(total_waiting_time) / num_processes;

    cout << "\nAverage Turnaround Time: " << average_turnaround_time << endl;
    cout << "Average Waiting Time: " << average_waiting_time << endl;

    return 0;
}
