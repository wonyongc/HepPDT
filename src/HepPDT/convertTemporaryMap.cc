// ----------------------------------------------------------------------
//
// convertTemporaryMap.cc
// Author: Lynn Garren, Walter Brown
//
// ----------------------------------------------------------------------

#include "HepPDT/defs.h"
#include "HepPDT/ParticleID.hh"
#include "HepPDT/DecayData.hh"
#include "HepPDT/DecayChannel.hh"
#include "HepPDT/ParticleDataTable.hh"
#include "HepPDT/ParticleData.hh"
#include "HepPDT/TempParticleData.hh"
#include "HepPDT/Version.hh"

namespace HepPDT {

void ParticleDataTable::convertTemporaryMap( TempMap & tempPDT, std::ostream & )
{
  std::map<ParticleID,TempParticleData>::iterator cit;
  // need an empty DecayData
  DecayData nodecay;
  DDID edid = addDecayData( nodecay );
  // first loop and create a PD map with empty DecayData
  for( cit=tempPDT.begin(); cit != tempPDT.end(); ++cit ) {
    TempParticleData & tempd = cit->second;
    // create CPD and add it to the list
    CommonParticleData cpd( tempd );
    CPDID cid = addParticleData( cpd );
    // now create ParticleData and add it to the map
    ParticleData pd( cid, edid );
    addParticle( pd );
  }
  // now loop again and add the DecayData
  std::vector<TempDecayData>::const_iterator cit2;
  for( cit=tempPDT.begin(); cit != tempPDT.end(); ++cit ) {
    // find the PD for this particle
    TempParticleData & tempd = cit->second;
    ParticleData* thisPD( particle( tempd.tempID ));
    // convert TempDecayData to DecayChannel
    std::vector<DecayChannel > dv;
    for( cit2=tempd.tempDecayList.begin(); cit2 != tempd.tempDecayList.end(); ++cit2 ) {
      TempDecayData tdd = *cit2;
      std::vector< ParticleData* > decaylist;
      for( unsigned int i=0; i<tdd.tempDaughterList.size(); ++i ) {
          ParticleData* dtr( particle( tdd.tempDaughterList[i] ) );
	  if( dtr ) { 
	      decaylist.push_back( dtr ); 
	  }
      }
      DecayChannel  dc( tdd.tempDecayName, 
                        Measurement( tdd.tempBranchingFraction, 0.),
                        decaylist, 
			tdd.tempDecayParameters );
      dv.push_back( dc );
    }
    // create DD and add it to the list
    DecayData dd( dv );
    DDID did = addDecayData( dd );
    // now add this DecayData to the ParticleData
    thisPD->setDecayData( did );
    
  }
}

}	// HepPDT
