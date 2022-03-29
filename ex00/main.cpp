/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 13:25:54 by mhaddi            #+#    #+#             */
/*   Updated: 2022/03/29 17:28:41 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <iostream>

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

	converter.printAllTypes();

	return (0);
}
