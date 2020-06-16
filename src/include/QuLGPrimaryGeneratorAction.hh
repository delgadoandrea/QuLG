#ifndef QuLGPrimaryGeneratorAction_h
#define QuLGPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleGunMessenger.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

class G4ParticleGun;
class G4Event;
class G4ParticleTable;
class QuLGPrimaryGeneratorMessenger;
class QuLGDetectorConstruction;

class QuLGPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:

    QuLGPrimaryGeneratorAction(QuLGDetectorConstruction*);
    virtual ~QuLGPrimaryGeneratorAction();
 
  public:

    virtual void GeneratePrimaries(G4Event* anEvent);

    void SetOptPhotonPolar();
    void SetOptPhotonPolar(G4double);
    const G4ThreeVector& PutCentre();
    const G4ThreeVector& PutTop();
    const G4ThreeVector& PutFlux();
    

  private:

    G4ParticleGun* fParticleGun;
    QuLGPrimaryGeneratorMessenger* fGunMessenger;
    QuLGDetectorConstruction* fDetector;
    G4ParticleTable*					particleTable;
    G4int positionFlag;
    enum{ UserPos=0, Top, Centre,flux};
    G4int particleFlag;
    enum{ User=0, Muon, Neutron,fluxNeutron,fluxNeutronSp,fission, positron, gamma2, gamma3, gamma1275};
    G4double monoEnergy;

};

#endif