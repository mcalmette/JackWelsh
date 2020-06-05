// ----------------------------------------------------------------------
// Author: Michael Calmette
// Assignment: 2
// ----------------------------------------------------------------------

#include "decimal.h"

// default value is "0."
//constructor
Decimal::Decimal() : point_loc(0) //0
{
  digits.push_back(0);
}


//overloaded constructor
Decimal::Decimal(std::string val, int point_location)
  : point_loc(point_location)
{
  int n = int(val.size());
  // invalid cases: bad point location, empty string
  if (point_loc > n || n == 0) {
    // set to default value "0."
    point_loc = 0;
    digits.push_back(0);
    return;
  }
  // parse string
  for (int i = 0; i < n; ++i) {
    char c = val[i];
    if (std::isdigit(c))
      digits.push_back(c - '0');
    else {
      // invalid character found
      digits.clear();
      point_loc = 0;
      digits.push_back(0);
      return;
    }
  }
  reduce_zeros();
}


// TODO: Finish remaining Decimal functions ... 


void Decimal::reduce_zeros()
{
   //digits is the vector
   //zeros = point_loc;
   int s = digits.size();

   for(int i = 0; i < point_loc; ++i)
   {
      if(digits.at(s-1) == 0)
      {
         digits.pop_back();
         point_loc--;
	 s--;
         zeros++;
      }
      else
      {
          break;
      }
   }

   for(int i = 0; i < sizeT(); i++)
   {
     if(digits.at(i) == 0)
     {
	digits.erase(digits.begin());
	frontZer++;
     }
       
     else
	break;
   }

}


//returns vector size
int Decimal::sizeT() const
{
    return digits.size();
}

//returns value for testing purposes
int Decimal::num(int pos) const
{
    //return digits.at(digits.size()-1);
    return digits.at(pos);
}

//used for other comparitive functions
bool Decimal::operator< (const Decimal& rhs) const 
{ 
   //checks vector size first
   if((digits.size() - point_loc) < (rhs.digits.size() - rhs.point_loc))
	return true;
   if((digits.size() - point_loc) > (rhs.digits.size() - point_loc))
	return false;
   else //checks position by position if sizes are equal
   {
     int x = digits.size();
     for(int i = 0; i < x; i++)
     {
      if(digits.at(i) < rhs.digits.at(i))
	 return true;
  
      if(rhs.digits.at(i) < digits.at(i))
	 return false;
  
    }
     return false;
   } 
}

//is equal
bool Decimal::operator==(const Decimal& rhs) const 
{ 
   return !(*this < rhs) && !(rhs < *this);
 
}

//greater than
bool Decimal::operator>(const Decimal& rhs) const
{
   return rhs < *this;
}

//less than or equal to
bool Decimal::operator<= (const Decimal& rhs) const
{
   return !(*this < rhs);
}

//greater than or equal to
bool Decimal::operator>= (const Decimal& rhs) const
{
   return !(*this > rhs);
}

//not equal to
bool Decimal::operator!= (const Decimal& rhs) const
{
   return !(*this == rhs);
}

//addition 
Decimal Decimal::operator+(const Decimal& rhs) const
{
   Decimal D = *this;
   int rightDec = rhs.point_loc;
   int leftDec = point_loc;
   int rightIndex = rhs.sizeT() - 1;
   int leftIndex = sizeT() - 1;
   int dif;
   //int index;
   D.digits.clear(); //empty's D's contents to push new ints
   if(rightDec > leftDec)
   {
       dif = rightDec - leftDec;
       D.point_loc = rhs.point_loc;
   }
   else
   {
       dif = leftDec - rightDec;
       D.point_loc = point_loc;
    }
   //starts from furthest decimal point to fill up smalles decimals first
   for(int i = 1; i < dif+1; i++)
   { 
      
      if(rightDec > leftDec)
      {
	D.digits.insert(D.digits.begin(), rhs.digits.at(rhs.sizeT() - i));
        rightIndex--;
      }

      if(rightDec < leftDec)
      {
	D.digits.insert(D.digits.begin(), digits.at(sizeT() - i));
        leftIndex--;
      }

   }
   /*now at the 1's position for the numbers, but 
     I create different indexes for different length vectors
   */
   int newIndex;
   if(rightIndex <= leftIndex)
   {
      newIndex = rightIndex;
   }else{
      newIndex = leftIndex;
   }
 
   bool remainder = false; //flag to indicate a one is carried over

   for(int i = newIndex; i >= 0; i--)
   {
       int x = rhs.digits.at(rightIndex) + digits.at(leftIndex);
       if(remainder == true)
       {
   	  x = x + 1;
	  remainder = false;
       }

       if(x > 9)
       {
   	   x = x - 10;
           remainder = true;
       }
       D.digits.insert(D.digits.begin(), x);
       rightIndex--;       
       leftIndex--;
   }

   //rememeber to add if remainder is there.

   int finalIndex;
   //fills up remaining vector once one vector remains
   if(rightIndex < leftIndex)
   {
	finalIndex = leftIndex;
        for(int i = finalIndex; i >= 0; i--)
	{
 	   int x = digits.at(finalIndex);
           if(remainder == true)
	   {
	        x = x+1;
                remainder = false;
           }
	   if(x > 9)
           {
   	        x = x - 10;
               remainder = true;
           }
           D.digits.insert(D.digits.begin(), x);
           finalIndex--;
        }
   }
   else
   {
	finalIndex = rightIndex;
	for(int i = finalIndex; i >= 0; i--)
	{
 	   int x = rhs.digits.at(finalIndex);
           if(remainder == true)
	   {
	        x = x+1;
                remainder = false;
           }
	   if(x > 9)
           {
   	        x = x - 10;
               remainder = true;
           }
           D.digits.insert(D.digits.begin(), x);
           finalIndex--;
        }
   }

   return D;

}

//postincrement
Decimal Decimal::operator++(int)
{
   Decimal tmp = *this;
   ++*this;
   return tmp;
}


//preincrement
Decimal& Decimal::operator++() 
{
   //check back of the vector, 
   int sz = digits.size();
   int dec = point_loc;
   if(sz == 1 && digits.at(0) == 9)
   {
	digits.push_back(0);
        digits.erase(digits.begin());
        digits.insert(digits.begin(),1);
        return *this;
   }
   for(int i = sz-1-dec; i>=0; i--)
   {
      if(digits.at(i) == 9) //has to go one further 
      {
         digits.erase(digits.begin() + i);
         digits.insert(digits.begin() + i, 0); //becomes a zero
         if(i == 0)
	 {
	    digits.erase(digits.begin() + i);
            digits.insert(digits.begin() + i, 1);
            digits.insert(digits.begin() + sz - 1 - point_loc, 0);
         }
      } 
      else
      {
         int x = digits.at(i);
         x = x + 1; 
         digits.at(i) = x;
         return *this;
      }
   }
 
   return *this;
   
}



//std::ostream& operator<<(ostream& out const Decimal& val)
std::ostream& operator<<(std::ostream& out, const Decimal& val)
{
     Decimal tmp = val;
     bool decDown = false;
     int sz  = tmp.digits.size();
     for(int j = 0; j < sz; j++)
     {
        if(tmp.frontZer > 0 && tmp.frontZer == j && decDown == false) 
        { //decimal if there were front zeros deleted
 	  out << '.';
          decDown = true;
	}
  	out << tmp.digits.at(j);
     }
     if(decDown == false)
     { //decimal if back zeros deleted
        out << ".";
     	for(int i = 0; i < tmp.zeros; i++)
     	{
		out << 0;
     	}
     }
    return out;
}


