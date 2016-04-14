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

    std::ofstream output("/tmp/bmtf_cur_conf.xml");
    output<<xmlConfig;
    output.close();

    XMLPlatformUtils::Initialize();
    xercesc::XercesDOMParser *parser_ = new XercesDOMParser();
    parser_->setValidationScheme(XercesDOMParser::Val_Auto);
    parser_->setDoNamespaces(false);
    parser_->parse("/tmp/bmtf_cur_conf.xml");
    xercesc::DOMDocument *doc_ = parser_->getDocument();
    DOMElement* rootElement = doc_->getDocumentElement();

    l1t::trigSystem ts;

    if( xercesc::XMLString::transcode(rootElement->getTagName()) != ts._xmlRdr.kModuleNameAlgo && xercesc::XMLString::transcode(rootElement->getTagName()) != ts._xmlRdr.kModuleNameRunSettings){
        std::cout<<"Unknown tag: "<<xercesc::XMLString::transcode(rootElement->getTagName())<<std::endl;
        return boost::shared_ptr< L1TMuonBarrelParams >( new L1TMuonBarrelParams() ) ;
    }

    ts.addProcRole("processors", "procMP7");
    ts._sysId = "bmtf";
    ts._xmlRdr.readContext(rootElement, ts._sysId, ts);
    ts._isConfigured = true;

    std::map<std::string, l1t::setting> settings = ts.getSettings("procMP7");
//    std::map<std::string, l1t::mask>    rs     = ts.getMasks("procMP7"); // this call throws an exception as there is currently no masks in BMTF

// following example code is similar to https://github.com/cms-l1t-offline/cmssw/blob/cms_o2o_devel-CMSSW_8_0_2/L1Trigger/L1TMuon/plugins/L1TMuonGlobalParamsESProducer.cc
//    L1TMuonBarrelParamsHelper m_params_helper;
//    m_params_helper.setBmtfInputsToDisable( settings["bmtfInputsToDisable"] );
//    m_params = (L1TMuonBarrelParams)m_params_helper;
// a more relevant code in https://github.com/cms-l1t-offline/cmssw/blob/cms_o2o_devel-CMSSW_8_0_2/L1Trigger/L1TMuonBarrel/plugins/L1TMuonBarrelParamsESProducer.cc
// (no helper class available) would require to bring here too many BMTF-specific details

    boost::shared_ptr< L1TMuonBarrelParams > retval( new L1TMuonBarrelParams() ) ;

    return retval;
}

//define this as a plug-in
DEFINE_FWK_EVENTSETUP_MODULE(L1TMuonBarrelParamsOnlineProd);
