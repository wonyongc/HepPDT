// ----------------------------------------------------------------------
//
// ParticleData.hh
// Author: Lynn Garren
//
// This is a base class for particle data information
// ----------------------------------------------------------------------
#ifndef PARTICLEDATA_HH
#define PARTICLEDATA_HH

#include <algorithm>	// swap()
#include <list>
#include <string>

#include "HepPDT/ParticleID.hh"
#include "HepPDT/CommonParticleData.hh"
#include "HepPDT/Measurement.hh"
#include "HepPDT/SpinState.hh"
#include "HepPDT/ResonanceStructure.hh"
#include "HepPDT/Constituent.hh"
#include "HepPDT/TempParticleData.hh"
#include "HepPDT/DecayData.hh"
#include "HepPDT/DecayChannel.hh"

namespace HepPDT {

//! The ParticleData class holds data for a single particle in the table.

///
/// \class ParticleData
/// \author Lynn Garren
///
/// All the particle information is accessed via this class.
///
class ParticleData {

public:
  // --- useful typedef's
  //
  typedef  CommonParticleData  CPD;

  typedef  std::list<CPD>            CPDlist;
  typedef  std::list<DecayData>      DDlist;
 
  typedef  std::list<CPD>::const_iterator       CPDID;
  typedef  std::list<DecayData>::const_iterator DDID;

  // ---  birth/death:
  //
  /// create from a CommonParticleData and a DecayData
  inline ParticleData( const CPDID & cpdid, const DDID & ddid );
  /// destructor
  inline ~ParticleData();

  // ---  copying:
  //
  inline void  swap( ParticleData & other );
  inline ParticleData( const ParticleData & orig );
  inline ParticleData& operator = ( const ParticleData & rhs );

  // ---  ParticleData accessors:
  //
  /// return the name of this particle
  const std::string &         name()        const { return itsCPDID->name();      }
  /// return the ParticleID of this particle
  ParticleID                  ID()          const { return itsCPDID->ID();        }
  /// return the ID of this particle
  int                         pid( )        const { return itsCPDID->ID().pid(); }
  /// return the charge of this particle
  double                      charge()      const { return itsCPDID->charge();    }
  /// return the color information for this particle
  double                      color()       const { return itsCPDID->color();     }
  /// return the spin information for this particle
  SpinState                   spin()        const { return itsCPDID->spin();      }
  /// return the mass of this particle
  Measurement                 mass()        const { return itsCPDID->mass(); }
  /// return the total width of this particle
  Measurement                 totalWidth()  const { return itsCPDID->totalWidth();  }
  /// return the calculated lifetime of this particle
  Measurement                 lifetime()    const { return itsCPDID->lifetime();  }
  /// lower cutoff of allowed width values
  double                      lowerCutoff() const { return itsCPDID->lowerCutoff(); }
  /// upper cutoff of allowed width values
  double                      upperCutoff() const { return itsCPDID->upperCutoff(); }
  /// number of constituent particles (e.g., quarks)
  int                         numConstituents() const { return itsCPDID->numConstituents(); }
  /// constituent information
  inline Constituent          constituent( unsigned int i ) const 
                                           { return itsCPDID->constituent(i); }
  /// ParticleID for a constituent particle
  inline ParticleID           constituentParticle( unsigned int i ) const
                                            { return itsCPDID->constituentParticle(i); }
  /// resonance (width) information
  ResonanceStructure const    resonance()   const { return itsCPDID->resonance(); }

  // --- ParticleData booleans:
  //
  /// is this a valid meson?
  bool isMeson( )   const  { return itsCPDID->isMeson(); }
  /// is this a valid baryon?
  bool isBaryon( )  const  { return itsCPDID->isBaryon(); }
  /// is this a valid diquark?
  bool isDiQuark( ) const  { return itsCPDID->isDiQuark(); }
  /// is this a valid hadron?
  bool isHadron( )  const  { return itsCPDID->isHadron(); }
  /// is this a valid lepton?
  bool isLepton( )  const  { return itsCPDID->isLepton(); }
  /// is this a valid ion?
  bool isNucleus( ) const  { return itsCPDID->isNucleus(); }
  /// is this a valid pentaquark ID?
  bool isPentaquark( ) const { return itsCPDID->isPentaquark(); }
  /// is this a valid SUSY ID?
  bool isSUSY( ) const { return itsCPDID->isSUSY(); }
  /// is this a valid R-hadron ID?
  bool isRhadron( ) const { return itsCPDID->isRhadron(); }
  // has methods look at Constituents, not PID
  /// does this particle contain an up quark?
  bool hasUp()      const  { return itsCPDID->hasUp();      }
  /// does this particle contain a down quark?
  bool hasDown()    const  { return itsCPDID->hasDown();    }
  /// does this particle contain a strange quark?
  bool hasStrange() const  { return itsCPDID->hasStrange(); }
  /// does this particle contain a charm quark?
  bool hasCharm()   const  { return itsCPDID->hasCharm();   }
  /// does this particle contain a bottom quark?
  bool hasBottom()  const  { return itsCPDID->hasBottom();  }
  /// does this particle contain a top quark?
  bool hasTop()     const  { return itsCPDID->hasTop();     }
  /// is this particle allowed to decay?
  bool isStable() const;

  // ---  ParticleData mutators:
  //
  //void  setCharge( double chg )            { itsCPDID->setCharge(chg); }
  //void  setColor( double col )             { itsCPDID->setColor(col); }
  //void  setSpin( SpinState const & spin )  { itsCPDID->setSpin(spin); }
  //void  addConstituent( Constituent c )    { itsCPDID->addConstituent(c); }
  //void  setMass( Measurement const & mass )        {  itsCPDID->setMass(mass); }
  //void  setTotalWidth( Measurement const & width ) {  itsCPDID->setTotalWidth(width); }
  //void  setTotalWidthFromLifetime( Measurement const & lt ) {  itsCPDID->setTotalWidthFromLifetime(lt); }
  //void  setLowerCutoff( double cut )               {  itsCPDID->setLowerCutoff(cut); }
  //void  setUpperCutoff( double cut )               {  itsCPDID->setUpperCutoff(cut); }

  // ---  DecayData accessors:
  //
  /// how many decay channels does this particle have?
  int                  numDecayChannels() const { return itsDDID->size(); }
  /// is this a stable particle?
  bool                 hasDecayData()     const { return itsDDID->isStable(); }
  /// return this DecayChannel
  DecayChannel  channel( int i )    const { return itsDDID->channel(i); }

  // ---  DecayData mutators:
  //
  //void  appendMode( DecayChannel const & dcp)  { itsDDID->appendMode(dcp); }
  /// change the DecayData reference
  void  setDecayData( DDID dd )                { itsDDID = dd; }

  // ---  accessors:
  //
  /// get the DecayData 
  DDID   getDecayData()            const { return itsDDID; }
  /// get the CommonParticleData
  CPDID  getCommonParticleData()   const { return itsCPDID; }
  
  /// output all information about a particle INCLUDING its decays
  inline void write( std::ostream & os ) const;
  /// output all information about a particle EXCEPT its decays
  inline void writeParticleInfo( std::ostream & os ) const;
  /// output the translation information for this particle
  inline void writeParticleTranslation( std::ostream & os ) const;

  // ---  booleans:
  //
  //bool  operator <  ( ParticleData const & other ) const;
  //bool  operator == ( ParticleData const & other ) const;

private:

  // ---  class-specific data:
  //
  CPDID  itsCPDID;	// pointer/iterator to ParticleData
  DDID   itsDDID;	// pointer/iterator to DecayData

  // default constructor not allowed
  ParticleData( );

};  // ParticleData

inline
void  swap( ParticleData & first, ParticleData & second ) {
  first.swap( second );
}

}	// HepPDT

#include "HepPDT/ParticleData.icc"

#endif // PARTICLEDATA_HH
