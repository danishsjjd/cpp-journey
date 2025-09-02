#include <iostream>
#include <string>
#include <vector>

#include "TaskManager.hpp"

using namespace std;

const string filename = "tasks.json";

void validateArgumentCount(int argc, int argcRequired,
                           const string& errorMessage = "Invalid arguments") {
  if (argc < argcRequired) {
    throw invalid_argument(errorMessage);
  }
}

void printTasks(const vector<Task>& tasks) {
  if (tasks.empty()) {
    cout << "No tasks" << endl;
    return;
  }
  for (const auto& t : tasks) {
    cout << "[" << t.id << "] " << t.description << " | " << t.status
         << " | created: " << t.createdAt << " | updated: " << t.updatedAt
         << endl;
  }
}

int main(int argc, char** argv) {
  try {
    validateArgumentCount(argc, 2);
    const string command = argv[1];

    TaskManager manager(filename);
    if (command == "add") {
      validateArgumentCount(argc, 3, "Task description required for 'add'");
      manager.addTask(argv[2]);
    } else if (command == "update") {
      validateArgumentCount(
          argc, 4, "Task ID and new description required for 'update'");
      manager.updateTask(stoi(argv[2]), argv[3]);
    } else if (command == "delete") {
      validateArgumentCount(argc, 3, "Task ID required for 'delete'");
      manager.deleteTask(stoi(argv[2]));
    } else if (command == "mark-in-progress") {
      validateArgumentCount(argc, 3, "Task ID required for 'mark-in-progress'");
      manager.markTaskStatus(stoi(argv[2]), "in-progress");
    } else if (command == "mark-done") {
      validateArgumentCount(argc, 3, "Task ID required for 'mark-done'");
      manager.markTaskStatus(stoi(argv[2]), "done");
    } else if (command == "list") {
      if (argc > 2) {
        auto tasks = manager.listTasks(string(argv[2]));
        printTasks(tasks);
      } else {
        auto tasks = manager.listTasks();
        printTasks(tasks);
      }
    } else {
      throw invalid_argument("Unknown command: " + command);
    }

  } catch (exception& e) {
    cerr << "Error: " << e.what() << endl;
  }

  return 0;
}