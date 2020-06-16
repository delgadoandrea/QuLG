#ifndef QuLGSteppingAction_H
#define QuLGSteppingACtion_H 1

#include "globals.hh"
#include "G4UserSteppingAction.hh"

#include "G4OpBoundaryProcess.hh"

class QuLGEventAction;
class QuLGTrackingAction;
class QuLGSteppingMessenger;

class QuLGSteppingAction : public G4UserSteppingAction
{
  public:

    QuLGSteppingAction(QuLGEventAction*);
    virtual ~QuLGSteppingAction();
    virtual void UserSteppingAction(const G4Step*);

    void SetOneStepPrimaries(G4bool b){fOneStepPrimaries=b;}
    G4bool GetOneStepPrimaries(){return fOneStepPrimaries;}
 
  private:

    G4bool fOneStepPrimaries;
    QuLGSteppingMessenger* fSteppingMessenger;
    QuLGEventAction*       fEventAction;

    G4OpBoundaryProcessStatus fExpectedNextStatus;
};

#endif