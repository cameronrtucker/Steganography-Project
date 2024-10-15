/**
 * @file Stenography.cpp
 * @author Mangos : Cameron Tucker and Ella Self
 * @date 2024-10-14
 * @brief stenography functions
 * 
 * steganography functions, comments
 */

#include "Stenography.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


vector<int> colorData;


/**
 * returns the nth bit from the character getting encoded 
 *
 * @param char cipherChar 
 * @param int N 
 * @pre cipherChar and N exist
 * @return int n (nth bit of a char) 
 * @post 
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
void readImage(string filename);


/**
 * writes the ppm image stored in member data to fileName
 *
 * @param string filename 
 * @pre file exists
 * @return void 
 * @post 
 * 
 */
void printImage(string filename);


/**
 * reads the plain text file with the fileName and stores it in member data
 *
 * @param string filename 
 * @pre file exists
 * @return void 
 * @post 
 * 
 */
void readCipherText(string filename);


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
