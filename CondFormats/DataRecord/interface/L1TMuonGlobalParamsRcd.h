#ifndef L1TGMTParamsRcd_L1TGMTParamsRcd_h
#define L1TGMTParamsRcd_L1TGMTParamsRcd_h
// -*- C++ -*-
//
// Package:     Subsystem/Package
// Class  :     L1TMuonGlobalParamsRcd
// 
/**\class L1TMuonGlobalParamsRcd L1TMuonGlobalParamsRcd.h Subsystem/Package/interface/L1TMuonGlobalParamsRcd.h

 Description: [one line class summary]

 Usage:
    <usage>

*/
//
// Author:      Thomas Reis
// Created:     Tue, 22 Sep 2015 13:32:54 GMT
//

#include "FWCore/Framework/interface/EventSetupRecordImplementation.h"
#include "CondFormats/DataRecord/interface/L1TriggerKeyListExtRcd.h"
#include "CondFormats/DataRecord/interface/L1TriggerKeyExtRcd.h"

class L1TMuonGlobalParamsRcd : public edm::eventsetup::DependentRecordImplementation<L1TMuonGlobalParamsRcd, boost::mpl::vector<L1TriggerKeyListExtRcd,L1TriggerKeyExtRcd> > {};

#endif
