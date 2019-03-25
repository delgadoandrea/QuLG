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
 : fQuLGDetector(detector)
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
  fDimensionsCmd->SetParameterName("scint_x","scint_y","scint_z",false);
  fDimensionsCmd->SetDefaultUnit("cm");
  fDimensionsCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fDimensionsCmd->SetToBeBroadcasted(false);

  fHousingThicknessCmd = new G4UIcmdWithADoubleAndUnit
    ("/QuLG/detector/housingThickness",this);
  fHousingThicknessCmd->SetGuidance("Set the thickness of the housing.");
  fHousingThicknessCmd->SetParameterName("d_mtl",false);
  fHousingThicknessCmd->SetDefaultUnit("cm");
  fHousingThicknessCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fHousingThicknessCmd->SetToBeBroadcasted(false);

  fPmtRadiusCmd = new G4UIcmdWithADoubleAndUnit
    ("/QuLG/detector/pmtRadius",this);
  fPmtRadiusCmd->SetGuidance("Set the radius of the PMTs.");
  fPmtRadiusCmd->SetParameterName("radius",false);
  fPmtRadiusCmd->SetDefaultUnit("cm");
  fPmtRadiusCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fPmtRadiusCmd->SetToBeBroadcasted(false);

  fNxCmd = new G4UIcmdWithAnInteger("/QuLG/detector/nx",this);
  fNxCmd->SetGuidance("Set the number of PMTs along the x-dimension.");
  fNxCmd->SetParameterName("nx",false);
  fNxCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fNxCmd->SetToBeBroadcasted(false);

  fNyCmd = new G4UIcmdWithAnInteger("/QuLG/detector/ny",this);
  fNyCmd->SetGuidance("Set the number of PMTs along the y-dimension.");
  fNyCmd->SetParameterName("ny",false);
  fNyCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fNyCmd->SetToBeBroadcasted(false);

  fNzCmd = new G4UIcmdWithAnInteger("/QuLG/detector/nz",this);
  fNzCmd->SetGuidance("Set the number of PMTs along the z-dimension.");
  fNzCmd->SetParameterName("nz",false);
  fNzCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fNzCmd->SetToBeBroadcasted(false);

  fSphereCmd = new G4UIcmdWithABool("/QuLG/detector/volumes/sphere",this);
  fSphereCmd->SetGuidance("Enable/Disable the sphere.");
  fSphereCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fSphereCmd->SetToBeBroadcasted(false);

  fReflectivityCmd = new G4UIcmdWithADouble("/QuLG/detector/reflectivity",this);
  fReflectivityCmd->SetGuidance("Set the reflectivity of the housing.");
  fReflectivityCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fReflectivityCmd->SetToBeBroadcasted(false);

  fWlsCmd = new G4UIcmdWithABool("/QuLG/detector/volumes/wls",this);
  fWlsCmd->SetGuidance("Enable/Disable the WLS slab");
  fWlsCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fWlsCmd->SetToBeBroadcasted(false);

  fQuLGCmd = new G4UIcmdWithABool("/QuLG/detector/volumes/QuLG",this);
  fQuLGCmd->SetGuidance("Enable/Disable the main detector volume.");
  fQuLGCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fQuLGCmd->SetToBeBroadcasted(false);

  fNFibersCmd = new G4UIcmdWithAnInteger("/QuLG/detector/nfibers",this);
  fNFibersCmd->SetGuidance("Set the number of WLS fibers in the WLS slab.");
  fNFibersCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fNFibersCmd->SetToBeBroadcasted(false);

  fMainScintYield=new G4UIcmdWithADouble("/QuLG/detector/MainScintYield",this);
  fMainScintYield->SetGuidance("Set scinitillation yield of main volume.");
  fMainScintYield->SetGuidance("Specified in photons/MeV");
  fMainScintYield->AvailableForStates(G4State_PreInit,G4State_Idle);
  fMainScintYield->SetToBeBroadcasted(false);

  fWLSScintYield = new G4UIcmdWithADouble("/QuLG/detector/WLSScintYield",this);
  fWLSScintYield->SetGuidance("Set scintillation yield of WLS Slab");
  fWLSScintYield->SetGuidance("Specified in photons/MeV");
  fWLSScintYield->AvailableForStates(G4State_PreInit,G4State_Idle);
  fWLSScintYield->SetToBeBroadcasted(false);

  fSaveThresholdCmd = new G4UIcmdWithAnInteger("/QuLG/saveThreshold",this);
  fSaveThresholdCmd->
SetGuidance("Set the photon count threshold for saving the random number seed");
  fSaveThresholdCmd->SetParameterName("photons",true);
  fSaveThresholdCmd->SetDefaultValue(4500);
  fSaveThresholdCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fDefaultsCmd = new G4UIcommand("/QuLG/detector/defaults",this);
  fDefaultsCmd->SetGuidance("Set all detector geometry values to defaults.");
  fDefaultsCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fDefaultsCmd->SetToBeBroadcasted(false);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QuLGDetectorMessenger::~QuLGDetectorMessenger()
{
  delete fDimensionsCmd;
  delete fHousingThicknessCmd;
  delete fPmtRadiusCmd;
  delete fNxCmd;
  delete fNyCmd;
  delete fNzCmd;
  delete fDetectorDir;
  delete fVolumesDir;
  delete fSphereCmd;
  delete fWlsCmd;
  delete fQuLGCmd;
  delete fNFibersCmd;
  delete fReflectivityCmd;
  delete fMainScintYield;
  delete fWLSScintYield;
  delete fSaveThresholdCmd;
  delete fDefaultsCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QuLGDetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  /*if( command == fDimensionsCmd ){
    fQuLGDetector->SetDimensions(fDimensionsCmd->GetNew3VectorValue(newValue));
  }
  else if (command == fHousingThicknessCmd){
    fQuLGDetector->SetHousingThickness(fHousingThicknessCmd
                                     ->GetNewDoubleValue(newValue));
  }
  else if (command == fPmtRadiusCmd){
    fQuLGDetector->SetPMTRadius(fPmtRadiusCmd->GetNewDoubleValue(newValue));
  }
  else if (command == fNxCmd){
    fQuLGDetector->SetNX(fNxCmd->GetNewIntValue(newValue));
  }
  else if (command == fNyCmd){
    fQuLGDetector->SetNY(fNyCmd->GetNewIntValue(newValue));
  }
  else if (command == fNzCmd){
    fQuLGDetector->SetNZ(fNzCmd->GetNewIntValue(newValue));
  }
  else if (command == fSphereCmd){
    fQuLGDetector->SetSphereOn(fSphereCmd->GetNewBoolValue(newValue));
  }
  else if (command == fReflectivityCmd){
    fQuLGDetector
      ->SetHousingReflectivity(fReflectivityCmd->GetNewDoubleValue(newValue));
  }
  else if (command == fWlsCmd){
    fQuLGDetector->SetWLSSlabOn(fWlsCmd->GetNewBoolValue(newValue));
  }
  else if (command == fQuLGCmd){
    fQuLGDetector->SetMainVolumeOn(fQuLGCmd->GetNewBoolValue(newValue));
  }
  else if (command == fNFibersCmd){
    fQuLGDetector->SetNFibers(fNFibersCmd->GetNewIntValue(newValue));
  }
  else if (command == fMainScintYield){
   fQuLGDetector->
              SetMainScintYield(fMainScintYield->GetNewDoubleValue(newValue));
  }
  else if (command == fWLSScintYield){
    fQuLGDetector->SetWLSScintYield(fWLSScintYield->GetNewDoubleValue(newValue));
  }
  else if( command == fSaveThresholdCmd ){
    fQuLGDetector->SetSaveThreshold(fSaveThresholdCmd->GetNewIntValue(newValue));
  }

  else if (command == fDefaultsCmd){
    fQuLGDetector->SetDefaults();
*/
    G4RunManager::GetRunManager()->ReinitializeGeometry(); //Add here this line
  //}
}