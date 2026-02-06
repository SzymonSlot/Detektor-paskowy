#include "MyProtonSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"

MyProtonSD::MyProtonSD(const G4String& name)
  :G4VSensitiveDetector(name)
{
  collectionName.insert("ProtonCollection");
  fProtonCollectionID = -1;
}

MyProtonSD::~MyProtonSD() {}

void MyProtonSD::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent)
{
 // Create a new collection
 fProtonCollection = new G4THitsCollection<MyProtonHit>(SensitiveDetectorName, collectionName[0]);
 if( fProtonCollectionID < 0) 
     fProtonCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(fProtonCollection);
 // Add collection to the events
 hitsCollectionOfThisEvent->AddHitsCollection(fProtonCollectionID, fProtonCollection); 
}

G4bool MyProtonSD::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{
 // Create a new hit
 MyProtonHit* aHit = new MyProtonHit();

 // Get energy and position
 G4double energy = aStep->GetTotalEnergyDeposit();
 G4ThreeVector position = aStep->GetTrack()->GetPosition();
 G4int stripNumber = aStep->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber();
 G4int trackID = aStep->GetTrack()->GetTrackID();

 // Set energy and position
 aHit->SetEnergy(energy);
 aHit->SetPosition(position);
 aHit->SetStrip(stripNumber);
 aHit->SetTrackID(trackID);

 // Insert hit into the collection
 fProtonCollection->insert(aHit); 
 return true;
}

void MyProtonSD::EndOfEvent(G4HCofThisEvent*) {}
