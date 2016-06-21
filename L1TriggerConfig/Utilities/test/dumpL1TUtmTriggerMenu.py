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
                 'sqlite_file:l1config.db', #default value
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

# Generate the parent L1TriggerKey 
process.load("CondTools.L1TriggerExt.L1TriggerKeyDummyExt_cff")
process.L1TriggerKeyDummyExt.tscKey = cms.string('dummyL1TUtmTriggerMenu')
process.L1TriggerKeyDummyExt.label  = cms.string('SubsystemKeysOnly')
process.L1TriggerKeyDummyExt.uGTKey = cms.string(options.objectKey)
# Using the parent L1TriggerKey trigger generation of system specific (labeled) L1TriggerKeys and pack them the main (unlabeled) L1TriggerKey (just one subsystem here)
process.load("CondTools.L1TriggerExt.L1TriggerKeyOnlineExt_cfi")
process.L1TriggerKeyOnlineExt.subsystemLabels = cms.vstring('uGT')
# Include the uGT specific key ESProducer (generates uGT labeled L1TriggerKey) and the corresponding payload ESProduced
process.load("L1TriggerConfig.L1TUtmTriggerMenuProducers.L1TUtmTriggerMenuObjectKeysOnline_cfi")
process.load("L1TriggerConfig.L1TUtmTriggerMenuProducers.L1TUtmTriggerMenuOnline_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )
process.source = cms.Source("EmptySource")

process.l1cr = cms.EDAnalyzer( "L1TriggerKeyExtReader", label = cms.string("uGT") )
# label = cms.string("SubsystemKeysOnly") )

process.getter = cms.EDAnalyzer("EventSetupRecordDataGetter",
   toGet = cms.VPSet(cms.PSet(
       record = cms.string('L1TUtmTriggerMenuO2ORcd'),
       data   = cms.vstring('L1TUtmTriggerMenu')
   )),
   verbose = cms.untracked.bool(True)
)

process.l1mw = cms.EDAnalyzer("L1MenuWriter")

from CondCore.DBCommon.CondDBSetup_cfi import CondDBSetup
outputDB = cms.Service("PoolDBOutputService",
    CondDBSetup,
    connect = cms.string(options.outputDBConnect),
    toPut   = cms.VPSet(
        cms.PSet(
            record = cms.string('L1TUtmTriggerMenuO2ORcd'),
            tag = cms.string('L1TUtmTriggerMenu_Stage2v0_hlt')
        ),
        cms.PSet(
            record = cms.string("L1TriggerKeyListExtRcd"),
            tag = cms.string("L1TriggerKeyListExt_Stage2v0_hlt")
        )
    )
)

outputDB.DBParameters.authenticationPath = options.outputDBAuth # cms.untracked.string("./o2o/")
process.add_(outputDB)

#process.p = cms.Path(process.l1cr)
process.p = cms.Path(process.getter + process.l1mw)

