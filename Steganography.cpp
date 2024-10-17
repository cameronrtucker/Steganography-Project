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
int getNthBit(char cipherChar, int N);


/**
 * reads in ppm image with fileName, stores in other member values
 *
 * @param string filename 
 * @pre file exists
 * @return void 
 * @post values from ppm image are stored
 * 
 */
void readImage(string fileName);
  // ask for fileName? (check to make sure file exists) 
  // open file with fileName
  // reads file into an array through a loop until !file (?)
  // file info is stored in an array? or is that what the vector is for

/**
 * writes the ppm image stored in member data to fileName
 *
 * @param string filename 
 * @pre file exists
 * @return void 
 * @post the image is printed
 * 
 */
void printImage(string fileName);
  // use filename to open file 
  // writes the info from the member data (from an array?) to fileName


/**
 * reads the plain text file with the fileName and stores it in member data
 *
 * @param string filename 
 * @pre file exists
 * @return void 
 * @post 
 * 
 */
void readCipherText(string fileName);


/**
 * writes the plain text (ciphertext) to the file fileName
 *
 * @param string fileName 
 * @pre file exists
 * @return void 
 * @post cipher text is in fileName
 * 
 */
void printCipherText(string fileName); 


/**
 * zeros out the least significant bit of each color value in colorData
 *
 * @pre colorData exists
 * @return void 
 * @post least significant bit for each color value in colorData is 0
 * 
 */
void cleanImage();


/**
 * stores the text from cipherText in the image colorData
 *
 * @pre cipherText amd colorData exist
 * @return void 
 * @post text is stored in the colorData
 * 
 */
void encipher();


/**
 * reads the ciphertext back from colorData and stores it in cipherText
 *
 * @pre colorData and cipherText exist
 * @return void 
 * @post the cipher is stored in cipherText
 * 
 */
void decipher();

int Steganography::getNthBit(char cipherChar, int n){
  return(cipherChar >> n) & 1; //shifts bit n times to the right, masks with 1
}

void Steganography::readImage(string fileName) {
  ifstream inputFile(fileName);

  inputFile>>magicNumber>>width>>height>>maxColor;
  colorData.resize(width*height*3); //RGB pixels have 3 color values

  for (int& color : colorData) {
    inputFile >> color;
  }

  inputFile.close();
}

void Steganography::printImage(string fileName) {
  ofstream outputFile(fileName);
  outputFile<<magicNumber<<"\n"<<width<<" "<<height<<"\n"<<maxColor<<"\n";

  for (size_t i=0; i<colorData.size(); ++i){
    outputFile<<colorData[i]<<" ";
    if ((i + 1) % 3 == 0) {
      outputFile <<"\n"; //should newline after RGB triplets
    }
  }
  outputFile.close();
}

void Steganography::readCipherText(string fileName) {
  ifstream inputFile(fileName);

  getline(inputFile, cipherText, '\0'); //reads entire file
  inputFile.close();
}

void Steganography::printCipherText(string fileName) {
  ofstream outputFile(fileName);
  outputFile<< cipherText;
  outputFile.close();
}

void Steganography::cleanImage(){
  for (int&color : colorData) {
    color&= ~1; //zero out least significant bit
  }
}

void Steganography::encipher(){
  int bitIndex = 0; //tracks which bit of message being encoded
  for (char c : cipherText) {
    for (int i=0; i<8; ++i) { //each character has 8 bits
      if (bitIndex < static_cast<int>(colorData.size())) {
	colorData[bitIndex] |= getNthBit(c, i); //Set the LSB to the bit of the message
	++bitIndex;
      }
    }
  }
}


void Steganography::decipher() {
  cipherText.clear();
  char currentChar = 0;
  int bitIndex = 0;

  for (size_t i=0; i<colorData.size(); ++i) {
    int lsb = (colorData[i] & 1);
    currentChar |= lsb << (bitIndex % 8); //extract lsb and shift left to build the character
    cout<<"Extracted LSB: " <<lsb<< "Current Char: "<<(int)currentChar<<endl; //DEBUG OUTPUT
    
    if (++bitIndex %8 == 0) { //after 8 bits, form a character
      if (currentChar == '\0'){ //termination character
        break;
    }
      cipherText += currentChar; // add char to decoded text
      cout<<"Formed Char: "<<currentChar<<endl; //DEBUG OUTPUT
      currentChar = 0; //reset for next run
    }
  }
}
