REM ESV1TEST TEST ESDS VAR LENGTH VSAM FILE SEQ AND RANDOM RBA/XRBA
REM RUN ESV1TEST TO CREATE AND TEST ESDS WITH 3 80 BYTE RCDS
SET QFILE=vsam\test\ESV1.TQ1
SET VFILE=vsam\test\TESTCAT.ESV1
erase vsam\test\ESV1.TQ1
erase vsam\test\ESV1.VES
erase vsam\test\ESV1.VX0
CALL ASMLG vsam\test\ESV1TEST %1 %2 %3 %4 %5 %6 %7 %8 %9
IF ERRORLEVEL 1 PAUSE ERROR IN ESV1TEST
