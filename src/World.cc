#include "World.hh"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"


World::World()
{}

World::~World()
{}

G4VPhysicalVolume* World::Construct()
{
    G4NistManager* matMan = G4NistManager::Instance();
    vac = matMan->FindOrBuildMaterial("G4_Galactic");
    tungsten = matMan->FindOrBuildMaterial("G4_W");

    G4double worldDim = 2000.0*mm;
    worldBox = new G4Box("worldBox", worldDim, worldDim, worldDim);
    worldLog = new G4LogicalVolume(worldBox, vac, "worldLog");
    worldPhys = new G4PVPlacement(0, G4ThreeVector(), worldLog, "worldPhys", 0, false, 0);
    
    G4double targetDim = 100.0*mm;
    targetBox = new G4Box("targetBox", targetDim, targetDim, targetDim);
    targetLog = new G4LogicalVolume(targetBox, tungsten, "targetLog");
    targetPhys = new G4PVPlacement(0, G4ThreeVector(), targetLog, "targetPhys", worldLog, false, 0);
    return worldPhys;
}

void World::ConstructSDandField()
{

}
