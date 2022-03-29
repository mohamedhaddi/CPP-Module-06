/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:12:54 by mhaddi            #+#    #+#             */
/*   Updated: 2022/03/29 18:48:02 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

#include <stdexcept>
#include <string>

class ScalarConverter
{

	public:

		ScalarConverter(void);
		~ScalarConverter(void);
		ScalarConverter(std::string const & value);
		ScalarConverter(ScalarConverter const &src);
		ScalarConverter &operator=(ScalarConverter const &rhs);

		void convert(void);
		void printAllTypes() const;

	private:
		
		std::string _stringValue;
		std::string _typeOfValue;
		int _intValue;
		float _floatValue;
		double _doubleValue;
		char _charValue;
		bool _isValidInt;
		bool _isValidChar;
		bool _isValidFloat;
		bool _isValidDouble;

		void detectType();
		bool isDouble() const;
		bool isFloat() const;
		bool isInt() const;
		bool isChar() const;

		void convertToRightType();
		void convertToOtherTypes();
		char convertToChar();
		int convertToInt();
		float convertToFloat();
		double convertToDouble();

		class InvalidLiteralException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

};

#endif
