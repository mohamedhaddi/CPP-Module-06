/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 13:25:54 by mhaddi            #+#    #+#             */
/*   Updated: 2022/03/29 21:50:47 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

struct Data {
	int a;
	int b;
};

uintptr_t serialize(Data* ptr)
{
	return reinterpret_cast<uintptr_t>(ptr);
}

Data* deserialize(uintptr_t ptr)
{
	return reinterpret_cast<Data*>(ptr);
}

int main()
{
	Data refData;

	refData.a = 42;
	refData.b = 1337;

	std::cout << "refData.a = " << refData.a << std::endl;
	std::cout << "refData.b = " << refData.b << std::endl << std::endl;

	uintptr_t serialized = serialize(&refData);

	std::cout << "serialize(&refData): " << serialized << std::endl << std::endl;

	Data* deserialized = deserialize(serialized);

	std::cout << "deserialize(serialized)->a: " << deserialized->a << std::endl;
	std::cout << "deserialize(serialized)->b: " << deserialized->b << std::endl;

	return 0;
}
