#include <iostream>
#include "CondTools/L1TriggerExt/interface/L1ObjectKeysOnlineProdBaseExt.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

class L1TMuonBarrelObjectKeysOnlineProd : public L1ObjectKeysOnlineProdBaseExt {
private:

public:
    virtual void fillObjectKeys( ReturnType pL1TriggerKey ) override ;

    L1TMuonBarrelObjectKeysOnlineProd(const edm::ParameterSet&);
    ~L1TMuonBarrelObjectKeysOnlineProd(void){}
};

L1TMuonBarrelObjectKeysOnlineProd::L1TMuonBarrelObjectKeysOnlineProd(const edm::ParameterSet& iConfig)
  : L1ObjectKeysOnlineProdBaseExt( iConfig ){
}


void L1TMuonBarrelObjectKeysOnlineProd::fillObjectKeys( ReturnType pL1TriggerKey ){

    std::string BMTFKey = pL1TriggerKey->subsystemKey( L1TriggerKeyExt::kBMTF ) ;

    std::string stage2Schema = "CMS_TRG_L1_CONF" ;

    if( !BMTFKey.empty() ) {
        std::vector< std::string > queryStrings ;
        queryStrings.push_back( "ALGO" ) ;

        std::string algo_key;

        // select ALGO from CMS_TRG_L1_CONF.BMTF_KEYS where ID = objectKey ;
        l1t::OMDSReader::QueryResults queryResult =
            m_omdsReader.basicQuery( queryStrings,
                                     stage2Schema,
                                     "BMTF_KEYS",
                                     "BMTF_KEYS.ID",
                                     m_omdsReader.singleAttribute(BMTFKey)
                                   ) ;

        if( queryResult.queryFailed() || queryResult.numberRows() != 1 ){
            edm::LogError( "L1-O2O" ) << "Cannot get BMTF_KEYS.ALGO" ;
            return ;
        }

        if( !queryResult.fillVariable( "ALGO", algo_key) ) algo_key = "";
        
        pL1TriggerKey->add( "L1TMuonBarrelParamsRcd",
                            "L1TMuonBarrelParams",
			    algo_key) ;
    }
}


//define this as a plug-in
DEFINE_FWK_EVENTSETUP_MODULE(L1TMuonBarrelObjectKeysOnlineProd);
