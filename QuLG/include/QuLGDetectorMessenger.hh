#ifndef QuLGDetectorMessenger_h
#define QuLGDetectorMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class QuLGDetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWithAnInteger;
class G4UIcommand;
class G4UIcmdWithABool;
class G4UIcmdWithADouble;

class QuLGDetectorMessenger: public G4UImessenger
{
  public:

    QuLGDetectorMessenger(QuLGDetectorConstruction*);
    virtual ~QuLGDetectorMessenger();
 
    virtual void SetNewValue(G4UIcommand*, G4String);
 
  private:

    QuLGDetectorConstruction*     fDetector;
    G4UIdirectory*               fDetectorDir;
    G4UIdirectory*               fVolumesDir;
    G4UIcmdWith3VectorAndUnit*   fDimensionsCmd;
    G4UIcmdWithADoubleAndUnit*          fGunPosXCmd;
    G4UIcmdWithADoubleAndUnit*          fGunPosYCmd;
    G4UIcmdWithADoubleAndUnit*          fGunPosZCmd;

};

#endif
