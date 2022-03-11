#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>

class Sparse {
   public :
      // creates the zero polynomial
      // the default character used as default is 'x'
      Sparse();
      
      // creates a sparse polynomial with one term   c*x^n
      Sparse(int c, int n);

      // returns true if it is the zero polynomial (the constant 0), false otherwise
      bool isZeroSparse() const;
         
      // returns the degree of the sparse polynomial
      // as a special case, it returns -1 for the zero polynomial
      int degree() const;
      
      // returns the coefficient of the term of degree n 
      // if there is no term with degree n, return 0
      int coefficient(int n) const;
      
      // reads the sparse polynomial using the input stream passed
      // the user is asked (with std::cout) to enter the number of terms
      // followed by pairs of integers for a term for the coefficient and degree
      // 
      // the zero polynomial can be entered as the coefficient 0 
      // followed by any degree
      // 
      // Note that internally there are no nodes with a zero coefficient so the
      // zero polynomial is a special case
      // 
      // Hint: if the coefficient of the term is 0, do not insert it into 
      // the sparse polynomial
      friend std::istream& operator >> (std::istream&, Sparse&);
      
      // prints the sparse polynomial with the variable (set with setPrintVariable)
      friend std::ostream& operator << (std::ostream&, const Sparse&);

      // multiply the sparse polynomial by the (scalar) constant c
      // c could be negative
      // returns a new sparse polynomial 
      // multiplying by c=0 returns the zero polynomial
      Sparse operator *(int c) const;
      
      // add the sparse polynomial f to the sparse polynomial g i.e. f + g
      // return the sum as a new polynomial
      friend Sparse operator + (const Sparse& f, const Sparse& g);

      // subtract the sparse polynomial g from the sparse polynomial f  i.e. f - g
      // return the difference as a new polynomial
      // Hint: use the operator * and the operator +
      friend Sparse operator - (const Sparse& f, const Sparse& g);
         
      // changes the character used to output the sparse polynomial
      // e.g. x^2 if variable is 'x' or y^2 is variable is 'y'
      void setPrintVariable(char variable);
      
      // returns the variable used in outputting the sparse polynomial
      char getPrintVariable() const;
      
      // copy constructor
      Sparse(const Sparse&); 
      
      // overloaded assignment operator
      Sparse& operator = (const Sparse&);
      
      // destructor
      ~Sparse();

      // BONUS
      // compute the derivative of the sparse polynomial
      Sparse derivative() const;
      
      
   private:
      struct Term {
         int coeff;
         int degree;
      };
      
      
      // a node in a linked list that represents the sparse polynomial
      struct Node {
         Term* term;  // CPSC 1160 use a pointer as defined here
         Node* link;
      };
      
      // The linked list poly is sorted in ascending order on the degree 
      // so that polynomial addition and subtraction can be done in linear time 
      // using merging. 
      // The insert operation needs to insert the term in order 
      // and if a term with the  same degree is already there, 
      // add the term's coefficient to that coefficient
      // So poly is always sorted and never has duplicate terms nor two terms
      // with the same degree.
      // Do not store a term with a zero coefficient (with the exception of
      // the zero polynomial which you need not represent with a struct Term )
      Node * poly;
      
      // when outputting the polynomial, 
      // use the variable as the output character
      char variable = 'x';  // initialize to x (default value)
      
      // the insert function is used in reading into poly 
      // i.e. in the friend function that overloads the operator >>  
      // insert the (already allocated) term t into this->poly
      void insert(Term *t);
      
      // insert the (already allocated) term t into the linked list p
      // no copy of t is made
      static Node* insert(Term *t, Node *p);
      
      //reverses the linklist
      void reverse();

};

#endif
