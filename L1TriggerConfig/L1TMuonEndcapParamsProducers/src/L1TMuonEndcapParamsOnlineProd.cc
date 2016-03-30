#include <iostream>
#include <fstream>

#include "CondTools/L1TriggerExt/interface/L1ConfigOnlineProdBaseExt.h"
#include "CondFormats/L1TObjects/interface/L1TMuonEndcapParams.h"
#include "CondFormats/DataRecord/interface/L1TMuonEndcapParamsRcd.h"
#include "CondFormats/L1TObjects/interface/L1TMuEndCapForest.h"

class L1TMuonOverlapParamsOnlineProd : public L1ConfigOnlineProdBaseExt<L1TMuonOverlapParamsRcd,L1TMuonOverlapParams> {
private:
public:
    virtual boost::shared_ptr<L1TMuonOverlapParams> newObject(const std::string& objectKey) override ;

    L1TMuonOverlapParamsOnlineProd(const edm::ParameterSet&);
    ~L1TMuonOverlapParamsOnlineProd(void){}
};

L1TMuonOverlapParamsOnlineProd::L1TMuonOverlapParamsOnlineProd(const edm::ParameterSet& iConfig) : L1ConfigOnlineProdBaseExt<L1TMuonOverlapParamsRcd,L1TMuonOverlapParams>(iConfig) {}

boost::shared_ptr<L1TMuonOverlapParams> L1TMuonOverlapParamsOnlineProd::newObject(const std::string& objectKey) {
    using namespace edm::es;

    std::string stage2Schema = "CMS_TRG_L1_CONF" ;
    edm::LogInfo( "L1-O2O: L1TMuonOverlapParamsOnlineProd" ) << "Producing L1TMuonOverlapParams with key =" << objectKey ;

    if (objectKey.empty()) {
        edm::LogInfo( "L1-O2O: L1TMuonOverlapParamsOnlineProd" ) << "Key is empty, returning empty L1TMuonOverlapParams";
        return boost::shared_ptr< L1TMuonOverlapParams > ( new L1TMuonOverlapParams() );
    }

    std::vector< std::string > queryColumns;
    queryColumns.push_back( "CONF" ) ;

    l1t::OMDSReader::QueryResults queryResult =
            m_omdsReader.basicQuery( queryColumns,
                                     stage2Schema,
                                     "OMTF_ALGO",
                                     "OMTF_ALGO.ID",
                                     m_omdsReader.singleAttribute(objectKey)
                                   ) ;

    if( queryResult.queryFailed() || queryResult.numberRows() != 1 ){
        edm::LogError( "L1-O2O: L1TMuonOverlapParamsOnlineProd" ) << "Cannot get OMTF_ALGO.CONF for ID="<<objectKey ;
        return boost::shared_ptr< L1TMuonOverlapParams >( new L1TMuonOverlapParams() ) ;
    }

    std::string xmlConfig;
    queryResult.fillVariable( "CONF", xmlConfig );
///    std::istringstream iss(xmlConfig);
 
    boost::shared_ptr< L1TMuonOverlapParams > retval( new L1TMuonOverlapParams() ) ;

/// your code populating the payload /// 

    return retval;
}

//define this as a plug-in
DEFINE_FWK_EVENTSETUP_MODULE(L1TMuonOverlapParamsOnlineProd);
