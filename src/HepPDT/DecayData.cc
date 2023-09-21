// ----------------------------------------------------------------------
//
// DecayData.cc
//
// ----------------------------------------------------------------------

#include "HepPDT/defs.h"
#include "HepPDT/DecayData.hh"

namespace HepPDT {

void DecayData::write( std::ostream & os ) const
{
  std::vector<DecayChannel >::const_iterator cit;
  for( cit=itsDecayList.begin(); cit != itsDecayList.end(); ++cit ) {
      const DecayChannel  dt = *cit;
      dt.write( os );
  }
}

bool  DecayData::isStable() const
{
    if( itsDecayList.size() > 0) { return false; }
    return true;
}

void  DecayData::appendMode( DecayChannel dc )
{
    itsDecayList.push_back( dc );
}

//bool  DecayData::decay( int i, const PT & parent, std::vector<PT> & daughters )
//{
//    if( i >= itsDecayList.size() ) { return false; }
//    itsDecayList[i].decay( parent, daughters );
//    return true;
//}

//bool  DecayData::decay( double rdm, const PT & parent, std::vector<PT> & daughters )
//{
//    int i;
//    double bfsum = 0.;
 //   if( rdm < 0. || rdm > 1. ) { return false; }

//    for( i=0; i<itsDecayList.size(); ++i ) {
//        bfsum += itsDecayList[i].branchingFraction();
//	if( rdm <= bfsum ) { 
//	    itsDecayList[i].decay( parent, daughters );
//	    return true;
//	}
//    }
//    return false;
//}

} // HepPDT
