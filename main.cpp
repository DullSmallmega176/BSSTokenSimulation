#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <random>
#include <cmath>
#include <chrono>

struct Bee {
	double speed;
	double gather;
	std::vector<std::string> token;
	std::vector<std::string> gifted;
};

struct TokenList {
	double tokengeneralcooldown;
	double tokenattemptcooldown;
	double tokensuccessrate;
};

struct Token {
	std::string name;
	int tokengeneralcooldown;
	int tokenattemptcooldown;
	double tokensuccessrate;
};

struct Timer {
	std::string name;
	int tokengeneralcooldown;
	int tokenattemptcooldown;
	int total;
};

class Simulation {
private:
	std::string beeName;
	Bee bee;
	double speed;
	int gatherTime;
	std::vector<std::string> tlist;
	std::unordered_map<int, Token> tokens;
	std::unordered_map<int, Timer> timers;
	int currentTime;
	int totalTokens;
	int movementTime;

	static double adjustCooldown(double base, double playerbeeabilityrate, double beeabilityrate, double beequipbeeabilityrate) {
		return base / (((playerbeeabilityrate + beequipbeeabilityrate) / 100) * (1 + (beeabilityrate / 100)));
	}

	static double adjustSpeed(double base, double addbeemovespeed, double percentagebeemovespeed, int level) {
		return (base + addbeemovespeed) * (1 + (percentagebeemovespeed / 100)) * (1 + ((level - 1) * 0.03));
	}

	static double adjustChance(double base, double playerbeeabilityrate, double beeabilityrate, double beequipbeeabilityrate) {
		return base * (1 + (((playerbeeabilityrate - 100) + beeabilityrate + beequipbeeabilityrate) * 0.01));
	}

	static int movementEffect(double walkspeed) {
		int studs = (rand() % 20 + 1) * 4;
		return static_cast<int>(round((studs / walkspeed) * 1000));
	}

	void reduceCooldown() {
		for (auto& token : timers) {
			token.second.tokengeneralcooldown = std::max(0, token.second.tokengeneralcooldown - 1);
			token.second.tokenattemptcooldown = std::max(0, token.second.tokenattemptcooldown - 1);
		}

		if (movementTime > 0) {
			movementTime--;
		} else if (gatherTime == 0) {
			movementTime = movementEffect(speed);
		}
	}

};

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
	int BEEQUIPBEEABILITYRATE = 0;
	std::unordered_map<std::string, Bee> BEES = {
		{"basic", {14.0, 4.0, {}, {"inspire"}}},
		{"bomber", {15.4, 4.0, {"bomb"}, {"inspire"}}},
		{"brave", {16.8, 4.0, {}, {"inspire"}}},
		{"bumble", {10.5, 4.0, {"bomb"}, {"inspire"}}},
		{"cool", {14.0, 3.0, {"boost"}, {"inspire"}}},
		{"hasty", {19.6, 3.0, {"haste"}, {"inspire"}}},
		{"looker", {14.0, 4.0, {"focus"}, {"inspire"}}},
		{"rad", {14.0, 4.0, {"boost"}, {"inspire"}}},
		{"rascal", {16.1, 4.0, {"bomb"}, {"inspire"}}},
		{"stubborn", {11.9, 4.0, {"mark"}, {"inspire"}}},
		{"bubble", {16.1, 4.0, {"bomb"}, {"inspire"}}},
		{"bucko", {15.4, 4.0, {"boost"}, {"inspire"}}},
		{"commander", {14.0, 4.0, {"focus", "bomb"}, {"inspire"}}},
		{"demo", {16.8, 4.0, {"bomb"}, {"inspire"}}},
		{"exhausted", {10.5, 4.6, {"bomb", "tokenlink"}, {"inspire"}}},
		{"fire", {11.2, 4.0, {"bomb"}, {"inspire"}}},
		{"frosty", {11.2, 4.0, {"boost", "bomb"}, {"inspire"}}},
		{"honey", {14.0, 4.0, {"honeygift"}, {"inspire"}}},
		{"rage", {15.4, 4.0, {"tokenlink"}, {"inspire"}}},
		{"riley", {15.4, 2.0, {"boost"}, {"inspire"}}},
		{"shocked", {19.6, 4.0, {"haste", "tokenlink"}, {"inspire"}}},
		{"baby", {10.5, 5.0, {"babylove"}, {"inspire"}}},
		{"carpenter", {11.2, 3.0, {"mark", "mark"}, {"inspire"}}},
		{"demon", {10.5, 4.0, {"bomb", "bomb"}, {"inspire"}}},
		{"diamond", {14.0, 4.0, {"boost", "honeygift"}, {"inspire"}}},
		{"lion", {19.6, 4.0, {"bomb"}, {"inspire"}}},
		{"music", {16.1, 4.0, {"melody", "focus", "tokenlink"}, {"inspire"}}},
		{"ninja", {21.0, 2.0, {"haste", "bomb"}, {"inspire"}}},
		{"shy", {18.2, 2.0, {"boost", "bomb"}, {"inspire"}}},
		{"buoyant", {14.0, 5.0, {"bomb", "inflateballoon"},{"inspire", "surpriseparty"}}},
		{"fuzzy", {11.9, 6.0, {"fuzzbombs", "bomb"}, {"inspire", "pollenhaze"}}},
		{"precise", {11.2, 4.0, {"targetpractice"}, {"inspire"}}},
		{"spicy", {14.0, 4.0, {"inferno"}, {"inspire", "flamefuel"}}},
		{"tadpole", {11.2, 6.0, {"boost", "summonfrog"}, {"inspire", "babylove"}}},
		{"vector", {16.24, 4.0, {"mark", "triangulate"}, {"inspire", "marksurge"}}},
		{"bear", {14.0, 2.0, {"bearmorph"}, {"inspire"}}},
		{"cobalt", {18.2, 4.0, {"pulse", "bombsync"}, {"inspire"}}},
		{"crimson", {18.2, 4.0, {"pulse", "bombsync"}, {"inspire"}}},
		{"digital", {11.9, 4.0, {"glitch"}, {"inspire", "mapcorruption"}}},
		{"festive", {16.1, 4.0, {"festivegift", "mark", "bomb"}, {"inspire"}}},
		{"gummy", {14.0, 4.0, {"gumdropbarrage", "glob"}, {"inspire"}}},
		{"photon", {21.0, 2.0, {"beamstorm", "haste"}, {"inspire"}}},
		{"puppy", {16.1, 4.0, {"fetch", "puppylove"}, {"inspire"}}},
		{"tabby", {16.1, 4.0, {"scratch", "tabbylove"}, {"inspire"}}},
		{"vicious", {17.5, 4.0, {"bomb"}, {"inspire"}}},
		{"windy", {19.6, 3.0, {"boost", "raincloud", "tornado"}, {"inspire"}}} };
	std::unordered_map<std::string, TokenList> TOKENLIST = {
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
