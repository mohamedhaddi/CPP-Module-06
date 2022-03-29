/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 13:25:54 by mhaddi            #+#    #+#             */
/*   Updated: 2022/03/29 23:10:07 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base *generate(void)
{
	srand(time(NULL));
	int rand_num = rand() % 3;
	if (rand_num == 0)
	{
		std::cout << "An instance of class A has been created" << std::endl;
		return (new A);
	}
	else if (rand_num == 1)
	{
		std::cout << "An instance of class B has been created" << std::endl;
		return (new B);
	}
	else
	{
		std::cout << "An instance of class C has been created" << std::endl;
		return (new C);
	}
}

void identify(Base* p)
{
	if (dynamic_cast<A*>(p))
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B*>(p))
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C*>(p))
		std::cout << "C" << std::endl;
}

void identify(Base& p)
{
    try {
		(void) dynamic_cast<A&>(p);
		std::cout << "A" << std::endl;
	} catch (std::bad_cast& e) {
		try {
			(void) dynamic_cast<B&>(p);
			std::cout << "B" << std::endl;
		} catch (std::bad_cast& e) {
			try {
				(void) dynamic_cast<C&>(p);
				std::cout << "C" << std::endl;
			} catch (std::bad_cast& e) {
				std::cout << "Unknown" << std::endl;
			}
		}
	}
}

int main()
{
	Base *ptr = generate();

	std::cout << "identify(ptr): ";
	identify(ptr);

	std::cout << "identify(*ptr): ";
	identify(*ptr);

	delete ptr;
}
