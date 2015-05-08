import FWCore.ParameterSet.Config as cms

process = cms.Process("L1ConfigWritePayloadDummy")
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cout.placeholder = cms.untracked.bool(False)
process.MessageLogger.cout.threshold = cms.untracked.string('DEBUG')
process.MessageLogger.debugModules = cms.untracked.vstring('*')

process.source = cms.Source("EmptySource")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )

from CondCore.DBCommon.CondDBSetup_cfi import CondDBSetup
process.l1conddb = cms.ESSource("PoolDBESSource",
       CondDBSetup,
       connect = cms.string('sqlite_file:l1config.db'),
       toGet   = cms.VPSet(
            cms.PSet(
                 record = cms.string('L1HfRingEtScaleRcd'),
                 tag = cms.string("L1HfRingEtScaleRcd_len1")
            ),
            cms.PSet(
                 record = cms.string('L1HtMissScaleRcd'),
                 tag = cms.string("L1HtMissScale_len1")
            )
       )
)
process.prefer("l1conddb")

process.l1sr = cms.EDAnalyzer("L1ScalesReader")

process.p = cms.Path(process.l1sr)
