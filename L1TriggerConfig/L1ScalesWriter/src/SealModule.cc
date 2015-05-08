#include "FWCore/PluginManager/interface/ModuleDef.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ModuleFactory.h"
#include <L1TriggerConfig/L1ScalesWriter/interface/L1ScalesWriter.h>
#include <L1TriggerConfig/L1ScalesWriter/interface/L1ScalesReader.h>

DEFINE_FWK_MODULE(L1ScalesWriter);
DEFINE_FWK_MODULE(L1ScalesReader);
