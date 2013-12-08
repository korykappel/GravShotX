#include <string>
#include <iostream>

class HighScoreEntry
{
public:
   std::string name;
   int score;

   HighScoreEntry(std::string n, int s);

   bool operator<(const HighScoreEntry& other) const
   {
       // code that determines ordering goes here
       return score > other.score;
	   if(score > other.score) return true;
	   else if(score == other.score)
	   {
		   return name < other.name;
	   }
	   else return false;
   }

   friend std::ostream& operator<<(std::ostream& os, const HighScoreEntry& s);
    friend std::istream& operator>> (std::istream &in, HighScoreEntry &s);
};

