#ifndef Alignment_OfflineValidation_TrackerGeometryCompare_h
#define Alignment_OfflineValidation_TrackerGeometryCompare_h

/** \class TrackerGeometryCompare
 *
 * Module that reads survey info from DB and prints them out.
 *
 * Usage:
 *   module comparator = TrackerGeometryCompare {
 *
 *   lots of stuff  
 *
 *   }
 *   path p = { comparator }
 *
 *
 *  $Date: 2007/12/06 01:46:42 $
 *  $Revision: 1.5 $
 *  \author Nhan Tran
 */

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "Alignment/TrackerAlignment/interface/AlignableTracker.h"
#include "CondFormats/Alignment/interface/SurveyErrors.h"
#include "Alignment/CommonAlignment/interface/StructureType.h"

#include <algorithm>
#include "TTree.h"

class AlignTransform;

class TrackerGeometryCompare:
public edm::EDAnalyzer
{
public:
	typedef AlignTransform SurveyValue;
	typedef Alignments SurveyValues;
	typedef std::vector<Alignable*> Alignables;
		
  /// Do nothing. Required by framework.
  TrackerGeometryCompare(
		const edm::ParameterSet&
		);
	
  /// Read from DB and print survey info.
	virtual void beginJob(
		const edm::EventSetup&
		);

	virtual void analyze(
		const edm::Event&,
		const edm::EventSetup&
		);
	
private:


	//parameters
  edm::ParameterSet m_params;
  std::vector<align::StructureType> theLevels;
  std::vector<int> theSubDets;
	
	//compares two geometries
	void compareGeometries(Alignable* refAli, Alignable* curAli);
	//filling the ROOT file
	void fillTree(Alignable *refAli, AlgebraicVector diff);
	//converts surveyRcd into alignmentRcd
	void surveyToTracker(AlignableTracker* ali, Alignments* alignVals, AlignmentErrors* alignErrors);
	//need for conversion for surveyToTracker
	void addSurveyInfo(Alignable* ali);
	void createDBGeometry(const edm::EventSetup& iSetup);
	void createROOTGeometry(const edm::EventSetup& iSetup);
	
	AlignableTracker* referenceTracker;
	AlignableTracker* dummyTracker;
	AlignableTracker* currentTracker;

	unsigned int theSurveyIndex;
	const Alignments* theSurveyValues;
	const SurveyErrors* theSurveyErrors;
	

	std::string _inputType;
	std::string _inputFileType;
	std::string _inputFilename1;
	std::string _inputFilename2;
	std::string _inputTreename;
	
	//root configuration
	std::string _filename;
	TFile* _theFile;
	TTree* _alignTree;
	TFile* _inputRootFile1;
	TFile* _inputRootFile2;
	TTree* _inputTree1;
	TTree* _inputTree2;
	
	int _id, _level, _mid, _mlevel, _sublevel;
	float _xVal, _yVal, _zVal, _rVal, _phiVal, _alphaVal, _betaVal, _gammaVal;
	float _dxVal, _dyVal, _dzVal, _drVal, _dphiVal, _dalphaVal, _dbetaVal, _dgammaVal;
	

	
};




#endif