#include "MyPrimaryGeneratorAction.hh"
#include "G4Event.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "Randomize.hh"


MyPrimaryGeneratorAction::MyPrimaryGeneratorAction()
{
  G4int n_particle = 1;
  particleGun  = new G4ParticleGun(n_particle);
  
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName="proton");
  
  particleGun->SetParticleDefinition(particle);
  particleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));  
  particleGun->SetParticleEnergy(100.*GeV);
  particleGun->SetParticlePosition(G4ThreeVector(0.,0.,-10.*cm));
}

MyPrimaryGeneratorAction::~MyPrimaryGeneratorAction()
{
  delete particleGun;
}

void MyPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
/**
  // Określenie rozmiarów detektora
  G4double detWidth = 7.9*cm;  // Szerokość detektora
  G4double detHeight = 4.9*cm; // Wysokość detektora

  // Losowanie pozycji na powierzchni detektora
  G4double x = (G4UniformRand() - 0.5) * detWidth;   // Równomierny rozkład wzdłuż osi x
  G4double y = (G4UniformRand() - 0.5) * detHeight;  // Równomierny rozkład wzdłuż osi y
  
  // Ustawienie losowej pozycji dla każdego generowanego protona
  particleGun->SetParticlePosition(G4ThreeVector(x, y, -10.*cm)); 
**/
  // Generowanie protona
  particleGun->GeneratePrimaryVertex(anEvent);
}

