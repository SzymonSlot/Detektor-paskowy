#include "MyRunAction.hh"
#include "G4Run.hh"
#include "MyRun.hh"
#include "globals.hh"
#include "MyAnalysis.hh"

MyRunAction::MyRunAction() 
{}

MyRunAction::~MyRunAction() 
{}


void MyRunAction::BeginOfRunAction(const G4Run* aRun)
{
 G4cout << "MyLog:   Begin of run" << G4endl;
 
 // Create analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetVerboseLevel(1);
  // analysisManager->SetFirstHistoId(1);
 
// Open an output file
  //analysisManager->OpenFile("hist.root");

// Creating histograms
 //G4int idPhotonFlux = analysisManager->CreateH1("PhotonFlux","photon flow",15,0.,90.);
 
  //analysisManager->OpenFile("tree/tree_jedn.root");
  analysisManager->OpenFile("tree/tree_forward2.root");
  analysisManager->CreateH1("Multiplycity", "Mulitpycity", 10, -0.5, 9.5); // ile cząstek w jednym evencie
  analysisManager->CreateH1("StrimMulti", "Strip multiplycity", 10, -0.5, 9.5); // ile pasków aktywowanych w jednym evencie
  analysisManager->CreateH1("Clusterlength", "Cluster length", 10, -0.5, 9.5); // długosć klastrów (ile pasków w jednym klastrze) fig 3.3
  analysisManager->CreateH1("ClusterMulti", "Cluster multiplycity", 10, -0.5, 9.5); // ilość klastrów w evencie fig 3.1
  analysisManager->CreateH1("Clusterenergysum", "Cluster energy sum for every cluster",  100, 0, 50); // całkowita energia zdeponowana w klastrze 
  analysisManager->CreateH1("Clusterenergy1", "Cluster energy 1", 100, 0, 50); // całkowita energia zdeponowana w klastrze o krotności 1
  analysisManager->CreateH1("Clusterenergy2", "Cluster energy 2", 100, 0, 50); // całkowita energia zdeponowana w klastrze o krotności 2
  analysisManager->CreateH1("Clusterenergy3", "Cluster energy 3", 100, 0, 50); // całkowita energia zdeponowana w klastrze o krotności 3
  analysisManager->CreateH1("Clusterenergy4", "Cluster energy 4", 100, 0, 50); // całkowita energia zdeponowana w klastrze o krotności 4
  analysisManager->CreateH1("Clusterenergy5", "Cluster energy 5", 100, 0, 50); // całkowita energia zdeponowana w klastrze o krotności 5
  analysisManager->CreateH1("PartEner", "Detonete energy", 100, 0, 50); // energia zdeponowana przez pojedyńczą cząstkę
  analysisManager->CreateH1("Multiplycityiflen2", "Mulitpycity if len of cluster equal 2", 10, -0.5, 9.5); // ile cząstek w jednym evencie
  //analysisManager->CreateH1("Strip", "Strip", 800, 0, 800);
  
  analysisManager->SetFirstNtupleId(1);
  
  analysisManager->CreateNtuple("ProtonCollection","Kolekcja protonów");
  analysisManager->CreateNtupleDColumn("E");
  analysisManager->CreateNtupleDColumn("X");
  analysisManager->CreateNtupleDColumn("Y");
  analysisManager->CreateNtupleDColumn("Z");
  analysisManager->CreateNtupleDColumn("Strip");
  analysisManager->FinishNtuple();
}

void MyRunAction::EndOfRunAction(const G4Run* aRun)
{
	 
// Get analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

// Get histogram id not efficient in event loop
  // Save histograms and close file
  analysisManager->Write();
  analysisManager->CloseFile();
 G4cout <<"MyLog:   Number of processed events:" << aRun->GetNumberOfEvent()
               << " events. " <<G4endl;
 G4cout << "MyLog:   End of run" << G4endl;
}

G4Run* MyRunAction::GenerateRun()
{
 return new MyRun();
}
