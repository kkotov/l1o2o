#include "L1TriggerConfig/L1ScalesWriter/interface/L1ScalesReader.h"
#include <iomanip>
#include <iostream>

#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "CondFormats/L1TObjects/interface/L1CaloEtScale.h"
#include "CondFormats/DataRecord/interface/L1EmEtScaleRcd.h"
#include "CondFormats/DataRecord/interface/L1JetEtScaleRcd.h"
#include "CondFormats/DataRecord/interface/L1HtMissScaleRcd.h"
#include "CondFormats/DataRecord/interface/L1HfRingEtScaleRcd.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CondCore/DBOutputService/interface/PoolDBOutputService.h"
#include "CondCore/CondDB/interface/Session.h"

#include <iostream>
using namespace std;

void L1ScalesReader::analyze(const edm::Event& iEvent, const edm::EventSetup& evSetup){

    edm::ESHandle<L1CaloEtScale> handle1;
    evSetup.get<L1HfRingEtScaleRcd>().get( handle1 ) ;
    boost::shared_ptr<L1CaloEtScale> ptr1(new L1CaloEtScale(*(handle1.product ())));

    edm::ESHandle<L1CaloEtScale> handle2;
    evSetup.get<L1HtMissScaleRcd>().get( handle2 );  // L1EmEtScaleRcd, 
    boost::shared_ptr<L1CaloEtScale> ptr2(new L1CaloEtScale(*(handle2.product ())));

    const std::vector<double>& thr1 = ptr1->getThresholds();
    cout<<"L1HfRingEtScaleRcd: "<<endl;
    for(auto &it : thr1) cout <<" "<< it << endl;

    const std::vector<double>& thr2 = ptr2->getThresholds();
    cout<<"L1HtMissScaleRcd: "<<endl;
    for(auto &it : thr2) cout <<" "<< it << endl;
}
