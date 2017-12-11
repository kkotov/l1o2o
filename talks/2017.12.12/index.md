---
title       : "Practical recipes for L1T Conditions"
subtitle    : 
author      : Khristian Kotov
job         : 
framework   : io2012        # {io2012, html5slides, shower, dzslides, ...}
highlighter : highlight.js  # {highlight.js, prettify, highlight}
hitheme     : tomorrow      # 
github:
  user: kkotov 
  repo: talks
url:
  lib:    ../../../../monohiggs/plots/libraries
  assets: ../../../../monohiggs/plots/assets
widgets     : [mathjax]     # {mathjax, quiz, bootstrap}
mode        : selfcontained # {standalone, draft}

--- .class #id

## Objectives

Formalize terminology 
 * know difference between databases (e.g. <span style="color:green">OMDS</span>, <span style="color:green">INT2R</span>,
 * avoid confusing <span style="color:green">payload</span> with <span style="color:green">tag</span>
<span style="color:green">ORC{ON,OFF}</span>, <span style="color:green">_ADG</span>, <span style="color:green">_LB</span>)

Put together handy recipes
 * know how to query online DBs and dump payloads from CondDB
 * prepare an O2O prototype or Monte Carlo tag for upload
 * if ever you have to reconstruct a tag history ...

Cover maintenance/development TODO list
 * clean the mess with BMTF and EMTF data tags
 * prevent Helpers from crashing on old data
 * migrate to CentOS7

--- .class #id

## Databases

<span style="color:green">OMDS</span> &ndash; production online DB at p5
* <span style="color:green">CMS_OMDS_LB</span> &ndash; for accessing it from p5
* <span style="color:green">CMS_OMDS_ADG</span> &ndash; from everywhere else

<span style="color:green">ORCON</span> &ndash; production Conditions DB at p5
* <span style="color:green">CMS_ORCON_PROD</span> &ndash; for accessing it from p5
* <span style="color:green">CMS_ORCON_ADG</span> &ndash; from everywhere else

<span style="color:green">ORCOFF</span> &ndash; production Conditions DB outside of p5 (synchronized with the one at p5)
* you've used it in your CMSSW jobs with `frontier://FrontierProd/CMS_CONDITIONS`
* development DB differs by two letters `frontier://FrontierPrep/CMS_CONDITIONS`

The `/etc/tnsnames.ora` config defines the actual DB servers behind the names above

--- .class #id

## CondDB Organization

* <span style="color:green">Payload</span> &ndash; a boost-serialized object stored in CondDB and referenced by its SHA1 hash sum
* <span style="color:green">Interval Of Validity (IOV)</span> &ndash; period when payload should be considered
* <span style="color:green">Tag</span> &ndash; a symbolic name defining a sequence of payloads and their IOVs

Dive into CondDB structure using a local SQLite \``sqlite3 ~kkotov/public/example.db`\`:

`sqlite> select * from IOV where TAG_NAME like 'L1TMuon%' ;`
<pre>
L1TMuonGlobalParams_Stage2v0_hlt|286046|216230...|2017-03-17 15:38:44.940854
L1TMuonGlobalParams_Stage2v0_hlt|286061|ca4e58...|2017-03-17 15:40:00.592204
L1TMuonGlobalParams_Stage2v0_hlt|286069|216230...|2017-03-17 15:40:21.443129
</pre>

Some other useful sqlite commands:
* `.tables` &ndash; see all the tables available 
* `PRAGMA table_info(TAG);` &ndash; print <span style="color:green">TAG</span> table schema (= `describe TAG;` in ORACLE)

For the central CondDB [the browser](https://cms-conddb.cern.ch/browser/) does the same + searches through the Global Tags


--- .class #id

## Fetching information from OMDS

Unless your favorite tool is L1CE, you can dump XMLs from with scripts from my afs public:
* `python ~kkotov/public/{calo,calol1,emtf,omtf}Dump.py [TSC_KEY]`
* `python ~kkotov/public/{bmtf,ugmt,ugt}Dump.py [TSC_KEY] [RS_KEY]`

Examples:

* `python ~kkotov/public/caloDump.py l1_trg_circulating2017/v56`
* `python ~kkotov/public/caloDump.py` &ndash; lists all the CaloL2 TSC keys
* `python ~kkotov/public/caloDump.py calol2_commissioning2017/v36`

The scripts accept top-level TSC and RS keys equally well as subsystem TSC and RS keys

--- .class #id

## Fetching information from CondDB

Prepare a working directory first:

* `cmsrel CMSSW_10_0_0_pre2 && cd CMSSW_10_0_0_pre2/src && cmsenv`

Following steps are needed until [#20939](https://github.com/cms-sw/cmssw/pull/20939)
is merged (otherwise use <span style="color:green">$CMSSW_RELEASE_BASE</span>):

* `git cms-init && git cms-merge-topic -u 20939`

* `scram b -j 4 && cd L1TriggerConfig/Utilities/test/`

* `rm ../../../../lib/slc6_amd64_gcc630/.poisonededmplugincache`

Several examples of `view*py` scripts (viewers):

* `cmsRun viewTKE.py db=prod run=286000` &ndash; shows subsystem TSC:RS keys
* `cmsRun viewCaloParams.py db=prod run=306000` &ndash; prints Calo L2+L1

Look inside the viewers, edit `viewPrescalesVetos.py` (tag, prescale_table_verbosity), run it

--- .class #id

## Creating a new O2O prototype (= MC tag)

Part of the L1T configuration that absent from OMDS is taken by O2O from
[prototypes](https://cms-conddb.cern.ch/cmsDbBrowser/search/Prod/Prototype)

This is the experts' responsibility to update prototypes whenever configuration at p5 changes!

Procedure:
* update your static python configuration
* run your `upload{Calo,Bmtf,Gmt}Params.py` script from L1TriggerConfig/Utilities/test
* send the resulting sqlite to a new AlCa-L1T liaison

If this is not done in a timely manner, a labor-intensive tag reconstruction may be required

To create a Monte Carlo tag follow the same steps as above plus:
* use `uploadEmtf{Params,Forest}.py` for EMTF
* use `dumpMenu.py` for the uGT menu (Manfred has an instruction)

In the end the liaison runs `uploadConditions.py`,
[submits GT request](https://cms-conddb.cern.ch/cmsDbBrowser/request/Prod),
and reports in [HN](https://hypernews.cern.ch/HyperNews/CMS/get/calibrations.html)

--- .class #id

## Reconstructing tag history

<span style="color:red">Avoid it unless you are left with no other choise</span>, for example:

Recent screw-up in the BMTF data tag:
* O2O job was logging BMTF conditions non-stop since 2016
* In May of 2017 system's configuration that is not part of the online DB has changed
* BMTF prototype providing this "missing" part to O2O was not updated simultaneously
* Therefore, payloads produced after run #292445 are not correct

Missing IOV in EMTF data tag:
* In 2016 EMTF did not have a specification for O2O and had to be ignored
* While "cooking-up" EMTF tag history of 2016 I forgot a single IOV
* In 2017 O2O job continued populating this "broken" tag
* The problem was identified while merging noHackConditions PR

--- .class #id

## Changing the BMTF data tag

Solution (assuming you already sourced environment with PR #20939 merged):
* Initialize a local O2O sqlite:
<span style="font-size:smaller">
\``cmsRun ${CMSSW_RELEASE_BASE}/src/CondTools/L1TriggerExt/test/init_cfg.py useO2OTags=1 outputDBConnect=sqlite:l1config.db`\`
</span>
* Create _all_ prototypes, e.g.:
<span style="font-size:smaller">
`cmsRun L1TriggerConfig/Utilities/test/uploadBmtfParams.py`
</span>
* Copy the payloads of 2016 from CondDB to the local sqlite:
<span style="font-size:smaller">
\``conddb_import -f frontier://FrontierProd/CMS_CONDITIONS -c sqlite:l1config.db -b 1 -e 292445 -i L1TMuonBarrelParams_Stage2v0_hlt`\`
</span>
* Prepare list of runs and trigger keys
<span style="font-size:smaller">
\``ssh -f cmsusr 'ssh -f cms-conddb-1 "cat /data/O2O/L1T/v11.2/o2o-summary"' | sed -ne 's|.*-x||gp' > runs`\`
</span>
* Copy and tune [O2O script](https://github.com/kkotov/cmssw/blob/synchO2O_171013/CondTools/L1TriggerExt/scripts/runL1-O2O-iov.sh#L45)
so that <span style="color:green">PROTODB_OPTIONS</span> connects to 
<span style="font-size:smaller">`sqlite:l1config.db`</span>
* "Replay" O2O:
<span style="font-size:smaller">
`while read line ; do ./runL1-O2O-iov.sh -k BMTF $line ; done < runs`
</span>


--- .class #id

## Insert an IOV in the middle of EMTF data tag

* <span style="font-size:smaller">
`conddb_import -f frontier://FrontierProd/CMS_CONDITIONS -c sqlite:l1config.db -b 1 -e 305045 -i L1TMuonEndCapParams_Stage2v1_hlt`
</span>

* <span style="font-size:smaller">
`cmsRun L1TriggerConfig/Utilities/test/uploadEmtfParams.py`
</span>

* <span style="font-size:smaller">
`for run in 1 276215 279024 281797 282408 283171 284079 ; do conddb_copy_iov -i L1TMuonEndCapParams_Stage2v1_hlt -t L1TMuonEndCapParams_Stage2v2_hlt -c sqlite:l1config.db -s $run ; done`
</span>

* <span style="font-size:smaller">
`conddb_copy_iov -i L1TMuonEndCapParamsPrototype_Stage2v0_hlt -t L1TMuonEndCapParams_Stage2v2_hlt -s 1 -d 295039 -c sqlite:l1config.db`
</span>

* <span style="font-size:smaller">
`for run in 296935 298371 299844 300847 300894 302215 302821; do conddb_copy_iov -i L1TMuonEndCapParams_Stage2v1_hlt -t L1TMuonEndCapParams_Stage2v2_hlt -c sqlite:l1config.db -s $run ; done`
</span>


--- &twocol

## Current data tags

*** =left

System     |   Type[Tag]
-----------|-----------------
uGT        | <span style="font-weight:bold;font-size:smaller;color:green">L1TUtmTriggerMenu[_Stage2v0_hlt]</span>
uGT RS     | <span style="font-weight:bold;font-size:smaller;color:green">L1TGlobalPrescalesVetos[_Stage2v0_hlt]</span>
CALOL{1,2} | <span style="font-weight:bold;font-size:smaller;color:green">L1TCaloParams[_Stage2v3_hlt]</span>
uGMT       | <span style="font-weight:bold;font-size:smaller;color:green">L1TMuonGlobalParams[_Stage2v0_hlt]</span>

*** =right

System     |   Type[Tag]
-----------|-----------------
BMTF       | <span style="font-weight:bold;font-size:smaller;color:red">L1TMuonBarrelParams[_Stage2v2_hlt]</span>
OMTF       | <span style="font-weight:bold;font-size:smaller;color:blue">L1TMuonOverlapParams[_Stage2v0_hlt]</span>
EMTF       | <span style="font-weight:bold;font-size:smaller;color:red">L1TMuonEndCapParams[_Stage2v3_hlt]</span>
EMTF       | <span style="font-weight:bold;font-size:smaller;color:blue">L1TMuonEndCapForest[_Stage2v1_hlt]</span>

*** =fullwidth
<br>
<span style="font-weight:bold;color:red">L1TMuonBarrelParams[_Stage2v2_hlt]</span>:
* tag history of past 2 months needs to be copied from v1 to v2 and O2O has to switch to v2

<span style="font-weight:bold;color:red">L1TMuonEndCapParams[_Stage2v3_hlt]</span>:
* need to switch v1$\rightarrow$v3 in O2O 

<span style="font-weight:bold;color:blue">OverlapParams</span> and <span style="font-weight:bold;color:blue">EndCapForests</span>: 
* static payloads that rarely change; whenever update is needed follow [instructions](https://github.com/kkotov/l1o2o/)

--- .class #id

## Current Monte Carlo tags

<span style="font-weight:bold;color:brown">uGT:</span>
[L1Menu_Collisions2017_v4](https://cms-conddb.cern.ch/cmsDbBrowser/list/Prod/tags/L1Menu_Collisions2017_v4)

<span style="font-weight:bold;color:brown">uGTrs:</span>
[L1TGlobalPrescalesVetos_passThrough_mc](https://cms-conddb.cern.ch/cmsDbBrowser/list/Prod/tags/L1TGlobalPrescalesVetos_passThrough_mc)
* a single prescale set with all prescales = 1 and disabled masks/vetos 

<span style="font-weight:bold;color:brown">CALO:</span>
[L1TCaloParams_static_v96.47_2017_v1_8_4](https://cms-conddb.cern.ch/cmsDbBrowser/list/Prod/tags/L1TCaloParams_static_v96.47_2017_v1_8_4)

<span style="font-weight:bold;color:brown">uGMT:</span>
[L1TMuonGlobalParams_static_v94.6.1](https://cms-conddb.cern.ch/cmsDbBrowser/list/Prod/tags/L1TMuonGlobalParams_static_v94.6.1)

<span style="font-weight:bold;color:brown">BMTF:</span>
[L1TMuonBarrelParams_static_v94.6.1](https://cms-conddb.cern.ch/cmsDbBrowser/list/Prod/tags/L1TMuonBarrelParams_static_v94.6.1)

<span style="font-weight:bold;color:brown">OMTF:</span>
[L1TMuonOverlapParams_static_2016_mc](https://cms-conddb.cern.ch/cmsDbBrowser/list/Prod/tags/L1TMuonOverlapParams_static_2016_mc)

<span style="font-weight:bold;color:brown">EMTF:</span>
[L1TMuonEndCapParams_static_v96.47_2017_MC](https://cms-conddb.cern.ch/cmsDbBrowser/list/Prod/tags/L1TMuonEndCapParams_static_v96.47_2017_MC)

<span style="font-weight:bold;color:brown">EMTF Forest 2017:</span>
[L1TMuonEndCapForest_static_Sq_20170613_v7_mc](https://cms-conddb.cern.ch/cmsDbBrowser/list/Prod/tags/L1TMuonEndCapForest_static_Sq_20170613_v7_mc)



--- .class #id

## TODO


