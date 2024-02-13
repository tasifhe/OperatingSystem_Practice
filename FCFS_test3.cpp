#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int startTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

bool compareArrival(Process p1, Process p2) {
    return p1.arrivalTime < p2.arrivalTime;
}

void calculateTimesAndPrintGantt(vector<Process>& processes) {
    int currentTime = 0, totalIdleTime = 0, totalWaitingTime = 0;
    double averageWaitingTime;

    cout << "Gantt Chart:\n";
    cout << setfill('-') << setw(50) << "" << setfill(' ') << endl; // Draw top border of Gantt chart

    for (auto &p : processes) {
        if (currentTime < p.arrivalTime) {
            cout << "| Idle (" << p.arrivalTime - currentTime << " units) ";
            totalIdleTime += p.arrivalTime - currentTime;
            currentTime = p.arrivalTime;
        }
        p.startTime = currentTime;
        p.completionTime = currentTime + p.burstTime;
        p.turnaroundTime = p.completionTime - p.arrivalTime;
        p.waitingTime = p.turnaroundTime - p.burstTime;

        cout << "| P" << p.id << " (" << p.burstTime << " units) ";
        totalWaitingTime += p.waitingTime;
        currentTime += p.burstTime;
    }

    cout << "|\n" << setfill('-') << setw(50) << "" << setfill(' ') << endl; // Draw bottom border of Gantt chart

    averageWaitingTime = (double)totalWaitingTime / processes.size();

    cout << "\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (auto &p : processes) {
        cout << p.id << "\t\t" << p.arrivalTime << "\t\t" << p.burstTime << "\t\t" << p.completionTime << "\t\t" << p.turnaroundTime << "\t\t" << p.waitingTime << "\n";
    }
    cout << "Total Idle Time: " << totalIdleTime << endl;
    cout << "Average Waiting Time: " << averageWaitingTime << endl;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cout << "Enter Arrival Time and Burst Time for Process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime;
    }

    sort(processes.begin(), processes.end(), compareArrival);
    calculateTimesAndPrintGantt(processes);

    return 0;
}