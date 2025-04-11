#pragma once
#include "serializer.h"

static const std::vector<Team> DefaultTeams {
    Team(
        L"Global Stars", 
        std::vector<Player>{
            Player(L"John Smith", Nationality::US, 15),
            Player(L"Marco Rossi", Nationality::IT, 12),
            Player(L"David Kim", Nationality::KR, 8),
            Player(L"Carlos Vega", Nationality::ES, 10),
            Player(L"Alex Johnson", Nationality::GB, 7)
        }, 42
    ),
    
    Team(
        L"European United",
        std::vector<Player>{
            Player(L"Maria Santos", Nationality::BR, 18),
            Player(L"Pierre Dubois", Nationality::FR, 14),
            Player(L"Hans Mueller", Nationality::DE, 9),
            Player(L"Yuki Tanaka", Nationality::JP, 11),
            Player(L"Andrei Popescu", Nationality::RO, 13)
        }, 38
    ),
    
    Team(
        L"World Champions",
        std::vector<Player>{
            Player(L"Li Wei", Nationality::CN, 7),
            Player(L"Anna Kowalski", Nationality::PL, 16),
            Player(L"Miguel Rodriguez", Nationality::MX, 20),
            Player(L"Eva Johansson", Nationality::SE, 15),
            Player(L"Ahmed Hassan", Nationality::EG, 12)
        }, 35
    ),
    
    Team(
        L"International All-Stars",
        std::vector<Player>{
            Player(L"Robert Clark", Nationality::AU, 9),
            Player(L"Sofia Ricci", Nationality::IT, 11),
            Player(L"Jan de Vries", Nationality::NL, 14),
            Player(L"Elena Ivanova", Nationality::RU, 8),
            Player(L"Jake Wilson", Nationality::CA, 13)
        }, 29
    )
};

class Engine {
    const Serializer serializer;

    std::vector<Team> teams;
public:
    Engine(const std::string&);

    void ShowPlayers(const Team&) const;
    void ShowTop() const;
    void EliminateLessThan(Team&, const u32);
    Nationality GetCountryWithMostPlayers() const;
};