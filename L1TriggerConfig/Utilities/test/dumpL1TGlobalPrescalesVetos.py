# to test the communication with DBS and produce the csctf configuration
import FWCore.ParameterSet.Config as cms

process = cms.Process("QWE")
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cout.placeholder = cms.untracked.bool(False)
process.MessageLogger.cout.threshold = cms.untracked.string('INFO')
process.MessageLogger.debugModules = cms.untracked.vstring('*')

import FWCore.ParameterSet.VarParsing as VarParsing
options = VarParsing.VarParsing()
options.register('objectKey',
                 'dummy', #default value
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.string,
                 "object key")
options.register('outputDBConnect',
                 'sqlite_file:./o2o/l1config.db', #default value
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.string,
                 "Connection string for output DB")
options.register('outputDBAuth',
                 '.', #default value
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.string,
                 "Authentication path for outputDB")
options.parseArguments()


# Generate dummy L1TriggerKeyList
process.load("CondTools.L1TriggerExt.L1TriggerKeyListDummyExt_cff")
process.load("L1TriggerConfig.L1TGlobalPrescalesVetosProducers.L1TGlobalPrescalesVetosOnline_cfi")

# Generate dummy L1TriggerKeyList
process.load("CondTools.L1TriggerExt.L1TriggerKeyDummyExt_cff")
process.L1TriggerKeyDummyExt.tscKey = cms.string('dummyL1TGlobalPrescalesVetos')
process.L1TriggerKeyDummyExt.objectKeys = cms.VPSet(
    cms.PSet(
        record = cms.string('L1TGlobalPrescalesVetosO2ORcd'),
        type = cms.string('L1TGlobalPrescalesVetos'),
        key = cms.string(options.objectKey)
    )
)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )
process.source = cms.Source("EmptySource")


process.getter = cms.EDAnalyzer("EventSetupRecordDataGetter",
   toGet = cms.VPSet(cms.PSet(
       record = cms.string('L1TGlobalPrescalesVetosO2ORcd'),
       data   = cms.vstring('L1TGlobalPrescalesVetos')
   )),
   verbose = cms.untracked.bool(True)
)

process.l1pvw = cms.EDAnalyzer("L1TGlobalPrescalesVetosWriter")

from CondCore.DBCommon.CondDBSetup_cfi import CondDBSetup
outputDB = cms.Service("PoolDBOutputService",
    CondDBSetup,
    connect = cms.string(options.outputDBConnect),
    toPut   = cms.VPSet(
        cms.PSet(
            record = cms.string('L1TGlobalPrescalesVetosO2ORcd'),
            tag = cms.string(options.objectKey)
        ),
        cms.PSet(
            record = cms.string("L1TriggerKeyListExtRcd"),
            tag = cms.string("L1TriggerKeyListExt_Stage2v0_hlt")
        )
    )
)

outputDB.DBParameters.authenticationPath = '.'
process.add_(outputDB)

process.p = cms.Path(process.getter + process.l1pvw)

