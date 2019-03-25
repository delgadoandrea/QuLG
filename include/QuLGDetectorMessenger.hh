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

    QuLGDetectorConstruction*     fQuLGDetector;
    G4UIdirectory*               fDetectorDir;
    G4UIdirectory*               fVolumesDir;
    G4UIcmdWith3VectorAndUnit*   fDimensionsCmd;
    G4UIcmdWithADoubleAndUnit*   fHousingThicknessCmd;
    G4UIcmdWithADoubleAndUnit*   fPmtRadiusCmd;
    G4UIcmdWithAnInteger*        fNxCmd;
    G4UIcmdWithAnInteger*        fNyCmd;
    G4UIcmdWithAnInteger*        fNzCmd;
    G4UIcmdWithABool*            fSphereCmd;
    G4UIcmdWithADouble*          fReflectivityCmd;
    G4UIcmdWithABool*            fWlsCmd;
    G4UIcmdWithABool*            fQuLGCmd;
    G4UIcmdWithAnInteger*        fNFibersCmd;
    G4UIcommand*                 fDefaultsCmd;
    G4UIcmdWithADouble*          fMainScintYield;
    G4UIcmdWithADouble*          fWLSScintYield;
    G4UIcmdWithAnInteger*        fSaveThresholdCmd;
};

#endif