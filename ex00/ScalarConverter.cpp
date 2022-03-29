/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:14:50 by mhaddi            #+#    #+#             */
/*   Updated: 2022/03/29 18:56:11 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <iostream>
#include <iomanip>
#include <limits>

int intMin = std::numeric_limits<int>::min();
int intMax = std::numeric_limits<int>::max();
int charMin = std::numeric_limits<char>::min();
int charMax = std::numeric_limits<char>::max();
int floatMin = std::numeric_limits<float>::min();
int floatMax = std::numeric_limits<float>::max();
int doubleMin = std::numeric_limits<double>::min();
int doubleMax = std::numeric_limits<double>::max();

ScalarConverter::ScalarConverter(void)
{
	return ;
}

ScalarConverter::ScalarConverter(std::string const & value): _stringValue(value)
{
	return ;
}

ScalarConverter::ScalarConverter(ScalarConverter const & src)
{
	*this = src;
	return ;
}

ScalarConverter & ScalarConverter::operator=(ScalarConverter const & rhs)
{
	if (this != &rhs)
	{
		this->_stringValue = rhs._stringValue;
	}
	return *this;
}

ScalarConverter::~ScalarConverter(void)
{
	return ;
}

size_t count(std::string const &str, char c)
{
	size_t count = 0;
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == c)
			count++;
	}
	return count;
}

bool ScalarConverter::isInt() const {

	std::string value = this->_stringValue;

	unsigned long indexOfNonDigit = value.find_first_not_of("0123456789");

	return
	(
	  (
	    indexOfNonDigit == std::string::npos
		|| (
			 indexOfNonDigit == 0
			 && value[indexOfNonDigit] == '-'
			 && value.substr(1).find_first_not_of("0123456789") == std::string::npos
		)
	  )
 	  && std::stof(value) >= intMin
	  && std::stof(value) <= intMax
	);
}

bool ScalarConverter::isChar() const {

	std::string value = this->_stringValue;

	return
	(
		value.size() == 1
		&& (value[0] >= charMin && value[0] <= charMax)
	);
}

bool ScalarConverter::isFloat() const {

	std::string value = this->_stringValue;

	return
	(
	    value == "-inff"
		|| value == "+inff"
		|| value == "nanf"
		|| (
	  		 (
			   (
			     value.size() >= 4
			     && count(value, '.') == 1
			     && count(value, 'f') == 1
			     && value[0] != '.'
			     && value[value.size() - 2] != '.'
			     && value[value.size() - 1] == 'f'
			   )
			   || (
				    value.size() >= 5
			 	    && value[0] == '-'
			 	    && count(value, '.') == 1
			 	    && count(value, 'f') == 1
			 	    && value[1] != '.'
			 	    && value[value.size() - 2] != '.'
			 	    && value[value.size() - 1] == 'f'
			   )
			 )
	  		 && std::stod(value) >= floatMin
	  		 && std::stod(value) <= floatMax
	  	)
	);
}

bool ScalarConverter::isDouble() const {

	std::string value = this->_stringValue;

	return
	(
		value == "-inf"
		|| value == "+inf"
		|| value == "nan"
	  	|| (
			 (
			   (
			     value.size() >= 3
			     && count(value, '.') == 1
			     && value[0] != '.'
			     && value[value.size() - 1] != '.'
			   )
			   || (
				    value.size() >= 4
				    && value[0] == '-'
				    && count(value, '.') == 1
				    && value[1] != '.'
				    && value[value.size() - 1] != '.'
			   )
			 )
	  		 && std::stold(value) >= doubleMin
	  		 && std::stold(value) <= doubleMax
		)
	);
}

void ScalarConverter::detectType() {
	if (isInt())
		this->_typeOfValue = "int";
	else if (isChar())
		this->_typeOfValue = "char";
	else if (isFloat())
		this->_typeOfValue = "float";
	else if (isDouble())
		this->_typeOfValue = "double";
	else
		throw ScalarConverter::InvalidLiteralException();
}

void ScalarConverter::convertToRightType()
{
	if (this->_typeOfValue == "int")
		this->_intValue = std::stoi(this->_stringValue);
	else if (this->_typeOfValue == "char")
		this->_charValue = this->_stringValue[0];
	else if (this->_typeOfValue == "float")
		this->_floatValue = std::stof(this->_stringValue);
	else if (this->_typeOfValue == "double")
		this->_doubleValue = std::stod(this->_stringValue);
}

void ScalarConverter::convertToOtherTypes()
{
	this->_isValidChar = true;
	this->_isValidInt = true;
	this->_isValidFloat = true;
	this->_isValidDouble = true;

	if (this->_typeOfValue == "char")
	{
		this->_intValue = static_cast<int>(this->_charValue);
		this->_floatValue = static_cast<float>(this->_charValue);
		this->_doubleValue = static_cast<double>(this->_charValue);
	}
	else if (this->_typeOfValue == "int")
	{
		this->_charValue = static_cast<char>(this->_intValue);
		this->_floatValue = static_cast<float>(this->_intValue);
		this->_doubleValue = static_cast<double>(this->_intValue);

		if (this->_intValue > charMax || this->_intValue < charMin)
			this->_isValidChar = false;
	}
	else if (this->_typeOfValue == "float")
	{
		this->_intValue = static_cast<int>(this->_floatValue);
		this->_charValue = static_cast<char>(this->_floatValue);
		this->_doubleValue = static_cast<double>(this->_floatValue);

		if (this->_floatValue > charMax || this->_floatValue < charMin)
			this->_isValidChar = false;
		if (this->_floatValue > intMax || this->_floatValue < intMin)
			this->_isValidInt = false;
	}
	else if (this->_typeOfValue == "double")
	{
		this->_intValue = static_cast<int>(this->_doubleValue);
		this->_charValue = static_cast<char>(this->_doubleValue);
		this->_floatValue = static_cast<float>(this->_doubleValue);

		if (this->_doubleValue > charMax || this->_doubleValue < charMin)
			this->_isValidChar = false;
		if (this->_doubleValue > intMax || this->_doubleValue < intMin)
			this->_isValidInt = false;
		if (this->_doubleValue > floatMax || this->_doubleValue < floatMin)
			this->_isValidFloat = false;
	}
}

void ScalarConverter::convert()
{
	try {
		this->detectType();
		this->convertToRightType();
		this->convertToOtherTypes();
	}
	catch (ScalarConverter::InvalidLiteralException) {
		throw ScalarConverter::InvalidLiteralException();
	}
}

void ScalarConverter::printAllTypes() const
{
	std::cout << "char: ";

	if (!this->_isValidChar)
		std::cout << "impossible" << std::endl;
	else if (this->_charValue >= 32 && this->_charValue <= 126)
		std::cout << "'" << this->_charValue << "'" << std::endl;
	else
		std::cout << "Non displayable" << std::endl;

	std::cout << "int: ";

	if (!this->_isValidInt)
		std::cout << "impossible" << std::endl;
	else
		std::cout << this->_intValue << std::endl;

	std::cout << "float: ";

	if (!this->_isValidFloat)
		std::cout << "impossible" << std::endl;
	else
		std::cout << std::fixed << std::setprecision(1) << this->_floatValue << 'f' << std::endl;

	std::cout << "double: ";

	if (!this->_isValidDouble)
		std::cout << "impossible" << std::endl;
	else
		std::cout << std::fixed << std::setprecision(1) << this->_doubleValue << std::endl;
}

const char* ScalarConverter::InvalidLiteralException::what() const throw() {
	return "Invalid literal";
}

