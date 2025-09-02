#pragma once
#include <ctime>
#include <filesystem>
#include <fstream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

struct Task {
  int id;
  std::string description;
  std::string status;  // todo, in-progress, done
  std::string createdAt;
  std::string updatedAt;
};

class TaskManager {
 public:
  TaskManager(const std::string& filename);
  bool addTask(const std::string& description);
  bool updateTask(int id, const std::string& newDescription);
  bool deleteTask(int id);
  bool markTaskStatus(int id, const std::string& status);
  std::vector<Task> listTasks(
      const std::optional<std::string>& status = std::nullopt);
  static std::string getCurrentDateTime();

 private:
  std::string filename;
  std::vector<Task> loadTasks();
  bool saveTasks(const std::vector<Task>& tasks);
  int getNextId(const std::vector<Task>& tasks);
};
