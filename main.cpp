#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <random>
#include <cmath>
#include <chrono>
#include <iomanip>

std::mt19937 gen(std::random_device{}());
std::uniform_real_distribution<> dist(0.0, 1.0);
std::uniform_int_distribution<> dis(1, 20);

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
	double tokengeneralcooldown;
	double tokenattemptcooldown;
	int total;
};

class Simulation {
private:
	std::string beeName;
	Bee bee;
	double speed;
	int gatherTime;
	int movementTime;
	std::vector<std::string> tlist;
	std::unordered_map<std::string, Token> tokens;
	std::unordered_map<std::string, Timer> timers;
	int milliseconds;
	int currentTime;
	int totalTokens;

	inline double adjustCooldown(double base, double playerbeeabilityrate, double beeabilityrate, double beequipbeeabilityrate) {
		return base / (((playerbeeabilityrate + beequipbeeabilityrate) / 100) * (1 + (beeabilityrate / 100)));
	}

	inline double adjustSpeed(double base, double addbeemovespeed, double percentagebeemovespeed, int level) {
		return (base + addbeemovespeed) * (1 + (percentagebeemovespeed / 100)) * (1 + ((level - 1) * 0.03));
	}

	inline double adjustChance(double base, double playerbeeabilityrate, double beeabilityrate, double beequipbeeabilityrate) {
		return base * (1 + (((playerbeeabilityrate - 100) + beeabilityrate + beequipbeeabilityrate) * 0.01));
	}

	inline bool spinEffect(double tokensuccessrate) {
		return dist(gen) <= tokensuccessrate;
	}

	inline int movementEffect(double walkspeed) {
		int studs = dis(gen) * 4;
		return static_cast<int>(round((studs / walkspeed) * 1000));
	}

	void reduceCooldown() {
		for (auto& pair : timers) {
			auto& timer = pair.second;
			if (timer.tokengeneralcooldown > 0) --timer.tokengeneralcooldown;
			if (timer.tokenattemptcooldown > 0) --timer.tokenattemptcooldown;
		}

        if (movementTime > 0) {
            movementTime--;
        } else if (gatherTime == 0) {
            movementTime = movementEffect(speed);
        }
    }

	void tokenAttempt() {
		if (gatherTime > 0 && movementTime > 0) return;

		for (auto& pair : timers) {
			auto& name = pair.first;
			auto& timer = pair.second;

			if (name == "movement" || name == "gather") continue;
			if (timer.tokengeneralcooldown > 0 || timer.tokenattemptcooldown > 0) continue;
			if (!spinEffect(tokens[name].tokensuccessrate)) continue;
			timer.tokengeneralcooldown = tokens[name].tokengeneralcooldown;
			timer.tokenattemptcooldown = tokens[name].tokenattemptcooldown;
			timer.total++;
			totalTokens++;
			gatherTime += 1000;
			break;
		}
	}

	void updateGather() {
		if (gatherTime > 0) {
			gatherTime--;
		}
	}

	void step() {
		reduceCooldown();
		tokenAttempt();
		updateGather();
		currentTime++;
	}

public:
	Simulation(const std::string& beeName, int milliseconds, const Bee& bee, int beemovespeed, int beeabilityrate, int playerbeeabilityratestat, int percentagebeemovespeed, int addbeemovespeed, int beelevel, int beequipbeeabilityrate, const std::unordered_map<std::string, TokenList>& tokenLists, const std::vector<std::string>& beequipTokens)
		: beeName(beeName), bee(bee), milliseconds(milliseconds),
		speed(adjustSpeed(bee.speed, addbeemovespeed, percentagebeemovespeed, beelevel)),
		gatherTime(static_cast<int>(bee.gather * 1000)),
		tlist(bee.token),
		currentTime(0),
		totalTokens(0),
		tokens(),
		timers()
	{
		if (bee.gifted.size() > 0) {
			tlist.insert(tlist.end(), bee.gifted.begin(), bee.gifted.end());
		}
		tlist.insert(tlist.end(), beequipTokens.begin(), beequipTokens.end());

		for (const auto& tokenName : tlist) {
			Token token;
			token.name = tokenName;
			token.tokengeneralcooldown = static_cast<int>(adjustCooldown(tokenLists.at(tokenName).tokengeneralcooldown, playerbeeabilityratestat, beeabilityrate, beequipbeeabilityrate) * 1000);
			token.tokenattemptcooldown = static_cast<int>(adjustCooldown(tokenLists.at(tokenName).tokengeneralcooldown, playerbeeabilityratestat, beeabilityrate, beequipbeeabilityrate) * 1000);
			token.tokensuccessrate = adjustChance(tokenLists.at(tokenName).tokensuccessrate, playerbeeabilityratestat, beeabilityrate, beequipbeeabilityrate);
			tokens[tokenName] = token;

			Timer timer;
			timer.name = tokenName;
			timer.tokengeneralcooldown = token.tokengeneralcooldown;
			timer.tokenattemptcooldown = token.tokenattemptcooldown;
			timer.total = 0;
			timers[tokenName] = timer;
		}
		movementTime = movementEffect(speed);
	}

	double decimal(double value, int decimalPlace) {
		double multiplier = std::pow(10.0, decimalPlace);
		return std::round(value * multiplier) / multiplier;
	}

	void run() {
		std::cout << "script has started\n";
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		while (currentTime < milliseconds) {
			step();
		}
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		double minutes = milliseconds / 60000.0;
		double tokenAverage = totalTokens / minutes;
		double elapseTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() / 1000.0;
		std::cout << "it took " << std::fixed << std::setprecision(2) << elapseTime << " seconds to simulate " << std::fixed << std::setprecision(2) << minutes << " minutes" << std::endl;
		std::cout << "\n-- bee stats --\n";
		std::cout << beeName << "\n";
		std::cout << "total tokens produced: " << totalTokens << "\n";
		std::cout << "average tokens per minute: " << decimal(tokenAverage, 2) << "\n";
		std::cout << "-- each token breakdown --\n";
		for (auto it = timers.begin(); it != timers.end(); ++it) {
			std::string name = it->first;
			Timer& timer = it->second;
			if (name == "movement" || name == "gather") continue;
			std::cout << "- " << name << ": " << timer.total << " - Avg: " << decimal(timer.total / minutes, 2) << " per minute.\n";
		}
	}
};

int main()
{
	int milliseconds = 3600000;
	std::string beeName = "ninja";
	bool gifted = true;
	int beemovespeed = 5;
	int beeabilityrate = 0;
	int playerbeeabilityratestat = 131;
	int percentagebeemovespeed = 11;
	int addbeemovespeed = 0;
	int beelevel = 21;
	int beequipbeeabilityrate = 0;
	std::vector<std::string> beequipTokens = {};

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
		{"windy", {19.6, 3.0, {"boost", "raincloud", "tornado"}, {"inspire"}}}};

	std::unordered_map<std::string, TokenList> TOKENLIST = {
		{"haste", {4.5, 4.5, 1.0 / 3.0}},
		{"focus", {4.5, 4.5, 1.0 / 3.0}},
		{"rage", {50.0, 15.0, 1.0}}, // battle only
		{"tokenlink", {5.0, 5.0, 1.0 / 3.0}},
		{"mark", {20.0, 5.0, 1.0 / 4.0}},
		{"babylove", {60.0, 5.0, 1.0 / 9.0}},
		{"melody", {45.0, 15.0, 1.0 / 3.0}},
		{"bomb", {8.0, 4.0, 1.0 / 4.0}},
		{"boost", {4.5, 4.5, 1.0 / 3.0}},
		{"honeygift", {120.0, 60.0, 1.0 / 4.0}},
		{"triangulate", {20.0, 10.0, 1.0 / 3.0}},
		{"marksurge", {24.0, 6.0, 1.0 / 4.0}},
		{"inferno", {30.0, 5.0, 1.0 / 6.0}},
		{"flamefuel", {45.0, 15.0, 1.0 / 3.0}},
		{"summonfrog", {50.0, 10.0, 1.0 / 4.0}},
		{"inflateballoon", {28.0, 8.0, 1.0 / 4.0}},
		{"surpriseparty", {360.0, 15.0, 1.0 / 8.0}},
		{"targetpractice", {24.0, 6.0, 1.0 / 4.0}},
		{"fuzzbombs", {20.0, 10.0, 1.0 / 3.0}},
		{"pollenhaze", {75.0, 4.0, 1.0 / 6.0}},
		{"beamstorm", {20.0, 10.0, 1.0 / 3.0}},
		{"scratch", {12.0, 6.0, 1.0 / 4.0}},
		{"tabbylove", {120.0, 60.0, 1.0 / 5.0}},
		{"fetch", {140.0, 5.0, 1.0 / 2.0}},
		{"puppylove", {80.0, 10.0, 1.0 / 5.0}},
		{"bearmorph", {45.0, 15.0, 1.0 / 2.0}},
		{"pulse", {12.0, 6.0, 1.0 / 4.0}},
		{"bombsync", {30.0, 15.0, 1.0 / 3.0}},
		{"festivegift", {480.0, 30.0, 1.0 / 8.0}},
		{"glob", {6.0, 3.0, 1.0 / 3.0}},
		{"gumdropbarrage", {9.0, 4.0, 1.0 / 4.0}},
		{"impale", {30.0, 1.0, 1.0}}, // battle only
		{"raincloud", {45.0, 20.0, 1.0 / 2.0}},
		{"tornado", {80.0, 10.0, 1.0 / 3.0}},
		{"glitch", {60.0, 10.0, 1.0 / 3.0}},
		{"mapcorruption", {360.0, 15.0, 1.0 / 8.0}},
		{"mindhack", {90.0, 2.0, 1.0 / 3.0}}, // battle only
		{"smile", {0.0, 15.0, 1.0}}, // dupe tokens
		{"festivemark", {300.0, 30.0, 1.0 / 6.0}},
		{"snowglobeshake", {300.0, 30.0, 1.0 / 6.0}},
		{"inspire", {60.0, 5.0, 1.0 / 100.0}},
	};
	if (BEES.find(beeName) != BEES.end()) {
		Bee bee = BEES[beeName];
		Simulation simulation(beeName, milliseconds, bee, beemovespeed, beeabilityrate, playerbeeabilityratestat, percentagebeemovespeed, addbeemovespeed, beelevel, beequipbeeabilityrate, TOKENLIST, beequipTokens);
		simulation.run();
	} else {
		std::cerr << "Error: Bee '" << beeName << "' is not int he bee list.\n";
	}

	return 0;
}
