/* Iterator constructors (default and with initialization) */

// default zero-parameter constructor, just set pointer 'current' to nullptr
template <typename T>
List<T>::const_iterator::const_iterator() : current{nullptr} {}

// one-parameter constructor, set 'current' pointer to the given node pointer p
template <typename T>
List<T>::const_iterator::const_iterator(Node* p) : current{p} {}

// one-parameter constructor, call base class (const_iterator) constructor
template <typename T>
List<T>::iterator::iterator(Node* p) : const_iterator{p} {}

/* Dereferencing elements from iterators */

// return a reference to the corresponding element in the list (using 'current' pointer)
template <typename T>
T& List<T>::const_iterator::retrieve() const
{
  return current->data;
}

// returns a reference to the corresponding element in the list by calling retrieve() member function
template <typename T>
const T& List<T>::const_iterator::operator*() const
{
  return this->retrieve();
}

// returns a reference to the corresponding element in the list by calling retrieve() member function
template <typename T>
T& List<T>::iterator::operator*()
{
  return this->retrieve();
}

// returns a reference to the corresponding element in the list by calling retrieve() member function
template <typename T>
const T& List<T>::iterator::operator*() const
{
  return this->retrieve();
}

/* Increment/decrement operators overloading */

// prefix increment operator (++iterator)
template <typename T>
typename List<T>::const_iterator& List<T>::const_iterator::operator++()
{
  current = current->next; // advance pointer to next node in list
  return *this;
}

// postfix increment operator (iterator++) - less effective
template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator++(int)
{
  auto result = *this; // make copy of iterator (we should return original value)
  ++(*this); // re-use prefix increment operator
  return result; // return original iterator value
}

// prefix decrement operator (--iterator)
template <typename T>
typename List<T>::const_iterator& List<T>::const_iterator::operator--()
{
  current = current->prev; // advance pointer to prev node in list
  return *this;
}

// postfix decrement operator (iterator--) - less effective
template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator--(int)
{
  auto result = *this; // make copy of iterator (we should return original value)
  --(*this); // re-use prefix decrement operator
  return result; // return original iterator value
}

// prefix increment operator (++iterator)
template <typename T>
typename List<T>::iterator& List<T>::iterator::operator++()
{
  const_iterator::current = const_iterator::current->next; // we should use base class name for accessing 'current' here
  return *this;
}

// postfix increment operator (iterator++) - less effective
template <typename T>
typename List<T>::iterator List<T>::iterator::operator++(int)
{
  auto result = *this; // make copy of iterator (we should return original value)
  ++(*this); // re-use prefix increment operator
  return result; // return original iterator value
}

// prefix decrement operator (--iterator)
template <typename T>
typename List<T>::iterator& List<T>::iterator::operator--()
{
  const_iterator::current = const_iterator::current->prev; // we should use base class name for accessing 'current' here
  return *this;
}

// postfix decrement operator (iterator--) - less effective
template <typename T>
typename List<T>::iterator List<T>::iterator::operator--(int)
{
  auto result = *this; // make copy of iterator (we should return original value)
  --(*this); // re-use prefix decrement operator
  return result; // return original iterator value
}

/* Equality/inequality operators overloading */

// two iterators are equal if they refer to the same element so just compare pointers
template <typename T>
bool List<T>::const_iterator::operator==(const List<T>::const_iterator& rhs) const
{
   return (current == rhs.current);
}

// two iterators are equal if they refer to the same element (re-use == operator)
template <typename T>
bool List<T>::const_iterator::operator!=(const List<T>::const_iterator& rhs) const
{
  return !(*this == rhs);
}

/* List constructors (default, copy/move, initialization) and desctructor */

// default zero parameter constructor - call init method for setting fields
template <typename T>
List<T>::List()
{
  init();
}

// copy constructor - just copy all values from source list into this one
template <typename T>
List<T>::List(const List& rhs)
{
  init();

  for(auto iter = rhs.begin(); iter != rhs.end(); ++iter) // for all items in 'rhs' list
  {
    push_back(*iter); // put element from 'rhs' list into end of this list
  }
}

// copy semantic - just use std::move helper method for implementing this logic
template <typename T>
List<T>::List(List&& rhs)
{
  init();

  *this = std::move(rhs);
}

// initializing list with 'num' elements equal to 'val' - just add values internally
template <typename T>
List<T>::List(int num, const T& val)
{
  init();

  for(auto i = 0; i < num; ++i) // repeate 'num' times
  {
    push_back(val); // put 'val' element into list
  }

}

// initializiing list from other list using iterators
template <typename T>
List<T>::List(List<T>::const_iterator start, List<T>::const_iterator end)
{
  init();

  for(auto iter = start; iter != end; ++iter) // from 'start' till 'end' iterator
  {
    push_back(*iter); // put element from source list into end of this list
  }
}

// dectructor - free all used memory (just call 'clear' for preventing code duplication)                      
template <typename T>
List<T>::~List()
{
  clear();
}

/* Assigment operators overloading */

// copy assigment operator - just copy all members from source
template <typename T>
const List<T>& List<T>::operator=(const List<T>& rhs)
{
  List<T> tmp{rhs}; // First, make copy of right-hand side

  // Swap all members between this one and temporary object
  std::swap(theSize, tmp.theSize);
  std::swap(head, tmp.head);
  std::swap(tail, tmp.tail);

  return *this;
}

// move semantic assigment operator - just copy all members from source with checks
template <typename T>
List<T>& List<T>::operator=(List<T>&& rhs)
{
  if (this != &rhs) // check for self-assigment
  {
    clear(); // clear target

    // Swap all members between this one and source object
    std::swap(theSize, rhs.theSize);
    std::swap(head, rhs.head);
    std::swap(tail, rhs.tail);
  }

  return *this;
}

/* List operations (size, clear, reverse) */

// returns list size - just read value from private field 'theSize'
template <typename T>
int List<T>::size() const
{
  return theSize;
}

// returns true if list is empty - just check if value of private field 'theSize' equal to 0
template <typename T>
bool List<T>::empty() const
{
  return size() == 0;
}

// clear list - just call 'pop_front' method till list not empty
template <typename T>
void List<T>::clear()
{
  while (!empty()) // while size greater than 0
  {
    pop_front(); // remove first element in list (with memory freeing)
  }
}

// reverse list in-place (w/o creating new list or re-creating nodes)
template <typename T>
void List<T>::reverse()
{
  auto current = head; // starting from head node

  while(current != nullptr) // till current node is not last (next after last)
  {  
    std::swap(current->next, current->prev); // swap 'next' and 'prev' pointer values
    current = current->prev; // advance next node (we use 'prev' because we swap it before)
  }

  std::swap(head, tail); // swap 'head' and 'tail' nodes
}

/* List first/last element accessors */

// get first list element - just return data from 'head' node
template <typename T>
T& List<T>::front()
{
  return head->data;
}

// get first list element - just return data from 'head' node
template <typename T>
const T& List<T>::front() const
{
  return head->data;
}

// get last list element - just return data from 'tail' node
template <typename T>
T& List<T>::back()
{
  return tail->data;
}

// get last list element - just return data from 'tail' node
template <typename T>
const T& List<T>::back() const
{
  return tail->data;
}

/* List modificatin methods - insertions into front/back */

// insert element into front of the list (copy value version)
template <typename T>
void List<T>::push_front(const T& val)
{
  auto node = new Node(val); // create new node with passed value

  if (head != nullptr)
  {
    node->next = head; // link new node and old head
    head->prev = node;
  }
  head = node; // set new head node

  if (tail == nullptr) // if this node is first set tail node too
  {
    tail = head;
  }

  ++theSize; // change list size
}

// insert element into front of the list (move value version)
template <typename T>
void List<T>::push_front(T&& val)
{
  auto node = new Node(val); // create new node with passed value

  if (head != nullptr)
  {
    node->next = head; // link new node and old head
    head->prev = node;
  }
  head = node; // set new head node

  if (tail == nullptr) // if this node is first set tail node too
  {
    tail = head;
  }

  ++theSize; // change list size
}

// insert element into end of the list (copy value version)
template <typename T>
void List<T>::push_back(const T& val)
{
  auto node = new Node(val); // create new node with passed value

  if (tail != nullptr)
  {
    node->prev = tail; // link new node and old tail
    tail->next = node;
  }
  tail = node; // set new tail node

  if (head == nullptr) // if this node is first set head node too
  {
    head = tail;
  }

  ++theSize; // change list size
}

// insert element into end of the list (move value version)
template <typename T>
void List<T>::push_back(T&& val)
{
  auto node = new Node(val); // create new node with passed value

  if (tail != nullptr)
  {
    node->prev = tail; // link new node and old tail
    tail->next = node;
  }
  tail = node; // set new tail node

  if (head == nullptr) // if this node is first set head node too
  {
    head = tail;
  }

  ++theSize; // change list size
}

/* List modificatin methods - removing from front/back and remove by value */

// remove first element from list (and free memory used by head node)
template <typename T>
void List<T>::pop_front()
{
  auto todelete = head; // remember old head pointer for later deletion
 
  head = head->next; // set new head pointer - use second element

  if (head == nullptr) // if new head is nullptr list is empty
  {
    tail = nullptr; // set tail pointer to nullptr also
  }
  else
  {
    head->prev = nullptr; // just remove link to old head from new head
  }

  --theSize; // change list size

  delete todelete; // free memory
}

// remove last element from list (and free memory used by last node)
template <typename T>
void List<T>::pop_back()
{
  auto todelete = tail; // remember old tail pointer for later deletion

  tail = tail->prev; // set new tail pointer - use pre-tail element

  if (tail == nullptr) // if new tail is nullptr list is empty
  {
    head = nullptr; // set head pointer to nullptr also
  }
  else
  {
    tail->next = nullptr; // just remove link to old tail from new tail
  }

  --theSize; // change list size

  delete todelete; // free memory
}

// remove element from list by node value - find element and remove it
template <typename T>
void List<T>::remove(const T& val)
{
  for(auto iter = begin(); iter != end(); ++iter) // for each nodes in list
  {
    if (*iter == val) // if value from node equal to value for deletion...
    {
      erase(iter); // delete item and return
      return;
    }
  }
}

/* Helper methods for obtaining list iterators */

// return new iterator pointed to first element of the list
template <typename T>
typename List<T>::iterator List<T>::begin()
{
   return iterator(head);
}

// return new iterator pointed to first element of the list
template <typename T>
typename List<T>::const_iterator List<T>::begin() const
{
   return const_iterator(head);
}

// return new iterator pointed out of the list (end is exclusive)
template <typename T>
typename List<T>::iterator List<T>::end()
{
   return iterator(nullptr);
}

// return new iterator pointed out of the list (end is exclusive)
template <typename T>
typename List<T>::const_iterator List<T>::end() const
{
   return const_iterator(nullptr);
} 

/* List modification methods - insertion and deletion */

// insert element into list using iterator as insertion position (copy value version)
template <typename T>
typename List<T>::iterator List<T>::insert(List<T>::iterator itr, const T& val)
{
  auto node = itr.current; // store current node
  if (node == nullptr) // unable to insert into incorrect position
  {
    return;
  }

  auto new_node = new Node(val); // create new node for insertion

  new_node->next = node; // link new node and current iterator node
  new_node->prev = node->prev;

  node->prev = node; // link current iterator node and new node
  if (node->prev == nullptr) // insertion into begining of the list
  {
    head = new_node; // update head pointer
  }
  else
  {
    node->perv->next = node; // we insert new node before so we should update this pointer too
  }

  ++theSize; // change list size

  return iterator(new_node); // return new iterator pointed to new node
}

// insert element into list using iterator as insertion position (move value version)
template <typename T>
typename List<T>::iterator List<T>::insert(List<T>::iterator itr, T&& val)
{
  auto node = itr.current; // store current node
  if (node == nullptr) // unable to insert into incorrect position
  {
    return;
  }

  auto new_node = new Node(val); // create new node for insertion

  new_node->next = node; // link new node and current iterator node
  new_node->prev = node->prev;

  node->prev = node; // link current iterator node and new node
  if (node->prev == nullptr) // insertion into begining of the list
  {
    head = new_node; // update head pointer
  }
  else
  {
    node->perv->next = node; // we insert new node before so we should update this pointer too
  }

  ++theSize; // change list size

  return iterator(new_node); // return new iterator pointed to new node
}

// remove element from list using iterator position
template <typename T>
typename List<T>::iterator List<T>::erase(List<T>::iterator itr)
{
  auto node = itr.current; // store current node pointer

  if (node->prev != nullptr) // if current node is not head
  {
    node->prev->next = node->next; // update previous node - link it with next
  }
  else
  {
    head = node->next; // else just upate 'head' pointer
  }

  if (node->next != nullptr) // if current node is not tail
  {
    node->next->prev = node->prev; // update next node - link it with previous
  }
  else
  {
    tail = node->prev; // else just upate 'tail' pointer
  }

  ++itr; // advance iterator

  delete node; // free node memory
  --theSize; // change list size

  return itr;
}

// remove all items between start and end iterators (end is exclusive range)
template <typename T>
typename List<T>::iterator List<T>::erase(List<T>::iterator start, List<T>::iterator end)
{
  while(start != end) // for all elements between two iterators
  {
    start = erase(start); // erase item pointed by 'start' (and advance 'start' as result of 'erase' call)
  }

  return start;
}

/* Helper list methods - initialization and printing */

// initialize members using default values (for reducing copy-paste code)
template <typename T>
void List<T>::init()
{
  theSize = 0;
  head = nullptr;
  tail = nullptr;
}

// put all list items values into output stream using defined separator character
template <typename T>
void List<T>::print(std::ostream& os, char ofc) const
{
  for(auto itr = begin(); itr != end(); ++itr) // for all items in list
  {
    os << *itr << ofc; // put item value into stream + separator char
  }
}

/* List equality/inequality operators overloading */

// two lists are equal if size is equal and each elements value are equal
template <typename T>
bool operator== (const List<T>& lhs, const List<T>& rhs)
{
  if (lhs.size() != rhs.size()) // if sizes are not equal - return false
  {
    return false;
  }

  // we should iterate both lists head-to-head and compare item values
  for(auto lhs_itr = lhs.begin(), rhs_itr = rhs.begin(); lhs_itr != lhs.end(); ++lhs_itr, ++rhs_itr)
  {
      if (*lhs_itr != *rhs_itr) // if item values are not equal - return false
      {
        return false;
      }
  }

  return true; // it's possible only if all elements are equal
}

// two lists are equal if size is equal and each elements value are equal
template <typename T>
bool operator!= (const List<T>& lhs, const List<T>& rhs)
{
  return !(lhs == rhs); // re-use equality operator overload
}

// overload stream output operator - use print() method call
template <typename T>
std::ostream& operator<< (std::ostream& os, const List<T>& l)
{
  l.print(os);
  return os;
}