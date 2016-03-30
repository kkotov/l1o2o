#ifndef L1TBMTFParamsRcd_L1TBMTFParamsRcd_h
#define L1TBMTFParamsRcd_L1TBMTFParamsRcd_h
// -*- C++ -*-
//
// Class  :     L1TMuonBarrelParamsRcd
//
// Author:      Giannis Flouris
// Created:
//

#include "FWCore/Framework/interface/EventSetupRecordImplementation.h"
#include "CondFormats/DataRecord/interface/L1TriggerKeyListExtRcd.h"
#include "CondFormats/DataRecord/interface/L1TriggerKeyExtRcd.h"
class L1TMuonBarrelParamsRcd : public edm::eventsetup::DependentRecordImplementation<L1TMuonBarrelParamsRcd, boost::mpl::vector<L1TriggerKeyListExtRcd,L1TriggerKeyExtRcd> > {};

#endif
