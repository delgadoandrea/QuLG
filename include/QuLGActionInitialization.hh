#ifndef QuLGActionInitialization_h
#define QuLGActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class QuLGDetectorConstruction;

/// Action initialization class.
///

class QuLGActionInitialization : public G4VUserActionInitialization
{
  public:
    QuLGActionInitialization(const QuLGDetectorConstruction* det);
    virtual ~QuLGActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;

  private:

    const QuLGDetectorConstruction* fDetector;
};

#endif