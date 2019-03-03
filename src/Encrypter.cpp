#include "Encrypter.h"
#include <iostream>
#include <string>
#include <sstream>
#include <string.h>
#include <array>

static unsigned char vigenereTable[26][26];
static const unsigned char ALPHABET[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

//ASCII 97 - 122 = a - z

Encrypter::Encrypter()
{
	initializeVigenereTable();
	this->key.clear();
}

void Encrypter::initializeVigenereTable()
{
	for (int i = 0; i < 26; i++)
	{
		for (int j = 0; j < 26; j++)
		{
			vigenereTable[i][j] = ALPHABET[(i + j) % (26)];
		}
	}
}

void Encrypter::setKey(std::string key)
{
	std::string tempKey;

	for (size_t i = 0; i < key.length(); i++)
	{
		tempKey += key[i];
	}

	this->key = tempKey;
}

std::string Encrypter::getKey()
{
	return this->key;
}

std::string Encrypter::encryptString(std::string string)
{
	if (this->key.empty())
	{
		std::cout << "The private key hasn't been set.\n";
		return nullptr;
	}

	std::string encodedString;
	uint16_t keyLength;

	for (size_t i = 0; i < string.length(); i++)
	{
		if ((string.at(i) > 96) && (string.at(i) < 123))
			encodedString += vigenereTable[tolower(string.at(i)) - 97][key.at(keyLength++) - 97];
		else if (string.at(i) == 32)
			encodedString += " ";
		if (keyLength == this->key.length())
			keyLength = 0;
	}

	return encodedString;
}

std::string Encrypter::decryptString(std::string string)
{
	if (this->key.empty())
	{
		std::cout << "The private key hasn't been set.\n";
		return nullptr;
	}

	uint16_t keyLength;

	std::string decodedString;

	for (size_t i = 0; i < string.length(); i++)
	{
		decodedString += findCorrectRow(key[keyLength++], string.at(i));

		if (keyLength == this->key.length())
			keyLength = 0;
	}

	return decodedString;
}

std::string Encrypter::setString()
{
	std::string message;
	std::cout << "Type the string you wish to encode: ";
	std::cin.ignore();
	getline(std::cin, message);

	return message;
}

char Encrypter::findCorrectRow(char keyChar, char letter)
{
	for (size_t i = 0; i < 26; ++i)
	{
		if (vigenereTable[i][keyChar - 97] == letter)
			return i + 97;
	}
	return -1;
}

void Encrypter::run_program()
{
	int option = 0;

	while (true)
	{
		std::cout << "******************************Encrypter*********************************\n";
		std::cout << "1 - Encrypt Message\n";
		std::cout << "2 - Decrypt Message\n";
		std::cout << "3 - Set Private Key\n";
		std::cout << "4 - Exit\n";
		std::cout << "Type the number of the operation you wish to execute: ";
		std::cin >> option;
		std::cout << std::endl;

		if (option == 1)
		{
			std::string message = this->setString();
			std::cout << this->encryptString(message) << std::endl;
		}
		else if (option == 2)
		{
			std::string message2 = this->setString();
			std::cout << this->decryptString(message2) << std::endl;
		}
		else if (option == 3)
		{
			std::string key;
			std::cout << "Enter the key you wish to use: ";
			std::cin.ignore();
			std::cin >> key;
			this->setKey(key);
		}
		else if (option == 4)
			exit(0);
		else
			std::cout << "Ingrese una opción válida.\n";
	}
}