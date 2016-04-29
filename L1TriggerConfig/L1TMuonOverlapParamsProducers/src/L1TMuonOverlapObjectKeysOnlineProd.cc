#include <iostream>
#include "CondTools/L1TriggerExt/interface/L1ObjectKeysOnlineProdBaseExt.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

class L1TMuonOverlapObjectKeysOnlineProd : public L1ObjectKeysOnlineProdBaseExt {
private:

public:
    virtual void fillObjectKeys( ReturnType pL1TriggerKey ) override ;

    L1TMuonOverlapObjectKeysOnlineProd(const edm::ParameterSet&);
    ~L1TMuonOverlapObjectKeysOnlineProd(void){}
};

L1TMuonOverlapObjectKeysOnlineProd::L1TMuonOverlapObjectKeysOnlineProd(const edm::ParameterSet& iConfig)
  : L1ObjectKeysOnlineProdBaseExt( iConfig ){
}


void L1TMuonOverlapObjectKeysOnlineProd::fillObjectKeys( ReturnType pL1TriggerKey ){

    std::string OMTFKey = pL1TriggerKey->subsystemKey( L1TriggerKeyExt::kOMTF ) ;

    std::string stage2Schema = "CMS_TRG_L1_CONF" ;

    if( !OMTFKey.empty() ) {
        // simply assign the top level key to the record
        pL1TriggerKey->add( "L1TMuonOverlapParamsO2ORcd",
                            "L1TMuonOverlapParams",
			    OMTFKey) ;
    }
}


//define this as a plug-in
DEFINE_FWK_EVENTSETUP_MODULE(L1TMuonOverlapObjectKeysOnlineProd);
