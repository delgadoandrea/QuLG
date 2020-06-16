#include "QuLGPMTHit.hh"
#include "G4ios.hh"
#include "G4VVisManager.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"

G4ThreadLocal G4Allocator<QuLGPMTHit>* QuLGPMTHitAllocator=0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QuLGPMTHit::QuLGPMTHit()
  :  fPmtNumber(-1),fPhotons(0),fPos(0,0,0),fPhysVol(nullptr),fPhotEnergy(0.0),fDrawit(false),fGlobalTime(0.0), fLocalTime(0.0),fCombinedTime(0.0), fdt(0.0), 
  Global_Times(0),  Local_Times(0), Combined_Times(0){}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// QuLGPMTHit::QuLGPMTHit(G4double gt,G4double lt)//
//   : fGlobalTime(gt), fLocalTime(lt) {}

// //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QuLGPMTHit::~QuLGPMTHit() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QuLGPMTHit::QuLGPMTHit(const QuLGPMTHit &right) : G4VHit()
{
  fPmtNumber=right.fPmtNumber;
  fPhotons=right.fPhotons;
  fPhysVol=right.fPhysVol;
  fGlobalTime=right.fGlobalTime;
  fLocalTime=right.fLocalTime;
  fCombinedTime=right.fCombinedTime;
  fdt=right.fdt;
  fPhotEnergy=right.fPhotEnergy;
  fDrawit=right.fDrawit;
  Global_Times=right.Global_Times;
  Local_Times=right.Local_Times;
  Combined_Times=right.Combined_Times;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const QuLGPMTHit& QuLGPMTHit::operator=(const QuLGPMTHit &right){
  fPmtNumber = right.fPmtNumber;
  fPhotons=right.fPhotons;
  fPhysVol=right.fPhysVol;
  fPhotEnergy=right.fPhotEnergy;
  fDrawit=right.fDrawit;
  fGlobalTime=right.fGlobalTime;
  fLocalTime=right.fLocalTime;
  fCombinedTime=right.fCombinedTime;
  Global_Times=right.Global_Times;
  Local_Times=right.Local_Times;
  Combined_Times=right.Combined_Times;
  fdt=right.fdt;

  return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4int QuLGPMTHit::operator==(const QuLGPMTHit &right) const{
  return (fPmtNumber==right.fPmtNumber);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QuLGPMTHit::Draw(){
  if(fDrawit&&fPhysVol){ //ReDraw only the PMTs that have hit counts > 0
    //Also need a physical volume to be able to draw anything
    G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
    if(pVVisManager){//Make sure that the VisManager exists
      G4VisAttributes attribs(G4Colour(1.,0.,0.));
      attribs.SetForceSolid(true);
      //G4RotationMatrix rot;
      //if(fPhysVol->GetRotation())//If a rotation is defined use it
      //  rot=*(fPhysVol->GetRotation());
      //G4Transform3D trans(rot,fPhysVol->GetTranslation());//Create transform
      //pVVisManager->Draw(*fPhysVol,attribs);//Draw it
//      pVVisManager->Draw(*fPhysVol,attribs,trans);//Draw it      
    }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QuLGPMTHit::Print() {}