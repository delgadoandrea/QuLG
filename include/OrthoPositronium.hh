//
// Created by blaine on 6/9/20.
// copied from Geant source file source/processes/electromagnetic/standard/include/G4eplusAnnihilation.hh
//

#ifndef ORTHOPOSITRONIUM_HH
#define ORTHOPOSITRONIUM_HH

//#include "G4VEmProcess.hh"
#include "G4eplusAnnihilation.hh"

class G4ParticleDefinition;

//class OrthoPositronium : public G4VEmProcess
class OrthoPositronium : public G4eplusAnnihilation
{

public:

    OrthoPositronium(const G4String& name = "orthoposannihil");

    ~OrthoPositronium() override;

    //G4bool IsApplicable(const G4ParticleDefinition& p) override;

    G4VParticleChange* AtRestDoIt(
            const G4Track& track,
            const G4Step& stepData) override;

    /*G4double AtRestGetPhysicalInteractionLength(
            const G4Track& track,
            G4ForceCondition* condition
    ) override;*/

    // Print out of the class parameters

    void PrintInfo() override;

/*protected:

    void InitialiseProcess(const G4ParticleDefinition*) override; */
private:

    //G4bool  isInitialised;
    const G4ParticleDefinition* theGamma;
    const G4double OrthoPsMeanLifetime;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif //ORTHOPOSITRONIUM_HH
