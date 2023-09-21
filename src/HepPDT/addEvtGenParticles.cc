// ----------------------------------------------------------------------
//
// addEvtGenParticles.cc
// Author: Lynn Garren
//
// this has the functions used by addEvtGenParticles
//
// ----------------------------------------------------------------------

#include <string>
#include <algorithm>	// min()
#include <iostream>
#include <sstream>

#include "HepPDT/defs.h"
#include "HepPDT/TableBuilder.hh"
#include "HepPDT/TempParticleData.hh"

namespace HepPDT {

bool getEvtGenLineType( std::string & ltype, int & id, std::string & name, const std::string & pdline );
void parseEvtGenLine( TempParticleData & tpd, const std::string & pdline );
void parseEvtGenAlias( TempAliasData & tad, const std::string & pdline );
bool parseEvtGenDecayLine( TempParticleData & tpd, const std::string & pdline );
bool parseEvtGenAliasDecayLine( TempAliasData & tad, const std::string & pdline );
TempDecayData getEvtGenDecay( const std::string & pdline );
void parseEvtGenConj( std::string & cname, const std::string & pdline );
void parseEvtGenDefinition( std::string & def, double & val, const std::string & pdline );
void findDecayModel( TempParticleData & tpd, TableBuilder & tb );
void findAliasDecayModel( TempAliasData & tad, TableBuilder & tb );

bool  addEvtGenParticles( std::istream & pdfile, TableBuilder & tb )
{ 
  std::string pdline, ltype, def, name, cname;
  int id, eid;
  double val;
  TempAliasData tad;
  // get definition table
  DefTable & dt = tb.definitions();
  // read and parse each line
  while( std::getline( pdfile, pdline) ) {
    if( getEvtGenLineType( ltype, eid, name, pdline ) ) {
      if( ltype == "add" ) {
          // this is a new particle definition
          id = HepPID::translateEvtGentoPDT( eid );
          TempParticleData& tpd = tb.getParticleData( ParticleID( id ) );
          parseEvtGenLine( tpd, pdline );
	  tb.addParticle( tpd );
      } else if( ltype=="Define" ) {
          // EvtGen definition
          parseEvtGenDefinition( def, val, pdline );
          dt.addDefinition( def, val );
      } else if( ltype=="Alias" ) {
          // EvtGen alias information
	  TempAliasData ntad;
	  parseEvtGenAlias( ntad, pdline );
	  tb.addAlias( ntad );
      } else if( ltype=="sets" ) {
          // put something here
      } else if( ltype=="ChargeConj" ) {
          // EvtGen charge conjugate alias
	  if( tb.hasAlias( name ) ) {
	      parseEvtGenConj( cname, pdline );
              tad = tb.aliasData( name );
	      tad.tempChargeConj = cname;
	  } else {
	      std::cout << "HepPDT TableBuilder: " << name << " is not an alias" << std::endl;
	  }
      } else if( ltype=="Decay" ) {
          // EvtGen assumes that all particles have been defined before
          // they are used in the decay table
	  if( tb.hasParticleData( name ) ) {
              TempParticleData& tpd = tb.getParticleData( name );
	      // read lines until we reach an "Enddecay"
	      while( parseEvtGenDecayLine( tpd, pdline ) ) {
        	  std::getline( pdfile, pdline);
	      }
	      // now sort out the decay information
	      findDecayModel( tpd, tb );
	  } else if( tb.hasAlias( name ) ) {
              // alias decays are maintained separately in temporary storage
              tad = tb.aliasData( name );
	      // read lines until we reach an "Enddecay"
	      while( parseEvtGenAliasDecayLine( tad, pdline ) ) {
        	  std::getline( pdfile, pdline);
	      }
	  } else {
	      std::cout << "HepPDT TableBuilder: could not match name " << name << std::endl;
	  }
      } else if( ltype=="CDecay" ) {
          // have to generate a charge conjugate decay table
      } else if( ltype=="JetSetPar" ) {
          // put something here
      } else if( ltype=="yesPhotos" ) {
          // put something here
      } else if( ltype=="yesIncoherentB0Mixing" ) {
          // put something here
      } else if( ltype=="yesIncoherentBsMixing" ) {
          // put something here
      } else if( ltype=="ModelAlias" ) {
          // put something here
      } else if( ltype=="SetLineshapePW" ) {
          // put something here
      } else {
         std::cout << "addEvtGenParticles: unrecognized line type " << ltype << std::endl;
      }
    }
  }
  std::cout << "found " << tb.size() << " particles and " 
                   << tb.aliasSize() << " aliases" << std::endl;
  // dt.writeDefinitions();
  return true;
}

void findDecayModel( TempParticleData & tpd, TableBuilder & tb )
{
    unsigned int cit, it, ddend, iend, psize, gmore;
    std::string name;
    for( cit=0; cit < tpd.tempDecayList.size(); ++cit ) {
        TempDecayData & tdd = tpd.tempDecayList[cit];
	ddend = 0;
	psize = tdd.tempDaughterList.size();
        if( psize > 0 ) {
	    gmore = 0;
	    for( it=0; it < tdd.tempDaughterList.size(); ++it ) {
		name = tdd.tempDaughterList[it];
		if( tb.hasParticleData( name ) || tb.hasAlias( name ) ) {
		} else if( ddend == 0 ) {
	            // first item that is not a daughter - must be the model name
		    // complication - photos models have two names
		    if( name == "PHOTOS" ) {
			gmore = 1;
	                tdd.tempDecayName = name;
		    } else if ( gmore == 1 ) {
		        ddend = it;
	                tdd.tempDecayName += ' ';
	                tdd.tempDecayName += name;
		    } else {
		        ddend = it;
	                tdd.tempDecayName = name;
		    }
		} else {
	            // anything here is a decay parameter
		    if( tb.hasDefinition( name ) ) {
			tdd.tempDecayParameters.push_back( tb.definition( name ) );
		    } else {
			tdd.tempDecayParameters.push_back( stringtodouble( name ) );
		    }
		}
	    }
	    // now clear out the parameters and model name
	    iend = tdd.tempDaughterList.size() - 1;
	    for( it = iend; it > ddend; --it ) {
		tdd.tempDaughterList.pop_back();
	    }
	}
    }
}

void findAliasDecayModel( TempAliasData & tad, TableBuilder & tb )
{
    unsigned int cit, it, ddend, iend, psize, gmore;
    std::string name;
    for( cit=0; cit < tad.tempAliasDecayList.size(); ++cit ) {
        TempDecayData & tdd = tad.tempAliasDecayList[cit];
	ddend = 0;
	psize = tdd.tempDaughterList.size();
        if( psize > 0 ) {
	    gmore = 0;
	    for( it=0; it < tdd.tempDaughterList.size(); ++it ) {
		name = tdd.tempDaughterList[it];
		if( tb.hasParticleData( name ) || tb.hasAlias( name ) ) {
		} else if( ddend == 0 ) {
		    // first item that is not a daughter - must be the model name
		    // complication - photos models have two names
		    if( name == "PHOTOS" ) {
			gmore = 1;
	                tdd.tempDecayName = name;
		    } else if ( gmore == 1 ) {
		        ddend = it;
	                tdd.tempDecayName += ' ';
	                tdd.tempDecayName += name;
		    } else {
		        ddend = it;
	                tdd.tempDecayName = name;
		    }
		} else {
		    // anything here is a decay parameter
		    if( tb.hasDefinition( name ) ) {
			tdd.tempDecayParameters.push_back( tb.definition( name ) );
		    } else {
			tdd.tempDecayParameters.push_back( stringtodouble( name ) );
		    }
		}
	    }
	    // now clear out the parameters and model name
	    iend = tdd.tempDaughterList.size() - 1;
	    for( it = iend; it > ddend; --it ) {
		tdd.tempDaughterList.pop_back();
	    }
	}
    }
}

bool getEvtGenLineType( std::string & ltype, int & id, std::string & name, const std::string & pdline )
{
    std::string s1, s2;
    int sl = pdline.length();
    std::string firstc = pdline.substr(0,1);
    id = 0;
    name = "";
    ltype = "";
    // check for comments
    if( firstc == "*" || firstc == "#" ) { return false; }
    // check for empty lines
    if( sl <= 5 ){ return false; }
    // a # may be anywhere on the line
    std::istringstream thisline( pdline.substr(0,sl).c_str() );
    thisline >> ltype;
    if( ltype == "#" ) { // blanks are allowed before the #
        return false;
    } else if( ltype == "add" ) {
        thisline >> s1 >> s2 >> name >> id;
    } else if( ltype=="Alias" ) {
        thisline >> name;
    } else if( ltype=="ChargeConj" ) {
        thisline >> name;
    } else if( ltype == "Decay" ) {
        thisline >> name;
    } else if( ltype == "CDecay" ) {
        thisline >> name;
    }
    return true;
}

void parseEvtGenLine( TempParticleData & tpd, const std::string & pdline )
{
    // this line defines a particle
    std::string s1, s2, ltype, name;
    int id, chg, spin, lid;
    double mass, width, wcut, lifet, dspin;
    
    // check for valid TempParticleData
    if( tpd.tempID.pid() == 0 ) { return; }
    // have a valid PID, so proceed
    int sl = pdline.length();
    std::istringstream thisline( pdline.substr(0,sl).c_str() );
    thisline >> ltype >> s1 >> s2 >> name >> id >> mass >> width >> wcut 
             >> chg >> spin >> lifet >> lid;
    // std::cout << ltype << " " << s1 << " " << s2 << " " << id << " " << name 
    //      << " " << chg << " " << spin <<  " " << mass << " " << width << " " 
    //      << wcut << " " << lifet <<  " " << lid << std::endl;
    if( ltype != "add" ) { 
        std::cout << "called parseEvtGenLine with wrong line type" << std::endl;
        return; 
    }
    tpd.tempParticleName = name;
    tpd.tempSource = "EvtGen";
    tpd.tempOriginalID = id;
    tpd.tempCharge = double(chg)/3.0;
    tpd.tempMass = Measurement( mass, 0.0 );
    tpd.tempHighCutoff = wcut;
    tpd.tempWidth = Measurement( calculateWidthFromLifetime( lifet ), 0.0 );
    dspin = double(spin)/2.;
    if( tpd.tempSpin.totalSpin() != dspin ) {
        // std::cout << "EvtGen spin " << dspin << " does not match ParticleID spin " 
	//      << tpd.tempSpin.totalSpin() << std::endl;
	tpd.tempSpin.setTotalSpin( dspin );
    }
}

bool parseEvtGenDecayLine( TempParticleData & tpd, const std::string & pdline )
{
    std::string ltype;
    // check for valid TempParticleData
    if( tpd.tempID.pid() == 0 ) { return false; }
    // have a valid PID, so proceed
    int sl = pdline.length();
    // check for empty lines
    if( sl < 5 ) { return true; }
    std::istringstream thisline( pdline.substr(0,sl).c_str() );
    // better check for comments and blank lines.....
    std::string firstc = pdline.substr(0,1);
    if( firstc == "*" || firstc == "#" || firstc == ";" ) { return true; }
    // check line type
    thisline >> ltype;
    if( ltype == "#" ) { // blanks are allowed before the #
        return true;
    } else if( ltype == "Decay" ) {
        // begin decay
	return true;
    } else if( ltype == "" ) {
        // blank line with white space
	return true;
    } else if( ltype == "Enddecay" ) {
        // end decay
	return false;
    }
    // this is a good decay line
    TempDecayData tempdd = getEvtGenDecay( pdline );
    tpd.tempDecayList.push_back( tempdd );
    return true;
}

TempDecayData getEvtGenDecay( const std::string & pdline )
{
    std::string dname = "";
    TempDecayData tdd;
    // unpack decay type and brancing fraction
    int sl = pdline.length();
    int semicol = pdline.find(';');
    if( semicol > 0 ) { sl = std::min( sl, semicol ); }
    std::istringstream thisline( pdline.substr(0,sl).c_str() );
    thisline >> tdd.tempBranchingFraction;
    while ( !thisline.eof() ) {
        thisline >> dname; 
        // this list will be parsed later for decay model and decay parameters
        tdd.tempDaughterList.push_back( dname );
	// std::cout << dname << " " ;
    }
    // std::cout << std::endl;
    return tdd;
}

bool parseEvtGenAliasDecayLine( TempAliasData & tad, const std::string & pdline )
{
    std::string ltype;
    int sl = pdline.length();
    std::istringstream thisline( pdline.substr(0,sl).c_str() );
    // better check for comments and blank lines.....
    std::string firstc = pdline.substr(0,1);
    if( firstc == "*" || firstc == "#" ) { return true; }
    // check line type
    thisline >> ltype;
    if( ltype == "#" ) { // blanks are allowed before the #
        return true;
    } else if( ltype == "Decay" ) {
        // begin decay
	return true;
    } else if( ltype == "Enddecay" ) {
        // end decay
	return false;
    }
    // this is a good decay line
    TempDecayData tempdd = getEvtGenDecay( pdline );
    tad.tempAliasDecayList.push_back( tempdd );
    return true;
}

void parseEvtGenAlias( TempAliasData & tad, const std::string & pdline )
{
    // this line defines a particle alias
    std::string ltype, alias, name;
    
    int sl = pdline.length();
    std::istringstream thisline( pdline.substr(0,sl).c_str() );
    thisline >> ltype >> alias >> name;
    // std::cout << ltype << " " << alias << " " << name << std::endl;
    if( ltype != "Alias" ) { 
        std::cout << "called parseEvtGenAlias with wrong line type: " << ltype << std::endl;
        return; 
    }
    tad.tempAlias = alias;
    tad.tempAliasedParticle = name;
}

void parseEvtGenConj( std::string & cname, const std::string & pdline )
{
    std::string ltype, alias;
    
    int sl = pdline.length();
    std::istringstream thisline( pdline.substr(0,sl).c_str() );
    thisline >> ltype >> alias >> cname;
    // std::cout << ltype << " " << alias << " " << cname << std::endl;
    if( ltype != "ChargeConj" ) { 
        std::cout << "called parseEvtGenConj with wrong line type: " << ltype << std::endl;
        cname = "";
        return; 
    }
}

void parseEvtGenDefinition( std::string & def, double & val, const std::string & pdline )
{
    std::string ltype;
    
    int sl = pdline.length();
    std::istringstream thisline( pdline.substr(0,sl).c_str() );
    thisline >> ltype >> def >> val;
    // std::cout << ltype << " " << def << " " << val << std::endl;
    if( ltype != "Define" ) { 
        std::cout << "called parseEvtGenDefinition with wrong line type: " << ltype << std::endl;
        val = 0.0;
	def = "";
    }
}

}	// HepPDT
