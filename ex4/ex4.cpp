#include <iostream>
#include <vector>
#include <algorithm>

struct Process {
    int id;            
    int burstTime;      
    int priority;       
};

void priorityScheduling(std::vector<Process>& processes) {
    
    std::sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.priority > b.priority; 
        });

  
    for (const auto& p : processes) {
        std::cout << "Process ID: " << p.id << "\n";
        std::cout << "Burst Time: " << p.burstTime << " ms\n";
        std::cout << "Priority: " << p.priority << "\n";
        std::cout << "-------------------------------\n";
    }
}

int main() {
    
    std::vector<Process> processes = {
        {1, 6, 3},   
        {2, 8, 1},   
        {3, 7, 2},   
        {4, 4, 4}    
    };

    priorityScheduling(processes);

    return 0;
}

