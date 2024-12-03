#include <iostream>
#include <vector>

struct Process {
    int id;             
    int arrivalTime;    
    int burstTime;      
    int startTime;      
    int completionTime; 
    int waitingTime;    
};


void fcfs(std::vector<Process>& processes) {
    int currentTime = 0; 

    
    for (auto& p : processes) {
        
        p.startTime = std::max(p.arrivalTime, currentTime);
        p.completionTime = p.startTime + p.burstTime; 
        p.waitingTime = p.startTime - p.arrivalTime;   

        currentTime = p.completionTime; 

        
        std::cout << "Process " << p.id << ":\n";
        std::cout << "  Arrival Time: " << p.arrivalTime << " ms\n";
        std::cout << "  Start Time: " << p.startTime << " ms\n";
        std::cout << "  Completion Time: " << p.completionTime << " ms\n";
        std::cout << "  Waiting Time: " << p.waitingTime << " ms\n";
        std::cout << "-----------------------------\n";
    }
}

int main() {
    
    std::vector<Process> processes = {
        {1, 0, 8, 0, 0, 0},  
        {2, 1, 4, 0, 0, 0},  
        {3, 2, 9, 0, 0, 0},  
        {4, 3, 5, 0, 0, 0}   
    };

    fcfs(processes);

    return 0;
}

