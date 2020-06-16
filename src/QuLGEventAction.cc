#include "QuLGEventAction.hh"
#include "QuLGPMTHit.hh"
#include "QuLGTrajectory.hh"
#include "QuLGRun.hh"
#include "QuLGHistoManager.hh"
#include "QuLGDetectorConstruction.hh"
#include "QuLGPrimaryGeneratorMessenger.hh"

#include "G4EventManager.hh"
#include "G4SDManager.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4ios.hh"
#include "G4UImanager.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QuLGEventAction::QuLGEventAction(const QuLGDetectorConstruction* det)
  : fDetector(det),fPMTCollID(-1),fVerbose(0),
   fPMTThreshold(1),fForcedrawphotons(false)
{
  fEventMessenger = new QuLGEventMessenger(this);
  //fPrimaryGenerator = new QuLGPrimaryGeneratorMessenger(this);

  fHitCount = 0;
  fAbsorptionCount = 0;
  fBoundaryAbsorptionCount = 0;
  fTotE = 0.0;

  fConvPosSet = false;
  fEdepMax = 0.0;

  fPMTsAboveThreshold = 0;
}
 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QuLGEventAction::~QuLGEventAction(){}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QuLGEventAction::BeginOfEventAction(const G4Event*) {
 
  fHitCount = 0;
  fAbsorptionCount = 0;
  fBoundaryAbsorptionCount = 0;
  fTotE = 0.0;

  fConvPosSet = false;
  fEdepMax = 0.0;

  fPMTsAboveThreshold = 0;

  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  if(fPMTCollID<0)
    fPMTCollID=SDman->GetCollectionID("pmtHitCollection");
}
 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QuLGEventAction::EndOfEventAction(const G4Event* anEvent){

  G4TrajectoryContainer* trajectoryContainer=anEvent->GetTrajectoryContainer();
 
  G4int n_trajectories = 0;
  if (trajectoryContainer) n_trajectories = trajectoryContainer->entries();

  // extract the trajectories and draw them
  if (G4VVisManager::GetConcreteInstance()){
    for (G4int i=0; i<n_trajectories; i++){
      QuLGTrajectory* trj = (QuLGTrajectory*)
        ((*(anEvent->GetTrajectoryContainer()))[i]);
      if(trj->GetParticleName()=="opticalphoton"){
        trj->SetForceDrawTrajectory(fForcedrawphotons);
        trj->SetForceNoDrawTrajectory(fForcenophotons);
      }
      trj->DrawTrajectory();
    }
  }
 
  QuLGPMTHitsCollection* pmtHC = nullptr;
  G4HCofThisEvent* hitsCE = anEvent->GetHCofThisEvent();
 
  //Get the hit collections
  if(hitsCE){
    if(fPMTCollID>=0) {
      pmtHC = (QuLGPMTHitsCollection*)(hitsCE->GetHC(fPMTCollID));
    }
  }
 
  if(pmtHC){
    //G4ThreeVector reconPos(0.,0.,0.);
    G4int pmts=pmtHC->entries();
    //Gather info from hits in hit collection
    for(G4int i=0;i<pmts;i++){
      fHitCount += (*pmtHC)[i]->GetPhotonCount();
      // get hit position, local and global time
      if((*pmtHC)[i]->GetPhotonCount()>0){

        // G4AnalysisManager::Instance()->FillH2(1,((*pmtHC)[i]->GetPMTPos().getX())/10.,((*pmtHC)[i]->GetPMTPos().getY())/10.);
        std::vector<G4double> CurHit_Gt = (*pmtHC)[i]->GetGlobalTimes(); //current event global times
        std::vector<G4double> CurHit_Lt = (*pmtHC)[i]->GetLocalTimes(); // current event local times
        std::vector<G4double> CurHit_Ct = (*pmtHC)[i]->GetCombinedTimes(); // current event combined times
        for(int j=0;j<CurHit_Gt.size();j++){
          G4AnalysisManager::Instance()->FillH1(8, CurHit_Gt[j]);
          G4AnalysisManager::Instance()->FillH1(9, CurHit_Lt[j]);
          // G4AnalysisManager::Instance()->FillH1(10, CurHit_Gt[i]);
          G4AnalysisManager::Instance()->FillH1(11, CurHit_Ct[j]);
        }
        // G4AnalysisManager::Instance()->FillH1(8, (*pmtHC)[i]->GetLocalTime());
        // G4AnalysisManager::Instance()->FillH1(9, (*pmtHC)[i]->GetGlobalTime());
        // G4AnalysisManager::Instance()->FillH1(10, (*pmtHC)[i]->GetDT());
        // G4AnalysisManager::Instance()->FillH1(11, (*pmtHC)[i]->GetCombinedTime());
      }
      //reconPos+=(*pmtHC)[i]->GetPMTPos()*(*pmtHC)[i]->GetPhotonCount();
      if((*pmtHC)[i]->GetPhotonCount()>=fPMTThreshold){
        fPMTsAboveThreshold++;
      }
      else{//wasnt above the threshold, turn it back off
        (*pmtHC)[i]->SetDrawit(false);
      }
    }

    G4AnalysisManager::Instance()->FillH1(1, fHitCount);
    G4AnalysisManager::Instance()->FillH1(2, fPMTsAboveThreshold);

    if(fHitCount>0){
      G4AnalysisManager::Instance()->FillH2(0,fDetector->GetGunPosX()/10.,fDetector->GetGunPosY()/10.);

    }
    pmtHC->DrawAllHits();
  }

  G4AnalysisManager::Instance()->FillH1(5, fAbsorptionCount);
  G4AnalysisManager::Instance()->FillH1(6, fBoundaryAbsorptionCount);

  //if(fVerbose>0){
    //End of event output. later to be controlled by a verbose level
    G4cout << "\tNumber of photons that hit PMTs in this event : "
           << fHitCount << G4endl;
    G4cout << "\tNumber of PMTs above threshold("<<fPMTThreshold<<") : "
           << fPMTsAboveThreshold << G4endl;
    G4cout << "\tNumber of photons absorbed (OpAbsorption) in this event : "
           << fAbsorptionCount << G4endl;
    G4cout << "\tNumber of photons absorbed at boundaries (OpBoundary) in "
           << "this event : " << fBoundaryAbsorptionCount << G4endl;
    G4cout << "Unaccounted for photons in this event : "
           << (fPhotonCount_Scint + fPhotonCount_Ceren -
                fAbsorptionCount - fHitCount - fBoundaryAbsorptionCount)
           << G4endl;
  //}

  // update the run statistics
  QuLGRun* run = static_cast<QuLGRun*>(
    G4RunManager::GetRunManager()->GetNonConstCurrentRun());

  run->IncHitCount(fHitCount);
  run->IncEDep(fTotE);
  run->IncAbsorption(fAbsorptionCount);
  run->IncBoundaryAbsorption(fBoundaryAbsorptionCount);
  run->IncHitsAboveThreshold(fPMTsAboveThreshold);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......