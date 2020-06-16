/// \file PhysicsList.cc

#include "PhysicsList.hh"

#include <stdexcept>

#include <G4UnitsTable.hh>
#include <G4SystemOfUnits.hh>
#include <G4ProductionCutsTable.hh>
#include <G4EmStandardPhysics.hh>
#include <G4EmLivermorePhysics.hh>
#include <G4EmPenelopePhysics.hh>

#include <G4RadioactiveDecay.hh>
#include <G4PhysicsListHelper.hh>
#include <G4UAtomicDeexcitation.hh>
#include <G4LossTableManager.hh>
#include <G4RegionStore.hh>
#include <G4ParticleTable.hh>
#include <G4ProcessManager.hh>

#include <G4Neutron.hh>
#include <G4HadronicProcessStore.hh>
#include <G4HadronicInteractionRegistry.hh>
#include <G4NeutronHPThermalScattering.hh>
#include <G4NeutronHPThermalScatteringData.hh>
#include <G4eplusAnnihilation.hh>
#include "OrthoPositronium.hh"


PhysicsList::PhysicsList():
QGSP_BERT_HP(1),
physDir("/phys/"),
opticalCmd("/phys/enableOptical",this),
emCmd("/phys/enableEM",this),
positroniumCmd("/phys/enableOrthoPs",this),
usePositronium(false){

    opticalCmd.SetGuidance("Enables optical photon physics.");
    opticalCmd.AvailableForStates(G4State_PreInit,G4State_Init);

    emCmd.SetGuidance("Enables precision low-energy electromagnetic physics.");
    emCmd.AvailableForStates(G4State_PreInit,G4State_Init);
    emCmd.SetCandidates("Livermore Penelope Standard");

    positroniumCmd.SetGuidance("Simulates ortho-positronium decay instead of normal annihilation for positronium decay.");
    positroniumCmd.AvailableForStates(G4State_PreInit,G4State_Init);
}

void PhysicsList::ConstructProcess() {

    QGSP_BERT_HP::ConstructProcess();

    //-//////////////////////////////////////////
    // Substituting improved G4NeutronHPThermalScattering model below 4 eV, per example Hadr04

    // neutron definition
    auto nDef = G4Neutron::Neutron();
    auto pl = nDef->GetProcessManager()->GetProcessList();

    // locate elastic process for neutron
    G4HadronicProcess* nep = nullptr;
    for(decltype(pl->size()) i = 0; i < pl->size() && !nep; ++i) {
        nep = dynamic_cast<G4HadronicProcess*>((*pl)[i]);
    }
    if(!nep) throw std::logic_error("Neutron elastic process missing");
    std::cout << "Neutron elastic process: '" << nep->GetProcessName() << "'" << G4endl;

    // Attach HP thermal scattering model and data files to process
    nep->RegisterMe(new G4NeutronHPThermalScattering);
    nep->AddDataSet(new G4NeutronHPThermalScatteringData);

    // Get the "regular" HP elastic scattering model, exclude thermal scattering region
    G4HadronicInteraction* nElasticHP = G4HadronicInteractionRegistry::Instance()->FindModel("NeutronHPElastic");
    if(!nElasticHP) throw std::logic_error("NeutronHPElastic model missing");
    nElasticHP->SetMinEnergy(4.*eV);


    // printout of physics
    for (G4int i = 0; ; ++i) {
        auto elem = const_cast<G4VPhysicsConstructor*>(GetPhysics(i));
        if(elem == nullptr) break;
        std::cout << "Has physics: '" << elem->GetPhysicsName() << "'" << G4endl;
    }

    //-//////////////////////
    // ion radioactive decay

    G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();
    G4RadioactiveDecay* radioactiveDecay = new G4RadioactiveDecay();
    radioactiveDecay->SetICM(true); //Internal Conversion
    radioactiveDecay->SetARM(true); //Atomic Rearangement
    ph->RegisterProcess(radioactiveDecay, G4GenericIon::GenericIon());
    // Deexcitation (in case of Atomic Rearangement)
    G4UAtomicDeexcitation* de = new G4UAtomicDeexcitation();
    de->SetFluo(true);
    de->SetAuger(true);
    de->SetPIXE(true);
    G4LossTableManager::Instance()->SetAtomDeexcitation(de);


    if(usePositronium) {
        // positron definition
        auto posDef = G4Positron::Positron();
        G4ProcessManager* pmanager = posDef->GetProcessManager();
        auto pos_pl = pmanager->GetProcessList();

        // locate annihilation process for the positron
        G4eplusAnnihilation *posep = nullptr;
        for (decltype(pos_pl->size()) i = 0; i < pos_pl->size() && !posep; ++i) {
            posep = dynamic_cast<G4eplusAnnihilation*>((*pos_pl)[i]);
        }
        if(!posep) throw std::logic_error("Positron annihilation process missing, make sure you are using the standard Em Model (use macro command /phys/enableEM Standard )");

        // Replace G4eplusAnnihilation with OrthoPositronium
        pmanager->RemoveProcess(posep);
        pmanager->AddProcess(new OrthoPositronium,
                0,-1, 4);
        std::cout << "Positron annihilation process: '" << "orthoposannihil" << "'" << G4endl;

    }
}

void PhysicsList::SetCuts() {
    QGSP_BERT_HP::SetCuts();

    if(myEMPhys) {
        printf("Setting cuts for precision EM physics list.\n");
        G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(250*eV, 1*GeV);
        double rangecut = 1*um;
        SetCutValue(rangecut, "gamma");
        SetCutValue(rangecut, "e-");
        SetCutValue(rangecut, "e+");
    } else {
        G4Region* region = G4RegionStore::GetInstance()->GetRegion("ScintVol");
        if(region) {
            G4ProductionCuts* cuts = new G4ProductionCuts;
            cuts->SetProductionCut(0.02*mm);
            region->SetProductionCuts(cuts);
        }
    }
}

void PhysicsList::SetNewValue(G4UIcommand* command, G4String newValue) {
    if(command == &opticalCmd) {
        if(!myOptPhys) {
            myOptPhys = new G4OpticalPhysics(0);
            G4cout << "RegisterPhysics: " << myOptPhys->GetPhysicsName() << G4endl;
            RegisterPhysics(myOptPhys);
        }
    } else if(command == &emCmd) {
        if(!myEMPhys) {
            if(newValue == "Livermore") myEMPhys = new G4EmLivermorePhysics();
            else if(newValue == "Penelope") myEMPhys = new G4EmPenelopePhysics();
            else myEMPhys = new G4EmStandardPhysics();
            G4cout << "ReplacePhysics: " << myEMPhys->GetPhysicsName() << G4endl;
            ReplacePhysics(myEMPhys);
        }
    } else if(command == &positroniumCmd) {
        G4cout << "Simulating ortho-positronium decay. " << G4endl;
        usePositronium = true;
    }
}