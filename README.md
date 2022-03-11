# Sparse-polynomial
Used linked list to represent non-zero terms of polynomial - this data structure is appropriate for sparse polynomial.
For example, given the polynomial: p = 2 - 3x3 + 4x5, we represent this sparse polynomial as a linked list of Terms of type Node, ordered by increasing
degree. That is, the terms are: 2*x^0 -3*x^3 4*x^5

Used method overload on >> operator to read the polynomial.  
Summary of functions done by program -  
• read a polynomial  
• determine if the polynomial is the zero polynomial  
• output the polynomial  
• add two polynomials  
• subtract two polynomials  
• multiply a polynomial by a scalar constant changing the polynomial  
• get the coefficient of a term given the degree  
• get the degree of the polynomial  
the zero polynomial is a special case and has a degree of -1.
