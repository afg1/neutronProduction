
#include "Physics.hh"

#include<iostream>
#include "G4EmDNAPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "G4EmProcessOptions.hh"
#include "G4EmPenelopePhysics.hh"
#include "G4RegionStore.hh"
//#include "G4HadronInelasticQLHEP.hh"
#include "G4HadronPhysicsQGSP_BIC.hh"
#include "G4DecayPhysics.hh"
#include "G4ProcessManager.hh"
#include "G4SystemOfUnits.hh"

Physics::Physics(): G4VUserPhysicsList()
{
    defaultCutValue = 0.25*mm;
    cutForGamma = defaultCutValue;
    cutForElectron = defaultCutValue;
    cutForPositron = defaultCutValue;
    cutForProton = defaultCutValue;


    emPhysicsList = new G4EmStandardPhysics_option3(0);
    hadrPhysicsList = new G4HadronPhysicsQGSP_BIC(0);
    decayPhysicsList = new G4DecayPhysics(0);
}

Physics::~Physics()
{
    delete emPhysicsList;
    delete hadrPhysicsList;
    delete decayPhysicsList;
    emPhysicsList = NULL;
    hadrPhysicsList = NULL;
    decayPhysicsList = NULL;
    
}

void Physics::ConstructParticle()
{
    emPhysicsList->ConstructParticle();
    hadrPhysicsList->ConstructParticle();
    decayPhysicsList->ConstructParticle();

}

void Physics::ConstructProcess()
{
    AddTransportation();
    emPhysicsList->ConstructProcess();
    hadrPhysicsList->ConstructProcess();
    decayPhysicsList->ConstructProcess();

}

void Physics::SetCuts()
{
    SetCutsWithDefault();
}

void Physics::SetCutsForRegion(G4double aCut, const G4String& rname)
{
    SetCutValue(aCut, "gamma", rname);
    SetCutValue(aCut, "e-", rname);
    SetCutValue(aCut, "e+", rname);
    SetCutValue(aCut, "proton", rname);
}
//
