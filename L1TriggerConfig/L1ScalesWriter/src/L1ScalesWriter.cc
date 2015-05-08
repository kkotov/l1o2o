#include "L1TriggerConfig/L1ScalesWriter/interface/L1ScalesWriter.h"
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

void L1ScalesWriter::analyze(const edm::Event& iEvent, const edm::EventSetup& evSetup){

    edm::ESHandle<L1CaloEtScale> handle1;
    evSetup.get<L1HfRingEtScaleRcd>().get( handle1 ) ;
    boost::shared_ptr<L1CaloEtScale> ptr1(new L1CaloEtScale(*(handle1.product ())));

    edm::ESHandle<L1CaloEtScale> handle2;
    evSetup.get<L1HtMissScaleRcd>().get( handle2 );  // L1EmEtScaleRcd, 
    boost::shared_ptr<L1CaloEtScale> ptr2(new L1CaloEtScale(*(handle2.product ())));

    edm::Service<cond::service::PoolDBOutputService> poolDb;
    if( poolDb.isAvailable() ){

//        cond::persistency::Session session = poolDb->session();
//        cond::persistency::TransactionScope tr(session.transaction());
//        tr.start(false);

//        std::string payloadToken1 = session.storePayload( *ptr1 );

        cond::Time_t firstSinceTime = poolDb->beginOfTime();

        poolDb->writeOne(ptr1.get(),firstSinceTime,"L1HfRingEtScaleRcd");

//        std::string payloadToken2 = session.storePayload( *ptr2 );

        poolDb->writeOne(ptr2.get(),firstSinceTime,"L1HtMissScaleRcd");

//        tr.commit();
//        tr.close();
    }

}
