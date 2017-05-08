## L1Trigger conditions guide 

# Introduction

The L1T O2O system performs an automated logging of the Level-1 Trigger (L1T) running conditions into the database.
The trigger running conditions include a range of configuration elements, such as triggering rules (aka. L1T Menu,
prescales, and masks), algorithmic parameters, timing delays of various electronic components, etc. These elements
are stored in the online database (OMDS) using XML format and are indexed with a series of keys. Once the detector
is requested to take data, the L1T O2O fetches the configuration XMLs, extracts the relevant parameters, and saves
them in the offline database stamped with a sequential run number. The main consumers of the resulting offline
payloads are: High Level Trigger (HLT), Data Quality Monitoring (DQM), and Trigger Studies Group (TSG).

# Basics:

The whole trigger system's online configuration is aggregated by two top-level keys: TSC key and RS key. You can
dump XML configuration for the specific TSC and RS keys using *ugtDump.py*, *ugmtDump.py*, *caloDump.py*,
*emtfDump.py*, *omtfDump.py*, *bmtfDump.py* python scripts available [in the CMSSW release](https://github.com/cms-sw/cmssw/tree/master/L1TriggerConfig/Utilities/test),
from my afs public area on lxplus, and within the private .cms network in ~l1emulator/o2o/. For example:

lxplus> python ~kkotov/public/bmtfDump.py l1\_trg\_cosmics2017/v75 l1\_trg\_rs\_cosmics2017/v57

dumps all of the algotighmic parameters of the Barrel Muon Track Finder trigger system into several local XML files.
These scripts can take both: top-level as well as system-specific TSC and RS keys.

The L1T O2O framework manages a set of XML parsers (aka. [Online Producers](https://github.com/cms-sw/cmssw/tree/master/L1TriggerConfig/L1TConfigProducers/src))
that can be run individually as, for example, shown in [runOneByOne.sh](https://github.com/cms-sw/cmssw/blob/master/L1TriggerConfig/Utilities/test/runOneByOne.sh)
script as well as you can run the whole framework. In the first case you can run it from lxplus of .cms:

lxplus> ~kkotov/python/runOneByOne.sh l1\_trg\_cosmics2017/v75 l1\_trg\_rs\_cosmics2017/v57

ssh cms-conddb-1.cms '/data/O2O/L1T/runOneByOne.sh TSC_KEY RS_KEY '

(The last two lines of the printout will indicate if there is a problem with any of the configurations aggregated by the new key.)

In the later case  


https://cms-conddb.cern.ch/cmsDbBrowser/logs/O2O_logs/Prod/


OMDS online database at p5 (inside the .cms network) is accessible via *CMS_OMDS_LB* name while the rest of the world
(e.g. lxplus) "sees" a synchronized copy of it under *CMS_OMDS_ADG* name.

Following scripts are available for dumping content of the online database

