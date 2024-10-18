/**
 * @file Steganography.cpp
 * @author Mangos : Cameron Tucker and Ella Self
 * @date 2024-10-14
 * @brief steganography functions
 * 
 * steganography functions, comments
 */

#include "Steganography.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// vector stores color data as flat ints
vector<int> colorData;


/**
 * Returns the nth bit from the character getting encoded 
 *
 * @param char cipherChar 
 * @param int N 
 * @pre cipherChar and N exist
 * @return int n (nth bit of a char) 
 * @post nth bit is found and returned 
 * 
 */
int Steganography::getNthBit(char cipherChar, int n){
  return(cipherChar >> n) & 1; //shifts bit n times to the right, masks with 1
}


/**
 * reads in ppm image with fileName, stores in other member values
 *
 * @param string filename 
 * @pre file exists
 * @return void 
 * @post values from ppm image are stored
 * 
 */
void Steganography::readImage(string fileName) {
  ifstream inputFile(fileName);
  if (!inputFile.is_open()) {
    cout << "Please provide a valid file. \n";
  }
  
  inputFile >> magicNumber >> width >> height >> maxColor;
  colorData.resize(width*height*3); //RGB pixels have 3 color values

  for (int& color : colorData) {
    inputFile >> color;
  }

  inputFile.close();
}


/**
 * writes the ppm image stored in member data to fileName
 *
 * @param string filename 
 * @pre file exists
 * @return void 
 * @post the image is printed
 * 
 */
void Steganography::printImage(string fileName) {
  ofstream outputFile(fileName);
  if (!outputFile.is_open()) {
    cout << "Please provide a valid file. \n";
  }

  outputFile << magicNumber << "\n" << width<<" " << height<< "\n" <<maxColor<<"\n";

  for (size_t i=0; i<colorData.size(); ++i){
    outputFile << colorData[i] <<" ";
    if ((i + 1) % 3 == 0) {
      outputFile << "\n"; //should newline after RGB triplets
    }
  }
  outputFile.close();
}


/**
 * reads the plain text file with the fileName and stores it in member data
 *
 * @param string filename 
 * @pre file exists
 * @return void 
 * @post 
 * 
 */
void Steganography::readCipherText(string fileName) {
  ifstream inputFile(fileName);
  if (!inputFile.is_open()) {
    cout << "Please provide a valid file. \n";
  }
  
  getline(inputFile, cipherText, '\0'); //reads entire file
  inputFile.close();
}


/**
 * writes the plain text (ciphertext) to the file fileName
 *
 * @param string fileName 
 * @pre file exists
 * @return void 
 * @post cipher text is in fileName
 * 
 */
void Steganography::printCipherText(string fileName) {
  ofstream outputFile(fileName);
  if (!outputFile.is_open()) {
    cout << "Please provide a valid file. \n";
  }
  
  outputFile << cipherText; //added debug here before, works correctly 
  outputFile.close();
}


/**
 * zeros out the least significant bit of each color value in colorData
 *
 * @pre colorData exists
 * @return void 
 * @post least significant bit for each color value in colorData is 0
 * 
 */
void Steganography::cleanImage(){
  for (size_t i = 0; i < colorData.size(); ++i) {
    colorData[i] &= ~1; //zero out least significant bit
  }
}


/**
 * stores the text from cipherText in the image colorData
 *
 * @pre cipherText amd colorData exist
 * @return void 
 * @post text is stored in the colorData
 * 
 */
void Steganography::encipher(){
  cleanImage(); //clear lsbs before encoding
  size_t colorDataSize = colorData.size();
  size_t textLength = cipherText.length(); //get text length

  for (size_t i = 0; i < textLength && i * 8 < colorDataSize; ++i) {
    char currentChar = cipherText[i]; //get current char to encode
    cout << "Encoding character: " << currentChar << " (ASCII: " << (int)currentChar<< ")\n"; //DEBUG OUTPUT
    
    for (int bitIndex=0; bitIndex < 8; ++bitIndex) {
      int lsb = (currentChar >> (7 - bitIndex)) & 1; //gets bit 1 or 0
      cout << "Bit " << (7 - bitIndex) << ": " << lsb << "\n"; //DEBUG OUTPUT

      if ( i * 8 + bitIndex < colorDataSize) {
	colorData[i * 8 + bitIndex] = (colorData[i * 8 + bitIndex] & ~1) | lsb;
      }
    }
  }
}


/**
 * reads the ciphertext back from colorData and stores it in cipherText
 *
 * @pre colorData and cipherText exist
 * @return void 
 * @post the cipher is stored in cipherText
 * 
 */
void Steganography::decipher() {
  cipherText.clear();
  unsigned char currentChar = 0; //to prevent negative values
  int bitIndex = 0;

  for (size_t i = 0; i < colorData.size(); ++i) {
    int lsb = (colorData[i] & 1);
    currentChar |= (lsb << (7 - bitIndex)); //extract lsb and shift left to build the character
    bitIndex++; // move to next bit index
		       
    if (bitIndex == 8) { //after 8 bits, form a character
      if (currentChar == '\0') {
	break;} //breaks decode at delimiter.. prevents junk printing
      cipherText += currentChar; //add character to cipherText
      currentChar = 0; //reset for next run
      bitIndex = 0;
    }
  }
}
