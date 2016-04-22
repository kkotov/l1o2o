#include <iostream>
#include <fstream>

#include "CondTools/L1TriggerExt/interface/L1ConfigOnlineProdBaseExt.h"
#include "CondFormats/L1TObjects/interface/L1TMuonBarrelParams.h"
#include "CondFormats/DataRecord/interface/L1TMuonBarrelParamsRcd.h"
#include "L1Trigger/L1TCommon/interface/trigSystem.h"
#include "L1Trigger/L1TMuon/interface/L1TMuonGlobalParamsHelper.h"

#include "xercesc/util/PlatformUtils.hpp"
using namespace XERCES_CPP_NAMESPACE;

class L1TMuonBarrelParamsOnlineProd : public L1ConfigOnlineProdBaseExt<L1TMuonBarrelParamsRcd,L1TMuonBarrelParams> {
private:
public:
    virtual boost::shared_ptr<L1TMuonBarrelParams> newObject(const std::string& objectKey) override ;

    L1TMuonBarrelParamsOnlineProd(const edm::ParameterSet&);
    ~L1TMuonBarrelParamsOnlineProd(void){}
};

L1TMuonBarrelParamsOnlineProd::L1TMuonBarrelParamsOnlineProd(const edm::ParameterSet& iConfig) : L1ConfigOnlineProdBaseExt<L1TMuonBarrelParamsRcd,L1TMuonBarrelParams>(iConfig) {}

boost::shared_ptr<L1TMuonBarrelParams> L1TMuonBarrelParamsOnlineProd::newObject(const std::string& objectKey) {
    using namespace edm::es;

    if (objectKey.empty()) {
        edm::LogInfo( "L1-O2O: L1TMuonBarrelParamsOnlineProd" ) << "Key is empty, returning empty L1TMuonBarrelParams";
        return boost::shared_ptr< L1TMuonBarrelParams > ( new L1TMuonBarrelParams() );
    }

    std::string tscKey = objectKey.substr(0, objectKey.find(":") );
    std::string  rsKey = objectKey.substr(   objectKey.find(":")+1, std::string::npos );


    std::string stage2Schema = "CMS_TRG_L1_CONF" ;
    edm::LogInfo( "L1-O2O: L1TMuonBarrelParamsOnlineProd" ) << "Producing L1TMuonBarrelParams with TSC key =" << tscKey << " and RS key = " << rsKey ;

        // first, find keys for the algo and RS tables

        // ALGO
        std::vector< std::string > queryStrings ;
        queryStrings.push_back( "ALGO" ) ;

        std::string algo_key;

        // select ALGO from CMS_TRG_L1_CONF.BMTF_KEYS where ID = tscKey ;
        l1t::OMDSReader::QueryResults queryResult =
            m_omdsReader.basicQuery( queryStrings,
                                     stage2Schema,
                                     "BMTF_KEYS",
                                     "BMTF_KEYS.ID",
                                     m_omdsReader.singleAttribute(tscKey)
                                   ) ;

        if( queryResult.queryFailed() || queryResult.numberRows() != 1 ){
            edm::LogError( "L1-O2O" ) << "Cannot get BMTF_KEYS.ALGO" ;
            return boost::shared_ptr< L1TMuonBarrelParams > ( new L1TMuonBarrelParams() );
        }

        if( !queryResult.fillVariable( "ALGO", algo_key) ) algo_key = "";


        // RS
        queryStrings.clear() ;
        queryStrings.push_back( "MP7"    ) ;
        queryStrings.push_back( "DAQTTC" ) ;

        std::string rs_mp7_key, rs_amc13_key;

        // select RS from CMS_TRG_L1_CONF.BMTF_RS_KEYS where ID = rsKey ;
        queryResult =
            m_omdsReader.basicQuery( queryStrings,
                                     stage2Schema,
                                     "BMTF_RS_KEYS",
                                     "BMTF_RS_KEYS.ID",
                                     m_omdsReader.singleAttribute(rsKey)
                                   ) ;

        if( queryResult.queryFailed() || queryResult.numberRows() != 1 ){
            edm::LogError( "L1-O2O" ) << "Cannot get BMTF_RS_KEYS.{MP7,DAQTTC}" ;
            return boost::shared_ptr< L1TMuonBarrelParams > ( new L1TMuonBarrelParams() );
        }

        if( !queryResult.fillVariable( "MP7",    rs_mp7_key  ) ) rs_mp7_key   = "";
        if( !queryResult.fillVariable( "DAQTTC", rs_amc13_key) ) rs_amc13_key = "";


        // At this point we have three keys: one ALGO key and two RS keys; now query the payloads for these keys
        std::map<std::string,std::string> configs;  // associates key -> XML config string
        std::string xmlConfig;

        queryStrings.clear();
        queryStrings.push_back( "CONF" );

        // query ALGO configuration
        queryResult =
            m_omdsReader.basicQuery( queryStrings,
                                     stage2Schema,
                                     "BMTF_ALGO",
                                     "BMTF_ALGO.ID",
                                     m_omdsReader.singleAttribute(algo_key)
                                   ) ;

        if( queryResult.queryFailed() || queryResult.numberRows() != 1 ){
            edm::LogError( "L1-O2O: L1TMuonBarrelParamsOnlineProd" ) << "Cannot get BMTF_ALGO.CONF for ID="<<algo_key;
            return boost::shared_ptr< L1TMuonBarrelParams >( new L1TMuonBarrelParams() ) ;
        }

        if( !queryResult.fillVariable( "CONF", xmlConfig ) ) xmlConfig = "";
        // remember ALGO configuration
        configs[algo_key] = xmlConfig;

        // query MP7 RS configuration
        queryResult =
            m_omdsReader.basicQuery( queryStrings,
                                     stage2Schema,
                                     "BMTF_RS",
                                     "BMTF_RS.ID",
                                     m_omdsReader.singleAttribute(rs_mp7_key)
                                   ) ;

        if( queryResult.queryFailed() || queryResult.numberRows() != 1 ){
            edm::LogError( "L1-O2O: L1TMuonBarrelParamsOnlineProd" ) << "Cannot get BMTF_RS.CONF for ID="<<rs_mp7_key;
            return boost::shared_ptr< L1TMuonBarrelParams >( new L1TMuonBarrelParams() ) ;
        }

        if( !queryResult.fillVariable( "CONF", xmlConfig ) ) xmlConfig = "";
        // remember MP7 RS configuration
        configs[rs_mp7_key] = xmlConfig;

        // query AMC13 RS configuration
        queryResult =
            m_omdsReader.basicQuery( queryStrings,
                                     stage2Schema,
                                     "BMTF_RS",
                                     "BMTF_RS.ID",
                                     m_omdsReader.singleAttribute(rs_amc13_key)
                                   ) ;

        if( queryResult.queryFailed() || queryResult.numberRows() != 1 ){
            edm::LogError( "L1-O2O: L1TMuonBarrelParamsOnlineProd" ) << "Cannot get BMTF_RS.CONF for ID="<<rs_amc13_key;
            return boost::shared_ptr< L1TMuonBarrelParams >( new L1TMuonBarrelParams() ) ;
        }

        if( !queryResult.fillVariable( "CONF", xmlConfig ) ) xmlConfig = "";
        // remember AMC13 RS configuration
        configs[rs_amc13_key] = xmlConfig;

std::cout << "configs.size(): " << configs.size() << std::endl;

// for debugging dump the configs to local files
for(auto &conf : configs){ 
    std::ofstream output(std::string("/tmp/").append(conf.first).append(".xml"));

std::cout<<" !!!!!!!!!!!!!!!!1 writing to "<<std::string("/tmp/").append(conf.first).append(".xml") <<std::endl;

    output<<conf.second;
    output.close();
}

        // now use standard tool for XML parsing and context merging
/*
        l1t::trigSystem ts;

        ts.configureSystem(contexts,"BMTF");

        std::map<std::string, l1t::setting> settings = ts.getSettings("processors");
        std::map<std::string, l1t::mask>    rs       = ts.getMasks   ("processors");

        L1TMuonBarrelParamsHelper m_params_helper(settings,rs);

        boost::shared_ptr< L1TMuonBarrelParams > retval( new L1TMuonBarrelParams(m_params_helper) ) ;

        return retval;
*/
    return boost::shared_ptr< L1TMuonBarrelParams >( new L1TMuonBarrelParams() ) ;

}

//define this as a plug-in
DEFINE_FWK_EVENTSETUP_MODULE(L1TMuonBarrelParamsOnlineProd);
