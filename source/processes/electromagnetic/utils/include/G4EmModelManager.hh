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
// $Id: G4EmModelManager.hh,v 1.19 2006/06/29 19:54:25 gunter Exp $
// GEANT4 tag $Name: geant4-08-02 $
//
// -------------------------------------------------------------------
//
// GEANT4 Class header file
//
// File name:     G4EmModelManager
//
// Author:        Vladimir Ivanchenko
//
// Creation date: 07.05.2002
//
// Modifications:
//
// 03-12-02 V.Ivanchenko fix a bug in model selection
// 20-01-03 Migrade to cut per region (V.Ivanchenko)
// 27-01-03 Make models region aware (V.Ivanchenko)
// 13-02-03 The set of models is defined for region (V.Ivanchenko)
// 26-03-03 Add GetDEDXDispersion (V.Ivanchenko)
// 13-04-03 Add startFromNull (V.Ivanchenko)
// 13-05-03 Add calculation of precise range (V.Ivanchenko)
// 21-07-03 Add UpdateEmModel method (V.Ivanchenko)
// 03-11-03 Substitute STL vector for G4RegionModels (V.Ivanchenko)
// 11-04-05 Remove access to fluctuation models (V.Ivanchenko)
// 10-01-06 PreciseRange -> CSDARange (V.Ivantchenko)
// 20-01-06 Introduce G4EmTableType and reducing number of methods (VI)
// 13-05-06 Add GetModel by index method (VI)
//
// Class Description:
//
// It is the unified energy loss process it calculates the continuous
// energy loss for charged particles using a set of Energy Loss
// models valid for different energy regions. There are a possibility
// to create and access to dE/dx and range tables, or to calculate
// that information on fly.

// -------------------------------------------------------------------
//


#ifndef G4EmModelManager_h
#define G4EmModelManager_h 1

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "globals.hh"
#include "G4DataVector.hh"
#include "G4EmTableType.hh"

class G4RegionModels
{

friend class G4EmModelManager;

public:

private:

  G4RegionModels(G4int nMod, std::vector<G4int>& list, G4DataVector& lowE);

  ~G4RegionModels();

  G4int SelectIndex(G4double e) const {
    G4int idx = 0;
    if (nModelsForRegion>1) {
      idx = nModelsForRegion;
      do {idx--;} while (idx && e <= lowKineticEnergy[idx]);
    }
    return theListOfModelIndexes[idx];
  };

  G4int ModelIndex(G4int n) const {
    return theListOfModelIndexes[n];
  };

  G4int NumberOfModels() const {
    return nModelsForRegion;
  };

  G4int              nModelsForRegion;
  G4int*             theListOfModelIndexes;
  G4double*          lowKineticEnergy;

};

#include "G4VEmModel.hh"
#include "G4VEmFluctuationModel.hh"
#include "G4DynamicParticle.hh"

class G4Region;
class G4ParticleDefinition;
class G4DataVector;
class G4PhysicsVector;
class G4MaterialCutsCouple;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class G4EmModelManager
{
public:

  G4EmModelManager();

  ~G4EmModelManager();

  void Clear();

  const G4DataVector* Initialise(const G4ParticleDefinition*,
                                 const G4ParticleDefinition*,
				       G4double,
                                       G4int);

  const G4DataVector* Cuts() const;

  const G4DataVector* SubCutoff() const;

  void FillDEDXVector(G4PhysicsVector*, const G4MaterialCutsCouple*, 
		      G4EmTableType t = fRestricted);

  void FillLambdaVector(G4PhysicsVector*, const G4MaterialCutsCouple*, 
                        G4bool startFromNull = true, G4EmTableType t = fRestricted);

  G4VEmModel* SelectModel(G4double& energy, size_t& index);

  G4VEmModel* GetModel(G4int);

  G4int NumberOfModels() const;

  void AddEmModel(G4int, G4VEmModel*, G4VEmFluctuationModel*, const G4Region*);
  
  void UpdateEmModel(const G4String&, G4double, G4double);

private:

  // hide  assignment operator

  G4EmModelManager(G4EmModelManager &);
  G4EmModelManager & operator=(const G4EmModelManager &right);

// =====================================================================

private:

  G4DataVector                theCuts;
  G4DataVector                theSubCuts;

  std::vector<G4VEmModel*>                models;
  std::vector<G4VEmFluctuationModel*>     flucModels;
  std::vector<const G4Region*>            regions;
  std::vector<G4int>                      orderOfModels;
  G4DataVector                            upperEkin;

  G4int                       nEmModels;
  G4int                       nRegions;
  G4int                       nCouples;

  G4int*                      idxOfRegionModels;
  G4RegionModels**            setOfRegionModels;

  G4double                    minSubRange;

  const G4ParticleDefinition* particle;
  const G4ParticleDefinition* secondaryParticle;

  G4int                       verboseLevel;

  // cash
  G4int                       currentIdx;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

inline G4VEmModel* G4EmModelManager::SelectModel(G4double& kinEnergy, 
						 size_t& index)
{
  currentIdx = 
    (setOfRegionModels[idxOfRegionModels[index]])->SelectIndex(kinEnergy);
  return models[currentIdx];
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

inline const G4DataVector* G4EmModelManager::Cuts() const
{
  return &theCuts;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

inline const G4DataVector* G4EmModelManager::SubCutoff() const
{
  return &theSubCuts;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

inline G4int G4EmModelManager::NumberOfModels() const
{
  return nEmModels;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif
