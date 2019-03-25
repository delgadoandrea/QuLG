#ifndef QuLGDetectorConstruction_h
#define QuLGDetectorConstruction_h

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4Cache.hh"

//#include "QuLGScintSD.hh"
#include "QuLGPMTSD.hh"


class G4VPhysicalVolume;
class G4LogicalVolume;

/// Detector construction class to define materials and geometry.

class QuLGDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    QuLGDetectorConstruction();
    virtual ~QuLGDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

    void SetDefaults();
    
    //G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }

  //protected:
    //G4LogicalVolume*  fScoringVolume;

   private:
   	   //Sensitive Detectors
    //G4Cache<QuLGScintSD*> fScint_SD;
    G4Cache<QuLGPMTSD*> fPmt_SD; //Right

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif