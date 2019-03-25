#ifndef QuLGTrajectory_h
#define QuLGTrajectory_h 1

#include "G4Trajectory.hh"
#include "G4Allocator.hh"
#include "G4ios.hh"
#include "globals.hh"
#include "G4ParticleDefinition.hh"
#include "G4TrajectoryPoint.hh"
#include "G4Track.hh"
#include "G4Step.hh"

class G4Polyline;                   // Forward declaration.

class QuLGTrajectory : public G4Trajectory
{
  public:

    QuLGTrajectory();
    QuLGTrajectory(const G4Track* aTrack);
    QuLGTrajectory(QuLGTrajectory &);
    virtual ~QuLGTrajectory();
 
    virtual void DrawTrajectory() const;
 
    inline void* operator new(size_t);
    inline void  operator delete(void*);

    void SetDrawTrajectory(G4bool b){fDrawit=b;}
    void WLS(){fWls=true;}
    void SetForceDrawTrajectory(G4bool b){fForceDraw=b;}
    void SetForceNoDrawTrajectory(G4bool b){fForceNoDraw=b;}

  private:

    G4bool fWls;
    G4bool fDrawit;
    G4bool fForceNoDraw;
    G4bool fForceDraw;
    G4ParticleDefinition* fParticleDefinition;
};

extern G4ThreadLocal G4Allocator<QuLGTrajectory>* QuLGTrajectoryAllocator;

inline void* QuLGTrajectory::operator new(size_t)
{
  if(!QuLGTrajectoryAllocator)
      QuLGTrajectoryAllocator = new G4Allocator<QuLGTrajectory>;
  return (void*)QuLGTrajectoryAllocator->MallocSingle();
}

inline void QuLGTrajectory::operator delete(void* aTrajectory)
{
  QuLGTrajectoryAllocator->FreeSingle((QuLGTrajectory*)aTrajectory);
}

#endif