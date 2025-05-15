#include "BelotTournament.h"
#include <iostream>
#include <algorithm> // for std::shuffle
#include <random>
#include <ctime>
#include <stdexcept>

// Utility for team array management
void BelotTournament::copyDynamic(const BelotTournament& other) {
    _teamCount = other._teamCount;
    _charityMoney = other._charityMoney;
    _tournament = new Team[_teamCount];
    for (int i = 0; i < _teamCount; ++i)
        _tournament[i] = other._tournament[i];
}

void BelotTournament::freeDynamic() {
    delete[] _tournament;
    _tournament = nullptr;
    _teamCount = 0;
    _charityMoney = 0;
}

// Constructors
BelotTournament::BelotTournament() : _tournament(nullptr), _teamCount(0), _charityMoney(0) {}

BelotTournament::BelotTournament(Team* teams, int teamCount, double charityMoney) 
    : _tournament(nullptr), _teamCount(0), _charityMoney(0) {
    setTournament(teams, teamCount, charityMoney);
}

BelotTournament::BelotTournament(const BelotTournament& other) {
    copyDynamic(other);
}

BelotTournament& BelotTournament::operator=(const BelotTournament& other) {
    if (this != &other) {
        freeDynamic();
        copyDynamic(other);
    }
    return *this;
}

BelotTournament::BelotTournament(BelotTournament&& other) noexcept
    : _tournament(other._tournament), _teamCount(other._teamCount), _charityMoney(other._charityMoney) {
    other._tournament = nullptr;
    other._teamCount = 0;
    other._charityMoney = 0;
}

BelotTournament& BelotTournament::operator=(BelotTournament&& other) noexcept {
    if (this != &other) {
        freeDynamic();
        _tournament = other._tournament;
        _teamCount = other._teamCount;
        _charityMoney = other._charityMoney;

        other._tournament = nullptr;
        other._teamCount = 0;
        other._charityMoney = 0;
    }
    return *this;
}

BelotTournament::~BelotTournament() {
    freeDynamic();
}

// Setters
void BelotTournament::setTournament(Team* teams, int teamCount, double charityMoney) {
    if (teamCount <= 2 || teamCount % 2 != 0) {
        throw std::invalid_argument("Team count must be even and > 2.");
    }

    freeDynamic();
    _teamCount = teamCount;
    _tournament = new Team[_teamCount];
    for (int i = 0; i < _teamCount; ++i)
        _tournament[i] = teams[i];
}

// Getters
const Team* BelotTournament::getTournament() const {
    return _tournament;
}

int BelotTournament::getTeamCount() const {
    return _teamCount;
}

double BelotTournament::getCharityMoney() const {
    return _charityMoney;
}

void BelotTournament::randomizeTeams() {
    std::srand(unsigned(std::time(nullptr)));
    std::random_shuffle(_tournament, _tournament + _teamCount);
}

void BelotTournament::startDuel(Team& t1, Team& t2) {
    int wins1 = 0, wins2 = 0;

    for (int round = 1; round <= Constants::MAX_ROUND_COUNT; ++round) {
        std::cout << "Round " << round << "!\n";
        int pointsT1 = 0;
        int pointsT2 = 0;
        int points;

        while (pointsT1 < 151 && pointsT2 < 151) {
            std::cout << "Team " << t1.getId() << " points: ";
            std::cin >> points;
            pointsT1 += points;
            std::cout << "Team " << t2.getId() << " points: ";
            std::cin >> points;
            pointsT2 += points;
        }

        if (pointsT1 > pointsT2)
        {
            wins1++;
        }
       
        else if (pointsT2 > pointsT1)
        {
            wins2++;
        }
        else 
        {
            std::cout << "Tie! Setting points to zero, teams will fight again.\n";
            pointsT1 = 0;
            pointsT2 = 0;
            round--;
        }
        

        if (wins1 == 2 || wins2 == 2)
            break;
    }

    Team& loser = (wins1 > wins2) ? t2 : t1;
    Team& winner = (wins1 > wins2) ? t1 : t2;

    int payment = 0;
    for (int i = 0; i < Constants::MIN_TEAM_SIZE; ++i) {
        int loserMoney = loser.getTeam()[i].getSalary() * 2 / 100;
        loser.getTeam()[i].setSalary(loser.getTeam()[i].getSalary() - loserMoney); 
        payment += loserMoney;
    }

    for (int i = 0; i < Constants::MIN_TEAM_SIZE; ++i) {
        int winnerMoney = payment / 2;
        winner.getTeam()[i].setSalary(winner.getTeam()[i].getSalary() + winnerMoney);
    }

    _charityMoney += payment;
    loser.setIsEliminated(true);
}

void BelotTournament::removeLosingTeams() {
    int newIndex = 0;
    for (int i = 0; i < _teamCount; ++i) {
        if (!_tournament[i].getIsEliminated()) {
            if (i != newIndex) {
                _tournament[newIndex] = std::move(_tournament[i]);
            }
            ++newIndex;
        }
    }
    _teamCount = newIndex;
}

void BelotTournament::startTournament() {
    if (_teamCount % 2 != 0) {
        std::cout << "Odd number of teams. Removing last team with ID "
            << _tournament[_teamCount - 1].getId() << "\n";
        _teamCount--;
    }
    while (_teamCount > 1) {
    
        randomizeTeams();

        for (int i = 0; i < _teamCount; i += 2) {
            std::cout << "Duel between team " << _tournament[i].getId()
                << " and team " << _tournament[i + 1].getId() << ":\n";

            startDuel(_tournament[i], _tournament[i + 1]);
            
        }      
        removeLosingTeams();
    }

    std::cout << "\nTournament Winner: Team " << _tournament[0].getId() << "!\n";
    std::cout << "Total Charity Collected: " << _charityMoney << "\n";
}
