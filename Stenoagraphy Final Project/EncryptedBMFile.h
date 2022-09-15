// --------------------------------------------------------
//  File: EncryptedBMFile.h
//  Author: Joseph Racz
//  Purpose: class definition to encrypt/decrypt a bitmap
//  file. Inherits from BMFile class
// --------------------------------------------------------

#ifndef ENCRYPTEDBMFILE_H
#define ENCRYPTEDBMFILE_H

#include "BMFile.h"

class EncryptedBMFile : public BMFile {
public:

	BMFile encrypt(std::string message, BMFile bmFile);
	std::string decrypt(EncryptedBMFile encryptedFile);

private:

};

#endif