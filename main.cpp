#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

struct Bee {
	double speed;
	int gather;
	std::vector<std::string> token;
	std::vector<std::string> gifted;
};

struct Token {
	double TGC;
	double TAC;
	double TSR;
};
/*
class Simulation {
public:

};
*/
int main()
{
	int MILLISECONDS = 3600000;
	std::string BEE = "ninja";
	bool GIFTED = true;
	int BEEMOVESPEED = 0;
	int BEEABILITYRATE = 4;
	int PLAYERBEEABILITYRATESTAT = 131;
	int PERCENTAGEBEEMOVESPEED = 11;
	int ADDBEEMOVESPEED = 0;
	int BEELEVEL = 21;
	int BEEQUIPBAR = 0;
	std::unordered_map<std::string, Bee> BEES = {
		{"basic", {14.0, 4, {}, {"inspire"}}},
		{"bomber", {15.4, 4, {"bomb"}, {"inspire"}}}
	};
	std::unordered_map<std::string, Token> TOKENLIST = {
		{"haste", {4.5, 4.5, 1.0 / 3.0}},
		{"focus", {4.5, 4.5, 1.0 / 3.0}},

	};
	return 0;
}
