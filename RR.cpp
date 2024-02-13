#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int startTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
    int remainingBurstTime;
};

int main() {
    int n, quantum;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    for (int i = 0; i < n; i++) {
        cout << "Enter Arrival Time and Burst Time for Process " << i + 1 << ": ";
        processes[i].id = i;
        cin >> processes[i].arrivalTime >> processes[i].burstTime;
        processes[i].remainingBurstTime = processes[i].burstTime;
    }

    cout << "Enter time quantum: ";
    cin >> quantum;

    int currentTime = 0;
    int completed = 0;
    int totalIdleTime = 0;
    queue<int> q;

    // Add processes to the queue in order of arrival
    while (completed != n) {
        for (auto &p : processes) {
            if (p.arrivalTime == currentTime) {
                q.push(p.id);
            }
        }

        if (!q.empty()) {
            int id = q.front();
            q.pop();

            if (processes[id].remainingBurstTime == processes[id].burstTime) {
                processes[id].startTime = currentTime;
            }

            if (processes[id].remainingBurstTime > quantum) {
                currentTime += quantum;
                processes[id].remainingBurstTime -= quantum;
            } else {
                currentTime += processes[id].remainingBurstTime;
                processes[id].completionTime = currentTime;
                processes[id].turnaroundTime = processes[id].completionTime - processes[id].arrivalTime;
                processes[id].waitingTime = processes[id].turnaroundTime - processes[id].burstTime;
                processes[id].remainingBurstTime = 0;
                completed++;
            }

            // Re-add process to queue if it's not completed
            for (auto &p : processes) {
                if (p.arrivalTime <= currentTime && p.remainingBurstTime > 0 && p.id != id) {
                    q.push(p.id);
                }
            }
            if (processes[id].remainingBurstTime > 0) {
                q.push(id);
            }

        } else {
            currentTime++;
            totalIdleTime++;
        }
    }

    cout << "\nProcess ID\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (auto &p : processes) {
        cout << p.id + 1 << "\t\t"
             << p.completionTime << "\t\t"
             << p.turnaroundTime << "\t\t"
             << p.waitingTime << endl;
    }
    cout << "Total Idle Time: " << totalIdleTime << endl;

    return 0;
}
