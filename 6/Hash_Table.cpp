#include "Hash_Table.hpp"

string Data_Record::string_rep() {
  string output = "";
  output += "[номер лицензии: " + to_string(license) + ", название: " + name +
            ", учредитель: " + owner + "]";
  return output;
}

Hash_Table::Hash_Table(int table_size) : size(table_size), num_of_elements(0) {
  table = new Data_Record *[size];
  for (int i = 0; i < size; i++) {
    table[i] = nullptr;
  }
}

Hash_Table::~Hash_Table() {
  for (int i = 0; i < size; i++) {
    Data_Record *current = table[i];
    while (current != nullptr) {
      Data_Record *temp = current;
      current = current->next;
      delete temp;
    }
  }
  delete[] table;
}

int Hash_Table::hash_function(int license) const { return license % size; }

void Hash_Table::rehash() {
  cout << "Rehashing: increasing table size to " << size * 2 << endl;
  int old_size = size;

  // Creating new empty table of twice the size
  size *= 2;
  Data_Record **new_table = new Data_Record *[size];
  for (int i = 0; i < size; i++) {
    new_table[i] = nullptr;
  }

  // Moving data from old table to the new
  for (int i = 0; i < old_size; i++) {
    Data_Record *current = table[i];
    while (current != nullptr) {
      int new_index = hash_function(current->license);
      Data_Record *next_record = current->next;

      current->next = new_table[new_index];
      new_table[new_index] = current;

      current = next_record;
    }
  }

  delete[] table;
  table = new_table;
}

void Hash_Table::insert(Data_Record *new_record) {
  int index = hash_function(new_record->license);
  new_record->next = table[index];
  table[index] = new_record;

  num_of_elements++;
  if ((static_cast<float>(num_of_elements) / size) > load_factor_threshold) {
    rehash();
  }
}

Data_Record *Hash_Table::search(int license) {
  int index = hash_function(license);
  Data_Record *current = table[index];
  while (current != nullptr) {
    if (current->license == license) {
      return current;
    }
    current = current->next;
  }
  return nullptr;
}

int Hash_Table::remove(int license) {
  int index = hash_function(license);
  Data_Record *current = table[index];
  Data_Record *prev = nullptr;

  while (current != nullptr) {
    if (current->license == license) {
      // Element to delete is first in chain
      if (prev == nullptr) {
        table[index] = current->next;
      }

      else {
        prev->next = current->next;
      }
      delete current;
      num_of_elements--;
      return 0; // Return code: data record successfully deleted
    }
    prev = current;
    current = current->next;
  }
  return 1; // Return code: data record not found
}

void Hash_Table::display() const {
  bool empty_flag = true;
  for (int i = 0; i < size; i++) {
    Data_Record *current = table[i];
    if (current != nullptr) {
      empty_flag = false;
      cout << "Index " << i << ": ";
      while (current != nullptr) {
        cout << current->string_rep() << endl;
        current = current->next;
      }
      cout << endl;
    }
  }
  if (empty_flag) {
    cout << "No data" << endl;
  }
}