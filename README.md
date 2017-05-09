# L1Trigger conditions guide 

## Introduction

The L1T O2O system performs an automated logging of the Level-1 Trigger (L1T) running conditions into the database.
The trigger running conditions include a range of configuration elements, such as triggering rules (aka. L1T Menu,
prescales, and masks), algorithmic parameters, timing delays of various electronic components, etc. These elements
are stored in the online database (OMDS) using XML format and are indexed with a series of keys. Once the detector
is requested to take data, the L1T O2O fetches the configuration XMLs, extracts the relevant parameters, and saves
them in the offline database stamped with a sequential run number. The main consumers of the resulting offline
payloads are: High Level Trigger (HLT), Data Quality Monitoring (DQM), and Trigger Studies Group (TSG).

## Basics:

The whole trigger system's online configuration is aggregated by two top-level keys: *Trigger System Configuration*
(TSC) key and *Run Settings* (RS) key. These keys are prepared by the Level-1 Detector On Call (L1 DOC) shifter and
utilized every time when starting a new data taking run. You can check the XML configuration for the specific TSC
and RS keys using the [L1 Configuration Editor](https://l1ce.cms) (assuming you are within .cms network or use a
tunnel) or alternatively, using following python scripts:
[ugtDump.py](https://github.com/kkotov/cmssw/blob/o2oUtilities/L1TriggerConfig/Utilities/test/ugtDump.py),
[ugmtDump.py](https://github.com/kkotov/cmssw/blob/o2oUtilities/L1TriggerConfig/Utilities/test/ugmtDump.py),
[caloDump.py](https://github.com/kkotov/cmssw/blob/o2oUtilities/L1TriggerConfig/Utilities/test/caloDump.py),
[emtfDump.py](https://github.com/kkotov/cmssw/blob/o2oUtilities/L1TriggerConfig/Utilities/test/emtfDump.py),
[omtfDump.py](https://github.com/kkotov/cmssw/blob/o2oUtilities/L1TriggerConfig/Utilities/test/omtfDump.py),
[bmtfDump.py](https://github.com/kkotov/cmssw/blob/o2oUtilities/L1TriggerConfig/Utilities/test/bmtfDump.py).
These scripts can be ran from my afs public area on lxplus as well as within the private .cms network in
~l1emulator/o2o/. For example:

lxplus> python ~kkotov/public/bmtfDump.py l1\_trg\_cosmics2017/v75 l1\_trg\_rs\_cosmics2017/v57

dumps the Barrel Muon Track-Finder trigger configuration from TSC\_KEY=l1\_trg\_cosmics2017/v75 and
RS\_KEY=l1\_trg\_rs\_cosmics2017/v57 into several local XML files. For arguments you can use both: top-level
TSC and RS keys (as in the example above) and system-specific TSC and RS keys
(e.g. bmtf\_cosmics\_2017/v4 bmtf\_rs\_base\_2017/v1 in the example above).

The L1T O2O framework manages a set of XML parsers (referred to as [Online Producers](https://github.com/cms-sw/cmssw/tree/master/L1TriggerConfig/L1TConfigProducers/src))
that can be run individually as, for example, shown in [runOneByOne.sh](https://github.com/cms-sw/cmssw/blob/master/L1TriggerConfig/Utilities/test/runOneByOne.sh)
script as well as you can run them in one go using the framework. In the first case you can run it from lxplus of .cms:

lxplus> ~kkotov/python/runOneByOne.sh l1\_trg\_cosmics2017/v75 l1\_trg\_rs\_cosmics2017/v57

ssh cms-conddb-1.cms '/data/O2O/L1T/runOneByOne.sh l1\_trg\_cosmics2017/v75 l1\_trg\_rs\_cosmics2017/v57'

The result of running this script is comprehensive printout the last two lines of which will summarize if
any problems were encountered parsing the configuration XMLs. In addition, an l1config.db sqlite file will
contain all of the successfully produced payloads ready to be used with the L1 trigger emulators in CMSSW.

Another way of running the  is by  

https://cms-conddb.cern.ch/cmsDbBrowser/logs/O2O_logs/Prod/


OMDS online database at p5 (inside the .cms network) is accessible via *CMS_OMDS_LB* name while the rest of the world
(e.g. lxplus) "sees" a synchronized copy of it under *CMS_OMDS_ADG* name.

Following scripts are available for dumping content of the online database

