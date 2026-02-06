#include "MyDetectorConstruction.hh"
#include "G4Box.hh"
#include "G4Colour.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4PVParameterised.hh"
#include "G4PVPlacement.hh"
#include "G4RunManager.hh"
#include "G4Tubs.hh"
#include "G4VisAttributes.hh"
#include "G4NistManager.hh"
#include "G4Sphere.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4SDManager.hh"
#include "G4PSSphereSurfaceCurrent.hh"
#include "G4ScoringBox.hh"
#include "G4PSEnergyDeposit.hh"
#include "MyProtonSD.hh"

MyDetectorConstruction::MyDetectorConstruction()
  :fpWorldLogical(0)
  ,fpWorldPhysical(0)
{}

MyDetectorConstruction::~MyDetectorConstruction() {}

G4VPhysicalVolume* MyDetectorConstruction::Construct()
{
  // Material Definition
  DefineMaterials();  

  // Geometry Definition
  SetupGeometry();   

  // Return world volume
  return fpWorldPhysical;  
}

void MyDetectorConstruction::DefineMaterials()
{
	G4String symbol;             
  G4double a, z, density;     
  G4int ncomponents;
  G4double fractionmass; 
  G4NistManager* nist = G4NistManager::Instance();
  
	new G4Material("Silicon",   z=14., a=28.0855*g/mole,  density=2.330*g/cm3);	
	
	// Define air
	  G4Material* air = nist->FindOrBuildMaterial("G4_AIR");
	
	// Define vacuum
	  G4Material* vacuum = new G4Material("Vacuum", density= 1.e-5*g/cm3, 
						  ncomponents=1, kStateGas, STP_Temperature, 
						  2.e-2*bar);
						  
	  
	  vacuum->AddMaterial(air, fractionmass=1.);
}

void MyDetectorConstruction::SetupGeometry()
{
  G4NistManager* nist = G4NistManager::Instance();
  G4Material* stainlesssteel = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");
  G4Material* vacuum = G4Material::GetMaterial("Vacuum");
  
  // World volume
  G4Box* worldSolid = new G4Box("World_Solid", 2.0*m, 2.0*m, 2.0*m); 
  fpWorldLogical = new G4LogicalVolume(worldSolid, vacuum, "World_Logical");
  fpWorldPhysical = new G4PVPlacement(0, G4ThreeVector(), fpWorldLogical, "World_Physical", nullptr, false, 0);

  // Steel window definition
  G4Box* OkienkoStalowe = new G4Box("Okienko_Stalowe", 8.*cm/2, 5.*cm/2, 300*um/2);
  G4LogicalVolume* logicOkienka = new G4LogicalVolume(OkienkoStalowe, stainlesssteel, "LogiczneOkienko");
  
  new G4PVPlacement(0, G4ThreeVector(0.,0.,-2.0*cm), logicOkienka, "Stal_Okienko_Physical", fpWorldLogical, false, 0);

  // Detector material
  G4Material* Si = G4Material::GetMaterial("Silicon");

  // Detector parameters
  G4double detWidth = 7.9 * cm;    
  G4double detHeight = 4.9 * cm;   
  G4double detThickness = 400.0 * um;
  G4int nStrips = 756; 
  G4double stripWidth = detWidth / nStrips; 

  // Detector volume
  G4VSolid* detectorSolid = new G4Box("Detector_Solid", detWidth / 2, detHeight / 2, detThickness / 2);
  G4LogicalVolume* detectorLogical = new G4LogicalVolume(detectorSolid, Si, "Detector_Logical");
  
  new G4PVPlacement(0, G4ThreeVector(), detectorLogical, "Detector_Physical", fpWorldLogical, false, 0);
  
  // Strip definition
  G4VSolid* scoreSolid = new G4Box("Score_Solid", stripWidth / 2, detHeight / 2, detThickness / 2);
  G4LogicalVolume* scoreLogical = new G4LogicalVolume(scoreSolid, Si, "Strip_Logical");

	SetupScoring(scoreLogical); 
  // Replication of strips along X-axis
  new G4PVReplica("Strip_Physical", scoreLogical, detectorLogical, kXAxis, nStrips, stripWidth);



  // Visual attributes
  fpWorldLogical->SetVisAttributes(G4VisAttributes::GetInvisible());

  G4VisAttributes* OkienkoStaloweAttributes = new G4VisAttributes(G4Colour(0.5, 0.5, 0.5, 1.0));
  OkienkoStaloweAttributes->SetForceSolid(true);
  logicOkienka->SetVisAttributes(OkienkoStaloweAttributes);

  G4VisAttributes* PasekKrzemowyAttributes = new G4VisAttributes(G4Colour::Magenta());
  PasekKrzemowyAttributes->SetForceWireframe(true);
  scoreLogical->SetVisAttributes(PasekKrzemowyAttributes);

  detectorLogical->SetVisAttributes(G4VisAttributes::GetInvisible());
}

void MyDetectorConstruction::SetupScoring(G4LogicalVolume* scoringVolume)
{  
    // Create a new sensitive detector named "MyDetector"
    G4MultiFunctionalDetector* detector =
        new G4MultiFunctionalDetector("MyDetector");

    // Get pointer to detector manager
    G4SDManager* manager = G4SDManager::GetSDMpointer();  

    // Register detector with manager
    manager->AddNewDetector(detector);

    // Attach detector to scoring volume
    // scoringVolume->SetSensitiveDetector(detector);
    
    MyProtonSD* protonSD = new MyProtonSD("Proton");
    manager->AddNewDetector(protonSD);
    scoringVolume->SetSensitiveDetector(protonSD);

    // Create a primitive Scorer for energy deposit
    G4PSEnergyDeposit* scorer =
        new G4PSEnergyDeposit("MyScorer");

    // Register scorer with detector
    detector->RegisterPrimitive(scorer);
}

	
