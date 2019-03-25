#ifndef QuLGScintHit_h
#define QuLGScintHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"
#include "G4VPhysicalVolume.hh"

#include "tls.hh"

class QuLGScintHit : public G4VHit
{
  public:
 
    QuLGScintHit();
    QuLGScintHit(G4VPhysicalVolume* pVol);
    virtual ~QuLGScintHit();
    QuLGScintHit(const QuLGScintHit &right);
    const QuLGScintHit& operator=(const QuLGScintHit &right);
    G4int operator==(const QuLGScintHit &right) const;

    inline void *operator new(size_t);
    inline void operator delete(void *aHit);
 
    virtual void Draw();
    virtual void Print();

    inline void SetEdep(G4double de) { fEdep = de; }
    inline void AddEdep(G4double de) { fEdep += de; }
    inline G4double GetEdep() { return fEdep; }

    inline void SetPos(G4ThreeVector xyz) { fPos = xyz; }
    inline G4ThreeVector GetPos() { return fPos; }

    inline const G4VPhysicalVolume * GetPhysV() { return fPhysVol; }

  private:
    G4double fEdep;
    G4ThreeVector fPos;
    const G4VPhysicalVolume* fPhysVol;

};

typedef G4THitsCollection<QuLGScintHit> QuLGScintHitsCollection;

extern G4ThreadLocal G4Allocator<QuLGScintHit>* QuLGScintHitAllocator;

inline void* QuLGScintHit::operator new(size_t)
{
  if(!QuLGScintHitAllocator)
      QuLGScintHitAllocator = new G4Allocator<QuLGScintHit>;
  return (void *) QuLGScintHitAllocator->MallocSingle();
}

inline void QuLGScintHit::operator delete(void *aHit)
{
  QuLGScintHitAllocator->FreeSingle((QuLGScintHit*) aHit);
}

#endif