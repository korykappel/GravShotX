#include "HighScoreEntry.h"

HighScoreEntry::HighScoreEntry(std::string n, int s)
{
	name = n;
	score = s;
}

std::ostream& operator<<(std::ostream& os, const HighScoreEntry& s)
{
	os << s.score << ' ' << s.name;
    return os;
}

std::istream& operator>> (std::istream &in, HighScoreEntry &s)
{
	in >> s.score;
	in >> s.name;
    return in;
}