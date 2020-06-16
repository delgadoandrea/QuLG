#ifndef QuLGSteppingMessenger_h
#define QuLGSteppingMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class QuLGSteppingAction;
class G4UIcmdWithABool;

class QuLGSteppingMessenger: public G4UImessenger
{
  public:
    QuLGSteppingMessenger(QuLGSteppingAction*);
    virtual ~QuLGSteppingMessenger();
 
    virtual void SetNewValue(G4UIcommand*, G4String);

  private:

    QuLGSteppingAction*        fStepping;
    G4UIcmdWithABool*  fOneStepPrimariesCmd;
 
};

#endif