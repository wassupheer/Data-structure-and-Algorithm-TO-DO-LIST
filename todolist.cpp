#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;
class Node {
public:
    string task;
    int hour;
    int minute;
    Node* next;

    Node(string task, int hour, int minute)
        : task(task), hour(hour), minute(minute), next(nullptr) {}
};
class ToDoList {
private:
    Node* head;

public:
    ToDoList() : head(nullptr) {}
    ~ToDoList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
    void addTask(const string& task, int hour, int minute) {
        Node* newTask = new Node(task, hour, minute);
        if (head == nullptr) {
            head = newTask;
        } else {
            Node* temp = head;
            while (temp->next != nullptr)
                temp = temp->next;
            temp->next = newTask;
        }
        cout << "Task '" << task << "' added successfully!\n";
    }
    void printTasks() const {
        if (head == nullptr) {
            cout << "No tasks available.\n";
            return;
        }

        cout << "\nAll Tasks:\n";
        Node* temp = head;
        int count = 1;
        while (temp != nullptr) {
            cout << count++ << ". " << left << temp->task
                 << " | Time: "<< temp->hour
                 << ":"<< temp->minute << endl;
            temp = temp->next;
        }
    }
    void removeTask(const string& task) {
        if (head == nullptr)
            return;

        if (head->task == task) {
            Node* toDelete = head;
            head = head->next;
            delete toDelete;
            return;
        }

        Node* temp = head;
        while (temp->next != nullptr && temp->next->task != task)
            temp = temp->next;

        if (temp->next != nullptr) {
            Node* toDelete = temp->next;
            temp->next = toDelete->next;
            delete toDelete;
        }
    }
    void markCompleted(const string& task) {
        if (!searchTask(task)) {
            cout << "Task '" << task << "' not found.\n";
            return;
        }
        removeTask(task);
        cout << "Task '" << task << "' marked as completed!\n";
    }
    bool searchTask(const string& task) const {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->task == task)
                return true;
            temp = temp->next;
        }
        return false;
    }
    void showPriorityList() const {
        if (head == nullptr) {
            cout << "No tasks to prioritize.\n";
            return;
        }

        vector<pair<string, pair<int, int>>> timeList;
        Node* temp = head;

        while (temp != nullptr) {
            timeList.push_back({temp->task, {temp->hour, temp->minute}});
            temp = temp->next;
        }

        sort(timeList.begin(), timeList.end(),
            [](const auto& a, const auto& b) {
                if (a.second.first == b.second.first)
                    return a.second.second < b.second.second;
                return a.second.first < b.second.first;
            });

        cout << "\nPriority List :\n";
        int i = 1;
        for (const auto& t : timeList) {
            cout << i++ << ". " << left << t.first
                 << " due at " << t.second.first
                 << ":" << t.second.second <<endl;
        }
    }
};
int main() {
    ToDoList myList;
    int choice;
    cout <<"TO-DO LIST\n";
    do {
        cout << "Menu:\n";
        cout << "1. Add Task\n";
        cout << "2. Show All Tasks\n";
        cout << "3. Show Priority List\n";
        cout << "4. Mark Task Completed\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string task;
            int hour, minute;
            cout << "Enter task description: ";
            getline(cin, task);
            cout << "Enter time (hour minute): ";
            cin >> hour >> minute;
            cin.ignore();
            myList.addTask(task, hour, minute);
        } 
        else if (choice == 2) {
            myList.printTasks();
        } 
        else if (choice == 3) {
            myList.showPriorityList();
        } 
        else if (choice == 4) {
            string task;
            cout << "Enter task to mark as completed: ";
            getline(cin, task);
            myList.markCompleted(task);
        } 
        else if (choice == 0) {
            cout << "Exiting... Have a productive day!\n";
        } 
        else {
            cout << "Invalid choice, please try again!\n";
        }

    } while (choice != 0);

    return 0;
}