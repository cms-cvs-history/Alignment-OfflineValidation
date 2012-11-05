import FWCore.ParameterSet.Config as cms

process = cms.Process("TEST")

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = "FT_R_53_V6C::All" 

process.load("Geometry.TrackerNumberingBuilder.trackerNumberingGeometry_cfi")
process.load("Geometry.CMSCommonData.cmsIdealGeometryXML_cff")
process.load("Geometry.TrackerGeometryBuilder.trackerGeometry_cfi")


process.load("Alignment.OfflineValidation.TrackerGeometryCompare_cfi")

process.load("CondCore.DBCommon.CondDBSetup_cfi")

process.MessageLogger = cms.Service("MessageLogger",
    destinations = cms.untracked.vstring('detailedInfo', 
        'cout')
)

process.source = cms.Source("EmptySource")

process.DQMStore=cms.Service("DQMStore")
process.TkDetMap = cms.Service("TkDetMap")
process.SiStripDetInfoFileReader = cms.Service("SiStripDetInfoFileReader")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1)
)
process.p = cms.Path(process.TrkGeomDeformCompare)

process.TrkGeomDeformCompare.inputROOTFile1 = 'myInputGeometry_RefGeometry.root' 

process.TrkGeomDeformCompare.inputROOTFile2 = 'myInputGeometry_2.root'
#process.TrkGeomDeformCompare.inputROOTFile2 = 'IDEAL' 

process.TrkGeomDeformCompare.outputFile = 'outputComparison_RefGeometry_2.root'

process.TFileService = cms.Service("TFileService",
		fileName = cms.string('TkSurfDeform_RefGeometry_2.root') 
		)

process.TrkGeomDeformCompare.levels = ['DetUnit']  
#process.TrkGeomDeformCompare.levels = ['Tracker','DetUnit'] 
#process.TrkGeomDeformCompare.levels = ['Tracker','TOBBarrel','TIBBarrel','TECEndcap','TECDisk']
#process.TrkGeomDeformCompare.levels = ["TPBBarrel","TPEEndcap","TIBBarrel","TIDEndcap","TOBBarrel","TECEndcap"] 

"""
process.TrkGeomDeformCompare.writeToDB = True

process.PoolDBOutputService = cms.Service("PoolDBOutputService",
   process.CondDBSetup,
   timetype = cms.untracked.string('runnumber'),
   connect = cms.string('sqlite_file:yourNewTrackerCenteredObject.db'),
   toPut = cms.VPSet(cms.PSet(
       record = cms.string('TrackerAlignmentRcd'),
       tag = cms.string('Alignments')
   ),
       cms.PSet(
           record = cms.string('TrackerAlignmentErrorRcd'),
           tag = cms.string('AlignmentErrors')
       ))
)
"""
