#ifndef STEGANOGRAPHY_H
#define STEGANOGRAPHY_H

#include <string>
#include <vector>

using namespace std;

class Steganography {

 private:
  string magicNumber; //P3 value
  int width, height, maxColor; //image height and width, maximum color value
  vector<int> colorData; //list of color values (RGB)
  string cipherText; //hidden data
  int getNthBit(char cipherChar, int n); //gets nth bit from a character

 public:
  void readImage(string fileName); //reads ppm file and stores data
  void printImage(string fileName); //writes image data to ppm file
  void readCipherText(string fileName); // reads plain text of data to be hidden
  void printCipherText(string fileName); //writes decoded text 
  void cleanImage(); //zeroes out least significant bits of color value
  void encipher(); // encodes text into image data
  void decipher(); //decodes hidden message from image data
};

#endif 
