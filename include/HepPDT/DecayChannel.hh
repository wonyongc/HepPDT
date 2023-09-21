// ----------------------------------------------------------------------
//
// DecayChannel.hh
// Author:  Lynn Garren
//
// ----------------------------------------------------------------------
#ifndef DecayChannel_HH
#define DecayChannel_HH

#include <vector>
#include <string>

//#include "HepPDT/ParticleData.hh"
#include "HepPDT/Measurement.hh"

namespace HepPDT {

class ParticleData;

//! The DecayChannel class holds particle decay information

///
/// \class DecayChannel
/// \author Lynn Garren
///
/// This class holds information about a single decay channel.
///
class DecayChannel  {

public:
  // --- useful typedef's
  //

  typedef std::vector< ParticleData* >    ProductMap;

  // ---  birth/death:
  //
  /// defaults 'cause we need vector<DecayChannel<> >
  inline DecayChannel( const std::string & name = "unknown", 
                 const Measurement & branchFrac = Measurement(), 
                 const std::vector<ParticleData*> & decaylist = ProductMap(), 
                 const std::vector<double> & dmparam = std::vector<double>() )
  : itsDecayName            ( name ),
  itsBranchingFraction    ( branchFrac ),
  itsDecayChannelProducts ( decaylist ),
  itsDecayModelParameters ( dmparam )
{ ; }

  virtual ~DecayChannel()
{ ; }

  // ---  copying:
  //
  inline DecayChannel( const DecayChannel & orig );
  inline DecayChannel & operator = ( const DecayChannel & rhs );
  inline void swap( DecayChannel & other );

  // ---  accessors:
  //
  /// get the name of this decay channel
  std::string                 decayName()         const { return itsDecayName; }
  /// return the branching fraction
  Measurement                 branchingFraction() const { return itsBranchingFraction; }
  /// how many decay products in this decay channel?
  int                         size()              const { return itsDecayChannelProducts.size(); }
  /// return this decay product
  ParticleData*                  decayProduct(int i) const { return itsDecayChannelProducts[i]; }
  
  /// output decay information
  void write( std::ostream & os ) const;

  // ---  mutators:
  //
  /// change the branching fraction
  void  setBranchingFraction( Measurement const & rate ) { itsBranchingFraction = rate; }
  /// append a new decay product
  void  appendDecayChannelProduct( ParticleData* const & dcp );
  
private:

  // ---  class-specific data:
  //
  std::string              itsDecayName;
  Measurement              itsBranchingFraction;
  ProductMap               itsDecayChannelProducts;
  std::vector<double>      itsDecayModelParameters;

};  // DecayChannel

inline
void  swap( DecayChannel & first, DecayChannel & second )  {
  first.swap( second );
}

}	// HepPDT

#include "HepPDT/DecayChannel.icc"

#endif // DecayChannel_HH

