#include <iostream>
#include <fstream>
#include <string>

const std::string fileName = "Library/HighScore.txt";

bool checkExistance(const std::string& Name)
{
    std::ifstream f (Name.c_str());
    bool check = f.good();
    f.close();
    return check;
}

void WriteFile(int score)
{
    
    std::ofstream file(fileName.c_str());
    file << score;
    file.close();
    
}

void ReadFile(int* score)
{
    if(!checkExistance(fileName))
    {
        std::ofstream file(fileName.c_str());
        file << 0;
        file.close();
        *score = 0;
    }else
    {
        std::ifstream file(fileName.c_str());
        file >> *score;
        file.close();
    }
}