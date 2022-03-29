/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:12:54 by mhaddi            #+#    #+#             */
/*   Updated: 2022/03/29 16:01:03 by mhaddi           ###   ########.fr       */
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
		char getCharValue(void) const;
		int getIntValue(void) const;
		float getFloatValue(void) const;
		double getDoubleValue(void) const;

	private:
		
		std::string _stringValue;
		std::string _typeOfValue;
		int _intValue;
		float _floatValue;
		double _doubleValue;
		char _charValue;

		void detectType();
		bool isInt() const;
		bool isChar() const;
		bool isFloat() const;
		bool isDouble() const;

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
