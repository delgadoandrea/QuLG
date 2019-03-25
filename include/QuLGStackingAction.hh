#ifndef QuLGStackingAction_H
#define QuLGStackingAction_H 1

#include "globals.hh"
#include "G4UserStackingAction.hh"

class QuLGEventAction;

class QuLGStackingAction : public G4UserStackingAction
{
  public:

    QuLGStackingAction(QuLGEventAction*);
    virtual ~QuLGStackingAction();
 
    virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack);
    virtual void NewStage();
    virtual void PrepareNewEvent();
 
  private:
    QuLGEventAction* fEventAction;
};

#endif