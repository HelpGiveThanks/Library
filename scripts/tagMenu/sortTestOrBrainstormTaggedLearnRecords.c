January 20, 2018 18:26:34 Library.fmp12 - sortTestOrBrainstormTaggedLearnRecords -1-
tagMenu: sortTestOrBrainstormTaggedLearnRecords
#
#Used by the following scripts:
#reportTagInfo
#addTagToMainRecord
#sortButtonLearnLayouts
#loadItemRecordForBrainstormTagMenu
#loadTestSectionAndTaggedLearnRecords
#
#Perform script for brainstorm and test tags only.
If [ $$citationMatch = "brainstorm" or $$citationMatch = "test"
 or
Left ( Get (LayoutName) ; 4 ) = "test" ]
#
#Make a key for the current record's lock so after
#this sort is complete the system can go back to
#this record.
Set Variable [ $recordKey; Value:testlearn::_Ltestlearn ]
#
#Turn off the loadcitation script to speed up the
#loop portion of the script.
Set Variable [ $$stoploadCitation; Value:1 ]
#
#Check if the user does or does not want brainstorm
#test learn table records sorted by order number.
#If they do (the tlbrainstormsort is blank) then sort
#by order number.
If [ TEMP::TLBrainstormSort = "order" and $$citationMatch = "brainstorm" ]
#
#Set the TLBrainstormSort field with a 1. Now if user
#clicks the sort button it will be because they
#now want the records sorted by date.
Set Field [ TEMP::TLBrainstormSort; 1 ]
#
#To speed up the process, sort to the top the records
#that have ksample numbers. Do not loop thru
#records whose ksample records are blank.
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::kcbrainstorm; descending ]
[ Restore; No dialog ]
#
#Go the first record.
Go to Record/Request/Page
[ First ]
#
#Check the brainstorm key fields if in
#brainstorm mode.
If [ $$citationMatch = "brainstorm" ]
Loop
#The first step is to blank or clear each record's
#order field, so only those records that are part
#of the current brainstorm or test will have order numbers
#and be part of the sort coming right after this
#assignment of sort order numbers.
Set Field [ testlearn::orderTestInformation; "" ]
Exit Loop If [ testlearn::kcbrainstorm = "" ]
#
#The order number is the left three digits of a
#brainstorm or test record lock number. ( Remember
#each record in the database has lock number or
#ID number. To open the lock and see any record's
#contents requires a key number that fits the lock.
#So if a lock number is 123, then the key that will
#fit this lock is 123 too. ) Because the brainstorm
#and test key fields (think of key chains) may
#have several keys, because any one learn record
#may be part of more than one brainstorm or test.
#the system must check each learn record's keys
#one at a time to see if any fit the current brainstorm
#or test's lock. So beginning with number one
#the system checks each key. The left most 3 numbers
#are order numbers so below you will note that
#they system starts the check on the 4th number
#from the left.
Set Variable [ $number; Value:1 ]
Go to Field [ ]
Loop
#
If [ Middle ( GetValue ( testlearn::kcbrainstorm ; $number ) ; 4 ; 42 ) & "¶" = $$tagBrainstorm & "¶" ]
#
#When and if a key is found that fits the current
#brainstorm or test record's lock, the order number
#( left most 3 digits ) is caputred and placed in
#in the order field.
Set Field [ testlearn::orderTestInformation; Left ( GetValue ( testlearn::kcbrainstorm ; $number ) ; 3 ) ]
#
#The 'number' variable is made blank to trigger
#the exit from this loop, the order number having
#been assigned.
Set Variable [ $number ]
// Else If [ Middle ( GetValue ( testlearn::kcbrainstorm ; $number ) ; 4 ; 42 ) & "¶" ≠ $$tagBrainstorm ]
// Set Field [ testlearn::orderTestInformation; "" ]
End If
Exit Loop If [ $number = "" ]
#
#Exit loop if the current record is not part
#of the selected brainstorm or test after checking
#all of its keys.
Exit Loop If [ GetValue ( testlearn::kcbrainstorm ; $number ) = "" ]
#
#Add 1 to the 'number' varaible after each key
#in the key field is checked, to direct the system
#to check the next key.
Set Variable [ $add; Value:$number ]
Set Variable [ $number; Value:$add + 1 ]
End Loop
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
End If
#
#Sort the records by order field.
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::orderTestInformation; based on value list:
“testPulldownListANDsortOrderList”
testlearn::timestamp; descending ]
[ Restore; No dialog ]
#
#Return to record user was on at
#the start of this script.
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
Loop
Exit Loop If [ $recordkey = testlearn::_Ltestlearn ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Turn loadcitation script back on and exit script.
Set Variable [ $$stoploadCitation ]
Exit Script [ ]
End If
#
#
#
#
#Check if the user does or does not want
#learn records sorted by order number.
#If they do (the TLTestSort is blank) then sort
#by order number.
If [ TEMP::TLTestSort = "order" and $$citationMatch = "test" ]
#
#To speed up the process, sort to the top the records
#that have kbrainstorm numbers. Do not loop thru
#records whose kbrainstorm records are blank.
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::kctestSubsectionInfo; descending ]
[ Restore; No dialog ]
#
#Go the first record.
Go to Record/Request/Page
[ First ]
#
#Check the test key fields if in brainstorm mode.
If [ $$citationMatch = "test" ]
Loop
#
#The first step is to blank or clear each record's
#order field, so only those records that are part
#of the current brainstorm or test will have order numbers
#and be part of the sort coming right after this
#assignment of sort order numbers.
Set Field [ testlearn::orderTestInformation; "" ]
Exit Loop If [ testlearn::kctestSubsectionInfo = "" ]
#
#The order number is the left three digits of a
#brainstorm or test record lock number. ( Remember
#each record in the database has lock number or
#ID number. To open the lock and see any record's
#contents requires a key number that fits the lock.
#So if a lock number is 123, then the key that will
#fit this lock is 123 too. ) Because the brainstorm
#and test key fields (think of key chains) may
#have several keys, because any one learn record
#may be part of more than one brainstorm or test,
#the system must check each learn record's keys
#one at a time to see if any fit the current brainstorm
#or test's lock. So beginning with number one
#the system checks each key. The left most 3 numbers
#are order numbers so below you will note that
#they system starts the check on the 4th number
#from the left.
Set Variable [ $number; Value:1 ]
Go to Field [ ]
Loop
If [ Middle ( GetValue ( testlearn::kctestSubsectionInfo ; $number ) ; 4 ; 42 ) & "¶" = $$tagtest & ¶ ]
#
#When and if a key is found that fits the current
#brainstorm or test record's lock, the order number
#( left most 3 digits ) is caputred and placed in
#in the order field.
Set Field [ testlearn::orderTestInformation; Left ( GetValue ( testlearn::kctestSubsectionInfo ; $number ) ;
3 ) ]
#
#The 'number' variable is made blank to trigger
#the exit from this loop, the order number having
#been assigned.
Set Variable [ $number ]
End If
Exit Loop If [ $number = "" ]
#
#Exit loop if the current record is not part
#of the selected brainstorm or test after checking
#all of its keys.
Exit Loop If [ GetValue ( testlearn::kctestSubsectionInfo ; $number ) = "" ]
#
#Add 1 to the 'number' varaible after each key
#in the key field is checked, to direct the system
#to check the next key.
Set Variable [ $add; Value:$number ]
Set Variable [ $number; Value:$add + 1 ]
End Loop
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
End If
#
#Sort the records by order field.
If [ Right ( Get (LayoutName) ; 4 ) = "info" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearnReportTags::orderTestInformation; based
on value list: “testPulldownListANDsortOrderList”
testlearnReportTags::timestamp; descending ]
[ Restore; No dialog ]
Else
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::orderTestInformation; based on value list:
“testPulldownListANDsortOrderList”
testlearn::timestamp; descending ]
[ Restore; No dialog ]
End If
#
#Return to record user was on at
#the start of this script.
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
Loop
Exit Loop If [ $recordkey = testlearn::_Ltestlearn ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Turn loadcitation script back on, load up the
#selected Learn records variables (just in case
#the user came here via the edit/new button in
#the test module), and exit script.
Set Variable [ $$stoploadCitation ]
#
Set Variable [ $$citationRecord; Value:testlearn::_Ltestlearn ]
Set Variable [ $$node; Value:testlearn::kNodeOther ]
Set Variable [ $$primaryNode; Value:testlearn::kNodePrimary ]
Set Variable [ $$copyright; Value:testlearn::kcopyright ]
Set Variable [ $$ref; Value:testlearn::kcreference ]
Set Variable [ $$PrimaryKey; Value:testlearn::kKeywordPrimary ]
Set Variable [ $$Key; Value:testlearn::kcKeywordOther ]
Set Variable [ $$OtherKey; Value:testlearn::kcKeywordOther ]
Set Variable [ $$test; Value:testlearn::kctestSubsectionInfo ]
Set Variable [ $$brainstorm; Value:testlearn::kcbrainstorm ]
Set Variable [ $$RecordID; Value:Get (RecordID) ]
#
#Note if record is locked to protect its tags.
If [ tagTLNodePrimary::orderOrLock ≠ "" ]
Set Variable [ $$lockedMainLearnRecord; Value:tagTLNodePrimary::tag ]
Else
Set Variable [ $$lockedMainLearnRecord ]
End If
Exit Script [ ]
End If
#
End If
