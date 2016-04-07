#ifndef L1MenuWriter_h
#define L1MenuWriter_h

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

class L1MenuWriter : public edm::EDAnalyzer {
public:
    virtual void analyze(const edm::Event&, const edm::EventSetup&);

    explicit L1MenuWriter(const edm::ParameterSet&) : edm::EDAnalyzer(){}
    virtual ~L1MenuWriter(void){}
};

#endif
