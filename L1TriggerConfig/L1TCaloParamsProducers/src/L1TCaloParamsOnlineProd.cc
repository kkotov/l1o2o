#include <iostream>
#include <fstream>

#include "CondTools/L1TriggerExt/interface/L1ConfigOnlineProdBaseExt.h"
#include "CondFormats/L1TObjects/interface/CaloParams.h"
#include "CondFormats/DataRecord/interface/L1TCaloParamsRcd.h"
#include "CondFormats/DataRecord/interface/L1TCaloParamsO2ORcd.h"
#include "L1Trigger/L1TCommon/interface/trigSystem.h"
//#include "L1Trigger/L1TCalorimeter/interface/L1TMuonGlobalParamsHelper.h"

#include "xercesc/util/PlatformUtils.hpp"
using namespace XERCES_CPP_NAMESPACE;

class L1TCaloParamsOnlineProd : public L1ConfigOnlineProdBaseExt<L1TCaloParamsO2ORcd,l1t::CaloParams> {
private:
public:
    virtual boost::shared_ptr<l1t::CaloParams> newObject(const std::string& objectKey, const L1TCaloParamsO2ORcd& record) override ;

    L1TCaloParamsOnlineProd(const edm::ParameterSet&);
    ~L1TCaloParamsOnlineProd(void){}
};

L1TCaloParamsOnlineProd::L1TCaloParamsOnlineProd(const edm::ParameterSet& iConfig) : L1ConfigOnlineProdBaseExt<L1TCaloParamsO2ORcd,l1t::CaloParams>(iConfig) {}

boost::shared_ptr<l1t::CaloParams> L1TCaloParamsOnlineProd::newObject(const std::string& objectKey, const L1TCaloParamsO2ORcd& record) {
    using namespace edm::es;

    const L1TCaloParamsRcd& baseRcd = record.template getRecord< L1TCaloParamsRcd >() ;
    edm::ESHandle< l1t::CaloParams > baseSettings ;
    baseRcd.get( baseSettings ) ;


    if (objectKey.empty()) {
        edm::LogInfo( "L1-O2O: L1TCaloParamsOnlineProd" ) << "Key is empty, returning empty l1t::CaloParams";
        return boost::shared_ptr< l1t::CaloParams > ( new l1t::CaloParams( *(baseSettings.product()) ) );
    }

    std::string tscKey = objectKey.substr(0, objectKey.find(":") );
    std::string  rsKey = objectKey.substr(   objectKey.find(":")+1, std::string::npos );


    std::string stage2Schema = "CMS_TRG_L1_CONF" ;
    edm::LogInfo( "L1-O2O: L1TCaloParamsOnlineProd" ) << "Producing L1TCaloParamsOnlineProd with TSC key =" << tscKey << " and RS key = " << rsKey ;

        // first, find keys for the algo and RS tables

        // ALGO
        std::vector< std::string > queryStrings ;
        queryStrings.push_back( "CALOL1_KEY" ) ;
        queryStrings.push_back( "CALOL2_KEY" ) ;

        std::string calol1_conf_key, calol2_conf_key;

        // select CALOL1_KEY,CALOL2_KEY from CMS_TRG_L1_CONF.L1_TRG_CONF_KEYS where ID = tscKey ;
        l1t::OMDSReader::QueryResults queryResult =
            m_omdsReader.basicQuery( queryStrings,
                                     stage2Schema,
                                     "L1_TRG_CONF_KEYS",
                                     "L1_TRG_CONF_KEYS.ID",
                                     m_omdsReader.singleAttribute(tscKey)
                                   ) ;

        if( queryResult.queryFailed() || queryResult.numberRows() != 1 ){
            edm::LogError( "L1-O2O" ) << "Cannot get L1_TRG_CONF_KEYS.{CALOL1_KEY,CALOL2_KEY}" ;
            return boost::shared_ptr< l1t::CaloParams > ( new l1t::CaloParams( *(baseSettings.product()) ) );
        }

        if( !queryResult.fillVariable( "CALOL1_KEY", calol1_conf_key) ) calol1_conf_key = "";
        if( !queryResult.fillVariable( "CALOL2_KEY", calol2_conf_key) ) calol2_conf_key = "";

/* According to Nick, masks are part of the data format, so no need to have those here
        // RS
        queryStrings.clear() ;
        queryStrings.push_back( "CALOL1_RS_KEY" ) ;
        queryStrings.push_back( "CALOL2_RS_KEY" ) ;

        std::string calol1_rs_key, calol2_rs_key;

        // select RS from CMS_TRG_L1_CONF.BMTF_RS_KEYS where ID = rsKey ;
        queryResult =
            m_omdsReader.basicQuery( queryStrings,
                                     stage2Schema,
                                     "L1_TRG_RS_KEYS",
                                     "L1_TRG_RS_KEYS.ID",
                                     m_omdsReader.singleAttribute(rsKey)
                                   ) ;

        if( queryResult.queryFailed() || queryResult.numberRows() != 1 ){
            edm::LogError( "L1-O2O" ) << "Cannot get L1_TRG_RS_KEYS.{CALOL1_RS_KEY,CALOL2_RS_KEY}" ;
            return boost::shared_ptr< l1t::CaloParams > ( new l1t::CaloParams( *(baseSettings.product()) ) );
        }

        if( !queryResult.fillVariable( "CALOL1_RS_KEY", calol1_rs_key ) ) calol1_rs_key = "";
        if( !queryResult.fillVariable( "CALOL2_RS_KEY", calol2_rs_key ) ) calol2_rs_key = "";
*/

        // At this point we have four keys: two Config keys and two RS keys; now query the payloads' keys for these keys
        std::string calol1_algo_key, calol2_algo_key;
        queryStrings.clear();
        queryStrings.push_back( "ALGO" );

        // query ALGO configurations
        queryResult =
            m_omdsReader.basicQuery( queryStrings,
                                     stage2Schema,
                                     "CALOL1_KEYS",
                                     "CALOL1_KEYS.ID",
                                     m_omdsReader.singleAttribute(calol1_conf_key)
                                   ) ;

        if( queryResult.queryFailed() || queryResult.numberRows() != 1 ){
            edm::LogError( "L1-O2O: L1TCaloParamsOnlineProd" ) << "Cannot get CALOL1_KEYS.ALGO for ID="<<calol1_conf_key;
            return boost::shared_ptr< l1t::CaloParams >( new l1t::CaloParams( *(baseSettings.product()) ) ) ;
        }

        if( !queryResult.fillVariable( "ALGO", calol1_algo_key ) ) calol1_algo_key = "";

        queryResult =
            m_omdsReader.basicQuery( queryStrings,
                                     stage2Schema,
                                     "CALOL2_KEYS",
                                     "CALOL2_KEYS.ID",
                                     m_omdsReader.singleAttribute(calol2_conf_key)
                                   ) ;

        if( queryResult.queryFailed() || queryResult.numberRows() != 1 ){
            edm::LogError( "L1-O2O: L1TCaloParamsOnlineProd" ) << "Cannot get CALOL2_KEYS.ALGO for ID="<<calol2_conf_key;
            return boost::shared_ptr< l1t::CaloParams >( new l1t::CaloParams( *(baseSettings.product()) ) ) ;
        }

        if( !queryResult.fillVariable( "ALGO", calol2_algo_key ) ) calol2_algo_key = "";


        // Now querry the actual payloads
        enum {kCONF=0, kRS, kHW, NUM_TYPES};
        std::map<std::string,std::string> payloads[NUM_TYPES];  // associates key -> XML payload for a given type of payloads
        std::string xmlPayload;

        queryStrings.clear();
        queryStrings.push_back( "CONF" );

        // query CALOL1 ALGO configuration
        queryResult =
            m_omdsReader.basicQuery( queryStrings,
                                     stage2Schema,
                                     "CALOL1_ALGO",
                                     "CALOL1_ALGO.ID",
                                     m_omdsReader.singleAttribute(calol1_algo_key)
                                   ) ;

        if( queryResult.queryFailed() || queryResult.numberRows() != 1 ){
            edm::LogError( "L1-O2O: L1TCaloParamsOnlineProd" ) << "Cannot get CALOL1_ALGO.CONF for ID="<<calol1_algo_key;
            return boost::shared_ptr< l1t::CaloParams >( new l1t::CaloParams( *(baseSettings.product()) ) ) ;
        }

        if( !queryResult.fillVariable( "CONF", xmlPayload ) ) xmlPayload = "";
        // remember ALGO configuration
        payloads[kCONF][calol1_algo_key.append("_L1")] = xmlPayload;


        // query CALOL2 ALGO configuration
        queryResult =
            m_omdsReader.basicQuery( queryStrings,
                                     stage2Schema,
                                     "CALOL2_ALGO",
                                     "CALOL2_ALGO.ID",
                                     m_omdsReader.singleAttribute(calol2_algo_key)
                                   ) ;

        if( queryResult.queryFailed() || queryResult.numberRows() != 1 ){
            edm::LogError( "L1-O2O: L1TCaloParamsOnlineProd" ) << "Cannot get CALOL2_ALGO.CONF for ID="<<calol2_algo_key;
            return boost::shared_ptr< l1t::CaloParams >( new l1t::CaloParams( *(baseSettings.product()) ) ) ;
        }

        if( !queryResult.fillVariable( "CONF", xmlPayload ) ) xmlPayload = "";
        // remember ALGO configuration
        payloads[kCONF][calol2_algo_key.append("_L2")] = xmlPayload;



// for debugging dump the configs to local files
for(auto &conf : payloads[kCONF]){ 
    std::ofstream output(std::string("/tmp/").append(conf.first.substr(0,conf.first.find("/"))).append(".xml"));
    output<<conf.second;
    output.close();
}
/*
        // now use standard tool for XML parsing and context merging

        l1t::trigSystem ts;

        ts.configureSystem(configs,"BMTF");

        std::map<std::string, l1t::setting> settings = ts.getSettings("processors");
        std::map<std::string, l1t::mask>    rs       = ts.getMasks   ("processors");

        L1TMuonBarrelParamsHelper m_params_helper(settings,rs);

        boost::shared_ptr< L1TMuonBarrelParams > retval( new L1TMuonBarrelParams(m_params_helper) ) ;

        return retval;
*/
    return boost::shared_ptr< l1t::CaloParams >( new l1t::CaloParams ( *(baseSettings.product()) ) ) ;

}

//define this as a plug-in
DEFINE_FWK_EVENTSETUP_MODULE(L1TCaloParamsOnlineProd);