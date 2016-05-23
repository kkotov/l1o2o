import FWCore.ParameterSet.Config as cms

L1TGlobalPrescalesVetosOnline = cms.ESProducer("L1TGlobalPrescalesVetosOnlineProd",
    onlineAuthentication = cms.string('.'),
    forceGeneration = cms.bool(False),
    onlineDB = cms.string('oracle://CMS_OMDS_LB/CMS_TRG_R')
)
