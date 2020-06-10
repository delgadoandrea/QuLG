#ifndef QuLGDetectorConstruction_h
#define QuLGDetectorConstruction_h

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4Cache.hh"

//#include "QuLGScintSD.hh"
#include "QuLGPMTSD.hh"


class G4VPhysicalVolume;
class G4LogicalVolume;
class QuLGDetectorMessenger;

/// Detector construction class to define materials and geometry.

class QuLGDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    QuLGDetectorConstruction();
    virtual ~QuLGDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

    void SetDefaults();
    
    void SetGunPosX(G4double);
    void SetGunPosY(G4double); 
    void SetGunPosZ(G4double);    


    G4double GetGunPosX() const   {return fGunPosX;};
    G4double GetGunPosY() const   {return fGunPosY;};
    G4double GetGunPosZ() const   {return fGunPosZ;};


   private:

    G4Cache<QuLGPMTSD*> fPmt_SD; //Right

    G4double  fGunPosX;
    G4double  fGunPosY;  
    G4double  fGunPosZ;    

    
    QuLGDetectorMessenger* fDetectorMessenger;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif