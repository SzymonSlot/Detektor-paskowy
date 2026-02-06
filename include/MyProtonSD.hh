#ifndef MYPROTOND_HH
#define MYPROTONSD_HH

#include "G4VSensitiveDetector.hh"
#include "MyProtonHit.hh"
#include "G4THitsCollection.hh"

class G4HCofThisEvent;
class G4TouchableHistory;
class G4Step;

class MyProtonSD : public G4VSensitiveDetector {

public:

  // Constructor
  MyProtonSD(const G4String& name);

  // Destructor
  virtual ~MyProtonSD();
  
  // Methods
  void Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent);  
  G4bool ProcessHits(G4Step* aStep,G4TouchableHistory* history);
  void EndOfEvent(G4HCofThisEvent* hitsCollectionOfThisEvent);
  
private:
  
  // Data members
  G4THitsCollection<MyProtonHit>* fProtonCollection;
  G4int fProtonCollectionID;

};




#endif

