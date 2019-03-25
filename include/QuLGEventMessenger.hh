#ifndef QuLGEventMessenger_h
#define QuLGEventMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class QuLGPrimaryGeneratorMessenger;
class QuLGEventAction;
class G4UIcmdWithAnInteger;
class G4UIcmdWithABool;

class QuLGEventMessenger: public G4UImessenger
{
  public:

    QuLGEventMessenger(QuLGEventAction*);
    virtual ~QuLGEventMessenger();
 
    virtual void SetNewValue(G4UIcommand*, G4String);
 
  private:

    QuLGEventAction*      fQuLGEvent;
    QuLGPrimaryGeneratorMessenger* fPrimaryGenerator; 
    G4UIcmdWithAnInteger*  fVerboseCmd;
    G4UIcmdWithAnInteger*  fPmtThresholdCmd;
    G4UIcmdWithABool*      fForceDrawPhotonsCmd;
    G4UIcmdWithABool*      fForceDrawNoPhotonsCmd;
};

#endif