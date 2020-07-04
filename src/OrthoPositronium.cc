//
// Created by blaine on 6/9/20.
// copied from Geant source file source/processes/electromagnetic/standard/src/G4eplusAnnihilation.cc
// add a poisson distributed time delay to the output gammas to simulate the ortho-positronium lifetime
// see borexino paper on this - https://arxiv.org/pdf/1308.0493.pdf
//


#include <G4SIunits.hh>
#include "OrthoPositronium.hh"
#include "G4MaterialCutsCouple.hh"
#include "G4Gamma.hh"
#include "G4Positron.hh"
#include "G4eeToTwoGammaModel.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

using namespace std;

OrthoPositronium::OrthoPositronium(const G4String& name)
//        : G4VEmProcess(name), isInitialised(false), OrthoPsMeanLifetime(3.0*ns)
        : G4eplusAnnihilation(name), OrthoPsMeanLifetime(3.5*ns)
{
    theGamma = G4Gamma::Gamma();
    /*SetIntegral(true);
    SetBuildTableFlag(false);
    SetStartFromNullFlag(false);
    SetSecondaryParticle(theGamma);
    SetProcessSubType(fAnnihilation);
    enableAtRestDoIt = true;*/
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

OrthoPositronium::~OrthoPositronium()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

/*G4bool OrthoPositronium::IsApplicable(const G4ParticleDefinition& p)
{
    return (&p == G4Positron::Positron());
}*/

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

/*G4double OrthoPositronium::AtRestGetPhysicalInteractionLength(
        const G4Track&, G4ForceCondition* condition)
{
    *condition = NotForced;
    return 0.0;
}*/

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

/*void OrthoPositronium::InitialiseProcess(const G4ParticleDefinition*)
{
    if(!isInitialised) {
        isInitialised = true;
        if(!EmModel(0)) { SetEmModel(new G4eeToTwoGammaModel()); }
        EmModel(0)->SetLowEnergyLimit(MinKinEnergy());
        EmModel(0)->SetHighEnergyLimit(MaxKinEnergy());
        AddEmModel(1, EmModel(0));
    }
}*/

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void OrthoPositronium::PrintInfo()
{
    G4cout << "OrthoPositronium mean lifetime is " << OrthoPsMeanLifetime << " ns." << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4VParticleChange* OrthoPositronium::AtRestDoIt(const G4Track& aTrack,
                                                   const G4Step& )
//
// Performs the e+ e- annihilation when both particles are assumed at rest.
// It generates two back to back photons with energy = electron_mass.
// The angular distribution is isotropic.
// GEANT4 internal units
//
// Note : Effects due to binding of atomic electrons are negliged.
{
    fParticleChange.InitializeForPostStep(aTrack);

    G4double cosTeta = 2.*G4UniformRand()-1.;
    G4double sinTeta = sqrt((1.-cosTeta)*(1.0 + cosTeta));
    G4double phi     = twopi * G4UniformRand();
    G4ThreeVector dir(sinTeta*cos(phi), sinTeta*sin(phi), cosTeta);
    phi = twopi * G4UniformRand();
    G4ThreeVector pol(cos(phi), sin(phi), 0.0);
    pol.rotateUz(dir);

    // e+ parameters
    G4double weight = aTrack.GetWeight();
    G4double time   = aTrack.GetGlobalTime();

    // add the time offset for orthopositronium decay
    time += G4RandExponential::shoot(OrthoPsMeanLifetime);

    // add gammas
    fParticleChange.SetNumberOfSecondaries(2);
    G4DynamicParticle* dp =
            new G4DynamicParticle(theGamma, dir, CLHEP::electron_mass_c2);
    dp->SetPolarization(pol.x(),pol.y(),pol.z());
    G4Track* track = new G4Track(dp, time, aTrack.GetPosition());
    track->SetTouchableHandle(aTrack.GetTouchableHandle());
    track->SetWeight(weight);
    pParticleChange->AddSecondary(track);

    dp = new G4DynamicParticle(theGamma,-dir, CLHEP::electron_mass_c2);
    dp->SetPolarization(-pol.x(),-pol.y(),-pol.z());
    track = new G4Track(dp, time, aTrack.GetPosition());
    track->SetTouchableHandle(aTrack.GetTouchableHandle());
    track->SetWeight(weight);
    pParticleChange->AddSecondary(track);

    // Kill the incident positron
    //
    fParticleChange.ProposeTrackStatus(fStopAndKill);
    return &fParticleChange;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
