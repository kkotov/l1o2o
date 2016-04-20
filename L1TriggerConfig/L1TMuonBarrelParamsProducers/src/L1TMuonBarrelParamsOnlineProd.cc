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

    std::string stage2Schema = "CMS_TRG_L1_CONF" ;
    edm::LogInfo( "L1-O2O: L1TMuonBarrelParamsOnlineProd" ) << "Producing L1TMuonBarrelParams with key =" << objectKey ;

    if (objectKey.empty()) {
        edm::LogInfo( "L1-O2O: L1TMuonBarrelParamsOnlineProd" ) << "Key is empty, returning empty L1TMuonBarrelParams";
        return boost::shared_ptr< L1TMuonBarrelParams > ( new L1TMuonBarrelParams() );
    }

    std::vector< std::string > queryColumns;
    queryColumns.push_back( "CONF" ) ;

    l1t::OMDSReader::QueryResults queryResult =
            m_omdsReader.basicQuery( queryColumns,
                                     stage2Schema,
                                     "BMTF_ALGO",
                                     "BMTF_ALGO.ID",
                                     m_omdsReader.singleAttribute(objectKey)
                                   ) ;

    if( queryResult.queryFailed() || queryResult.numberRows() != 1 ){
        edm::LogError( "L1-O2O: L1TMuonBarrelParamsOnlineProd" ) << "Cannot get BMTF_ALGO.CONF for ID="<<objectKey ;
        return boost::shared_ptr< L1TMuonBarrelParams >( new L1TMuonBarrelParams() ) ;
    }

    std::string xmlConfig;
    queryResult.fillVariable( "CONF", xmlConfig );

    std::map<std::string,std::string> contexts; // associates key -> XML config string
    contexts[objectKey] = xmlConfig;            // just one XML config here

    l1t::trigSystem ts;

    ts.configureSystem(contexts,"BMTF");

    std::map<std::string, l1t::setting> settings = ts.getSettings("processors");
    std::map<std::string, l1t::mask>    rs       = ts.getMasks   ("processors");

    L1TMuonBarrelParamsHelper m_params_helper(settings,rs);

    boost::shared_ptr< L1TMuonBarrelParams > retval( new L1TMuonBarrelParams(m_params_helper) ) ;

    return retval;
}

//define this as a plug-in
DEFINE_FWK_EVENTSETUP_MODULE(L1TMuonBarrelParamsOnlineProd);
