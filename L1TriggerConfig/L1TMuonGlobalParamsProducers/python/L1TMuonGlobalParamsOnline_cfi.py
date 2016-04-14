import FWCore.ParameterSet.Config as cms

from L1TriggerConfig.L1TMuonGlobalParamsProducers.L1TMuonGlobalObjectKeysOnline_cfi import *

L1TMuonGlobalParamsOnlineProd = cms.ESProducer("L1TMuonGlobalParamsOnlineProd",
    onlineAuthentication = cms.string('.'),
    forceGeneration = cms.bool(False),
    onlineDB = cms.string('oracle://CMS_OMDS_LB/CMS_TRG_R')
)
