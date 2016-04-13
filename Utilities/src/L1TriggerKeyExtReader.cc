#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "CondFormats/DataRecord/interface/L1TriggerKeyExtRcd.h"
#include "CondFormats/L1TObjects/interface/L1TriggerKeyExt.h"

class L1TriggerKeyExtReader : public edm::EDAnalyzer {
public:
    virtual void analyze(const edm::Event&, const edm::EventSetup&);

    explicit L1TriggerKeyExtReader(const edm::ParameterSet&) : edm::EDAnalyzer(){}
    virtual ~L1TriggerKeyExtReader(void){}
};

#include <iostream>
using namespace std;

void L1TriggerKeyExtReader::analyze(const edm::Event& iEvent, const edm::EventSetup& evSetup){

    edm::ESHandle<L1TriggerKeyExt> handle1;
    evSetup.get<L1TriggerKeyExtRcd>().get( handle1 ) ;
    boost::shared_ptr<L1TriggerKeyExt> ptr1(new L1TriggerKeyExt(*(handle1.product ())));

    cout<<"L1TriggerKeyExt: parent key = "<<ptr1->tscKey()<<endl;

    cout<<" GT    key:"<<ptr1->subsystemKey( L1TriggerKeyExt::kuGT  )<<endl;
    cout<<" BMTF  key:"<<ptr1->subsystemKey( L1TriggerKeyExt::kBMTF )<<endl;

    cout<<"Records: "<<endl;

    L1TriggerKeyExt::RecordToKey::const_iterator itr = ptr1->recordToKeyMap().begin() ;
    L1TriggerKeyExt::RecordToKey::const_iterator end = ptr1->recordToKeyMap().end() ;

    for( ; itr != end ; ++itr ){
        std::string recordType = itr->first ;
        std::string objectKey = itr->second ;
        std::string recordName( recordType, 0, recordType.find_first_of("@") ) ;
        cout<<" record "<<recordName<<" key: "<<itr->second<<endl;
    }

    cout<<dec<<endl;


}

#include "FWCore/PluginManager/interface/ModuleDef.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ModuleFactory.h"

DEFINE_FWK_MODULE(L1TriggerKeyExtReader);
