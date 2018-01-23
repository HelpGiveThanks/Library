January 15, 2018 14:59:35 Library.fmp12 - loadTestResultRecord -1-
test: test: loadTestResultRecord
#
#
#Admin tasks.
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#Prevents script from running to speed up other
#scripts that keep calling it up by looping thru
#multiple records.
If [ $$stopLoadTestRecord = 1 ]
Exit Script [ ]
End If
#
#Set record's variables.
Set Variable [ $$evidenceToBeTagged; Value:testlearn::_Ltestlearn ]
Set Variable [ $$taggedEvidence; Value:testlearn::kcKeywordOther ]
#Clear before loading any item keys.
Set Variable [ $$checkedTestItem ]
Set Variable [ $$checkedTestItem; Value:testlearn::kctestResultCheckedItems ]
#
#Get return window name, and the refresh
#conditonal formatting in the Tag Menus
#window, and return this test record window.
Set Variable [ $windowName; Value:Get (WindowName) ]
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
#
#When a user creates a new test result, this
#variable becomes active, so when this script
#runs, it will perform the create form script.
#This is done by this load script to reduce the
#flashing back-and-forth between windows.
#Since the load script is on the Tag Menus
#window where this create form script starts, it
#is most efficient if it is started here.
If [ $$addFormToNewTestResult ≠ "" ]
Perform Script [ “createFormOutOf_FT_TestItems” ]
Set Variable [ $$addFormToNewTestResult ]
End If
#
#Return to the test or report window.
Select Window [ Name: $windowName; Current file ]
Refresh Window
#
#
