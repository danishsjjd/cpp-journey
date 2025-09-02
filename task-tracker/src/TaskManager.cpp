#include "TaskManager.hpp"

#include <iomanip>
#include <iostream>
#include <stdexcept>

namespace {
std::string escape(const std::string &s) {
  std::string out;
  out.reserve(s.size());
  for (char c : s) {
    switch (c) {
      case '\\':
        out += "\\\\";
        break;
      case '"':
        out += "\\\"";
        break;
      case '\n':
        out += "\\n";
        break;
      case '\r':
        out += "\\r";
        break;
      case '\t':
        out += "\\t";
        break;
      default:
        out += c;
    }
  }
  return out;
}
}  // namespace

TaskManager::TaskManager(const std::string &filename) : filename(filename) {}

std::string TaskManager::getCurrentDateTime() {
  std::time_t now = std::time(nullptr);
  std::tm *tmPtr = std::localtime(&now);
  char buf[32];
  std::strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%S", tmPtr);
  return std::string(buf);
}

int TaskManager::getNextId(const std::vector<Task> &tasks) {
  int maxId = 0;
  for (const auto &t : tasks) {
    if (t.id > maxId) maxId = t.id;
  }
  return maxId + 1;
}

bool TaskManager::addTask(const std::string &description) {
  auto tasks = loadTasks();
  Task t;
  t.id = getNextId(tasks);
  t.description = description;
  t.status = "todo";
  t.createdAt = t.updatedAt = getCurrentDateTime();
  tasks.push_back(t);
  if (!saveTasks(tasks)) return false;
  std::cout << "Task added successfully (ID: " << t.id << ")" << std::endl;
  return true;
}

bool TaskManager::updateTask(int id, const std::string &newDescription) {
  auto tasks = loadTasks();
  bool found = false;
  for (auto &t : tasks) {
    if (t.id == id) {
      t.description = newDescription;
      t.updatedAt = getCurrentDateTime();
      found = true;
      break;
    }
  }
  if (!found) {
    std::cerr << "Task not found: " << id << std::endl;
    return false;
  }
  if (!saveTasks(tasks)) return false;
  std::cout << "Task updated successfully (ID: " << id << ")" << std::endl;
  return true;
}

bool TaskManager::deleteTask(int id) {
  auto tasks = loadTasks();
  std::vector<Task> updated;
  updated.reserve(tasks.size());
  bool removed = false;
  for (auto &t : tasks) {
    if (t.id == id) {
      removed = true;
      continue;
    }
    updated.push_back(t);
  }
  if (!removed) {
    std::cerr << "Task not found: " << id << std::endl;
    return false;
  }
  if (!saveTasks(updated)) return false;
  std::cout << "Task deleted successfully (ID: " << id << ")" << std::endl;
  return true;
}

bool TaskManager::markTaskStatus(int id, const std::string &status) {
  if (status != "todo" && status != "in-progress" && status != "done") {
    std::cerr << "Invalid status: " << status << std::endl;
    return false;
  }
  auto tasks = loadTasks();
  bool found = false;
  for (auto &t : tasks) {
    if (t.id == id) {
      t.status = status;
      t.updatedAt = getCurrentDateTime();
      found = true;
      break;
    }
  }
  if (!found) {
    std::cerr << "Task not found: " << id << std::endl;
    return false;
  }
  if (!saveTasks(tasks)) return false;
  std::cout << "Task marked as '" << status << "' (ID: " << id << ")"
            << std::endl;
  return true;
}

std::vector<Task> TaskManager::listTasks(
    const std::optional<std::string> &status) {
  auto tasks = loadTasks();
  if (status && *status != "todo" && *status != "in-progress" &&
      *status != "done") {
    throw std::invalid_argument("Invalid filter: " + *status);
  }
  if (status) {
    std::vector<Task> filtered;
    for (const auto &t : tasks) {
      if (t.status == *status) filtered.push_back(t);
    }
    return filtered;
  }
  return tasks;
}

// Minimal JSON writer (not pretty printed except newlines between objects)
bool TaskManager::saveTasks(const std::vector<Task> &tasks) {
  std::ofstream ofs(filename, std::ios::trunc);
  if (!ofs.is_open()) {
    std::cerr << "Failed to open file for writing: " << filename << std::endl;
    return false;
  }
  ofs << "[";
  for (size_t i = 0; i < tasks.size(); ++i) {
    const auto &t = tasks[i];
    ofs << "{\"id\":" << t.id << ",\"description\":\"" << escape(t.description)
        << "\",\"status\":\"" << t.status << "\",\"createdAt\":\""
        << t.createdAt << "\",\"updatedAt\":\"" << t.updatedAt << "\"}";
    if (i + 1 < tasks.size()) ofs << ",";
  }
  ofs << "]";
  return true;
}

// Very small JSON parser for our controlled format only
std::vector<Task> TaskManager::loadTasks() {
  std::vector<Task> tasks;
  if (!std::filesystem::exists(filename)) {
    return tasks;  // empty
  }
  std::ifstream ifs(filename);
  if (!ifs.is_open()) {
    std::cerr << "Failed to open file: " << filename << std::endl;
    return tasks;
  }
  std::stringstream buffer;
  buffer << ifs.rdbuf();
  std::string content = buffer.str();
  size_t i = 0;
  while (i < content.size() && isspace(static_cast<unsigned char>(content[i])))
    ++i;
  if (i >= content.size() || content[i] != '[') {
    std::cerr << "Corrupt tasks file (expected '[')" << std::endl;
    return tasks;
  }
  ++i;  // skip [
  while (i < content.size()) {
    while (i < content.size() &&
           isspace(static_cast<unsigned char>(content[i])))
      ++i;
    if (i < content.size() && content[i] == ']') break;
    if (i >= content.size() || content[i] != '{') {
      // skip unexpected
      ++i;
      continue;
    }
    // capture object
    int brace = 0;
    size_t start = i;
    while (i < content.size()) {
      if (content[i] == '{')
        ++brace;
      else if (content[i] == '}') {
        --brace;
        if (brace == 0) {
          ++i;  // include closing
          break;
        }
      }
      ++i;
    }
    std::string obj = content.substr(start, i - start);
    // parse fields
    Task t{};
    auto getString = [&](const std::string &key) -> std::optional<std::string> {
      std::string pattern = "\"" + key + "\"";
      size_t pos = obj.find(pattern);
      if (pos == std::string::npos) return std::nullopt;
      pos = obj.find(':', pos);
      if (pos == std::string::npos) return std::nullopt;
      ++pos;
      while (pos < obj.size() && isspace(static_cast<unsigned char>(obj[pos])))
        ++pos;
      if (pos >= obj.size()) return std::nullopt;
      if (obj[pos] == '"') {
        ++pos;
        std::string val;
        while (pos < obj.size() && obj[pos] != '"') {
          if (obj[pos] == '\\' && pos + 1 < obj.size()) {
            char esc = obj[pos + 1];
            switch (esc) {
              case 'n':
                val += '\n';
                break;
              case 'r':
                val += '\r';
                break;
              case 't':
                val += '\t';
                break;
              case '"':
                val += '"';
                break;
              case '\\':
                val += '\\';
                break;
              default:
                val += esc;
            }
            pos += 2;
          } else {
            val += obj[pos++];
          }
        }
        return val;
      } else {  // number
        size_t startNum = pos;
        while (
            pos < obj.size() &&
            (isdigit(static_cast<unsigned char>(obj[pos])) || obj[pos] == '-'))
          ++pos;
        return obj.substr(startNum, pos - startNum);
      }
    };
    auto idStr = getString("id");
    if (idStr) t.id = std::stoi(*idStr);
    if (auto d = getString("description")) t.description = *d;
    if (auto s = getString("status")) t.status = *s;
    if (auto c = getString("createdAt")) t.createdAt = *c;
    if (auto u = getString("updatedAt")) t.updatedAt = *u;
    if (t.status.empty()) t.status = "todo";
    tasks.push_back(t);
    // skip comma
    while (i < content.size() &&
           isspace(static_cast<unsigned char>(content[i])))
      ++i;
    if (i < content.size() && content[i] == ',') ++i;
  }
  return tasks;
}
