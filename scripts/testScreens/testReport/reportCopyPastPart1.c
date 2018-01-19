January 15, 2018 15:41:22 Library.fmp12 - reportCopyPastPart1 -1-
test: report: reportCopyPastPart1
#
#
#Stop this script if any of the following are true:
#
#Test subject is locked.
If [ $$testSubjectIsLocked ≠ "" and Get ( LayoutName ) ≠ "defaultTest" and Get ( LayoutName ) ≠ "learnTest" ]
Show Custom Dialog [ Message: "The test subject — " & $$testSubjectIsLocked & " — is locked. To unlock, A) go back to the
setup node tag menu. B) Select this test subject. C) Click 'lock' and enter the password."; Default Button: “OK”, Commit:
“No” ]
Set Variable [ $exit; Value:1 ]
End If
#
#Primary node is locked.
If [ TEMP::primaryNodeIsLocked ≠ "" ]
If [ $exit = "" ]
Show Custom Dialog [ Message: "The default primary node — " & TEMP::DEFAULTNodePrimaryName & " — is locked.
Go to the Default Node Tag Menu and A) click 'lock' to unlock it, B) select an unlocked node for the primary node, or C)
create a new primary node."; Default Button: “OK”, Commit: “No” ]
Else
Show Custom Dialog [ Message: "ALSO, the default primary node — " & TEMP::DEFAULTNodePrimaryName & " — is
locked. Go to the Default Node Tag Menu and A) click 'lock' to unlock it, B) select an unlocked node for the primary
node, or C) create a new primary node."; Default Button: “OK”, Commit: “No” ]
End If
Set Variable [ $exit; Value:1 ]
End If
#
#If any of the above are true, then
#exit this script.
If [ $exit = 1 ]
Exit Script [ ]
End If
#
#
If [ $$finding ≠ "" ]
Set Variable [ $$Finding ]
Go to Field [ ]
Refresh Window
Select Window [ Name: "Report"; Current file ]
Refresh Window
Select Window [ Name: "Tag Menus"; Current file ]
Exit Script [ ]
End If
#
If [ testlearnReportTags::ktestSubject & $$reportNumber & "¶" = FilterValues ( testlearnReportTags::kcInUseOnReportSubsection ; $
$testSubject & $$reportNumber) ]
Go to Field [ ]
Show Custom Dialog [ Title: "!"; Message: "Already in use on this section of the report. Click on " & testlearnReportTags::
_Number & " on the Report screen to begin the process of moving it to a different slot. Click on a different slot to complete
the move."; Default Button: “OK”, Commit: “No” ]
Halt Script
End If
Set Variable [ $$finding; Value:testlearnReportTags::_Ltestlearn ]
Set Variable [ $$findingCaption; Value:testlearnReportTags::note ]
Set Variable [ $$window; Value:"Tag Menus" ]
Go to Field [ ]
Refresh Window
Select Window [ Name: "Report"; Current file ]
Refresh Window
#
