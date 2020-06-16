#ifndef QuLGTrackingAction_h
#define QuLGTrackingAction_h 1

#include "G4UserTrackingAction.hh"
#include "globals.hh"

class QuLGTrackingAction : public G4UserTrackingAction {

  public:

    QuLGTrackingAction();
    virtual ~QuLGTrackingAction() {};

    virtual void PreUserTrackingAction(const G4Track*);
    virtual void PostUserTrackingAction(const G4Track*);

  private:

};

#endif