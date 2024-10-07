#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

#include <sstream>


class CartridgeManager
{
private:

public:

};

void printFromTxtFile(std::ifstream& file);
void printFromGbFile(std::ifstream& file);


static void printRomInHex(const std::wstring& filePath) {
    std::ifstream file(filePath, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Erreur : impossible d'ouvrir le fichier " << std::endl;
        return;
    }

    //printFromTxtFile(file);
    printFromGbFile(file);

    file.close();
}

void printFromGbFile(std::ifstream& file)
{
    unsigned char byte;
    int byteCount = 0;

    while (file.read(reinterpret_cast<char*>(&byte), sizeof(byte))) {
        // Affiche chaque octet en hexadécimal avec deux chiffres et remplissage '0'
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte) << " ";

        // Limite le nombre de valeurs affichées par ligne à 16 pour une lecture plus facile
        if (++byteCount % 16 == 0) {
            std::cout << std::endl;
        }
    }
}

void printFromTxtFile(std::ifstream& file)
{
    std::string line;
    int byteCount = 0;

    while (std::getline(file, line)) {
        std::istringstream lineStream(line);
        std::string hexValue;

        // Lire chaque valeur hexadécimale de la ligne
        while (lineStream >> hexValue) {
            // Convertir la chaîne de caractères hexadécimale en valeur binaire
            unsigned int byte;
            std::stringstream ss;
            ss << std::hex << hexValue;
            ss >> byte;

            // Afficher chaque octet en hexadécimal avec deux chiffres
            std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte) << " ";

            // Limite le nombre de valeurs affichées par ligne à 16 pour une lecture plus facile
            if (++byteCount % 16 == 0) {
                std::cout << std::endl;
            }
        }
    }
}