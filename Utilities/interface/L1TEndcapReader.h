#ifndef L1TEndcapReader_h
#define L1TEndcapReader_h

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

class L1TEndcapReader: public edm::EDAnalyzer {
public:
    virtual void analyze(const edm::Event&, const edm::EventSetup&);

    explicit L1TEndcapReader(const edm::ParameterSet&) : edm::EDAnalyzer(){}
    virtual ~L1TEndcapReader(void){}
};

#endif

