// ----------------------------------------------------------------------
//
// QQDecay.hh
// Author: Lynn Garren
//
// Temporary holding tank for QQ decays 
// 
// ----------------------------------------------------------------------
#ifndef QQDECAY_HH
#define QQDECAY_HH

#include <vector>
#include <sstream>

#include "HepPDT/defs.h"
#include "HepPDT/QQChannel.hh"

namespace HepPDT {

//! QQDecay is a temporary holder for QQ decay information

///
/// \class QQDecay
/// \author Lynn Garren
///
/// Temporarily keep QQ decay information in this class and convert it 
/// when we finish inputing QQ information.
///
class QQDecay  {

public:

  typedef std::vector<QQChannel>  ChannelList;

  // -- constructors
  QQDecay();
  ~QQDecay();

  // ---  copying:
  //
  void  swap ( QQDecay & rhs );
  QQDecay( const QQDecay & orig );
  QQDecay & operator = ( const QQDecay & rhs );

  // --- mutators
  //
  /// add a decay channel
  void addChannel( QQChannel c ) { itsChannels.push_back( c ); }
  /// declare this particle stable
  void makeStable( ) { itsStable = true; }

  // --- accessors
  //
  /// does this particle decay?
  bool isStable()  const { return itsStable; };
  /// return a QQ decay channel
  QQChannel  channel( int i ) const { return itsChannels[i]; }
  /// write decay information for diagnostics
  void write( std::ostream & os ) const;	// intended for diagnostic use

  /// how many decay channels does this particle have?
  int                          size()  const { return itsChannels.size(); }

private:

  bool itsStable;
  ChannelList itsChannels;

};  // QQDecay

inline void swap( QQDecay & first, QQDecay & second ) {
  first.swap( second );
}

}  // namespace HepPDT

#endif // QQDECAY_HH
