#ifndef ENCRYPTOR_H
#define ENCRYPTOR_H

#include <ctype.h>
#include <string>

class Encrypter
{
  public:
	Encrypter();

	/* Creates the Vigenere Table to be used in the algorithm */
	void initializeVigenereTable();

	/*	Sets the private key to be used in the process */
	void setKey(std::string key);

	/* Gets the private key */
	std::string getKey();

	/* Encodes the string passed by parameter */
	std::string encryptString(std::string string);

	/* Decodes ths string passed by parameter */
	std::string decryptString(std::string string);

	/* User inputs a string to be used in the Encryption process (Console use only ***for tests) */
	std::string setString();

	/* Finds the corresponding column to the letter in the encoded string */
	char findCorrectRow(char keyChar, char letter);

	void run_program();

  private:
	std::string key;
};

#endif // !ENCRYPTOR_H
