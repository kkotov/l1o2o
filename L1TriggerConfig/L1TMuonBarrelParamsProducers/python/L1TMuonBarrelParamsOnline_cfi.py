import FWCore.ParameterSet.Config as cms

from L1TriggerConfig.L1TMuonBarrelParamsProducers.L1TMuonBarrelObjectKeysOnline_cfi import *

L1TMuonBarellParamsOnlineProd = cms.ESProducer("L1TMuonBarrelParamsOnlineProd",
    onlineAuthentication = cms.string('.'),
    forceGeneration = cms.bool(False),
    onlineDB = cms.string('oracle://CMS_OMDS_LB/CMS_TRG_R')
)
