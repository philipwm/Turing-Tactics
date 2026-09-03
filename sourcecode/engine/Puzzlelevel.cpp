#include "Puzzlelevel.h"

PuzzleLevel::PuzzleLevel(): maxSteps(0){}

PuzzleLevel::PuzzleLevel(
    const std::string& name,
    const std::string& description,
    const std::vector<Bandsymbol>& input,
    const std::vector<Bandsymbol>& expectedOutput,
    int maxSteps
)
    : name(name),
      description(description),
      input(input),
      expectedOutput(expectedOutput),
      maxSteps(maxSteps){}

const std::string& PuzzleLevel::getName() const{
    return name;
}

const std::string& PuzzleLevel::getDescription() const{
    return description;
}

const std::vector<Bandsymbol>& PuzzleLevel::getInput() const{
    return input;
}

const std::vector<Bandsymbol>& PuzzleLevel::getExpectedOutput() const{
    return expectedOutput;
}

int PuzzleLevel::getMaxSteps() const{
    return maxSteps;
}

bool PuzzleLevel::checkSolution(const TuringMachine& machine) const{
    //left empty for now because not the whole tape accessible at once yet!
    return false;
}
