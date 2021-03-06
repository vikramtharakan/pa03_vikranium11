//poly0.cxx
//Vikram Tharakan 5/1/17

#include "poly0.h"
#include <cassert>
#include <climits>
#include <cmath>

namespace main_savitch_3
{
  polynomial::polynomial(double c, unsigned int exponent){
    assert(exponent <= MAX_EX);
    for(int i = 0; i<CAPACITY; i++){
	coef[i] = 0;
    }
    current_degree = 0;
    if(c > 0){
      coef[exponent] = c;
      current_degree = exponent;
    }
  }
  void polynomial::add_to_coef(double amount, unsigned int exponent){
    assert(exponent <= MAX_EX);
    coef[exponent] += amount;
    //Solely for adding down
    if(coef[exponent] == 0){
      current_degree = 0;
      for(unsigned int i = 0; i<CAPACITY; i++){
	if(coef[i] != 0)
	  current_degree = i;
      }
    } 
    if(exponent > current_degree && coef[exponent] != 0)
      current_degree = exponent;
  }
  
  void polynomial::assign_coef(double coefficient, unsigned int exponent){
    assert(exponent <= MAX_EX);
    coef[exponent] = coefficient;
    //Solely for adding down
    if(coef[exponent] == 0){
      current_degree = 0;
      for(unsigned int i = 0; i<CAPACITY; i++){
	if(coef[i] != 0)
	  current_degree = i;
      }
    }
    if(exponent > current_degree && coef[exponent] != 0)
      current_degree = exponent;

  }
  
  void polynomial::clear(){
    for(int i = 0; i < CAPACITY; i++){
      coef[i] = 0;
    }
    current_degree = 0;
  }
  
  double polynomial::coefficient(unsigned int exponent) const{
    if(exponent <= MAX_EX)
      return coef[exponent];
    else
      return 0;
  }

  polynomial polynomial::derivative( ) const{
    polynomial p1;
    if(current_degree > 0){
      for(int i = 0; i < MAX_EX; i++){
	p1.coef[i] = coef[i+1]*(i+1);
      }
      p1.current_degree = current_degree - 1;
    }
    else{
      p1.current_degree = 0;
      p1.coef[0] = 0;
    }
    return p1;
  }

  double polynomial::eval(double x) const{
    double total = 0;
    for(unsigned int i = 0; i<CAPACITY; i++){
      if(i == 0)
	total += coef[i];
      else
	total += pow(x,i)*coef[i];
    }
    return total;
  }

  unsigned int polynomial::next_term(unsigned int e) const{
    for(unsigned int i = (e+1); i<CAPACITY; i++){
      if(coef[i]!=0)
	return i;
    }
      return 0;
  }

  unsigned int polynomial::previous_term(unsigned int e) const{
    if (e == 0)
      return UINT_MAX;
    
    //Just in case e> is like 56 or something 
    if(e > CAPACITY)
      e = CAPACITY;
        
    for(int i = (e-1); i>=0; i--){
      if(coef[i]!= 0)
	return i; 
    }

    return UINT_MAX;
  }

  polynomial operator +(const polynomial& p1, const polynomial& p2){
    polynomial p;
    for(unsigned int i = 0; i<polynomial::CAPACITY; i++){
      double holder = p1.coefficient(i) + p2.coefficient(i);
      p.assign_coef(holder,i);
    }
    return p;
  }

  polynomial operator -(const polynomial& p1, const polynomial& p2){
    polynomial p;
    for(unsigned int i = 0; i<polynomial::CAPACITY; i++){
      double holder = p1.coefficient(i) - p2.coefficient(i);
      p.assign_coef(holder,i);
    }
    return p;
  }

  polynomial operator *(const polynomial& p1, const polynomial& p2){
    assert(p1.degree( ) + p2.degree( ) <= polynomial::MAX_EX);
    polynomial p;
    for(unsigned int i = 0; i<=p1.degree(); i++){
      for(unsigned int j = 0; j<=p2.degree(); j++){
	if(p1.coefficient(i) != 0 && p2.coefficient(j) != 0){
	  double holder = p1.coefficient(i)*p2.coefficient(j);
	  p.add_to_coef(holder,(i+j));
	}
      }
    }
    return p;
  }

  std::ostream& operator << (std::ostream& out, const polynomial& p){

    ////////////////////////////////////////////////////////
    //FIRST DRAFT WAS SEGFAULTING BUT IT IS LEFT IN JUST TO LOOK BACK AT

    /*    for(unsigned int i = 0; i<polynomial::CAPACITY; i++){
      if(p.coefficient(i) != 0){
	if(p.previous_term(i) != UINT_MAX && p.coefficient(i) > 0)
	  out << " + ";
	else if(p.previous_term(i) != UINT_MAX && p.coefficient(i) < 0)
	  out << " - ";
	
	if(i > 1)
	  out << std::abs(p.coefficient(i)) << "x^" << i;
	else if(i == 1)
	  out << std::abs(p.coefficient(i)) << "x";
	else
	  out << std::abs(p.coefficient(i));
      }
    }
    if(p.degree() == 0 && p.coefficient(0) == 0)
      out << "0";
    out << std::endl;
    */
    //////////////////////////////////////////////////////////


    //ACTUAL COUT FUNCTION
    if ( p.degree( ) == 0 && p.coefficient(0)==0 )
      {
	out << 0;
	return out;
      }

    out << p.coefficient(p.degree());
    if(p.degree()>1)
      out << "x^" << p.degree();
    else if(p.degree() ==1)
      out << "x";

    for (int i = p.degree( )-1; i >= 0; i--)
      {
	if ( p.coefficient( i ) < 0.0 )
	  out << " - " << std::abs(p.coefficient( i ));
	else if (p.coefficient(i) > 0)
	  out << " + " << p.coefficient(i);

	if(p.coefficient(i) !=0){
	  if(i>1)
	    out << "x^" << i;
	  else if(i ==1)
	    out << "x";
	}
      }
    out << std::endl;
    return out;
    
    }

}
