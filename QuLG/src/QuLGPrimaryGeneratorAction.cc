#include "QuLGPrimaryGeneratorAction.hh"
#include "QuLGPrimaryGeneratorMessenger.hh"
#include "QuLGDetectorConstruction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "globals.hh"
#include "G4eplusAnnihilation.hh"
#include "G4VEmProcess.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QuLGPrimaryGeneratorAction::QuLGPrimaryGeneratorAction(QuLGDetectorConstruction* detector)
:G4VUserPrimaryGeneratorAction(), fDetector(detector)
{
  G4int n_particle = 1;
  fParticleGun = new G4ParticleGun(n_particle);
  fGunMessenger = new QuLGPrimaryGeneratorMessenger(this);
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  fParticleGun->SetParticleDefinition(particleTable->FindParticle(particleName="e+"));
  //Default energy,position,momentum
  fParticleGun->SetParticleEnergy(2.0*MeV);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.)); 
  // G4double px, py, pz;
  // G4double cs, sn, phi;
  // cs    =  CLHEP::RandFlat::shoot(-1.,1.);
  // sn    =  std::sqrt((1.0-cs)*(1.0+cs));
  // phi   =  CLHEP::RandFlat::shoot(0., CLHEP::twopi);
  // px    =  sn*std::cos(phi);
  // py    =  sn*std::sin(phi);
  // pz    =  0;
  // // fParticleGun -> SetParticleMomentumDirection(G4ThreeVector(px,py,pz));
  // fParticleGun->SetParticlePolarization(G4ThreeVector(px,py,pz));
  ///////////////////////////////////////////////// 
//   fParticleGun -> SetParticleMomentumDirection(G4ThreeVector(kx,ky,kz));
  //fParticleGun->SetParticleMomentumDirection(G4ThreeVector(std::cos(angle),std::sin(angle),0.)); 
  // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QuLGPrimaryGeneratorAction::~QuLGPrimaryGeneratorAction(){
    delete fParticleGun;
    delete fGunMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QuLGPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent){
  fParticleGun->SetParticlePosition(G4ThreeVector(fDetector->GetGunPosX() , fDetector->GetGunPosY(), fDetector->GetGunPosZ()));
  fParticleGun->GeneratePrimaryVertex(anEvent);
    // G4ThreeVector vPos;
    // if(positionFlag == Top)	{
    //     static G4ThreeVector Temp(0.0,0.0,49.9*cm);
    //     vPos = Temp;
    // }			
    // else if (positionFlag == Centre){
    //     static G4ThreeVector Temp(0.0,0.0,0.0);
    //     vPos = Temp;
    // }	
    // else if (positionFlag == flux){
    //     G4double radius = 40*cm;
    //     G4double phi = CLHEP::RandFlat::shoot(0.0,twopi);
    //     G4double theta = CLHEP::RandFlat::shoot(0.0,pi);
    //     G4double posX =radius*sin(theta)*cos(phi);
    //     G4double posY =radius*sin(theta)*sin(phi);
    //     G4double posZ =radius*cos(theta);
    //     static G4ThreeVector Temp(0,0,0);
    //     Temp.setX(posX);
    //     Temp.setY(posY);
    //     Temp.setZ(posZ);
    //     vPos = Temp;
    // }
   /////////////////////////////////////////////////////////////////////////////////////////////////////////
    // G4PrimaryVertex* vertex = new G4PrimaryVertex();
    // G4PrimaryParticle* gamma[2]={0,0};
    // G4ParticleDefinition* pD = particleTable->FindParticle("gamma");
    // // fParticleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
    // gamma[0] = new G4PrimaryParticle(pD);
    // gamma[1] = new G4PrimaryParticle(pD);
    // gamma[0]->SetMass(0.);
    // gamma[1]->SetMass(0.);
    // gamma[0]->SetCharge(0.);
    // gamma[1]->SetCharge(0.);
    // gamma[0]->SetKineticEnergy(CLHEP::electron_mass_c2);
    // gamma[1]->SetKineticEnergy(CLHEP::electron_mass_c2);
    // G4double px, py, pz;
    // G4double cs, sn, phi;
    // cs    =  CLHEP::RandFlat::shoot(-1.,1.);
    // sn    =  std::sqrt((1.0-cs)*(1.0+cs));
    // phi   =  CLHEP::RandFlat::shoot(0., CLHEP::twopi);
    // px    =  sn*std::cos(phi);
    // py    =  sn*std::sin(phi);
    // pz    =  cs;
    // gamma[0]->SetMomentumDirection(G4ThreeVector(px, py, pz));
    // // gamma[0]->SetMomentumDirection(G4ThreeVector(0, 0, 1));
    // gamma[0]->SetPolarization(G4ThreeVector(px, py, pz));
    // gamma[1]->SetMomentumDirection(G4ThreeVector(-1.*px, -1.*py, -1.*pz));
    // // gamma[1]->SetMomentumDirection(G4ThreeVector(0, 0, -1));
    // gamma[1]->SetPolarization(G4ThreeVector(px, py, pz));
    // vertex->SetPrimary(gamma[0]);
    // vertex->SetPrimary(gamma[1]);
    // anEvent->AddPrimaryVertex(vertex);
    // fParticleGun->GeneratePrimaryVertex(anEvent);
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////  ////
    // if(particleFlag == gamma2){
    //     G4PrimaryParticle* particle[2]={0,0};
    //     GenerateTwoGamma(particle);
    //     vertex->SetPrimary(particle[0]);
    //     vertex->SetPrimary(particle[1]);
    // }else if(particleFlag == gamma3){
    //     G4PrimaryParticle* particle[3]={0,0,0};
    //     GenerateThreeGamma(particle);
    //     vertex->SetPrimary(particle[0]);
    //     vertex->SetPrimary(particle[1]);
    //     vertex->SetPrimary(particle[2]);
    // }else{
    //     G4double mass = particle_definition->GetPDGMass();	
    //     for(G4int i=0; i<NumberOfParticlesToBeGenerated; i++){
    //         G4PrimaryParticle* particle = new G4PrimaryParticle(particle_definition);
    //         particle->SetKineticEnergy(particle_energy);
    //         particle->SetMass(mass);
    //         particle->SetMomentumDirection(particle_momentum_direction);
    //         particle->SetCharge(particle_charge);
    //         particle->SetPolarization(particle_polarization.x(),
    //                                   particle_polarization.y(),
    //                                   particle_polarization.z());
    //         vertex->SetPrimary(particle);
            
    //     }
    // }
    // anEvent->AddPrimaryVertex(vertex);
  // genModule->GeneratePrimaries(anEvent);
  // FileIO::GetEvent().t = GetGeneratorTime();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QuLGPrimaryGeneratorAction::SetOptPhotonPolar()
{
 G4double angle = G4UniformRand() * 360.0*deg;
 SetOptPhotonPolar(angle);
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QuLGPrimaryGeneratorAction::SetOptPhotonPolar(G4double angle){
  if (fParticleGun->GetParticleDefinition()->GetParticleName()!="opticalphoton"){
     G4cout << "--> warning from PrimaryGeneratorAction::SetOptPhotonPolar() :"
               "the particleGun is not an opticalphoton" << G4endl;
     return;
  }
  
  // Best-case scenario for momentum
  // G4ThreeVector normal (1., 0., 0.);
  // // Isotropic momentum case
  // // G4double cosTheta = -1.0 + 2.0*G4UniformRand(); // cosine of random angle theta
  // // G4double phi = 2*3.14*G4UniformRand(); // angle phi
  // // G4double sinTheta = sqrt(1 - cosTheta*cosTheta); // sine of random angle theta
  // // G4double kx = sinTheta*std::cos(phi); // x component of momentum
  // // G4double ky = sinTheta*std::sin(phi); // y component of momentum
  // // G4double kz = cosTheta;// z component of momentum
  // // // Define unit normal vector (perpendicular lo k vector)
  // // G4double nx=1.0; // 
  // // G4double ny=1.0; // 
  // // G4double nz = (-(kx*nx) - (ky*ny))/(kz); //  
  // // G4ThreeVector normal (nx, ny, nz);
  // normal = normal/(std::sqrt(normal*normal)); // to make it have unit length
  // G4ThreeVector kphoton = fParticleGun->GetParticleMomentumDirection(); // momentum (K) vector
  // G4ThreeVector product = normal.cross(kphoton); // find a vector perpendicular to both the normal and the k vector
  // G4double modul2       = product*product; // find its magnitude squared
  // G4ThreeVector e_perpend (0., 0., 1.); // dummy definition for perpendicular component of E field
  // if (modul2 > 0.) e_perpend = (1./std::sqrt(modul2))*product; // so that we do not divide by 0 (acutual definition of Eperp)
  // G4ThreeVector e_paralle    = e_perpend.cross(kphoton); // define Epar
  // G4ThreeVector polar = std::cos(angle)*e_paralle + std::sin(angle)*e_perpend; // polar
  // fParticleGun->SetParticlePolarization(polar);
  // // Best case scenario, particle with momentum only along the z axis (axis of the light guide)
  // G4ThreeVector normal (1., 0., 0.);
  // G4ThreeVector kphoton = fParticleGun->GetParticleMomentumDirection();
  // G4ThreeVector product = normal.cross(kphoton);
  // G4double modul2       = product*product;

  // G4ThreeVector e_perpend (0., 0., 1.);
  // if (modul2 > 0.) e_perpend = (1./std::sqrt(modul2))*product;
  // G4ThreeVector e_paralle    = e_perpend.cross(kphoton);

  // G4ThreeVector polar = std::cos(angle)*e_paralle + std::sin(angle)*e_perpend;
  // fParticleGun->SetParticlePolarization(polar); 

}