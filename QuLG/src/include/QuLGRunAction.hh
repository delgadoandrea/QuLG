#include "G4UserRunAction.hh"

#ifndef QuLGRunAction_h
#define QuLGRunAction_h 1

class QuLGRun;
class QuLGHistoManager;
class G4Run;

class QuLGRunAction : public G4UserRunAction
{
  public:

    QuLGRunAction();
    virtual ~QuLGRunAction();

    virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);

  private:

    QuLGRun*          fRun;
    QuLGHistoManager* fHistoManager;
};

#endif