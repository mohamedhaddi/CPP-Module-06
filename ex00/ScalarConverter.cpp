/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:14:50 by mhaddi            #+#    #+#             */
/*   Updated: 2022/03/29 16:04:00 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <iostream>

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

	return (
		indexOfNonDigit == std::string::npos
		|| (
			indexOfNonDigit == 0
			&& value[indexOfNonDigit] == '-'
			&& value.substr(1).find_first_not_of("0123456789") == std::string::npos
		)
	);

}

bool ScalarConverter::isChar() const {

	std::string value = this->_stringValue;

	return (
		value.size() == 1
		&& (value[0] >= 32 && value[0] <= 126)
	);

}

bool ScalarConverter::isFloat() const {

	std::string value = this->_stringValue;

	return (
		value == "-inff"
		|| value == "+inff"
		|| value == "nanf"
		|| (
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
	);

}

bool ScalarConverter::isDouble() const {

	std::string value = this->_stringValue;

	return (
		value == "-inf"
		|| value == "+inf"
		|| value == "nan"
		|| (
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
	if (this->_typeOfValue == "int")
	{
		this->_charValue = static_cast<char>(this->_intValue);
		this->_floatValue = static_cast<float>(this->_intValue);
		this->_doubleValue = static_cast<double>(this->_intValue);
	}
	else if (this->_typeOfValue == "char")
	{
		this->_intValue = static_cast<int>(this->_charValue);
		this->_floatValue = static_cast<float>(this->_charValue);
		this->_doubleValue = static_cast<double>(this->_charValue);
	}
	else if (this->_typeOfValue == "float")
	{
		this->_intValue = static_cast<int>(this->_floatValue);
		this->_charValue = static_cast<char>(this->_floatValue);
		this->_doubleValue = static_cast<double>(this->_floatValue);
	}
	else if (this->_typeOfValue == "double")
	{
		this->_intValue = static_cast<int>(this->_doubleValue);
		this->_charValue = static_cast<char>(this->_doubleValue);
		this->_floatValue = static_cast<float>(this->_doubleValue);
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

char ScalarConverter::getCharValue() const
{
	return this->_charValue;
}

int ScalarConverter::getIntValue() const
{
	return this->_intValue;
}

float ScalarConverter::getFloatValue() const
{
	return this->_floatValue;
}

double ScalarConverter::getDoubleValue() const
{
	return this->_doubleValue;
}

const char* ScalarConverter::InvalidLiteralException::what() const throw() {
	return "Invalid literal";
}

