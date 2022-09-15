// --------------------------------------------------------
//  File: EncryptedBMFile.h
//  Author: Joseph Racz
//  Purpose: class implementation to encrypt/decrypt a bitmap
//  file. Inherits from BMFile class
// --------------------------------------------------------

#include "EncryptedBMFile.h"


BMFile EncryptedBMFile::encrypt(std::string message, BMFile bmFile) {
	PixelArray* pixels = bmFile.getPixels();
	Pixel** pixel = pixels->getPixels();
	BMInfoHeader* header = bmFile.getInfoHeader();
	int width = header->getWidth();
	int bytes = 0;

	int row = 0, column = 0;
	
	for (int next = 0; next < message.length(); next++) {
		char nextChar = message[next];

		for (int bit = 0; bit < 8; bit++) {
			int nextbit = nextChar & 1;
			
			Pixel *pixelSave = &pixel[row][column];

			BYTE blue = pixelSave->getBlue();

			
			if (nextbit) { 
				blue |= 1;
			}
			else {
				blue &= 0xFE;
			}

			pixelSave->setBlue(blue);

			nextChar >> 1; 

			column++;
			if (column == width) {
				column = 0;
				row++;
			}
			bytes++;

		} 


	} 


	for (int term = 0; term < 8; term++) {

		Pixel* pixelSave = &pixel[row][column];

		BYTE blue = pixelSave->getBlue();

		
		blue &= 0xFE; 

		pixelSave->setBlue(blue);


		column++;
		if (column == width) {
			column = 0;
			row++;
		}
		bytes++;

	}
	return bmFile;

}

std::string EncryptedBMFile::decrypt(EncryptedBMFile encryptedFile) {
	PixelArray* pixels = encryptedFile.getPixels();
	Pixel** pixel = pixels->getPixels();
	BMInfoHeader* header = encryptedFile.getInfoHeader();
	int width = header->getWidth();
	int row = 0, column = 0;
	char nextChar;
	std::string secretMessage = "";

	do {

		for (int i = 0; i < 8; i++) {

			Pixel* pixelSave = &pixel[row][column];

			nextChar |= (pixelSave->getBlue() & 1) << i;

			column++;
			if (column == width) {
				column = 0;
				row++;
			}

		}

		secretMessage += nextChar;
	} while (nextChar);
	return secretMessage;
}