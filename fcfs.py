def fcfs_scheduling(processes):
    n = len(processes)
    
    # Initializing variables
    completion_time = [0] * n
    turnaround_time = [0] * n
    waiting_time = [0] * n
    start_time = [0] * n
    idle_time = 0
    
    # Sort processes by their arrival time
    processes.sort(key=lambda x: x[1])
    
    # Calculate completion time for each process
    for i in range(n):
        if i == 0 or completion_time[i-1] < processes[i][1]:
            completion_time[i] = processes[i][1] + processes[i][2]
            start_time[i] = processes[i][1]
        else:
            completion_time[i] = completion_time[i-1] + processes[i][2]
            start_time[i] = completion_time[i-1]
        
        # Calculate turnaround time: TAT = CT - AT
        turnaround_time[i] = completion_time[i] - processes[i][1]
        
        # Calculate waiting time: WT = TAT - BT
        waiting_time[i] = turnaround_time[i] - processes[i][2]
        
        # Calculate idle time
        if i > 0:
            idle_time += max(0, processes[i][1] - completion_time[i-1])
    
    # Print the results
    print("Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time")
    for i in range(n):
        print(f"{processes[i][0]}\t\t{processes[i][1]}\t\t{processes[i][2]}\t\t{completion_time[i]}\t\t{turnaround_time[i]}\t\t{waiting_time[i]}")
    print(f"\nTotal Idle Time: {idle_time}")

if __name__ == "__main__":
    n = int(input("Enter the number of processes: "))
    processes = []  # Each process is a tuple of (Process ID, Arrival Time, Burst Time)
    
    for i in range(n):
        process_id = i + 1
        arrival_time, burst_time = map(int, input(f"Enter Arrival Time and Burst Time for Process {process_id}: ").split())
        processes.append((process_id, arrival_time, burst_time))
    
    fcfs_scheduling(processes)
