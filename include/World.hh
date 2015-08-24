#ifndef WORLD_H
#define WORLD_H

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4Box.hh"



class World : public G4VUserDetectorConstruction
{
    public:
        World();
        ~World();
        
        G4VPhysicalVolume* Construct();
        void ConstructSDandField();
        
    private:
        G4Box* worldBox;
        G4LogicalVolume* worldLog;
        G4VPhysicalVolume* worldPhys;
        
        G4Box* targetBox;
        G4LogicalVolume* targetLog;
        G4VPhysicalVolume* targetPhys;
                
        G4Material* vac;
        G4Material* tungsten;
};
#endif
