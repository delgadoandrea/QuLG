#include "QuLGDetectorMessenger.hh"
#include "QuLGDetectorConstruction.hh"

#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcommand.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4Scintillation.hh"

#include "G4RunManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QuLGDetectorMessenger::QuLGDetectorMessenger(QuLGDetectorConstruction* detector)
 : fDetector(detector)
{
  //Setup a command directory for detector controls with guidance
  fDetectorDir = new G4UIdirectory("/QuLG/detector/");
  fDetectorDir->SetGuidance("Detector geometry control");

  fVolumesDir = new G4UIdirectory("/QuLG/detector/volumes/");
  fVolumesDir->SetGuidance("Enable/disable volumes");
 
  //Various commands for modifying detector geometry
  fDimensionsCmd =
    new G4UIcmdWith3VectorAndUnit("/QuLG/detector/dimensions",this);
  fDimensionsCmd->SetGuidance("Set the dimensions of the detector volume.");
  fDimensionsCmd->SetDefaultUnit("cm");
  fDimensionsCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fDimensionsCmd->SetToBeBroadcasted(false);

  fGunPosXCmd = new G4UIcmdWithADoubleAndUnit("/QuLG/detector/gunPosX", this);
  fGunPosXCmd->SetDefaultUnit("cm");
  fGunPosXCmd->SetGuidance("Set particle gun x-position");
  fGunPosXCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fGunPosYCmd = new G4UIcmdWithADoubleAndUnit("/QuLG/detector/gunPosY", this);
  fGunPosYCmd->SetDefaultUnit("cm");  
  fGunPosYCmd->SetGuidance("Set particle gun y-position");
  fGunPosYCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QuLGDetectorMessenger::~QuLGDetectorMessenger()
{
  delete fDimensionsCmd;
  delete fGunPosXCmd;
  delete fGunPosYCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QuLGDetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  if( command == fGunPosXCmd){
    fDetector->SetGunPosX(fGunPosXCmd->GetNewDoubleValue(newValue));

  } 
  else if( command == fGunPosYCmd){
    fDetector->SetGunPosY(fGunPosYCmd->GetNewDoubleValue(newValue));

  } 
    //G4RunManager::GetRunManager()->ReinitializeGeometry(); //Add here this line
}