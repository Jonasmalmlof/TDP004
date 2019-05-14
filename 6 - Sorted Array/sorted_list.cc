#include <iostream>
#include <string>
#include "sorted_list.h"

// Kommentarer för vad som behöver kompletteras:
// 1) movetilldelning och movekonstruktor ska inte använda copy,
//    det går att lösa utan att kopiera.
// 2) Det räcker med att kolla varje element max 1 gång vid en copy,
//    en lista som innehåller 10000 objekt tar 500000% längre tid att
//    kopiera med den nuvarande lösningen.
// 3) parametrar som inte modifieras ska vara konstanta referenser
//    (gäller alla icke-primitiva typer) (finns minst 3 ställen där
//    detta saknas)
// 4) Alla icke-void funktioner Måste returnera något.
//
// Extra kommentar:
//    Skriv kommentarer i koden, ha som vana att göra det, det hjälper
//    med att förstå när man kollar på koden vid ett senare tillfälle,
//    och det kommer vara till stor hjälp senare i projektet.
//

Sorted_List::Sorted_List() {}

Sorted_List::Sorted_List(Sorted_List const &source)
{
  copy(source);
}

Sorted_List::Sorted_List(Sorted_List &&source)
{
  first = source.first;
  source.first=nullptr;
}

Sorted_List::~Sorted_List()
{
  remove_all();

  // Borde inte first vara nullptr efter en "remove_all"?
  //Fixat
}

Sorted_List& Sorted_List::operator= (Sorted_List const &rhs)
{
  copy(rhs);
  return *this;
}

Sorted_List& Sorted_List::operator= (Sorted_List &&rhs)
{
  if( this!=&rhs )
  {
    std::swap(first,rhs.first);
  }
  return *this;
}

bool Sorted_List::is_empty() const
{
  return ( size() == 0 );
}

int Sorted_List::size() const
{
  int size {};
  Node *current = first;
  while ( current != nullptr )
  {
    ++size;
    current = current->next;
  }
  return size;
}

int Sorted_List::get_value(int index) const
{
  int step {};
  Node *current = first;
  while ( step <= index && current != nullptr )
  {
    if ( step == index )
    {
      return current->value;
    }
    current = current->next;
    ++step;
  }
  return 0;
}

void Sorted_List::copy(Sorted_List const &source)
{
  remove_all();
  if ( !source.is_empty() )
  {
    first = new Node{*(source.first)};;
    Node *current = first;
    while( current->next != nullptr )
    {
      current->next = new Node{*(current->next)};
      current=current->next;
    }
  }
}

void Sorted_List::insert(int value)
{
  insert(first, value);
}

void Sorted_List::insert(Node *&node, int value)
{
  if ( node == nullptr || node->value > value )
  {
    node = new Node{value,node};
  }
  else
  {
    insert(node->next, value);
  }
}

void Sorted_List::remove(int index)
{
  if ( index == 0 && first != nullptr )
  {
    Node *temp = first;
    delete first;
    first = temp->next;
  }
  else
  {
    Node *current = first;
    int step{};
    while ( current != nullptr && step < index )
    {
      if ( step == index-1 )
      {
        Node *next = current->next;
        if ( next != nullptr )
        {
          Node *temp = next->next;
          delete next;
          current->next = temp;
        }
        break;
      }
      current = current->next;
      ++step;
    }
  }
}

void Sorted_List::print() const
{
  std::string output {};

  for(int step {}; step < size(); ++step)
  {
    output = output + std::to_string(get_value(step)) + ", ";
  }

  output = output.substr(0, output.size()-2);

  std::cout << output << std::endl;
}

void Sorted_List::remove_all()
{
  while ( first != nullptr )
  {
    remove(0);
  }
}
