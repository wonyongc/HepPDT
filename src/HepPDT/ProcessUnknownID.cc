// ----------------------------------------------------------------------
//
// ProcessUnknownID.cc
// Author: Lynn Garren
//
// ----------------------------------------------------------------------
#include "HepPDT/ProcessUnknownID.hh"
#include "HepPDT/ParticleDataTable.hh"

namespace HepPDT {

CommonParticleData * ProcessUnknownID::callProcessUnknownID
              ( ParticleID key, const ParticleDataTable & pdt ) 
{ 
    if ( alreadyHere ) return 0;
    alreadyHere = true;
    CommonParticleData * cpd = processUnknownID( key, pdt );
    alreadyHere = false;
    return cpd;
}

}	// HepPDT
