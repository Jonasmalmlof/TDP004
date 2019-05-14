// This test program uses a test framework supporting TDD and BDD.
// You are not required to use the framework, but encouraged to.
// Documentation:
// https://github.com/philsquared/Catch/blob/master/docs/tutorial.md

// You ARE however required to implement all test cases outlined here,
// even if you do it by way of your own function for each case.  You
// are recommended to solve the cases in order, and rerun all tests
// after you modify your code.

// This define lets Catch create the main test program
// (Must be in only one place!)
#include "catch.hpp"
#include "sorted_list.h"

#include <random>

//=======================================================================
// Test cases
//=======================================================================

TEST_CASE( "Create an empty list" ) 
{
    Sorted_List l{};

    REQUIRE( l.is_empty() );
    REQUIRE( l.size() == 0 );
}

TEST_CASE( "Insert an item in an empty list" ) 
{
    Sorted_List l{};

    l.insert(5);
  
    REQUIRE( !l.is_empty() );
    REQUIRE( !l.size() == 0 );
  
}

SCENARIO( "Empty lists" ) 
{
  
    GIVEN( "An empty list" ) 
    {
	Sorted_List l{};

	REQUIRE( l.is_empty() );
	REQUIRE( l.size() == 0 );
    
	WHEN( "an item is inserted" )
	{

          l.insert(5);
      
	    THEN( "the size increase and the item is first in the list" )
	    {
		REQUIRE( !l.is_empty()  );
		REQUIRE( l.size() == 1 );
                REQUIRE( l.get_value(0) == 5 );
	    }
	}

	WHEN( "an item is removed" )
	{
          l.remove(0);
      
	    THEN( "the list is still empty" )
	    {
              REQUIRE( l.size() == 0 );
              REQUIRE( l.is_empty() );
	    }
	}
    
	WHEN( "the list is copied to a new list" )
	{

          Sorted_List l2{l};
      
	    THEN( "the new list is also empty" )
	    {
		REQUIRE( l2.is_empty() );
		REQUIRE( l2.size() == 0 );
	    }
	}
    
	WHEN( "the list is copied to an existing non-empty list" )
	{
          Sorted_List l3{};
          l3.insert(5);
          l3.insert(9);
          l3.insert(2);
          l3 = l;
      
	    THEN( "the existing list is also empty" )
	    {
              REQUIRE( l.is_empty() );
              REQUIRE( l.size() == 0 );
              REQUIRE( l3.is_empty() );
              REQUIRE( l3.size() == 0 );
	    }
      
	}
    }
}

SCENARIO( "Single item lists" )
{

    GIVEN( "A list with one item in it" )
    {
      Sorted_List l{};
      l.insert(3);
    
	WHEN( "a smaller item is inserted" )
	{
          l.insert(2);
          
          THEN( "the smaller item appears first in the list" )
	  {
            REQUIRE( l.size() == 2);
            REQUIRE( l.get_value(0) == 2 );
            REQUIRE( l.get_value(1) == 3 );
	  }
	}
	WHEN( "a larger item is inserted" )
	{
          l.insert(9);
	    THEN( "the larger item appears last in the list" )
	    {
              REQUIRE( l.size() == 2);
              REQUIRE( l.get_value(0) == 3 );
              REQUIRE( l.get_value(1) == 9 );
	    }
	}
	WHEN( "an item is removed" )
	{
          l.remove(0);
	    THEN( "the list is empty" )
	    {
              REQUIRE( l.is_empty() );
              REQUIRE( l.size() == 0 );
	    }
	}
	WHEN( "the list is copied to a new list" )
	{
          Sorted_List l2{l};
	    THEN( "The new list is identical to the original" )
	    {
              REQUIRE( l.get_value(0) == l2.get_value(0) );
              REQUIRE( l.size() == l2.size() );
	    }
	}
	WHEN( "the list is copied to an existing non-empty list" )
	{
          Sorted_List l2{};
          l2.insert(5);
          l2.insert(7);
          l2 = l;
          
	    THEN( "the list is identical to the original list" )
	    {
              REQUIRE( l.size() == l2.size() );
              REQUIRE( l.get_value(0) == l2.get_value(0) );
	    }
	}
    }
}

SCENARIO( "Multi-item lists" )
{

    GIVEN( "A list with five items in it" )
    {

      Sorted_List l{};
      l.insert(2);
      l.insert(4);
      l.insert(5);
      l.insert(6);
      l.insert(8);
    
	WHEN( "an item smaller than all other is inserted" )
	{
          l.insert(1);
          THEN( "the inserted item is the first index" )
          {
            REQUIRE( l.get_value(0) == 1 );
            REQUIRE( l.size() == 6 );
          }
	}
	WHEN( "an item larger than all other is inserted" )
	{
          l.insert(9);
          THEN( "the inserted item is the last index" )
          {
            REQUIRE( l.get_value(5) == 9 );
            REQUIRE( l.size() == 6 );
          }
	}
	WHEN( "an item smaller than all but one item is inserted" )
	{
          l.insert(3);
          THEN( "the inserted item is the second index" )
          {
            REQUIRE( l.get_value(1) == 3 );
            REQUIRE( l.size() == 6 );
          }
	}
	WHEN( "an item larger than all but one item is inserted" )
	{
          l.insert(7);
          THEN( "the inserted item is the second to last index" )
          {
            REQUIRE( l.get_value(4) == 7 );
            REQUIRE( l.size() == 6 );
          }
	}
	WHEN( "an item is removed" )
	{
          l.remove(2);
          THEN( "the removed item is no longer in its index" )
          {
            REQUIRE( l.get_value(2) == 6 );
            REQUIRE( l.size() == 4 );
          }
	}
	WHEN( "all items are removed" )
	{
          l.remove(4);
          l.remove(3);
          l.remove(2);
          l.remove(1);
          l.remove(0);
          THEN( "the list is empty" )
          {
            REQUIRE( l.is_empty() );
            REQUIRE( l.size() == 0 );
          }
	}
	WHEN( "the list is copied to a new list" )
	{
          Sorted_List l2{l};
          THEN( "the new list has the same values and size" )
          {
            REQUIRE( l.get_value(0) == l2.get_value(0) );
            REQUIRE( l.get_value(4) == l2.get_value(4) );
            REQUIRE( l.size() == l2.size() );
          }
	}
	WHEN( "the list is copied to an existing non-empty list" )
	{
          Sorted_List l2{};
          l2.insert(19);
          l2.insert(500);
          l2 = l;
          THEN( "the lists have the same values and size" )
          {
            REQUIRE( l.get_value(0) == l2.get_value(0) );
            REQUIRE( l.get_value(4) == l2.get_value(4) );
            REQUIRE( l.size() == l2.size() );
          }
	}
    }
}

SCENARIO( "Lists can be copied" )
{

    GIVEN( "A list with five items in it, and a new copy of that list" )
    {
      Sorted_List l{};
      l.insert(1);
      l.insert(2);
      l.insert(5);
      l.insert(10);
      l.insert(100);
      Sorted_List l2{l};
      
	WHEN( "the original list is changed" )
	{
          l.remove(0);
	    THEN( "the copy remain unmodified" )
	    {
              REQUIRE( l.size() == 4 );
              REQUIRE( l2.size() == 5 );
	    }
	}

	WHEN( "the copied list is changed" )
	{
          l2.insert(1000);
          THEN( "the original remain unmodified" )
	    {
              REQUIRE( l.size() == 5 );
              REQUIRE( l2.size() == 6 );
	    }
	}
    }
}

SCENARIO( "Lists can be heavily used" )
{

    GIVEN( "A list with 1000 random items in it" )
    {

      Sorted_List l{};
	// create the given list with 1000 random items
	std::random_device rd;
	std::uniform_int_distribution<int> uniform(1,1000);
    
	for (int i{0}; i < 1000; ++i)
	{
	    int random { uniform(rd) }; // generate a random number
	    l.insert(random);
	}
    
	WHEN( "the list have 1000 random numbers inserted" )
	{
          for (int i{0}; i < 1000; ++i)
          {
	    int random { uniform(rd) }; // generate a random number
	    l.insert(random);
          }
          THEN( "the list have 2000 items in correct order" )
          {
            bool correct_order = true;
            for (int i {0}; i<1999; ++i)
            {
              if( l.get_value(i) > l.get_value(i+1) )
              {
                correct_order = false;
              }
            }
            REQUIRE( correct_order );
            REQUIRE( l.size() == 2000 );
          }
	    // (assumes unique inserts or duplicates allowed)
	}

	WHEN( "the list have 1000 random numbers removed" )
	{
          int random_index {};
          for (int i {0}; i<1000; ++i)
          {     
            std::uniform_int_distribution<int> rand_int(0,l.size()-1);
            int rand { rand_int(rd) };
            l.remove(rand);
          }
          THEN( "the list is empty" )
          {
            REQUIRE( l.size() == 0 );
            REQUIRE( l.is_empty() );
          }
	    // (assumes successful removes)
	}
    }
}

Sorted_List trigger_move(Sorted_List l)
{
  l.remove(0);
    return l;
}

SCENARIO( "Lists can be passed to functions" )
{

    GIVEN( "A list with 5 items in it" )
    {

	Sorted_List given{};
	given.insert(1);
        given.insert(2);
        given.insert(3);
        given.insert(4);
        given.insert(5);
  
	WHEN( "the list is passed to trigger_move()" )
	{

	    Sorted_List l{ trigger_move(given) };
            
	    THEN( "the given list is unchanged and the resulting list has the change" )
	    {
              REQUIRE( given.size() == l.size()+1 );
	    }
	}

        WHEN( "the trigger move operator is used" )
        {
          Sorted_List l{};

          l = trigger_move(given);

          THEN( "the given list remains and the resulting list has the change" )
          {
            REQUIRE( given.size() == l.size()+1 );
          }
        }
    }
}

// In addition you must of course verify that the list is printed
// correct and that no memory leaks occur during use. You can solve
// the printing part on your own. Here's how to run the (test) program
// when you check for memory leaks:

// You must of course verify that no memory leaks occur during use.
// To do so, an external program must be used to track what memory
// is allocated and free'd, you can run such a program like so:
//
// $ valgrind --tool=memcheck ./a.out

// Finally you need to check that you can do all operations that make
// sense also on a immutable list (eg all operations but insert):  
void use_const_list(Sorted_List const& l)
{
  l.size();
  l.get_value(0);
  l.is_empty();
  l.print();
}

SCENARIO( "Lists can be passed to const functions" )
{

    GIVEN( "A list with 5 items in it" )
    {

	Sorted_List given{};
	given.insert(3);
        given.insert(4);
        given.insert(2);
        given.insert(5);
        given.insert(1);
  
	WHEN( "the list is passed to use_const_list()" )
	{

          use_const_list(given);
      
	    THEN( "the given list remains unchanged" )
	    {
              REQUIRE( given.size() == 5 );
              REQUIRE( given.get_value(0) == 1 );
              REQUIRE( given.get_value(4) == 5 );
	    }
	}
    }
}

// Solve one TEST_CASE or WHEN at a time!
//
// Move this comment and following #if 0 down one case at a time!
// Make sure to close any open braces before this comment.
// The #if 0 will disable the rest of the file.
#if 0

#endif
