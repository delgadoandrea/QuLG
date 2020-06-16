#include "QuLGSteppingMessenger.hh"
#include "QuLGSteppingAction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithABool.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QuLGSteppingMessenger::QuLGSteppingMessenger(QuLGSteppingAction* step)
 : fStepping(step)
{
  fOneStepPrimariesCmd = new G4UIcmdWithABool("/QuLG/oneStepPrimaries",this);
  fOneStepPrimariesCmd->
      SetGuidance("Only allows primaries to go one step before being killed.");

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QuLGSteppingMessenger::~QuLGSteppingMessenger(){
  delete fOneStepPrimariesCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void 
QuLGSteppingMessenger::SetNewValue(G4UIcommand* command,G4String newValue){
  if( command == fOneStepPrimariesCmd ){
    fStepping->SetOneStepPrimaries(fOneStepPrimariesCmd
                                  ->GetNewBoolValue(newValue));
  }
}