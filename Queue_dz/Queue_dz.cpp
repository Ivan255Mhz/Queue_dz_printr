
#pragma warning(disable : 4996)
#include <queue>
#include <vector>
#include <chrono>
#include <ctime>
#include <iostream>

struct PrintJob {
    std::string user;
    int priority;
    std::chrono::system_clock::time_point time;

    bool operator<(const PrintJob& other) const {
        
        if (priority != other.priority) {
            return priority > other.priority;
        }
        else {
            return time < other.time;
        }
    }
};

class PrinterQueue {
private:
    std::priority_queue<PrintJob, std::vector<PrintJob>, std::less<PrintJob>> queue;
    std::vector<PrintJob> printHistory;

public:
    void addPrintJob(const std::string& user, int priority) {
        PrintJob job{ user, priority, std::chrono::system_clock::now() };
        queue.push(job);
        std::cout << "New print job added: User - " << user << ", Priority - " << priority << std::endl;
    }

    void printNextJob() {
        if (!queue.empty()) {
            PrintJob job = queue.top();
            queue.pop();
            std::cout << "Printing job: User - " << job.user << ", Priority - " << job.priority << std::endl;
            printHistory.push_back(job);
        }
        else {
            std::cout << "No jobs in the queue." << std::endl;
        }
    }

    void printStatistics() {
        std::cout << "Print History:" << std::endl;
        for (const auto& job : printHistory) {
            std::time_t time = std::chrono::system_clock::to_time_t(job.time);
            std::cout << "User - " << job.user << ", Priority - " << job.priority << ", Time - " << std::ctime(&time);
        }
    }
};

int main() {
    PrinterQueue printer;

    printer.addPrintJob("User1", 3);
    printer.addPrintJob("User2", 1);
    printer.addPrintJob("User3", 2);
    printer.addPrintJob("User4", 2);

    printer.printNextJob();
    printer.printNextJob();
    printer.printNextJob();
    printer.printNextJob();

    printer.printStatistics();

    return 0;
}
