#ifndef L1ScalesReader_h
#define L1ScalesReader_h

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

class L1ScalesReader : public edm::EDAnalyzer {
public:
    virtual void analyze(const edm::Event&, const edm::EventSetup&);

    explicit L1ScalesReader(const edm::ParameterSet&) : edm::EDAnalyzer(){}
    virtual ~L1ScalesReader(void){}
};

#endif
