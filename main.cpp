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
	double tokengeneralcooldown;
	double tokenattemptcooldown;
	double tokensuccessrate;
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
		{"bomber", {15.4, 4, {"bomb"}, {"inspire"}}},
		{"brave", {15.4, 4, {"bomb"}, {"inspire"}}},
		{"bumble", {15.4, 4, {"bomb"}, {"inspire"}}},
		{"cool", {15.4, 4, {"bomb"}, {"inspire"}}},
		{"hasty", {15.4, 4, {"bomb"}, {"inspire"}}},
		{"looker", {15.4, 4, {"bomb"}, {"inspire"}}},
		{"rad", {15.4, 4, {"bomb"}, {"inspire"}}},
		{"rascal", {15.4, 4, {"bomb"}, {"inspire"}}},
		{"stubborn", {15.4, 4, {"bomb"}, {"inspire"}}},
		{"bubble", {15.4, 4, {"bomb"}, {"inspire"}}},
		{"bucko", {15.4, 4, {"bomb"}, {"inspire"}}},
		{"commander", {15.4, 4, {"bomb"}, {"inspire"}}},
		{"demo", {15.4, 4, {"bomb"}, {"inspire"}}},
		{"exhausted", {15.4, 4, {"bomb"}, {"inspire"}}},
		{"fire", {15.4, 4, {"bomb"}, {"inspire"}}},
		{"frosty", {15.4, 4, {"bomb"}, {"inspire"}}},
		{"honey", {15.4, 4, {"bomb"}, {"inspire"}}},
		{"rage", {15.4, 4, {"bomb"}, {"inspire"}}},
		{"riley", {15.4, 4, {"bomb"}, {"inspire"}}},
		{"shocked", {15.4, 4, {"bomb"}, {"inspire"}}},
		{"baby", {15.4, 4, {"bomb"}, {"inspire"}}},
		{"carpenter", {15.4, 4, {"bomb"}, {"inspire"}}},
		{"demon", {15.4, 4, {"bomb"}, {"inspire"}}},
		{"diamond", {15.4, 4, {"bomb"}, {"inspire"}}},
		{"lion", {15.4, 4, {"bomb"}, {"inspire"}}},
		{"music", {15.4, 4, {"bomb"}, {"inspire"}}},
		{"ninja", {15.4, 4, {"bomb"}, {"inspire"}}},
		{"shy", {15.4, 4, {"bomb"}, {"inspire"}}},
		{"buoyant", {15.4, 4, {"bomb"}, {"inspire"}}},
		{"fuzzy", {15.4, 4, {"bomb"}, {"inspire"}}},
		{"precise", {15.4, 4, {"bomb"}, {"inspire"}}},
		{"spicy", {15.4, 4, {"bomb"}, {"inspire"}}},
		{"tadpole", {15.4, 4, {"bomb"}, {"inspire"}}},
		{"vector", {15.4, 4, {"bomb"}, {"inspire"}}},
		{"bear", {15.4, 4, {"bomb"}, {"inspire"}}},
		{"cobalt", {15.4, 4, {"bomb"}, {"inspire"}}},
		{"crimson", {15.4, 4, {"bomb"}, {"inspire"}}},
		{"digital", {15.4, 4, {"bomb"}, {"inspire"}}},
		{"festival", {15.4, 4, {"bomb"}, {"inspire"}}},
		{"gummy", {15.4, 4, {"bomb"}, {"inspire"}}},
		{"photon", {15.4, 4, {"bomb"}, {"inspire"}}},
		{"puppy", {15.4, 4, {"bomb"}, {"inspire"}}},
		{"tabby", {15.4, 4, {"bomb"}, {"inspire"}}},
		{"vicious", {15.4, 4, {"bomb"}, {"inspire"}}},
		{"windy", {15.4, 4, {"bomb"}, {"inspire"}}}
	};
	std::unordered_map<std::string, Token> TOKENLIST = {
		{"haste", {4.5, 4.5, 1.0/3.0}},
		{"focus", {4.5, 4.5, 1.0/3.0}},
		{"rage", {50.0, 15.0, 1.0}}, // battle only
		{"tokenlink", {5.0, 5.0, 1.0/3.0}},
		{"mark", {20.0, 5.0, 1.0/4.0}},
		{"babylove", {60.0, 5.0, 1.0/9.0}},
		{"melody", {45.0, 15.0, 1.0/3.0}},
		{"bomb", {8.0, 4.0, 1.0/4.0}},
		{"boost", {4.5, 4.5, 1.0/3.0}},
		{"honeygift", {120.0, 60.0, 1.0/4.0}},
		{"triangulate", {20.0, 10.0, 1.0/3.0}},
		{"marksurge", {24.0, 6.0, 1.0/4.0}},
		{"inferno", {30.0, 5.0, 1.0/6.0}},
		{"flamefuel", {45.0, 15.0, 1.0/3.0}},
		{"summonfrog", {50.0, 10.0, 1.0/4.0}},
		{"inflateballoon", {28.0, 8.0, 1.0/4.0}},
		{"surpriseparty", {360.0, 15.0, 1.0/8.0}},
		{"targetpractice", {24.0, 6.0, 1.0/4.0}},
		{"fuzzbombs", {20.0, 10.0, 1.0/3.0}},
		{"pollenhaze", {75.0, 4.0, 1.0/6.0}},
		{"beamstorm", {20.0, 10.0, 1.0/3.0}},
		{"scratch", {12.0, 6.0, 1.0/4.0}},
		{"tabbylove", {120.0, 60.0, 1.0/5.0}},
		{"fetch", {140.0, 5.0, 1.0/2.0}},
		{"puppylove", {80.0, 10.0, 1.0/5.0}},
		{"bearmorph", {45.0, 15.0, 1.0/2.0}},
		{"pulse", {12.0, 6.0, 1.0/4.0}},
		{"bombsync", {30.0, 15.0, 1.0/3.0}},
		{"festivegift", {480.0, 30.0, 1.0/8.0}},
		{"glob", {6.0, 3.0, 1.0/3.0}},
		{"gumdropbarrage", {9.0, 4.0, 1.0/4.0}},
		{"impale", {30.0, 1.0, 1.0}}, // battle only
		{"raincloud", {45.0, 20.0, 1.0/2.0}},
		{"tornado", {80.0, 10.0, 1.0/3.0}},
		{"glitch", {60.0, 10.0, 1.0/3.0}},
		{"mapcorruption", {360.0, 15.0, 1.0/8.0}},
		{"mindhack", {90.0, 2.0, 1.0/3.0}}, // battle only
		{"smile", {0.0, 15.0, 1.0}}, // dupe tokens
		{"festivemark", {300.0, 30.0, 1.0/6.0}},
		{"snowglobeshake", {300.0, 30.0, 1.0/6.0}},
		{"inspire", {60.0, 5.0, 1.0/100.0}},
	};
	return 0;
}
