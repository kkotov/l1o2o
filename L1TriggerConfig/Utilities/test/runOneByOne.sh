#!/bin/bash

cd o2o/
rm -f l1config.db

cmsRun ../CMSSW_8_0_10_patch1/src/CondTools/L1TriggerExt/test/init_cfg.py useO2OTags=1 outputDBConnect=sqlite:./l1config.db outputDBAuth=./
initcode=$?
if [ $initcode -ne 0 ] ; then exit 1 ; fi

keys=$(cmsRun ../CMSSW_8_0_10_patch1/src/L1TriggerConfig/Utilities/test/viewTKEonline.py tscKey=$1 rsKey=$2 2>/dev/null | grep ' key: ')

keyscode=$?
if [ $keyscode -ne 0 ] ; then exit 2 ; fi

uGT_key=$(echo $keys | sed -n -e's|.*uGT *key: \([^ ]*\).*|\1|gp')
uGMT_key=$(echo $keys | sed -n -e's|.*uGMT *key: \([^ ]*\).*|\1|gp')
CALO_key=$(echo $keys | sed -n -e's|.*CALO *key: \([^ ]*\).*|\1|gp')
BMTF_key=$(echo $keys | sed -n -e's|.*BMTF *key: \([^ ]*\).*|\1|gp')
OMTF_key=$(echo $keys | sed -n -e's|.*OMTF *key: \([^ ]*\).*|\1|gp')
EMTF_key=$(echo $keys | sed -n -e's|.*EMTF *key: \([^ ]*\).*|\1|gp')

echo "uGT_key=$uGT_key uGMT_key=$uGMT_key CALO_key=$CALO_key BMTF_key=$BMTF_key OMTF_key=$OMTF_key EMTF_key=$EMTF_key"

cmsRun ../CMSSW_8_0_10_patch1/src/L1TriggerConfig/Utilities/test/dumpL1TUtmTriggerMenu.py systemKey=$uGT_key
ugtcode=$?

cmsRun ../CMSSW_8_0_10_patch1/src/L1TriggerConfig/Utilities/test/dumpL1TCaloParams.py systemKey=$CALO_key
caloparcode=$?

cmsRun ../CMSSW_8_0_10_patch1/src/L1TriggerConfig/Utilities/test/dumpL1TMuonBarrelParams.py systemKey=$BMTF_key
bmtfcode=$?

cmsRun ../CMSSW_8_0_10_patch1/src/L1TriggerConfig/Utilities/test/dumpL1TMuonGlobalParams.py systemKey=$uGMT_key
ugmtcode=$?

cmsRun ../CMSSW_8_0_10_patch1/src/L1TriggerConfig/Utilities/test/dumpL1TGlobalPrescalesVetos.py systemKey=$uGT_key
ugtrscode=$?

exitcode=0

if [ $ugtcode     -ne 0 ] ; then exitcode=`expr $exitcode + 10`; fi
if [ $caloparcode -ne 0 ] ; then exitcode=`expr $exitcode + 100`; fi
if [ $bmtfcode    -ne 0 ] ; then exitcode=`expr $exitcode + 1000`; fi
if [ $ugmtcode    -ne 0 ] ; then exitcode=`expr $exitcode + 10000`; fi
if [ $ugtrscode   -ne 0 ] ; then exitcode=`expr $exitcode + 100000`; fi

echo "Status codes: uGT: $ugtcode,  CALO: $caloparcode,  BMTF: $bmtfcode,  uGMT: $ugmtcode,  uGTrs: $ugtrscode,  Total: $exitcode"

exit $exitcode
