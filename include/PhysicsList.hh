/// \file PhysicsList.hh Physics list using G4NeutronHPThermalScattering precision thermal neutrons

//-//////////////////////////////////////////
// Starting from QGSP_BERT_HP "high precision" (above thermal)
// neutron scattering model, we substitute improved G4NeutronHPThermalScattering
// model below 4 eV, as per Geant4 example Hadr04

#ifndef PHYSICSLIST_HH
#define PHYSICSLIST_HH

#include <G4UImessenger.hh>
#include <G4OpticalPhysics.hh>
#include <QGSP_BERT_HP.hh>

#include <G4UIdirectory.hh>
#include <G4UIcmdWithoutParameter.hh>
#include <G4UIcmdWithAString.hh>
#include <G4UIcmdWithADoubleAndUnit.hh>

class StepMax;

/// Physics list
class PhysicsList: public QGSP_BERT_HP, public G4UImessenger {
public:
    /// Constructor
    PhysicsList();

    /// Response to UI commands
    void SetNewValue(G4UIcommand* command, G4String newValue) override;

    void ConstructProcess() override;
    void SetCuts() override;

protected:
    G4OpticalPhysics* myOptPhys = nullptr;      ///< optical physics processes
    G4VPhysicsConstructor* myEMPhys = nullptr;  ///< low-energy electromagnetic physics
    StepMax* myStepMax = nullptr;               ///< optional step-size limit

    G4UIdirectory physDir;                      ///< UI directory for physics commands
    G4UIcmdWithoutParameter opticalCmd;         ///< command for enabling optical physics
    G4UIcmdWithAString emCmd;                   ///< command for enabling precision electromagnetic physics
    G4UIcmdWithoutParameter positroniumCmd;     ///< command for enabling positronium decay

private:
    G4bool usePositronium;                      ///< boolean for whether or not to simulate positronium decay
};

#endif
