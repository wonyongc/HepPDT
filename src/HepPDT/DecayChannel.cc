// ----------------------------------------------------------------------
//
// DecayChannel.cc
//
// ----------------------------------------------------------------------

#include <algorithm>	// swap()

#include "HepPDT/defs.h"
#include "HepPDT/DecayChannel.hh"
#include "HepPDT/ParticleData.hh"


namespace HepPDT {
  
void  DecayChannel::appendDecayChannelProduct( ParticleData* const & dcp )
{
    itsDecayChannelProducts.push_back( dcp );
}

void DecayChannel::write( std::ostream & os ) const
{
  ProductMap::const_iterator cit;
  os << "          " << itsDecayName << " " << itsBranchingFraction;
  if( itsDecayChannelProducts.size() > 0 ) { 
    for( cit=itsDecayChannelProducts.begin(); 
	 cit != itsDecayChannelProducts.end(); ++cit ) {
       ParticleData*  pd = *cit;
       os << " " << pd->name();
    }
  }
  os << std::endl;
}

} // HepPDT
