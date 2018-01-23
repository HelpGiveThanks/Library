January 15, 2018 15:51:11 Library.fmp12 - reportTagInfo -1-
test: report: reportTagInfo
#
#Admin tasks.
Set Error Capture [ On ]
Allow User Abort [ Off ]
#
#Turn off record load scripts.
Set Variable [ $$stoploadtestinfo; Value:1 ]
Set Variable [ $$stoploadCitation; Value:1 ]
#
#Note if in testing or reporting mode.
If [ Left ( Get (LayoutName) ; 6 ) = "report" ]
Set Variable [ $reportLayout; Value:1 ]
Else If [ Left ( Get (LayoutName) ; 6 ) ≠ "report" ]
Set Variable [ $testLayout; Value:1 ]
End If
Go to Layout [ “reportTagInfo” (testlearnReportTags) ]
#
#Go to testinfo layout.
Enter Find Mode [ ]
#
#Find and show all informational
#(Learn module) records tagged
#to this test section.
Set Field [ testlearnReportTags::kctestSubsectionInfo; "###" & $$testSubsection ]
Perform Find [ ]
#
#Clear brainstorm and test tags.
Set Variable [ $$tagBrainstorm ]
Set Variable [ $$tagtest ]
Set Variable [ $$tagRecordID ]
Set Variable [ $$tagEdit ]
#
#Now refind these same records on this
#testlearn layout to perform the next part of
#this script.
Go to Layout [ “learn2” (testlearn) ]
Enter Find Mode [ ]
Set Field [ testlearn::kctestSubsectionInfo; "###" & $$testSubsection ]
Perform Find [ ]
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
#the system checks each key.
# The left most 3 numbers are order
#numbers which the next script will copy,
#paste into the records' testOrder fields, and
#then sort based on this these temporary test
#order numbers.
Set Variable [ $$citationMatch; Value:"test" ]
Set Variable [ $$tagTest; Value:$$testSubsection ]
Perform Script [ “sortTestOrBrainstormTaggedLearnRecords” ]
#
If [ $reportLayout = 1 ]
Go to Layout [ “reportTagInfo” (testlearnReportTags) ]
Else If [ $testLayout = 1 ]
Go to Layout [ “testInfo” (testlearnReportTags) ]
End If
#
#Sort button script uses the "order" text to tell
#it to perform the next sort by date instead of
#by order number which is the default sort.
Set Field [ TEMP::TLTestSort; "order" ]
#
#Sort the records by order field.
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearnReportTags::orderTestInformation; based on value list:
“order Pulldown List”
testlearnReportTags::timestamp; descending ]
[ Restore; No dialog ]
#
#Return to record user was on at
#the start of this script.
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
#
#Turn loadcitation script back on and exit script.
Set Variable [ $$stoploadtestinfo ]
Set Variable [ $$stoploadCitation ]
Perform Script [ “loadTestInfo” ]
#
#
