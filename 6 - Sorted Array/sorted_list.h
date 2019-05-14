#ifndef _SORTED_LIST_H_
#define _SORTED_LIST_H_

struct Node
{
  int value{};
  Node *next{nullptr};
};

class Sorted_List
{
public:
  Sorted_List();
  Sorted_List(Sorted_List const &source);
  Sorted_List(Sorted_List &&source);

  ~Sorted_List();

  Sorted_List& operator= (Sorted_List const &rhs);
  Sorted_List& operator= (Sorted_List &&rhs);
  
  bool is_empty() const;
  int size() const;
  int get_value(int index) const;
  void insert(int value);
  void remove(int index);
  void print() const;

private:
  void copy(Sorted_List const &source);
  void remove_all();
  void insert(Node *&node, int value);
  Node *first{nullptr};
};
#endif
