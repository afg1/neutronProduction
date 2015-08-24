
#ifndef INITIALIZATION_H
#define INITIALIZATION_H 1

#include "G4VUserActionInitialization.hh"

#include "G4VProcess.hh"

class Initialization : public G4VUserActionInitialization
{
    public:
        Initialization();
        ~Initialization();
        void Build() const;
        void BuildForMaster() const;
};

#endif
