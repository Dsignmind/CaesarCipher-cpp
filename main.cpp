//
//  CST 312: lab2_wilson.cpp
//
//  Program that allows a user to create a named
//  encrypted file using a cipher key. Or decrypt
//  a specified file using a previously created
//  cipher key value. If key is unknown a bruteforce
//  option can be chosen.
//
//  Created by Daniel Wilson on 3/10/16.
//  Copyright © 2016 Daniel Wilson. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
using namespace std;
void encrypt(string in_filename, string out_filename, int shift)//encrypt function gets passed input filename containing plaintext, and output filename and key value
{
    string input_text;//Variable for current text, counter, text length
    int counter = 0, text_length;
    ifstream plain_file (in_filename);//Create ifstream instance
    ofstream encrypted_file;//Create ofstream instance
    encrypted_file.open(out_filename);//Open file to write encrypted text
    if(encrypted_file.fail())//If this fails, alert user
    {
        cout << "Error opening output file!";
    }
    if (plain_file.is_open())//Open plaintext file to parse
    {
        while ( getline (plain_file,input_text) )//Loop until there are no more lines of text
        {
            text_length = (int)input_text.length();//Get length of text
            for(counter = 0; counter < text_length; counter++)//Loop for length of text...
            {
                if(isalpha(input_text[counter]))//if element is a letter...
                {
                    input_text[counter] = tolower(input_text[counter]);//change character to lowercase...
                    for(int i = 1; i <= shift; i++)//loop for key size...
                    {
                        if (input_text[counter] == 'z')//if element gets to end of alphabet...
                        {
                            input_text[counter] = 'a';//wrap around to begining of alphabet
                        }
                        else//If it doesn't then shift letter
                            input_text[counter]++;
                    }
                }
            }
            encrypted_file << input_text;//Write text string to file
        }
        plain_file.close();//Close both text files
        encrypted_file.close();
    }
    else//If unable to open plaintext file, alert user
        cout << "Unable to open file!";
}
void decrypt(string filename, int shift)//decrypt gets passed input file path and key value
{
    string cipher_text;//Variable for ciphertext string, counter, and string length
    int counter = 0, text_length;
    ifstream decrypt_file (filename);//Create ifstream instance
    if (decrypt_file.is_open())//If opening encrypted text file is successful
    {
        while ( getline(decrypt_file,cipher_text) )//While there are lines of input...
        {
            text_length = (int)cipher_text.length();//get length of text string...
            for(counter = 0; counter < text_length; counter++)//loop for as long as text string
            {
                if(isalpha(cipher_text[counter]))//If element is a character...
                {
                    cipher_text[counter] = tolower(cipher_text[counter]);//change character to lowercase...
                    for(int i = shift; i > 0; i--)//loop for key size...
                    {
                        if (cipher_text[counter] == 'a')//if element gets to begining of alphabet...
                        {
                            cipher_text[counter] = 'z';//wrap back to end of alphabet
                        }
                        else//If it doesn't then shift letter
                            cipher_text[counter]--;
                    }
                }
            }
            cout << cipher_text << "\n";//Print out shifted text string
        }
        decrypt_file.close();//Close text file
    }
    else//If unable to open ciphertext file alert user
    {
        cout << "Unable to open file!";
    }
}

int main(int argc, const char * argv[]) {
    string input_file, output_file;//Input variables for filenames, key size, input choices, and flags
    int shift, choice, decrypt_choice, key, inner_flag = 0;
    
    cout << "Enter 1 for encryption, or 2 for brute force decryption: ";//Prompt user for choice encrypt/decrypt
    cin >> choice;//Store choice
    switch(choice)//Interpret choice
    {
        case 1://If encryption...
        {
            cout << "Enter a file to encrypt (e.g. filename.txt): ";//prompt for encryption filepath...
            cin >> input_file;
            cout << "Enter a shift amount: ";//prompt for key size...
            cin >> shift;
            cout << "Enter file to write to(e.g. filename.txt): ";//prompt for output file...
            cin >> output_file;
            encrypt(input_file,output_file,shift);//call encrypt function
            break;
        }
        case 2://If decryption...
        {
            cout << "Do you know the key? \n" << "Enter 1 for yes, 2 for no: ";//ask user if they know the key...
            cin >> decrypt_choice;
            switch(decrypt_choice)//check if they do...
            {
                case 1://if they do...
                {
                    cout << "Enter a file to decrypt (e.g. filename.txt): ";//prompt for input filepath...
                    cin >> input_file;
                    cout << "Enter key: ";//prompt for key size...
                    cin >> key;
                    cout << "\n";
                    decrypt(input_file, key);//call decrypt function
                    cout << "\n";
                    inner_flag = 1;//set inner flag
                    break;
                }
                case 2://If they don't know the key...
                {
                    cout << "Enter a file to decrypt (e.g. filename.txt): ";//prompt for input filepath...
                    cin >> input_file;
                    cout << "\n";
                    for(shift = 0; shift < 26; shift++)//for number of letter in alphabet...
                    {
                        cout << "Key:" << shift << "\n";//display key value...
                        decrypt(input_file,shift);//call decrypt function with incremented key value...
                        cout << "\n";
                    }
                    inner_flag = 1;//set inner flag
                    break;
                }
                default://If bad input was passed alert user, set inner flag, and quit
                    cout << "Please enter a valid choice!\n";
                    inner_flag = 1;
                    return 0;
            }
            
        }
        default://If we got here, bad input was passed...
            if(inner_flag == 0)
            {
            cout << "Please enter a valid choice!\n";
            break;
            }
            else//or inner loop was executed
                break;
    }
    return 0;
}
