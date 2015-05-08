import FWCore.ParameterSet.Config as cms

process = cms.Process("L1ConfigWritePayloadDummy")
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cout.placeholder = cms.untracked.bool(False)
process.MessageLogger.cout.threshold = cms.untracked.string('DEBUG')
process.MessageLogger.debugModules = cms.untracked.vstring('*')

process.source = cms.Source("EmptySource")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )

# Generate dummy L1TriggerKeyList
process.load("CondTools.L1Trigger.L1TriggerKeyListDummy_cff")
process.load("CondTools.L1Trigger.L1TriggerKeyDummy_cff")
process.L1TriggerKeyDummy.objectKeys = cms.VPSet(
    cms.PSet(
        record = cms.string("L1HfRingEtScaleRcd"),
        type   = cms.string("L1CaloEtScale"),
        key    = cms.string("dummy")
    ),
    cms.PSet(
        record = cms.string("L1HtMissScaleRcd"),
        type   = cms.string("L1CaloEtScale"),
        key    = cms.string("dummy")
    )
)

process.load("L1TriggerConfig.L1ScalesProducers.l1CaloScales_cfi")
process.prefer("l1CaloScales") 

process.l1sw = cms.EDAnalyzer("L1ScalesWriter")

from CondCore.DBCommon.CondDBSetup_cfi import CondDBSetup
outputDB = cms.Service("PoolDBOutputService",
                       CondDBSetup,
                       connect = cms.string('sqlite_file:l1config.db'),
                       toPut   = cms.VPSet(
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
outputDB.DBParameters.authenticationPath = '.'
process.add_(outputDB)

process.p = cms.Path(process.l1sw)
