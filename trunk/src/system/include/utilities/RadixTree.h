/*
 * Copyright (c) 2008 James Molloy, Jörg Pfähler, Matthew Iselin
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef KERNEL_UTILITIES_RADIX_TREE_H
#define KERNEL_UTILITIES_RADIX_TREE_H

#include <processor/types.h>

/** @addtogroup kernelutilities
 * @{ */

/** Dictionary class, aka Map for string keys. This is
 *  implemented as a Radix Tree - also known as a Patricia Trie.
 * \brief A key/value dictionary for string keys. */
template<class E>
class RadixTree;

/** Tree specialisation for void* */
template<>
class RadixTree<void*>
{
private:
  /** Tree node. */
  class Node
  {
    String key;
    void *value;
    struct Node *children;
    struct Node *parent;
    struct Node *next;
    struct Node *prev;

    /** Get the next data structure in the list
     *\return pointer to the next data structure in the list */
    Node *next()
    {
      if (children)
        return children;
      else if (next)
        return next;
      else
      {
        Node *n = n->parent;
        while (n)
        {
          if (n->next)
            return n;
          n = n->parent;
        }
        return 0;
      }
    }
    /** Get the previous data structure in the list
     *\return pointer to the previous data structure in the list  
     * \note Not implemented! */ 
    Node *previous()
      {return 0;}
  };

public:

  /** Type of the bidirectional iterator */
  typedef ::Iterator<void*, Node>       Iterator;
  /** Type of the constant bidirectional iterator */
  typedef Iterator::Const               ConstIterator;

  /** The default constructor, does nothing */
  RadixTree();
  /** The copy-constructor
   *\param[in] x the reference object to copy */
  RadixTree(const RadixTree &x);
  /** The destructor, deallocates memory */
  ~RadixTree();

  /** The assignment operator
   *\param[in] x the object that should be copied */
  RadixTree &operator = (const RadixTree &x);

  /** Get the number of elements in the Tree
   *\return the number of elements in the Tree */
  size_t count() const;
  /** Add an element to the Tree.
   *\param[in] key the key
   *\param[in] value the element */
  void insert(String key, void *value);
  /** Attempts to find an element with the given key.
   *\return the element found, or NULL if not found. */
  void *lookup(String key);
  /** Attempts to remove an element with the given key. */
  void remove(String key);

  /** Clear the tree */
  void clear();

  /** Get an iterator pointing to the beginning of the List
   *\return iterator pointing to the beginning of the List */
  inline Iterator begin()
  {
    return Iterator(root);
  }
  /** Get a constant iterator pointing to the beginning of the List
   *\return constant iterator pointing to the beginning of the List */
  inline ConstIterator begin() const
  {
    return ConstIterator(root);
  }
  /** Get an iterator pointing to the end of the List + 1
   *\return iterator pointing to the end of the List + 1 */
  inline Iterator end()
  {
    return Iterator();
  }
  /** Get a constant iterator pointing to the end of the List + 1
   *\return constant iterator pointing to the end of the List + 1 */
  inline ConstIterator end() const
  {
    return ConstIterator();
  }

private:
  /** Internal function to delete a subtree. */
  void deleteNode(Node *node);
  /** Internal function to create a copy of a subtree. */
  Node *cloneNode(Node *node);

  /** Number of items in the tree. */
  int nItems;
  /** The tree's root. */
  Node *root;
};

#endif

