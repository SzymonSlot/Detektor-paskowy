#include "MyRun.hh"
#include "G4Event.hh"
#include "globals.hh"
#include "G4TrajectoryContainer.hh"
#include "G4VTrajectory.hh"
#include <iomanip>
#include "G4SDManager.hh"
#include "G4THitsMap.hh"
#include "G4THitsCollection.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "MyProtonHit.hh"
#include "MyAnalysis.hh"
#include <set>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <cmath>
#include "Randomize.hh"

MyRun::MyRun()
{
    G4SDManager* manager = G4SDManager::GetSDMpointer();
    fMapId = manager->GetCollectionID("MyDetector/MyScorer");
    G4cout << "MyLog: MyRun constructor: index of photon scorer map: " << fMapId << G4endl;
    
	fCollectionId =  manager->GetCollectionID("Proton/ProtonCollection");
	G4cout << "MyLog:  MyRun constructor: index of proton collection : " << fCollectionId << G4endl;
}

MyRun::~MyRun()
{}

void MyRun::RecordEvent(const G4Event* evt)
{
    numberOfEvent++;

    G4HCofThisEvent* hce = evt->GetHCofThisEvent();
    if (!hce) {
        G4cerr << "Error: HCofThisEvent is null." << G4endl;
        return;
    }

    G4THitsMap<double>* hitsMap = (G4THitsMap<double>*)(hce->GetHC(fMapId));
    if (!hitsMap) {
        G4cerr << "Error: HitsMap is null." << G4endl;
        return;
    }

    frunHitsMap += *hitsMap;
    
    
	G4THitsCollection<MyProtonHit>* protonCollection =
		dynamic_cast<G4THitsCollection<MyProtonHit>*> (hce->GetHC(fCollectionId));
		
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	
	//G4int multiplicity = protonCollection->entries();
    
    
    //std::set<int> uniqueStrip;
    //float esum = 0;
    std::map<int, float> energySums;
    std::map<int, float> enrgyofpart;
    
	  for( G4int i = 0; i< protonCollection->entries(); i++) {
		 float e = (*protonCollection)[i]->GetEnergy()/MeV;
		 //e = std::abs(e+CLHEP::RandGauss::shoot(0, std::sqrt(e)))
		 float x = (*protonCollection)[i]->GetPosition().x()/cm;
		 float y = (*protonCollection)[i]->GetPosition().y()/cm;
		 float z = (*protonCollection)[i]->GetPosition().z()/cm;
		 int strip = (*protonCollection)[i]->GetStrip();
		 int track = (*protonCollection)[i]->GetTrackID();
		 
		 //uniqueStrip.insert(strip);
		 //if(e>0.5e+3) energySums[strip] += e;
		 if(e>2){
			 energySums[strip] += e;
			 enrgyofpart[track] += e;
		}
		
		 analysisManager->FillNtupleDColumn(0,e);
		 analysisManager->FillNtupleDColumn(1,x);
		 analysisManager->FillNtupleDColumn(2,y);
		 analysisManager->FillNtupleDColumn(3,z);
		 analysisManager->FillNtupleDColumn(4,strip);
		 analysisManager->AddNtupleRow();	
	 }
	 
	 analysisManager->FillH1(0, enrgyofpart.size());
	 
	 analysisManager->FillH1(1, energySums.size());
	 
	 for(const auto& [track, energy]: enrgyofpart){
		 analysisManager->FillH1(10, energy);
	}
	 
    std::vector<std::pair<int, float>> stripEnergyVec;
	for (const auto& [strip, energy] : energySums) {
		stripEnergyVec.emplace_back(strip, energy);
	}


	std::sort(stripEnergyVec.begin(), stripEnergyVec.end(),
			  [](const std::pair<int, float>& a, const std::pair<int, float>& b) {
				  return a.first < b.first; 
     });

 
    // std::vector<int> countstripinclaster;
	int countstrip = 1;  
	int countclasters = 1;
	float clusterEnergySum = 0;

	
	if (!stripEnergyVec.empty()) {
		if (stripEnergyVec.size() > 1) {
			for (size_t i = 0; i < stripEnergyVec.size() - 1; i++) {
				clusterEnergySum += stripEnergyVec[i].second;
				if (stripEnergyVec[i].first == stripEnergyVec[i + 1].first - 1) {
					countstrip++;
				} else {
					countclasters++;
					analysisManager->FillH1(2, countstrip);      
					analysisManager->FillH1(4, clusterEnergySum); 
					if(countstrip<6) analysisManager->FillH1(4+countstrip, clusterEnergySum);
					countstrip = 1;
					clusterEnergySum = 0; 
				}
			}
			clusterEnergySum += stripEnergyVec.back().second;
			analysisManager->FillH1(2, countstrip);
			analysisManager->FillH1(4, clusterEnergySum);
			if(countstrip<6) analysisManager->FillH1(4+countstrip, clusterEnergySum);
		} 
		else {
			clusterEnergySum += stripEnergyVec[0].second;
			countstrip = 1;
			analysisManager->FillH1(2, countstrip);
			analysisManager->FillH1(4, clusterEnergySum);
			analysisManager->FillH1(5, clusterEnergySum);
		}
	} 
	else {
		// std::cerr << "Warning: stripEnergyVec is empty!" << std::endl;
		clusterEnergySum = 0;
	}
	
	if(countstrip==2 && countclasters==1) analysisManager->FillH1(11, enrgyofpart.size());

	analysisManager->FillH1(3, countclasters);

}
