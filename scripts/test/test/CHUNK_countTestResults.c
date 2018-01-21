January 21, 2018 11:24:34 Library.fmp12 - CHUNK_countTestResults -1-
test: test: CHUNK_countTestResults
#Add 1 to test results count.
Set Variable [ $count; Value:testlearn::countOfALLSubsectionsTestResults ]
Set Field [ testlearn::countOfALLSubsectionsTestResults; $count + 1 ]
