import FWCore.ParameterSet.Config as cms

from L1TriggerConfig.L1TMuonEndcapParamsProducers.L1TMuonEndcapObjectKeysOnline_cfi import *

L1TMuonEndcapParamsOnlineProd = cms.ESProducer("L1TMuonEndcapParamsOnlineProd",
    onlineAuthentication = cms.string('.'),
    forceGeneration = cms.bool(False),
    onlineDB = cms.string('oracle://CMS_OMDS_LB/CMS_TRG_R')
)
