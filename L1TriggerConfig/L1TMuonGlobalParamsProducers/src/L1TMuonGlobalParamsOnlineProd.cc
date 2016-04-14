#include <iostream>
#include <fstream>

#include "CondTools/L1TriggerExt/interface/L1ConfigOnlineProdBaseExt.h"
#include "CondFormats/L1TObjects/interface/L1TMuonGlobalParams.h"
#include "CondFormats/DataRecord/interface/L1TMuonGlobalParamsRcd.h"
#include "L1Trigger/L1TCommon/interface/trigSystem.h"
#include "L1Trigger/L1TMuon/interface/L1TMuonGlobalParamsHelper.h"

#include "xercesc/util/PlatformUtils.hpp"
using namespace XERCES_CPP_NAMESPACE;

class L1TMuonGlobalParamsOnlineProd : public L1ConfigOnlineProdBaseExt<L1TMuonGlobalParamsRcd,L1TMuonGlobalParams> {
private:
public:
    virtual boost::shared_ptr<L1TMuonGlobalParams> newObject(const std::string& objectKey) override ;

    L1TMuonGlobalParamsOnlineProd(const edm::ParameterSet&);
    ~L1TMuonGlobalParamsOnlineProd(void){}
};

L1TMuonGlobalParamsOnlineProd::L1TMuonGlobalParamsOnlineProd(const edm::ParameterSet& iConfig) : L1ConfigOnlineProdBaseExt<L1TMuonGlobalParamsRcd,L1TMuonGlobalParams>(iConfig) {}

boost::shared_ptr<L1TMuonGlobalParams> L1TMuonGlobalParamsOnlineProd::newObject(const std::string& objectKey) {
    using namespace edm::es;

    std::string stage2Schema = "CMS_TRG_L1_CONF" ;
    edm::LogInfo( "L1-O2O: L1TMuonGlobalParamsOnlineProd" ) << "Producing L1TMuonGlobalParams with key =" << objectKey ;

    if (objectKey.empty()) {
        edm::LogInfo( "L1-O2O: L1TMuonGlobalParamsOnlineProd" ) << "Key is empty, returning empty L1TMuonGlobalParams";
        return boost::shared_ptr< L1TMuonGlobalParams > ( new L1TMuonGlobalParams() );
    }

    std::vector< std::string > queryColumns;
    queryColumns.push_back( "CONF" ) ;

    l1t::OMDSReader::QueryResults queryResult =
            m_omdsReader.basicQuery( queryColumns,
                                     stage2Schema,
                                     "UGMT_ALGO",
                                     "UGMT_ALGO.ID",
                                     m_omdsReader.singleAttribute(objectKey)
                                   ) ;

    if( queryResult.queryFailed() || queryResult.numberRows() != 1 ){
        edm::LogError( "L1-O2O: L1TMuonGlobalParamsOnlineProd" ) << "Cannot get BMTF_ALGO.CONF for ID="<<objectKey ;
        return boost::shared_ptr< L1TMuonGlobalParams >( new L1TMuonGlobalParams() ) ;
    }

    std::string xmlConfig;
    queryResult.fillVariable( "CONF", xmlConfig );

    std::ofstream output("/tmp/ugmt_cur_conf.xml");
    output<<xmlConfig;
    output.close();

    XMLPlatformUtils::Initialize();
    xercesc::XercesDOMParser *parser_ = new XercesDOMParser();
    parser_->setValidationScheme(XercesDOMParser::Val_Auto);
    parser_->setDoNamespaces(false);
    parser_->parse("/tmp/ugmt_cur_conf.xml");
    xercesc::DOMDocument *doc_ = parser_->getDocument();
    DOMElement* rootElement = doc_->getDocumentElement();

    l1t::trigSystem ts;

    if( xercesc::XMLString::transcode(rootElement->getTagName()) != ts._xmlRdr.kModuleNameAlgo && xercesc::XMLString::transcode(rootElement->getTagName()) != ts._xmlRdr.kModuleNameRunSettings){
        std::cout<<"Unknown tag: "<<xercesc::XMLString::transcode(rootElement->getTagName())<<std::endl;
        return boost::shared_ptr< L1TMuonGlobalParams >( new L1TMuonGlobalParams() ) ;
    }
/*
    ts.addProcRole("processors", "procMP7");
    ts._sysId = "ugmt";
    ts._xmlRdr.readContext(rootElement, ts._sysId, ts);
    ts._isConfigured = true;
*/
//    std::map<std::string, l1t::setting> settings = ts.getSettings("procMP7");
//    std::map<std::string, l1t::mask>    rs     = ts.getMasks("procMP7"); // this call throws an exception as there is currently no masks in BMTF

// following example code is similar to https://github.com/cms-l1t-offline/cmssw/blob/cms_o2o_devel-CMSSW_8_0_2/L1Trigger/L1TMuon/plugins/L1TMuonGlobalParamsESProducer.cc
//    L1TMuonGlobalParamsHelper m_params_helper;
//    m_params_helper.setBmtfInputsToDisable( settings["bmtfInputsToDisable"] );
//    m_params = (L1TMuonGlobalParams)m_params_helper;
// a more relevant code in https://github.com/cms-l1t-offline/cmssw/blob/cms_o2o_devel-CMSSW_8_0_2/L1Trigger/L1TMuonGlobal/plugins/L1TMuonGlobalParamsESProducer.cc
// (no helper class available) would require to bring here too many BMTF-specific details

    boost::shared_ptr< L1TMuonGlobalParams > retval( new L1TMuonGlobalParams() ) ;

    return retval;
}

//define this as a plug-in
DEFINE_FWK_EVENTSETUP_MODULE(L1TMuonGlobalParamsOnlineProd);
