#include <iostream>
#include <fstream>
#include <strstream>

#include "CondTools/L1TriggerExt/interface/L1ConfigOnlineProdBaseExt.h"
#include "CondFormats/L1TObjects/interface/L1TMuonGlobalParams.h"
#include "CondFormats/DataRecord/interface/L1TMuonGlobalParamsRcd.h"
#include "CondFormats/DataRecord/interface/L1TMuonGlobalParamsO2ORcd.h"
#include "L1Trigger/L1TCommon/interface/trigSystem.h"
#include "L1Trigger/L1TMuon/interface/L1TMuonGlobalParamsHelper.h"

#include "xercesc/util/PlatformUtils.hpp"
using namespace XERCES_CPP_NAMESPACE;

class L1TMuonGlobalParamsOnlineProd : public L1ConfigOnlineProdBaseExt<L1TMuonGlobalParamsO2ORcd,L1TMuonGlobalParams> {
private:
public:
    virtual boost::shared_ptr<L1TMuonGlobalParams> newObject(const std::string& objectKey, const L1TMuonGlobalParamsO2ORcd &record) override ;

    L1TMuonGlobalParamsOnlineProd(const edm::ParameterSet&);
    ~L1TMuonGlobalParamsOnlineProd(void){}
};

L1TMuonGlobalParamsOnlineProd::L1TMuonGlobalParamsOnlineProd(const edm::ParameterSet& iConfig) : L1ConfigOnlineProdBaseExt<L1TMuonGlobalParamsO2ORcd,L1TMuonGlobalParams>(iConfig) {}

boost::shared_ptr<L1TMuonGlobalParams> L1TMuonGlobalParamsOnlineProd::newObject(const std::string& objectKey, const L1TMuonGlobalParamsO2ORcd &record) {
    using namespace edm::es;

    const L1TMuonGlobalParamsRcd& baseRcd = record.template getRecord< L1TMuonGlobalParamsRcd >() ;
    edm::ESHandle< L1TMuonGlobalParams > baseSettings ;
    baseRcd.get( baseSettings ) ;


    std::string stage2Schema = "CMS_TRG_L1_CONF" ;
    edm::LogInfo( "L1-O2O: L1TMuonGlobalParamsOnlineProd" ) << "Producing L1TMuonGlobalParams with key =" << objectKey ;

    if (objectKey.empty()) {
        edm::LogInfo( "L1-O2O: L1TMuonGlobalParamsOnlineProd" ) << "Key is empty, returning empty L1TMuonGlobalParams";
        return boost::shared_ptr< L1TMuonGlobalParams > ( new L1TMuonGlobalParams( *(baseSettings.product()) ) );
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
        return boost::shared_ptr< L1TMuonGlobalParams >( new L1TMuonGlobalParams( *(baseSettings.product()) ) ) ;
    }

    std::string xmlConfig;
    queryResult.fillVariable( "CONF", xmlConfig );

/* Ideally, the code should look like this:

    std::map<std::string,std::string> contexts; // associates key -> XML config string
    contexts[objectKey] = xmlConfig;            // just one XML config here

    l1t::trigSystem ts;

    ts.configureSystem(contexts,"UGMT");

    std::map<std::string, l1t::setting> settings = ts.getSettings("processors");
    std::map<std::string, l1t::mask>    rs       = ts.getMasks   ("processors");

    L1TMuonGlobalParamsHelper m_params_helper(settings,rs);

    boost::shared_ptr< L1TMuonGlobalParams > retval( new L1TMuonGlobalParams(m_params_helper) ) ;

    return retval;

*/ 

/// But in reality we have something like this:
//
/// this chunk of code should go away with a proper interface to the XML parser

/*
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
///



    l1t::trigSystem ts;

/// temporary solution that will be replaced with just one ts.readContexts call
    if( xercesc::XMLString::transcode(rootElement->getTagName()) != ts._xmlRdr.kModuleNameAlgo && xercesc::XMLString::transcode(rootElement->getTagName()) != ts._xmlRdr.kModuleNameRunSettings){
        std::cout<<"Unknown tag: "<<xercesc::XMLString::transcode(rootElement->getTagName())<<std::endl;
        return boost::shared_ptr< L1TMuonGlobalParams >( new L1TMuonGlobalParams() ) ;
    }

    ts.addProcRole("processors", "processors");
    ts._sysId = "ugmt";
    ts._xmlRdr.readContext(rootElement, ts._sysId, ts);
    ts._isConfigured = true;
///



/// this code should belong to the helper class
    std::map<std::string, l1t::setting> settings = ts.getSettings("processors");
//    std::map<std::string, l1t::mask>    rs     = ts.getMasks("processors"); // this call throws an exception if there is nothing for masks

// following example code is similar to https://github.com/cms-l1t-offline/cmssw/blob/cms_o2o_devel-CMSSW_8_0_2/L1Trigger/L1TMuon/plugins/L1TMuonGlobalParamsESProducer.cc
    L1TMuonGlobalParamsHelper m_params_helper;

    std::string bmtfInputsToDisableStr = settings["bmtfInputsToDisable"].getValueAsStr();
    std::string omtfInputsToDisableStr = settings["omtfInputsToDisable"].getValueAsStr();
    std::string emtfInputsToDisableStr = settings["emtfInputsToDisable"].getValueAsStr();

    std::stringstream ss;

    std::bitset<12> bmtfDisables;
    std::bitset<6>  omtfpDisables, omtfnDisables;
    std::bitset<6>  emtfpDisables, emtfnDisables;
    for(size_t i=0; i<12; i++){

        ss.str("");
        ss<<"BMTF"<<i+1;
        if( bmtfInputsToDisableStr.find(ss.str()) != std::string::npos )
            bmtfDisables.set(i, 1);
        else
            bmtfDisables.set(i, 0);

        ss.str("");
        ss<<"OMTF";
        if( i < 6 ){
           ss << "p" << i+1;
           if( omtfInputsToDisableStr.find(ss.str()) != std::string::npos )
               omtfpDisables.set(i, 1);
           else
               omtfpDisables.set(i, 0);
        } else {
           ss << "n" << i-5;
           if( omtfInputsToDisableStr.find(ss.str()) != std::string::npos )
               omtfnDisables.set(i-6, 1);
           else
               omtfnDisables.set(i-6, 0);
        }

        ss.str("");
        ss<<"EMTF";
        if( i < 6 ){
           ss << "p" << i+1;
           if( emtfInputsToDisableStr.find(ss.str()) != std::string::npos )
               emtfpDisables.set(i, 1);
           else
               emtfpDisables.set(i, 0);
        } else {
           ss << "n" << i-5;
           if( emtfInputsToDisableStr.find(ss.str()) != std::string::npos )
               emtfnDisables.set(i-6, 1);
           else
               emtfnDisables.set(i-6, 0);
        }

   }

   m_params_helper.setBmtfInputsToDisable(bmtfDisables);
   m_params_helper.setEmtfpInputsToDisable(emtfpDisables);
   m_params_helper.setEmtfnInputsToDisable(emtfnDisables);
   m_params_helper.setOmtfpInputsToDisable(omtfpDisables);
   m_params_helper.setOmtfnInputsToDisable(omtfnDisables);
///



   return boost::shared_ptr< L1TMuonGlobalParams >( new L1TMuonGlobalParams( m_params_helper ) ) ;
*/
   return boost::shared_ptr< L1TMuonGlobalParams >( new L1TMuonGlobalParams( *(baseSettings.product()) ) ) ;
}

//define this as a plug-in
DEFINE_FWK_EVENTSETUP_MODULE(L1TMuonGlobalParamsOnlineProd);
