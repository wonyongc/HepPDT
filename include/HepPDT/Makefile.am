## Process this file with automake to produce Makefile.in

if USE_GMAKE
  MAKE = gmake
endif

pkgincludedir = $(prefix)/include/HepPDT
COPY_P = @COPY_P@

pkginclude_HEADERS = 		\
	CommonParticleData.hh	\
	CommonParticleData.icc	\
	Constituent.hh		\
	DecayChannel.hh		\
	DecayChannel.icc	\
	DecayData.hh		\
	DecayData.icc		\
	DefTable.hh		\
	HeavyIonUnknownID.hh	\
	Measurement.hh		\
	Measurement.icc		\
	ParticleID.hh		\
	ParticleID.icc		\
	ParticleData.hh		\
	ParticleData.icc	\
	ParticleDataTable.hh	\
	ParticleDataTable.icc	\
	ParticleDataTableComparison.hh	\
	ProcessUnknownID.hh	\
	ResonanceStructure.hh	\
	QQChannel.hh		\
	QQDecay.hh		\
	SimpleProcessUnknownID.hh	\
	SpinState.hh		\
	SpinState.icc		\
	stringtodouble.hh	\
	TableBuilder.hh		\
	TableBuilder.icc	\
	TempParticleData.hh	\
	Version.hh		\
	defs.h

# Identify generated file(s) to be removed when 'make clean' is requested:
CLEANFILES = defs.h
