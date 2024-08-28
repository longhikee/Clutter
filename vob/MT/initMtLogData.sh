#!/bin/bash
LOGDIR=/home/brantz/mt_log
TOP=/home/brantz/HSS
HSS=${TOP}/ims_hss1

TestSuiteUpdate=${TOP}/ims_mt/scripts/robot/TestSuiteUpdate.py
RUN="${TOP}/ims_mt/scripts/run_module_tests_log.pl ${TOP}/ims_mt/configs/HSS/config.xml"
LOGS=${TOP}/ims_mt/logs/TC*.log

source /home/brantz/.bash_profile


S6A=${HSS}/moduletest/testcases/HSS/LTE/S6A

S6C=${HSS}/moduletest/testcases/HSS/LTE/S6C

S6MN=${HSS}/moduletest/testcases/HSS/LTE/S6MN

S6T=${HSS}/moduletest/testcases/HSS/LTE/S6T

SLH=${HSS}/moduletest/testcases/HSS/LTE/SLH

SWX=${HSS}/moduletest/testcases/HSS/LTE/SWX

WX=${HSS}/moduletest/testcases/HSS/LTE/WX

HSSLI=${HSS}/moduletest/testcases/HSS/HSSLI

CX=${HSS}/moduletest/testcases/HSS/IMS/CX

HD=${HSS}/moduletest/testcases/HSS/IMS/HD

LLB=${HSS}/moduletest/testcases/HSS/IMS/LLB

SH=${HSS}/moduletest/testcases/HSS/IMS/SH

UHHD=${HSS}/moduletest/testcases/HSS/LTE/UHHD

ZH=${HSS}/moduletest/testcases/HSS/IMS/ZH

IWK=${HSS}/moduletest/testcases/HSS/IWK5GNewDM

UDICOM=${HSS}/moduletest/testcases/HSS/LTE/UDICOM

folders=($S6A $S6C $S6MN $S6T $SLH $SWX $WX $HSSLI $CX $HD $LLB $SH $UHHD $ZH $IWK $UDICOM)
#folders=($ZH $HD)

updateRepo()
{
  cd $TOP/ims_hss1
  git clean -fdx;git co *

  cd $TOP
  ./pull.sh
  ./pull.sh

  cd $TOP/ims_do
  git clean -fdx

  cd $HSS
  gm libTFRFormatterHelper -cld;gm libUMSstrcCframe -cld;gm ums_mt -cld -gf -j5
  return $?
}

clean()
{
  rm ${LOGDIR}/*
  cd $HSS
  git clean -fdx
  cd $TOP/ims_mt
  git clean -fdx
}

clean
updateRepo
if [ $? -eq 0 ];then
  echo "build success"
  rm /home/brantz/log-database/*
  rm -rf ~/MT-TOOL-BUILD-FAILURE.txt
else
  echo "build failure"
  touch ~/MT-TOOL-BUILD-FAILURE.txt
  exit 1
fi

for folder in ${folders[@]}
do
  echo "TestSuiteUpdate ${folder}"
   cd $TOP/ims_mt
  ${TestSuiteUpdate} ${folder}
  ${RUN}
  mv ${LOGS} ${LOGDIR}
  /home/brantz/MT-Log-Search/CookFiles > /dev/null
  clean
done

//autosave tool usage this week
date "+%Y-%m-%d" | tr '\n' '\t' >> /home/brantz/Documents/Mt_Tool_Usage.log
curl 127.0.0.1:9999/counter >> /home/brantz/Documents/Mt_Tool_Usage.log

pkill -9 ServerHttp
/home/brantz/MT-Log-Search/ServerHttp &

