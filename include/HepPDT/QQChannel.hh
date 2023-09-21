// ----------------------------------------------------------------------
//
// QQChannel.hh
// Author: Lynn Garren
// 
// Temporary holding tank for QQ decay channels
// information must be collected from multiple input lines
// 
// ----------------------------------------------------------------------
#ifndef QQCHANNEL_HH
#define QQCHANNEL_HH

#include <string>
#include <vector>
#include <sstream>

namespace HepPDT {

//! QQhelicity is a temporary holder for QQ decay information

/// QQ decay helicity information
struct QQhelicity {
  /// normally HELICITY has 3 values, but the documentation allows for more
  double           prob;
  std::vector<int> hel;
};

/// QQ decay angular helicity information
struct QQAngularHelicity {
  int     hel;
  double  a0;
  double  a1;
  double  a2;
  double  a3;
  double  a4;
  double  a5;
  double  a6;
};

/// QQ decay matrix information
struct QQmatrix {
  double  a;
  double  b;
  double  c;
};

//! QQChannel is a temporary holder for QQ decay information

///
/// \class QQChannel
/// \author Lynn Garren
///
/// Temporarily keep QQ decay information in this class and convert it 
/// when we finish inputing QQ information.
///
class QQChannel  {

public:

  typedef std::vector<std::string>       SringVect;
  typedef std::vector<QQhelicity>        HelVect;
  typedef std::vector<QQAngularHelicity> AngHelVect;

  // -- constructors
  QQChannel();
  ~QQChannel();

  // ---  copying:
  //
  void  swap ( QQChannel & rhs );
  QQChannel( const QQChannel & orig );
  QQChannel & operator = ( const QQChannel & rhs );

  // --- mutators
  //
  /// add a decay particle to the list
  void addDaughter( std::string nm )           { itsDaughters.push_back( nm ); }
  /// add helicity information
  void addHelicity( QQhelicity hel )           { itsHelicity.push_back( hel ); }
  /// add angular helicity information
  void addAngHelicity( QQAngularHelicity hel ) { itsAngularHelicity.push_back( hel ); }
  /// change the decay matrix code
  void setMatrixCode( std::string & m )        { itsMatrixCode = m; }
  /// change the branching fraction
  void setBranchingFraction( double bf )       { itsBranchingFraction = bf; }
  /// change sin(phi)
  void setSinPhi( double s )                   { itsSinPhi = s; }
  /// change the decay matrix information
  void setMatrix( QQmatrix m )                 { itsMatrix = m; }
  /// change the CPT tag
  void setCPTag( )                             { itsCPTag = true; }
  /// clear this channel
  void clear();
  /// add helicity information
  void addHelicity( std::istringstream & thisline );
  /// add angular helicity information
  void addAngHelicity( std::istringstream & thisline );
  /// parse a QQ decay channel line
  void parse( std::istringstream & thisline );

  // --- accessors
  //
  /// get the CPT tag
  bool              cpt( )               const { return itsCPTag; }
  /// get the matrix code
  std::string       matrixCode( )        const { return itsMatrixCode; }
  /// get the branching fraction
  double            branchingFraction( ) const { return itsBranchingFraction; }
  /// get sin(phi)
  double            sinPhi( )            const { return itsSinPhi; }
  /// get the name of this daughter
  std::string       daughter( int i )    const { return itsDaughters[i]; }
  /// get helicity information
  QQhelicity        helicity( int i )    const { return itsHelicity[i]; }
  /// get angular helicity information
  QQAngularHelicity angHelicity( int i ) const { return itsAngularHelicity[i]; }
  /// how many decay particles in this channel?
  int               sizeDtr()            const { return itsDaughters.size(); }
  /// how many helicity entries in this channel?
  int               sizeHel()            const { return itsHelicity.size(); }
  /// how many angular helicity entries in this channel?
  int               sizeAngHel()         const { return itsAngularHelicity.size(); }
  
  /// use for diagnostics
  void write( std::ostream & os ) const;	// intended for diagnostic use


private:

  std::string itsMatrixCode;
  double      itsBranchingFraction;
  double      itsSinPhi;
  QQmatrix    itsMatrix;
  SringVect   itsDaughters;
  HelVect     itsHelicity;
  AngHelVect  itsAngularHelicity;
  bool        itsCPTag;

};  // QQChannel

inline void swap( QQChannel & first, QQChannel & second ) {
  first.swap( second );
}

}  // namespace HepPDT

#endif // QQCHANNEL_HH
