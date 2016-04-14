#include "FWCore/Framework/interface/MakerMacros.h"
#include "CondTools/L1TriggerExt/plugins/L1CondDBPayloadWriterExt.h"
#include "CondTools/L1TriggerExt/plugins/L1CondDBIOVWriterExt.h"
#include "CondTools/L1TriggerExt/plugins/L1TriggerKeyDummyProdExt.h"
#include "CondTools/L1TriggerExt/plugins/L1TriggerKeyListDummyProdExt.h"
#include "CondTools/L1TriggerExt/plugins/L1SubsystemKeysOnlineProdExt.h"
#include "CondTools/L1TriggerExt/plugins/L1TriggerKeyOnlineProdExt.h"


using namespace l1t;

DEFINE_FWK_MODULE(L1CondDBPayloadWriterExt);
DEFINE_FWK_MODULE(L1CondDBIOVWriterExt);
DEFINE_FWK_EVENTSETUP_MODULE(L1TriggerKeyDummyProdExt);
DEFINE_FWK_EVENTSETUP_MODULE(L1TriggerKeyListDummyProdExt);
DEFINE_FWK_EVENTSETUP_MODULE(L1SubsystemKeysOnlineProdExt);
DEFINE_FWK_EVENTSETUP_MODULE(L1TriggerKeyOnlineProdExt);

#include "CondCore/PluginSystem/interface/registration_macros.h"
#include "CondTools/L1Trigger/interface/WriterProxy.h"



// Central L1 records
#include "CondFormats/DataRecord/interface/L1TriggerKeyExtRcd.h"
#include "CondFormats/L1TObjects/interface/L1TriggerKeyExt.h"

REGISTER_L1_WRITER(L1TriggerKeyExtRcd, L1TriggerKeyExt);

#include "CondFormats/DataRecord/interface/L1TriggerKeyListExtRcd.h"
#include "CondFormats/L1TObjects/interface/L1TriggerKeyListExt.h"

REGISTER_L1_WRITER(L1TriggerKeyListExtRcd, L1TriggerKeyListExt);

// Ext Records:

#include "CondFormats/L1TObjects/interface/L1TUtmTriggerMenu.h"
#include "CondFormats/DataRecord/interface/L1TUtmTriggerMenuRcd.h"

REGISTER_L1_WRITER(L1TUtmTriggerMenuRcd, L1TUtmTriggerMenu);

#include "CondFormats/L1TObjects/interface/L1TMuonBarrelParams.h"
#include "CondFormats/DataRecord/interface/L1TMuonBarrelParamsRcd.h"

REGISTER_L1_WRITER(L1TMuonBarrelParamsRcd, L1TMuonBarrelParams);

#include "CondFormats/L1TObjects/interface/L1TMuonEndcapParams.h"
#include "CondFormats/DataRecord/interface/L1TMuonEndcapParamsRcd.h"

REGISTER_L1_WRITER(L1TMuonEndcapParamsRcd, L1TMuonEndcapParams);

#include "CondFormats/L1TObjects/interface/L1TMuonOverlapParams.h"
#include "CondFormats/DataRecord/interface/L1TMuonOverlapParamsRcd.h"

REGISTER_L1_WRITER(L1TMuonOverlapParamsRcd, L1TMuonOverlapParams);

#include "CondFormats/L1TObjects/interface/L1TMuonGlobalParams.h"
#include "CondFormats/DataRecord/interface/L1TMuonGlobalParamsRcd.h"

REGISTER_L1_WRITER(L1TMuonGlobalParamsRcd, L1TMuonGlobalParams);
