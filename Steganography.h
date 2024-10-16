#ifndef STEGANOGRAPHY_H
#define STEGANOGARPHY_H

class Steganography {

 private:
  string magicNumber;
  int width, height, maxColor;
  vector<int> colorData;
  string cipherText;
  int getNthBit(char cipherChar, int n);

 public:
  void readImage(string fileName);
  void PrintImage(string fileName);
  void readCipherText(string fileName);
  void cleanImage();
  void encipher();
  void decipher();
}
