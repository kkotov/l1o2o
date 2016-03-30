#include <iostream>
#include "CondTools/L1TriggerExt/interface/L1ObjectKeysOnlineProdBaseExt.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

class L1TMuonEndcapObjectKeysOnlineProd : public L1ObjectKeysOnlineProdBaseExt {
private:

public:
    virtual void fillObjectKeys( ReturnType pL1TriggerKey ) override ;

    L1TMuonEndcapObjectKeysOnlineProd(const edm::ParameterSet&);
    ~L1TMuonEndcapObjectKeysOnlineProd(void){}
};

L1TMuonEndcapObjectKeysOnlineProd::L1TMuonEndcapObjectKeysOnlineProd(const edm::ParameterSet& iConfig)
  : L1ObjectKeysOnlineProdBaseExt( iConfig ){
}


void L1TMuonEndcapObjectKeysOnlineProd::fillObjectKeys( ReturnType pL1TriggerKey ){

    std::string EMTFKey = pL1TriggerKey->subsystemKey( L1TriggerKeyExt::kEMTF ) ;

    std::string stage2Schema = "CMS_TRG_L1_CONF" ;

    if( !EMTFKey.empty() ) {
        std::vector< std::string > queryStrings ;
        queryStrings.push_back( "EMTF_ALGO" ) ;

        std::string algo_key;

        // select MP7_PP_CONF_KEY from CMS_S1CALOL2.S1CALOL2_CONF where S1CALOL2_CONF_KEY = objectKey ;
        l1t::OMDSReader::QueryResults queryResult =
            m_omdsReader.basicQuery( queryStrings,
                                     stage2Schema,
                                     "EMTF_KEYS",
                                     "EMTF_KEYS.ID",
                                     m_omdsReader.singleAttribute(EMTFKey)
                                   ) ;

        if( queryResult.queryFailed() || queryResult.numberRows() != 1 ){
            edm::LogError( "L1-O2O" ) << "Cannot get OMTF_KEYS.EMTF_ALGO" ;
            return ;
        }

        if( !queryResult.fillVariable( "EMTF_ALGO", algo_key) ) algo_key = "";
        
        pL1TriggerKey->add( "L1TMuonEndcapParamsRcd",
                            "L1TMuonEndcapParams",
			    algo_key) ;
    }
}


//define this as a plug-in
DEFINE_FWK_EVENTSETUP_MODULE(L1TMuonEndcapObjectKeysOnlineProd);
