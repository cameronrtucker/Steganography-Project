/**
 * @file main.cpp
 * @author Mangos: Cameron Tucker and Ella Self
 * @date 2024-10-14
 * @brief main file for Steganography 
 * 
 * steganography main file
 */

#include "Steganography.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
  Steganography steg;
  string ppmFile, textFile, outputFile;
  int choice;

  cout <<"Choose operation: \n1. Encode\n2. Decode\n";
  cin >> choice;

  if (choice == 1) {
    cout<<"Enter input PPM file name: ";
    cin>>ppmFile;
    steg.readImage(ppmFile);

    cout<<"Enter input text file name: ";
    cin>>textFile;
    steg.readCipherText(textFile);

    cout<<"Enter output PPM file name: ";
    cin>>outputFile;
    steg.cleanImage();
    steg.encipher();
    steg.printImage(outputFile);

  } else if (choice == 2) {
    cout<<"Enter input PPM file name: ";
    cin>>ppmFile;
    steg.readImage(ppmFile);

    cout<<"Enter output text file name: ";
    cin>>outputFile;
    steg.decipher();
    steg.printCipherText(outputFile);
  }
  return 0;
}
