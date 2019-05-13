/** @file BigNumbers.cpp
 *  @brief The CPP file for BigNumbers
 *
 * This contains the definitions for the BigNumbers class
 *
 *
 *  @author Ethan Balderas
 */
#include "BigNumbers.h"

//! A Constructor
/*! The default constructor for a BigNumber*/
//! Creates a BigNumber that represents zero
BigNumbers::BigNumbers()
{
	positive = true;
	nums = { 0 };
	size = 1;
}

//! A Constructor
/*! An Overloaded constructor for a BigNumber
/param number An int to be made into a BigNumber
*/
BigNumbers::BigNumbers(int number)
{
	//Check for positive or negative first
	if (number >= 0) {
		positive = true;
	}
	else {
		positive = false;
		number = number * -1;
	}

	//Check how large the size needs to be 
	size = 1;    //every number has at least 1 place

	//we need to check up to what place the number goes to
	int temp = number;
	while ((temp / 10) != 0) {
		size++;
		temp = temp / 10;
	}

	temp = number;
	//We need to put each digit into the vector 
	for (int x = size; x > 0; x--) {
		int place = temp / (pow(10, x - 1));
		nums.push_back(place);
		temp -= place * pow(10, x - 1);
	}

}

//! A Constructor
/*! An Overloaded constructor for a BigNumber
/param big A BigNumber to be made into a BigNumber
*/
BigNumbers::BigNumbers(BigNumbers & big)
{
	nums = big.nums;
	size = big.size;
	positive = big.positive;
}

//! A Constructor
/*! An Overloaded constructor for a BigNumber	/param s A string to be made into a BigNumber
*/
BigNumbers::BigNumbers(std::string s)
{
	//convert from string to int
	std::string myString = s;
	int number = atoi(myString.c_str());

	//Check for positive or negative first
	if (number >= 0) {
		positive = true;
	}
	else {
		positive = false;
		//get rid of the negative sign
		number *= -1;
	}
	size = 1;

	//we need to check up to what place the number goes to
	int temp = number;
	while ((temp / 10) != 0) {
		size++;
		temp = temp / 10;
	}

	temp = number;
	//We need to put each digit into the vector
	for (int x = size; x > 0; x--) {
		int place = temp / (pow(10, x - 1));
		nums.push_back(place);
		temp -= place * pow(10, x - 1);
	}

}

/** @brief Prints out the contents of a BigNumber
	* Loops through all the elements in the BigNumber's vector and prints them out
	*  @return Void.
	*/
void BigNumbers::printNumber()
{
	//Prints out the "-" symbol if negative
	if (!positive) {
		std::cout << "-";
	}

	//Prints our each value left to right
	for (int x = 0; x < size; x++) {
		std::cout << nums.at(x);
	}
	std::cout << std::endl;
}



bool BigNumbers::isSmaller(BigNumbers const& big)
{
	int n1 = nums.size();
	int n2 = big.nums.size();
	//Check the sizes first
	if (n1 < n2)
		return true;
	if (n2 < n1)
		return false;
	//Check each element
	for (int i = 0; i < n1; i++)
		if (nums.at(i) < big.nums.at(i))
			return true;
		else if (nums.at(i) > big.nums.at(i))
			return false;

	return false;
}

bool BigNumbers::isEqual(BigNumbers const& big) {
	int n1;
	//check if they are the same powers 
	if (big.nums.size() == nums.size()) {
		n1 = big.nums.size();
	}
	else {
		return false;
	}
	//check for each element if they are the same
	for (int i = 0; i < n1; i++)
		if (nums.at(i) < big.nums.at(i))
			return false;
		else if (nums.at(i) > big.nums.at(i))
			return false;

	return true;
}

BigNumbers BigNumbers::add(BigNumbers const& big)
{
	int carry = 0;
	int temp;
	int indexOne = nums.size();
	int indexTwo = big.nums.size();
	int largest;
	//determine the max index
	if (indexOne > indexTwo) {
		largest = indexOne;
	}
	else {
		largest = indexTwo;
	}
	//Create object to return
	BigNumbers returnMe;
	returnMe.nums.clear();
	returnMe.size = 0;
	//we have to start left to right

	for (int x = 0; x < largest + 1; x++) {
		indexOne--;
		indexTwo--;
		if (indexOne >= 0 && indexTwo >= 0) {
			//we add both and do the carry

			temp = nums.at(indexOne) + big.nums.at(indexTwo) + carry;
			if (temp > 9) {
				carry = 1;
				temp -= 10;
			}
			else {
				carry = 0;
			}
			
			//Increase returnMe size and put in the new value
			returnMe.size++;
			returnMe.nums.insert(returnMe.nums.begin(), temp);
		}
		else if (indexOne >= 0) {
			//we just add carry and one's values
			temp = nums.at(indexOne) + carry;
			if (temp > 9) {
				carry = 1;
				temp -= 10;
			}
			else {
				carry = 0;
			}
			//Increase returnMe size and put in the new value
			returnMe.size++;
			returnMe.nums.insert(returnMe.nums.begin(), temp);
			//std::cout << "Adding First Only, Result: " << temp << std::endl;
		}
		else if (indexTwo >= 0) {
			//we just add carry and two's values
			temp = big.nums.at(indexTwo) + carry;
			if (temp > 9) {
				carry = 1;
				temp -= 10;
			}
			else {
				carry = 0;
			}
			//Increase returnMe size and put in the new value
			returnMe.size++;
			returnMe.nums.insert(returnMe.nums.begin(), temp);
			
		}
		else {
			//finally we just check the final value for a carry 
			if (carry == 1) {
				returnMe.size++;
				returnMe.nums.insert(returnMe.nums.begin(), 1);
			}
		}
	}
	return returnMe;
}


BigNumbers BigNumbers::subtractTwoNegatives(BigNumbers const& big) {
	//create object to be returned
	BigNumbers returnMe;
	returnMe.nums.clear();
	returnMe.size = 0;

	//size of both numbers
	int indexOne = nums.size()-1;
	int indexTwo = big.nums.size()-1;
	int temp=0;
	int carry = 0;

	//If they are both the same number the result is 0
	if (isEqual(big)) {
		returnMe.size = 1;
		returnMe.nums = { 0 };
		returnMe.positive = true;
		return returnMe;
	}
	//If the second negative is bigger then the result is posiive 
	if (isSmaller(big)) {
		returnMe.positive = true;
		while (indexTwo>=0) {
			if (indexOne >= 0) {
				temp = big.nums.at(indexTwo) - nums.at(indexOne) - carry;
			}
			else {
				temp = big.nums.at(indexTwo) - carry;
			}

			if (temp < 0) {
				carry = 1;
				temp += 10;
			}
			else {
				carry = 0;
			}
			//Write the value to the array
			returnMe.size++;
			returnMe.nums.insert(returnMe.nums.begin(), temp);

			//increment
			indexTwo--;
			indexOne--;
		}
		
	}
	//If the first negative is bigger then the result is negative
	else {
		returnMe.positive = false;
		while (indexOne >= 0) {
			if (indexTwo >= 0) {
				temp = nums.at(indexOne) - big.nums.at(indexTwo) - carry;
			}
			else {
				temp = nums.at(indexOne)  - carry;
			}

			if (temp < 0) {
				temp += 10;
				carry = 1;
			}
			else {
				carry = 0;
			}
			//Write the value to the array
			returnMe.size++;
			returnMe.nums.insert(returnMe.nums.begin(), temp);
			//increment at the end
			indexOne--; indexTwo--;
		}

	}
	//Clean up carried over zeros
	while (returnMe.nums.size() > 1 && returnMe.nums[0] == 0) {
		returnMe.nums.erase(returnMe.nums.begin());
		returnMe.size--;
	}
	return returnMe;
}


BigNumbers BigNumbers::subtractTwoPositives(BigNumbers const& big) {
	//create object to be returned
	BigNumbers returnMe;
	returnMe.nums.clear();
	returnMe.size = 0;

	//size of both numbers
	int indexOne = nums.size()-1;
	int indexTwo = big.nums.size()-1;
	int temp;
	int carry = 0;
	//First check for equal
	if (isEqual(big)) {
		returnMe.size = 1;
		returnMe.nums = { 0 };
		returnMe.positive = true;
		return returnMe;
	}

	if (isSmaller(big)) {
		returnMe.positive = false;
		while (indexTwo >= 0) {
			if (indexOne >= 0) {
				temp = big.nums.at(indexTwo) - nums.at(indexOne) - carry;
			}
			else {
				temp = big.nums.at(indexTwo) - carry;
			}

			if (temp < 0) {
				carry = 1;
				temp += 10;
			}
			else {
				carry = 0;
			}
			//Write the value to the array
			returnMe.size++;
			returnMe.nums.insert(returnMe.nums.begin(), temp);

			//increment
			indexTwo--;
			indexOne--;
		}

	}
	else {
		returnMe.positive = true;
		while (indexOne >= 0) {
			if (indexTwo >= 0) {
				temp = nums.at(indexOne) - big.nums.at(indexTwo) - carry;
			}
			else {
				temp = nums.at(indexOne) - carry;
			}

			if (temp < 0) {
				temp += 10;
				carry = 1;
			}
			else {
				carry = 0;
			}
			//Write the value to the array
			returnMe.size++;
			returnMe.nums.insert(returnMe.nums.begin(), temp);
			//increment at the end
			indexOne--; indexTwo--;
		}

	}
	//delete leading zeros
	while (returnMe.nums.size() > 1 && returnMe.nums[0] == 0) {
		returnMe.nums.erase(returnMe.nums.begin());
		returnMe.size--;
	}

	return returnMe;
}


BigNumbers BigNumbers::multiply(BigNumbers const& big)
{
	BigNumbers temp;
	temp.nums.clear();
	temp.size = 0;

	BigNumbers returnMe;

	int indexOne = nums.size()-1;
	int indexTwo = big.nums.size()-1;

	//Case 1: Multiply by zero
	if ((big.nums.size() == 1 && big.nums.at(0) == 0) || (nums.size() == 1 && nums.at(0) == 0)) {
		returnMe.size = 1;
		returnMe.nums = { 0 };
		returnMe.positive = true;
		return returnMe;

	}
	int power = 0;
	while (indexTwo >= 0) {
		indexOne = nums.size() - 1;
		while (indexOne >= 0) {
			//This is just basic multiplication we do by hand. Multiple each element in to the all elemenets of the upper and shift over
			//BY 10 each time
			temp.nums.insert(temp.nums.begin(), nums.at(indexOne) * big.nums.at(indexTwo) * pow(10, power));
			indexOne--;
		}
		indexTwo--;
		power++;
		returnMe = returnMe.add(temp);
		temp.nums.clear();
	}

	//Case 2: Positive * Negative
	if (positive & !big.positive) {
		returnMe.positive = false;
		return returnMe;
	}
	//Case 3: Positve * Positive
	if (positive & big.positive) {
		returnMe.positive = true;
		return returnMe;
	}
	//Case 4: Negative * Positive
	if (!positive & big.positive) {
		returnMe.positive = false;
		return returnMe;
	}
	//Case 5: Negative * Negative
	if (!positive & !big.positive) {
		returnMe.positive = true;
		return returnMe;
	}
}


BigNumbers BigNumbers::divide(BigNumbers const& big)
{
	std::cout << "Start" << std::endl;
	BigNumbers one;
	one.nums = { 1 };
	one.size = 1;
	one.positive = true;

	BigNumbers copy2;
	copy2.nums = nums;
	copy2.size = size;
	copy2.positive = true;

	BigNumbers returnMe;
	returnMe.nums.clear();
	returnMe.size = 0;

	int counter = 0;
	//Check Basic Cases first
	if (big.nums.size() == 1 && big.nums.at(0) == 0) {
		//error divide by zero
		throw "Can not divide by zero!";
		return returnMe;
	}

	if (isEqual(big)) {
		std::cout << "Same size!" << std::endl;
		returnMe.size = 1;
		returnMe.nums = {1};
		returnMe.positive = true;
		return returnMe;
	}

	if (isSmaller(big)) {
		// (x/ (x+1) = 0 
		returnMe.size = 1;
		returnMe.nums = { 0 };
		returnMe.positive = true;
		return returnMe;
	}

	while (copy2.positive) {
		copy2 = (copy2 - big);
		if (copy2.positive) {
			returnMe = returnMe + one;
		}

	}


	//Case 2: Positive / Negative
	if (positive & !big.positive) {
		returnMe.positive = false;
		return returnMe;
	}
	//Case 3: Positve / Positive
	if (positive & big.positive) {
		returnMe.positive = true;
		return returnMe;
	}
	//Case 4: Negative / Positive
	if (!positive & big.positive) {
		returnMe.positive = false;
		return returnMe;
	}
	//Case 5: Negative / Negative
	if (!positive & !big.positive) {
		returnMe.positive = true;
		return returnMe;
	}


	return returnMe;
}





/** @brief Overload the add symbol for BigNumbers
	*
	*  Adds two BigNumbers together and returns the result
	*
	*  @param big The BigNumber to be added
	*
	*/
BigNumbers BigNumbers::operator+(BigNumbers const& big)
{
	BigNumbers returnMe;
	returnMe.nums.clear();
	returnMe.size = 0;

	if (positive && big.positive) {
		returnMe = add(big);

	}
	else if (!positive && !big.positive) {
		returnMe = add(big);
		returnMe.positive = false;

	}
	else if (positive && !big.positive) {
		//Big needs to be positive to be interpreted by the subtraction method
		returnMe = subtractTwoPositives(big);
	}
	else if (!positive && big.positive) {
		returnMe = subtractTwoNegatives(big);
	}

	if (returnMe.size > maximum) {
		throw "Max BigNumber Size Exceeded";
	}
	return returnMe;
}

/** @brief Overload the subtract symbol for BigNumbers
	*
	*  Subtract two BigNumbers together and returns the result
	*
	*  @param big The BigNumber to be subtracted
	*
	*/
BigNumbers BigNumbers::operator-(BigNumbers const& big) {
	//create object to return
	BigNumbers returnMe;
	returnMe.nums.clear();
	returnMe.size = 0;
	//x-y
	if (positive && big.positive) {
		returnMe = subtractTwoPositives(big);
	}
	//x- (-y)  == x+y
	else if (positive && !big.positive) {
		returnMe = add(big);
		returnMe.positive = true;
	}
	//-x-y == -(x+y)
	else if (!positive && big.positive) {
		returnMe = add(big);
		returnMe.positive = false;
	}
	//-x -(-y) == -x+y
	else if (!positive && !big.positive) {
		// make a reliable subtract
		returnMe = subtractTwoNegatives(big);
	}

	if (returnMe.size > maximum) {
		throw "Max BigNumber Size Exceeded";
	}
	return returnMe;
}


/** @brief Overload the multiply symbol for BigNumbers
	*
	*  Multiplies two BigNumbers together and returns the result
	*
	*  @param big The BigNumber to be multiplied
	*
	*/
BigNumbers BigNumbers::operator*(BigNumbers const& big)
{
	BigNumbers returnMe;
	returnMe.nums.clear();
	returnMe.size = 0;

	returnMe = multiply(big);
	return returnMe;
	
}


/** @brief Overload the divide symbol for BigNumbers
	*
	*  Divides two BigNumbers together and returns the result
	*
	*  @param big The BigNumber to be divided
	*
	*/
BigNumbers BigNumbers::operator/(BigNumbers const& big)
{
	BigNumbers returnMe;
	returnMe.nums.clear();
	returnMe.size = 0;
	returnMe = divide(big);
	if (returnMe.size > maximum) {
		throw "Max BigNumber Size Exceeded";
	}
	return returnMe;
}

/** @brief Overload the mod symbol for BigNumbers
	*
	*  Mods two BigNumbers together and returns the result
	*
	*  @param big The BigNumber to be modded
	*
	*/
BigNumbers BigNumbers::operator%(BigNumbers const& big) 
{
	//create object to return
	//mod is just the remainder, but that can be a big number still cuz big %1 is the big number
	BigNumbers returnMe;
	returnMe.nums.clear();
	returnMe.size = 0;

	BigNumbers divisor;
	divisor.nums = big.nums;
	divisor.size = big.size;
	divisor.positive = big.positive;

	BigNumbers base;
	base.nums = nums;
	base.size = size;
	base.positive = positive;


	//Find base/divisor --> round down
	returnMe = (base/divisor);
	//Multiply the divisor by the result


	returnMe = (divisor * returnMe);

	//Subtract that result from base
	returnMe = base - returnMe;
	returnMe.printNumber();
	//the left over is the mod

	if (returnMe.size > maximum) {
		throw "Max BigNumber Size Exceeded";
	}
	return returnMe;
}

/** @brief Overload the equal symbol for BigNumbers
*
*  Sets one BigNumber equal to the other
*
*  @param big The BigNumber to be set equal to
*
*/
BigNumbers BigNumbers::operator=(BigNumbers const& big)
{
	nums = big.nums;
	size = big.size;
	positive = big.positive;
	return *this;
}
