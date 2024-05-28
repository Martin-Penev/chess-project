#include "Player.hpp"
#include <iostream>
#include <cstring>
Player::Player(const char* nameVal,const char* colorVal,int ratingVal):name(new char[strlen(nameVal)+1]{}),color(new char[strlen(colorVal)+1]),rating(ratingVal)
{
    strcpy(this->name,nameVal);
    strcpy(this->color,colorVal);
}
Player::Player(const Player &other):name(new char[strlen(other.name)+1]{}),color(new char[strlen(other.color)+1]),rating(other.rating)
{
    strcpy(this->name,other.name);
    strcpy(this->color,other.color);

}
Player::~Player()
{
    delete[] name;
    delete[] color;
}
Player &Player::operator=(const Player &other) {
     if (this != &other) {
        delete[] name;
        delete[] color;
     
        name = new char[strlen(other.name) + 1]{};
        color=new char[strlen(other.color)+1]{};
        strcpy(name, other.name);
        strcpy(color,other.color);
        rating = other.rating;
        }
        return *this; 
}
void Player::info()
{
    std::cout<<"------------------\n";
    std::cout<<"Name:  "<<name<<std::endl;
    std::cout<<"Color: "<<color<<std::endl;
    std::cout<<"Elo:   "<<rating<<std::endl;
    std::cout<<"------------------\n";
}
