January 15, 2018 15:43:23 Library.fmp12 - reportCopyPastPart3 -1-
test: report: reportCopyPastPart3
#
#
#BEGIN A
#
#COPY record key on Report window.
#
If [ Get ( ActiveFieldName ) = "kTag1" and $$finding = "" or
Get ( ActiveFieldName ) = "kTag2" and $$finding = "" or
Get ( ActiveFieldName ) = "kTag3" and $$finding = "" or
Get ( ActiveFieldName ) = "kTag4" and $$finding = "" ]
#
#If record slot is blank, there is nothing
#to copy so exit this script.
If [ $$finding = "" and Get (ActiveFieldContents) = "" ]
Go to Field [ ]
Halt Script
End If
#
#Copy tag record's key; then clear it
#from its current slot.
Set Variable [ $$finding; Value:Get ( ActiveFieldContents ) ]
Set Variable [ $$window; Value:"Report" ]
Refresh Window
Clear [ ]
[ Select ]
Go to Field [ ]
#
#Find this copied tag record in
#the Tag Menus window.
Select Window [ Name: "Tag Menus"; Current file ]
#
#Turn off record load script.
Set Variable [ $$stopLoadTestResultRecord; Value:1 ]
#
#First, check if record is a test result.
If [ Get (LayoutName) ≠ "reportTestResult" ]
#
#Find all test results for this subsection.
Go to Layout [ “reportTestResult” (testlearnReportTags) ]
Enter Find Mode [ ]
Set Field [ testlearnReportTags::ktestSubject; TEMP::kdefaultNodeTestSubject ]
Set Field [ testlearnReportTags::ktestSubsection; TEMP::ktestSubsection ]
Set Field [ testlearnReportTags::kreportNumber; TEMP::reportNumber ]
Perform Find [ ]
Set Variable [ $$citationMatch; Value:"testResult" ]
#
#Sort based on users current sort for
#test result records.
If [ TEMP::TLTestSort = "" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearnReportTags::date; descending
testlearnReportTags::timestamp; descending ]
[ Restore; No dialog ]
Else
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearnReportTags::orderTestResult; based on
value list: “testPulldownListANDsortOrderList”
testlearnReportTags::timestamp; descending ]
[ Restore; No dialog ]
End If
End If
Go to Field [ ]
#
#If it not selected, find and select it.
If [ $$finding ≠ testlearnReportTags::_Ltestlearn ]
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ $$finding = testlearnReportTags::_Ltestlearn ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
End If
#
#Turn back on record load script.
Set Variable [ $$stopLoadTestResultRecord ]
#
#If it is a test result record, return to the
#Report window and halt this script allowing
#the user to paste the test result into a
#yellow slot.
If [ $$finding = testlearnReportTags::_Ltestlearn ]
#
#If it is a test result record, note that
#it is copied and not in use.
Set Field [ testlearnReportTags::kcInUseOnReportSubsection; "" ]
#
Perform Script [ “loadReportTestResultRecord (new)” ]
#
Select Window [ Name: "Report"; Current file ]
Halt Script
End If
#
#
#
#If it is not a test result record, then it must
#be an info record. Find this record and
#then return to the Report window and halt
#this script allowing the user to paste its key
#into a yellow slot.
If [ $$finding ≠ testlearnReportTags::_Ltestlearn ]
#
#Turn off record load script and find
#all info records for this test section.
Set Variable [ $$stopPart3InProgress; Value:1 ]
Perform Script [ “reportTagInfo (update)” ]
#
#Find and select copied test info record.
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ $$finding = testlearnReportTags::_Ltestlearn ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Start to remove its key from this info record's
#keychain of pasted info records pasted
#on reports.
Set Variable [ $inUse; Value:testlearnReportTags::kcInUseOnReportSubsection ]
#
#Find out how many times its was used on the
#same report as a user can copy a learn record
#and paste it multiple times.
Set Variable [ $numberOfTimesUsedOnSameReport; Value:ValueCount ( FilterValues ( testlearnReportTags::
kcInUseOnReportSubsection ; $$testSubsection & $$testSubject & $$reportNumber & ¶ ) ) ]
#
#Remove all copies of the key.
Set Field [ testlearnReportTags::kcInUseOnReportSubsection; Substitute ( testlearnReportTags::
kcInUseOnReportSubsection ; $$testSubsection & $$testSubject & $$reportNumber & ¶ ; "" ) ]
Set Variable [ $inUse; Value:testlearnReportTags::kcInUseOnReportSubsection ]
#
#If it was used more than 1 time, put back
#the other copies still in use.
If [ $numberOfTimesUsedOnSameReport - 1 > 0 ]
Set Variable [ $countDown; Value:$numberOfTimesUsedOnSameReport - 1 ]
Loop
Set Field [ testlearnReportTags::kcInUseOnReportSubsection; $inUse & $$testSubsection & $$testSubject & $
$reportNumber & ¶ ]
Set Variable [ $inUse; Value:testlearnReportTags::kcInUseOnReportSubsection ]
Set Variable [ $countDown; Value:$countDown - 1 ]
Exit Loop If [ $countDown = 0 ]
End Loop
End If
#
#Turn back on record load script.
Set Variable [ $$stopPart3InProgress ]
#
#Reset conditional formatting variables, then
#return to the Report window and halt
#this script allowing the user to paste
#the info record's key into a yellow slot.
Perform Script [ “loadTestInfo (update)” ]
#
Select Window [ Name: "Report"; Current file ]
Halt Script
End If
#
#END A
#
#
#
#
#
#BEGIN B
#
#PASTE record key copied from the Report
#window into a BLANK slot.
#
Else If [ Get ( ActiveFieldName ) = "kTag1" and Get ( ActiveFieldContents )="" and $$finding ≠ "" and $$window = "Report"
 or
Get ( ActiveFieldName ) = "kTag2" and Get ( ActiveFieldContents )="" and $$finding ≠ "" and $$window = "Report"
 or
Get ( ActiveFieldName ) = "kTag3" and Get ( ActiveFieldContents )="" and $$finding ≠ "" and $$window = "Report"
 or
Get ( ActiveFieldName ) = "kTag4" and Get ( ActiveFieldContents )="" and $$finding ≠ "" and $$window = "Report" ]
#
#Paste record key selected into blank slot.
Set Field [ $$finding ]
Go to Field [ ]
#
#Find this pasted tag record
#in the Tag Menus window.
Select Window [ Name: "Tag Menus"; Current file ]
#
#Turn off record load script.
Set Variable [ $$stopLoadTestResultRecord; Value:1 ]
#
#First, check if record is a test result.
If [ Get (LayoutName) ≠ "reportTestResult" ]
#
#Find all test results for this subsection.
Go to Layout [ “reportTestResult” (testlearnReportTags) ]
Enter Find Mode [ ]
Set Field [ testlearnReportTags::ktestSubject; TEMP::kdefaultNodeTestSubject ]
Set Field [ testlearnReportTags::ktestSubsection; TEMP::ktestSubsection ]
Set Field [ testlearnReportTags::kreportNumber; TEMP::reportNumber ]
Perform Find [ ]
Set Variable [ $$citationMatch; Value:"testResult" ]
#
#Sort based on users current sort for
#test result records.
If [ TEMP::TLTestSort = "" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearnReportTags::date; descending
testlearnReportTags::timestamp; descending ]
[ Restore; No dialog ]
Else
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearnReportTags::orderTestResult; based on
value list: “testPulldownListANDsortOrderList”
testlearnReportTags::timestamp; descending ]
[ Restore; No dialog ]
End If
End If
#
#Find the copied record, if it is not selected.
If [ $$finding ≠ testlearnReportTags::_Ltestlearn ]
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ $$finding = testlearnReportTags::_Ltestlearn ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
End If
#
#Turn back on record load script.
Set Variable [ $$stopLoadTestResultRecord ]
#
#If it is a test result record, note that
#it is now in use.
If [ $$finding = testlearnReportTags::_Ltestlearn ]
Set Field [ testlearnReportTags::kcInUseOnReportSubsection; $$testSubject & $$reportNumber & "¶" ]
#
#Return to the Report window and
#halt this script after clearing yellow
#conditional formatting variables.
Set Variable [ $$finding ]
Set Variable [ $$window ]
Perform Script [ “loadReportTestResultRecord (new)” ]
#
Select Window [ Name: "Report"; Current file ]
Refresh Window
Halt Script
End If
#
#
#
#If it is not a test result record, then it must
#be an info record. Find this record and
#then return to the Report window and halt
#this script after noting that this info record is
#being used on this test subject's report.
If [ $$finding ≠ testlearnReportTags::_Ltestlearn ]
#
#Turn off record load script and find
#all info records for this test section.
Set Variable [ $$stopPart3InProgress; Value:1 ]
Perform Script [ “reportTagInfo (update)” ]
#
#Find and select copied test info record.
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ $$finding = testlearnReportTags::_Ltestlearn ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Insert test-subject's key and report number
#into this info record's keychain.
Set Variable [ $inUse; Value:testlearnReportTags::kcInUseOnReportSubsection ]
Set Field [ testlearnReportTags::kcInUseOnReportSubsection; $inUse & $$testSubsection & $$testSubject & $
$reportNumber & ¶ ]
#
#Turn back on record load script.
Set Variable [ $$stopPart3InProgress ]
#
#Return to the Report window and
#halt this script after clearing yellow
#conditional formatting variables.
Set Variable [ $$finding ]
Set Variable [ $$window ]
Perform Script [ “loadTestInfo (update)” ]
#
Select Window [ Name: "Report"; Current file ]
Refresh Window
Halt Script
End If
#
#END B
#
#
#
#
#
#BEGIN C
#
#PASTE record key copied from Report window
#into an OCCUPIED slot.
#
#If user has selected to insert a copied finding from the Report window,
#into a slot already occupied,
#PREVENT USER FROM DOING SO. DISABLE PART C.
Else If [ Get ( ActiveFieldName ) = "kTag1" and Get ( ActiveFieldContents ) ≠ "" and $$window = "Report"
 or
Get ( ActiveFieldName ) = "kTag2" and Get ( ActiveFieldContents ) ≠ "" and $$window = "Report"
or
Get ( ActiveFieldName ) = "kTag3" and Get ( ActiveFieldContents ) ≠ "" and $$window = "Report"
 or
Get ( ActiveFieldName ) = "kTag4" and Get ( ActiveFieldContents ) ≠ ""and $$window = "Report" ]
Go to Field [ ]
#
#Inform user that they can past only
#into empty slots.
Show Custom Dialog [ Message: "Click the X button to clear this slot before pasting anything into it."; Default Button: “OK”,
Commit: “No” ]
Exit Script [ ]
#
#END C
#
#
#
#
#
#BEGIN D
#
#PASTE record key copied from Tag Menus
#window into an OCCUPIED slot.
#
#Prevent pasting keys into occupied slots.
Else If [ Get ( ActiveFieldName ) = "kTag1" and Get ( ActiveFieldContents ) ≠ "" and $$window = "Tag Menus"
 or
Get ( ActiveFieldName ) = "kTag2" and Get ( ActiveFieldContents ) ≠ "" and $$window = "Tag Menus"
or
Get ( ActiveFieldName ) = "kTag3" and Get ( ActiveFieldContents ) ≠ "" and $$window = "Tag Menus"
 or
Get ( ActiveFieldName ) = "kTag4" and Get ( ActiveFieldContents ) ≠ ""and $$window = "Tag Menus" ]
Go to Field [ ]
#
#Inform user that they can past only
#into empty slots.
Show Custom Dialog [ Message: "Click the X button to clear this slot before pasting anything into it."; Default Button: “OK”,
Commit: “Yes” ]
Exit Script [ ]
End If
#
#END D
#
#
#
#
#
#BEGIN E
#
#PASTE record key copied from Tag Menus
#into a BLANK slot.
#
#Paste record key selected blank slot.
Set Field [ $$finding ]
Set Field [ $$finding ]
Go to Field [ ]
#
#Find and this pasted tag record
#in the Tag Menus window.
Select Window [ Name: "Tag Menus"; Current file ]
#
#Turn off record load script.
Set Variable [ $$stopLoadTestResultRecord; Value:1 ]
#
#First, check if record is a test result.
If [ Get (LayoutName) ≠ "reportTestResult" ]
#
#Find all test results for this subsection.
Go to Layout [ “reportTestResult” (testlearnReportTags) ]
Enter Find Mode [ ]
Set Field [ testlearnReportTags::ktestSubject; TEMP::kdefaultNodeTestSubject ]
Set Field [ testlearnReportTags::ktestSubsection; TEMP::ktestSubsection ]
Set Field [ testlearnReportTags::kreportNumber; TEMP::reportNumber ]
Perform Find [ ]
Set Variable [ $$citationMatch; Value:"testResult" ]
#
#Sort based on users current sort for
#test result records.
If [ TEMP::TLTestSort = "" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearnReportTags::date; descending
testlearnReportTags::timestamp; descending ]
[ Restore; No dialog ]
Else
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearnReportTags::orderTestResult; based on value
list: “testPulldownListANDsortOrderList”
testlearnReportTags::timestamp; descending ]
[ Restore; No dialog ]
End If
End If
Go to Field [ ]
#
#Find the copied record, if it is not selected.
If [ $$finding ≠ testlearnReportTags::_Ltestlearn ]
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ $$finding = testlearnReportTags::_Ltestlearn ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
End If
#
#Turn back on record load script.
Set Variable [ $$stopLoadTestResultRecord ]
#
#If it is a test result record, note that
#it is now in use.
If [ $$finding = testlearnReportTags::_Ltestlearn ]
Set Field [ testlearnReportTags::kcInUseOnReportSubsection; $$testSubject & $$reportNumber & "¶" ]
#
#Return to the Report window and
#halt this script after clearing yellow
#conditional formatting variables.
Set Variable [ $$finding ]
Set Variable [ $$window ]
Perform Script [ “loadReportTestResultRecord (new)” ]
#
Select Window [ Name: "Report"; Current file ]
Refresh Window
Halt Script
End If
#
#
#
#If it is not a test result record, then it must
#be an info record. Find this record and
#then return to the Report window and halt
#this script after noting that this info record is
#being used on this test subject's report.
If [ $$finding ≠ testlearnReportTags::_Ltestlearn ]
#
#Turn off record load script and find
#all info records for this test section.
Set Variable [ $$stopPart3InProgress; Value:1 ]
Perform Script [ “reportTagInfo (update)” ]
#
#Find and select copied test info record.
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ $$finding = testlearnReportTags::_Ltestlearn ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Insert test-subject's key and report number
#into this info record's keychain.
Set Variable [ $inUse; Value:testlearnReportTags::kcInUseOnReportSubsection ]
Set Field [ testlearnReportTags::kcInUseOnReportSubsection; $inUse & $$testSubsection & $$testSubject & $$reportNumber &
¶ ]
#
#Turn back on record load script.
Set Variable [ $$stopPart3InProgress ]
#
#Return to the Report window and
#halt this script after clearing yellow
#conditional formatting variables.
Set Variable [ $$finding ]
Set Variable [ $$window ]
Perform Script [ “loadTestInfo (update)” ]
#
Select Window [ Name: "Report"; Current file ]
Refresh Window
Halt Script
End If
#
#END E
#
