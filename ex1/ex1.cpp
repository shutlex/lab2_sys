#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>


struct Process {
    int id;             
    int arrivalTime;    
    int burstTime;      
    int priority;       
};


int getRandomNumber(int min, int max) {
    return rand() % (max - min + 1) + min;
}

int main() {
    
    srand(time(0));  

    int numProcesses = 5;  
    std::vector<Process> processes;  

    
    for (int i = 0; i < numProcesses; ++i) {
        Process p;
        p.id = i + 1;                          
        p.arrivalTime = getRandomNumber(0, 10); 
        p.burstTime = getRandomNumber(1, 10);   
        p.priority = getRandomNumber(1, 5);     

        processes.push_back(p);  
    }

    std::cout << "Generated Processes:" << std::endl;
    std::cout << "ID\tArrival Time\tBurst Time\tPriority" << std::endl;
    for (const auto& p : processes) {
        std::cout << p.id << "\t" << p.arrivalTime << "\t\t" << p.burstTime << "\t\t" << p.priority << std::endl;
    }

    return 0;
}
