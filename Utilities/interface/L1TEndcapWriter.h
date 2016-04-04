#ifndef L1TEndcapWriter_h
#define L1TEndcapWriter_h

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

class L1TEndcapWriter : public edm::EDAnalyzer {
public:
    virtual void analyze(const edm::Event&, const edm::EventSetup&);

    explicit L1TEndcapWriter(const edm::ParameterSet&) : edm::EDAnalyzer(){}
    virtual ~L1TEndcapWriter(void){}
};

#endif
