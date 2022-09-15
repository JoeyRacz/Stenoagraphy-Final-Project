// --------------------------------------------------------
//    File: bitmap.cpp
//  Author: COP 3003 Programming II
// Purpose: main application file for bitmap program that
//  currently opens a bitmap and copies it to an output file
// --------------------------------------------------------
#include <iostream>
#include <fstream>

#include "BMFile.h"     // bitmap file class
#include "EncryptedBMFile.h"

int main() {

    std::string inFileName, outFileName;
	int choice;
	std::string message;
	EncryptedBMFile* encryptedFile;

	std::cout << "1. Enrypting\n";
	std::cout << "2. Decrypting\n";
	std::cout << "Enter: ";
	std::cin >> choice;

	switch (choice) {
	case 1: {
		std::cout << "Enter bitmap file that will be encrypted: ";
		std::cin >> inFileName;
		std::cout << "Enter string to encrypt: ";
		std::cin >> message;
		std::cout << "Enter encrypted bitmap file name: ";
		std::cin >> outFileName;
		std::ifstream inFile;
		inFile.open(inFileName, std::ios::binary);

		std::ofstream outFile;
		outFile.open(outFileName, std::ios::out | std::ios::trunc | std::ios::binary);
		BMFile bmFile = BMFile(&inFile, &outFile);

		int bytes = bmFile.load();
		
		encryptedFile = reinterpret_cast<EncryptedBMFile*>(&bmFile);
		encryptedFile->encrypt(message, bmFile);

		bytes = encryptedFile->BMFile::store();
		break;
	}
	case 2: {
		std::cout << "Enter bitmap file that will be decrypted: ";
		std::cin >> inFileName;
		std::ifstream inFile;
		inFile.open(inFileName, std::ios::binary);
		BMFile bmFile = BMFile(&inFile);
		
		int bytes = bmFile.load();
		
		encryptedFile = reinterpret_cast<EncryptedBMFile*>(&bmFile);
		EncryptedBMFile newEncrypt = *encryptedFile;
		message = newEncrypt.decrypt(newEncrypt);

		std::cout << "The message was: " + message;
		break;
	}
	default:
		std::cout << "Invalid choice!\n";
	}


    return 0;
}
