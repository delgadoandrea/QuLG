#include "QuLGActionInitialization.hh"

#include "QuLGPrimaryGeneratorAction.hh"
#include "QuLGDetectorConstruction.hh"

#include "QuLGRunAction.hh"
#include "QuLGEventAction.hh"
#include "QuLGTrackingAction.hh"
#include "QuLGSteppingAction.hh"
#include "QuLGStackingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QuLGActionInitialization::QuLGActionInitialization(
   QuLGDetectorConstruction* det)
  : G4VUserActionInitialization(), fDetector(det)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QuLGActionInitialization::~QuLGActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QuLGActionInitialization::BuildForMaster() const
{
  SetUserAction(new QuLGRunAction());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QuLGActionInitialization::Build() const
{
  QuLGPrimaryGeneratorAction *prim = new QuLGPrimaryGeneratorAction(fDetector);
  SetUserAction(prim);

  QuLGEventAction* eventAction = new QuLGEventAction(fDetector);
  SetUserAction(eventAction);
  SetUserAction(new QuLGStackingAction(eventAction));

  SetUserAction(new QuLGRunAction());
  SetUserAction(new QuLGTrackingAction());
  SetUserAction(new QuLGSteppingAction(eventAction));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......