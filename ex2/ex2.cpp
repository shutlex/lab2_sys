#include <iostream>
#include <queue>
#include <vector>


struct Process {
    int id;             
    int burstTime;      
    int remainingTime;  
};


void roundRobin(std::vector<Process>& processes, int timeQuantum) {
    std::queue<Process> processQueue;  

    for (const auto& p : processes) {
        processQueue.push(p);
    }

    while (!processQueue.empty()) {
        Process current = processQueue.front();
        processQueue.pop();

        std::cout << "Process " << current.id << " started with remaining time " << current.remainingTime << " ms.\n";

        int executionTime = std::min(current.remainingTime, timeQuantum);
        current.remainingTime -= executionTime;

        std::cout << "Process " << current.id << " executed for " << executionTime << " ms. Remaining time: " << current.remainingTime << " ms.\n";

        if (current.remainingTime > 0) {
            processQueue.push(current);
        }
        else {
            std::cout << "Process " << current.id << " completed.\n";
        }
    }
}

int main() {
    
    std::vector<Process> processes = {
        {1, 12, 12},  
        {2, 8, 8},    
        {3, 15, 15},  
        {4, 5, 5}     
    };

   
    int timeQuantum = 4;

    
    roundRobin(processes, timeQuantum);

    return 0;
}
