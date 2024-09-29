
#pragma once
#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;

struct Data_Record {
  int license;
  string name;
  string owner;
  Data_Record *next;

  // Constructor
  Data_Record(int license_value, const string name_value, const string owner_value)
      : license(license_value), name(name_value), owner(owner_value), next(nullptr) {}

  string string_rep();
};

class Hash_Table {
private:
  Data_Record **table;
  int size;
  int num_of_elements;
  const float load_factor_threshold = 0.75;

  int hash_function(int license) const;
  void rehash();

public:
  Hash_Table(int table_size);
  ~Hash_Table();

  void insert(Data_Record *new_record);
  Data_Record *search(int license);
  int remove(int license);
  void display() const;
};
