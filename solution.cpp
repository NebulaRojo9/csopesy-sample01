#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

struct Process {
    int pid;
    int at;  // Arrival Time
    int bt;  // Burst Time
    int ct;  // Completion Time
    int tat; // Turnaround Time
    int wt;  // Waiting Time
    bool is_completed = false;
};

void calculateSJF(std::vector<Process>& processes) {
    int current_time = 0;
    int completed = 0;
    int n = processes.size();

    while (completed != n) {
        int idx = -1;
        int min_bt = 1e9; // Represents infinity

        for (int i = 0; i < n; ++i) {
            if (processes[i].at <= current_time && !processes[i].is_completed) {
                if (processes[i].bt < min_bt) {
                    min_bt = processes[i].bt;
                    idx = i;
                } else if (processes[i].bt == min_bt) {
                    // Tie-breaker 1: Earliest Arrival Time
                    if (processes[i].at < processes[idx].at) {
                        idx = i;
                    } 
                    // Tie-breaker 2: Lower Process ID
                    else if (processes[i].at == processes[idx].at) {
                        if (processes[i].pid < processes[idx].pid) {
                            idx = i;
                        }
                    }
                }
            }
        }

        if (idx != -1) {
            processes[idx].ct = current_time + processes[idx].bt;
            processes[idx].tat = processes[idx].ct - processes[idx].at;
            processes[idx].wt = processes[idx].tat - processes[idx].bt;
            processes[idx].is_completed = true;
            
            current_time = processes[idx].ct;
            completed++;
        } else {
            current_time++; // CPU Idle state gap advancement
        }
    }
}

int main() {
    // Satisfying the standard test cases given in assignment specifications
    std::vector<Process> processes = {
        {1, 0, 7},
        {2, 2, 4},
        {3, 4, 1},
        {4, 5, 4}
    };

    calculateSJF(processes);

    // Displaying Verification Matrix
    std::cout << "=========================================================\n";
    std::cout << "PID\tAT\tBT\tCT\tTAT\tWT\n";
    std::cout << "=========================================================\n";
    for (const auto& p : processes) {
        std::cout << p.pid << "\t" 
                  << p.at << "\t" 
                  << p.bt << "\t" 
                  << p.ct << "\t" 
                  << p.tat << "\t" 
                  << p.wt << "\n";
    }
    std::cout << "=========================================================\n";

    return 0;
}