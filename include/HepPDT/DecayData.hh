// ----------------------------------------------------------------------
//
// DecayData.hh
// Author:  Lynn Garren
//
// ----------------------------------------------------------------------
#ifndef DecayData_HH
#define DecayData_HH

#include <vector>

#include "HepPDT/DecayChannel.hh"

namespace HepPDT {

//! The DecayData class holds particle decay information

///
/// \class DecayData
/// \author Lynn Garren
///
/// Use this class to access particle decay information.
///
class DecayData {

public:

  // ---  birth/death:
  //
  /// default constructor
  inline DecayData( );
  /// construct from a vector of decay channels
  inline DecayData( std::vector<DecayChannel > const & dv );
  inline ~DecayData();

  // ---  copying:
  //
  inline DecayData( DecayData const & orig );
  inline DecayData & operator = ( DecayData const & rhs );
  inline void swap( DecayData & other );

  // ---  accessors:
  //
  /// is this a stable particle?
  bool                   isStable()     const;
  /// how many decay channels does this particle have?
  int                    size()         const { return itsDecayList.size(); }
  /// return this DecayChannel
  DecayChannel  channel( int i ) const { return itsDecayList[i]; }
  
  /// output decay information
  void write( std::ostream & os ) const;

  // ---  mutators:
  //
  /// append a new decay channel
  void  appendMode( DecayChannel );

private:

  std::vector<DecayChannel > itsDecayList; 

};  // DecayData

inline
void swap( DecayData & first, DecayData & second )  {
  first.swap( second );
}

}	// HepPDT

#include "HepPDT/DecayData.icc"

#endif // DecayData_HH
