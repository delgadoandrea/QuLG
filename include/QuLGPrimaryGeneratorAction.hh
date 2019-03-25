#ifndef QuLGPrimaryGeneratorAction_h
#define QuLGPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;
class QuLGPrimaryGeneratorMessenger;

class QuLGPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:

    QuLGPrimaryGeneratorAction();
    virtual ~QuLGPrimaryGeneratorAction();
 
  public:

    virtual void GeneratePrimaries(G4Event* anEvent);

    void SetOptPhotonPolar();
    void SetOptPhotonPolar(G4double);


  private:

    G4ParticleGun* fParticleGun;
    QuLGPrimaryGeneratorMessenger* fGunMessenger;

};

#endif