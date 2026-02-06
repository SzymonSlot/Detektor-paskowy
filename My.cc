#include "MyDetectorConstruction.hh"
#include "MyPhysicsList.hh"
#include "MyPrimaryGeneratorAction.hh"
#include "G4RunManager.hh"
#include "G4String.hh"
#include "G4UImanager.hh"
#include "MyRunAction.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
#include "FTFP_BERT.hh"



int main(int argc,char** argv) {
  
  // Run manager
  G4RunManager * runManager = new G4RunManager;
  
  // Mandatory initialization classes
  runManager->SetUserInitialization(new MyDetectorConstruction);
  //runManager->SetUserInitialization(new MyPhysicsList);
  G4VModularPhysicsList* physicsList = new FTFP_BERT;
  runManager->SetUserInitialization(physicsList);
    
  // User action classes
  runManager->SetUserAction(new MyPrimaryGeneratorAction());
  runManager->SetUserAction(new MyRunAction());
  
  // Initialize G4 kernel
  runManager->Initialize();
    
  // Start a run

// Get the pointer to the User Interface manager
  G4UImanager* UI = G4UImanager::GetUIpointer(); 


//  G4int numberOfEvents=2;
//  runManager->BeamOn(numberOfEvents);
 

   if ( argc == 1) {

 // Visualization manager
   G4VisManager* visManager = new G4VisExecutive;
   visManager->Initialize();

    G4UIExecutive * ui = new G4UIExecutive(argc,argv);     
    ui->SessionStart();
    delete ui; 

    delete visManager;
       }
  else {
// Execute macro argv[1] from c++ code
    G4String macro = argv[1];
    UI->ApplyCommand("/control/execute "+macro);
 }
  // Job termination
  delete runManager;
  
  return 0;
}

