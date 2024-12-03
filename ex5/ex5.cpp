#include <iostream>
#include <vector>
#include <algorithm>

struct Process {
    int id;            
    int arrivalTime;    
    int burstTime;      
    int startTime;      
    int completionTime; 
    int waitingTime;    
    int turnaroundTime; 
};


void calculateAverageTimes(std::vector<Process*>& processes) {
    int totalWaitingTime = 0, totalTurnaroundTime = 0;
    int n = processes.size();

    for (const auto& p : processes) {
        totalWaitingTime += p->waitingTime;
        totalTurnaroundTime += p->turnaroundTime;
    }

    double avgWaitingTime = (double)totalWaitingTime / n;
    double avgTurnaroundTime = (double)totalTurnaroundTime / n;

    std::cout << "Average Waiting Time: " << avgWaitingTime << " ms\n";
    std::cout << "Average Turnaround Time: " << avgTurnaroundTime << " ms\n";
}


void fcfs(std::vector<Process*>& processes) {
    int currentTime = 0; 

    for (auto& p : processes) {
        p->startTime = std::max(p->arrivalTime, currentTime);
        p->completionTime = p->startTime + p->burstTime;
        p->waitingTime = p->startTime - p->arrivalTime;
        p->turnaroundTime = p->completionTime - p->arrivalTime;

        currentTime = p->completionTime;
    }

    calculateAverageTimes(processes);
}


void roundRobin(std::vector<Process*>& processes, int quantum) {
    int currentTime = 0;
    std::vector<Process*> queue = processes;
    std::vector<int> remainingBurstTime(processes.size());

    for (int i = 0; i < processes.size(); ++i) {
        remainingBurstTime[i] = processes[i]->burstTime;
    }

    while (!queue.empty()) {
        Process* currentProcess = queue.front();
        queue.erase(queue.begin());

        if (remainingBurstTime[currentProcess->id - 1] > quantum) {
            remainingBurstTime[currentProcess->id - 1] -= quantum;
            currentTime += quantum;
            queue.push_back(currentProcess);  
        }
        else {
            currentTime += remainingBurstTime[currentProcess->id - 1];
            currentProcess->completionTime = currentTime;
            currentProcess->waitingTime = currentTime - currentProcess->arrivalTime - currentProcess->burstTime;
            currentProcess->turnaroundTime = currentProcess->completionTime - currentProcess->arrivalTime;
            remainingBurstTime[currentProcess->id - 1] = 0;
        }
    }

    calculateAverageTimes(processes);
}


void priorityScheduling(std::vector<Process*>& processes) {
    std::sort(processes.begin(), processes.end(), [](const Process* a, const Process* b) {
        return a->arrivalTime < b->arrivalTime; 
        });

    std::sort(processes.begin(), processes.end(), [](const Process* a, const Process* b) {
        return a->burstTime > b->burstTime; 
        });

    int currentTime = 0;
    for (auto& p : processes) {
        p->startTime = std::max(p->arrivalTime, currentTime);
        p->completionTime = p->startTime + p->burstTime;
        p->waitingTime = p->startTime - p->arrivalTime;
        p->turnaroundTime = p->completionTime - p->arrivalTime;

        currentTime = p->completionTime;
    }

    calculateAverageTimes(processes);
}

int main() {
    std::vector<Process*> processes = {
        new Process{1, 0, 6, 0, 0, 0, 0},  
        new Process{2, 1, 8, 0, 0, 0, 0},  
        new Process{3, 2, 7, 0, 0, 0, 0},  
        new Process{4, 3, 4, 0, 0, 0, 0}  
    };

    std::cout << "FCFS Algorithm:\n";
    fcfs(processes);  

    std::cout << "\nRound Robin Algorithm (Quantum = 4):\n";
    roundRobin(processes, 4);  

    std::cout << "\nPriority Scheduling Algorithm:\n";
    priorityScheduling(processes);  

    
    for (auto& p : processes) {
        delete p;
    }

    return 0;
}
