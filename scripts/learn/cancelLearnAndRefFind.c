January 17, 2018 11:30:40 Library.fmp12 - cancelLearnAndRefFind -1-
learn: cancelLearnAndRefFind
#
#This script is used by the findLearnRecord
#and findReferenceRecord scripts.
#
#
#!!! IMPORTANT !!! SAY WHAT !!! HERE YE, HERE YE !!!
#
#The cancel logic of this script is identical
#to the logic in the ActionLog's cancelFindSpecificAction
#script. Any changes made to this logic needs
#to also be made to that script to keep
#them identical.
#
#!!! IMPORTANT !!! SAY WHAT !!! HERE YE, HERE YE !!!
#
#
#BEGIN identical catch error logic
#
#
#Admin tasks.
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#Clear out any invalid find requests,
#otherwise script will fail to go back
# to the main layout.
Set Field [ testlearn::note; "" ]
Set Field [ testlearn::timestamp; "" ]
Set Field [ testlearn::brainstormCasePoint; "" ]
#
Set Variable [ $$clearUserFindRequests; Value:1 ]
Perform Script [ “CHUNK_findReferenceRecordUserFindRequests (new)” ]
Set Variable [ $$clearUserFindRequests ]
#
#Then return to the main layout.
If [ Get ( LayoutTableName ) = "reference" ]
#
If [ $$findReferenceLayout = "" ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “ReferenceStuff” (reference) ]
Else
Go to Layout [ “Reference” (reference) ]
End If
#
Else
Go to Layout [ $$findReferenceLayout ]
Set Variable [ $$findReferenceLayout ]
End If
Else
If [ $$findLearnLayout = "" ]
#
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “learnStuff3” (testlearn) ]
Else
Go to Layout [ “learn3” (testlearn) ]
End If
#
Else
Go to Layout [ $$findLearnLayout ]
Set Variable [ $$findLearnLayout ]
End If
End If
#
#Exit find mode.
Enter Browse Mode
#
#Only find all records if there are no records to
#show (the records the user was looking at
#before clicking find).
If [ Get (FoundCount) = 0 ]
Perform Script [ “findALL_LearnOrRefRecords (update moved from folder menuFind and name change findReference)” ]
End If
#
#Clear user find request variables.
Set Variable [ $$note ]
Set Variable [ $$timestamp ]
Set Variable [ $$brainstormCasePoint ]
#
#Clear out all the pause script requests.
Halt Script
#
#
#END identical cancel error logic
#
#
