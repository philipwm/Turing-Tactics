#ifndef PUZZLELEVEL_H
#define PUZZLELEVEL_H

#include "Symbol.h"
#include "TuringMachine.h"

#include <vector>
#include <string>

class PuzzleLevel{
private:
    std::string name;
    std::string description;

    std::vector<Bandsymbol> input;
    std::vector<Bandsymbol> expectedOutput;

    int maxSteps;

public:
    PuzzleLevel();

    PuzzleLevel(
        const std::string& name,
        const std::string& description,
        const std::vector<Bandsymbol>& input,
        const std::vector<Bandsymbol>& expectedOutput,
        int maxSteps
    );

    const std::string& getName() const;
    const std::string& getDescription() const;

    const std::vector<Bandsymbol>& getInput() const;
    const std::vector<Bandsymbol>& getExpectedOutput() const;

    int getMaxSteps() const;

    bool checkSolution(const TuringMachine& machine) const;
};

#endif//PUZZLELEVEL_H