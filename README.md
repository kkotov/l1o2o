# L1Trigger conditions guide 

## Introduction

The L1T O2O system performs an automated logging of the Level-1 Trigger (L1T) running conditions into the database.
The trigger running conditions include a range of configuration elements, such as triggering rules (aka. L1T Menu,
prescales, and masks), algorithmic parameters, timing delays of various electronic components, etc. These elements
are stored in the online database (OMDS) using XML format and are indexed with a series of keys. Once the detector
is requested to take data, the L1T O2O fetches the configuration XMLs, extracts the relevant parameters, and saves
them in the offline database stamped with a sequential run number. The main consumers of the resulting offline
payloads are: High Level Trigger (HLT), Data Quality Monitoring (DQM), and Trigger Studies Group (TSG).

## Infrastructure

The L1T O2O system is part of the CMSSW release and can be run in any environment that has an installation of CMSSW.
Production system is installed in _cms-conddb-1.cms:/data/O2O/L1T/_ and gets automatically invoked over ssh by the
Function Manager executing _o2o.sh_ with three arguments: _RUN NUMBER_, _TSC KEY_ and _RS KEY_. It needs .netrc and
.cms\_cond credentials (sitting in the same directory) for accessing OMDS and CondDB. The process logs are easily
available in the CondDB browser [here](https://cms-conddb.cern.ch/cmsDbBrowser/logs/O2O_logs/Prod/) where they are
tagged by "L1TMenu" job name or on the local file system in _cms-conddb-1.cms:/data/O2O/logs/L1TMenu*_ files.
A currently active version is pointed to with _pro_ soft link and (minimally) contains
[runL1-O2O-iov.sh](https://github.com/cms-sw/cmssw/blob/master/CondTools/L1TriggerExt/scripts/runL1-O2O-iov.sh)
script that among all of the options should have *ONLINEDB_OPTIONS* pointing to *cms_omds_lb* and
*PROTODB_OPTIONS* pointing to *cms_orcon_prod* (it would have been *cms_omds_adg* and *cms_orcon_adg* respectively
on lxplus). The choice of active O2O working directory is made in _o2o2017.sh_ script (_JOBDIR_) that also defines
a CMSSW version (_RELEASE_) and logging environment. Deploying the new O2O version most often means modifying the
_JOBDIR_ and _RELEASE_ variables and changing a _pro_ soft line (that is actually not used for anything).

The system can also be installed on lxplus (e.g. for testing purposes), but another .cms\_cond credentials needs to
be requested. If you have it, you can run the runL1-O2O-iov.sh script directly with the same three arguments as the
o2o.sh described above. Make sure you'll initialize a local l1config.db sqlite beforehand as, for example, outlined
in [runOneByOne.sh](https://github.com/cms-sw/cmssw/blob/master/L1TriggerConfig/Utilities/test/runOneByOne.sh#L31-L37)
script.

## Arguments

As indicated earlier, most of the scripts take just three arguments: _RUN NUMBER_, _TSC KEY_ and _RS KEY_ (in this
order), except the _runOneByOne.sh_ that does not need the _RUN NUMBER_ parameter. The only exception from this rule
is the _runL1-O2O-iov.sh_ script that is also used for development/debugging purposes and allows more flexibility.
One can change the Cond DB tag suffix for a specific payload with "-t" option or limit the L1T O2O to process a
set of specific trigger systems with "-k" option. Please, refrain from using "-x" option unless you understand what
you do as this forward the transactions directly to the CondDB as opposed to the local sqlite.

## Code organization (technical, should go to the CondTools/L1TriggerExt)

The L1T O2O system is partitioned into the [core framework](https://github.com/cms-sw/cmssw/blob/master/CondTools/L1TriggerExt)
and a set of system-specific [online producers](https://github.com/cms-sw/cmssw/blob/master/L1TriggerConfig/L1TConfigProducers)
invoked by means of [data writers](https://github.com/cms-sw/cmssw/blob/master/CondTools/L1TriggerExt/src/DataWriterExt.cc)
from the core framework and fetching the information from the online DB. The only component of the core framework that
explicitly queries online DB is
[L1SubsystemKeysOnlineProdExt](https://github.com/cms-sw/cmssw/blob/master/CondTools/L1TriggerExt/plugins/L1SubsystemKeysOnlineProdExt.cc)
generating a L1TriggerKeyExt object with TSC and RS keys for all of the systems. This object is distributed to
system-specific ObjectKeys online producers that in turn generate system-specific L1TriggerKeyExt objects forwarded
to the final online producers. The CondDB tag names are specified in
[this config](https://github.com/cms-sw/cmssw/blob/master/CondTools/L1TriggerExt/python/L1SubsystemParamsExt_cfi.py).
The core framework's design is outlined in [this talk](http://kkotov.github.io/l1o2o/talks/2016.04.19).

Currently, the RS specific code is still available in the core framework, but is not used or intended to be used. So
if you browse the code, you can ignore files containing the RS in the name.

## Prototypes and static payloads

The L1T O2O uses a "starting checkpoint" or a prototype payload for Calo, EMTF, BMTF, and uGMT systems. It allows to
have defaults for the configuration parameters that may or may not be overridden by the O2O process (generally
depends on the policy for each of these subsystems and availability in the online DB).

Static payloads ...

## Manual construction of the history

Sometimes manual construction of the history from static configuration can be useful. This that case one needs to
create an sqlite with a set of payloads tagged by keys and then write Intervals Of Validity for each of these keys.
An [EMTF example](https://github.com/cms-sw/cmssw/blob/master/CondTools/L1TriggerExt/test/L1ConfigWriteIOVDummyExt_cfg.py)
of how to write the IOV can be of some help here.

## Miscellanea

Have a look at [README.md](https://github.com/cms-sw/cmssw/tree/master/L1TriggerConfig/Utilities/test) for set of
tools to query information from different DBs.
