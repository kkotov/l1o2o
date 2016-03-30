import FWCore.ParameterSet.Config as cms

from L1TriggerConfig.L1TMuonOverlapParamsProducers.L1TMuonOverlapObjectKeysOnline_cfi import *

L1TMuonOverlapParamsOnlineProd = cms.ESProducer("L1TMuonOverlapParamsOnlineProd",
    onlineAuthentication = cms.string('.'),
    forceGeneration = cms.bool(False),
    onlineDB = cms.string('oracle://CMS_OMDS_LB/CMS_TRG_R')
)
