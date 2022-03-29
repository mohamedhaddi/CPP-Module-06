/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 13:25:54 by mhaddi            #+#    #+#             */
/*   Updated: 2022/03/29 16:13:24 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <iostream>
#include <iomanip>

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Usage: ./convert <char|int|float|double literal>" << std::endl;
		return (0);
	}

	ScalarConverter converter(argv[1]);

	try {
		converter.convert();
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
		return (0);
	}

	std::cout << "char: '" << converter.getCharValue() << "'" << std::endl;
	std::cout << "int: " << converter.getIntValue() << std::endl;
	std::cout << "float: " << std::fixed << std::setprecision(1) << converter.getFloatValue() << 'f' << std::endl;
	std::cout << "double: " << std::fixed << std::setprecision(1) << converter.getDoubleValue() << std::endl;

	return (0);
}
