// ----------------------------------------------------------------------
//
// ParticleDataTable.cc
// Author: Lynn Garren, Walter Brown
//
// ----------------------------------------------------------------------

#include <iostream>
#include <string>
#include <map>
#include <list>

#include "HepPDT/defs.h"
#include "HepPDT/ParticleDataTable.hh"

namespace HepPDT {

void ParticleDataTable::writeParticleData( std::ostream & outstr )
{
  // write header
  outstr << std::endl;
  outstr << "HepPDT-ParticleDataTable-begin" << std::endl;
  outstr << "             *****  ParticleDataTable  *****" << std::endl;
  writeVersion( outstr );
  outstr << "             Table Name : " << tableName() << std::endl;
  outstr << "                  ( " << size() << " entries )" << std::endl;
  outstr << "PARTICLE NAME                 ID  CHARGE COLOR"
         << " SPIN: J  S   L"
	 << "  MASS"
	 << "                       WIDTH"
	 << "                    LOW CUT    HIGH CUT"
	 << "      LIFETIME"
         << std::endl;  
  // write particle info
  const_iterator cit;
  for( cit=begin(); cit != end(); ++cit ) {
    const ParticleData & pd = cit->second;
    pd.write( outstr );
  }
  outstr << "HepPDT-ParticleDataTable-end" << std::endl;
  return;
}

void ParticleDataTable::writeParticleInfo( std::ostream & outstr )
{
  // write header
  outstr << std::endl;
  outstr << "HepPDT-ParticleDataTable-Particle-Information-begin" << std::endl;
  outstr << "             *****  ParticleDataTable  *****" << std::endl;
  writeVersion( outstr );
  outstr << "             Table Name : " << tableName() << std::endl;
  outstr << "                  ( " << size() << " entries )" << std::endl;
  outstr << "PARTICLE NAME                 ID  CHARGE COLOR"
         << " SPIN: J  S   L"
	 << "  MASS"
	 << "                       WIDTH"
	 << "                    LOW CUT    HIGH CUT"
	 << "      LIFETIME"
         << std::endl;  
  // write particle info
  const_iterator cit;
  for( cit=begin(); cit != end(); ++cit ) {
    const ParticleData & pd = cit->second;
    pd.writeParticleInfo( outstr );
  }
  outstr << "HepPDT-ParticleDataTable-Particle-Information-end" << std::endl;
  return;
}

void ParticleDataTable::writeParticleTranslation( std::ostream & outstr )
{
  // write particle info
  const_iterator cit;
  for( cit=begin(); cit != end(); ++cit ) {
    const ParticleData & pd = cit->second;
    pd.writeParticleTranslation( outstr );
  }
  return;
}

void ParticleDataTable::writeParticleStatus( std::ostream & os )
{
  /// This routine writes the particle name, ID, charge, mass, width, 
  /// lifetime, and the results of isStable().
  // write header
  os << std::endl;
  os << "HepPDT-Particle-Status-begin" << std::endl;
  os << "         HepPDT Version : " << versionName()  << std::endl;
  os << "             Table Name : " << tableName()
     << " ( " << size() << " entries )" << std::endl;
  os << "         ID NAME                   MASS"
	 << "          WIDTH"
	 << "        LIFETIME"
	 << "    STABLE?"
         << std::endl;  
  // write particle info
  const_iterator cit;
  for( cit=begin(); cit != end(); ++cit ) {
    const ParticleData & pd = cit->second;
    int il = pd.name().length();
    os.width(11);
    os <<  pd.pid() << " ";
    os << pd.name() ;
    // pad the name
    int pad;
    for( pad = 0; pad < 21 - il; ++pad ) {
        os << " " ;
    }
    os.width(13);
    os.precision(5);
    os.setf(std::ios::scientific, std::ios::floatfield);
    os << pd.mass().value();
    os.width(13);
    os.precision(4);
    os << pd.totalWidth().value();
    os.width(13);
    os.precision(4);
    os << pd.lifetime().value();
    if( pd.isStable() ) { 
        os << "  stable";
    } else {
        os << "  decays";
    }
    // return to default settings
    os.precision(6);
    os.setf(std::ios::fmtflags(0), std::ios::floatfield);
    // end the line
    os << std::endl;
  }
  os << "HepPDT-Particle-Status-end" << std::endl;
  return;
}

ParticleData * ParticleDataTable::particle( ParticleID key )
{ 
  iterator it;
  it = itsMap.find( key );
  if( it != itsMap.end() ) {
    return & it->second;
  } else {
    // call special lookup function and return that value
    return DealWithUnknownID(key);
  }
}

ParticleData const * ParticleDataTable::particle( ParticleID key ) const
{ 
  const_iterator cit;
  //int id = key.pid();
  cit = itsMap.find( key );
  if( cit != itsMap.end() ) {
    return & cit->second;
  } else {
    // call special lookup function and return that value
    return DealWithUnknownID(key);
  }
}

ParticleData * ParticleDataTable::DealWithUnknownID( ParticleID & key ) const
{
  // call special lookup function and return that value
  CommonParticleData * cpd = itsProcessUnknownID->callProcessUnknownID( key, *this );
  if( !cpd ) return 0;
  // have the CPD, now create the PD
  CPDID cid = addParticleData(*cpd);
  // a ParticleData will ALWAYS have a DecayData, which can be empty
  // The first DDID in the list will be an empty DecayData 
  // (see the convertTemporaryMap code)
  DDID edid = itsDDlist.begin();
  // there is no decay information for this ParticleData
  ParticleData * pd = new ParticleData( cid, edid );
  addParticle( *pd );
  ParticleID id = pd->ID();
  // cleanup of temporarys
  delete pd;
  delete cpd;
  // find the real pd
  return & itsMap.find( id )->second;
}

ParticleData * ParticleDataTable::particle( std::string nkey)
{ 
  nameIterator it = itsNameMap.find( nkey );
  if( it != itsNameMap.end() ) {
    return  particle(it->second);
  } else {
    //std::cerr << "cannot find particle " << nkey << " in map" << std::endl;
    return 0;
  }
}

ParticleData const * ParticleDataTable::particle( std::string nkey ) const
{ 
  const_iteratorByName cit = itsNameMap.find( nkey );
  if( cit != itsNameMap.end() ) {
    return particle(cit->second);
  } else {
    //std::cerr << "cannot find particle " << nkey << " in map" << std::endl;
    return 0;
  }
}

ParticleDataTable::DDID ParticleDataTable::addDecayData( DecayData const d )
{
  itsDDlist.push_back( d );
  DDID it = itsDDlist.end();
  --it;
  return it;
}

ParticleDataTable::CPDID ParticleDataTable::addParticleData( CPD const d ) const
{
  itsCPDlist.push_back( d );
  CPDID it = itsCPDlist.end();
  --it;
  return it;
}

void ParticleDataTable::addParticle( ParticleData const & p ) const
{
  // private method
  ParticleID id=p.ID();
  //std::string nid(p.name());
  itsMap.insert( std::make_pair( id, p )); 
  itsNameMap.insert( std::make_pair( p.name(), id )); 
}

}	// HepPDT
