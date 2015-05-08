#ifndef L1ScalesWriter_h
#define L1ScalesWriter_h

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

class L1ScalesWriter : public edm::EDAnalyzer {
public:
    virtual void analyze(const edm::Event&, const edm::EventSetup&);

    explicit L1ScalesWriter(const edm::ParameterSet&) : edm::EDAnalyzer(){}
    virtual ~L1ScalesWriter(void){}
};

#endif
