#include "Sparse.h"
#include <iostream>

// the zero polynomial i.e. the constant zero
//Initializes poly linklist to the nullptr
//if poly is nullptr then it is zero polynomial
Sparse::Sparse() {
   poly =  nullptr;
}

// basically, checks the representation of the zero polynomial 
// O(1)
//Zero polynomial has poly pointing to nullptr
//if poly is nullptr return true otherwise false
bool Sparse::isZeroSparse() const { 
   return this->poly==nullptr;
}

// changes this->variable to w
void Sparse:: setPrintVariable(char w) {
   this->variable = w;
}
      
// returns the variable used in outputting the polynomial
char Sparse::getPrintVariable() const {
   return this->variable;
}

// creates the term  c*x^n and sets the polynomial to this term
// O(1)

//if the coefficient is 0 it will initialize poly with nullptr that means
//zero  polynomial
Sparse::Sparse(int c, int n) { 
   if(c == 0){
      poly = nullptr;
   } else{
      Term* t = new Term;
      t->coeff = c;
      t->degree = n;
      poly = new Node;
      poly->term = t;
      poly->link = nullptr;
   }
}


// finds the last term and returns its degree so as 
// to give the degree of the sparse polynomial
// as a special case, it returns -1 for the zero polynomial
// O(n) where n is the number of terms of the polynomial
int Sparse::degree() const {
   if(this->isZeroSparse()){
      return -1;   
   }
   Node* p = poly;
   int d = 0;
   while(p!=nullptr){
      d = (p->term)->degree;
      p = p->link;
   }
   return d;
}

// returns the coefficient of the term which has degree d
// since the list is sorted, getting the coeff is order O(n) 
// where n is the number of terms of the polynomial
int Sparse::coefficient(int d) const{
   Node * p = poly;
   while(p != nullptr){
      if((p->term)->degree == d){
         return (p->term)->coeff;
      }
      p = p->link;
   }
   
   return 0;
}  

// outputs the polynomial and then terminates with a "\n"
// it uses the linked list poly and the instance variable this->variable
// do not output  "+ -" when outputting negative coefficients
// outputing is O(n) where n is the number of terms of the polynomial f
std::ostream& operator << (std::ostream& out, const Sparse& f) {
   // make a special case for the poly that has no terms i.e. the zero polynomial
   if(f.poly == nullptr){
      return out<<"0";   
   }




   // get the private list poly from a
   Sparse::Node *p = f.poly;
   // variable is a private member of f
   // so that I don't have to type f.variable every time, use x
   char x = f.variable; 
   int c; // variable to hold a coefficient
   int d; // variable to hold a degree
   bool first_term = true;
   while (p != nullptr) {
      c = p->term->coeff;
      d = p->term->degree;
      if (d == 0) { // do not output "x^0"
         out << c;
      }
      else { 
         // d  > 0
         if (c > 0) {
            if (!first_term) out << " + ";
            if (c != 1) {
               out << c <<  "*" ;
            }
         }
         else {
            // c < 0, could not be c == 0
            out << " - ";
            if (c != -1) {
               out << -c <<  "*" ;
            }
         }
         out << x << "^" << d;
      }
      // get the next Node
      p = p->link;
      first_term = false;
   } // while
   return out;
}

//Citation: code took from my assignment 8 (linklist)
//This function reverses the linklist (poly of the Sparse) such that if the link list is
// 5 4 3 2 1 then it reverses it to 1 2 3 4 5. poly is pointing to the 1 and 5 will link to nullptr.
void Sparse::reverse(){
   Node* next, * curr;
   if(poly==nullptr){
      return;
   }
   next = poly->link;
   curr = poly;
   poly->link = nullptr;
   while(next!=nullptr){
      curr = next;
      next = curr->link;
      curr->link = poly;
      poly = curr;      
   }
}

// if p has n terms, the operator* is O(n)
// Creates and returns Sparse object which will have all the terms and nodes of the 
// calling object and the coefficients of the terms will be multiplied by int c
Sparse Sparse::operator *(int c) const {
   if(c==0){
      Sparse s;
      return s;
   }
   
   Sparse n;
   n.poly = nullptr;
   Node* p = poly;
   
   while(p!= nullptr){
      Term * t = new Term;
      t->coeff = c*p->term->coeff;
      t->degree = p->term->degree;
      Node* node = new Node;
      node->term = t;
      node->link = n.poly;
      n.poly = node;
      p = p->link;
   }
   n.reverse();
   return n;
}

// basically insert t in order into poly (based on degree using linear search)
// do not make a new copy of t
// O(n) for n terms which is the length of the linked listpoly 
void Sparse::insert(Term *t) { 
   poly = insert(t, poly);
}

// insert t based on degree into p and return the list with t in it
// do not make a new copy of t
// delete t if t cannot be inserted
// O(n) where n is the length of the linked list p
Sparse::Node* Sparse::insert(Term *t, Node *p) {
   if(p == nullptr){
      Node* n = new Node;
      n->term = t;
      n->link = nullptr;
      p = n;
      return p;
   }else if(t->degree < p->term->degree){
      Node* n = new Node;
      n->term = t;
      n->link = p;
      return n;
   }
   Node* head = p;
   Node* n = new Node;
   n->term = t;
   Node* prev = p;
   p = p->link;
   while(p!= nullptr && (p->term)->degree < t->degree){
      prev = p;
      p = p->link;
   }
   
   prev->link = n;
   n->link = p;

   return head;
}

// the number of terms read must be positive
// read each term and build the polynomial by inserting each term in order 
// into the list poly
// if poly has  n terms, insert is O(n), 
// i.e. in the worst case, the complete
// list poly needs to be searched before the term can be inserted
std::istream& operator >> (std::istream& in, Sparse& p) {
   int numTerms;
   do {
      std::cout << "Enter the number of terms of the polynomial: ";
      in >> numTerms;
   } while (numTerms <= 0);
   std::cout << "For each term, enter the coefficient followed by the degree:\n";
   int c; // a coefficient
   int d; // a degree
   
   for(int i = 0; i <numTerms; i++){
      in>>c;
      in>>d;
      if(numTerms == 1 && c==0){
         p.poly = nullptr;
      }
      if(c!=0){
         Sparse::Term* t = new Sparse::Term;
         t->coeff = c;
         t->degree = d;
         p.insert(t);
      }
   }
   
  return in;
}
  
// use a merge type of algorithm to add the two polynomials f and g 
// (which have sorted lists)
// in the worst case, the addition is the sum of the length of "f" 
// plus the length of "g"
// so if f has n terms and g has m terms, it is O(n+m)
//Creates and return a Sparse which have the copy of nodes of f and g Sparse
//if the f and g node's term have same degree then the its coefficients will be added and node is inserted 
// into the Sparse object.
Sparse operator +(const Sparse & f, const Sparse & g) {
   Sparse::Node* p = f.poly;
   Sparse::Node* q = g.poly;
   
   Sparse n;
   n.poly = nullptr;
   while(p!= nullptr && q!= nullptr){
      Sparse::Term* t = new Sparse::Term;
      if(p->term->degree == q->term->degree){
         t->coeff = p->term->coeff + q->term->coeff;
         t->degree = p->term->degree;  
         p = p->link;
         q = q->link;  
      }else if(p->term->degree < q->term->degree){
         t->coeff = p->term->coeff;
         t->degree = p->term->degree;
         p = p->link;
      }else{
         t->coeff = q->term->coeff;
         t->degree = q->term->degree; 
         q = q->link;         
      }
      Sparse::Node* node = new Sparse::Node;
      if(t->coeff == 0){
         delete t;
      }else{
         node->term = t;
         node->link = n.poly;
         n.poly = node;
      }
   }
   
   while(p!=nullptr){
      Sparse::Term* t = new Sparse::Term;
      t->coeff = p->term->coeff;
      t->degree = p->term->degree;
      p = p->link;
      Sparse::Node* node = new Sparse::Node;
      node->term = t;
      node->link = n.poly;
      n.poly = node;
   }
   
   while(q!=nullptr){
      Sparse::Term* t = new Sparse::Term;
      t->coeff = q->term->coeff;
      t->degree = q->term->degree; 
      q = q->link;  
      Sparse::Node* node = new Sparse::Node;
      node->term = t;
      node->link = n.poly;
      n.poly = node;
   }
   n.reverse();
   return n;

}

//Creates and return a Sparse obect which have the linklist of terms such that 
//it is the subtraction of the polynomial of f- g;
//return Sparse object
Sparse operator -(const Sparse & f, const Sparse & g) {
   Sparse::Node* p = f.poly;
   Sparse::Node* q = g.poly;
   
   Sparse n;
   n.poly = nullptr;
   while(p!= nullptr && q!= nullptr){
      Sparse::Term* t = new Sparse::Term;
      if(p->term->degree == q->term->degree){
         t->coeff = p->term->coeff - q->term->coeff;
         
         t->degree = p->term->degree;  
         p = p->link;
         q = q->link;  
      }else if(p->term->degree < q->term->degree){
         t->coeff = p->term->coeff;
         t->degree = p->term->degree;
         p = p->link;
      }else{
         t->coeff = q->term->coeff;
         t->degree = q->term->degree; 
         q = q->link;         
      }
      if(t->coeff !=0){
         Sparse::Node* node = new Sparse::Node;
         node->term = t;
         node->link = n.poly;
         n.poly = node;
      }
   }
   
   while(p!=nullptr){
      Sparse::Term* t = new Sparse::Term;
      t->coeff = p->term->coeff;
      t->degree = p->term->degree;
      p = p->link;
      Sparse::Node* node = new Sparse::Node;
      node->term = t;
      node->link = n.poly;
      n.poly = node;
   }
   
   while(q!=nullptr){
      Sparse::Term* t = new Sparse::Term;
      t->coeff = q->term->coeff;
      t->degree = q->term->degree; 
      q = q->link;  
      Sparse::Node* node = new Sparse::Node;
      node->term = t;
      node->link = n.poly;
      n.poly = node;
   }
   
   n.reverse();
   return n;

}


// BONUS
// compute the derivative using the power rule by computing the
// derivative of every term in the list
// O(n) for n the number of terms of the polynomial
Sparse Sparse::derivative() const {
   Sparse n;
   Node* p = poly;
   while(p!=nullptr){
      Term* t = new Term;
      t->coeff = p->term->coeff * p->term->degree;
      t->degree = p->term->degree-1;
      
      if(t->degree >= 0){
         Node* node = new Node;
         node->term = t;
         node->link = n.poly;
         n.poly = node;
      }
      p = p->link;
   }
   
   n.reverse();

   return n;
}

//copy constructor. Creates Sparse with all values of other.
//copy of the linklist and terms is created
Sparse::Sparse(const Sparse& other) {
   poly = nullptr;
   Node* p = other.poly;
   
   while(p!=nullptr){
      Term* t = new Term;
      t->coeff = p->term->coeff;
      t->degree = p->term->degree;
      
      Node* node = new Node;
      node->term = t;
      node->link = poly;
      poly = node;
      p = p->link;
   }
   
   reverse();
   
}

//assignment operator
//if this is not the right hand side object then it deletes 
//all the terms and nodes of poly of this object and then create 
// a new copy of the rhs Sparse's linklist
Sparse& Sparse::operator = (const Sparse& rhs) {
   if(this != &rhs){
      while(poly != nullptr){
         Node* dump = poly;
         poly = poly->link;
         delete dump->term;
         delete dump;
      }
      
      if(rhs.poly == nullptr){
         return *this;   
      }
      Node* p = rhs.poly;
      
      while(p!=nullptr){
         Term* t = new Term;
         t->coeff = p->term->coeff;
         t->degree = p->term->degree;
      
         Node* node = new Node;
         node->term = t;
         node->link = poly;
         poly = node;
         p = p->link;
      }
   }
   reverse();
   return *this;
}

//Destructor
//deletes all the nodes and term of the poly
//poly points to nullptr
Sparse::~Sparse(){
   while(poly != nullptr){
      Node* dump = poly;
      poly = poly->link;
      delete dump->term;
      delete dump;
   }
}