#include <iostream>
#include <limits> // For error handling with invalid input

using namespace std;

#define MAX_PROCESSES 100

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

void calculateCPUPerformance(Process processes[], int n) {
    Process readyQueue[MAX_PROCESSES]; // Queue for storing ready processes
    int front = 0, rear = -1;
    int currentTime = 0;
    int idleTime = 0;

    // Calculate completion time, turnaround time, and waiting time for each process
    for (int i = 0; i < n; i++) {
        // Simulate process arrival
        if (processes[i].arrivalTime <= currentTime) {
            rear++;
            readyQueue[rear] = processes[i];
        }

        // Enqueue arrived process (non-preemptive)
        if (readyQueue[front].arrivalTime <= currentTime) {
            Process p = readyQueue[front];
            currentTime += p.burstTime;
            p.completionTime = currentTime;
            p.turnaroundTime = p.completionTime - p.arrivalTime;
            p.waitingTime = p.turnaroundTime - p.burstTime;
            processes[i] = p; // Update original process object
            front++;
        } else {
            // CPU is idle if no process is ready
            idleTime++;
        }
    }

    // Display results
    cout << "\nProcess | Arrival Time | Burst Time | Completion Time | Turnaround Time | Waiting Time\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << processes[i].pid << " | " << processes[i].arrivalTime << " | " << processes[i].burstTime << " | " << processes[i].completionTime << " | " << processes[i].turnaroundTime << " | " << processes[i].waitingTime << endl;
    }

    // Calculate average waiting time and average turnaround time
    float avgWaitingTime = 0.0, avgTurnaroundTime = 0.0;
    for (int i = 0; i < n; i++) {
        avgWaitingTime += processes[i].waitingTime;
        avgTurnaroundTime += processes[i].turnaroundTime;
    }
    avgWaitingTime /= n;
    avgTurnaroundTime /= n;

    cout << "\nAverage Waiting Time: " << avgWaitingTime << endl;
    cout << "Average Turnaround Time: " << avgTurnaroundTime << endl;
    cout << "Idle Time: " << idleTime << endl;
}

int main() {
    int n;
    //freopen("input.txt", "r", stdin);
    cout << "Enter the number of processes: ";
    cin >> n;

    if (n <= 0 || n > MAX_PROCESSES) {
        cerr << "Invalid number of processes (must be between 1 and " << MAX_PROCESSES << ").\n";
        return 1;
    }

    Process processes[n];

    cout << "Enter process details (arrival time, burst time):\n";
    for (int i = 0; i < n; i++) {
        cout << "Process " << i + 1 << ": ";
        if (!(cin >> processes[i].arrivalTime >> processes[i].burstTime)) {
            cerr << "Invalid input. Please enter integers." << endl;
            return 1;
        }
        processes[i].pid = i + 1; // Assign process IDs
    }

    cout << "\nFCFS Scheduling Results:\n";
    calculateCPUPerformance(processes, n);

    return 0;
}
