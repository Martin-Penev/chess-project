#ifndef PLAYER_HPP
#define PLAYER_HPP
class Player
{
    private:
    char* name;
    char* color;
    unsigned int rating;

    public :
    Player(const char* name="<Anonymous>",const char* color="none",int rating=400);
    Player(const Player &);
    ~Player();
    Player &operator=(const Player &);
    void info() ;
    
};
#endif