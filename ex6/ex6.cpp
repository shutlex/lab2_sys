#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <ctime>
#include <cstdlib>

struct Process {
    int id;            
    int arrivalTime;    
    int burstTime;      
    int remainingTime;  
    int priority;       
    int startTime;      
    int completionTime; 
    int waitingTime;    
    int turnaroundTime; 

    Process(int id, int arrivalTime, int burstTime, int priority)
        : id(id), arrivalTime(arrivalTime), burstTime(burstTime), remainingTime(burstTime),
        priority(priority), startTime(0), completionTime(0), waitingTime(0), turnaroundTime(0) {
    }
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

void prioritySchedulingDynamic(std::vector<Process*>& processes, std::queue<Process*>& newProcesses, int timeQuantum) {
    int currentTime = 0;
    std::vector<Process*> readyQueue;
    bool processChanged = false;

    for (auto& p : processes) {
        if (p->arrivalTime <= currentTime) {
            readyQueue.push_back(p);
        }
    }

    while (!readyQueue.empty() || !newProcesses.empty()) {
        while (!newProcesses.empty() && newProcesses.front()->arrivalTime <= currentTime) {
            readyQueue.push_back(newProcesses.front());
            newProcesses.pop();
        }

        if (!readyQueue.empty()) {
            auto it = std::max_element(readyQueue.begin(), readyQueue.end(), [](Process* a, Process* b) {
                return a->priority < b->priority;
                });

            Process* currentProcess = *it;
            readyQueue.erase(it);

            std::cout << "Executing Process ID: " << currentProcess->id << ", Remaining Time: " << currentProcess->remainingTime << ", Priority: " << currentProcess->priority << "\n";

            int executedTime = std::min(timeQuantum, currentProcess->remainingTime);
            currentProcess->remainingTime -= executedTime;
            currentTime += executedTime;

            if (currentProcess->remainingTime == 0) {
                currentProcess->completionTime = currentTime;
                currentProcess->waitingTime = currentTime - currentProcess->arrivalTime - currentProcess->burstTime;
                currentProcess->turnaroundTime = currentProcess->completionTime - currentProcess->arrivalTime;
            }
            else {
                readyQueue.push_back(currentProcess);
            }

            currentProcess->priority = std::rand() % 10 + 1; // Змінюємо пріоритет випадковим чином
        }
        else {
            currentTime++;
        }
    }

    calculateAverageTimes(processes);
}

int main() {
    std::vector<Process*> processes = {
        new Process(1, 0, 6, 3),
        new Process(2, 1, 8, 5),
        new Process(3, 2, 7, 4),
        new Process(4, 3, 4, 2)
    };

    std::queue<Process*> newProcesses;

    newProcesses.push(new Process(5, 5, 5, 6));

    std::cout << "Priority Scheduling with Dynamic Priority Changes:\n";
    prioritySchedulingDynamic(processes, newProcesses, 3);

    for (auto& p : processes) {
        delete p;
    }

    return 0;
}

