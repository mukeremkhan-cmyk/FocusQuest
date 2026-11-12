#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

class Task {
public:
    string name;
    bool completed;

    Task(string n, bool c = false) {
        name = n;
        completed = c;
    }
};

vector<Task> tasks;

void saveTasks() {
    ofstream file("tasks.txt");

    for (const auto& task : tasks) {
        file << task.completed << " "
             << quoted(task.name) << "\n";
    }

    file.close();
}

void loadTasks() {
    ifstream file("tasks.txt");
    bool completed;
    string name;

    while (file >> completed >> quoted(name)) {
        tasks.push_back(Task(name, completed));
    }

    file.close();
}

void addTask() {
    string name;

    cout << "\nEnter task name: ";
    getline(cin, name);

    if (name.empty()) {
        cout << "Task cannot be empty!\n";
        return;
    }

    tasks.push_back(Task(name));
    saveTasks();

    cout << "Task added successfully!\n";
}

void viewTasks() {
    cout << "\n========== YOUR TASKS ==========\n";

    if (tasks.empty()) {
        cout << "No tasks yet. Add your first task!\n";
        return;
    }

    for (int i = 0; i < (int)tasks.size(); i++) {
        cout << i + 1 << ". "
             << (tasks[i].completed ? "[DONE] " : "[TODO] ")
             << tasks[i].name << "\n";
    }
}

void completeTask() {
    viewTasks();

    if (tasks.empty()) return;

    int choice;
    cout << "\nEnter task number to complete: ";
    cin >> choice;

    if (choice >= 1 && choice <= (int)tasks.size()) {
        tasks[choice - 1].completed = true;
        saveTasks();
        cout << "Congratulations! Task completed!\n";
    } else {
        cout << "Invalid task number!\n";
    }
}

void showProgress() {
    int completed = 0;

    for (const auto& task : tasks) {
        if (task.completed) completed++;
    }

    int total = tasks.size();

    double percentage = total == 0
        ? 0
        : (completed * 100.0 / total);

    cout << "\n========== PROGRESS ==========\n";
    cout << "Total tasks: " << total << "\n";
    cout << "Completed:   " << completed << "\n";
    cout << "Remaining:   " << total - completed << "\n";

    cout << fixed << setprecision(1);
    cout << "Progress:    " << percentage << "%\n";
}

int main() {
    loadTasks();

    int choice;

    cout << "================================\n";
    cout << "       F O C U S Q U E S T      \n";
    cout << "     Student Productivity App   \n";
    cout << "================================\n";

    do {
        cout << "\n1. Add a task\n";
        cout << "2. View tasks\n";
        cout << "3. Complete a task\n";
        cout << "4. View progress\n";
        cout << "5. Exit\n";

        cout << "\nChoose an option: ";
        cin >> choice;
        cin.ignore(10000, '\n');

        switch (choice) {
            case 1: addTask(); break;
            case 2: viewTasks(); break;
            case 3: completeTask(); break;
            case 4: showProgress(); break;
            case 5:
                saveTasks();
                cout << "\nThank you for using FocusQuest!\n";
                break;
            default:
                cout << "Invalid choice. Try again!\n";
        }

    } while (choice != 5);

    return 0;
}
