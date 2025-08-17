#include <iostream>
using namespace std;

struct Customer {
  short id;
  string name;
  string email;
};

int main() {
  Customer customer;

  cout << "ID: ";
  cin >> customer.id;

  cout << "Name: ";
  cin >> customer.name;

  cout << "Email: ";
  cin >> customer.email;

  cout << endl;
  cout << "ID: " << customer.id << " Name: " << customer.name
       << " Email: " << customer.email << endl;

  auto [id, name, email]{customer};
  auto [id1, name2, email3] = customer;

  return 0;
}