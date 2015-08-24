
#include "G4MTRunManager.hh"
#include "G4RunManager.hh"
#include "G4MTRunManagerKernel.hh"
#include "G4UImanager.hh"


#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif


#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#include "G4UIsession.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#endif

#include "G4ScoringManager.hh"


#include "World.hh"
#include "Physics.hh"
#include "Generator.hh"
#include "Initialization.hh"


#include "G4RegionStore.hh"
#include "G4SystemOfUnits.hh"


// Include timing feature
#include <ctime>
#include <climits>
#include <fstream>


using namespace std;

int main(int argc, char** argv)
{
    G4UImanager* UI = G4UImanager::GetUIpointer();
    UI->StoreHistory(false);
	UI->SetThreadUseBuffer(false);
    
    #ifdef G4MULTITHREADED
    G4MTRunManager* runManager;
    runManager = new G4MTRunManager;
    runManager->SetVerboseLevel(0);
    #else 
    G4RunManager* runManager;
    runManager = new G4RunManager;
    runManager->SetVerboseLevel(0);
    #endif
    
    World* theWorld = new World();
    runManager->SetUserInitialization(theWorld);
    
    Physics* phys = new Physics();
    runManager->SetUserInitialization(phys);
    
    #ifdef G4MULTITHREADED
    Initialization* init = new Initialization();
    runManager->SetUserInitialization(init);
    #else
    G4VUserPrimaryGeneratorAction* gen = new Generator;
    runManager->SetUserAction(gen);
    #endif
    
    // Activate command based scorer
    G4ScoringManager::GetScoringManager();
    
    #ifdef G4UI_USE
    G4UIsession* ui = new G4UIterminal(new G4UItcsh);
    if(argc == 1)// This means we want to run in interactive mode
    {
        ui->SessionStart();
        return -2;
    }
    #endif
    
    #ifdef G4VIS_USE
    G4VisManager* visMan = new G4VisExecutive;
    visMan->Initialise();
    #endif

//    UI->ExecuteMacroFile(macname.c_str()); // Uncomment and implement if desired
   
	G4RegionStore* rs = G4RegionStore::GetInstance();
	rs->clear();
	rs->Clean();
    
    delete theWorld;// This is included because in sequential mode, it is needed to trigger output
    return 0;
}
