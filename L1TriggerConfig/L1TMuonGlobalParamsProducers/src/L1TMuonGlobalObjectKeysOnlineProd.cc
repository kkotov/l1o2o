#include <iostream>
#include "CondTools/L1TriggerExt/interface/L1ObjectKeysOnlineProdBaseExt.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

class L1TMuonGlobalObjectKeysOnlineProd : public L1ObjectKeysOnlineProdBaseExt {
private:

public:
    virtual void fillObjectKeys( ReturnType pL1TriggerKey ) override ;

    L1TMuonGlobalObjectKeysOnlineProd(const edm::ParameterSet&);
    ~L1TMuonGlobalObjectKeysOnlineProd(void){}
};

L1TMuonGlobalObjectKeysOnlineProd::L1TMuonGlobalObjectKeysOnlineProd(const edm::ParameterSet& iConfig)
  : L1ObjectKeysOnlineProdBaseExt( iConfig ){
}


void L1TMuonGlobalObjectKeysOnlineProd::fillObjectKeys( ReturnType pL1TriggerKey ){

    std::string uGMTKey = pL1TriggerKey->subsystemKey( L1TriggerKeyExt::kuGMT ) ;

    std::string stage2Schema = "CMS_TRG_L1_CONF" ;

    if( !uGMTKey.empty() ) {
        std::vector< std::string > queryStrings ;
        queryStrings.push_back( "ALGO" ) ;

        std::string algo_key;

        // select ALGO from CMS_TRG_L1_CONF.UGMT_KEYS where ID = objectKey ;
        l1t::OMDSReader::QueryResults queryResult =
            m_omdsReader.basicQuery( queryStrings,
                                     stage2Schema,
                                     "UGMT_KEYS",
                                     "UGMT_KEYS.ID",
                                     m_omdsReader.singleAttribute(uGMTKey)
                                   ) ;

        if( queryResult.queryFailed() || queryResult.numberRows() != 1 ){
            edm::LogError( "L1-O2O" ) << "Cannot get UGMT_KEYS.ALGO" ;
            return ;
        }

        if( !queryResult.fillVariable( "ALGO", algo_key) ) algo_key = "";
        
        pL1TriggerKey->add( "L1TMuonGlobalParamsRcd",
                            "L1TMuonGlobalParams",
			    algo_key) ;
    }
}


//define this as a plug-in
DEFINE_FWK_EVENTSETUP_MODULE(L1TMuonGlobalObjectKeysOnlineProd);
