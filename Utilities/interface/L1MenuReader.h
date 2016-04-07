#ifndef L1MenuReader_h
#define L1MenuReader_h

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

class L1MenuReader : public edm::EDAnalyzer {
public:
    virtual void analyze(const edm::Event&, const edm::EventSetup&);

    explicit L1MenuReader(const edm::ParameterSet&) : edm::EDAnalyzer(){}
    virtual ~L1MenuReader(void){}
};

#endif

