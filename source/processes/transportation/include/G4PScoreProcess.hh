//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id: G4PScoreProcess.hh,v 1.9 2006/06/29 21:10:04 gunter Exp $
// GEANT4 tag $Name: geant4-08-02 $
//
// ----------------------------------------------------------------------
// Class G4PIScoreProcess
//
// Class description:
//
// Used internally by scoring in a "parallel" geometry.
// This forced process messages a "scorer" derived from G4VScorer.
// The scorer is messaged with the current G4Step and G4GeometryCellStep.
// This post step process is supposed to be placed as the 
// process following directly after transportation and the 
// importance sampling process if applied, and before all physical
// post step processes.

// Author: Michael Dressel (Michael.Dressel@cern.ch)
// ----------------------------------------------------------------------
#ifndef G4PScoreProcess_hh 
#define G4PScoreProcess_hh G4PScoreProcess_hh

#include "G4VProcess.hh"
#include "G4VTrackTerminator.hh"

class G4VParallelStepper;
class G4VScorer;

class G4PScoreProcess : public G4VProcess, 
                        public G4VTrackTerminator
{

public:  // with description

  G4PScoreProcess(G4VParallelStepper  &astepper,
                  G4VScorer &aScorer,
                  const G4String &aName = "PScoreProcess");
    // create a G4ParticleChange

  virtual ~G4PScoreProcess();
    // delete the G4ParticleChange

  virtual G4double 
  PostStepGetPhysicalInteractionLength(const G4Track& aTrack,
                                       G4double   previousStepSize,
                                       G4ForceCondition* condition);
    // make the process beeing forced

  virtual G4VParticleChange * PostStepDoIt(const G4Track&, 
                                           const G4Step&);
    // get G4GeometryCellStep and G4Step and message "scorer"

  virtual void KillTrack() const;

  virtual const G4String &GetName() const;

    // to be called by the importance process if the track should
    // be killed after scoring
 
public:  // without description

  //  no operation in  AtRestDoIt and  AlongStepDoIt
  
  virtual G4double 
  AlongStepGetPhysicalInteractionLength(const G4Track&,
                                        G4double  ,
                                        G4double  ,
                                        G4double& ,
                                        G4GPILSelection*);
  
  virtual G4double AtRestGetPhysicalInteractionLength(const G4Track& ,
                                                      G4ForceCondition*);
  
  virtual G4VParticleChange* AtRestDoIt(const G4Track&, const G4Step&);
  virtual G4VParticleChange* AlongStepDoIt(const G4Track&, const G4Step&);
  
private:

  G4PScoreProcess(const G4PScoreProcess &);
  G4PScoreProcess &operator=(const G4PScoreProcess &);

  G4VParallelStepper &fPstepper;
  G4VScorer &fScorer;  

  mutable G4bool fKillTrack;
};

#endif



