#ifndef PROCESSUNKNOWNID_HH
#define PROCESSUNKNOWNID_HH
// ----------------------------------------------------------------------
//
// ProcessUnknownID.hh
// Author: Lynn Garren
//
// ----------------------------------------------------------------------

#include "HepPDT/ParticleID.hh"
#include "HepPDT/CommonParticleData.hh"

namespace HepPDT {

// forward declaration to avoid circular dependencies
class ParticleDataTable;

  
//! The ProcessUnknownID class is abstract.

///
/// \class ProcessUnknownID
/// \author Lynn Garren
///
/// This is an abstract class which allows you to define 
/// your own methods for handling undefined particle lookups.
///
class ProcessUnknownID  {

public:

  /// safety wrapper to avoid secondary calls to processUnknownID
  CommonParticleData  * callProcessUnknownID( ParticleID, const ParticleDataTable & );

  /// allow cleanup by ParticleDataTable
  virtual ~ProcessUnknownID( ) {}

protected:
  ProcessUnknownID( ) : alreadyHere(false) {}

private: 

  bool alreadyHere;

  virtual CommonParticleData  * processUnknownID( ParticleID, 
                                            const ParticleDataTable & ) = 0;

};  // ProcessUnknownID

}	// HepPDT

#endif // PROCESSUNKNOWNID_HH
