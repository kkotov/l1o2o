L1Trigger conditions guide 
==============

Introduction
--------------

The L1T O2O system performs an automated logging of the Level-1 Trigger (L1T) running conditions into the database.
The trigger running conditions include a range of configuration elements, such as triggering rules (aka. L1T Menu,
prescales, and masks), algorithmic parameters, timing delays of various electronic components, etc. These elements
are stored in the online database (OMDS) using XML format and are indexed with a series of keys. Once the detector
is requested to take data, the L1T O2O fetches the configuration XMLs, extracts the relevant parameters, and saves
them in the offline database stamped with a sequential run number. The main consumers of the resulting offline
payloads are: High Level Trigger (HLT), Data Quality Monitoring (DQM), and Trigger Studies Group (TSG).

Infrastructure
--------------

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
script or in the very last section of this README file.

Options
--------------

As indicated earlier, most of the scripts take just three arguments: _RUN NUMBER_, _TSC KEY_ and _RS KEY_ (in this
order), except the _runOneByOne.sh_ that does not need the _RUN NUMBER_ parameter. The _runL1-O2O-iov.sh_ script
allows more flexibility in addition to these three standard arguments.
One can change the CondDB tag's suffix for a specific payload with "-t" option or limit the L1T O2O to process a
set of specific trigger systems with "-k" option. Please, refrain from using "-x" option unless you are certain
about what you do as this forwards the transactions directly to the CondDB as opposed to the local sqlite.

Prototypes and static payloads
--------------

The L1T O2O uses a "starting point" or a prototype payload for Calo, EMTF, BMTF, and uGMT systems. It allows to have
defaults for the configuration parameters that may or may not appear in the online configuration. The prototypes are
prepared with the _upload*py_ scripts that, despite what name suggests, do not normally upload anything directly to
the CondDB, but create a local sqlite with the payloads. These payloads can then be transferred to the CondDB using
the standard CMSSW [uploadConditions.py](https://twiki.cern.ch/twiki/bin/view/CMS/ConditionUploader) script accepting
the sqlite as an argument. The best practices here is to always indicate run #1 as starting Intervals Of Validity (IOV)
for the prototypes while the _uploadConditions.py_ guides you through the final steps of uploading conditions as in
such case the last upload will automatically override what was written before. The DropBox permissions are required
for the _uploadConditions.py_ to work.

Currently two trigger systems, EMTF and OMTF, have so called static payloads representing configuration pieces that
cannot be stored in the online DB. For example, EMTF uses a raw 2Gb pT Look Up Table sitting on a disk of the control
PC and generated from an XML representation used by the EMTF emulator. In this case O2O cannot generate an offline
payload as the online DB contains nothing else but just a single pT assignment version number. Instead the O2O process
is limited to extending an IOV for one of the "preloaded" EMTF Forests payloads, tagged with this version number or,
more generally, a key. The workfolow of preloading the static payloads is different from the one for prototypes as
additional O2O bookkeeping is involved. Step-by-step examples are given in the end of this README file.

Manual construction of the history
--------------

Sometimes manual construction of the history from static configuration can be useful. In this case one needs to create
an sqlite with a set of static payloads tagged by keys (can be made-up unique keys) and then write IOVs for these keys.
Remember, history reconstruction is tedious, error-prone, and time-consuming. It should be avoided if possible.
Step-by-step examples for EMTF parameters are given in the end of this README file.

## Useful tips 

1. Initialize a local sqlite DB

```
$ cmsRun ${CMSSW_RELEASE_BASE}/src/CondTools/L1TriggerExt/test/init_cfg.py useO2OTags=1 outputDBConnect=sqlite:./l1config.db
```

2. Create a static payload for OMTF indexed with "OMTF\_ALGO\_EMPTY" object key

```
$ cmsRun ${CMSSW_RELEASE_BASE}/src/CondTools/L1TriggerExt/test/L1ConfigWriteSinglePayloadExt_cfg.py objectKey="OMTF_ALGO_EMPTY" objectType=L1TMuonOverlapParams recordName=L1TMuonOverlapParamsO2ORcd useO2OTags=1 outputDBConnect=sqlite:l1config.db
```

3. Create a static payload for EMTF indexed with "7" object key

lxplus (assuming you have the .cms\_cond token locally):
```
$ env TNS_ADMIN=/cvmfs/cms.cern.ch/slc6_amd64_gcc493/cms/oracle-env/29/etc cmsRun ${CMSSW_RELEASE_BASE}/src/CondTools/L1TriggerExt/test/L1ConfigWriteSinglePayloadExt_cfg.py objectKey="7" objectType=L1TMuonEndCapForest recordName=L1TMuonEndCapForestO2ORcd useO2OTags=1 protoDBConnect=oracle://cms_orcon_adg/CMS_CONDITIONS protoDBAuth=. outputDBConnect=sqlite:l1config.db
```
p5:
```
$ env TNS_ADMIN=/opt/offline/slc6_amd64_gcc493/cms/oracle-env/29/etc/ cmsRun ${CMSSW_RELEASE_BASE}/src/CondTools/L1TriggerExt/test/L1ConfigWriteSinglePayloadExt_cfg.py objectKey="7" objectType=L1TMuonEndCapForest recordName=L1TMuonEndCapForestO2ORcd useO2OTags=1 protoDBAuth=/data/O2O/L1T/ outputDBConnect=sqlite:l1config.db 
```

4. Launch L1T O2O for specific TSC and RS keys (make sure you've edited DB environment inside the script)

```
$ ./runL1-O2O-iov.sh 296485 l1_trg_collisions2017/v33 l1_trg_rs_collisions2017/v31
```

5. Low-level look into the resulting sqlite

```
$ sqlite3 l1config.db

select * from TAG ;

select * from IOV ;

select * from PAYLOAD ;
```

6. Creating a prototype payload for CaloL2

```
$ tar -xzf ~kkotov/public/caloproto.tgz
```

For other systems, one should be able to use a central CMSSW _L1TriggerConfig/Utilities_ package, but for CaloL2 we
are not done with the campaign of removing the _Stage2_ from CaloParams record name.

```
$ scram b && cd L1TriggerConfig/Utilities/test
```

Edit the line that includes caloStage2Params configuration python to the version you need.

```
$ cmsRun uploadCaloParams.py

$ uploadConditions.py l1config.db
```

7. Reconstruction a history of the EMTF parameters

```
$ cmsRun ${CMSSW_RELEASE_BASE}/src/CondTools/L1TriggerExt/test/init_cfg.py useO2OTags=1 outputDBConnect=sqlite:./l1config.db
```

Edit *L1TriggerConfig/L1TConfigProducers/python/L1TMuonEndcapParamsOnlineProxy_cfi.py* to manually set the parameters

```
$ cmsRun ${CMSSW_RELEASE_BASE}/src/CondTools/L1TriggerExt/test/L1ConfigWriteSinglePayloadExt_cfg.py objectKey="1" objectType=L1TMuonEndCapParams recordName=L1TMuonEndcapParamsO2ORcd useO2OTags=1 outputDBConnect=sqlite:l1config.db
```

(continue generating and writing the payloads)

Set the IOVs:

```
$ cmsRun ${CMSSW_RELEASE_BASE}/src/CondTools/L1TriggerExt/test/L1ConfigWriteIOVDummyExt_cfg.py runNumber=284079 tscKey='1' useO2OTags=1
```

Check the content now:

```
$ cmsRun $CMSSW_RELEASE_BASE/src/L1TriggerConfig/Utilities/test/viewECpar.py db=sqlite:l1config.db run=284460
```

Also have a look at [README.md](https://github.com/cms-sw/cmssw/tree/master/L1TriggerConfig/Utilities/test) for set of
tools to query information from different DBs.
