#ifndef MYPROTONHIT_HH
#define MYPROTONHIT_HH

#include "G4VHit.hh"
#include "G4ThreeVector.hh"

class MyProtonHit : public G4VHit {

public:

  // Constructor
  MyProtonHit();

  // Destructor
  virtual ~MyProtonHit();

  // Methods 
  // void Draw()
  // void Print()

  // Proton energy
  inline void SetEnergy(G4double energy) {fEnergy = energy;}
  inline G4double GetEnergy() const {return fEnergy;}

  // Proton position
  inline void SetPosition(G4ThreeVector position) {fPosition = position;}
  inline G4ThreeVector GetPosition() const {return fPosition;}
  
  // Strip Number
  inline void SetStrip(G4int strip) {fStrip = strip;}
  inline G4int GetStrip() const {return fStrip;}
  
  inline void SetTrackID(G4int track) {fTrackID = track;}
  inline G4int GetTrackID() const {return fTrackID;}

private:
  //Data Members
 G4double fEnergy;
 G4ThreeVector fPosition;
 G4int fStrip;
 G4int fTrackID;
};

#endif

