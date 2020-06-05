// ----------------------------------------------------------------------
// Author: Michael Calmette
// Assignment: 2
//
// Basic driver for testing the Decimal class implementation using
// assert statements. This file only partially tests the Decimal class
// and should be extended (see TODO below) with your own test cases.
// ----------------------------------------------------------------------


#include <iostream>
#include <cassert>
#include "decimal.h"

using namespace std;


int main(int argc, char** argv)
{
  // poorly formed decimal values
  Decimal zero = Decimal();

  Decimal y = Decimal("2100", 0);
  Decimal x = Decimal ("2100", 0);
  assert(y == x); //==  works

  Decimal c = Decimal("99", 0);
  assert(++c == Decimal("100", 0)); //preincrement works
 
  
  Decimal q = Decimal("2101", 1);
  Decimal w = Decimal ("2100", 0);
  assert(q < w);  //less than works

  Decimal h = Decimal("200", 1);
  Decimal k = Decimal("199",2);
  assert(h>k);  //greater than works
  
  // increment  
  Decimal one = Decimal("0", 0);   
  //assert(++Decimal() == one); //decimal() = 0
  assert(Decimal()++ == zero); //Decimal = 0
 
  
  // basic addition
  Decimal xx = Decimal("12345", 1);
  Decimal yy = Decimal("67890", 3);
  Decimal AA = xx + yy;
  //cout << AA.num(0) << AA.num(1) << AA.num(2) << AA.num(3) << AA.num(4) << AA.num(5) << endl;

  assert(x + y == Decimal("1302390", 3));
  
  
  // large addition
  /*Decimal z = Decimal("99999999999999999999", 0);
  z = z + Decimal("1", 0);
  for(int i = 0; i < 19; i++)
  {
     cout << z.num(i);
  }
  cout << endl;
  assert(z == Decimal("100000000000000000000", 0));*/
  
  // test same values
  Decimal pi_1("314159", 5);
  Decimal pi_2("3141590", 6);
  assert(pi_1 == pi_2);
  assert(!(pi_1 != pi_2));
  assert(!(pi_1 < pi_2));
  assert(!(pi_1 > pi_2));
  assert(pi_1 <= pi_2);
  assert(pi_1 >= pi_2);
  

  cout << Decimal("100",0) << endl;


  // test printing
  cout << "should be 1: " << Decimal("1",0) << endl;
  cout << "should be 43: " << Decimal("430", 1) << endl;
  cout << "should be 1.75: " << Decimal("01750", 3) << endl;
  
  // ...
  // TODO: add your own tests, considering the various cases
  // ...

  //further testing of function
  Decimal zss = Decimal("997", 0);
  zss = zss + Decimal("2", 0);
  assert(zss == Decimal("999",0));

  Decimal kl = Decimal("231", 1);
  kl = kl + Decimal("1",0);
  assert(kl == Decimal("241",1));

 
  Decimal p_1("031", 0);
  Decimal p_2("31", 0);
  assert(p_1 == p_2);
  assert(!(p_1 != p_2));
  assert(!(p_1 < p_2));
  assert(!(p_1 > p_2));
  assert(p_1 <= p_2);
  assert(p_1 >= p_2);

  Decimal x_q("1001",1); //preincrement with dec
  assert(++x_q == Decimal("1011",1));

  Decimal x_p("1001",1); //postincrement with dec
  assert(x_p++ == Decimal("1001",1));

}

