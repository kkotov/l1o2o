def initL1SubsystemsExt( tagBaseVec = [],
                      objectKey = 'dummy' ):

    import FWCore.ParameterSet.Config as cms
    from CondTools.L1TriggerExt.L1CondEnumExt_cfi import L1CondEnumExt

    if len( tagBaseVec ) == 0:
        from CondTools.L1TriggerExt.L1UniformTagsExt_cfi import initL1UniformTagsExt
        initL1UniformTagsExt()
        tagBaseVec = initL1UniformTagsExt.tagBaseVec

    initL1SubsystemsExt.params = cms.PSet(
        recordInfo = cms.VPSet(
        cms.PSet(
            record = cms.string('L1TUtmTriggerMenuRcd'),
            tag = cms.string('L1TUtmTriggerMenu_' + tagBaseVec[ L1CondEnumExt.L1TUtmTriggerMenu ]),
            type = cms.string('L1TUtmTriggerMenu'),
            key = cms.string(objectKey)
        ),
        cms.PSet(
            record = cms.string('L1TMuonGlobalParamsRcd'),
            tag = cms.string('L1TMuonGlobalParams_' + tagBaseVec[ L1CondEnumExt.L1TMuonGlobalParams ]),
            type = cms.string('L1TMuonGlobalParams'),
            key = cms.string(objectKey)
        ),
        cms.PSet(
            record = cms.string('L1TMuonEndcapParamsRcd'),
            tag = cms.string('L1TMuonEndcapParams_' + tagBaseVec[ L1CondEnumExt.L1TMuonEndcapParams ]),
            type = cms.string('L1TMuonEndcapParams'),
            key = cms.string(objectKey)
        ),
        cms.PSet(
            record = cms.string('L1TMuonOverlapParamsRcd'),
            tag = cms.string('L1TMuonOverlapParams_' + tagBaseVec[ L1CondEnumExt.L1TMuonOverlapParams ]),
            type = cms.string('L1TMuonOverlapParams'),
            key = cms.string(objectKey)
        ),
        cms.PSet(
            record = cms.string('L1TMuonBarrelParamsRcd'),
            tag = cms.string('L1TMuonBarrelParams_' + tagBaseVec[ L1CondEnumExt.L1TMuonBarrelParams ]),
            type = cms.string('L1TMuonBarrelParams'),
            key = cms.string(objectKey)
        )
        )
    )

    from CondTools.L1TriggerExt.L1RSSubsystemParamsExt_cfi import initL1RSSubsystemsExt
    initL1RSSubsystemsExt( tagBaseVec )
    initL1SubsystemsExt.params.recordInfo.extend(initL1RSSubsystemsExt.params.recordInfo)
